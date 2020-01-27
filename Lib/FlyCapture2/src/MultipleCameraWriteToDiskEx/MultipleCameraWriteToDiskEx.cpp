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
// $Id: MultipleCameraWriteToDiskEx.cpp 347612 2017-12-01 20:44:28Z wgallego $
//=============================================================================

#include "stdafx.h"

#include "assert.h"
#include "FlyCapture2.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace FlyCapture2;
using namespace std;

// Maximum cameras on the bus. (Maximum devices allowed on a 1394 bus is 64).
const int ciMaxCameras = 64;

// Maximum size of expected (raw) image.
const int ciMaxImageSize = 2000 * 2000;

// Directory to save data to.
const string csDestinationDirectory = "";

// Number of grabbed images
const int numberOfImages = 20;

// Buffers used for color-processing (BGR pixel format)
unsigned char g_srcBuffer[ciMaxImageSize];

vector<string> filenames;

int createFiles(FILE **arhFile, unsigned int g_uiNumCameras)
{
    for (unsigned int uiCamera = 0; uiCamera < g_uiNumCameras; uiCamera++)
    {
        stringstream sstream;
        string tmpfilename;

        sstream << csDestinationDirectory << "camera" << uiCamera << ".tmp";
        sstream >> tmpfilename;
        filenames.push_back(tmpfilename);

        cout << "Creating " << tmpfilename << "..." << endl;

        // Create temporary files to do writing to
        arhFile[uiCamera] = fopen(tmpfilename.c_str(), "w+");
        if (arhFile[uiCamera] == NULL)
        {
            assert(false);
            return -1;
        }
    }
    return 0;
}

void PrintBuildInfo()
{
    FC2Version fc2Version;
    Utilities::GetLibraryVersion(&fc2Version);

    cout << "FlyCapture2 library version: " << fc2Version.major << "."
         << fc2Version.minor << "." << fc2Version.type << "."
         << fc2Version.build << endl
         << endl;

    cout << "Application build date: " << __DATE__ << ", " << __TIME__ << endl
         << endl;
}

void PrintCameraInfo(CameraInfo *pCamInfo)
{
    cout << "\n*** CAMERA INFORMATION ***\n"
         << "Serial number - " << pCamInfo->serialNumber << endl
         << "Camera model - " << pCamInfo->modelName << endl
         << "Camera vendor - " << pCamInfo->vendorName << endl
         << "Sensor - " << pCamInfo->sensorInfo << endl
         << "Resolution - " << pCamInfo->sensorResolution << endl
         << "Firmware version - " << pCamInfo->firmwareVersion << endl
         << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl
         << endl;
}

void PrintError(Error error) { error.PrintErrorTrace(); }

int main()
{
    PrintBuildInfo();

    FILE *arhFile[ciMaxCameras];
    size_t ardwBytesWritten[ciMaxCameras];
    const int k_numImages = numberOfImages;
    Error error;

    BusManager busMgr;
    Image image;
    FC2Config BufferFrame;
    EmbeddedImageInfo EmbeddedInfo;

    unsigned int numCameras;

    int iCountMissedIm = NULL;
    int iFrameNumberPrev[ciMaxCameras];
    int iFrameNumberDelta[ciMaxCameras];
    int iImageSize = NULL;

    ImageMetadata imFrameCount[ciMaxCameras];

    FILE *rawFile;

    error = busMgr.GetNumOfCameras(&numCameras);
    if (error != PGRERROR_OK)
    {
        PrintError(error);
        return -1;
    }

    cout << "Number of cameras detected: " << numCameras << endl << endl;

    if (numCameras < 1)
    {
        cout << "Insufficient number of cameras... press Enter to exit."
             << endl;
        cin.ignore();
        return -1;
    }

    // Create files to write to
    if (createFiles(arhFile, numCameras) != 0)
    {
        cout << "There was error creating the files... press Enter to exit.";
        cin.ignore();
        return -1;
    }

    Camera **ppCameras = new Camera *[numCameras];

    // Connect to all detected cameras and attempt to set them to
    // the same video mode and frame rate
    for (unsigned int uiCamera = 0; uiCamera < numCameras; uiCamera++)
    {
        ppCameras[uiCamera] = new Camera();

        PGRGuid guid;
        error = busMgr.GetCameraFromIndex(uiCamera, &guid);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        // Connect to a camera
        error = ppCameras[uiCamera]->Connect(&guid);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        // Get the camera information
        CameraInfo camInfo;
        error = ppCameras[uiCamera]->GetCameraInfo(&camInfo);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        PrintCameraInfo(&camInfo);

        // Set video mode and frame rate. This function is only
        // used for firewire and USB2 cameras.
        error = ppCameras[uiCamera]->SetVideoModeAndFrameRate(
            VIDEOMODE_640x480Y8, FRAMERATE_30);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            cout << "Error starting cameras." << endl
                 << "This example requires cameras to be able to set to the "
                    "same video mode and frame rate."
                 << endl
                 << "If your cameras do not support the requested mode, please "
                    "edit the source code and recompile the application."
                 << endl
                 << "Press Enter to exit." << endl;

            cin.ignore();
            return -1;
        }
    }

    for (unsigned int uiCamera = 0; uiCamera < numCameras; uiCamera++)
    {
        error = ppCameras[uiCamera]->GetConfiguration(&BufferFrame);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        BufferFrame.numBuffers = 200;

        BufferFrame.grabMode = BUFFER_FRAMES;

        error = ppCameras[uiCamera]->SetConfiguration(&BufferFrame);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        error = ppCameras[uiCamera]->GetEmbeddedImageInfo(&EmbeddedInfo);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        if (EmbeddedInfo.timestamp.available == true)
        {
            EmbeddedInfo.timestamp.onOff = true;
        }
        else
        {
            cout << "Timestamp is not available!" << endl;
        }

        if (EmbeddedInfo.frameCounter.available == true)
        {
            EmbeddedInfo.frameCounter.onOff = true;
        }
        else
        {
            cout << "Framecounter is not avalable!" << endl;
        }

        error = ppCameras[uiCamera]->SetEmbeddedImageInfo(&EmbeddedInfo);
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            return -1;
        }

        error = ppCameras[uiCamera]->StartCapture();
        if (error != PGRERROR_OK)
        {
            PrintError(error);
            cout << "Error starting to capture images." << endl
                 << "Press Enter to exit." << endl;
            cin.ignore();
            return -1;
        }
    }

    cout << "Grabbing ...";

    // grabbing all images
    for (int iImages = 0; iImages < k_numImages; iImages++)
    {
        // grabbing for all cameras
        for (unsigned int uiCamera = 0; uiCamera < numCameras; uiCamera++)
        {
            error = ppCameras[uiCamera]->RetrieveBuffer(&image);
            if (error != PGRERROR_OK)
            {
                PrintError(error);
                return -1;
            }

            // Get the size of the buffer associated with the image, in bytes.
            // Returns the size of the buffer in bytes.
            iImageSize = image.GetDataSize();

            // Write to the file
            ardwBytesWritten[uiCamera] =
                fwrite(image.GetData(),
                       1,
                       image.GetCols() * image.GetRows(),
                       arhFile[uiCamera]);

            // Ensure that the write was successful
            if (ardwBytesWritten[uiCamera] != (unsigned)iImageSize)
            {
                cout << "Error writing to file for camera " << uiCamera << " !"
                     << endl;
                return -1;
            }

            imFrameCount[uiCamera] = image.GetMetadata();

            // Keep track of the difference in image sequence numbers
            // (iFrameCount)
            // in order to determine if any images have been missed.  A
            // difference
            // greater than 1 indicates that an image has been missed.

            if (iImages == 0)
            {
                // This is the first image, set up the variables
                iFrameNumberPrev[uiCamera] =
                    imFrameCount[uiCamera].embeddedFrameCounter;

                iFrameNumberDelta[uiCamera] = 1;
            }
            else
            {
                // Get the difference in sequence numbers between the current
                // image and the last image we received
                iFrameNumberDelta[uiCamera] =
                    imFrameCount[uiCamera].embeddedFrameCounter -
                    iFrameNumberPrev[uiCamera];
            }

            if (iFrameNumberDelta[uiCamera] != 1)
            {
                iCountMissedIm += iFrameNumberDelta[uiCamera] - 1;
            }

            iFrameNumberPrev[uiCamera] =
                imFrameCount[uiCamera].embeddedFrameCounter;
        }
    }

    cout << endl;

    cout << "We missed " << iCountMissedIm << " images!" << endl << endl;

    // Open file
    for (unsigned int uiCamera = 0; uiCamera < numCameras; uiCamera++)
    {
        string tempFilename = filenames.at(uiCamera);

        fclose(arhFile[uiCamera]);

        cout << "Opening " << tempFilename.c_str() << "..." << endl;

        if ((rawFile = fopen(tempFilename.c_str(), "rb")) == NULL)
        {
            cout << "Error opening file: " << tempFilename.c_str() << endl
                 << "Press Enter to exit." << endl;
            ;
            cin.ignore();
            return -1;
        }

        cout << "Splitting images" << endl;

        // Read image into buffer
        for (int iImages = 0; iImages < k_numImages; iImages++)
        {
            string imageFilename;
            stringstream sstream;

            if (fread(g_srcBuffer, sizeof(char), iImageSize, rawFile) !=
                iImageSize)
            {
                cout << "Error reading image # " << iImages
                     << " from file: " << tempFilename.c_str() << endl
                     << "Press Enter to exit." << endl;
                ;
                cin.ignore();
                return -1;
            }

            // Import image into Image structure
            error = image.SetData(g_srcBuffer, iImageSize);
            if (error != PGRERROR_OK)
            {
                PrintError(error);
                return -1;
            }

            sstream << csDestinationDirectory << "camera" << uiCamera << "_"
                    << iImages << ".pgm";
            sstream >> imageFilename;

            //  Save image to disk
            error = image.Save(imageFilename.c_str());
            if (error != PGRERROR_OK)
            {
                PrintError(error);
                return -1;
            }
            cout << ".";
        }

        cout << endl << endl;

        // Close file
        fclose(rawFile);
    }

    for (unsigned int uiCamera = 0; uiCamera < numCameras; uiCamera++)
    {
        ppCameras[uiCamera]->StopCapture();
        ppCameras[uiCamera]->Disconnect();
        delete ppCameras[uiCamera];
    }

    delete[] ppCameras;

    cout << "Press Enter to exit..." << endl;
    cin.ignore();

    return 0;
}
