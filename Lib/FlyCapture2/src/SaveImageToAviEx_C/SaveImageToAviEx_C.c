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

#if defined(_WIN32) || defined(_WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "C/FlyCapture2_C.h"
#include <stdio.h>

typedef enum _AviType { UNCOMPRESSED, MJPG, H264 } AviType;

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

int SaveAVIHelper(fc2Context context, AviType aviType, float frameRate)
{
    fc2Error error;
    const int k_numImagesToGrab = 100;

    // Set maximum AVI file size to 2GB. A new AVI file is generated when 2GB
    // limit is reached. Setting maximum file size to 0 indicates no limit.
    const unsigned int k_aviFileSize = 2048;

    fc2Image rawImage;
    fc2AVIContext aviContext;
    fc2AVIOption aviOption;
    fc2H264Option h264Option;
    fc2MJPGOption mjpgOption;
    int i;

    error = fc2CreateAVI(&aviContext);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2CreateAVI: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    error = fc2AVISetMaximumSize(aviContext, k_aviFileSize);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2AVISetMaximumSize: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    error = fc2CreateImage(&rawImage);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2CreateImage: %s\n", fc2ErrorToDescription(error));
        fc2DestroyAVI(aviContext);
        return -1;
    }

    for (i = 0; i < k_numImagesToGrab; i++)
    {
        // Retrieve the image
        error = fc2RetrieveBuffer(context, &rawImage);
        if (error != FC2_ERROR_OK)
        {
            printf("Error in retrieveBuffer: %s\n", fc2ErrorToDescription(error));
            continue;
        }

        // Perform some initialization for the first time
        if (i == 0)
        {
            switch (aviType)
            {
            case UNCOMPRESSED:
                aviOption.frameRate = frameRate;

                // Uncompressed videos are always saved with avi containers with or without
                // extensions specified in the filepath
                error = fc2AVIOpen(
                    aviContext, "SaveImageToAviEx_C-Uncompressed", &aviOption);
                if (error != FC2_ERROR_OK)
                {
                    printf("Error opening AVI: %s\n", fc2ErrorToDescription(error));
                }
                break;

            case MJPG:
                mjpgOption.frameRate = frameRate;
                mjpgOption.quality = 75;

                // Motion JPEG videos are always saved with avi containers with or without
                // extensions specified in the filepath
                error = fc2MJPGOpen(
                    aviContext, "SaveImageToAviEx_C-MJPG", &mjpgOption);
                if (error != FC2_ERROR_OK)
                {
                    printf("Error opening AVI: %s\n", fc2ErrorToDescription(error));
                }
                break;

            case H264:
                h264Option.frameRate = frameRate;
                h264Option.bitrate = 1000000;
                h264Option.width = rawImage.cols;
                h264Option.height = rawImage.rows;

                // H.264 videos defaults to saving in mp4 containers if extensions are not
                // specified. Otherwise the extension specified by the user will be used.
                error = fc2H264Open(
                    aviContext, "SaveImageToAviEx_C-H264", &h264Option);
                if (error != FC2_ERROR_OK)
                {
                    printf("Error opening AVI: %s\n", fc2ErrorToDescription(error));
                }
                break;
            }
        }

        error = fc2AVIAppend(aviContext, &rawImage);
        if (error != FC2_ERROR_OK)
        {
            printf("Error appending to AVI: %s\n", fc2ErrorToDescription(error));
        }

        printf("Appended image %d\n", i);
    }

    error = fc2DestroyImage(&rawImage);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2CreateImaged: %s\n", fc2ErrorToDescription(error));
        fc2DestroyAVI(aviContext);
        return -1;
    }

    error = fc2DestroyAVI(aviContext);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2DestroyAVI: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    return 0;
}

float GetFrameRate(fc2Context context)
{
    fc2Error error;
    fc2PropertyInfo propInfo;
    fc2Property prop;

    // Check if the camera supports the FRAME_RATE property
    printf("Detecting frame rate from camera... \n");
    propInfo.type = FC2_FRAME_RATE;
    error = fc2GetPropertyInfo(context, &propInfo);
    if (error != FC2_ERROR_OK)
    {
        return 0.0f;
    }

    if (propInfo.present)
    {
        // Get the frame rate
        prop.type = FC2_FRAME_RATE;
        error = fc2GetProperty(context, &prop);
        if (error != FC2_ERROR_OK)
        {
            return 0.0f;
        }

        // Set the frame rate.
        // Note that the actual recording frame rate may be slower,
        // depending on the bus speed and disk writing speed.
        return prop.absValue;
    }

    return 0.0f;
}

int RunCamera(fc2Context context, fc2PGRGuid guid)
{
    fc2Error error;
    float frameRate = 0.0f;

    error = fc2Connect(context, &guid);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2Connect: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    PrintCameraInfo(context);

    error = fc2StartCapture(context);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2StartCapture: %s\n", fc2ErrorToDescription(error));
        return -1;
    }

    frameRate = GetFrameRate(context);
    if (frameRate == 0.0f)
    {
        printf("Invalid frame rate returned\n");
        return -1;
    }

    SaveAVIHelper(context, UNCOMPRESSED, frameRate);
    SaveAVIHelper(context, H264, frameRate);
    SaveAVIHelper(context, MJPG, frameRate);

    error = fc2StopCapture(context);
    if (error != FC2_ERROR_OK)
    {
        printf("Error in fc2StopCapture: %s\n", fc2ErrorToDescription(error));
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

    if (RunCamera(context, guid) != 0)
    {
        fc2DestroyContext(context);

        printf("Error running camera\n");
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
