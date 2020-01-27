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
// $Id: GigEGrabEx.cpp 349447 2017-12-22 00:24:14Z vsiu $
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
    ostringstream macAddress;
    macAddress << hex << setw(2) << setfill('0')
               << (unsigned int)pCamInfo->macAddress.octets[0] << ":" << hex
               << setw(2) << setfill('0')
               << (unsigned int)pCamInfo->macAddress.octets[1] << ":" << hex
               << setw(2) << setfill('0')
               << (unsigned int)pCamInfo->macAddress.octets[2] << ":" << hex
               << setw(2) << setfill('0')
               << (unsigned int)pCamInfo->macAddress.octets[3] << ":" << hex
               << setw(2) << setfill('0')
               << (unsigned int)pCamInfo->macAddress.octets[4] << ":" << hex
               << setw(2) << setfill('0')
               << (unsigned int)pCamInfo->macAddress.octets[5];

    ostringstream ipAddress;
    ipAddress << (unsigned int)pCamInfo->ipAddress.octets[0] << "."
              << (unsigned int)pCamInfo->ipAddress.octets[1] << "."
              << (unsigned int)pCamInfo->ipAddress.octets[2] << "."
              << (unsigned int)pCamInfo->ipAddress.octets[3];

    ostringstream subnetMask;
    subnetMask << (unsigned int)pCamInfo->subnetMask.octets[0] << "."
               << (unsigned int)pCamInfo->subnetMask.octets[1] << "."
               << (unsigned int)pCamInfo->subnetMask.octets[2] << "."
               << (unsigned int)pCamInfo->subnetMask.octets[3];

    ostringstream defaultGateway;
    defaultGateway << (unsigned int)pCamInfo->defaultGateway.octets[0] << "."
                   << (unsigned int)pCamInfo->defaultGateway.octets[1] << "."
                   << (unsigned int)pCamInfo->defaultGateway.octets[2] << "."
                   << (unsigned int)pCamInfo->defaultGateway.octets[3];

    cout << endl;
    cout << "*** CAMERA INFORMATION ***" << endl;
    cout << "Serial number - " << pCamInfo->serialNumber << endl;
    cout << "Camera model - " << pCamInfo->modelName << endl;
    cout << "Camera vendor - " << pCamInfo->vendorName << endl;
    cout << "Sensor - " << pCamInfo->sensorInfo << endl;
    cout << "Resolution - " << pCamInfo->sensorResolution << endl;
    cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
    cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl;
    cout << "GigE version - " << pCamInfo->gigEMajorVersion << "."
         << pCamInfo->gigEMinorVersion << endl;
    cout << "User defined name - " << pCamInfo->userDefinedName << endl;
    cout << "XML URL 1 - " << pCamInfo->xmlURL1 << endl;
    cout << "XML URL 2 - " << pCamInfo->xmlURL2 << endl;
    cout << "MAC address - " << macAddress.str() << endl;
    cout << "IP address - " << ipAddress.str() << endl;
    cout << "Subnet mask - " << subnetMask.str() << endl;
    cout << "Default gateway - " << defaultGateway.str() << endl << endl;
}

void PrintStreamChannelInfo(GigEStreamChannel *pStreamChannel)
{
    // char ipAddress[32];
    ostringstream ipAddress;
    ipAddress << (unsigned int)pStreamChannel->destinationIpAddress.octets[0]
              << "."
              << (unsigned int)pStreamChannel->destinationIpAddress.octets[1]
              << "."
              << (unsigned int)pStreamChannel->destinationIpAddress.octets[2]
              << "."
              << (unsigned int)pStreamChannel->destinationIpAddress.octets[3];

    cout << "Network interface - " << pStreamChannel->networkInterfaceIndex
         << endl;
    cout << "Host Port - " << pStreamChannel->hostPort << endl;
    cout << "Do not fragment bit - "
         << (pStreamChannel->doNotFragment ? "Enabled" : "Disabled") << endl;
    cout << "Packet size - " << pStreamChannel->packetSize << endl;
    cout << "Inter packet delay - " << pStreamChannel->interPacketDelay << endl;
    cout << "Destination IP address - " << ipAddress.str() << endl;
    cout << "Source port (on camera) - " << pStreamChannel->sourcePort << endl
         << endl;
}

void PrintError(Error error) { error.PrintErrorTrace(); }

int DisableHeartbeat(GigECamera& cam)
{
    const unsigned int k_GVCPCapabilityAddr = 0x0934;
    const unsigned int k_GVCPConfigAddr = 0x0954;
    unsigned int regVal;

    // Determine if heartbeat can be disabled by reading the GVCP Capability register
    Error error = cam.ReadGVCPRegister(k_GVCPCapabilityAddr, &regVal);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    const unsigned BitMask = 0x20000000;
    const bool CanDisableHeartbeat = ((regVal & BitMask) == BitMask);

    if (CanDisableHeartbeat)
    {
        error = cam.ReadGVCPRegister(k_GVCPConfigAddr, &regVal);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        // Disable heartbeat by setting GVCP Configuration register's bit 31 to 1
        regVal |= 0x00000001; 

        error = cam.WriteGVCPRegister(k_GVCPConfigAddr, regVal);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        cout << endl;
        cout << "NOTE: GigE camera's heartbeat is disabled in Debug Mode" << endl;
        cout << "      Please power cycle the camera to re-enable the heartbeat." << endl;
    }

    return 0;
}

int RunSingleCamera(PGRGuid guid)
{
    const int k_numImages = 10;

    Error error;    

    cout << "Connecting to camera..." << endl;

    // Connect to a camera
	GigECamera cam;
    error = cam.Connect(&guid);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

#ifdef _DEBUG
    // For convenience, heartbeat is disabled to prevent heartbeat timeout in debugging
    if (DisableHeartbeat(cam) != 0)
    {
        cout << "Error in disabling heartbeat for GigE camera." << endl;
        return -1;
    }  
#endif

    // Get the camera information
    CameraInfo camInfo;
    error = cam.GetCameraInfo(&camInfo);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    PrintCameraInfo(&camInfo);

    unsigned int numStreamChannels = 0;
    error = cam.GetNumStreamChannels(&numStreamChannels);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    for (unsigned int i = 0; i < numStreamChannels; i++)
    {
        GigEStreamChannel streamChannel;
        error = cam.GetGigEStreamChannelInfo(i, &streamChannel);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        streamChannel.destinationIpAddress.octets[0] = 224;
        streamChannel.destinationIpAddress.octets[1] = 0;
        streamChannel.destinationIpAddress.octets[2] = 0;
        streamChannel.destinationIpAddress.octets[3] = 1;

        error = cam.SetGigEStreamChannelInfo(i, &streamChannel);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        cout << "Printing stream channel information for channel " << i << endl;
        PrintStreamChannelInfo(&streamChannel);
    }

    cout << "Querying GigE image setting information..." << endl;

    GigEImageSettingsInfo imageSettingsInfo;
    error = cam.GetGigEImageSettingsInfo(&imageSettingsInfo);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    GigEImageSettings imageSettings;
    imageSettings.offsetX = 0;
    imageSettings.offsetY = 0;
    imageSettings.height = imageSettingsInfo.maxHeight;
    imageSettings.width = imageSettingsInfo.maxWidth;
    imageSettings.pixelFormat = PIXEL_FORMAT_MONO8;

    cout << "Setting GigE image settings..." << endl;

    error = cam.SetGigEImageSettings(&imageSettings);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    cout << "Starting image capture..." << endl;

    // Start capturing images
    error = cam.StartCapture();
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    Image rawImage;
    Image convertedImage;
    for (int imageCnt = 0; imageCnt < k_numImages; imageCnt++)
    {
        // Retrieve an image
        error = cam.RetrieveBuffer(&rawImage);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            continue;
        }

        cout << "Grabbed image " << imageCnt << endl;

        // Convert the raw image
        error = rawImage.Convert(PIXEL_FORMAT_RGBU, &convertedImage);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }
    }

    cout << "Stopping capture" << endl;

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

    return 0;
}

int main(int /*argc*/, char ** /*argv*/)
{
    PrintBuildInfo();

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

    // Check to make sure GigE cameras are connected/discovered
    CameraInfo camInfo[10];
    unsigned int numCamInfo = 10;
    error = BusManager::DiscoverGigECameras(camInfo, &numCamInfo);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    cout << "Number of GigE cameras discovered: " << numCamInfo << endl;

    for (unsigned int i = 0; i < numCamInfo; i++)
    {
        PrintCameraInfo(&camInfo[i]);
    }

    if (numCamInfo == 0)
    {
        cout << "No suitable GigE cameras found. Press Enter to exit..."
             << endl;
        cin.ignore();
        return 0;
    }

    // Iterate through all enumerated devices but only run example on GigE
    // cameras
    unsigned int numCameras;
    error = busMgr.GetNumOfCameras(&numCameras);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    cout << "Number of cameras enumerated: " << numCameras << endl;

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

        if (interfaceType == INTERFACE_GIGE)
        {
            RunSingleCamera(guid);
        }
    }

    cout << "Press Enter to exit..." << endl;
    cin.ignore();

    return 0;
}
