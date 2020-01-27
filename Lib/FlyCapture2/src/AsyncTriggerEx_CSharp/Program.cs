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
// $Id: Program.cs 317586 2017-03-01 23:16:12Z alin $
//=============================================================================

using System;
using System.Text;

using FlyCapture2Managed;

namespace AsyncTriggerEx_CSharp
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

        static bool CheckSoftwareTriggerPresence(ManagedCamera cam)
        {
            const uint TriggerInquiry = 0x530;
            uint triggerInquiryValue = cam.ReadRegister(TriggerInquiry);

            if ((triggerInquiryValue & 0x10000) != 0x10000)
            {
                return false;
            }

            return true;
        }

        static bool PollForTriggerReady(ManagedCamera cam)
        {
            const uint SoftwareTrigger = 0x62C;

            uint softwareTriggerValue = 0;

            do
            {
                softwareTriggerValue = cam.ReadRegister(SoftwareTrigger);
            }
            while ((softwareTriggerValue >> 31) != 0);

            return true;
        }

        static bool FireSoftwareTrigger(ManagedCamera cam)
        {
            const uint SoftwareTrigger = 0x62C;
            const uint SoftwareTriggerFireValue = 0x80000000;

            cam.WriteRegister(SoftwareTrigger, SoftwareTriggerFireValue);

            return true;
        }

        static void Main(string[] args)
        {
            PrintBuildInfo();

            const int NumImages = 10;
            bool useSoftwareTrigger = true;

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

            ManagedPGRGuid guid = busMgr.GetCameraFromIndex(0);

            ManagedCamera cam = new ManagedCamera();

            cam.Connect(guid);

            // Power on the camera
            const uint CameraPower = 0x610;
            const uint CameraPowerValue = 0x80000000;
            cam.WriteRegister(CameraPower, CameraPowerValue);

            const Int32 MillisecondsToSleep = 100;
            uint cameraPowerValueRead = 0;

            // Wait for camera to complete power-up
            do
            {
                System.Threading.Thread.Sleep(MillisecondsToSleep);

                cameraPowerValueRead = cam.ReadRegister(CameraPower);
            }
            while ((cameraPowerValueRead & CameraPowerValue) == 0);

            // Get the camera information
            CameraInfo camInfo = cam.GetCameraInfo();

            PrintCameraInfo(camInfo);

            if (!useSoftwareTrigger)
            {
                // Check for external trigger support
                TriggerModeInfo triggerModeInfo = cam.GetTriggerModeInfo();
                if (triggerModeInfo.present != true)
                {
                    Console.WriteLine("Camera does not support external trigger!");
                    Console.WriteLine("Press enter to exit...");
                    Console.ReadLine();
                    return;
                }
            }

            // Get current trigger settings
            TriggerMode triggerMode = cam.GetTriggerMode();

            // Set camera to trigger mode 0
            // A source of 7 means software trigger
            triggerMode.onOff = true;
            triggerMode.mode = 0;
            triggerMode.parameter = 0;

            if (useSoftwareTrigger)
            {
                // A source of 7 means software trigger
                triggerMode.source = 7;
            }
            else
            {
                // Triggering the camera externally using source 0.
                triggerMode.source = 0;
            }

            // Set the trigger mode
            cam.SetTriggerMode(triggerMode);

            // Poll to ensure camera is ready
            bool retVal = PollForTriggerReady(cam);
            if (retVal != true)
            {
                Console.WriteLine("Poll for trigger read failed!");
                Console.WriteLine("Press enter to exit...");
                Console.ReadLine();
                return;
            }

            // Get the camera configuration
            FC2Config config = cam.GetConfiguration();

            // Set the grab timeout to 5 seconds
            config.grabTimeout = 5000;

            // Set the camera configuration
            cam.SetConfiguration(config);

            // Camera is ready, start capturing images
            cam.StartCapture();

            if (useSoftwareTrigger)
            {
                if (CheckSoftwareTriggerPresence(cam) == false)
                {
                    Console.WriteLine("SOFT_ASYNC_TRIGGER not implemented on this camera!  Stopping application\n");
                    Console.WriteLine("Press enter to exit...");
                    Console.ReadLine();
                    return;
                }
            }
            else
            {
                Console.WriteLine("Trigger the camera by sending a trigger pulse to GPIO%d.\n",
                  triggerMode.source);
            }

            ManagedImage rawImage = new ManagedImage();
            for (int iImageCount = 0; iImageCount < NumImages; iImageCount++)
            {
                if (useSoftwareTrigger)
                {
                    // Check that the trigger is ready
                    retVal = PollForTriggerReady(cam);

                    Console.WriteLine("Press the Enter key to initiate a software trigger.\n");
                    Console.ReadLine();

                    // Fire software trigger
                    retVal = FireSoftwareTrigger(cam);
                    if (retVal != true)
                    {
                        Console.WriteLine("Error firing software trigger!");
                        Console.WriteLine("Press enter to exit...");
                        Console.ReadLine();
                        return;
                    }
                }

                try
                {
                    // Retrieve an image
                    cam.RetrieveBuffer(rawImage);
                }
                catch (FC2Exception ex)
                {
                    Console.WriteLine("Error retrieving buffer : {0}", ex.Message);
                    continue;
                }

                Console.WriteLine(".\n");
            }

            Console.WriteLine("Finished grabbing images");

            // Stop capturing images
            cam.StopCapture();

            // Turn off trigger mode
            triggerMode.onOff = false;
            cam.SetTriggerMode(triggerMode);

            // Disconnect the camera
            cam.Disconnect();

            Console.WriteLine("Done! Press enter to exit...");
            Console.ReadLine();
        }
    }
}
