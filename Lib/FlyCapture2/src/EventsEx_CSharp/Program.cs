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
// $Id: Program.cs 320072 2017-03-29 00:32:36Z erich $
//=============================================================================

using System;
using System.Text;

using FlyCapture2Managed;

namespace EventsEx_CSharp
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

        void OnEventReceived(ManagedEventCallbackData data)
        {
            Console.Out.WriteLine("----Event Received----");
            Console.Out.WriteLine(string.Format("EventName = {0}", data.EventName));
            Console.Out.WriteLine(string.Format("EventID = {0:X}", data.EventID));
            Console.Out.WriteLine(string.Format("EventTimeStamp = {0}", data.EventTimestamp));
            Console.Out.WriteLine("---------------------");
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
            
            //
            // Register for End of Exposure (EoE) event. We simply create an instance of
            // the ManagedEventOptions, populate it, and register it with the camera.
            //
            ManagedEventOptions option = new ManagedEventOptions();
            option.EventCallbackFcn = OnEventReceived;
            option.EventName = "EventExposureEnd";

            try
            {
                cam.RegisterEvent(option);

                Console.WriteLine("Successfully registered event: {0}", option.EventName);
            }
            catch (FC2Exception ex)
            {
                Console.WriteLine("Error registering EventExposureEnd : {0}", ex.Message);
                return;
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
            try
            {
                cam.RegisterAllEvents(option);
            }
            catch (FC2Exception ex)
            {
            	// Expected error
                Console.WriteLine("Error registering EventExposureEnd : {0}", ex.Message);
            }

            // Start capturing images
            cam.StartCapture();

            // Retrieve images from buffer
            ManagedImage rawImage = new ManagedImage();
            for (ImageCount = 0; ImageCount < NumImages; ImageCount++)
            {
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
            }

            // Stop capturing images
            cam.StopCapture();

            // Uncomment the following to deregister event handler for specific device event
            //cam.DeregisterEvent(option);

            // Deregister event handler for all events
            cam.DeregisterAllEvents();

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
