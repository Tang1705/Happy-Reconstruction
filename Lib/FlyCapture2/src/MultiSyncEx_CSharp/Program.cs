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
// $Id: Program.cs 347612 2017-12-01 20:44:28Z wgallego $
//=============================================================================

using System;
using System.Text;
using System.Threading;

using MultiSyncLibraryManaged;
using FlyCapture2Managed;

namespace MultiSyncEx_CSharp
{
    class Program
    {
        static void PrintBuildInfo()
        {
            FC2Version version = ManagedUtilities.libraryVersion;

            StringBuilder newStr = new StringBuilder();
            newStr.AppendFormat(
                "FlyCapture2 library version: {0}.{1}.{2}.{3}\n",
                version.major, version.minor, version.type, version.build);

            Console.WriteLine(newStr);
        }

        static void PrintCameraInfo(CameraInfo camInfo)
        {
            StringBuilder newStr = new StringBuilder();
            newStr.Append("\n*** CAMERA INFORMATION ***\n");
            newStr.AppendFormat("Serial number - {0}\n", camInfo.serialNumber);
            newStr.AppendFormat("Camera model - {0}\n", camInfo.modelName);
            newStr.AppendFormat("Camera vendor - {0}\n", camInfo.vendorName);
            newStr.AppendFormat("Sensor - {0}\n", camInfo.sensorInfo);
            newStr.AppendFormat("Resolution - {0}\n", camInfo.sensorResolution);

            Console.WriteLine(newStr);
        }

        static String SyncStatusToString(PGRSyncMessage message)
        {
            switch (message)
            {
                case PGRSyncMessage.PGRSyncMessage_OK:
                    return "Started";
                case PGRSyncMessage.PGRSyncMessage_STARTED:
                    return "Object created";
                case PGRSyncMessage.PGRSyncMessage_STOPPED:
                    return "Stopped";
                case PGRSyncMessage.PGRSyncMessage_SYNCING:
                    return "Establishing sync";
                case PGRSyncMessage.PGRSyncMessage_NOMASTER:
                    return "No master device found";
                case PGRSyncMessage.PGRSyncMessage_THREAD_ERROR:
                    return "Error managing sync thread";
                case PGRSyncMessage.PGRSyncMessage_DEVICE_ERROR:
                    return "There was an error with a device";
                case PGRSyncMessage.PGRSyncMessage_NOT_ENOUGH_DEVICES:
                    return "Not enough buses found to sync";
                case PGRSyncMessage.PGRSyncMessage_BUS_RESET:
                    return "Bus reset. Restablishing sync";
                case PGRSyncMessage.PGRSyncMessage_NOT_INITIALIZED:
                    return "Sync object not initialized";
                default:
                    return "Unknown error";
            }
        }

        static int StartSyncCaptureAndGrab(ref ManagedCamera[] cameras, uint numCameras)
        {
            const int NumImages = 50;
            ManagedBusManager busMgr = new ManagedBusManager();

            // Connect to all detected cameras and attempt to set them to
            // a common video mode and frame rate
            for (uint i = 0; i < numCameras; i++)
            {
                cameras[i] = new ManagedCamera();

                ManagedPGRGuid guid = busMgr.GetCameraFromIndex(i);

                // Connect to a camera
                cameras[i].Connect(guid);

                // Get the camera information
                CameraInfo camInfo = cameras[i].GetCameraInfo();
                PrintCameraInfo(camInfo);

                // Set all cameras to a specific mode and frame rate so they
                // can be synchronized. This function is only used for firewire and usb2 cameras
                try
                {
                    cameras[i].SetVideoModeAndFrameRate(VideoMode.VideoMode640x480Y8, FrameRate.FrameRate15);
                }
                catch (System.Exception /*ex*/)
                {
                    Console.WriteLine("Error configuring cameras.");
                    Console.WriteLine("This example requires cameras to be able to set to 640x480 Y8 at 15fps.");
                    Console.WriteLine("If your camera does not support this mode, please edit the source code and recompile the application.");
                    return -1;
                }
            }

            // Put StartSyncCapture in a try-catch block in case
            // cameras failed to synchronize
            try
            {
                Console.WriteLine("Starting sync capture...");
                //sync firewire cameras
                ManagedCamera.StartSyncCapture(numCameras, cameras);
            }
            catch (System.Exception /*ex*/)
            {
                Console.WriteLine("Error starting cameras.");
                Console.WriteLine("This example requires cameras to be able to set to 640x480 Y8 at 15fps.");
                Console.WriteLine("If your camera does not support this mode, please edit the source code and recompile the application.");
                return -1;
            }

            ManagedImage tempImage = new ManagedImage();

            // Retrieve images from attached cameras
            for (int imageCnt = 0; imageCnt < NumImages; imageCnt++)
            {
                for (int camCount = 0; camCount < numCameras; camCount++)
                {
                    try
                    {
                        // Retrieve an image
                        cameras[camCount].RetrieveBuffer(tempImage);
                    }
                    catch (FC2Exception ex)
                    {
                        Console.WriteLine("Error retrieving buffer : {0}", ex.Message);
                        continue;                
                    }

                    // Display the timestamps for all cameras to show that the
                    // captured image is synchronized for each camera
                    TimeStamp timeStamp = tempImage.timeStamp;
                    Console.Out.WriteLine("Camera {0} - Frame {1} - TimeStamp {2} {3}", camCount, imageCnt, timeStamp.cycleSeconds, timeStamp.cycleCount);
                }
            }

            for (uint i = 0; i < numCameras; i++)
            {
                // Stop capturing images
                cameras[i].StopCapture();
                // Disconnect the camera
                cameras[i].Disconnect();
            }

            return 0;
        }

        static void Main(string[] args)
        {
            ManagedBusManager busMgr = new ManagedBusManager();
            uint numCameras = busMgr.GetNumOfCameras();

            Console.WriteLine("Number of cameras detected: {0}", numCameras);

            // Check to make sure enough cameras are connected
            if (numCameras < 2)
            {
                Console.WriteLine("Insufficient number of cameras...");
                Console.WriteLine("Please connect at least two 1394 cameras for example to run.");
                Console.WriteLine("Press Enter to exit...");
                Console.ReadLine();
                return;
            }

            // Check to make sure only 1394 cameras are connected
            for (uint i = 0; i < numCameras; i++)
            {
                ManagedPGRGuid guid = busMgr.GetCameraFromIndex(i);
                if (busMgr.GetInterfaceTypeFromGuid(guid) != InterfaceType.Ieee1394)
                {
                    Console.WriteLine("Please make sure ONLY 1394 cameras are connected for example to run.");
                    Console.WriteLine("Press Enter to exit...");
                    Console.ReadLine();
                    return;
                }
            }

            Console.Out.WriteLine("Creating ManagedSyncManager Object...");
            ManagedSyncManager syncManager = new ManagedSyncManager();

            Console.Out.WriteLine("Starting Sync process...");
            PGRSyncError syncError;
            syncError = syncManager.Start();
            if (syncError != PGRSyncError.PGRSyncError_OK)
            {
                Console.Out.WriteLine("Error in sync start call: {0}", syncError.ToString());
                Console.WriteLine("Press Enter to exit...");
                Console.ReadLine();
                return;
            }

            // Grab and check synchonization status
            uint numChecks = 0;
            PGRSyncMessage message;
            do
            {
                // Short delay before checking sync status
                Thread.Sleep(1000);

                message = syncManager.GetSyncStatus();
                Console.WriteLine("Current sync status : {0}", SyncStatusToString(message));
            }
            while (message != PGRSyncMessage.PGRSyncMessage_OK && ++numChecks < 10);

            Console.Out.WriteLine("\nTiming bus is {0}connected.", syncManager.IsTimingBusConnected() ? "" : "not ");
            Console.Out.WriteLine("Time since sync started in seconds: {0:F2}.", syncManager.GetTimeSinceSynced());

            // Start sync capture and grab images
            ManagedCamera[] cameras = new ManagedCamera[numCameras];
            int grabStatus = StartSyncCaptureAndGrab(ref cameras, numCameras);
            if (grabStatus != 0)
            {
                // Cleanup if start sync capture fails intermittently
                for (uint i = 0; i < numCameras; i++)
                {
                    if (cameras[i] != null)
                    {
                        cameras[i].StopCapture();
                        cameras[i].Disconnect();
                    }
                }

                Console.WriteLine("Press Enter to exit...");
                Console.ReadLine();
                return;
            }

            Console.Out.WriteLine("\nTime since sync started in seconds: {0:F2}.", syncManager.GetTimeSinceSynced());

            // Stop sync
            Console.WriteLine("Stopping Sync Process...");
            syncError = syncManager.Stop();
            if (syncError != PGRSyncError.PGRSyncError_OK)
            {
                Console.Out.WriteLine("Error in sync stop call: {0}", syncError.ToString());
                Console.WriteLine("Press Enter to exit...");
                Console.ReadLine();
                return;
            }

            Console.Out.WriteLine("Press any key to exit...");
            Console.ReadLine();
        }
    }
}
