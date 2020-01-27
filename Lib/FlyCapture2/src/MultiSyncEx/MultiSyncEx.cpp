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
// $Id: MultiSyncEx.cpp 347612 2017-12-01 20:44:28Z wgallego $
//=============================================================================

#include "stdafx.h"

#include "FlyCapture2.h"
#include "MultiSyncLibrary.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace FlyCapture2;
using namespace MultiSyncLibrary;
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

std::string SyncStatusToString(PGRSyncMessage message)
{
    switch (message)
    {
    case PGRSyncMessage_OK:
        return "Started";
    case PGRSyncMessage_STARTED:
        return "Object created";
    case PGRSyncMessage_STOPPED:
        return "Stopped";
    case PGRSyncMessage_SYNCING:
        return "Establishing sync";
    case PGRSyncMessage_NOMASTER:
        return "No master device found";
    case PGRSyncMessage_THREAD_ERROR:
        return "Error managing sync thread";
    case PGRSyncMessage_DEVICE_ERROR:
        return "There was an error with a device";
    case PGRSyncMessage_NOT_ENOUGH_DEVICES:
        return "Not enough buses found to sync";
    case PGRSyncMessage_BUS_RESET:
        return "Bus reset. Restablishing sync";
    case PGRSyncMessage_NOT_INITIALIZED:
        return "Sync object not initialized";
    default:
        return "Unknown error";
    }
}

int StartSyncCaptureAndGrab(Camera **ppCameras, unsigned int numCameras)
{
    const int k_numImages = 50;
    Error error;
    BusManager busManager;

    // Connect to all detected cameras and attempt to set them to
    // a common video mode and frame rate
    for (unsigned int i = 0; i < numCameras; i++)
    {
        ppCameras[i] = new Camera();

        PGRGuid guid;
        error = busManager.GetCameraFromIndex(i, &guid);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        // Connect to a camera
        error = ppCameras[i]->Connect(&guid);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        // Get the camera information
        CameraInfo camInfo;
        error = ppCameras[i]->GetCameraInfo(&camInfo);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        PrintCameraInfo(&camInfo);

        // Set all cameras to a specific mode and frame rate so they
        // can be synchronized. This function is only used for firewire and usb2 cameras
        error = ppCameras[i]->SetVideoModeAndFrameRate(VIDEOMODE_640x480Y8,
                                                       FRAMERATE_30);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            cout << "Error setting video mode and frame rate." << endl;
            cout << "This example requires cameras to be able to set to "
                    "640x480 Y8 at 30fps."
                 << endl;
            cout << "If your camera does not support this mode, please edit "
                    "the source code and recompile the application."
                 << endl;
            return -1;
        }
    }

    cout << "Starting sync capture..." << endl;
    //sync firewire cameras
    error = Camera::StartSyncCapture(numCameras, (const Camera **)ppCameras);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        cout << "Error calling StartSyncCapture()" << endl;
        return -1;
    }

    for (int j = 0; j < k_numImages; j++)
    {
        // Display the timestamps for all cameras to show that the image
        // capture is synchronized for each image
        for (unsigned int i = 0; i < numCameras; i++)
        {
            Image image;
            error = ppCameras[i]->RetrieveBuffer(&image);
            if (error != PGRERROR_OK)
            {
                PrintError(error);
                return -1;
            }

            TimeStamp timestamp = image.GetTimeStamp();
            cout << "Camera " << i << " - Frame " << j << " - TimeStamp ["
                 << timestamp.cycleSeconds << " " << timestamp.cycleCount << "]"
                 << endl;
        }
    }

    // Cleanup
    for (unsigned int i = 0; i < numCameras; i++)
    {
        ppCameras[i]->StopCapture();
        ppCameras[i]->Disconnect();
        delete ppCameras[i];
    }

    return 0;
}

int main()
{
    PrintBuildInfo();

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

    // Check to make sure enough cameras are connected
    if (numCameras < 2)
    {
        cout << "Insufficient number of cameras..." << endl;
        cout << "Please connect at least two 1394 cameras for example to run."
             << endl;
        cout << "Press Enter to exit..." << endl;
        cin.ignore();
        return -1;
    }

    // Check to make sure only 1394 cameras are connected
    for (unsigned int i = 0; i < numCameras; i++)
    {
        PGRGuid guid;
        error = busMgr.GetCameraFromIndex(i, &guid);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        InterfaceType interfaceType;
        error = busMgr.GetInterfaceTypeFromGuid(&guid, &interfaceType);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        if (interfaceType != INTERFACE_IEEE1394)
        {
            cout << "Please make sure ONLY 1394 cameras are connected for "
                    "example to run."
                 << endl;
            cout << "Press Enter to exit..." << endl;
            cin.ignore();
            return -1;
        }
    }

    cout << "Creating SyncManager Object..." << endl;
    MultiSyncLibrary::SyncManager syncManager;

    cout << "Starting Sync Process..." << endl;
    PGRSyncError syncError;
    syncError = syncManager.Start();
    if (syncError != PGRSyncError_OK)
    {
        cout << "Error in sync start call: " << syncError << endl;
        cout << "Press Enter to exit..." << endl;
        cin.ignore();
        return -1;
    }

    // Grab and check synchonization status
    unsigned int numChecks = 0;
    PGRSyncMessage message;

    do
    {
// Short delay before checking sync status
#if defined(_WIN32) || defined(_WIN64)
        Sleep(1000);
#else
        usleep(1000 * 1000);
#endif

        message = syncManager.GetSyncStatus();
        cout << "Current sync status : " << SyncStatusToString(message) << endl;
    } while (message != PGRSyncMessage_OK && ++numChecks < 10);

    if (message != PGRSyncMessage_OK)
    {
        cout << "Sync status check failed. " << endl;
        cout << "Press Enter to exit..." << endl;
        cin.ignore();
        return -1;
    }

    cout << endl
         << "Timing bus is " << (syncManager.IsTimingBusConnected() ? "" : "not ")
         << "connected." << endl;
    cout << "Time since started in seconds: " << setprecision(1)
         << syncManager.GetTimeSinceSynced() << endl;

    // Start sync capture and grab images
    Camera **ppCameras = new Camera *[numCameras];
    int grabStatus = StartSyncCaptureAndGrab(ppCameras, numCameras);
    if (grabStatus != 0)
    {
        // Cleanup if start sync capture fails intermittently
        for (unsigned int i = 0; i < numCameras; i++)
        {
            if (ppCameras[i] != NULL)
            {
                ppCameras[i]->StopCapture();
                ppCameras[i]->Disconnect();
                delete ppCameras[i];
            }
        }

        cout << "Press Enter to exit..." << endl;
        cin.ignore();
        return -1;
    }

    // Cleanup
    delete[] ppCameras;

    cout << endl
         << "Time since started in seconds: " << setprecision(1)
         << syncManager.GetTimeSinceSynced() << endl;

    // Stop sync
    cout << "Stopping Sync Process..." << endl;
    syncError = syncManager.Stop();
    if (syncError != PGRSyncError_OK)
    {
        cout << "Error in sync stop call: " << syncError << endl;
        cout << "Press Enter to exit..." << endl;
        cin.ignore();
        return -1;
    }

    cout << "Press Enter to exit..." << endl;
    cin.ignore();

    return grabStatus;
}
