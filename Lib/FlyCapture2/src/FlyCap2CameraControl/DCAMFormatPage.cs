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
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /* If you can not open the design view of this class, try to modify base class
     * to "UserControl" instead of "BasePage". VS2005 probably has issue of opening 
     * design view for inherited user control. The reason is still investigating.
     * */

    //internal partial class DCAMFormatPage : UserControl
    internal partial class DCAMFormatPage : BasePage
    {
        private const uint k_numOfResolutionModes = 7;
        private const uint k_numOfPixelFormat = 6;
        private const uint k_numOfFrameRateButtons = 8;
        private const VideoMode k_theFirstVideoMode = VideoMode.VideoMode160x120Yuv444;
        private const FrameRate k_theFirstFrameRateType = FrameRate.FrameRate1_875;
        private RadioButton[,] m_videoModeRadioButtons = null;
        private RadioButton[] m_frameRateRadioButton = new RadioButton[k_numOfFrameRateButtons];

        private FrameRate m_currentFrameRate = FrameRate.NumberOfFrameRates; // the initial value can not be null
        private VideoMode m_currentVideoMode = VideoMode.NumberOfVideoModes;
        private bool m_isUpdatingRadioStatus = false;

        public DCAMFormatPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitializePage();
        }

        public void UpdateRadioButtonStatusFromCamera()
        {
            if (m_camera == null)
            {
                // Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            m_isUpdatingRadioStatus = true;
            InitializeCurrentVideoModeAndFrameRate();
            bool disableAll = LadybugChecker.IsLadybugDLLPresent() && LadybugChecker.IsLadybug(m_camInfo) && IsCameraStreaming();
            if (m_currentVideoMode == VideoMode.VideoModeFormat7)
            {
                m_format7RadioButton.Checked = true;
                DisableFrameRateButtons();
                m_isUpdatingRadioStatus = false;
                if (m_videoModeRadioButtons != null)
                {
                    for (int y = 0; y < m_videoModeRadioButtons.GetLength(1); y++)
                    {
                        for (int x = 0; x < m_videoModeRadioButtons.GetLength(0); x++)
                        {
                            if (disableAll == true)
                            {
                                m_videoModeRadioButtons[x, y].Enabled = false;
                            }
                            else
                            {
                                m_videoModeRadioButtons[x, y].Enabled = true;
                            }

                            m_videoModeRadioButtons[x, y].Checked = false;
                        }
                    }
                }

                return;
            }
            else
            {
                for (int y = 0; y < m_videoModeRadioButtons.GetLength(1); y++)
                {
                    for (int x = 0; x < m_videoModeRadioButtons.GetLength(0); x++)
                    {
                        if (disableAll)
                        {
                            m_videoModeRadioButtons[x, y].Enabled = false;
                        }
                        else
                        {
                            m_videoModeRadioButtons[x, y].Enabled = true;
                        }

                        if (m_videoModeRadioButtons[x, y].Visible &&
                            (m_currentVideoMode == ((VideoMode)m_videoModeRadioButtons[x, y].Tag)))
                        {
                            m_videoModeRadioButtons[x, y].Checked = true;
                        }
                        else
                        {
                            m_videoModeRadioButtons[x, y].Checked = false;
                        }
                    }
                }
            }

            UpdateCurrentAvailableFrameRate(m_currentVideoMode);
            UpdateCheckStatusForFrameRateRadioButtons();
            m_isUpdatingRadioStatus = false;
        }

        private static string GetNameOfRadioButtonLocationX(int locationX)
        {
            string result;
            switch (locationX)
            {
                case 0:
                    result = "Y8";
                    break;
                case 1:
                    result = "Y16";
                    break;
                case 2:
                    result = "Rgb";
                    break;
                case 3:
                    result = "Yuv411";
                    break;
                case 4:
                    result = "Yuv422";
                    break;
                case 5:
                    result = "Yuv444";
                    break;
                default:
                    result = "Unknown";
                    break;
            }

            return result;
        }

        private static string GetNameOfRadioButtonLocationY(int locationY)
        {
            string result;
            switch (locationY)
            {
                case 0:
                    result = "160x120";
                    break;
                case 1:
                    result = "320x240";
                    break;
                case 2:
                    result = "640x480";
                    break;
                case 3:
                    result = "800x600";
                    break;
                case 4:
                    result = "1024x768";
                    break;
                case 5:
                    result = "1280x960";
                    break;
                case 6:
                    result = "1600x1200";
                    break;
                default:
                    result = "Unknown";
                    break;
            }

            return result;
        }

        private void InitializePage()
        {
            if (m_camera == null)
            {
                // Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            InitializeCurrentVideoModeAndFrameRate();
            InitialFrameRateRadioButtons();
            InitializeModeRadioButtons();
            UpdateRadioButtonStatusFromCamera();
        }

        private void InitializeCurrentVideoModeAndFrameRate()
        {
            if (IsIIDC())
            {
                ManagedCamera camera = (ManagedCamera)m_camera;

                try
                {
                    camera.GetVideoModeAndFrameRate(ref m_currentVideoMode, ref m_currentFrameRate);
                }
                catch (FC2Exception ex)
                {
                    string error = string.Format("Error getting current video mode and frame rate {0}", ex.Message);
                    Console.WriteLine(error);
                    MessageBox.Show(error, "FlyCapture2 Camera Control", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else if (IsGEV())
            {
                m_currentFrameRate = FrameRate.FrameRateFormat7;
                m_currentVideoMode = VideoMode.VideoModeFormat7;
            }
            else
            {
                Debug.WriteLine("The Camera is unknown tpye. Can not get Current Frame Rate.");
                return;
            }
        }

        private void InitialFrameRateRadioButtons()
        {
            /*foreach (FrameRate frameRateIterator in Enum.GetValues(typeof(FrameRate)))
            {
                Console.WriteLine("FrameRate Type: {0}", frameRateIterator);
            }*/
            if (m_currentFrameRate == FrameRate.NumberOfFrameRates)
            {
                DisableFrameRateButtons();
                return;
            }

            MapFrameRateRadioButtons();
            FrameRate frameRateIterator = k_theFirstFrameRateType;
            for (int i = 0; i < m_frameRateRadioButton.Length; i++)
            {
                if (m_frameRateRadioButton[i] == null)
                {
                    //skip unmapped radio buttons
                    continue;
                }

                if (frameRateIterator == FrameRate.NumberOfFrameRates)
                {
                    //reach the end of frame rate elements
                    //this should not happen if mapping function is working correctly
                    Console.WriteLine("The frame rate radio button mapping is incorrect. The mapping function has bug.");
                    break;
                }

                m_frameRateRadioButton[i].Tag = frameRateIterator;
                if (m_currentFrameRate == frameRateIterator)
                {
                    m_frameRateRadioButton[i].Checked = true;
                }

                m_frameRateRadioButton[i].CheckedChanged += new EventHandler(FrameRateRadioButton_CheckedChanged);
                frameRateIterator++;
            }

            if (m_currentVideoMode == VideoMode.VideoModeFormat7)
            {
                m_format7RadioButton.Checked = true;
                DisableFrameRateButtons();
                return;
            }
        }

        private void MapFrameRateRadioButtons()
        {
            //map radio buttons
            m_frameRateRadioButton[0] = m_frameRate_1_875_RadioButton;
            m_frameRateRadioButton[1] = m_frameRate_3_75_RadioButton;
            m_frameRateRadioButton[2] = m_frameRate_7_5_RadioButton;
            m_frameRateRadioButton[3] = m_frameRate_15_RadioButton;
            m_frameRateRadioButton[4] = m_frameRate_30_RadioButton;
            m_frameRateRadioButton[5] = m_frameRate_60_RadioButton;
            m_frameRateRadioButton[6] = m_frameRate_120_RadioButton;
            m_frameRateRadioButton[7] = m_frameRate_240_RadioButton;
        }

        private void DisableFrameRateButtons()
        {
            for (int i = 0; i < m_frameRateRadioButton.Length; i++)
            {
                if (m_frameRateRadioButton[i] == null)
                {
                    //skip unmapped radio buttons
                    continue;
                }

                m_frameRateRadioButton[i].Visible = false;
            }
        }

        private void InitializeModeRadioButtons()
        {
            bool isLadybugGui = LadybugChecker.IsLadybugDLLPresent() && LadybugChecker.IsLadybug(m_camInfo);
            if (IsIIDC())
            {
                m_videoModeRadioButtons = new RadioButton[k_numOfPixelFormat, k_numOfResolutionModes];
                ManagedCamera camera = (ManagedCamera)m_camera;

                // Update the video mode radio buttons
                // Loop through all the video modes
                // For each video mode, loop through all the frame rates
                // If the camera supports this video mode at any frame rate, then
                // the radio button should be shown
                ArrayList supportedVideoMode = GetIIDCSupportedVideoMode(camera);
                for (int y = 0; y < m_videoModeRadioButtons.GetLength(1); y++)
                {
                    for (int x = 0; x < m_videoModeRadioButtons.GetLength(0); x++)
                    {
                        //bool supported = false;
                        string buttonStringName = string.Format("VideoMode{1}{0}", GetNameOfRadioButtonLocationX(x), GetNameOfRadioButtonLocationY(y));
                        m_videoModeRadioButtons[x, y] = new RadioButton();
                        m_videoModeRadioButtons[x, y].Tag = null;
                        m_videoModeRadioButtons[x, y].Visible = false;
                        m_videoModeRadioButtons[x, y].AutoSize = true;
                        m_videoModeRadioButtons[x, y].Anchor = AnchorStyles.None;
                        m_radioButtonLayout.Controls.Add(m_videoModeRadioButtons[x, y], x, y);
                        foreach (VideoMode videoModeIterator in supportedVideoMode)
                        {
                            if (buttonStringName.Equals(videoModeIterator.ToString()))
                            {
                                m_videoModeRadioButtons[x, y].Visible = true;

                                //TODO: need to check this function is working properly or not, for bug 12879
                                if (isLadybugGui == true && (IsCameraStreaming() == true))
                                {
                                    m_videoModeRadioButtons[x, y].Enabled = false;
                                }
                                else
                                {
                                    m_videoModeRadioButtons[x, y].Enabled = true;
                                }

                                m_videoModeRadioButtons[x, y].Tag = videoModeIterator;
                                if (m_currentVideoMode == videoModeIterator)
                                {
                                    m_videoModeRadioButtons[x, y].Checked = true;
                                }

                                break;
                            }
                        }

                        m_videoModeRadioButtons[x, y].CheckedChanged += new EventHandler(VideoModeRadioButton_CheckedChanged);
                    }
                }

                m_format7RadioButton.Visible = true;
            }
            else if (IsGEV())
            {
                m_videoModeRadioButtons = null;
                m_format7RadioButton.Visible = true;
            }
        }

        private void VideoModeRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (!button.Checked)
            {
                // This function gets called twice, when the old button
                // is unchecked, and the new button is checked
                return;
            }

            if (!IsIIDC())
            {
                // Nothing to do here
                return;
            }

            VideoMode newVideoMode = (VideoMode)button.Tag;
            FrameRate fastestFrameRate = UpdateCurrentAvailableFrameRate(newVideoMode);
            if (fastestFrameRate != FrameRate.NumberOfFrameRates)
            {
                // update camera frame rate and video mode,set current frame rate to fastest
                SetCameraVideoModeAndFrameRate(newVideoMode, fastestFrameRate);
            }
            else
            {
#if (DEBUG)
                Debug.WriteLine("Bug: There is no frame rate for this video mode. This should not happen.");
                MessageBox.Show("Bug: There is no frame rate for this video mode. This should not happen.", "Failed to Set Frame rate", MessageBoxButtons.OK, MessageBoxIcon.Error);
#endif
            }
        }

        private void SetCameraVideoModeAndFrameRate(VideoMode newVideoMode, FrameRate newFrameRate)
        {
            if (m_isUpdatingRadioStatus)
            {
                Debug.WriteLine("There is a update action in progress, setting video mode and frame rate failed. ");
                
                // avoid update confliction
                return;
            }

            if ((m_currentVideoMode == newVideoMode) && (m_currentFrameRate == newFrameRate))
            {
                // nothing changed
                return;
            }

            ManagedCamera camera = (ManagedCamera)m_camera;
            bool needToRestartCamera = true;
            bool noError = true;
            try
            {
                camera.StopCapture();
            }
            catch (FC2Exception ex)
            {
                if (ex.Type == ErrorType.IsochNotStarted)
                {
                    // This means the camera was stopped and therefore we
                    // do not need to restart it
                    needToRestartCamera = false;
                }
                else
                {
                    string error = string.Format("Error stopping capture. {0}", ex.Message);
                    Console.WriteLine(error);
                    DialogResult result = MessageBox.Show(
                                          string.Format(
                                          "{0}\r\n Do you wish to continue change the mode? Click ok to continue",
                                          error),
                                          "FlyCapture2 Camera Control", 
                                          MessageBoxButtons.OKCancel, 
                                          MessageBoxIcon.Error);
                    if (result == DialogResult.Cancel)
                    {
                        return;
                    }
                }
            }

            try
            {
                camera.SetVideoModeAndFrameRate(newVideoMode, newFrameRate);
            }
            catch (FC2Exception ex)
            {
                string error = string.Format("Error setting video mode and frame rate. {0}", ex.Message);
                Console.WriteLine(error);
                MessageBox.Show(error, "FlyCapture2 Camera Control", MessageBoxButtons.OK, MessageBoxIcon.Error);
                noError = false;
                ex.Dispose();
            }

            if (needToRestartCamera == true)
            {
                try
                {
                    camera.StartCapture();
                }
                catch (FC2Exception ex)
                {
                    string error = string.Format("Error restarting image streaming. {0}", ex.Message);
                    Console.WriteLine(error);
                    MessageBox.Show(error, "FlyCapture2 Camera Control", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    ex.Dispose();
                }
            }

            if (noError == true)
            {
                // if everything ok, update current video mode and frame rate
                m_currentFrameRate = newFrameRate;
                m_currentVideoMode = newVideoMode;

                // update check status for frame rate radio buttons
                UpdateCheckStatusForFrameRateRadioButtons();
            }
        }

        private void UpdateCheckStatusForFrameRateRadioButtons()
        {
            if (m_currentVideoMode == VideoMode.VideoModeFormat7)
            {
                m_format7RadioButton.Checked = true;
                DisableFrameRateButtons();
                return;
            }

            m_format7RadioButton.Checked = false;

            for (int i = 0; i < m_frameRateRadioButton.Length; i++)
            {
                if (m_frameRateRadioButton[i] == null)
                {
                    //skip unmapped radio buttons
                    continue;
                }

                FrameRate frameRate = (FrameRate)m_frameRateRadioButton[i].Tag;
                if (frameRate == m_currentFrameRate)
                {
                    m_frameRateRadioButton[i].Checked = true;
                }
                else
                {
                    m_frameRateRadioButton[i].Checked = false;
                }
            }
        }

        private void FrameRateRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (!button.Checked)
            {
                // This function gets called twice, when the old button
                // is unchecked, and the new button is checked
                return;
            }

            // if this button is checked, then check to see if the frame rate needs to change
            FrameRate frameRate = (FrameRate)button.Tag;
            if (m_currentFrameRate == frameRate)
            {
                //frame rate is same as current frame rate
                //then there is no need to change
                return;
            }

            SetCameraVideoModeAndFrameRate(m_currentVideoMode, frameRate);
        }

        private FrameRate UpdateCurrentAvailableFrameRate(VideoMode currentVideoMode)
        {
            //this function will return the current fastest frame rate for this video mode
            ManagedCamera camera = (ManagedCamera)m_camera; 
            FrameRate fastestFrameRate = FrameRate.NumberOfFrameRates;
            for (int i = 0; i < m_frameRateRadioButton.Length; i++)
            {
                if (m_frameRateRadioButton[i] == null)
                {
                    //skip unmapped radio buttons
                    continue;
                }

                bool supported = false;
                FrameRate currentFrameRate = (FrameRate)m_frameRateRadioButton[i].Tag;
                try
                {
                    supported = camera.GetVideoModeAndFrameRateInfo(currentVideoMode, currentFrameRate);
                }
                catch (FC2Exception ex)
                {
                    string error = string.Format("Error querying video mode and frame rate {0}", ex.Message);
                    Console.WriteLine(error);
                    MessageBox.Show(error, "FlyCapture2 Camera Control", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    ex.Dispose();
                    break;
                }

                if (supported)
                {
                    m_frameRateRadioButton[i].Visible = true;
                    fastestFrameRate = currentFrameRate;
                }
                else
                {
                    m_frameRateRadioButton[i].Visible = false;
                }
            }

            return fastestFrameRate;
        }

        private ArrayList GetIIDCSupportedVideoMode(ManagedCamera camera)
        {
            ArrayList supportedVideoMode = new ArrayList();
            for (VideoMode videoModeIterator = k_theFirstVideoMode;
                 videoModeIterator < VideoMode.NumberOfVideoModes; // VideoMode.NumberOfVideoModes is always the last element in the enum
                 videoModeIterator++)
            {
                if (videoModeIterator == VideoMode.VideoModeFormat7)
                {
                    //skip this video mode, it is for ManagedGigECamera (GEV)
                    continue;
                }

                for (FrameRate frameRateIterator = k_theFirstFrameRateType; frameRateIterator < FrameRate.NumberOfFrameRates; frameRateIterator++)
                {
                    bool supported = false;
                    if (frameRateIterator == FrameRate.FrameRateFormat7)
                    {
                        //skip this frame rate, it is for ManagedGigECamera (GEV)
                        continue;
                    }

                    try
                    {
                        supported = camera.GetVideoModeAndFrameRateInfo(videoModeIterator, frameRateIterator);
                    }
                    catch (FC2Exception ex)
                    {
                        string error = string.Format("Error querying video mode and frame rate {0}", ex.Message);
                        Console.WriteLine(error);
                        MessageBox.Show(error, "FlyCapture2 Camera Control", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        break;
                    }

                    if (supported)
                    {
                        supportedVideoMode.Add(videoModeIterator);
                        break;
                    }
                }
            }

            return supportedVideoMode;
        }

        private void OnFormat7RadioButtonCheckedStatusChanged(object sender, EventArgs e)
        {
            RadioButton fmt7Button = (RadioButton)sender;
            if (fmt7Button.Checked == true)
            {
                SetCameraVideoModeAndFrameRate(VideoMode.VideoModeFormat7, FrameRate.FrameRateFormat7);
            }
        }
    }
}
