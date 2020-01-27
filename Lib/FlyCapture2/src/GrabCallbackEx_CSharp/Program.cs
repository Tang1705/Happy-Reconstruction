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
// $Id: Program.cs 316528 2017-02-22 00:03:53Z alin $
//=============================================================================

using System;
using System.Text;
using System.Threading;

using FlyCapture2Managed;

namespace GrabCallbackEx_CSharp
{
    class Program
    {
        static uint ImageCount = 0;

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

        void OnImageGrabbed(ManagedImage image)
        {
            Console.WriteLine("Grabbed image {0} - {1}.{2}", ImageCount++,
                image.timeStamp.cycleSeconds,
                image.timeStamp.cycleCount);
        }

        void RunSingleCamera(ManagedPGRGuid guid)
        {
            const int NumImages = 10;

            ManagedCamera cam = new ManagedCamera();

            // Connect to a camera
            cam.Connect(guid);

            // Get the camera information
            CameraInfo camInfo = cam.GetCameraInfo();

            PrintCameraInfo(camInfo);

            // Get embedded image info from camera
            EmbeddedImageInfo embeddedInfo = cam.GetEmbeddedImageInfo();

            // Enable timestamp collection
            if (embeddedInfo.timestamp.available == true)
            {
                embeddedInfo.timestamp.onOff = true;
            }

            // Set embedded image info to camera
            cam.SetEmbeddedImageInfo(embeddedInfo);

            // Start capturing images
            cam.StartCapture(OnImageGrabbed);

            CameraProperty frameRateProp = cam.GetProperty(PropertyType.FrameRate);

            while (ImageCount < 10)
            {
                int millisecondsToSleep = (int)(1000 / frameRateProp.absValue);
                Thread.Sleep(millisecondsToSleep);
            }

            // Stop capturing images
            cam.StopCapture();

            // Disconnect the camera
            cam.Disconnect();

            // Reset counter for next iteration
            ImageCount = 0;
        }

        static void Main(string[] args)
        {
            PrintBuildInfo();

            Program program = new Program();

            ManagedBusManager busMgr = new ManagedBusManager();
            uint numCameras = busMgr.GetNumOfCameras();

            Console.WriteLine("Number of cameras detected: {0}", numCameras);

            // Finish if there are no cameras
            if (numCameras == 0)
            {
                Console.WriteLine("Not enough cameras!");
                Console.WriteLine("Press Enter to exit...");
                Console.ReadLine();
                return;
            }

            for (uint i = 0; i < numCameras; i++)
            {
                ManagedPGRGuid guid = busMgr.GetCameraFromIndex(i);

                program.RunSingleCamera(guid);
            }

            Console.WriteLine("Done! Press enter to exit...");
            Console.ReadLine();
        }
    }
}
