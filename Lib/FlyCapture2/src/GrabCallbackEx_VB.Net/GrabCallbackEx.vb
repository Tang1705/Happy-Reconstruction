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
' $Id: GrabCallBackEx.vb 316528 2017-02-22 00:03:53Z alin $
' =============================================================================

Imports System
Imports System.Text
Imports System.Threading
Imports FlyCapture2Managed

Namespace GrabCallbackEx_VB
    Class Program

        Shared ImageCount As UInteger = 0

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

        Sub OnImageGrabbed(ByVal image As ManagedImage)
            Console.WriteLine("Grabbed image {0} - {1}.{2}", _
                ImageCount, _
                image.timeStamp.cycleSeconds, _
                image.timeStamp.cycleCount)
            ImageCount += 1
        End Sub

        Sub RunSingleCamera(ByVal guid As ManagedPGRGuid)

            Dim cam As ManagedCamera = New ManagedCamera()

            ' Connect to a camera
            cam.Connect(guid)

            ' Get the camera information
            Dim camInfo As CameraInfo = cam.GetCameraInfo()

            PrintCameraInfo(camInfo)

            ' Get embedded image info from camera
            Dim embeddedInfo As EmbeddedImageInfo = cam.GetEmbeddedImageInfo()

            ' Enable timestamp collection	
            If (embeddedInfo.timestamp.available) Then
                embeddedInfo.timestamp.onOff = True
            End If

            ' Set embedded image info to camera
            cam.SetEmbeddedImageInfo(embeddedInfo)

            ' Start capturing images
            cam.StartCapture(AddressOf OnImageGrabbed)

            Dim frameRateProp As CameraProperty = cam.GetProperty(PropertyType.FrameRate)

            While (ImageCount < 10)
                Dim millisecondsToSleep As Integer = (1000 / frameRateProp.absValue)
                Thread.Sleep(millisecondsToSleep)
            End While

            ' Stop capturing images
            cam.StopCapture()

            ' Disconnect the camera
            cam.Disconnect()
        End Sub

        Shared Sub Main()

            PrintBuildInfo()

            Dim program As Program = New Program()

            Dim busMgr As ManagedBusManager = New ManagedBusManager()
            Dim numCameras As UInteger = busMgr.GetNumOfCameras()

            Console.WriteLine("Number of cameras detected: {0}", numCameras)

            If numCameras < 1 Then
                Console.WriteLine("No cameras detected!")
                Console.WriteLine("Press enter to exit...")
                Console.ReadLine()
                Return
            End If

            For i As UInteger = 0 To (numCameras - 1)
                Dim guid As ManagedPGRGuid = busMgr.GetCameraFromIndex(i)
                program.RunSingleCamera(guid)
            Next

            Console.WriteLine("Done! Press enter to exit...")
            Console.ReadLine()
        End Sub

    End Class
End Namespace