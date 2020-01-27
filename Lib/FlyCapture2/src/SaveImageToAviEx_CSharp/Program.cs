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

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

using FlyCapture2Managed;

namespace SaveImageToAviEx_CSharp
{
    class Program
    {
        enum AviType
        {
            Uncompressed,
            Mjpg,
            H264
        }

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

        private void SaveAviHelper(AviType aviType, ref List<ManagedImage> imageList, string aviFileName, float frameRate)
        {
            // Set maximum AVI file size to 2GB. A new AVI file is generated when 2GB
            // limit is reached. Setting maximum file size to 0 indicates no limit.
            const uint AviMaxSize = 2048;

            using (ManagedAVIRecorder aviRecorder = new ManagedAVIRecorder())
            {
                aviRecorder.SetMaximumAVISize(AviMaxSize);

                switch (aviType)
                {
                    case AviType.Uncompressed:
                        {
                            AviOption option = new AviOption();
                            option.frameRate = frameRate;
                            aviRecorder.AVIOpen(aviFileName, option);
                        }
                        break;

                    case AviType.Mjpg:
                        {
                            MJPGOption option = new MJPGOption();
                            option.frameRate = frameRate;
                            option.quality = 75;
                            aviRecorder.AVIOpen(aviFileName, option);
                        }
                        break;

                    case AviType.H264:
                        {
                            H264Option option = new H264Option();
                            option.frameRate = frameRate;
                            option.bitrate = 1000000;
                            option.height = Convert.ToInt32(imageList[0].rows);
                            option.width = Convert.ToInt32(imageList[0].cols);
                            aviRecorder.AVIOpen(aviFileName, option);
                        }
                        break;
                }

                Console.WriteLine("Appending {0} images to AVI file {1}...", imageList.Count, aviFileName);

                for (int imageCnt = 0; imageCnt < imageList.Count; imageCnt++)
                {
                    // Append the image to AVI file
                    aviRecorder.AVIAppend(imageList[imageCnt]);

                    Console.WriteLine("Appended image {0}", imageCnt);
                }

                aviRecorder.AVIClose();
            }
        }

        void RunCamera(ManagedPGRGuid guid)
        {
            const uint NumImages = 100;

            try
            {
                using (ManagedCamera cam = new ManagedCamera())
                {
                    cam.Connect(guid);

                    CameraInfo camInfo = cam.GetCameraInfo();
                    PrintCameraInfo(camInfo);

                    // Start capturing images
                    Console.WriteLine("Starting capture...");
                    cam.StartCapture();

                    List<ManagedImage> imageList = new List<ManagedImage>();

                    ManagedImage rawImage = new ManagedImage();
                    for (int imageCnt = 0; imageCnt < NumImages; imageCnt++)
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
                        ManagedImage tempImage = new ManagedImage(rawImage);
                        imageList.Add(tempImage);

                        Console.WriteLine("Grabbed image {0}", imageCnt);
                    }

                    // Stop capturing images
                    Console.WriteLine("Stopping capture...");

                    // Check if the camera supports the FRAME_RATE property
                    CameraPropertyInfo propInfo = cam.GetPropertyInfo(PropertyType.FrameRate);

                    float frameRateToUse = 15.0F;
                    if (propInfo.present == true)
                    {
                        // Get the frame rate
                        CameraProperty prop = cam.GetProperty(PropertyType.FrameRate);
                        frameRateToUse = prop.absValue;
                    }

                    Console.WriteLine("Using frame rate of {0}", frameRateToUse);

                    string aviFileName;

                    // Uncompressed videos are always saved with avi containers with or without
                    // extensions specified in the filepath
                    aviFileName = String.Format("SaveImageToAviEx_CSharp-Uncompressed-{0}", camInfo.serialNumber);
                    SaveAviHelper(AviType.Uncompressed, ref imageList, aviFileName, frameRateToUse);

                    // Motion JPEG videos are always saved with avi containers with or without
                    // extensions specified in the filepath
                    aviFileName = String.Format("SaveImageToAviEx_CSharp-Mjpg-{0}", camInfo.serialNumber);
                    SaveAviHelper(AviType.Mjpg, ref imageList, aviFileName, frameRateToUse);

                    // H.264 videos defaults to saving in mp4 containers if extensions are not
                    // specified. Otherwise the extension specified by the user will be used.
                    aviFileName = String.Format("SaveImageToAviEx_CSharp-H264-{0}", camInfo.serialNumber);
                    SaveAviHelper(AviType.H264, ref imageList, aviFileName, frameRateToUse);
                }
            }
            catch (FC2Exception ex)
            {
                Console.WriteLine("There was an FC2 error: " + ex.Message);
            }
        }


        static void Main(string[] args)
        {
            PrintBuildInfo();

            Program program = new Program();

            // Since this application saves images in the current folder
            // we must ensure that we have permission to write to this folder.
            // If we do not have permission, fail right away.
            FileStream fileStream;
            try
            {
                fileStream = new FileStream(@"test.txt", FileMode.Create);
                fileStream.Close();
                File.Delete("test.txt");
            }
            catch
            {
                Console.WriteLine("Failed to create file in current folder. Please check permissions.");
                Console.WriteLine("Press Enter to exit...");
                Console.ReadLine();
                return;
            }

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

                program.RunCamera(guid);
            }

            Console.WriteLine("Done! Press enter to exit...");
            Console.ReadLine();
        }
    }
}
