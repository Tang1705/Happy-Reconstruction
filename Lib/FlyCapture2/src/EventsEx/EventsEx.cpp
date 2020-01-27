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
// $Id: EventsEx.cpp 316528 2017-02-22 00:03:53Z alin $
//=============================================================================

#include "stdafx.h"

#include "FlyCapture2.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

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

//
// User-supplied data structure which is passed to the callback function (along
// with other parameters) when the event is triggered, which in turn issues the
// callback function.
//
struct CustomUserDataStruct
{
    int i;
    char c;
};

// User-supplied callback function to run when an event is triggered.
void SimpleCallback(void *cbData)
{
    if (cbData)
    {
        // Determine which type of event triggered this callback to be issued.
        EventCallbackData *pData = static_cast<EventCallbackData *>(cbData);
        if (pData->EventName)
        {
            cout << "Received callback for event:" << pData->EventName << " (0x"
                 << hex << pData->EventID << dec << ")." << endl;
        }
        else
        {
            cout << "Error: Event name/type invalid." << endl;
        }

        //
        // Print out the time at which this event was generated (from the
        // camera's perspective).
        // This helps to sequence image/event ordering.
        //
        cout << "Timestamp: " << pData->EventTimestamp << endl;

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
        CustomUserDataStruct *pUserData =
            static_cast<CustomUserDataStruct *>(pData->EventUserData);
        if (pUserData &&
            (pData->EventUserDataSize == sizeof(CustomUserDataStruct)))
        {
            cout << "User Data: i=" << pUserData->i << " c=" << pUserData->c
                 << endl;
        }
        else
        {
            cout << "Error parsing user data." << endl;
        }
    }
    else
    {
        cout << "No callback data provided." << endl;
    }

    return;
}

//
// Trigger a single camera to start streaming images, and generating End of
// Exposure (EoE) events with a user-supplied callback function to notify
// the user when the event has been triggered.
//
int RunSingleCamera(PGRGuid guid)
{
    // Context variable
    Camera cam;

    // Additional parameters
    const int k_numImages = 100;
    Error error;

    // Connect to a camera
    error = cam.Connect(&guid);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    //
    // Register for End of Exposure (EoE) event. We simply create an instance of
    // the EventOptions structure, populate it, and register it with the camera.
    //
    EventOptions optEOE;
    optEOE.EventName = "EventExposureEnd";
    optEOE.EventCallbackFcn = &SimpleCallback;
    CustomUserDataStruct UserDataEOE = {1, 'a'};
    optEOE.EventUserData = static_cast<void *>(&UserDataEOE);
    optEOE.EventUserDataSize = sizeof(CustomUserDataStruct);
    error = cam.RegisterEvent(&optEOE);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return (-1);
    }
    else
    {
        cout << "Successfully registered event:" << optEOE.EventName << endl;
    }

    //
    // Attempt to register all events. This will fail, since we only expect this
    // to be called if no events have yet been registered, but a fatal error
    // will not be generated. If the user wants to use this call, the user can
    // DeregisterAllEvents(), and then run RegisterAllEvents().
    //
    // If there are numerious different event types, and the user would like to
    // create a "default" callback and/or UserData struct, the user can run
    // RegisterAllEvents() with the default callback function, issue
    // DeregisterEvent() for the specific event that uses a custom callback, and
    // then issue RegisterEvent() with the specific callback function. This is
    // to ensure the user doesn't accidentally corrupt the callback function
    // list.
    //
    error = cam.RegisterAllEvents(&optEOE);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
    }
    else
    {
        cout << "Successfully registered all events. This should not succeed."
             << endl;
    }

	//
    // Now, let's attempt to de-register an event we know we haven't registered
    // yet. This will fail, but will not trigger a fatal error in this example.
    //
    EventOptions optError;
    optError.EventName = "EventError";
    optError.EventCallbackFcn = &SimpleCallback;
    CustomUserDataStruct UserDataError = {2, 'b'};
    optError.EventUserData = static_cast<void *>(&UserDataError);
    optError.EventUserDataSize = sizeof(CustomUserDataStruct);
    error = cam.DeregisterEvent(&optError);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
    }
    else
    {
        cout << "Successfully de-registered event:" << optError.EventName
             << ". This should not succeed." << endl;
    }

    // Get the camera information (serial number, capabilities, etc)
    CameraInfo camInfo;
    error = cam.GetCameraInfo(&camInfo);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    PrintCameraInfo(&camInfo);

	//
    // Start capturing images (ie: signal the camera to start streaming data and
    // storing it in pre-allocated output buffers.
    //
    error = cam.StartCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

	//
    // Create an intermediate image buffer to store the data we request from the
    // camera.
	//
    Image rawImage;
    for (int imageCnt = 0; imageCnt < k_numImages; imageCnt++)
    {
        // Retrieve an image from the camera
        error = cam.RetrieveBuffer(&rawImage);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            continue;
        }
        cout << "Grabbed image " << imageCnt << endl;
    }

    // Stop capturing images
    error = cam.StopCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    // De-register all events before disconnecting from camera
    cam.DeregisterAllEvents();

    // Disconnect the camera
    error = cam.Disconnect();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    return 0;
}

// Main entry point
int main(int /*argc*/, char ** /*argv*/)
{
    PrintBuildInfo();

    Error error;

	//
    // Since this application saves images in the current folder
    // we must ensure that we have permission to write to this folder.
    // If we do not have permission, fail right away.
	//
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

    // Create a Bus Manager instance so we can query all connected cameras.
    BusManager busMgr;
    unsigned int numCameras;
    error = busMgr.GetNumOfCameras(&numCameras);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }
    cout << "Number of cameras detected: " << numCameras << endl;
	
	//
    // Get a handle to an individual camera, and start to receive images and
    // event callbacks
	//
    for (unsigned int i = 0; i < numCameras; i++)
    {
        PGRGuid guid;
        error = busMgr.GetCameraFromIndex(i, &guid);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        RunSingleCamera(guid);
    }

    cout << "Done! Press Enter to exit..." << endl;
    cin.ignore();

    return 0;
}
