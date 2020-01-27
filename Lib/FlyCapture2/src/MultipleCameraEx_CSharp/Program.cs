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

using FlyCapture2Managed;

namespace MultipleCameraEx_CSharp
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

        static void Main(string[] args)
        {
            PrintBuildInfo();

            const int NumImages = 50;

            Program program = new Program();

            //
            // Initialize BusManager and retrieve number of cameras detected
            //
            ManagedBusManager busMgr = new ManagedBusManager();
            uint numCameras = busMgr.GetNumOfCameras();

            Console.WriteLine("Number of cameras detected: {0}", numCameras);

            //
            // Check to make sure at least two cameras are connected before
            // running example
            //
            if (numCameras < 2)
            {
                Console.WriteLine("Insufficient number of cameras.");
                Console.WriteLine("Make sure at least two cameras are connected for example to run.");
                Console.WriteLine("Press Enter to exit.");
                Console.ReadLine();
                return;
            }

            //
            // Initialize an array of cameras
            //
            // *** NOTES ***
            // The size of the array is equal to the number of cameras detected.
            // The array of cameras will be used for connecting, configuring,
            // and capturing images.
            //
            ManagedCamera[] cameras = new ManagedCamera[numCameras];

            //
            // Prepare each camera to acquire images
            //
            // *** NOTES ***
            // For pseudo-simultaneous streaming, each camera is prepared as if it
            // were just one, but in a loop. Notice that cameras are selected with
            // an index. We demonstrate pseduo-simultaneous streaming because true
            // simultaneous streaming would require multiple process or threads,
            // which is too complex for an example.
            //
            for (uint i = 0; i < numCameras; i++)
            {
                cameras[i] = new ManagedCamera();

                ManagedPGRGuid guid = busMgr.GetCameraFromIndex(i);

                // Connect to a camera
                cameras[i].Connect(guid);

                // Get the camera information
                CameraInfo camInfo = cameras[i].GetCameraInfo();
                PrintCameraInfo(camInfo);

                try
                {
                    // Turn trigger mode off
                    TriggerMode trigMode = new TriggerMode();
                    trigMode.onOff = false;
                    cameras[i].SetTriggerMode(trigMode);

                    // Turn Timestamp on
                    EmbeddedImageInfo imageInfo = new EmbeddedImageInfo();
                    imageInfo.timestamp.onOff = true;
                    cameras[i].SetEmbeddedImageInfo(imageInfo);
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine("Error configuring camera : {0}", ex.Message);
                    Console.WriteLine("Press any key to exit...");
                    Console.ReadLine();
                    return;
                }

                try
                {
                    // Start streaming on camera
                    cameras[i].StartCapture();
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine("Error starting camera : {0}", ex.Message);
                    Console.WriteLine("Press any key to exit...");
                    Console.ReadLine();
                    return;
                }
            }

            //
            // Retrieve images from all cameras
            //
            // *** NOTES ***
            // In order to work with simultaneous camera streams, nested loops are
            // needed. It is important that the inner loop be the one iterating
            // through the cameras; otherwise, all images will be grabbed from a
            // single camera before grabbing any images from another.
            //
            ManagedImage tempImage = new ManagedImage();

            for (int imageCnt = 0; imageCnt < NumImages; imageCnt++)
            {
                for (int camCount = 0; camCount < numCameras; camCount++)
                {
                    try
                    {
                        // Retrieve an image
                        cameras[camCount].RetrieveBuffer(tempImage);
                    }
                    catch (System.Exception ex)
                    {
                        Console.WriteLine("Error retrieving buffer : {0}", ex.Message);
                        Console.WriteLine("Press any key to exit...");
                        Console.ReadLine();
                        return;
                    }

                    // Display the timestamps of the images grabbed for each camera
                    TimeStamp timeStamp = tempImage.timeStamp;
                    Console.Out.WriteLine("Camera {0} - Frame {1} - TimeStamp {2} {3}", camCount, imageCnt, timeStamp.cycleSeconds, timeStamp.cycleCount);
                }
            }

            //
            // Stop streaming for each camera
            //
            for (uint i = 0; i < numCameras; i++)
            {
                try
                {
                    cameras[i].StopCapture();
                    cameras[i].Disconnect();
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine("Error cleaning up camera : {0}", ex.Message);
                    Console.WriteLine("Press any key to exit...");
                    Console.ReadLine();
                    return;
                }
            }

            Console.WriteLine("Press enter to exit...");
            Console.ReadLine();
        }
    }
}
