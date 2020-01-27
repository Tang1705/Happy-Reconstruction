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
// $Id: FlyCapture2Test_C.c 317691 2017-03-02 18:42:42Z erich $
//=============================================================================

#if defined(_WIN32) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "C/FlyCapture2_C.h"
#include <stdio.h>

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
    fc2Image convertedImage;
    fc2TimeStamp prevTimestamp = {0};
    int i;

    error = fc2CreateImage(&rawImage);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2CreateImage: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    error = fc2CreateImage(&convertedImage);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2CreateImage: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    // If externally allocated memory is to be used for the converted image,
    // simply assigning the pData member of the fc2Image structure is
    // insufficient. fc2SetImageData() should be called in order to populate
    // the fc2Image structure correctly. This can be done at this point,
    // assuming that the memory has already been allocated.

    for (i = 0; i < numImagesToGrab; i++)
    {
        // Retrieve the image
        error = fc2RetrieveBuffer(context, &rawImage);
        if (error != FC2_ERROR_OK)
        {
			printf("Error in retrieveBuffer: %s\n", fc2ErrorToDescription(error));
            return -1;
        }
        else
        {
            // Get and print out the time stamp
            fc2TimeStamp ts = fc2GetImageTimeStamp(&rawImage);
            int diff = (ts.cycleSeconds - prevTimestamp.cycleSeconds) * 8000 +
                       (ts.cycleCount - prevTimestamp.cycleCount);
            prevTimestamp = ts;
            printf("timestamp [%d %d] - %d\n",
                   ts.cycleSeconds,
                   ts.cycleCount,
                   diff);
        }
    }

    if (error == FC2_ERROR_OK)
    {
        // Convert the final image to RGB
        error = fc2ConvertImageTo(FC2_PIXEL_FORMAT_BGR, &rawImage, &convertedImage);
        if (error != FC2_ERROR_OK)
        {
			printf("Error in fc2ConvertImageTo: %s\n", fc2ErrorToDescription(error));
            return -1;
        }

        // Save it to PNG
        printf("Saving the last image to fc2TestImage.png \n");
        error = fc2SaveImage(&convertedImage, "fc2TestImage.png", FC2_PNG);
        if (error != FC2_ERROR_OK)
        {
			printf("Error in fc2SaveImage: %s\n", fc2ErrorToDescription(error));
            printf("Please check write permissions.\n");
            return -1;
        }
    }

    error = fc2DestroyImage(&rawImage);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2DestroyImage: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    error = fc2DestroyImage(&convertedImage);
    if (error != FC2_ERROR_OK)
    {
		printf("Error in fc2DestroyImage: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    const unsigned int k_numImages = 10;

    fc2Error error;
    fc2Context context;
    fc2PGRGuid guid;
    unsigned int numCameras = 0;

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