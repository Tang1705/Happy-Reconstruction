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
// $Id: MultiSyncEx_C.c 347612 2017-12-01 20:44:28Z wgallego $
//=============================================================================

#if defined(_WIN32) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif

#include "C/FlyCapture2_C.h"
#include "C/MultiSyncLibrary_C.h"
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

char *SyncStatusToString(syncMessage message)
{
    switch (message)
    {
    case SYNC_MESSAGE_OK:
        return "Started";
    case SYNC_MESSAGE_STARTED:
        return "Object created";
    case SYNC_MESSAGE_STOPPED:
        return "Stopped";
    case SYNC_MESSAGE_SYNCING:
        return "Establishing sync";
    case SYNC_MESSAGE_NOMASTER:
        return "No master device found";
    case SYNC_MESSAGE_THREAD_ERROR:
        return "Error managing sync thread";
    case SYNC_MESSAGE_DEVICE_ERROR:
        return "There was an error with a device";
    case SYNC_MESSAGE_NOT_ENOUGH_DEVICES:
        return "Not enough buses found to sync";
    case SYNC_MESSAGE_BUS_RESET:
        return "Bus reset. Restablishing sync";
    case SYNC_MESSAGE_NOT_INITIALIZED:
        return "Sync object not initialized";
    default:
        return "Unknown error";
    }
}

int StartSyncCaptureAndGrab(fc2Context *cameraContext, unsigned int numCameras)
{
    const int k_numImages = 50;
    fc2Error error;
    fc2Image rawImage;
    fc2PGRGuid guid;
    unsigned int i, j;
    fc2TimeStamp ts;

    // Connect to all detected cameras and attempt to set them to
    // a common video mode and frame rate
    for (i = 0; i < numCameras; i++)
    {
        error = fc2CreateContext(&cameraContext[i]);
        if (error != FC2_ERROR_OK)
        {
			printf("Error in fc2CreateContext: %s\n", fc2ErrorToDescription(error));
            return -1;
        }

        error = fc2GetCameraFromIndex(cameraContext[i], i, &guid);
        if (error != FC2_ERROR_OK)
        {
            printf("Error in fc2GetCameraFromIndex: %s\n", fc2ErrorToDescription(error));
            return -1;
        }

        // Connect to a camera
        error = fc2Connect(cameraContext[i], &guid);
        if (error != FC2_ERROR_OK)
        {
            printf("Error in fc2Connect: %s\n", fc2ErrorToDescription(error));
            return -1;
        }

        // Get the camera information
        PrintCameraInfo(cameraContext[i]);

        // Set all cameras to a specific mode and frame rate so they
        // can be synchronized.  This function is only used for firewire and usb2 cameras
        error = fc2SetVideoModeAndFrameRate(
            cameraContext[i], FC2_VIDEOMODE_640x480Y8, FC2_FRAMERATE_30);
        if (error != FC2_ERROR_OK)
        {
            printf("Error setting video mode and frame rate: %s\n", fc2ErrorToDescription(error));
            printf("This example requires cameras to be able to set to 640x480 "
                   "Y8 at 30fps.\n");
            printf("If your camera does not support this mode, please edit the "
                   "source code and recompile the application.\n");
            return -1;
        }
    }

    printf("Starting sync capture...\n");
    //sync firewire cameras
    error = fc2StartSyncCapture(numCameras, cameraContext);
    if (error != FC2_ERROR_OK)
    {
        printf("Error calling fc2StartSyncCapture() : %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    error = fc2CreateImage(&rawImage);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2CreateImage: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    for (j = 0; j < k_numImages; j++)
    {
        // Display the timestamps for all cameras to show that the image
        // capture is synchronized for each image
        for (i = 0; i < numCameras; i++)
        {
            // Retrieve the image
            error = fc2RetrieveBuffer(cameraContext[i], &rawImage);
            if (error != FC2_ERROR_OK)
            {
                printf("Error in retrieveBuffer: %s\n", fc2ErrorToDescription(error));
                return -1;
            }

            // Get and print out the time stamp
            ts = fc2GetImageTimeStamp(&rawImage);
            printf("Camera %d - Frame %d - Timestamp [%u %u]\n",
                   i,
                   j,
                   ts.cycleSeconds,
                   ts.cycleCount);
        }
    }

    error = fc2DestroyImage(&rawImage);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2DestroyImage: %s\n", fc2ErrorToDescription(error));
    }

    // Cleanup
    for (i = 0; i < numCameras; i++)
    {
        if (cameraContext[i] != NULL)
        {
            error = fc2StopCapture(cameraContext[i]);
            if (error != FC2_ERROR_OK)
            {
                printf("Error in fc2StopCapture: %s\n", fc2ErrorToDescription(error));
            }

            error = fc2Disconnect(cameraContext[i]);
            if (error != FC2_ERROR_OK)
            {
                printf("Error in fc2Disconnect: %s\n", fc2ErrorToDescription(error));
            }

            error = fc2DestroyContext(cameraContext[i]);
            if (error != FC2_ERROR_OK)
            {
                printf("Error in fc2DestroyContext: %s\n", fc2ErrorToDescription(error));
            }
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    fc2Error error;
    fc2Context context;
    fc2PGRGuid guid;
    fc2Context cameraContext[10];

    unsigned int numCameras = 0;
    unsigned int numChecks = 0;
    unsigned int i;

    syncMessage message;
    syncError syncError;
    syncContext syncContext;

    int grabStatus;

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

    printf("Number of cameras detected: %d\n", numCameras);

    // Check to make sure enough cameras are connected
    if (numCameras < 2)
    {
        fc2DestroyContext(context);

        printf("Insufficient number of cameras...\n");
        printf("Please connect at least two 1394 cameras for example to run.\n");
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    // Check to make sure only 1394 cameras are connected
    for (i = 0; i < numCameras; i++)
    {
        fc2InterfaceType interfaceType;

        error = fc2GetCameraFromIndex(context, i, &guid);
        if (error != FC2_ERROR_OK)
        {
            fc2DestroyContext(context);

            printf("Error in fc2GetCameraFromIndex: %s\n",
                   fc2ErrorToDescription(error));
            printf("Press Enter to exit...\n");
            getchar();
            return -1;
        }

        error = fc2GetInterfaceTypeFromGuid(context, &guid, &interfaceType);
        if (error != FC2_ERROR_OK)
        {
            fc2DestroyContext(context);

            printf("Error in fc2GetInterfaceTypFromGuid: %s\n",
                   fc2ErrorToDescription(error));
            printf("Press Enter to exit...\n");
            getchar();
            return -1;
        }

        if (interfaceType != FC2_INTERFACE_IEEE1394)
        {
            fc2DestroyContext(context);

            printf("Please make sure ONLY 1394 cameras are connected for "
                   "example to run.\n");
            printf("Press Enter to exit...\n");
            getchar();
            return -1;
        }
    }

    printf("Creating SyncManager Object...\n");
    syncError = syncCreateContext(&syncContext);
    if (syncError != SYNC_ERROR_OK)
    {
        fc2DestroyContext(context);

        printf("Error in syncCreateContext: %d\n", syncError);
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    printf("Starting Sync Process...\n");
    syncError = syncStart(syncContext);
    if (syncError != SYNC_ERROR_OK)
    {
        fc2DestroyContext(syncContext);
        fc2DestroyContext(context);

        printf("Error in sync start call: %d\n", syncError);
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    do
    {
// Short delay before checking sync status
#if defined(_WIN32) || defined(_WIN64)
        Sleep(1000);
#else
        usleep(1000 * 1000);
#endif

        message = syncGetStatus(syncContext);
        printf("Current sync status : %s\n", SyncStatusToString(message));
    } while (message != SYNC_MESSAGE_OK && ++numChecks < 10);

    if (message != SYNC_MESSAGE_OK)
    {
        fc2DestroyContext(syncContext);
        fc2DestroyContext(context);

        printf("Sync status check failed.\n");
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    printf("\nTiming bus is %sconnected.\n",
           syncIsTimingBusConnected(syncContext) ? "" : "not ");
    printf("Time since started in seconds: %3.3fs.\n",
           syncGetTimeSinceSynced(syncContext));

    // Start sync capture and grab images
    grabStatus = StartSyncCaptureAndGrab(cameraContext, numCameras);
    if (grabStatus != 0)
    {
        // Cleanup if start sync capture fails intermittently
        for (i = 0; i < numCameras; i++)
        {
            if (cameraContext[i] != NULL)
            {
                error = fc2StopCapture(cameraContext[i]);
                if (error != FC2_ERROR_OK)
                {
                    printf("Error in fc2StopCapture: %s\n", fc2ErrorToDescription(error));
                }

                error = fc2DestroyContext(cameraContext[i]);
                if (error != FC2_ERROR_OK)
                {
                    printf("Error in fc2DestroyContext: %s\n", fc2ErrorToDescription(error));
                }
            }
        }

        fc2DestroyContext(syncContext);
        fc2DestroyContext(context);

        printf("Error in sync start call: %d\n", syncError);
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    printf("\nTime since started in seconds: %3.3fs.\n",
           syncGetTimeSinceSynced(syncContext));

    printf("Stopping...\n");
    syncError = syncStop(syncContext);
    if (syncError != SYNC_ERROR_OK)
    {
        fc2DestroyContext(syncContext);
        fc2DestroyContext(context);

        printf("Error in sync start call: %d\n", syncError);
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    printf("Destroying sync context...\n");
    syncError = syncDestroyContext(syncContext);
    if (syncError != SYNC_ERROR_OK)
    {
        fc2DestroyContext(context);

        printf("Error destroyContext call: %d\n", syncError);
        printf("Press Enter to exit...\n");
        getchar();
        return -1;
    }

    printf("Destroying context...\n");
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