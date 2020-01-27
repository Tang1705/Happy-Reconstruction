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
// $Id: HighDynamicRangeEx.cpp 316528 2017-02-22 00:03:53Z alin $
//=============================================================================

#include "stdafx.h"

#include "FlyCapture2.h"
#include <iostream>
#include <sstream>

using namespace FlyCapture2;
using namespace std;

const unsigned int k_HDRCtrl = 0x1800;

const unsigned int k_HDRShutter1 = 0x1820;
const unsigned int k_HDRShutter2 = 0x1840;
const unsigned int k_HDRShutter3 = 0x1860;
const unsigned int k_HDRShutter4 = 0x1880;

const unsigned int k_HDRGain1 = 0x1824;
const unsigned int k_HDRGain2 = 0x1844;
const unsigned int k_HDRGain3 = 0x1864;
const unsigned int k_HDRGain4 = 0x1884;

const unsigned int k_HDROn = 0x82000000;
const unsigned int k_HDROff = 0x80000000;

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

void PrintError(Error error) { error.PrintErrorTrace(); }

bool IsHDRSupported(Camera *pCam)
{
    Error error;
    unsigned int RegVal;
    error = pCam->ReadRegister(k_HDRCtrl, &RegVal);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return false;
    }

    return (0x80000000 & RegVal) ? true : false;
}

bool ToggleHDRMode(Camera *pCam, bool hdrOn)
{
    Error error;
    error = pCam->WriteRegister(k_HDRCtrl, hdrOn ? k_HDROn : k_HDROff);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return false;
    }
    else
    {
        cout << "HDR mode turned to " << (hdrOn ? "on" : "off") << endl;
    }

    return true;
}

void InitializeHDRRegisters(Camera *pCam)
{
    Error error;
    error = pCam->WriteRegister(k_HDRShutter1, 0x000);
    error = pCam->WriteRegister(k_HDRShutter2, 0x120);
    error = pCam->WriteRegister(k_HDRShutter3, 0x240);
    error = pCam->WriteRegister(k_HDRShutter4, 0x360);

    error = pCam->WriteRegister(k_HDRGain1, 0x000);
    error = pCam->WriteRegister(k_HDRGain2, 0x0E3);
    error = pCam->WriteRegister(k_HDRGain3, 0x1C6);
    error = pCam->WriteRegister(k_HDRGain4, 0x2A9);

    cout << "Initialized HDR registers..." << endl;
}

int main(int /*argc*/, char ** /*argv*/)
{
    PrintBuildInfo();

    Error error;

    bool check;

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

    error = cam.StartCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    bool supported = IsHDRSupported(&cam);
    if (supported != true)
    {
        cout << "HDR is not supported! Exiting..." << endl;
        return -1;
    }

    InitializeHDRRegisters(&cam);

    check = ToggleHDRMode(&cam, true);
	if (check != true)
	{
		return -1;
	}

    // Grab 4 images
    Image rawImage[4];
    for (int imageCnt = 0; imageCnt < 4; imageCnt++)
    {
        error = cam.RetrieveBuffer(&rawImage[imageCnt]);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        cout << "Grabbed image " << imageCnt << endl;
    }

    // Process and save the 4 images
    for (int imageCnt = 0; imageCnt < 4; imageCnt++)
    {
        // Create a converted image
        Image convertedImage;

        // Convert the raw image
        error = rawImage[imageCnt].Convert(PIXEL_FORMAT_BGRU, &convertedImage);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        cout << "Converted image " << imageCnt << endl;

        // Create a unique filename
        ostringstream filename;
        filename << "HDR-" << camInfo.serialNumber << "-" << imageCnt << ".ppm";

        // Save the image. If a file format is not passed in, then the file
        // extension is parsed to attempt to determine the file format.
        error = convertedImage.Save(filename.str().c_str());
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        cout << "Saved image " << imageCnt << endl;
    }

    cout << "Finished grabbing images" << endl;

    // Stop capturing images
    error = cam.StopCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    check = ToggleHDRMode(&cam, false);
    if (check != true)
        return -1;

    // Disconnect the camera
    error = cam.Disconnect();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    cout << "Press Enter to exit..." << endl;
    cin.ignore();

    return 0;
}
