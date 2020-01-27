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
// $Id: SaveImageToFlashEx.cpp 340335 2017-09-29 23:54:11Z rguo $
//=============================================================================

#include "stdafx.h"

#include "FlyCapture2.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include <string.h>

enum FlashMode
{
    CAPTURE,
    RETRIEVE
};

using namespace FlyCapture2;
using namespace std;

void PrintUsage()
{
    cout << endl;
    cout << "Usage:" << endl << endl;
    cout << "SaveImageToFlashEx [-c | -r]" << endl;
    cout << "\twhere" << endl << endl;
    cout << "\t-c  = Used to capture an image in on-camera FLASH" << endl;
    cout << "\t-r = Used to retrieve an image from FLASH and save it to disk."
         << endl
         << endl;
}

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
    cout << "Serial number -" << pCamInfo->serialNumber << endl;
    cout << "Camera model - " << pCamInfo->modelName << endl;
    cout << "Camera vendor - " << pCamInfo->vendorName << endl;
    cout << "Sensor - " << pCamInfo->sensorInfo << endl;
    cout << "Resolution - " << pCamInfo->sensorResolution << endl;
    cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
    cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl
         << endl;
}

void PrintError(Error error) { error.PrintErrorTrace(); }

bool IsDataFlashSupported(Camera *pCam)
{
    const unsigned int k_dataFlashReg = 0x1240;
    Error error;
    unsigned int regVal;
    error = pCam->ReadRegister(k_dataFlashReg, &regVal);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return false;
    }

    return (regVal & 0x80000000) == 0 ? false : true;
}

unsigned int GetDataFlashSize(Camera *pCam)
{
    const unsigned int k_dataFlashReg = 0x1240;
    Error error;
    unsigned int regVal;
    error = pCam->ReadRegister(k_dataFlashReg, &regVal);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return 0;
    }

    int exponent = 0;

    exponent = static_cast<int>((regVal & 0x00FFF000) >> 12);
    int pageSize = static_cast<int>(pow(2.0, exponent));

    exponent = static_cast<int>(regVal & 0x00000FFF);
    int numPages = static_cast<int>(pow(2.0, exponent));
    unsigned int availableFlashSize = pageSize * numPages;

    return availableFlashSize;
}

unsigned int GetDataFlashOffset(Camera *pCam)
{
    const unsigned int k_uiDataFlashOffset = 0x1244;
    Error error;
    unsigned int regVal;
    error = pCam->ReadRegister(k_uiDataFlashOffset, &regVal);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return 0;
    }

    return regVal;
}

int main(int argc, char **argv)
{
    PrintBuildInfo();

    // Make sure the number of arguments is correct
    if (argc != 2)
    {
        PrintUsage();
        return -1;
    }

    // Figure out what mode to be operating in
    FlashMode flashMode;
    if (strcmp(argv[1], "-r") == 0)
    {
        flashMode = RETRIEVE;
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        flashMode = CAPTURE;
    }
    else
    {
        PrintUsage();
        return -1;
    }

    Error error;

    if (flashMode == RETRIEVE)
    {
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
    }

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

    Camera cam;

    // Connect to a camera
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

    bool dataFlashSupported = IsDataFlashSupported(&cam);
    if (dataFlashSupported != true)
    {
        cout << "This camera does not support the data flash feature... press "
                "Enter to exit."
             << endl;
        cin.ignore();
        return -1;
    }

    error = cam.StartCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    Image image;
    error = cam.RetrieveBuffer(&image);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    error = cam.StopCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    const unsigned int dataFlashSize = GetDataFlashSize(&cam);

    // If the flash is not large enough to hold a full image,
    // determine the maximum image with a 4:3 aspect ratio which can fit in
    // the flash and use those dimensions. We will then start the camera
    // in Format7 using these settings. Otherwise, we will just save an
    // image with the current settings.
    if (image.GetDataSize() > dataFlashSize)
    {
        const unsigned int bytesPerPixel = image.GetBitsPerPixel() / 8;
        unsigned int imageWidth = image.GetCols();
        unsigned int imageHeight = image.GetRows();

        imageHeight = static_cast<unsigned int>(
            sqrt((dataFlashSize / bytesPerPixel) * 3.0 / 4.0));
        imageWidth = static_cast<unsigned int>(imageHeight * 4.0 / 3.0);

        // Query for available Format 7 modes
        Format7Info fmt7Info;
        bool supported;
        fmt7Info.mode = MODE_0;
        error = cam.GetFormat7Info(&fmt7Info, &supported);

        imageHeight -= imageHeight % fmt7Info.imageVStepSize;
        imageWidth -= imageWidth % fmt7Info.imageHStepSize;

        Format7ImageSettings fmt7ImageSettings;
        fmt7ImageSettings.mode = MODE_0;
        fmt7ImageSettings.offsetX = 0;
        fmt7ImageSettings.offsetY = 0;
        fmt7ImageSettings.width = imageWidth;
        fmt7ImageSettings.height = imageHeight;
        fmt7ImageSettings.pixelFormat = image.GetPixelFormat();

        // Set the settings to the camera
        error = cam.SetFormat7Configuration(&fmt7ImageSettings, 100.0f);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        cout << "Full size image does not fit in memory." << endl;
        cout << "Using Format7 image of size " << imageWidth << "x"
             << imageHeight << ", " << bytesPerPixel << " bytes per pixel."
             << endl;
    }

    // Start capture
    error = cam.StartCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Grab 10 images to stabilize the image, but only keep the last one
    for (int i = 0; i < 10; i++)
    {
        cam.RetrieveBuffer(&image);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }
    }

    // Stop capturing images
    error = cam.StopCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    if (flashMode == CAPTURE)
    {
        cout << "Starting writing of image to flash" << endl;

        const unsigned int dataFlashLocation = GetDataFlashOffset(&cam);

        error = cam.WriteRegisterBlock(0xFFFF,
                                       0xF0000000 + (dataFlashLocation * 4),
                                       (unsigned int *)image.GetData(),
                                       image.GetDataSize() / 4);
        if (error != PGRERROR_OK)
        {
            // If timeout error was encountered on GigE cameras, try increasing Register Read Timeout from 100 ms to 250 ms. 
            // Timeout value can be changed using RegistryControlUtility on Windows.

            PrintError(error);
            return -1;
        }

        cout << "Successfully wrote image to flash" << endl;
    }
    else if (flashMode == RETRIEVE)
    {
        cout << "Starting reading of image from flash" << endl;

        unsigned int dataFlashLocation = GetDataFlashOffset(&cam);
        unsigned int imageSize = image.GetDataSize();
        unsigned char *pData = new unsigned char[imageSize];

        error = cam.ReadRegisterBlock(0xFFFF,
                                      0xF0000000 + (dataFlashLocation * 4),
                                      (unsigned int *)pData,
                                      imageSize / 4);

        Image retrievedImage(image.GetRows(),
                             image.GetCols(),
                             image.GetStride(),
                             pData,
                             image.GetStride() * image.GetRows(),
                             image.GetPixelFormat(),
                             image.GetBayerTileFormat());

        ostringstream filename;
        filename << camInfo.serialNumber << "_from_flash.pgm";

        retrievedImage.Save(filename.str().c_str());

        delete[] pData;

        cout << "Successfully retrieved image from camera to " << filename.str()
             << endl;
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
