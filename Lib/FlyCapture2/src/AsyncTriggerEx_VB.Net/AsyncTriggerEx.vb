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
' $Id: AsyncTriggerEx.vb 317565 2017-03-01 21:05:37Z alin $
' =============================================================================

Imports System
Imports System.Text
Imports FlyCapture2Managed

Namespace AsyncTriggerEx_VB
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

        Shared Function CheckSoftwareTriggerPresence(ByVal cam As ManagedCamera) As Boolean

            Const TriggerInquiry As UInteger = &H530
            Dim regVal As UInteger = cam.ReadRegister(TriggerInquiry)

            If ((regVal And &H10000) <> &H10000) Then
                Return False
            End If

            Return True

        End Function

        Shared Function PollForTriggerReady(ByVal cam As ManagedCamera) As Boolean

            Const SoftwareTrigger As UInteger = &H62C
            Dim SoftwareTriggerValue As UInteger = 0

            Do
                SoftwareTriggerValue = cam.ReadRegister(SoftwareTrigger)
            Loop While ((SoftwareTriggerValue >> 31) <> 0)

            Return True

        End Function

        Shared Function FireSoftwareTrigger(ByVal cam As ManagedCamera) As Boolean

            Const SoftwareTrigger As UInteger = &H62C
            Const SoftwareTriggerFireValue As UInt32 = &H80000000UI

            cam.WriteRegister(SoftwareTrigger, SoftwareTriggerFireValue)
            Return True

        End Function

        Shared Sub Main()

            PrintBuildInfo()

            Const NumImages As Integer = 10
            Dim useSoftwareTrigger As Boolean = True

            Dim busMgr As ManagedBusManager = New ManagedBusManager()
            Dim numCameras As UInteger = busMgr.GetNumOfCameras()

            Console.WriteLine("Number of cameras detected: {0}", numCameras)

            If numCameras < 1 Then
                Console.WriteLine("No cameras detected!")
                Console.WriteLine("Press enter to exit...")
                Console.ReadLine()
                Return
            End If

            Dim guid As ManagedPGRGuid = busMgr.GetCameraFromIndex(0)

            Dim cam As ManagedCamera = New ManagedCamera()

            cam.Connect(guid)

            ' Power on the camera
            Const CameraPower As UInteger = &H610
            Const CameraPowerValue As UInt32 = &H80000000UI
            cam.WriteRegister(CameraPower, CameraPowerValue)

            ' Wait for camera to complete power-up
            Const MillisecondsToSleep = 100
            Dim regVal As UInteger = 0

            Do While ((regVal And CameraPowerValue) = 0)
                System.Threading.Thread.Sleep(MillisecondsToSleep)
                regVal = cam.ReadRegister(CameraPower)
            Loop

            ' Get the camera information
            Dim camInfo As CameraInfo = cam.GetCameraInfo()

            PrintCameraInfo(camInfo)

            If (Not useSoftwareTrigger) Then

                ' Check for external trigger support
                Dim triggerModeInfo As TriggerModeInfo = cam.GetTriggerModeInfo()

                If (Not triggerModeInfo.present) Then
                    Console.WriteLine("Camera does not support external trigger!")
                    Console.WriteLine("Press enter to exit...")
                    Console.ReadLine()
                    Return
                End If
            End If

            ' Get current trigger settings
            Dim triggerMode As TriggerMode = cam.GetTriggerMode()

            ' Set camera to trigger mode 0
            ' A source of 7 means software trigger
            triggerMode.onOff = True
            triggerMode.mode = 0
            triggerMode.parameter = 0

            If (useSoftwareTrigger) Then
                ' A source of 7 means software trigger
                triggerMode.source = 7
            Else
                ' Triggering the camera externally using source 0.
                triggerMode.source = 0
            End If


            ' Set the trigger mode
            cam.SetTriggerMode(triggerMode)

            ' Poll to ensure camera is ready
            Dim retVal As Boolean = PollForTriggerReady(cam)

            If (Not retVal) Then
                Return
            End If

            ' Get the camera configuration
            Dim config As FC2Config = cam.GetConfiguration()

            ' Set the grab timeout to 5 seconds
            config.grabTimeout = 5000

            ' Set the camera configuration
            cam.SetConfiguration(config)

            ' Camera is ready, start capturing images
            cam.StartCapture()

            If (useSoftwareTrigger) Then
                If (Not CheckSoftwareTriggerPresence(cam)) Then
                    Console.WriteLine("SOFT_ASYNC_TRIGGER not implemented on this camera!")
                    Console.WriteLine("Press enter to exit...")
                    Console.ReadLine()
                    Return
                End If
            Else
                Console.WriteLine("Trigger the camera by sending a trigger pulse to GPIO%d." & vbNewLine, _
                triggerMode.source)
            End If

            Dim rawImage As ManagedImage = New ManagedImage()
            For iImageCount As Integer = 0 To (NumImages - 1)

                If (useSoftwareTrigger) Then

                    ' Check that the trigger is ready
                    retVal = PollForTriggerReady(cam)

                    Console.WriteLine("Press the Enter key to initiate a software trigger." & vbNewLine)
                    Console.ReadLine()

                    ' Fire software trigger
                    retVal = FireSoftwareTrigger(cam)
                    If (Not retVal) Then
                        Console.WriteLine("Error firing software trigger!")
                        Console.WriteLine("Press enter to exit...")
                        Console.ReadLine()
                        Return
                    End If
                End If

                Try
                    ' Retrieve an image
                    cam.RetrieveBuffer(rawImage)
                Catch ex As FC2Exception
                    Console.WriteLine("Error retrieving buffer : {0}", ex.Message)
                    Continue For
                End Try

                Console.WriteLine("." & vbNewLine)
            Next

            Console.WriteLine("Finished grabbing images")

            ' Stop capturing images
            cam.StopCapture()

            ' Turn off trigger mode
            triggerMode.onOff = False
            cam.SetTriggerMode(triggerMode)

            ' Disconnect the camera
            cam.Disconnect()

            Console.WriteLine("Done! Press enter to exit...")
            Console.ReadLine()
        End Sub

    End Class
End Namespace
