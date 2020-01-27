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
// $Id: AsyncTriggerEx.cpp 316528 2017-02-22 00:03:53Z alin $
//=============================================================================

#include "stdafx.h"

#if defined(LINUX32) || defined(LINUX64)
#define LINUX
#endif

#ifdef LINUX
#include <time.h>
#include <unistd.h>
#endif

#include "FlyCapture2.h"
#include <iostream>
#include <sstream>

//
// Software trigger the camera instead of using an external hardware trigger
//
#define SOFTWARE_TRIGGER_CAMERA

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

void PrintError(Error error) { error.PrintErrorTrace(); }

bool CheckSoftwareTriggerPresence(Camera *pCam)
{
    const unsigned int k_triggerInq = 0x530;

    Error error;
    unsigned int regVal = 0;

    error = pCam->ReadRegister(k_triggerInq, &regVal);

    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return false;
    }

    if ((regVal & 0x10000) != 0x10000)
    {
        return false;
    }

    return true;
}

bool PollForTriggerReady(Camera *pCam)
{
    const unsigned int k_softwareTrigger = 0x62C;
    Error error;
    unsigned int regVal = 0;

    do
    {
        error = pCam->ReadRegister(k_softwareTrigger, &regVal);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return false;
        }

    } while ((regVal >> 31) != 0);

    return true;
}

bool FireSoftwareTrigger(Camera *pCam)
{
    const unsigned int k_softwareTrigger = 0x62C;
    const unsigned int k_fireVal = 0x80000000;
    Error error;

    error = pCam->WriteRegister(k_softwareTrigger, k_fireVal);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return false;
    }

    return true;
}

int main(int /*argc*/, char ** /*argv*/)
{
    PrintBuildInfo();

    const int k_numImages = 10;

    Error error;

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

    // Power on the camera
    const unsigned int k_cameraPower = 0x610;
    const unsigned int k_powerVal = 0x80000000;
    error = cam.WriteRegister(k_cameraPower, k_powerVal);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    const unsigned int millisecondsToSleep = 100;
    unsigned int regVal = 0;
    unsigned int retries = 10;

    // Wait for camera to complete power-up
    do
    {
#if defined(_WIN32) || defined(_WIN64)
        Sleep(millisecondsToSleep);
#elif defined(LINUX)
        struct timespec nsDelay;
        nsDelay.tv_sec = 0;
        nsDelay.tv_nsec = (long)millisecondsToSleep * 1000000L;
        nanosleep(&nsDelay, NULL);
#endif
        error = cam.ReadRegister(k_cameraPower, &regVal);
        if (error == PGRERROR_TIMEOUT)
        {
            // ignore timeout errors, camera may not be responding to
            // register reads during power-up
        }
        else if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        retries--;
    } while ((regVal & k_powerVal) == 0 && retries > 0);

    // Check for timeout errors after retrying
    if (error == PGRERROR_TIMEOUT)
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

#ifndef SOFTWARE_TRIGGER_CAMERA
    // Check for external trigger support
    TriggerModeInfo triggerModeInfo;
    error = cam.GetTriggerModeInfo(&triggerModeInfo);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    if (triggerModeInfo.present != true)
    {
        cout << "Camera does not support external trigger! Exiting..." << endl;
        return -1;
    }
#endif

    // Get current trigger settings
    TriggerMode triggerMode;
    error = cam.GetTriggerMode(&triggerMode);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Set camera to trigger mode 0
    triggerMode.onOff = true;
    triggerMode.mode = 0;
    triggerMode.parameter = 0;

#ifdef SOFTWARE_TRIGGER_CAMERA
    // A source of 7 means software trigger
    triggerMode.source = 7;
#else
    // Triggering the camera externally using source 0.
    triggerMode.source = 0;
#endif

    error = cam.SetTriggerMode(&triggerMode);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Poll to ensure camera is ready
    bool retVal = PollForTriggerReady(&cam);
    if (!retVal)
    {
        cout << endl;
        cout << "Error polling for trigger ready!" << endl;
        return -1;
    }

    // Get the camera configuration
    FC2Config config;
    error = cam.GetConfiguration(&config);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Set the grab timeout to 5 seconds
    config.grabTimeout = 5000;

    // Set the camera configuration
    error = cam.SetConfiguration(&config);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // Camera is ready, start capturing images
    error = cam.StartCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

#ifdef SOFTWARE_TRIGGER_CAMERA
    if (!CheckSoftwareTriggerPresence(&cam))
    {
        cout << "SOFT_ASYNC_TRIGGER not implemented on this camera! Stopping "
                "application"
             << endl;
        return -1;
    }
#else
    cout << "Trigger the camera by sending a trigger pulse to GPIO"
         << triggerMode.source << endl;

#endif

    Image image;
    for (int imageCount = 0; imageCount < k_numImages; imageCount++)
    {

#ifdef SOFTWARE_TRIGGER_CAMERA
        // Check that the trigger is ready
        PollForTriggerReady(&cam);

        cout << "Press the Enter key to initiate a software trigger" << endl;
        cin.ignore();

        // Fire software trigger
        bool retVal = FireSoftwareTrigger(&cam);
        if (!retVal)
        {
            cout << endl;
            cout << "Error firing software trigger" << endl;
            return -1;
        }
#endif

        // Grab image
        error = cam.RetrieveBuffer(&image);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            break;
        }
        cout << "." << endl;
    }

    // Turn trigger mode off.
    triggerMode.onOff = false;
    error = cam.SetTriggerMode(&triggerMode);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
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
