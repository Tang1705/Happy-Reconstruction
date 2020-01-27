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

     //internal partial class AdvCameraSettingsPage : UserControl
     internal partial class AdvCameraSettingsPage : BasePage
    {        
        private const uint sk_imageDataFmtReg = 0x1048;
        private const uint sk_testPatternReg = 0x104C;
        private const uint sk_frameInfoReg = 0x12F8;

        private const uint sk_mirrorImageCtrlReg = 0x1054;  // IIDC v1.32 
        private const uint sk_bayerMonoCtrlReg = 0x1050;    // IIDC v1.32 
        private const uint sk_dataDepthCtrlReg = 0x0630;    // IIDC v1.32 

        private CheckBox[] m_embeddedImageInfoCheckBoxes;
        private Dictionary<int, string> m_embeddedImageInfoDictionary;

        private bool m_initializing;

        private Timer m_updateTimer = new Timer();

        public event EventHandler MemoryChannelRestored;
        public event EventHandler ISOSpeedChanged;

        public AdvCameraSettingsPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitializePage();
        }

        private enum EmbeddedInfoType
        {
            EmbeddedTimestamp = 0,
            EmbeddedGain,
            EmbeddedShutter,
            EmbeddedBrightness,
            EmbeddedExposure,
            EmbeddedWhiteBalance,
            EmbeddedFrameCounter,
            EmbeddedStrobePattern,
            EmbeddedGpioPinState,
            EmbeddedRoiPosition,
            EmbeddedNumInformation, // Number of information entries
        }

        private void OnTimer(object o, EventArgs eventArgs)
        {
            if (m_camera == null)
            {
                return;
            }

            if (m_isPageSelected)
            {
                UpdateImageDataFormat();
                UpdateTestPattern();
                UpdateEmbeddedInfo();
                UpdateIsoComboBox();
                UpdatePacketResend();
            }
        }

        private void InitializePage()
        {
            m_initializing = true;

            if (m_camera == null)
            {
                // Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            InitializeEmbeddedImageInforationPanel();
            InitializeAutoRangeControl();
            InitializeBusSpeedControlPanel(m_camInfo);
            UpdateMemoryChannels();
            UpdatePacketResend();

            m_updateTimer.Tick += new EventHandler(OnTimer);
            m_updateTimer.Interval = 100;
            m_updateTimer.Start();

            m_initializing = false;
        }

        private void OnMemoryChannelRestored(EventArgs e)
        {
             if (MemoryChannelRestored != null)
             {
                 MemoryChannelRestored(this, e);
             }
        }

        private void OnISOSpeedChanged(EventArgs e)
        {
            if (ISOSpeedChanged != null)
            {
                ISOSpeedChanged(this, e);
            }
        }

        private void InitializeEmbeddedImageInforationPanel()
        {
            InitializeEmbeddedImageInfoDictionary();
            m_embeddedImageInfoCheckBoxes = new CheckBox[(int)EmbeddedInfoType.EmbeddedNumInformation];
            const int k_buttonMatrixColumnWidth = 110;
            int buttonLocationX = 0;
            int buttonLocationY = 0;
            
            for (int i = 0; i < m_embeddedImageInfoCheckBoxes.Length; i++)
            {
                m_embeddedImageInfoCheckBoxes[i] = new CheckBox();
                string checkBoxText;
                if (m_embeddedImageInfoDictionary.TryGetValue(i, out checkBoxText) == true)
                {
                    m_embeddedImageInfoCheckBoxes[i].Text = checkBoxText;
                    if (Environment.OSVersion.Version.Major >= 6) // Vista and 7
                    {
                        float dpiX, dpiY;
                        Graphics graphics = this.CreateGraphics();
                        dpiX = graphics.DpiX;
                        dpiY = graphics.DpiY;
                        if (dpiX == 120 || dpiY == 120) // Medium Text Size 125%
                        {
                            m_embeddedImageInfoCheckBoxes[i].Font = new Font(m_embeddedImageInfoCheckBoxes[i].Font.FontFamily, m_embeddedImageInfoCheckBoxes[i].Font.Size - 1);
                        }
                        else if (dpiX == 144 || dpiY == 144) // Large Text Size 150%
                        {
                            m_embeddedImageInfoCheckBoxes[i].Font = new Font(m_embeddedImageInfoCheckBoxes[i].Font.FontFamily, m_embeddedImageInfoCheckBoxes[i].Font.Size - 2);
                        }
                        else
                        {
                            // Do nothing for normal size
                        }
                    }
                }
                else
                {
                    Debug.WriteLine("Bug: Invalid embedded image information, please define it at InitializeEmbeddedImageInfoDictionary().\n");
                    m_embeddedImageInfoCheckBoxes[i].Text = "Undefined embedded image information";
                    continue;
                }

                m_embeddedImageInfoCheckBoxes[i].Tag = i;
                m_embeddedImageInfoCheckBoxes[i].TabIndex = i;
                m_embeddedImageInfoCheckBoxes[i].TabStop = true;

                // check to see if there is enough space to put this control in the panel
                if (buttonLocationY + m_embeddedImageInfoCheckBoxes[i].Height > m_embeddedImageInfoSelectionPanel.Height)
                {
                    buttonLocationY = 0;
                    buttonLocationX += k_buttonMatrixColumnWidth;
                }

                m_embeddedImageInfoCheckBoxes[i].Location = new Point(buttonLocationX, buttonLocationY);
                buttonLocationY += m_embeddedImageInfoCheckBoxes[i].Height;
                m_embeddedImageInfoCheckBoxes[i].CheckStateChanged += new EventHandler(EmbeddedImageInformationCheckStateChanged);
                
                // Add this control in the panel
                m_embeddedImageInfoSelectionPanel.Controls.Add(m_embeddedImageInfoCheckBoxes[i]);
            }
        }

        private void InitializeEmbeddedImageInfoDictionary()
        {
            // define the enbedded information to readable words
            m_embeddedImageInfoDictionary = new Dictionary<int, string>();
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedTimestamp, "Timestamp");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedGain, "Gain");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedShutter, "Shutter");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedBrightness, "Brightness");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedExposure, "Exposure");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedWhiteBalance, "White balance");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedFrameCounter, "Frame counter");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedStrobePattern, "Strobe pattern");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedGpioPinState, "GPIO pin state");
            m_embeddedImageInfoDictionary.Add((int)EmbeddedInfoType.EmbeddedRoiPosition, "ROI position");
        }

        private void InitializeAutoRangeControl()
        {
            if (m_autoRangePropertyComboBox.Items.Count > 0)
            {
                m_autoRangePropertyComboBox.SelectedIndex = 0;
            }
        }

        private void UpdateMemoryChannels()
        {
            UpdateMemChannelComboBox();
            uint currMemChannel = 0;
            try
            {
                currMemChannel = m_camera.GetMemoryChannel();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting current memory channel", ex);
                ex.Dispose();
            }

            SetActiveMemChannelComboBox(currMemChannel);
        }

        private void SetActiveMemChannelComboBox(uint channel)
        {
            if (m_memoryChannelsComboBox.Items.Count == 0)
            {
                return;
            }

            int selectedIndex = m_memoryChannelsComboBox.Items.IndexOf(channel.ToString());
            if (selectedIndex == -1)
            {
                m_memoryChannelsComboBox.SelectedIndex = 0; // 0 is defualt 
            }
            else
            {
                m_memoryChannelsComboBox.SelectedIndex = selectedIndex;
            }
        }

        private void UpdateMemChannelComboBox()
        {
            m_memoryChannelsComboBox.Items.Clear();
            uint numMemChannels;
            try
            {
                numMemChannels = m_camera.GetMemoryChannelInfo();
            }
            catch (FC2Exception ex)
            {
                m_memoryChannelControlPanel.Enabled = false;
                ex.Dispose();
                return;
            }

            if (numMemChannels == 0)
            {
                m_memoryChannelControlPanel.Enabled = false;
                return;
            }
            else
            {
                m_memoryChannelControlPanel.Enabled = true;
            }

            // Iterate to numMemChannels+1, since 0th channel is default
            for (uint i = 0; i < numMemChannels + 1; i++)
            {
                if (i == 0)
                {
                    m_memoryChannelsComboBox.Items.Insert(0, "Default"); // set default at index 0
                    m_memoryChannelsComboBox.SelectedIndex = 0;
                }
                else
                {
                    m_memoryChannelsComboBox.Items.Add(i.ToString());
                }
            }
        }

        private void UpdateImageDataFormat()
        {
            // Read image data format register
            uint dataDepthVal = 0, rawBayerOutputVal = 0, mirrorImageVal = 0;
            uint imageDataFmtVal = 0;
            if (m_camInfo.iidcVersion >= iidcVersion)
            {
                try
                {
                    dataDepthVal = m_camera.ReadRegister(sk_dataDepthCtrlReg);
                }
                catch (FC2Exception ex)
                {
                    //ShowErrorMessageDialog("Error reading data depth register", ex);
                    Debug.WriteLine("Error reading data depth register:" + ex.Message);
                    ex.Dispose();
                    return;
                }

                try
                {
                    mirrorImageVal = m_camera.ReadRegister(sk_mirrorImageCtrlReg);
                }
                catch (FC2Exception ex)
                {
                    //ShowErrorMessageDialog("Error reading mirror image control register", ex);
                    Debug.WriteLine("Error reading mirror image control register:" + ex.Message);
                    ex.Dispose();
                    return;
                }

                try
                {
                    rawBayerOutputVal = m_camera.ReadRegister(sk_bayerMonoCtrlReg);
                }
                catch (FC2Exception ex)
                {
                    //ShowErrorMessageDialog("Error reading bayer mono control register", ex);
                    Debug.WriteLine("Error reading bayer mono control register:" + ex.Message);
                    ex.Dispose();
                    return;
                }

                m_rawBayerOutputCheckBox.Enabled = (rawBayerOutputVal & 0x80000000) != 0;
                m_mirrorImageCheckBox.Enabled = (mirrorImageVal & 0x80000000) != 0;
                m_y16EndiannessSelectionPanel.Enabled = true;
                m_rawBayerOutputCheckBox.Checked = (rawBayerOutputVal & 0x1) != 0;
                m_mirrorImageCheckBox.Checked = (mirrorImageVal & 0x1) != 0;
                if ((dataDepthVal & 0x00800000) == 0)
                {
                    m_y16BigEndianRadioButton.Checked = true;
                }
                else
                {
                    m_y16LittleEndianRadioButton.Checked = true;
                }
            }
            else
            {
                try
                {
                    imageDataFmtVal = m_camera.ReadRegister(sk_imageDataFmtReg);
                }
                catch (FC2Exception ex)
                {
                    //ShowErrorMessageDialog("Error reading image data format register", ex);
                    Debug.WriteLine("Error reading image data format register:" + ex.Message);
                    ex.Dispose();
                    return;
                }

                m_rawBayerOutputCheckBox.Enabled = (imageDataFmtVal >> 31) != 0;
                m_mirrorImageCheckBox.Enabled = (imageDataFmtVal >> 31) != 0;
                m_y16EndiannessSelectionPanel.Enabled = (imageDataFmtVal >> 31) != 0;
                m_rawBayerOutputCheckBox.Checked = (imageDataFmtVal & (0x1 << 7)) != 0;
                m_mirrorImageCheckBox.Checked = (imageDataFmtVal & (0x1 << 8)) != 0;
                if ((imageDataFmtVal & (0x1 << 0)) != 0)
                {
                    m_y16BigEndianRadioButton.Checked = true;
                }
                else
                {
                    m_y16LittleEndianRadioButton.Checked = true;
                }
            }
        }

        private void UpdateTestPattern()
        {
            uint testPatternVal = 0;
            try
            {
                testPatternVal = m_camera.ReadRegister(sk_testPatternReg);
            }
            catch (FC2Exception ex)
            {
                //ShowErrorMessageDialog("Error reading test pattern register", ex);
                Debug.WriteLine("Error reading test pattern register" + ex.Message);
                ex.Dispose();
                return;
            }

            if (testPatternVal >> 31 != 0)
            {
                m_testPatternSelectionPanel.Enabled = true;
            }
            else
            {
                m_testPatternSelectionPanel.Enabled = false;
            }

            // Update test pattern
            bool testPattern1 = (testPatternVal & (0x1 << 0)) != 0;
            bool testPattern2 = (testPatternVal & (0x1 << 1)) != 0;

            if (testPattern1 && !testPattern2)
            {
                m_testPattern1RadioButton.Checked = true;
            }
            else if (!testPattern1 && testPattern2)
            {
                m_testPattern2RadioButton.Checked = true;
            }
            else if (!testPattern1 && !testPattern2)
            {
                m_testPatternNoneRadioButton.Checked = true;
            }
            else
            {
                // Should never get here
                Debug.WriteLine("Bug: Unknown test pattern.");
            }
        }

        private void UpdateEmbeddedInfo()
        {
            uint frameInfoRegVal = 0;
            try
            {
                frameInfoRegVal = m_camera.ReadRegister(sk_frameInfoReg);
            }
            catch (FC2Exception ex)
            {
                m_embeddedImageInfoSelectionPanel.Enabled = false;
                ex.Dispose();
                return;
            }

            if ((frameInfoRegVal >> 31) == 0)
            {
                m_embeddedImageInfoSelectionPanel.Enabled = false;
            }
            else
            {
                // TODO: Maybe figure out what is supported, since some cameras
                // don't support specific functions
                m_embeddedImageInfoSelectionPanel.Enabled = true;
            }

            for (int i = 0; i < m_embeddedImageInfoCheckBoxes.Length; i++)
            {
                bool isCurrentInfoEnabled = (frameInfoRegVal >> i & 0x1) != 0;
                m_embeddedImageInfoCheckBoxes[i].Checked = isCurrentInfoEnabled;
            }
        }

        private void OnMirrorImageCheckedStatusChanged(object sender, EventArgs e)
        {
            uint value = 0;
            uint mirrorCtrlRegister = sk_imageDataFmtReg;
            uint mirrorMask = 0x1 << 8;
            if (m_camInfo.iidcVersion >= iidcVersion)
            {
                mirrorCtrlRegister = sk_mirrorImageCtrlReg;
                mirrorMask = 0x1;
            }

            try
            {
                value = m_camera.ReadRegister(mirrorCtrlRegister);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading image data format register", ex);
                ex.Dispose();
            }

            if (m_mirrorImageCheckBox.Checked == true)
            {
                value |= mirrorMask;
            }
            else
            {
                value &= ~mirrorMask;
            }

            try
            {
                m_camera.WriteRegister(mirrorCtrlRegister, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing image data format register", ex);
                ex.Dispose();
            }
        }

        private void OnSelectAllEmbeddedImageInfoButtonClick(object sender, EventArgs e)
        {
            for (int i = 0; i < m_embeddedImageInfoCheckBoxes.Length; i++)
            {
                m_embeddedImageInfoCheckBoxes[i].Checked = true;
            }
        }

        private void OnUnselectAllEmbeddedImageInfoButtonClick(object sender, EventArgs e)
        {
            for (int i = 0; i < m_embeddedImageInfoCheckBoxes.Length; i++)
            {
                m_embeddedImageInfoCheckBoxes[i].Checked = false;
            }
        }

        private void EmbeddedImageInformationCheckStateChanged(object sender, EventArgs e)
        {
            EmbeddedImageInfo embeddedInfo;
            try
            {
                embeddedInfo = m_camera.GetEmbeddedImageInfo();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading embedded image info", ex);
                ex.Dispose();
                return;
            }

            CheckBox currentCheckBox = (CheckBox)sender;
            int embeddedInfoType = (int)currentCheckBox.Tag;
            bool checkState = currentCheckBox.Checked;
            switch (embeddedInfoType)
            {
                case (int)EmbeddedInfoType.EmbeddedTimestamp: 
                    embeddedInfo.timestamp.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedGain: 
                    embeddedInfo.gain.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedShutter: 
                    embeddedInfo.shutter.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedBrightness: 
                    embeddedInfo.brightness.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedExposure: 
                    embeddedInfo.exposure.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedWhiteBalance: 
                    embeddedInfo.whiteBalance.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedFrameCounter: 
                    embeddedInfo.frameCounter.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedStrobePattern: 
                    embeddedInfo.strobePattern.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedGpioPinState: 
                    embeddedInfo.GPIOPinState.onOff = checkState; 
                    break;
                case (int)EmbeddedInfoType.EmbeddedRoiPosition: 
                    embeddedInfo.ROIPosition.onOff = checkState; 
                    break;
                default:
                    break;
            }

            try
            {
                m_camera.SetEmbeddedImageInfo(embeddedInfo);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing embedded image info", ex);
                ex.Dispose();
                return;
            }
        }

        private void OnMemoryChannelsSaveButtonClick(object sender, EventArgs e)
        {
            int currentIndex = m_memoryChannelsComboBox.SelectedIndex;
            if (currentIndex < 0)
            {
                // it means nothing is selected
                return;
            }

            uint memChannel = (uint)currentIndex;
            if (memChannel == 0)
            {
                DialogResult result = MessageBox.Show(
                                        "Saving to the default memory channel will cause the camera to load its factory default settings after power cycle.\r\n" +
                                        "Do you wish to proceed?",
                                        "Confirm restore to default settings", 
                                        MessageBoxButtons.OKCancel, 
                                        MessageBoxIcon.Question);
                if (result != DialogResult.OK)
                {
                    return;
                }
            }

            try
            {
                m_camera.SaveToMemoryChannel(memChannel);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error saving to memory channel", ex);
                ex.Dispose();
            }
        }

        private void OnMemoryChannelsRestoreButtonClick(object sender, EventArgs e)
        {
            bool wasStreaming = true;
            bool timeStampsWasEnabled = m_embeddedImageInfoCheckBoxes[0].Checked;
            try
            {
                m_camera.StopCapture();
            }
            catch (FC2Exception ex)
            {
                if (ex.Type == FlyCapture2Managed.ErrorType.IsochNotStarted)
                {
                    wasStreaming = false;
                    ex.Dispose();
                }
                else
                {
                    ShowErrorMessageDialog("Error stopping camera in preparation for restoring from memory channel", ex);
                    ex.Dispose();
                    return;
                }
            }

            int currentIndex = m_memoryChannelsComboBox.SelectedIndex;
            if (currentIndex < 0)
            {
                // it means nothing is selected
                return;
            }

            uint memChannel = (uint)currentIndex;
            try
            {
                m_camera.RestoreFromMemoryChannel(memChannel);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error restoring from memory channel", ex);
                ex.Dispose();
            }

            // Check to see if the camera was streaming (need to restart it after restoring
            // the memory channel).
            if (wasStreaming == true)
            {
                try
                {
                    m_camera.StartCapture();

                    //re-enable embedded timestamps for Received FPS calculation
                    if (timeStampsWasEnabled)
                    {
                        EmbeddedImageInfo embeddedInfo;
                        try
                        {
                            embeddedInfo = m_camera.GetEmbeddedImageInfo();
                            embeddedInfo.timestamp.onOff = true;
                            m_camera.SetEmbeddedImageInfo(embeddedInfo);
                        }
                        catch (FC2Exception ex)
                        {
                            Debug.WriteLine("Error re-enabling embedded timestamps after restoring from memeory channel.");
                            ex.Dispose();
                        }
                    }
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error restarting camera after restoring from memory channe", ex);
                    ex.Dispose();
                }
            }

            OnMemoryChannelRestored(EventArgs.Empty);
        }

        private void OnTestPatternRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (button.Checked == true)
            {
                try
                {
                    ChangeTestPattern(Convert.ToInt32(button.Tag.ToString()));
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine("Invalid argument to convert int 32.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
                catch (OverflowException ex)
                {
                    Debug.WriteLine("Unable to convert value. The value is overflow.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
                catch (FormatException ex)
                {
                    Debug.WriteLine("Invalid tag value in Test Pattern Radio Button.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
            }
        }

        private void ChangeTestPattern(int testPattern)
        {
            // 0 - No pattern
            // 1 - Test pattern 1
            // 2 - Test pattern 2
            uint value = 0;
            try
            {
                value = m_camera.ReadRegister(sk_testPatternReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading test pattern register", ex);
                ex.Dispose();
            }

            value &= 0x00;

            switch (testPattern)
            {
                case 0:
                    // Nothing to do here
                    break;

                case 1:
                    value |= 0x1 << 0;
                    break;

                case 2:
                    value |= 0x1 << 1;
                    break;

                default:
                    break;
            }

            try
            {
                m_camera.WriteRegister(sk_testPatternReg, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing test pattern register", ex);
                ex.Dispose();
            }
        }

        private void OnY16EndiannessRadioButtonCheckedChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (button.Checked == false)
            {
                // avoid call twice for both check and uncheck bottons
                return;
            }

            uint value = 0;
            uint endianCtrlRegister = sk_imageDataFmtReg;
            uint endianMask = 0x1;
            if (m_camInfo.iidcVersion >= iidcVersion)
            {
                endianCtrlRegister = sk_dataDepthCtrlReg;
                endianMask = 0x1 << 23;
            }

            try
            {
                value = m_camera.ReadRegister(endianCtrlRegister);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading image data format register", ex);
                ex.Dispose();
            }

            if (m_y16BigEndianRadioButton.Checked == true)
            {
                if (m_camInfo.iidcVersion >= iidcVersion)
                {
                    value &= ~endianMask;
                }
                else
                {
                    value |= endianMask;
                }
            }
            else if (m_y16LittleEndianRadioButton.Checked == true)
            {
                if (m_camInfo.iidcVersion >= iidcVersion)
                {
                    value |= endianMask;
                }
                else
                {
                    value &= ~endianMask;
                }
            }
            else
            {
                // should never goes here
                Debug.WriteLine("Bug: Unknown Y16 Endianness status.");
                return;
            }

            try
            {
                m_camera.WriteRegister(endianCtrlRegister, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing image data format register", ex);
                ex.Dispose();
            }
        }

        private void RawBayerOutputCheckedStatusChanged(object sender, EventArgs e)
        {
            uint value = 0;
            uint rawBayerCtrlRegister = sk_imageDataFmtReg;
            uint rawBayerMask = 0x1 << 7;
            if (m_camInfo.iidcVersion >= iidcVersion)
            {
                rawBayerCtrlRegister = sk_bayerMonoCtrlReg;
                rawBayerMask = 0x1;
            }

            try
            {
                value = m_camera.ReadRegister(rawBayerCtrlRegister);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading image data format register", ex);
                ex.Dispose();
                return;
            }

            if (m_rawBayerOutputCheckBox.Checked == true)
            {
                value |= rawBayerMask;
            }
            else
            {
                value &= ~rawBayerMask;
            }

            try
            {
                m_camera.WriteRegister(rawBayerCtrlRegister, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing image data format register", ex);
                ex.Dispose();
            }

            bool needToRestartCamera = true;

            try
            {
                m_camera.StopCapture();
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
                ex.Dispose();
            }
            
            if (needToRestartCamera == true)
            {
                try
                {
                    m_camera.StartCapture();
                }
                catch (FC2Exception ex)
                {
                    string error = string.Format("Error restarting image streaming. {0}", ex.Message);
                    Console.WriteLine(error);
                    MessageBox.Show(error, "FlyCapture2 Camera Control", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    ex.Dispose();
                }
            }
        }

        private void OnAutoRangePropertySelectedIndexChanged(object sender, EventArgs e)
        {
            GetCurrentPropertyAutoRange();
        }

        private void GetCurrentPropertyAutoRange()
        {
            uint propRegVal = 0;
            uint propRegister = 0;
            try
            {
                propRegister = GetCurrentSelectAutoRangePropertyRegister();
            }
            catch (ArgumentException ex)
            {
                m_autoRangeMinTextBox.Text = "Error";
                m_autoRangeMaxTextBox.Text = "Error";
                SetRangeValueEnabled(false);
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                return;
            }

            try
            {
                propRegVal = m_camera.ReadRegister(propRegister);
            }
            catch (FC2Exception ex)
            {
                ex.Dispose();
                return;
            }

            if (propRegVal >> 31 != 0)
            {
                uint minVal = (propRegVal & 0x00FFF000) >> 12;
                uint maxVal = propRegVal & 0x00000FFF;
                m_autoRangeMinTextBox.Text = minVal.ToString();
                m_autoRangeMaxTextBox.Text = maxVal.ToString();
                SetRangeValueEnabled(true);
            }
            else
            {
                m_autoRangeMinTextBox.Text = "N/A";
                m_autoRangeMaxTextBox.Text = "N/A";
                SetRangeValueEnabled(false);
            }
        }

        private void SetRangeValueEnabled(bool isEnabled)
        {
            m_autoRangeMinTextBox.Enabled = isEnabled;
            m_autoRangeMaxTextBox.Enabled = isEnabled;
            m_getAutoRangeValueButton.Enabled = isEnabled;
            m_setAutoRangeValueButton.Enabled = isEnabled;
        }

        private uint GetCurrentSelectAutoRangePropertyRegister()
        {
            uint propRegister = 0;
            switch (m_autoRangePropertyComboBox.SelectedItem.ToString())
            {
                case "Exposure":
                    propRegister = 0x1088;
                    break;
                case "Shutter":
                    propRegister = 0x1098;
                    break;
                case "Gain":
                    propRegister = 0x10A0;
                    break;
                default:
                    Debug.WriteLine("Bug: Unknown property tpye.");
                    throw new ArgumentException("Unknown property tpye. Get property register failed.");
            }

            return propRegister;
        }

        private void OnSetAutoRangeValueButtonClick(object sender, EventArgs e)
        {
            uint propRegVal = 0;
            uint propRegister = 0;
            try
            {
                propRegister = GetCurrentSelectAutoRangePropertyRegister();
            }
            catch (ArgumentException ex)
            {
                m_autoRangeMinTextBox.Text = "Error";
                m_autoRangeMaxTextBox.Text = "Error";
                SetRangeValueEnabled(false);
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                return;
            }

            uint minVal, maxVal;

            try
            {
                maxVal = Convert.ToUInt32(m_autoRangeMaxTextBox.Text);
                minVal = Convert.ToUInt32(m_autoRangeMinTextBox.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Invalid auto range value", "Unable to set auto range value", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            propRegVal += minVal << 12;
            propRegVal += maxVal;

            try
            {
                m_camera.WriteRegister(propRegister, propRegVal);
            }
            catch (FC2Exception ex)
            {
                ex.Dispose();
                return;
            }
        }

        /*private bool IsGEV()
        {
            return (m_camera.GetType() == (new ManagedGigECamera()).GetType());
        }*/

        private void OnPacketResendLoadButtonClicked(object sender, EventArgs e)
        {
            OnPacketResendLoad();
        }

         private void OnPacketResendLoad()
         {
             // TODO: check GigE part
             if (!IsGEV())
             {
                 return;
             }

             GigEConfig currConfig;
             ManagedGigECamera camera = (ManagedGigECamera)m_camera;

             try
             {
                 currConfig = camera.GetGigEConfig();
             }
             catch (FC2Exception ex)
             {
                 // TODO: Print error
                 Debug.WriteLine(ex.Message);
                ex.Dispose();
                return;
             }

             m_enableGigEPacketResendCheckBox.Checked = currConfig.enablePacketResend;
         }

         private void m_enableGigEPacketResendCheckBox_CheckedChanged(object sender, EventArgs e)
         {
             // TODO: check GigE part
             if (!IsGEV())
             {
                 return;
             }

             GigEConfig currConfig;
             ManagedGigECamera camera = (ManagedGigECamera)m_camera;

             try
             {
                 currConfig = camera.GetGigEConfig();
             }
             catch (FC2Exception ex)
             {
                 // TODO: Print error
                 Debug.WriteLine(ex.Message);
                ex.Dispose();
                return;
             }

             currConfig.enablePacketResend = m_enableGigEPacketResendCheckBox.Checked;

             try
             {
                 camera.SetGigEConfig(currConfig);
             }
             catch (FC2Exception ex)
             {
                 // TODO: Print error
                 Debug.WriteLine(ex.Message);
                ex.Dispose();
                return;
             }
         }

        private void OnPacketResendSaveButtonClicked(object sender, EventArgs e)
        {
            return;
            ////// TODO: check GigE part
            ////if (!IsGEV())
            ////{
            ////    return;
            ////}

            ////GigEConfig currConfig;
            ////ManagedGigECamera camera = (ManagedGigECamera)m_camera;

            ////try
            ////{
            ////    currConfig = camera.GetGigEConfig();
            ////}
            ////catch (FC2Exception ex)
            ////{
            ////    // TODO: Print error
            ////    Debug.WriteLine(ex.Message);
            ////    return;
            ////}

            ////currConfig.enablePacketResend = m_enableGigEPacketResendCheckBox.Checked;

            ////try
            ////{
            ////    camera.SetGigEConfig(currConfig);
            ////}
            ////catch (FC2Exception ex)
            ////{
            ////    // TODO: Print error
            ////    Debug.WriteLine(ex.Message);
            ////    return;
            ////}
        }

        private void UpdatePacketResend()
        {
            // TODO: check GigE part
            if (IsGEV() && IsPacketResendSupported())
            {
                m_gigEPacketResendControlPanel.Visible = true;

                if (IsCameraStreaming())
                {
                    m_gigEPacketResendControlPanel.Enabled = false;
                    m_pktResendEnableLabel.Visible = true;
                }
                else
                {
                    m_gigEPacketResendControlPanel.Enabled = true;
                    m_pktResendEnableLabel.Visible = false;
                }
                OnPacketResendLoad();
            }
            else
            {
                m_gigEPacketResendControlPanel.Visible = false;
            }
        }

        private void OnGetAutoRangeValueButtonClick(object sender, EventArgs e)
        {
            GetCurrentPropertyAutoRange();
        }

        private void InitializeBusSpeedControlPanel(CameraInfo cameraInfo)
        {
            m_AsyncSpeedCombo.Items.Clear();
            m_IsochSpeedCombo.Items.Clear();
            m_IsochHelperLabel.Visible = false; // Hide "Camera is streaming label by default

            if (cameraInfo.interfaceType == InterfaceType.Ieee1394 )
            {
                if (cameraInfo.maximumBusSpeed == BusSpeed.S1600)
                {
                    m_AsyncSpeedCombo.Items.Add("S1600");
                    m_IsochSpeedCombo.Items.Add("S1600");

                    m_AsyncSpeedCombo.Items.Add("S800");
                    m_IsochSpeedCombo.Items.Add("S800");

                    m_AsyncSpeedCombo.Items.Add("S400");
                    m_IsochSpeedCombo.Items.Add("S400");

                    m_AsyncSpeedCombo.Items.Add("S200");
                    m_IsochSpeedCombo.Items.Add("S200");

                    m_AsyncSpeedCombo.Items.Add("S100");
                    m_IsochSpeedCombo.Items.Add("S100");
                }

                if (cameraInfo.maximumBusSpeed == BusSpeed.S800)
                {
                    m_AsyncSpeedCombo.Items.Add("S800");
                    m_IsochSpeedCombo.Items.Add("S800");

                    m_AsyncSpeedCombo.Items.Add("S400");
                    m_IsochSpeedCombo.Items.Add("S400");

                    m_AsyncSpeedCombo.Items.Add("S200");
                    m_IsochSpeedCombo.Items.Add("S200");

                    m_AsyncSpeedCombo.Items.Add("S100");
                    m_IsochSpeedCombo.Items.Add("S100");
                }

                if (cameraInfo.maximumBusSpeed == BusSpeed.S400)
                {
                    m_AsyncSpeedCombo.Items.Add("S400");
                    m_IsochSpeedCombo.Items.Add("S400");

                    m_AsyncSpeedCombo.Items.Add("S200");
                    m_IsochSpeedCombo.Items.Add("S200");

                    m_AsyncSpeedCombo.Items.Add("S100");
                    m_IsochSpeedCombo.Items.Add("S100");
                }

                if (cameraInfo.maximumBusSpeed == BusSpeed.S200)
                {
                    m_AsyncSpeedCombo.Items.Add("S200");
                    m_IsochSpeedCombo.Items.Add("S200");

                    m_AsyncSpeedCombo.Items.Add("S100");
                    m_IsochSpeedCombo.Items.Add("S100");
                }

                if (cameraInfo.maximumBusSpeed == BusSpeed.S100)
                {
                    m_AsyncSpeedCombo.Items.Add("S100");
                    m_IsochSpeedCombo.Items.Add("S100");
                }

                if (m_camera != null)
                {
                    if (m_camera.ReadRegister(0x614) != 0) //Camera is streaming
                    {
                        m_IsochSpeedCombo.Enabled = false;
                        m_IsochHelperLabel.Visible = true;
                    }
                }
            }
            if (cameraInfo.interfaceType == InterfaceType.Usb2)
            {
                m_AsyncSpeedCombo.Items.Add("S480");
                m_IsochSpeedCombo.Items.Add("S480");
            }
            if (cameraInfo.interfaceType == InterfaceType.Usb3)
            {
                m_AsyncSpeedCombo.Items.Add("S3200");
                m_IsochSpeedCombo.Items.Add("S3200");
            }
            if (cameraInfo.interfaceType == InterfaceType.GigE)
            {
                m_AsyncSpeedCombo.Items.Add("GigE_1000Base_T");
                m_IsochSpeedCombo.Items.Add("GigE_1000Base_T");
                m_speedControlPanel.Hide(); // Hide all speed controls for GigE
            }

            // Set default selection to Max
            if (m_AsyncSpeedCombo.Items.Count > 0 && m_IsochSpeedCombo.Items.Count > 0)
            {
                m_AsyncSpeedCombo.SelectedIndex = 0;
                m_IsochSpeedCombo.SelectedIndex = 0;
            }
            else
            {
                // Hide panel in case any of the comboboxes were empty
                m_speedControlPanel.Hide();
            }

            // Hide all speed controls for ZEBRA1 camera
            if (cameraInfo.interfaceType == InterfaceType.Ieee1394 && cameraInfo.modelName.ToLower().Contains("zebra"))
            {
                m_speedControlPanel.Hide();
            }
        }

        private void UpdateIsoComboBox()
        {
            try
            {
                if (m_speedControlPanel.Visible && m_camInfo.interfaceType != InterfaceType.GigE && !((m_camInfo.interfaceType == InterfaceType.Ieee1394 && m_camInfo.modelName.ToLower().Contains("zebra")))) // Only update controls if its a Firewire or USB camera
                {
                    if (m_camera.IsConnected() && (m_camera.ReadRegister(0x614) == 0))
                    {
                        m_IsochSpeedCombo.Enabled = true;
                        m_IsochHelperLabel.Visible = false;
                    }
                    else
                    {
                        m_IsochSpeedCombo.Enabled = false;
                        m_IsochHelperLabel.Visible = true;
                    }
                }
            }
            catch (System.Exception ex)
            {
            	Debug.WriteLine("Problem updating iso combobox.");
            }
            
        }

        private void m_AsyncSpeedCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!m_initializing && m_speedControlPanel.Visible)
            {
                try
                {
                    if (m_camera.IsConnected() && m_camInfo.interfaceType == InterfaceType.Ieee1394 && m_AsyncSpeedCombo.Items.Count > 0) //Async speed can only be changed for Firewire
                    {
                        BusSpeed asyncSpeed = (BusSpeed)Enum.Parse(typeof(BusSpeed), m_AsyncSpeedCombo.SelectedItem.ToString(), true);
                        FC2Config config = new FC2Config();
                        config = m_camera.GetConfiguration();
                        config.asyncBusSpeed = asyncSpeed;
                        m_camera.SetConfiguration(config);
                        OnISOSpeedChanged(EventArgs.Empty);
                        //config = m_camera.GetConfiguration(); Hal can not retrieve Async Speed at the moment
                    }
                }
                catch (Exception ex)
                {
                    string error = string.Format("Failed to set asynchronous bus speed: {0}", ex.Message);
                    Debug.WriteLine(error);
                    MessageBox.Show(error, "FlyCapture2", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
        }

        private void m_IsochSpeedCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!m_initializing && m_speedControlPanel.Visible)
            {
                try
                {
                    if (m_camera.IsConnected() && m_camInfo.interfaceType == InterfaceType.Ieee1394 && m_IsochSpeedCombo.Items.Count > 0) //Isoch speed can only be changed for Firewire
                    {
                        BusSpeed isochSpeed = (BusSpeed)Enum.Parse(typeof(BusSpeed), m_IsochSpeedCombo.SelectedItem.ToString(), true);
                        if (m_camera.ReadRegister(0x614) == 0) // Make sure camera is not streaming while changing Isoch speed
                        {
                            FC2Config config = new FC2Config();
                            config = m_camera.GetConfiguration();
                            config.isochBusSpeed = isochSpeed;
                            m_camera.SetConfiguration(config);
                            config = m_camera.GetConfiguration();
                            if (config.isochBusSpeed != (BusSpeed)Enum.Parse(typeof(BusSpeed), m_IsochSpeedCombo.SelectedItem.ToString()))
                            {
                                MessageBox.Show("Could not set new Isoch Speed.", "FlyCapture2", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                            else
                            {
                                OnISOSpeedChanged(EventArgs.Empty);
                            }
                        }
                    }

                }
                catch (Exception ex)
                {
                    string error = string.Format("Failed to set isochronous bus speed: {0}", ex.Message);
                    Debug.WriteLine(error);
                    MessageBox.Show(error, "FlyCapture2", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
        }
    }
}
