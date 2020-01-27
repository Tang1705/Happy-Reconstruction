//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
//=============================================================================
// $Id: EventsEx_C.c 317691 2017-03-02 18:42:42Z erich $
//=============================================================================

#if defined(_WIN32) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "C/FlyCapture2_C.h"
#include <stdio.h>

//
// User-supplied data structure which is passed to the callback function (along
// with other parameters) when the event is triggered, which in turn issues the
// callback function.
//
typedef struct _CustomUserDataStruct
{
    int i;
    char c;
} CustomUserDataStruct;

// User-supplied callback function to run when an event is triggered.
void SimpleCallback(void *cbData)
{
    CustomUserDataStruct *pUserData;

    if (cbData)
    {
        //
        // Determine which type of event triggered this callback to be issued.
        //
        fc2EventCallbackData *pData = (fc2EventCallbackData *)cbData;
        if (pData->EventName)
        {
            printf("Received callback for event: 0x%04llX.\n", pData->EventID);
        }
        else
        {
            printf("Error: Event name/type invalid.\n");
        }

        //
        // Print out the time at which this event was generated (from the
        // camera's perspective).
        // This helps to sequence image/event ordering.
        //
        printf("Timestamp: %lld\n", pData->EventTimestamp);

        //
        // Retrieve and print the user-supplied data. In this case, where we
        // register for notification of the End of Exposure (EoE) event, this
        // might be where you signal your external motorized stage or converyor
        // belt to provide a new region of interest to the camera so that
        // another image acquisiton can be manually triggered while data from a
        // previously captured image is being fed to the host computer, allowing
        // for greater throughput than one would achieve by simply waiting for
        // an image transfer to complete before starting another.
        //
        pUserData = (CustomUserDataStruct *)pData->EventUserData;
        if (pUserData &&
            (pData->EventUserDataSize == sizeof(CustomUserDataStruct)))
        {
            printf("User Data: i=%d c=%c.\n", pUserData->i, pUserData->c);
        }
        else
        {
            printf("Error parsing user data.\n");
        }
    }
    else
    {
        printf("No callback data provided.\n");
    }

    return;
}

void PrintBuildInfo()
{
    fc2Version version;
    char versionStr[512];
    char timeStamp[512];

    fc2GetLibraryVersion(&version);

    sprintf(versionStr,
            "FlyCapture2 library version: %d.%d.%d.%d\n",
            version.major,
            version.minor,
            version.type,
            version.build);

    printf("%s", versionStr);

    sprintf(timeStamp, "Application build date: %s %s\n\n", __DATE__, __TIME__);

    printf("%s", timeStamp);
}

void PrintCameraInfo(fc2Context context)
{
    fc2Error error;
    fc2CameraInfo camInfo;
    error = fc2GetCameraInfo(context, &camInfo);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2GetCameraInfo: %s\n", fc2ErrorToDescription(error));
    }

    printf("\n*** CAMERA INFORMATION ***\n"
           "Serial number - %u\n"
           "Camera model - %s\n"
           "Camera vendor - %s\n"
           "Sensor - %s\n"
           "Resolution - %s\n"
           "Firmware version - %s\n"
           "Firmware build time - %s\n\n",
           camInfo.serialNumber,
           camInfo.modelName,
           camInfo.vendorName,
           camInfo.sensorInfo,
           camInfo.sensorResolution,
           camInfo.firmwareVersion,
           camInfo.firmwareBuildTime);
}

void SetTimeStamping(fc2Context context, BOOL enableTimeStamp)
{
    fc2Error error;
    fc2EmbeddedImageInfo embeddedInfo;

    error = fc2GetEmbeddedImageInfo(context, &embeddedInfo);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2GetEmbeddedImageInfo: %s\n", fc2ErrorToDescription(error));
    }

    if (embeddedInfo.timestamp.available != 0)
    {
        embeddedInfo.timestamp.onOff = enableTimeStamp;
    }

    error = fc2SetEmbeddedImageInfo(context, &embeddedInfo);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2SetEmbeddedImageInfo: %s\n", fc2ErrorToDescription(error));
    }
}

int GrabImages(fc2Context context, int numImagesToGrab)
{
    fc2Error error;
    fc2Image rawImage;
    fc2TimeStamp prevTimestamp = {0};
    CustomUserDataStruct UserDataEOE;
    int i;

    //
    // Register for End of Exposure (EoE) event. We simply create an instance of
    // the EventOptions structure, populate it, and register it with the camera.
    //
    fc2EventOptions optEOE;
    optEOE.EventName = "EventExposureEnd";
    optEOE.EventCallbackFcn = &SimpleCallback;
    UserDataEOE.i = 1;
    UserDataEOE.c = 'a';
    optEOE.EventUserData = (void *)&UserDataEOE;
    optEOE.EventUserDataSize = sizeof(CustomUserDataStruct);

    error = fc2RegisterEvent(context, &optEOE);
    if (error != FC2_ERROR_OK)
    {
		printf("Error registering for events: %s.\n", fc2ErrorToDescription(error));
        return -1;
    }
    else
    {
        printf("Successfully registered event:%s", optEOE.EventName);
    }

    // Create buffer to store retrieved raw image data
    error = fc2CreateImage(&rawImage);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2CreateImage: %s.\n", fc2ErrorToDescription(error));
        return -1;
    }

    for (i = 0; i < numImagesToGrab; i++)
    {
        // Retrieve the image
        error = fc2RetrieveBuffer(context, &rawImage);
        if (error != FC2_ERROR_OK)
        {
			printf("Error in retrieveBuffer: %s\n", fc2ErrorToDescription(error));
            return -1;
        }

		printf("Grabbed image %d\n", i);
    }

    (void)fc2DeregisterAllEvents(context);

    error = fc2DestroyImage(&rawImage);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2DestroyImage: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    fc2Error error;
    fc2Context context;
    fc2PGRGuid guid;
    unsigned int numCameras = 0;
    const int k_numImages = 100;

    PrintBuildInfo();

    error = fc2CreateContext(&context);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2CreateContext: %s\n", fc2ErrorToDescription(error));
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    error = fc2GetNumOfCameras(context, &numCameras);
    if (error != FC2_ERROR_OK)
    {
        fc2DestroyContext(context);

		printf("Error in fc2GetNumOfCameras: %s\n", fc2ErrorToDescription(error));
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    if (numCameras == 0)
    {
        fc2DestroyContext(context);

        // No cameras detected
        printf("No cameras detected.\n");
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    // Get the 0th camera
    error = fc2GetCameraFromIndex(context, 0, &guid);
    if (error != FC2_ERROR_OK)
    {
        fc2DestroyContext(context);

		printf("Error in fc2GetCameraFromIndex: %s\n", fc2ErrorToDescription(error));
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    error = fc2Connect(context, &guid);
    if (error != FC2_ERROR_OK)
    {
        fc2DestroyContext(context);

		printf("Error in fc2Connect: %s\n", fc2ErrorToDescription(error));
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    PrintCameraInfo(context);

    SetTimeStamping(context, TRUE);

    error = fc2StartCapture(context);
    if (error != FC2_ERROR_OK)
    {
        fc2DestroyContext(context);

		printf("Error in fc2StartCapture: %s\n", fc2ErrorToDescription(error));
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    if (GrabImages(context, k_numImages) != 0)
    {
        fc2DestroyContext(context);

        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    error = fc2StopCapture(context);
    if (error != FC2_ERROR_OK)
    {
        fc2DestroyContext(context);

		printf("Error in fc2StopCapture: %s\n", fc2ErrorToDescription(error));
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    error = fc2DestroyContext(context);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2DestroyContext: %s\n", fc2ErrorToDescription(error));
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    printf("Press Enter to exit...\n");
    getchar();

    return 0;
}