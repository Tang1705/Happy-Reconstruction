'=============================================================================
' Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
'
' This software Is the confidential And proprietary information of FLIR
' Integrated Imaging Solutions, Inc. ("Confidential Information"). You
' shall Not disclose such Confidential Information And shall use it only in
' accordance with the terms of the license agreement you entered into
' with FLIR Integrated Imaging Solutions, Inc. (FLIR).
'
' FLIR MAKES NO REPRESENTATIONS Or WARRANTIES ABOUT THE SUITABILITY OF THE
' SOFTWARE, EITHER EXPRESSED Or IMPLIED, INCLUDING, BUT Not LIMITED TO, THE
' IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
' PURPOSE, Or NON-INFRINGEMENT. FLIR SHALL Not BE LIABLE FOR ANY DAMAGES
' SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING Or DISTRIBUTING
' THIS SOFTWARE Or ITS DERIVATIVES.
'=============================================================================
' =============================================================================
' $Id: FlyCapture2Test.vb 317548 2017-03-01 19:27:16Z alin $
' =============================================================================

Imports System
Imports System.Text
Imports System.IO
Imports System.Drawing
Imports FlyCapture2Managed

Namespace FlyCapture2Test_VB
    Class Program

        Shared Sub PrintBuildInfo()

            Dim version As FC2Version = ManagedUtilities.libraryVersion
            Dim newStr As StringBuilder = New StringBuilder()
            newStr.AppendFormat("FlyCapture2 library version: {0}.{1}.{2}.{3}" & vbNewLine, _
                                version.major, version.minor, version.type, version.build)
            Console.WriteLine(newStr)

        End Sub

        Shared Sub PrintCameraInfo(ByVal camInfo As CameraInfo)

            Dim newStr As StringBuilder = New StringBuilder()
            newStr.Append(vbNewLine & "*** CAMERA INFORMATION ***" & vbNewLine)
            newStr.AppendFormat("Serial number - {0}" & vbNewLine, camInfo.serialNumber)
            newStr.AppendFormat("Camera model - {0}" & vbNewLine, camInfo.modelName)
            newStr.AppendFormat("Camera vendor - {0}" & vbNewLine, camInfo.vendorName)
            newStr.AppendFormat("Sensor - {0}" & vbNewLine, camInfo.sensorInfo)
            newStr.AppendFormat("Resolution - {0}" & vbNewLine, camInfo.sensorResolution)

            Console.WriteLine(newStr)

        End Sub

        Sub RunSingleCamera(ByVal guid As ManagedPGRGuid)

            Const NumImages As Integer = 10

            Dim cam As ManagedCamera = New ManagedCamera()

            ' Connect to a camera
            cam.Connect(guid)

            ' Get the camera information
            Dim camInfo As CameraInfo = cam.GetCameraInfo()

            PrintCameraInfo(camInfo)

            ' Get embedded image info from camera
            Dim embeddedInfo As EmbeddedImageInfo = cam.GetEmbeddedImageInfo()

            ' Enable timestamp collection	
            If (embeddedInfo.timestamp.available = True) Then
                embeddedInfo.timestamp.onOff = True
            End If

            ' Set embedded image info to camera
            cam.SetEmbeddedImageInfo(embeddedInfo)

            ' Start capturing images
            cam.StartCapture()

            ' Create a raw image
            Dim rawImage As ManagedImage = New ManagedImage()

            ' Create a converted image
            Dim convertedImage As ManagedImage = New ManagedImage()

            For imageCnt As Integer = 0 To (NumImages - 1)
                Try
                    ' Retrieve an image
                    cam.RetrieveBuffer(rawImage)
                Catch ex As FC2Exception
                    Console.WriteLine("Error retrieving buffer : {0}", ex.Message)
                    Continue For
                End Try

                ' Get the timestamp
                Dim timeStamp As TimeStamp = rawImage.timeStamp

                Console.WriteLine( _
                   "Grabbed image {0} - {1} {2} {3}", _
                   imageCnt, _
                   timeStamp.cycleSeconds, _
                   timeStamp.cycleCount, _
               timeStamp.cycleOffset)

                ' Convert the raw image
                rawImage.Convert(PixelFormat.PixelFormatBgr, convertedImage)

                ' Create a unique filename
                Dim filename As String = String.Format( _
                   "FlyCapture2Test_CSharp-{0}-{1}.bmp", _
                   camInfo.serialNumber, _
                   imageCnt)

                ' Get the Bitmap object. Bitmaps are only valid if the
                ' pixel format of the ManagedImage is RGB or RGBU.
                Dim bitmap As Bitmap = convertedImage.bitmap

                ' Save the image
                bitmap.Save(filename)
            Next

            ' Stop capturing images
            cam.StopCapture()

            ' Disconnect the camera
            cam.Disconnect()

        End Sub

        Shared Sub Main()
            PrintBuildInfo()

            Dim program As Program = New Program()

            ' Since this application saves images in the current folder
            ' we must ensure that we have permission to write to this folder.
            ' If we do not have permission, fail right away.
            Dim fileStream As FileStream

            Try
                fileStream = New FileStream("test.txt", FileMode.Create)
                fileStream.Close()
                File.Delete("test.txt")
            Catch ex As Exception
                Console.WriteLine("Failed to create file in current folder. Please check permissions.")
                Console.WriteLine("Press enter to exit...")
                Console.ReadLine()
                Return
            End Try

            Dim busMgr As ManagedBusManager = New ManagedBusManager()
            Dim numCameras As UInt32 = busMgr.GetNumOfCameras()

            Console.WriteLine("Number of cameras detected: {0}", numCameras)

            If numCameras < 1 Then
                Console.WriteLine("No cameras detected!")
                Console.WriteLine("Press enter to exit...")
                Console.ReadLine()
                Return
            End If

            For i As UInt32 = 0 To (numCameras - 1)
                Dim guid As ManagedPGRGuid = busMgr.GetCameraFromIndex(i)
                program.RunSingleCamera(guid)
            Next

            Console.WriteLine("Done! Press enter to exit...")
            Console.ReadLine()
        End Sub
    End Class
End Namespace