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
// $Id: CustomImageEx.cpp 316528 2017-02-22 00:03:53Z alin $
//=============================================================================

#include "stdafx.h"

#include "FlyCapture2.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace FlyCapture2;
using namespace std;
void PrintBuildInfo()
{
    FC2Version fc2Version;
    Utilities::GetLibraryVersion(&fc2Version);

    ostringstream version;
    version << "FlyCapture2 library version: " << fc2Version.major << "."
            << fc2Version.minor << "." << fc2Version.type << "."
            << fc2Version.build;
    cout << version.str() << endl;

    ostringstream timeStamp;
    timeStamp << "Application build date: " << __DATE__ << " " << __TIME__;
    cout << timeStamp.str() << endl << endl;
}

void PrintCameraInfo(CameraInfo *pCamInfo)
{
    cout << endl;
    cout << "*** CAMERA INFORMATION ***" << endl;
    cout << "Serial number - " << pCamInfo->serialNumber << endl;
    cout << "Camera model - " << pCamInfo->modelName << endl;
    cout << "Camera vendor - " << pCamInfo->vendorName << endl;
    cout << "Sensor - " << pCamInfo->sensorInfo << endl;
    cout << "Resolution - " << pCamInfo->sensorResolution << endl;
    cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
    cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl
         << endl;
}

void PrintFormat7Capabilities(Format7Info fmt7Info)
{
    cout << "Max image pixels: (" << fmt7Info.maxWidth << ", "
         << fmt7Info.maxHeight << ")" << endl;
    cout << "Image Unit size: (" << fmt7Info.imageHStepSize << ", "
         << fmt7Info.imageVStepSize << ")" << endl;
    cout << "Offset Unit size: (" << fmt7Info.offsetHStepSize << ", "
         << fmt7Info.offsetVStepSize << ")" << endl;
    cout << "Pixel format bitfield: 0x" << fmt7Info.pixelFormatBitField << endl;
}

void PrintError(Error error) { error.PrintErrorTrace(); }

int main(int /*argc*/, char ** /*argv*/)
{
    PrintBuildInfo();

    const Mode k_fmt7Mode = MODE_0;
    const PixelFormat k_fmt7PixFmt = PIXEL_FORMAT_MONO8;
    const int k_numImages = 10;

    Error error;

    // Since this application saves images in the current folder
    // we must ensure that we have permission to write to this folder.
    // If we do not have permission, fail right away.
    FILE *tempFile = fopen("test.txt", "w+");
    if (tempFile == NULL)
    {
        cout << "Failed to create file in current folder.  Please check "
                "permissions."
             << endl;
        return -1;
    }
    fclose(tempFile);
    remove("test.txt");

    BusManager busMgr;
    unsigned int numCameras;
    error = busMgr.GetNumOfCameras(&numCameras);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    cout << "Number of cameras detected: " << numCameras << endl;

    if (numCameras < 1)
    {
        cout << "Insufficient number of cameras... exiting" << endl;
        return -1;
    }

    PGRGuid guid;
    error = busMgr.GetCameraFromIndex(0, &guid);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }    

    // Connect to a camera
	Camera cam;
    error = cam.Connect(&guid);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Get the camera information
    CameraInfo camInfo;
    error = cam.GetCameraInfo(&camInfo);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    PrintCameraInfo(&camInfo);

    // Query for available Format 7 modes
    Format7Info fmt7Info;
    bool supported;
    fmt7Info.mode = k_fmt7Mode;
    error = cam.GetFormat7Info(&fmt7Info, &supported);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    PrintFormat7Capabilities(fmt7Info);

    if ((k_fmt7PixFmt & fmt7Info.pixelFormatBitField) == 0)
    {
        // Pixel format not supported!
        cout << "Pixel format is not supported" << endl;
        return -1;
    }

    Format7ImageSettings fmt7ImageSettings;
    fmt7ImageSettings.mode = k_fmt7Mode;
    fmt7ImageSettings.offsetX = 0;
    fmt7ImageSettings.offsetY = 0;
    fmt7ImageSettings.width = fmt7Info.maxWidth;
    fmt7ImageSettings.height = fmt7Info.maxHeight;
    fmt7ImageSettings.pixelFormat = k_fmt7PixFmt;

    bool valid;
    Format7PacketInfo fmt7PacketInfo;

    // Validate the settings to make sure that they are valid
    error = cam.ValidateFormat7Settings(
        &fmt7ImageSettings, &valid, &fmt7PacketInfo);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    if (!valid)
    {
        // Settings are not valid
        cout << "Format7 settings are not valid" << endl;
        return -1;
    }

    // Set the settings to the camera
    error = cam.SetFormat7Configuration(
        &fmt7ImageSettings, fmt7PacketInfo.recommendedBytesPerPacket);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Start capturing images
    error = cam.StartCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Retrieve frame rate property
    Property frmRate;
    frmRate.type = FRAME_RATE;
    error = cam.GetProperty(&frmRate);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    cout << "Frame rate is " << fixed << setprecision(2) << frmRate.absValue
         << " fps" << endl;

    cout << "Grabbing " << k_numImages << " images" << endl;

    Image rawImage;
    for (int imageCount = 0; imageCount < k_numImages; imageCount++)
    {
        // Retrieve an image
        error = cam.RetrieveBuffer(&rawImage);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            continue;
        }

        cout << ".";

        // Get the raw image dimensions
        PixelFormat pixFormat;
        unsigned int rows, cols, stride;
        rawImage.GetDimensions(&rows, &cols, &stride, &pixFormat);

        // Create a converted image
        Image convertedImage;

        // Convert the raw image
        error = rawImage.Convert(PIXEL_FORMAT_BGRU, &convertedImage);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        // Create a unique filename

        ostringstream filename;
        filename << camInfo.serialNumber << "-" << imageCount << ".bmp";

        // Save the image. If a file format is not passed in, then the file
        // extension is parsed to attempt to determine the file format.
        error = convertedImage.Save(filename.str().c_str());
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }
    }

    cout << endl;
    cout << "Finished grabbing images" << endl;

    // Stop capturing images
    error = cam.StopCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Disconnect the camera
    error = cam.Disconnect();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    cout << "Done! Press Enter to exit..." << endl;
    cin.ignore();

    return 0;
}
