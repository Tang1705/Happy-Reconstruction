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
using System.Drawing.Drawing2D;
using System.Text;
using System.Windows.Forms;
using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /* If you can not open the design view of this class, try to modify base class
     * to "UserControl" instead of "BasePage". VS2005 probably has issue of opening 
     * design view for inherited user control. The reason is still investigating.
     * */

    //internal partial class Format7Page : UserControl
    internal partial class Format7Page : BasePage
    {
        private Rectangle m_captureArea;

        private bool m_isLeftButtonDragging = false;
        private bool m_isRightButtonDragging = false;

        private bool m_skippSpinBtnEvent = false;

        private int m_draggingStartX = 0;
        private int m_draggingStartY = 0;

        private int m_cursorX = 0;
        private int m_cursorY = 0;

        private int m_imageWidth = 640;
        private int m_imageHeight = 480;
        private uint m_imageSize = 0;

        private Dictionary<string, PixelFormat> m_pixelFormatDictionary = new Dictionary<string, PixelFormat>();
        private bool m_isLadybugGUI = false;
        private bool m_isTextInsufficientSpace = false;

        private Timer m_updateTimer = new Timer();

        private bool m_disableValidation = false;

        private bool m_initilizing = false;

        // Variable for estimating GigE bandwidth
        private uint m_linkSpeed;
        private uint m_tick_high;
        private uint m_tick_low;
        private long m_tick = 0;

        private bool m_bNeedReset = true;

        public Format7Page(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitializePage();
        }

        private void OnTimer(object o, EventArgs eventArgs)
        {
            if (m_isPageSelected)
            {
                UpdateModeComboBoxForLadybug();
            }
        }

        public void UpdateModeComboBoxForLadybug()
        {
            if (m_isLadybugGUI == true && IsCameraStreaming() == true)
            {
                ManagedCamera camera = (ManagedCamera)m_camera;
                m_modeComboBox.Enabled = false;
                m_pixelFormatComboBox.Enabled = false;
                Mode currentMode;
                if (IsCurrentlyInFormat7())
                {
                    Format7ImageSettings imageSettings = new Format7ImageSettings();
                    uint packetSize = 0;
                    float speed = 0;
                    try
                    {
                        camera.GetFormat7Configuration(imageSettings, ref packetSize, ref speed);
                    }
                    catch (FC2Exception ex)
                    {
                        ShowErrorMessageDialog("Unable to get Format7 Configuration.", ex);
                        ex.Dispose();
                    }

                    currentMode = imageSettings.mode;
                    SetActivePixelFormatComboBox(imageSettings.pixelFormat);
                }
                else
                {
                    currentMode = GetLowestMode();
                }

                if (currentMode == Mode.Mode0 || currentMode == Mode.Mode2)
                {
                    m_imageHeightSpinButton.Enabled = false;
                }
                else
                {
                    m_imageHeightSpinButton.Enabled = true;
                }

                m_modeComboBox.SelectedItem = (int)currentMode;
            }
            else
            {
                m_modeComboBox.Enabled = true;
                m_pixelFormatComboBox.Enabled = true;
            }
        }

        public void UpdateModeSettings()
        {
            if (m_camera == null || !m_isLadybugGUI)
            {
                // Do nothing if the camera is not for ladybugGUI
                return;
            }

            // Do nothing if the camera is not running
            if (IsCameraStreaming() == true)
            {
                // Camera is running
                ManagedCamera camera = (ManagedCamera)m_camera;
                Mode modeToPopulate;
                PixelFormat pixelFormatToPopulate;

                // Currently in Format 7, get the current settings
                Format7ImageSettings imageSettings = new Format7ImageSettings();
                uint packetSize = 0;
                float speed = 0;
                try
                {
                    camera.GetFormat7Configuration(imageSettings, ref packetSize, ref speed);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error getting current Format7 configuration", ex);
                    ex.Dispose();
                    return;
                }

                modeToPopulate = imageSettings.mode;
                pixelFormatToPopulate = imageSettings.pixelFormat;

                // Populate fields with camera settings for current mode
                SetActiveModeComboBox(modeToPopulate);

                // Do not allow changing mode and pixel format when LB camera is running
                m_modeComboBox.Enabled = false;
                m_pixelFormatComboBox.Enabled = false;
                if (modeToPopulate != Mode.Mode3 && modeToPopulate != Mode.Mode7)
                {
                    m_imageHeightSpinButton.Enabled = false;
                    m_captureAreaControl.Enabled = false;
                }
                else
                {
                    m_imageHeightSpinButton.Enabled = true;
                    m_captureAreaControl.Enabled = true;
                }
            }
        }

        private static string GetStringVerticalAndHorizontalInformation(bool isVerticalEnable, bool isHorizontalEnable)
        {
            if (isVerticalEnable && isHorizontalEnable)
            {
                return "Vertical + Horizontal";
            }
            else if (isVerticalEnable && !isHorizontalEnable)
            {
                return "Vertical only";
            }
            else if (!isVerticalEnable && isHorizontalEnable)
            {
                return "Horizontal only";
            }
            else
            {
                return "None";
            }
        }

        private static decimal ClampValue(decimal inputVal, decimal stepSize)
        {
            if (inputVal % stepSize != 0)
            {
                return inputVal - (inputVal % stepSize);
            }
            else
            {
                return inputVal;
            }
        }

        private void InitializePage()
        {
            if (m_camera == null)
            {
                //Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }
            m_initilizing = true;
            //TODO: need to check this function is working properly or not, for bug 12879
            m_isLadybugGUI = LadybugChecker.IsLadybugDLLPresent() && LadybugChecker.IsLadybug(m_camInfo);
            lbl_PacketDelayEnable.Visible = false;
            InitializePixelFormatDictionary();
            InitializeCameraInformation();
            InitializeCaptureAreaDrawingArea();
            AdjustCaptureAreaControlSize();
            InitializeGigEVariables();
            m_updateTimer.Tick += new EventHandler(OnTimer);
            m_updateTimer.Interval = 100;
            m_updateTimer.Start();
            UpdateImageSize();
            InitializeEvents();

            //if (m_isLadybugGUI)
            //{
            //    this.Enabled = false;
            //}

            m_initilizing = false;
        }

        private void ResetBandwidthString()
        {
            if (m_bNeedReset)
            {
                m_expectedBandwidthLabel.Text = string.Format("Estimated Bandwidth: -- MB/s");
                m_bNeedReset = false;
            }
        }

        private void InitializeGigEVariables()
        {
            if (m_camera == null)
            {
                m_linkSpeed = 0;
                m_tick = 0;
                return;
            }

            if (m_camera is ManagedGigECamera)
            {
                // Get link speed
                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                m_linkSpeed = camera.ReadGVCPRegister(0x0670) * 1000000 / 8;

                // Get Packet delay in seconds
                m_tick_high = camera.ReadGVCPRegister(0x093C);
                m_tick_low = camera.ReadGVCPRegister(0x0940);
                m_tick = (m_tick_high << 32) + m_tick_low;
            }
        }

        private void InitializeEvents()
        {
            m_gigEPacketDelayTrackBar.Scroll += new EventHandler(OnGigEPacketDelayTrackBarScroll);
            m_packetSizeTrackBar.ValueChanged += new EventHandler(OnPackSizeTrackBarScroll);
            m_packetSizeTrackBar.Scroll += new EventHandler(this.OnPackSizeTrackBarScroll);
            m_gigEPacketDelaySpinButton.ValueChanged += new EventHandler(OnGigEPacketDelaySpinButtonValueChanged);
            m_packetSizeSpinButton.ValueChanged += new EventHandler(OnPacketSizeSpinButtonValueChanged);
            m_binningHSpinBtn.ValueChanged += new EventHandler(OnBinningSpinBtnValueChanged);
            m_binningVSpinBtn.ValueChanged += new EventHandler(OnBinningSpinBtnValueChanged);
            m_imageLeftSpinButton.ValueChanged += new EventHandler(OnImageCaptureAreaSpinButtonValueChanged);
            m_imageLeftSpinButton.KeyUp += new KeyEventHandler(OnImageSpinButtonKeyRelaase);
            m_imageHeightSpinButton.ValueChanged += new EventHandler(OnImageCaptureAreaSpinButtonValueChanged);
            m_imageHeightSpinButton.KeyUp += new KeyEventHandler(OnImageSpinButtonKeyRelaase);
            m_imageTopSpinButton.ValueChanged += new EventHandler(OnImageCaptureAreaSpinButtonValueChanged);
            m_imageTopSpinButton.KeyUp += new KeyEventHandler(OnImageSpinButtonKeyRelaase);
            m_imageWidthSpinButton.ValueChanged += new EventHandler(OnImageCaptureAreaSpinButtonValueChanged);
            m_imageWidthSpinButton.KeyUp += new KeyEventHandler(OnImageSpinButtonKeyRelaase);
            m_modeComboBox.SelectedIndexChanged += new EventHandler(OnModeComboBoxSelectedIndexChanged);
            m_pixelFormatComboBox.SelectedIndexChanged += new EventHandler(OnPixelFormatComboBoxSelectedIndexChanged);
            m_captureAreaControl.MouseMove += new MouseEventHandler(OnCaptureAreaControlMouseMove);
            m_captureAreaControl.MouseDown += new MouseEventHandler(OnCaptureAreaControlMousePress);
            m_captureAreaControl.Paint += new PaintEventHandler(OnCaptureDrawingAreaPaint);
            m_captureAreaControl.MouseUp += new MouseEventHandler(OnCaptureAreaControlMouseRelease);
            m_captureAreaControl.MouseLeave += new EventHandler(OnCaptureAreaControMouseLeave);
            m_maxSizeBtn.Click += new EventHandler(OnMaxImageSizeClick);
            m_centerROIButton.Click += new EventHandler(OnCenterROIButtonClick);
            m_applyButton.Click += new EventHandler(OnApplyButtonClick);
        }

        private void InitializeCaptureAreaDrawingArea()
        {
            m_captureArea = new Rectangle(
                            Convert.ToInt32(m_imageLeftSpinButton.Value),
                            Convert.ToInt32(m_imageTopSpinButton.Value),
                            Convert.ToInt32(m_imageWidthSpinButton.Value),
                            Convert.ToInt32(m_imageHeightSpinButton.Value));
        }

        private void InitializePixelFormatDictionary()
        {
            m_pixelFormatDictionary.Clear();
            m_pixelFormatDictionary.Add("Mono 8", PixelFormat.PixelFormatMono8);
            m_pixelFormatDictionary.Add("Mono 12", PixelFormat.PixelFormatMono12);
            m_pixelFormatDictionary.Add("Mono 16", PixelFormat.PixelFormatMono16);
            m_pixelFormatDictionary.Add("Raw 8", PixelFormat.PixelFormatRaw8);
            m_pixelFormatDictionary.Add("Raw 12", PixelFormat.PixelFormatRaw12);
            m_pixelFormatDictionary.Add("Raw 16", PixelFormat.PixelFormatRaw16);
            m_pixelFormatDictionary.Add("YUV 411", PixelFormat.PixelFormat411Yuv8);
            m_pixelFormatDictionary.Add("YUV 422", PixelFormat.PixelFormat422Yuv8);
            m_pixelFormatDictionary.Add("YUV 444", PixelFormat.PixelFormat444Yuv8);
            m_pixelFormatDictionary.Add("RGB 8", PixelFormat.PixelFormatRgb8);
            m_pixelFormatDictionary.Add("RGB 16", PixelFormat.PixelFormatRgb16);
            m_pixelFormatDictionary.Add("Signed Mono 16", PixelFormat.PixelFormatSignedMono16);
            m_pixelFormatDictionary.Add("Signed RGB 16", PixelFormat.PixelFormatSignedRgb16);
            m_pixelFormatDictionary.Add("YUV 422 (JPEG)", PixelFormat.PixelFormat422Yuv8Jpeg);
        }

        public void InitializeCameraInformation()
        {
            CameraInfo cameraInfo;

            try
            {
                cameraInfo = m_camera.GetCameraInfo();
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Unable to get Camera Info. {0}", ex.Message);
                DisableWidgets();
                ex.Dispose();
                return;
            }
            
            if (cameraInfo.interfaceType == InterfaceType.GigE)
            {
                //SetPacketSizeVisible(true);
                m_PacketSizeLabel.Text = "Packet Size";
                SetGigEPacketDelayEnabled(true);

                // Make sure binning is enabled
                m_binningControlPanel.Enabled = true;            
            }
            else
            {
                //SetPacketSizeVisible(true);
                m_PacketSizeLabel.Text = "Packet Size";
                SetGigEPacketDelayEnabled(false);

                // Make sure binning is disabled
                m_binningControlPanel.Enabled = false;
            }

            AdjustCaptureAreaControlSize();
            if (IsIIDC())
            {
                ManagedCamera camera = (ManagedCamera)m_camera;
                Mode modeToPopulate;
                PixelFormat currentPixelFormat;

                const uint Fmt7InqReg = 0x19C;
                uint fmt7InqRegVal = 0;
                try
                {
                    fmt7InqRegVal = camera.ReadRegister(Fmt7InqReg);
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine("Unable to read register value. {0}", ex.Message);
                    DisableWidgets();
                    ex.Dispose();
                    return;
                }

                if (fmt7InqRegVal == 0)
                {
                    DisableWidgets();
                    return;
                }

                if (IsCurrentlyInFormat7())
                {
                    // Currently in Format 7, get the current config and use it
                    // to populate the combo boxes
                    Format7ImageSettings imageSettings = new Format7ImageSettings();
                    uint packetSize = 0;
                    float speed = 0;
                    try
                    {
                        camera.GetFormat7Configuration(imageSettings, ref packetSize, ref speed);
                    }
                    catch (FC2Exception ex)
                    {
                        ShowErrorMessageDialog("Unable to get Format7 Configuration. Initialize camera information failed.", ex);
                        ex.Dispose();
                    }

                    modeToPopulate = imageSettings.mode;
                    currentPixelFormat = imageSettings.pixelFormat;
                }
                else
                {
                    // Populate using the lowest mode (usually 0)
                    modeToPopulate = GetLowestMode();
                    currentPixelFormat = GetLowestPixelFormat(modeToPopulate);
                }

                PopulateModeComboBox(camera, modeToPopulate);
                SetActiveModeComboBox(modeToPopulate);
                OnIIDCModeChanged(modeToPopulate);
            }
            else if (IsGEV())
            {
                Debug.Assert(m_camera is ManagedGigECamera, "The interface type must be GigE.");

                // Update the packet size
                UpdateGigEPacketInfo();

                // Update the packet delay value
                UpdateGigEPacketDelay();                

                ManagedGigECamera camera = (ManagedGigECamera)m_camera;

                GigEImageSettings imageSettings;
                GigEImageSettingsInfo imageSettingsInfo;
                Mode currMode = Mode.NumberOfModes;
                try
                {
                    imageSettings = camera.GetGigEImageSettings();
                    imageSettingsInfo = camera.GetGigEImageSettingsInfo();
                    currMode = camera.GetGigEImagingMode();
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error getting current GigE image settings.", ex);
                    ex.Dispose();
                    return;
                }                

                PopulateModeComboBox(camera, currMode);
                SetActiveModeComboBox(currMode);
                OnGigEModeChanged(currMode);
            }

            // initilize all spin button value
            ValidateSettings();

            // initialize all slider's value
            OnPacketSizeSpinButtonValueChanged(null, null);
            OnGigEPacketDelaySpinButtonValueChanged(null, null);
        }

        private void UpdateGigEImageInfo(GigEImageSettingsInfo imageSettingsInfo)
        {
            // Common labels
            m_imageWidth = (int)imageSettingsInfo.maxWidth;
            m_imageHeight = (int)imageSettingsInfo.maxHeight;

            m_imageWidthSpinButton.Maximum = m_imageWidth;
            m_imageWidthSpinButton.Increment = imageSettingsInfo.imageHStepSize;
            m_imageWidthSpinButton.Minimum = imageSettingsInfo.imageHStepSize;

            m_imageHeightSpinButton.Maximum = m_imageHeight;
            m_imageHeightSpinButton.Increment = imageSettingsInfo.imageVStepSize;
            m_imageHeightSpinButton.Minimum = imageSettingsInfo.imageVStepSize;

            m_imageLeftSpinButton.Maximum = m_imageWidth - imageSettingsInfo.imageHStepSize;
            m_imageLeftSpinButton.Increment = imageSettingsInfo.offsetHStepSize;
            m_imageTopSpinButton.Maximum = m_imageHeight - imageSettingsInfo.imageVStepSize;
            m_imageTopSpinButton.Increment = imageSettingsInfo.offsetVStepSize;

            m_imageMaxSizeLabel.Text = string.Format(
                                        "Maximum image size: {0}x{1}",
                                        imageSettingsInfo.maxWidth,
                                        imageSettingsInfo.maxHeight);
            m_imageSizeUnits.Text = string.Format(
                                        "Image size units: {0}(H), {1}(V)",
                                        imageSettingsInfo.imageHStepSize,
                                        imageSettingsInfo.imageVStepSize);
            m_imageOffsetUnits.Text = string.Format(
                                        "Image offset units: {0}(H), {1}(V)",
                                        imageSettingsInfo.offsetHStepSize,
                                        imageSettingsInfo.offsetVStepSize);
            ValidateImageSize();
        }

        private void UpdateGigEPacketInfo()
        {
            if (IsIIDC() == true)
            {
                return;
            }

            ManagedGigECamera camera = (ManagedGigECamera)m_camera;
            GigEProperty packetSize;

            try
            {
                packetSize = camera.GetGigEProperty(GigEPropertyType.PacketSize);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting current packet size", ex);
                ex.Dispose();
                return;
            }

            UpdatePacketSize(packetSize);
        }

        private void UpdateGigEPacketDelay()
        {
            if (IsIIDC() == true)
            {
                return;
            }

            ManagedGigECamera camera = (ManagedGigECamera)m_camera;
            GigEProperty packetDelay;

            try
            {
                packetDelay = camera.GetGigEProperty(GigEPropertyType.PacketDelay);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting current packet size", ex);
                ex.Dispose();
                return;
            }

            m_gigEPacketDelayMaxLabel.Text = packetDelay.max.ToString();
            m_gigEPacketDelayMinLabel.Text = packetDelay.min.ToString();
            m_gigEPacketDelaySpinButton.Maximum = packetDelay.max;
            m_gigEPacketDelaySpinButton.Minimum = packetDelay.min;
            m_gigEPacketDelayTrackBar.Maximum = (int)packetDelay.max;
            m_gigEPacketDelayTrackBar.Minimum = (int)packetDelay.min;
            m_gigEPacketDelayTrackBar.LargeChange = (m_gigEPacketDelayTrackBar.Maximum - m_gigEPacketDelayTrackBar.Minimum) / 10;
            m_gigEPacketDelayTrackBar.TickFrequency = m_gigEPacketDelayTrackBar.LargeChange;
            try
            {
                m_gigEPacketDelaySpinButton.Value = packetDelay.value;
            }
            catch (ArgumentException ex)
            {
                m_gigEPacketDelaySpinButton.Value = m_gigEPacketDelaySpinButton.Maximum;
                Debug.WriteLine("Packet size spin value is out of range. {0}", ex.Message);
            }            
        }

        private void PopulatePixelFormatComboBox(uint pixelFormatsBitField, uint vendorPixelFormats)
        {
            m_pixelFormatComboBox.Items.Clear();
            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatMono8))
            {
                m_pixelFormatComboBox.Items.Add("Mono 8");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatMono12))
            {
                m_pixelFormatComboBox.Items.Add("Mono 12");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatMono16))
            {
                m_pixelFormatComboBox.Items.Add("Mono 16");
            }
            
            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatRaw8))
            {
                m_pixelFormatComboBox.Items.Add("Raw 8");
            }
            
            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatRaw12))
            {
                m_pixelFormatComboBox.Items.Add("Raw 12");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatRaw16))
            {
               m_pixelFormatComboBox.Items.Add("Raw 16");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormat411Yuv8))
            {
                m_pixelFormatComboBox.Items.Add("YUV 411");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormat422Yuv8))
            {
                m_pixelFormatComboBox.Items.Add("YUV 422");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormat444Yuv8))
            {
                m_pixelFormatComboBox.Items.Add("YUV 444");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatRgb8))
            {
                m_pixelFormatComboBox.Items.Add("RGB 8");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatRgb16))
            {
                m_pixelFormatComboBox.Items.Add("RGB 16");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatSignedMono16))
            {
                m_pixelFormatComboBox.Items.Add("Signed Mono 16");
            }

            if (IsPixelFormatMatch(pixelFormatsBitField, PixelFormat.PixelFormatSignedRgb16))
            {
                m_pixelFormatComboBox.Items.Add("Signed RGB 16");
            }

            // Check vendor unique pixel formats
            if (IsPixelFormatMatch(vendorPixelFormats, PixelFormat.PixelFormat422Yuv8Jpeg))
            {
                m_pixelFormatComboBox.Items.Add("YUV 422 (JPEG)");
            }

            if (m_isLadybugGUI == true && IsCameraStreaming() == true)
            {
                m_pixelFormatComboBox.Enabled = false;
            }
            else
            {
                m_pixelFormatComboBox.Enabled = true;
            }
        }

        private void PopulateModeComboBox(ManagedCamera camera, Mode currentMode)
        {
            m_modeComboBox.Items.Clear();
            for (int i = 0; i < (int)Mode.NumberOfModes; i++)
            {
                bool isThisModeSupported = false;
                try
                {
                    camera.GetFormat7Info((Mode)i, ref isThisModeSupported);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying Format7 information", ex);
                    ex.Dispose();
                    continue;
                }

                if (isThisModeSupported == true)
                {
                    m_modeComboBox.Items.Add(i);
                }
            }

            if (m_isLadybugGUI == true && IsCameraStreaming() == true)
            {
                m_modeComboBox.Enabled = false;
                if (currentMode == Mode.Mode0 || currentMode == Mode.Mode2)
                {
                   m_imageHeightSpinButton.Enabled = false;
                }
                else
                {
                   m_imageHeightSpinButton.Enabled = true;
                }
            }
            else
            {
                m_modeComboBox.Enabled = true;
            }
        }

        private void PopulateModeComboBox(ManagedGigECamera camera, Mode currentMode)
        {
            m_modeComboBox.Items.Clear();
            for (int i = 0; i < (int)Mode.NumberOfModes; i++)
            {
                bool isThisModeSupported = false;
                try
                {
                    isThisModeSupported = camera.QueryGigEImagingMode((Mode)i);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying GigE imaging mode availability.", ex);
                    ex.Dispose();
                    continue;
                }

                if (isThisModeSupported == true)
                {
                    //m_modeComboBox.Items.Add((Mode)i);
                    m_modeComboBox.Items.Add(i);
                    /*if ((int)currentMode == i)
                    {
                        m_modeComboBox.SelectedItem = i;
                    }*/
                }
            }
        }

        private Mode GetLowestMode()
        {
            int lowest = 0;
            Mode lowestMode = Mode.Mode0;
            bool supported = false;
            if (IsIIDC())
            {
                ManagedCamera camera = (ManagedCamera)m_camera;
                while (supported == false)
                {
                    if ((Mode)lowest == Mode.NumberOfModes)
                    {
                        //the last one, stop here
                        break;
                    }

                    //Format7Info fmt7Info;
                    //fmt7Info.mode = (Mode)lowest;
                    try
                    {
                        camera.GetFormat7Info((Mode)lowest, ref supported);
                    }
                    catch (FC2Exception ex)
                    {
                        ShowErrorMessageDialog("Error querying video mode and frame rate.", ex);
                        supported = false;
                        ex.Dispose();
                    }

                    if (m_isLadybugGUI == true && 
                        ((Mode)lowest == Mode.Mode6 || (Mode)lowest == Mode.Mode1))
                    {
                        //ladybug do not support mode 1 and 6 when LadybugGUI.dll is loaded
                        supported = false;
                    }

                    if (supported == false)
                    {
                        lowest++;
                    }
                }

                lowestMode = (Mode)lowest;
            }

            return lowestMode;
        }

        private PixelFormat GetLowestPixelFormat(Mode mode)
        {
            uint pixelFormats = 0;
            if (IsIIDC())
            {
                bool supported = false;
                Format7Info fmt7Info;
                ManagedCamera camera = (ManagedCamera)m_camera;
                try
                {
                    fmt7Info = camera.GetFormat7Info(mode, ref supported);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying Format7 information", ex);
                    return PixelFormat.PixelFormatMono8;
                    ex.Dispose();
                }

                pixelFormats = fmt7Info.pixelFormatBitField;
            }
            else if (IsGEV())
            {
                GigEImageSettingsInfo imageSettingsInfo;
                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                try
                {
                    imageSettingsInfo = camera.GetGigEImageSettingsInfo();
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying GigE image settings information", ex);
                    ex.Dispose();
                    return PixelFormat.PixelFormatMono8;
                }

                pixelFormats = imageSettingsInfo.pixelFormatBitField;
            }
            
            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatMono8))
            {
                return PixelFormat.PixelFormatMono8;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatMono12))
            {
                return PixelFormat.PixelFormatMono12;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatMono16))
            {
                return PixelFormat.PixelFormatMono16;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatRaw8))
            {
                return PixelFormat.PixelFormatRaw8;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatRaw12))
            {
                return PixelFormat.PixelFormatRaw12;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormat411Yuv8))
            {
                return PixelFormat.PixelFormat411Yuv8;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormat422Yuv8))
            {
                return PixelFormat.PixelFormat422Yuv8;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormat444Yuv8))
            {
                return PixelFormat.PixelFormat444Yuv8;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatRgb8))
            {
                return PixelFormat.PixelFormatRgb8;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatRgb16))
            {
                return PixelFormat.PixelFormatRgb16;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatSignedMono16))
            {
                return PixelFormat.PixelFormatSignedMono16;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormatSignedRgb16))
            {
                return PixelFormat.PixelFormatSignedRgb16;
            }

            if (IsPixelFormatMatch(pixelFormats, PixelFormat.PixelFormat422Yuv8Jpeg))
            {
                return PixelFormat.PixelFormat422Yuv8Jpeg;
            }

            return PixelFormat.PixelFormatMono8;
        }

        private bool IsPixelFormatMatch(uint pixelFormatBitField, PixelFormat checkFormat)
        {
            uint result = (uint)(pixelFormatBitField & checkFormat.GetHashCode());
            return result != 0;
        }

        private void SetPacketSizeVisible(bool isVisible)
        {
            m_PacketSizeLabel.Visible = isVisible;
            m_packetSizeMaxLabel.Visible = isVisible;
            m_packetSizeMinLabel.Visible = isVisible;
            m_packetSizeSpinButton.Visible = isVisible;
            m_packetSizeTrackBar.Visible = isVisible;
            m_packetSizeSpinButtonLabel.Visible = isVisible;
        }

        private void SetGigEPacketDelayEnabled(bool isEnabled)
        {
            m_gigEPacketDelayLabel.Enabled = isEnabled;
            m_gigEPacketDelayMaxLabel.Enabled = isEnabled;
            m_gigEPacketDelayMinLabel.Enabled = isEnabled;
            m_gigEPacketDelaySpinButton.Enabled = isEnabled;
            m_gigEPacketDelayTrackBar.Enabled = isEnabled;
            m_gigEPacketDelaySpinButtonLabel.Enabled = isEnabled;
        }

        private void OnCaptureAreaControlMousePress(object sender, MouseEventArgs e)
        {
            m_disableValidation = true;

            if (e.Button == MouseButtons.Left)
            {
                m_draggingStartX = GetMouseLocationX(e);
                m_draggingStartY = GetMouseLocationY(e);
                m_isLeftButtonDragging = true;

                if (m_draggingStartX > m_imageLeftSpinButton.Maximum)
                {
                    m_draggingStartX = Convert.ToInt32(m_imageLeftSpinButton.Maximum);
                }
                else if (m_draggingStartX < m_imageLeftSpinButton.Minimum)
                {
                    m_draggingStartX = Convert.ToInt32(m_imageLeftSpinButton.Minimum);
                }

                m_imageLeftSpinButton.Value = m_draggingStartX;
                if (m_draggingStartY > m_imageTopSpinButton.Maximum)
                {
                    m_draggingStartY = Convert.ToInt32(m_imageTopSpinButton.Maximum);
                }
                else if (m_draggingStartY < m_imageTopSpinButton.Minimum)
                {
                    m_draggingStartY = Convert.ToInt32(m_imageTopSpinButton.Minimum);
                }

                m_imageTopSpinButton.Value = m_draggingStartY;
                m_imageWidthSpinButton.Value = m_imageWidthSpinButton.Minimum;
                m_imageHeightSpinButton.Value = m_imageHeightSpinButton.Minimum;
            }
            else if (e.Button == MouseButtons.Right)
            {
                if (!m_isLeftButtonDragging)
                {
                    m_isRightButtonDragging = true;
                    m_draggingStartX = GetMouseLocationX(e);
                    m_draggingStartY = GetMouseLocationY(e);
                }
            }
        }

        private void OnCaptureAreaControlMouseRelease(object sender, MouseEventArgs e)
        {

            ValidateSettings();
            m_isLeftButtonDragging = false;
            m_isRightButtonDragging = false;
            m_disableValidation = false;
            UpdateImageSize();
        }

        private void OnCaptureAreaControlMouseMove(object sender, MouseEventArgs e)
        {
            m_cursorX = GetMouseLocationX(e);
            m_cursorY = GetMouseLocationY(e);
            if (m_isLeftButtonDragging)
            {  
                //check to see if the cursor is in drawing area 
                if (m_cursorX > m_imageWidth)
                {
                    m_cursorX = m_imageWidth;
                }
                else if (m_cursorX < 0)
                {
                    m_cursorX = 0;
                }

                if (m_cursorY > m_imageHeight)
                {
                    m_cursorY = m_imageHeight;
                }
                else if (m_cursorY < 0)
                {
                    m_cursorY = 0;
                } // check cursor in drawing area end

                // update value to spin button
                if (m_cursorX > m_draggingStartX)
                {
                    m_imageLeftSpinButton.Value = m_draggingStartX;
                    if (m_cursorX - m_captureArea.X < m_imageWidthSpinButton.Minimum)
                    {
                        m_imageWidthSpinButton.Value = m_imageWidthSpinButton.Minimum;
                    }
                    else
                    {
                        m_imageWidthSpinButton.Value = m_cursorX - m_captureArea.X;
                    }
                }
                else
                {
                    m_imageLeftSpinButton.Value = m_cursorX;
                    if (m_draggingStartX - m_cursorX < m_imageWidthSpinButton.Minimum)
                    {
                        m_imageWidthSpinButton.Value = m_imageWidthSpinButton.Minimum;
                    }
                    else
                    {
                        m_imageWidthSpinButton.Value = m_draggingStartX - m_cursorX;
                    }
                }

                if (m_cursorY > m_draggingStartY)
                {
                    m_imageTopSpinButton.Value = m_draggingStartY;
                    if (m_cursorY - m_captureArea.Y < m_imageHeightSpinButton.Minimum)
                    {
                        m_imageHeightSpinButton.Value = m_imageHeightSpinButton.Minimum;
                    }
                    else
                    {
                        m_imageHeightSpinButton.Value = m_cursorY - m_captureArea.Y;
                    }

                    if (m_cursorX < m_draggingStartX)
                    {
                        Cursor.Current = Cursors.SizeNESW;
                    }
                    else
                    {
                        Cursor.Current = Cursors.SizeNWSE;
                    }
                }
                else
                {
                    /* if it is: m_cursorY <= m_draggingStartY */
                    
                    m_imageTopSpinButton.Value = m_cursorY;
                    if (m_draggingStartY - m_cursorY < m_imageHeightSpinButton.Minimum)
                    {
                        m_imageHeightSpinButton.Value = m_imageHeightSpinButton.Minimum;
                    }
                    else
                    {
                        m_imageHeightSpinButton.Value = m_draggingStartY - m_cursorY;
                    }

                    if (m_cursorX >= m_draggingStartX)
                    {
                        Cursor.Current = Cursors.SizeNESW;
                    }
                    else
                    {
                        Cursor.Current = Cursors.SizeNWSE;
                    }
                } // update new value to spin button end
            }
            else if (m_isRightButtonDragging)
            {
                Cursor.Current = Cursors.SizeAll;

                //if it is right button
                //then move rectangle position       
                int moveX = m_cursorX - m_draggingStartX;
                int moveY = m_cursorY - m_draggingStartY;

                if (m_imageLeftSpinButton.Value + moveX < 0) 
                {
                    // make sure the rectangle is on the control drawing area
                    m_imageLeftSpinButton.Value = 0;
                }
                else if (m_imageLeftSpinButton.Value + moveX + m_imageWidthSpinButton.Value > m_imageWidth)
                {
                    // make sure the rectangle is on the control drawing area
                    m_imageLeftSpinButton.Value = m_imageWidth - m_captureArea.Width;
                }
                else
                {
                    m_imageLeftSpinButton.Value += moveX;

                    //after action finish reset drag position
                    m_draggingStartX = m_cursorX;
                }

                if (m_imageTopSpinButton.Value + moveY < 0)                   
                {
                    //make sure the rectangle is on the control drawing area 
                    m_imageTopSpinButton.Value = 0;
                }
                else if (m_imageTopSpinButton.Value + moveY + m_imageHeightSpinButton.Value > m_imageHeight)
                {
                    //make sure the rectangle is on the control drawing area
                    m_imageTopSpinButton.Value = m_imageHeight - m_captureArea.Height;
                }
                else
                {
                    m_imageTopSpinButton.Value += moveY;
                    m_draggingStartY = m_cursorY;
                }

                // write move position to register
                UpdateImagePositionInRegister();
            }

            m_maxDrawingAreaSize.Refresh();
        }

        private int GetMouseLocationY(MouseEventArgs e)
        {
            return (int)((float)e.Y * m_imageHeight / (m_captureAreaControl.Height - 5.0f)); // 5.0px is for Fixed3D Border
        }

        private int GetMouseLocationX(MouseEventArgs e)
        {
            return (int)((float)e.X * m_imageWidth / (m_captureAreaControl.Width - 5.0f)); // 5.0px is for Fixed3D Border
        }

        private void OnMainGroupBoxResize(object sender, EventArgs e)
        {
            AdjustCaptureAreaControlSize();           
        }

        private void AdjustCaptureAreaControlSize()
        {
            int captureAreaMaxWidth = m_maxDrawingAreaSize.Width;
            int captureAreaMaxHeight = m_maxDrawingAreaSize.Height;
            float imageAspectRatio = (float)m_imageHeight / (float)m_imageWidth;

            // Check to see if there is enough height for CaptureAreaControl
            if ((int)(captureAreaMaxWidth * imageAspectRatio) > captureAreaMaxHeight)
            {
                // Not enough height to put CaptureAreaControl on the page
                m_captureAreaControl.Height = captureAreaMaxHeight;

                // If the height is not enough, then the CaptureAreaControl width depends on its height in order to keep m_imageHeight : imageWidth
                m_captureAreaControl.Width = (int)(m_captureAreaControl.Height / imageAspectRatio);
            }
            else
            {
                m_captureAreaControl.Width = captureAreaMaxWidth;
                m_captureAreaControl.Height = (int)(m_captureAreaControl.Width * imageAspectRatio);
            }

            m_captureAreaControl.Refresh();
        }

        private void OnCaptureDrawingAreaPaint(object sender, PaintEventArgs e)
        {
            Graphics drawingAreaGraphics = e.Graphics;
            drawingAreaGraphics.SmoothingMode = SmoothingMode.HighQuality;
            drawingAreaGraphics.PixelOffsetMode = PixelOffsetMode.HighQuality;
            
            //clear graphics
            drawingAreaGraphics.Clear(Color.LightBlue);

            //start to draw capture area rectangle (red) and grey dash lines
            DrawCaptureAreaRectangle(drawingAreaGraphics);

            //draw information text
            if (m_captureAreaControl.Width < 150 || m_captureAreaControl.Height < 150)
            {
                //If there is not enough space to show the Cursor Information in drawing area, 
                //the information will shows outside of drawing area.
                string text;
                if (IsFormat7Supported() == true)
                {
                        text = string.Format(
                            "Start: ({0},{1}) End:({2},{3}){4}Dimensions: {5} x {6}{7}Cursor: ({8} , {9})",
                            m_captureArea.X,
                            m_captureArea.Y,
                            m_captureArea.Right,
                            m_captureArea.Bottom,
                            Environment.NewLine,
                            m_captureArea.Width,
                            m_captureArea.Height,
                            Environment.NewLine,
                            m_cursorX,
                            m_cursorY);
                }
                else
                {
                    text = "Custom Image mode is not supported by this camera.";
                }

                m_captureAreaAndCursorInfoLabel.Text = text;
                if (m_captureAreaControl.Height + 150 < m_maxDrawingAreaSize.Height)
                {
                    m_isTextInsufficientSpace = true;
                    m_captureAreaAndCursorInfoLabel.Visible = false;
                }
                else
                {
                    m_isTextInsufficientSpace = false;
                    m_captureAreaAndCursorInfoLabel.Visible = true;
                }
            }
            else
            {
                m_isTextInsufficientSpace = false;
                m_captureAreaAndCursorInfoLabel.Visible = false;
                DrawInformationText(drawingAreaGraphics);
            }
        }

        private void DrawInformationText(Graphics drawingAreaGraphics)
        {
            int centerX = m_captureAreaControl.Width / 2;
            int centerY = m_captureAreaControl.Height / 2;
            Font font = new Font("Tahoma", 8F, FontStyle.Regular, GraphicsUnit.Point, (byte)0);

            // specifying string format - centre text
            StringFormat format = new StringFormat();
            format.Alignment = StringAlignment.Center;
            format.LineAlignment = StringAlignment.Center;

            if (IsFormat7Supported() == false)
            {
                //if format7 is not supported, then just draw string to indicate
                if (m_captureAreaControl.Width < 300)
                {
                    //Oops! the sentence is too long to put in the display area
                    string notice = "Custom Image mode is not supported\n     by this camera.";
                    ////drawingAreaGraphics.DrawString(notice, font, Brushes.Black, centerX - (25 * k_pixelPerWord) / 2.0f, centerY - 10);
                    drawingAreaGraphics.DrawString(notice, font, Brushes.Black, centerX, centerY - 10, format);
                }
                else
                {
                    string notice = "Custom Image mode is not supported by this camera.";
                    drawingAreaGraphics.DrawString(notice, font, Brushes.Black, centerX, centerY - 10, format);
                } 

                return;
            }

            string rectangleStartEndLocation = string.Format(
                                               "Start: ({0},{1}) End:({2},{3})", 
                                                m_captureArea.X, 
                                                m_captureArea.Y, 
                                                m_captureArea.Width + m_captureArea.X,
                                                m_captureArea.Height + m_captureArea.Y);

            string rectangleDimension = string.Format(
                                        "Dimensions: {0} x {1}  ",
                                        m_captureArea.Width,
                                        m_captureArea.Height);

            string cursorLocation = string.Format(
                                        "Cursor: ({0} , {1})  ",
                                        m_cursorX,
                                        m_cursorY);

            //string cursorLocation=string
            drawingAreaGraphics.DrawString(rectangleStartEndLocation, font, Brushes.Black, centerX, centerY - 10, format);
            drawingAreaGraphics.DrawString(rectangleDimension, font, Brushes.Black, centerX, centerY + 10, format);
            drawingAreaGraphics.DrawString(cursorLocation, font, Brushes.Black, centerX, m_captureAreaControl.Height - 40, format);
        }

        private void OnTextInsufficientSpacePaint(object sender, PaintEventArgs e)
        {
            if (m_isTextInsufficientSpace)
            {
                int x = m_maxDrawingAreaSize.Width / 2;
                int y = m_captureAreaControl.Height + 25;

                // specifying string format - centre text
                StringFormat format = new StringFormat();
                format.Alignment = StringAlignment.Center;
                format.LineAlignment = StringAlignment.Center;
                Font font = new Font("Tahoma", 8F, FontStyle.Regular, GraphicsUnit.Point, (byte)0);
                e.Graphics.DrawString(m_captureAreaAndCursorInfoLabel.Text, font, Brushes.Black, x, y, format);
            }
        }

        private bool IsFormat7Supported()
        {
            if (m_camera == null)
            {
                return false;
            }

            if (IsGEV())
            {
                return true;
            }

            if (IsIIDC())
            {
                return true;
            }

            return false;
        }

        private void DrawCaptureAreaRectangle(Graphics drawingAreaGraphics)
        {
            float widthFixValue = 0.0f;
            float heightFixValue = 0.0f;
            if (m_captureAreaControl.BorderStyle == BorderStyle.Fixed3D) 
            {
                //trick of drawing: To get a better looking in the picture box for Fixed3D BorderStyle, 
                //I added some fix values to fix graphic size
                widthFixValue = -4.5f;
                heightFixValue = -4.5f;
            }

            //scale graphic to a size which is same as image size
            drawingAreaGraphics.ScaleTransform(
            (float)((m_captureAreaControl.Width + widthFixValue) / m_imageWidth),
            (float)((m_captureAreaControl.Height + heightFixValue) / m_imageHeight));
           
            Pen pen = new Pen(Color.Red, (float)m_imageWidth / m_captureAreaControl.Width * 2);
            drawingAreaGraphics.DrawRectangle(pen, m_captureArea);

            //draw grey dash line
            pen.DashStyle = DashStyle.Dash;
            pen.Color = Color.DarkGray;
            drawingAreaGraphics.DrawLine(pen, 0, m_captureArea.Y, m_captureArea.X, m_captureArea.Y);
            drawingAreaGraphics.DrawLine(pen, m_captureArea.X, 0, m_captureArea.X, m_captureArea.Y);
            drawingAreaGraphics.DrawLine(
                pen, 
                m_imageWidth, 
                m_captureArea.Y + m_captureArea.Height,
                m_captureArea.X + m_captureArea.Width, 
                m_captureArea.Y + m_captureArea.Height);
            drawingAreaGraphics.DrawLine(
                pen, 
                m_captureArea.X + m_captureArea.Width, 
                m_imageHeight,
                m_captureArea.X + m_captureArea.Width, 
                m_captureArea.Y + m_captureArea.Height);

            //restore scaling
            drawingAreaGraphics.ScaleTransform(
                (float)m_imageWidth / m_captureAreaControl.Width,
                (float)m_imageHeight / m_captureAreaControl.Height);
        }

        private void UpdateCaptureAreaRectangle()
        {
            m_captureArea.X = Convert.ToInt32(m_imageLeftSpinButton.Value);
            m_captureArea.Y = Convert.ToInt32(m_imageTopSpinButton.Value);
            m_captureArea.Width = Convert.ToInt32(m_imageWidthSpinButton.Value);
            m_captureArea.Height = Convert.ToInt32(m_imageHeightSpinButton.Value);
        }

        private void OnImageCaptureAreaSpinButtonValueChanged(object sender, EventArgs e)
        {
            UpdateCaptureAreaRectangle();
            ResetBandwidthString();
            // Clamp spin button values
            ClampAllSpinButtonValue();
            ValidateImageSize();
            m_captureAreaControl.Refresh();
            UpdateImageSize();
            ////WriteBackCurrentImageSizeValues()
        }

        private void UpdateF7PacketInfo(Format7ImageSettings imageSettings, Format7PacketInfo info)
        {
            if (IsIIDC() == false)
            {
                return;
            }

            uint configPacketSize = 0;
            float speed = 0.0f;

            uint currPacketSize = info.recommendedBytesPerPacket;
            if (IsCurrentlyInFormat7())
            {
                ManagedCamera camera = (ManagedCamera)m_camera;
                Format7ImageSettings camImageSettings = new Format7ImageSettings();
                try
                {
                    camera.GetFormat7Configuration(camImageSettings, ref configPacketSize, ref speed);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error getting current Format7 configuration", ex);
                    ex.Dispose();
                }

                if (imageSettings.pixelFormat == camImageSettings.pixelFormat
                    && imageSettings.mode == camImageSettings.mode)
                {
                    if (configPacketSize < info.maxBytesPerPacket)
                    {
                        currPacketSize = configPacketSize;
                    }
                    else
                    {
                        currPacketSize = info.maxBytesPerPacket;
                    }
                }
                else
                {
                    currPacketSize = info.maxBytesPerPacket;
                }
            }

            m_packetSizeMinLabel.Text = info.unitBytesPerPacket.ToString();
            m_packetSizeMaxLabel.Text = info.maxBytesPerPacket.ToString();
            m_packetSizeSpinButton.Maximum = info.maxBytesPerPacket;
            m_packetSizeSpinButton.Minimum = info.unitBytesPerPacket;
            m_packetSizeSpinButton.Increment = info.unitBytesPerPacket;

            m_packetSizeTrackBar.Maximum = (int)info.maxBytesPerPacket;
            m_packetSizeTrackBar.Minimum = (int)info.unitBytesPerPacket;
            m_packetSizeTrackBar.SmallChange = (int)info.unitBytesPerPacket;
            m_packetSizeTrackBar.LargeChange = (m_packetSizeTrackBar.Maximum - m_packetSizeTrackBar.Minimum) / 10;
            m_packetSizeTrackBar.TickFrequency = m_packetSizeTrackBar.LargeChange;

            try
            {
                m_packetSizeSpinButton.Value = currPacketSize;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                m_packetSizeSpinButton.Value = m_packetSizeSpinButton.Maximum;
                string msgText = string.Format(
                                 "Packet size spin value is out of range. Error from UpdateF7PacketInfo function. \n{0}\n{1}", 
                                 ex.Message,
                                 ex.StackTrace);
                Debug.WriteLine(msgText);
            }

            ValidatePacketSize();
        }

        private bool UpdateImagePositionInRegister()
        {
            if (m_modeComboBox.Items.Count <= 0)
            {
                return false;
            }

            uint left = Convert.ToUInt32(m_imageLeftSpinButton.Value);
            uint top = Convert.ToUInt32(m_imageTopSpinButton.Value);

            // Get the current mode from the video mode register
            uint currModeRegVal = 0;
            try
            {
                currModeRegVal = m_camera.ReadRegister(0x604);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Unable to read current mode register value. Current image size can not be saved in the register.", ex);
                ex.Dispose();
                return false;
            }

            uint currModeVal =
                ((currModeRegVal & 0xE0000000) >> 29) +
                (((currModeRegVal & 0x02000000) >> 25) << 4) +
                (((currModeRegVal & 0x01000000) >> 24) << 3);
            uint currMode = currModeVal;

            // Get the quadlet offset for the mode
            uint modeOffsetInqReg = 0x2E0 + (0x4 * currMode);
            uint modeOffsetInqRegVal = 0;
            try
            {
                modeOffsetInqRegVal = m_camera.ReadRegister(modeOffsetInqReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading mode offset register. Current image size can not be saved in the register.", ex);
                ex.Dispose();
                return false;
            }

            // Write to the offset registers   
            uint regOffset = ((modeOffsetInqRegVal * 4) & 0x000FFFFF) + 0x8;
            uint roiOffsetVal = (left << 16) | (top & 0xFFFF);
            try
            {
                m_camera.WriteRegister(regOffset, roiOffsetVal);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing ROI offset register", ex);
                ex.Dispose();
            }

            ValidateSettings();
            return true;
        }

        private bool ValidateImageSize()
        {
            bool isValid = true;
            if (Convert.ToInt32(m_imageLeftSpinButton.Value + m_imageWidthSpinButton.Value) > m_imageWidth)
            {
                m_imageLeftSpinButton.BackColor = Color.Red;
                m_imageWidthSpinButton.BackColor = Color.Red;
                isValid = false;
            }
            else
            {
                m_imageLeftSpinButton.BackColor = Color.PaleGreen;
                m_imageWidthSpinButton.BackColor = Color.PaleGreen;
            }
            
            if (Convert.ToInt32(m_imageTopSpinButton.Value + m_imageHeightSpinButton.Value) > m_imageHeight)
            {
                m_imageTopSpinButton.BackColor = Color.Red;
                m_imageHeightSpinButton.BackColor = Color.Red;
                isValid = false;
            }
            else
            {
                m_imageTopSpinButton.BackColor = Color.PaleGreen;
                m_imageHeightSpinButton.BackColor = Color.PaleGreen;
            }

            return isValid;
        }

        private void ClampAllSpinButtonValue()
        {
            try
            {
                m_imageLeftSpinButton.Value = ClampValue(m_imageLeftSpinButton.Value, m_imageLeftSpinButton.Increment);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("Image left value in spin button is out of range.");
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }

            try
            {
                m_imageWidthSpinButton.Value = ClampValue(m_imageWidthSpinButton.Value, m_imageWidthSpinButton.Increment);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("Image width value in spin button is out of range.");
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }

            try
            {
                m_imageTopSpinButton.Value = ClampValue(m_imageTopSpinButton.Value, m_imageTopSpinButton.Increment);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("Image top value in spin button is out of range.");
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            } 

            try
            {
                m_imageHeightSpinButton.Value = ClampValue(m_imageHeightSpinButton.Value, m_imageHeightSpinButton.Increment);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("Image height value in spin button is out of range.");
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }
        }

        private void DisableWidgets()
        {
            m_modeComboBox.Enabled = false;
            m_pixelFormatComboBox.Enabled = false;
            m_centerROIButton.Enabled = false;
            m_applyButton.Visible = false;
            m_imageLeftSpinButton.Enabled = false;
            m_imageTopSpinButton.Enabled = false;
            m_imageWidthSpinButton.Enabled = false;
            m_imageHeightSpinButton.Enabled = false;
            m_packetSizeTrackBar.Enabled = false;
            m_packetSizeSpinButton.Enabled = false;
            m_gigEPacketDelayTrackBar.Enabled = false;
            m_gigEPacketDelaySpinButton.Enabled = false;
            m_captureAreaControl.Enabled = false;
        }

        private void EnableWidgets()
        {
            m_modeComboBox.Enabled = true;
            m_pixelFormatComboBox.Enabled = true;
            m_centerROIButton.Enabled = true;
            m_applyButton.Visible = true;
            m_imageLeftSpinButton.Enabled = true;
            m_imageTopSpinButton.Enabled = true;
            m_imageWidthSpinButton.Enabled = true;
            m_imageHeightSpinButton.Enabled = true;
            m_packetSizeTrackBar.Enabled = true;
            m_packetSizeSpinButton.Enabled = true;
            m_gigEPacketDelayTrackBar.Enabled = true;
            m_gigEPacketDelaySpinButton.Enabled = true;
            m_captureAreaControl.Enabled = true;
        }

        private bool IsCurrentlyInFormat7()
        {
            if (IsGEV() == true)
            {
                return true;
            }

            VideoMode currVideoMode = VideoMode.NumberOfVideoModes;
            FrameRate currFrameRate = FrameRate.NumberOfFrameRates;
            ManagedCamera camera = (ManagedCamera)m_camera;
            try
            {
                camera.GetVideoModeAndFrameRate(ref currVideoMode, ref currFrameRate);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting current video mode and frame rate", ex);
                ex.Dispose();
            }

            return currVideoMode == VideoMode.VideoModeFormat7;
        }

        private void OnPackSizeTrackBarScroll(object sender, EventArgs e)
        {
            ResetBandwidthString();
            if (IsIIDC())
            {
                try
                {
                    m_packetSizeSpinButton.Value = m_packetSizeTrackBar.Value;
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine("The Packet Size spin button value is out of range. {0}", ex.Message);
                }

                m_packetSizeSpinButton.Value = ClampValue(m_packetSizeSpinButton.Value, m_packetSizeSpinButton.Increment);
                ValidatePacketSize();
            }
            else
            {
                try
                {
                    m_packetSizeSpinButton.Value = m_packetSizeTrackBar.Value;
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine("The Packet Size spin button value is out of range. {0}", ex.Message);
                }
            }
        }

        private void OnImageSpinButtonKeyRelaase(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter || e.KeyCode == Keys.Return)
            {
                NumericUpDown button = (NumericUpDown)sender;
                button.Select(button.Value.ToString().Length, 0);
                ValidateSettings();
                ResetBandwidthString();
            }
        }

        private void OnCenterROIButtonClick(object sender, EventArgs e)
        {
            if (IsIIDC())
            {
                Format7ImageSettings settings = GetF7InfoFromPage();
                ManagedCamera camera = (ManagedCamera)m_camera;
                bool supported = false;
                Format7Info fmt7Info;
                try
                {
                    fmt7Info = camera.GetFormat7Info(settings.mode, ref supported);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error getting Custom Image information from camera. Center ROI failed.", ex);
                    ex.Dispose();
                    return;
                }

                uint left = (fmt7Info.maxWidth - settings.width) / 2;
                while (left % fmt7Info.offsetHStepSize != 0)
                {
                    left++;
                }

                if ((left + settings.width) <= fmt7Info.maxWidth)
                {
                    settings.offsetX = left;
                    m_imageLeftSpinButton.Value = left;
                }

                uint top = (fmt7Info.maxHeight - settings.height) / 2;
                while (top % fmt7Info.offsetVStepSize != 0)
                {
                    top++;
                }

                if ((top + settings.height) <= fmt7Info.maxHeight)
                {
                    settings.offsetY = top;
                    m_imageTopSpinButton.Value = top;
                }
            }
            else if (IsGEV())
            {
                GigEImageSettings settings = GetGigEImageInfoFromPage();
                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                GigEImageSettingsInfo imageSettingsInfo;
                try
                {
                    imageSettingsInfo = camera.GetGigEImageSettingsInfo();
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error getting GigE image setting from camera. Center ROI failed.", ex);
                    ex.Dispose();
                    return;
                }

                uint left = (imageSettingsInfo.maxWidth - settings.width) / 2;
                while (left % imageSettingsInfo.offsetHStepSize != 0)
                {
                    left++;
                }

                if ((left + settings.width) <= imageSettingsInfo.maxWidth)
                {
                    settings.offsetX = left;
                    m_imageLeftSpinButton.Value = left;
                }

                uint top = (imageSettingsInfo.maxHeight - settings.height) / 2;
                while (top % imageSettingsInfo.offsetVStepSize != 0)
                {
                    top++;
                }

                if ((top + settings.height) <= imageSettingsInfo.maxHeight)
                {
                    settings.offsetY = top;
                    m_imageTopSpinButton.Value = top;
                }
            }

            //check 
            ValidateSettings();
        }

        private void OnModeComboBoxSelectedIndexChanged(object sender, EventArgs e)
        {
            m_disableValidation = true;
            // Get current selected mode in the Mode ComboBox
            Mode selectedMode = (Mode)m_modeComboBox.SelectedItem;
            if (selectedMode == Mode.NumberOfModes)
            {
                Debug.WriteLine("Invalid mode specified");
                return;
            }

            // TODO: check if this works.
            if (m_isLadybugGUI == true &&
                (selectedMode == Mode.Mode1 || selectedMode == Mode.Mode6))
            {
                MessageBox.Show("Ladybug camera does not support mode 1 and mode 6.");
                selectedMode = GetLowestMode();
            }

            if (IsIIDC())
            {
                OnIIDCModeChanged(selectedMode);                
            }
            else if (IsGEV())
            {
                OnGigEModeChanged(selectedMode);
            }

            AdjustCaptureAreaControlSize();
            m_disableValidation = false;
            ValidateSettings();
            ResetBandwidthString();
        }

        private void OnIIDCModeChanged(Mode newMode)
        {
            Debug.Assert(m_camera is ManagedCamera, "The interface type must be GigE.");

            ManagedCamera camera = (ManagedCamera)m_camera;
            bool supported = false;
            Format7Info fmt7Info = new Format7Info();
            try
            {
                fmt7Info = camera.GetFormat7Info(newMode, ref supported);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error querying Format7 information", ex);
                ex.Dispose();
            }

            UpdateImageInformation(fmt7Info);
            UpdateResizeInformation();

            uint left = 0;
            uint top = 0;
            uint width = 0;
            uint height = 0;
            uint packetSize = 0;
            PixelFormat pixelFormat = PixelFormat.NumberOfPixelFormats;

            bool success = GetF7ImageParametersFromCamera(newMode, ref left, ref top, ref width, ref height, ref pixelFormat, ref packetSize);
            if (success)
            {
                bool leftOk = ValidateImageLeft(left, width, fmt7Info.offsetHStepSize, fmt7Info.maxWidth);
                bool topOk = ValidateImageTop(top, height, fmt7Info.offsetVStepSize, fmt7Info.maxHeight);
                bool widthOk = ValidateImageWidth(left, width, fmt7Info.imageHStepSize, fmt7Info.maxWidth);
                bool heightOk = ValidateImageHeight(top, height, fmt7Info.imageVStepSize, fmt7Info.maxHeight);

                if (!leftOk || !topOk || !widthOk || !heightOk)
                {
                    ResetImageSize(fmt7Info);
                }
                else
                {
                    //(left,top,width,height are Ok)
                    m_imageLeftSpinButton.Value = left;
                    m_imageTopSpinButton.Value = top;
                    m_imageWidthSpinButton.Value = width;
                    m_imageHeightSpinButton.Value = height;
                }

                PopulatePixelFormatComboBox(
                    fmt7Info.pixelFormatBitField,
                    fmt7Info.vendorPixelFormatBitField);
                SetActivePixelFormatComboBox(pixelFormat);
                ////UpdatePacketSize(packetSize, fmt7Info);
            }
            else
            {
                ResetImageSize(fmt7Info);
                UpdatePacketSize(fmt7Info.maxPacketSize, fmt7Info);
            }

            // Display message if the selected mode is not supported by ladybug library
            if (m_isLadybugGUI)
            {
                bool isLadybugLibSupported = true;
                if (IsLadybug3())
                {
                    isLadybugLibSupported =
                        newMode == Mode.Mode0 || newMode == Mode.Mode7 ||
                        newMode == Mode.Mode2 || newMode == Mode.Mode3;
                }
                else
                {
                    if (IsLadybug2())
                    {
                        isLadybugLibSupported = newMode == Mode.Mode0 || newMode == Mode.Mode7;
                    }
                }

                if (!isLadybugLibSupported)
                {
                    MessageBox.Show(
                    "Please select another mode.",
                    "This mode is not supported by Ladybug library.",
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Information);
                }
            }
        }

        private void OnGigEModeChanged(Mode newMode)
        {
            Debug.Assert(m_camera is ManagedGigECamera, "The interface type must be GigE.");

            try
            {
                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                camera.SetGigEImagingMode(newMode);

                GigEImageSettingsInfo imageSettingsInfo;
                imageSettingsInfo = camera.GetGigEImageSettingsInfo();

                GigEImageSettings imageSettings;
                imageSettings = camera.GetGigEImageSettings();

                // Get the new binning values
                uint horzBinning = 0;
                uint vertBinning = 0;

                camera.GetGigEImageBinningSettings(ref horzBinning, ref vertBinning);

                // At this point, we have all the information we need to 
                // set the image settings on the page
                PopulatePixelFormatComboBox(
                    imageSettingsInfo.pixelFormatBitField,
                    imageSettingsInfo.vendorPixelFormatBitField);

                // Set the appropriate mode and pixel format as active
                SetActivePixelFormatComboBox(imageSettings.pixelFormat);

                // No need to raise value changed event on two spinbtns
                m_skippSpinBtnEvent = true;
                m_binningHSpinBtn.Value = horzBinning;
                m_binningVSpinBtn.Value = vertBinning;

                // Update image information
                UpdateGigEImageInfo(imageSettingsInfo);

                m_imageLeftSpinButton.Value = imageSettings.offsetX;
                m_imageTopSpinButton.Value = imageSettings.offsetY;
                m_imageWidthSpinButton.Value = imageSettings.width;
                m_imageHeightSpinButton.Value = imageSettings.height;

                ValidateImageSize();
                OnApply();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error setting GigE imaging mode.", ex);
                Debug.WriteLine("Failed to set GigE imaging mode: " + ex.ToString());
                ex.Dispose();
                return;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Debug.WriteLine(ex.ToString());
            }
            finally
            {
                m_skippSpinBtnEvent = false;
            }
        }

        private void ResetImageSize(Format7Info fmt7Info)
        {
            m_imageLeftSpinButton.Value = 0;
            m_imageTopSpinButton.Value = 0;
            m_imageWidthSpinButton.Value = fmt7Info.maxWidth;
            m_imageHeightSpinButton.Value = fmt7Info.maxHeight;
        }

        private void ResetImageSize(GigEImageSettingsInfo imageInfo)
        {
            m_imageLeftSpinButton.Value = 0;
            m_imageTopSpinButton.Value = 0;
            m_imageWidthSpinButton.Value = imageInfo.maxWidth;
            m_imageHeightSpinButton.Value = imageInfo.maxHeight;
        }

        private void UpdatePacketSize(uint packetSize, Format7Info fmt7Info)
        {
            m_packetSizeMaxLabel.Text = fmt7Info.maxPacketSize.ToString();
            m_packetSizeMinLabel.Text = fmt7Info.minPacketSize.ToString();
            m_packetSizeSpinButton.Maximum = fmt7Info.maxPacketSize;
            m_packetSizeSpinButton.Minimum = fmt7Info.minPacketSize;
            m_packetSizeSpinButton.Increment = fmt7Info.minPacketSize;
            m_packetSizeTrackBar.Maximum = (int)fmt7Info.maxPacketSize;
            m_packetSizeTrackBar.Minimum = (int)fmt7Info.minPacketSize;
            m_packetSizeTrackBar.SmallChange = (int)fmt7Info.minPacketSize;
            m_packetSizeTrackBar.LargeChange = (m_packetSizeTrackBar.Maximum - m_packetSizeTrackBar.Minimum) / 10;
            m_packetSizeTrackBar.TickFrequency = m_packetSizeTrackBar.LargeChange;
            try
            {
                m_packetSizeSpinButton.Value = packetSize;
            }
            catch (ArgumentException ex)
            {
                m_packetSizeSpinButton.Value = m_packetSizeSpinButton.Maximum;
                Debug.WriteLine("Packet size spin value is out of range. {0}", ex.Message);
            }
        }

        private void UpdatePacketSize(GigEProperty property)
        {
            m_packetSizeMaxLabel.Text = property.max.ToString();
            m_packetSizeMinLabel.Text = property.min.ToString();
            m_packetSizeSpinButton.Maximum = property.max;
            m_packetSizeSpinButton.Minimum = property.min;
            m_packetSizeSpinButton.Increment = 1;
            m_packetSizeTrackBar.Maximum = (int)property.max;
            m_packetSizeTrackBar.Minimum = (int)property.min;
            m_packetSizeTrackBar.SmallChange = 1;
            m_packetSizeTrackBar.LargeChange = (m_packetSizeTrackBar.Maximum - m_packetSizeTrackBar.Minimum) / 10;
            try
            {
                m_packetSizeSpinButton.Value = property.value;
            }
            catch (ArgumentException ex)
            {
                m_packetSizeSpinButton.Value = m_packetSizeSpinButton.Maximum;
                Debug.WriteLine("Packet size spin value is out of range. {0}", ex.Message);
            }
        }

        private bool SetActiveModeComboBox(Mode mode)
        {
            for (int i = 0; i < m_modeComboBox.Items.Count; i++)
            {
                if ((int)m_modeComboBox.Items[i] == (int)mode)
                {
                    m_modeComboBox.SelectedIndex = i;
                    return true;
                }
            }

            return false;
        }

        private bool SetActivePixelFormatComboBox(PixelFormat pixelFormat)
        {
            PixelFormat currFormat;

            for (int i = 0; i < m_pixelFormatComboBox.Items.Count; i++)
            {
                try
                {
                    currFormat = m_pixelFormatDictionary[(string)m_pixelFormatComboBox.Items[i]];

                    if (currFormat == pixelFormat)
                    {
                        m_pixelFormatComboBox.SelectedIndex = i;
                        return true;
                    }
                }
                catch (SystemException ex)
                {
                    Debug.WriteLine(ex.Message);
                    return false;
                }
            }

            return false;
        }

        private bool ValidateImageLeft(uint left, uint width, uint offsetHStepSize, uint maxWidth)
        {
            // Offset must be a multiple of the step size
            // Offset and width combined must be less than the maximum width
            if ((left % offsetHStepSize == 0) &&
                (left + width <= maxWidth))
            {
                return true;
            }

            return false;
        }

        private bool ValidateImageTop(uint top, uint height, uint offsetVStepSize, uint maxHeight)
        {
            // Offset must be a multiple of the step size
            // Offset and height combined must be less than the maximum height
            if ((top % offsetVStepSize == 0) &&
                (top + height <= maxHeight))
            {
                return true;
            }

            return false;
        }

        private bool ValidateImageWidth(uint left, uint width, uint imageHStepSize, uint maxWidth)
        {
            // Width must be a multiple of the step size
            // Offset and width combined must be less than the maximum width
            // Width can't be zero
            if ((width % imageHStepSize == 0) &&
                (left + width <= maxWidth) &&
                (width != 0))
            {
                return true;
            }

            return false;
        }

        private bool ValidateImageHeight(uint top, uint height, uint offsetVStepSize, uint maxHeight)
        {
            // Height must be a multiple of the step size
            // Offset and height combined must be less than the maximum height
            // Height can't be zero
            if ((height % offsetVStepSize == 0) &&
                (top + height <= maxHeight) &&
                (height != 0))
            {
                return true;
            }

            return false;
        }

        private void UpdateImageInformation(Format7Info fmt7Info)
        {
            m_imageWidth = (int)fmt7Info.maxWidth;
            m_imageHeight = (int)fmt7Info.maxHeight;

            m_imageWidthSpinButton.Increment = fmt7Info.imageHStepSize;
            m_imageWidthSpinButton.Maximum = m_imageWidth;
            m_imageWidthSpinButton.Minimum = fmt7Info.imageHStepSize;

            m_imageHeightSpinButton.Increment = fmt7Info.imageVStepSize;
            m_imageHeightSpinButton.Maximum = m_imageHeight;
            m_imageHeightSpinButton.Minimum = fmt7Info.imageVStepSize;

            m_imageLeftSpinButton.Maximum = m_imageWidth - fmt7Info.imageHStepSize;
            m_imageLeftSpinButton.Increment = fmt7Info.offsetHStepSize;
            m_imageTopSpinButton.Maximum = m_imageHeight - fmt7Info.imageVStepSize;
            m_imageTopSpinButton.Increment = fmt7Info.offsetVStepSize;

            m_imageMaxSizeLabel.Text = string.Format("Maximum image size: {0}x{1}", fmt7Info.maxWidth, fmt7Info.maxHeight);
            m_imageSizeUnits.Text = string.Format("Image size units: {0}(H), {1}(V)", fmt7Info.imageHStepSize, fmt7Info.imageVStepSize);
            m_imageOffsetUnits.Text = string.Format("Image offset units: {0}(H), {1}(V)", fmt7Info.offsetHStepSize, fmt7Info.offsetVStepSize);
        }

        private void UpdateBandwidthInformation()
        {
            bool noError = true;
            decimal framerate = 0m;
            float maxFramerate = 0;
            uint packetSize = 0;
            try
            {
                packetSize = Convert.ToUInt32(m_packetSizeSpinButton.Value);
            }
            catch
            {
                noError = false;
            }

            if(m_imageSize!=0 && noError)
            {
                decimal bandwidth = 0;
                decimal numofPacketsPerImage = 0;

                try
                {
                    CameraInfo info = m_camera.GetCameraInfo();

                    switch (info.interfaceType)
                    {
                        case InterfaceType.GigE:
                            bandwidth = CalculateGigEBandwidth(m_imageSize) / 1000000m; // convert to MB/s
                            break;
                        case InterfaceType.Ieee1394:
                            numofPacketsPerImage = Convert.ToDecimal(m_imageSize) / Convert.ToDecimal(packetSize);
                            numofPacketsPerImage = Math.Ceiling(numofPacketsPerImage);
                            maxFramerate = 0;
                            try
                            {
                                //read resize information value from register
                                //maxFramerateRegVal = m_camera.ReadRegister(0x964);
                                CameraPropertyInfo pinfo;
                                pinfo = m_camera.GetPropertyInfo(PropertyType.FrameRate);
                                maxFramerate = pinfo.absMax;
                            }
                            catch
                            {
                                bandwidth = 0;
                                break;
                            }

                            framerate = 8000m / numofPacketsPerImage;
                            if (maxFramerate != 0 && Convert.ToDecimal(maxFramerate) < framerate)
                            {
                                // Since Apply button might not be clicked yet. We can know whether calculated
                                // frame rate is more than the actual max frame rate. To be safe, let's user 
                                // current mode's max frame rate to test. This will result in an inaccurate 
                                // bandwidth result before Apply was clicked.
                                framerate = Convert.ToDecimal(maxFramerate);
                            }

                            bandwidth = framerate * Convert.ToDecimal(m_imageSize) / 1000000m; // convert to MB/s
                            break;
                        case InterfaceType.Usb2:
                        case InterfaceType.Usb3:
                            // Can't really calculate real bandwidth for USB3.0. Let's estimate it using 8000 cycle/sec instead.
                            if (m_imageSize < packetSize)
                            {
                                packetSize = m_imageSize;
                            }
                            numofPacketsPerImage = Convert.ToDecimal(m_imageSize) / Convert.ToDecimal(packetSize);
                            numofPacketsPerImage = Math.Ceiling(numofPacketsPerImage);
                            maxFramerate = 0;
                            try
                            {
                                //read resize information value from register
                                //maxFramerateRegVal = m_camera.ReadRegister(0x964);
                                CameraPropertyInfo pinfo;
                                pinfo = m_camera.GetPropertyInfo(PropertyType.FrameRate);
                                maxFramerate = pinfo.absMax;
                            }
                            catch
                            {
                                bandwidth = 0;
                                break;
                            }

                            framerate = 8000m / numofPacketsPerImage;
                            if (maxFramerate != 0 && Convert.ToDecimal(maxFramerate) < framerate)
                            {
                                // Since Apply button might not be clicked yet. We can know whether calculated
                                // frame rate is more than the actual max frame rate. To be safe, let's user 
                                // current mode's max frame rate to test. This will result in an inaccurate 
                                // bandwidth result before Apply was clicked.
                                framerate = Convert.ToDecimal(maxFramerate);
                            }

                            bandwidth = framerate * Convert.ToDecimal(m_imageSize) / 1000000m; // convert to MB/s
                            break;
                        case InterfaceType.Unknown:
                            bandwidth = 0;
                            break;
                    }
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine("Unable to get Camera Info. {0}", ex.Message);
                    bandwidth = 0;
                    ex.Dispose();
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                    bandwidth = 0;
                }

                if (bandwidth == 0)
                {
                    m_expectedBandwidthLabel.Text = string.Format("Estimated Bandwidth: N/A");
                }
                else
                {
                    m_expectedBandwidthLabel.Text = string.Format("Estimated Bandwidth: {0:F0} MB/s", bandwidth);
                }
            }
        }

        private void UpdateImageSize()
        {
            bool noError = true;
            uint imageWidth = 0;
            uint imageHeight = 0;
            uint packetSize = 0;
            PixelFormat pixelFormat = PixelFormat.NumberOfPixelFormats;
            uint bitsPerPixel = 0;

            try
            {
                imageWidth = Convert.ToUInt32(m_imageWidthSpinButton.Value);
                imageHeight = Convert.ToUInt32(m_imageHeightSpinButton.Value);
                packetSize = Convert.ToUInt32(m_packetSizeSpinButton.Value);
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine(ex.Message);
                noError = false;
            }

            if (m_pixelFormatComboBox.Items.Count > 0)
            {
                try
                {
                    pixelFormat = m_pixelFormatDictionary[(string)m_pixelFormatComboBox.SelectedItem];
                }
                catch (System.Exception ex)
                {
                    pixelFormat = PixelFormat.NumberOfPixelFormats;
                    Debug.WriteLine(ex.Message);
                }
            }
            else
            {
                pixelFormat = PixelFormat.NumberOfPixelFormats;
            }

            if (noError)
            {
                if (pixelFormat == PixelFormat.PixelFormatRgb8)
                {
                    bitsPerPixel = 24;
                }
                else
                {
                    switch (pixelFormat)
                    {
                        case PixelFormat.PixelFormatMono8:
                        case PixelFormat.PixelFormatRaw8:
                            bitsPerPixel = 8;
                            break;
                        case PixelFormat.PixelFormatRaw12:
                        case PixelFormat.PixelFormatMono12:
                        case PixelFormat.PixelFormat411Yuv8:
                            bitsPerPixel = 12;
                            break;
                        case PixelFormat.PixelFormat422Yuv8:
                        case PixelFormat.PixelFormatMono16:
                        case PixelFormat.PixelFormatRaw16:
                            bitsPerPixel = 16;
                            break;
                        case PixelFormat.PixelFormat444Yuv8:
                        case PixelFormat.PixelFormatBgr:
                        case PixelFormat.PixelFormatRgb:
                            bitsPerPixel = 24;
                            break;
                        case PixelFormat.PixelFormatRgbu:
                        case PixelFormat.PixelFormatBgru:
                            bitsPerPixel = 32;
                            break;
                        case PixelFormat.PixelFormatBgr16:
                        case PixelFormat.PixelFormatRgb16:
                        case PixelFormat.PixelFormatSignedRgb16:
                            bitsPerPixel = 48;
                            break;
                        default:
                            bitsPerPixel = 0;
                            break;
                    }
                }

                m_imageSize = imageWidth * imageHeight * bitsPerPixel / 8; // in Bytes
                m_imageSizeLabel.Text = string.Format("Image Size: {0}", m_imageSize == 0 ? "N/A" : (m_imageSize / 1000).ToString() + " KB");
            }
        }

        private decimal CalculateGigEBandwidth(uint imageSize)
        {
            if (m_linkSpeed == 0 || m_tick == 0)
            {
                return 0m;
            }
            else
            {
                decimal delay = m_gigEPacketDelaySpinButton.Value * (1m / m_tick); // Handling an zero packet delay as 0 for now

                // check Packet Size and Image Size
                decimal realPacketSize = 0;
                if (imageSize >= m_packetSizeSpinButton.Value)
                {
                    realPacketSize = m_packetSizeSpinButton.Value;
                }
                else
                {
                    realPacketSize = imageSize;
                }

                // Calculate number of packets for a single image
                decimal timePerPacket = realPacketSize / Convert.ToDecimal(m_linkSpeed) + delay;
                decimal packetsPerImage = Convert.ToDecimal(imageSize) / realPacketSize;
                packetsPerImage = Math.Ceiling(packetsPerImage);

                // Calculate theoretical frame rate 
                decimal PacketPerSecond = 1m / timePerPacket;
                decimal framerate = PacketPerSecond / packetsPerImage;

                // check whether calculated frame rate make sense
                float maxFramerate = 0;
                try
                {
                    //read resize information value from register
                    //maxFramerateRegVal = m_camera.ReadRegister(0x964);
                    CameraPropertyInfo pinfo;
                    pinfo = m_camera.GetPropertyInfo(PropertyType.FrameRate);
                    maxFramerate = pinfo.absMax;
                }
                catch
                {
                    // Error getting PropertyInfo from camera
                    // So, no point calculating bandwidth
                    framerate = 0;
                }

                if (maxFramerate != 0 && Convert.ToDecimal(maxFramerate) < framerate)
                {
                    // Since Apply button might not be clicked yet. We can know whether calculated
                    // frame rate is more than the actual max frame rate. To be safe, let's user 
                    // current mode's max frame rate to test. This will result in an inaccurate 
                    // bandwidth result before Apply was clicked.
                    framerate = Convert.ToDecimal(maxFramerate);
                }

                // Calculate theoretical bandwidth
                decimal bandwidth = framerate * Convert.ToDecimal(imageSize);

                return bandwidth; // bit/s
            }
        }

        private void UpdateResizeInformation()
        {
            uint resizeRegVal = 0;
            try
            {
                //read resize information value from register
                resizeRegVal = m_camera.ReadRegister(0x1AC8);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Failed to read resize information from register (Register Address:0x1AC8). {0}", ex);
                DisableImageResizeInformation();
                ex.Dispose();
                return;
            }

            if ((resizeRegVal >> 31) != 1)
            {
                DisableImageResizeInformation();
                return;
            }            

            // Check to see what is enabled
            bool isPreVert = (resizeRegVal & (0x1 << 7)) != 0;
            bool isPreHorz = (resizeRegVal & (0x1 << 6)) != 0;
            bool isPostVert = (resizeRegVal & (0x1 << 5)) != 0;
            bool isPostHorz = (resizeRegVal & (0x1 << 4)) != 0;

            bool isStdVert = (resizeRegVal & (0x1 << 3)) != 0;
            bool isStdHorz = (resizeRegVal & (0x1 << 2)) != 0;
            bool isBayerVert = (resizeRegVal & (0x1 << 1)) != 0;
            bool isBayerHorz = (resizeRegVal & (0x1 << 0)) != 0;

            // If nothing is enabled the set all resize information to unknown
            if (!isPreVert && !isPreHorz && !isPostVert && !isPostHorz && !isStdVert && !isStdHorz && !isBayerVert && !isBayerHorz)
            {
                DisableImageResizeInformation();
                return;
            }

            // Check pre-color processing subsampling
            m_preColorProcessingSubsampling.Text = "Pre color processing subsampling: " + GetStringVerticalAndHorizontalInformation(isPreVert, isPreHorz);

            // Check post-color processing subsampling
            m_postColorProcessingSubsampling.Text = "Post color processing subsampling: " + GetStringVerticalAndHorizontalInformation(isPostVert, isPostHorz);

            // Check std binning
            m_standardBinning.Text = "Standard binning: " + GetStringVerticalAndHorizontalInformation(isStdVert, isStdHorz);

            // Check bayer binning
            m_bayerBinning.Text = "Bayer binning: " + GetStringVerticalAndHorizontalInformation(isBayerVert, isBayerHorz);

            // Add the rows and cols 
            uint numCols = ((resizeRegVal & 0x00F00000) >> 20) + 1;
            uint numRows = ((resizeRegVal & 0x000F0000) >> 16) + 1;
            m_colsRowsLabel.Text = string.Format("Cols: {0}     Rows: {1}", numCols, numRows);
        }

        private bool GetF7ImageParametersFromCamera(Mode mode, ref uint imageLeft, ref uint imageTop, ref uint imageWidth, ref uint imageHeight)
        {
            // Get the proper mode offset
            uint modeOffset = 0;
            uint modeOffsetRegisterAddress = 0x2E0 + (4 * (uint)mode);
            try
            {
                modeOffset = m_camera.ReadRegister(modeOffsetRegisterAddress);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Failed to get mode offset. {0}", ex.Message);
                ex.Dispose();
                return false;
            }

            modeOffset *= 4;
            modeOffset &= 0x000FFFFF;
            uint imageSize;
            try
            {
                imageSize = m_camera.ReadRegister(modeOffset + 0x008);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Failed to get image size. {0}", ex.Message);
                ex.Dispose();
                return false;
            }

            imageLeft = imageSize >> 16;
            imageTop = imageSize & 0x0000FFFF;

            uint imagePosition;
            try
            {
                imagePosition = m_camera.ReadRegister(modeOffset + 0x00C);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Failed to get image position. {0}", ex.Message);
                ex.Dispose();
                return false;
            }

            imageWidth = imagePosition >> 16;
            imageHeight = imagePosition & 0x0000FFFF;

            return true;
        }

        private bool GetF7ImageParametersFromCamera(Mode mode, ref uint imageLeft, ref uint imageTop, ref uint imageWidth, ref uint imageHeight, ref PixelFormat pixelFormat, ref uint packetSize)
        {
            if (GetF7ImageParametersFromCamera(mode, ref imageLeft, ref imageTop, ref imageWidth, ref imageHeight) == true)
            {
                // Get the proper mode offset
                uint modeOffset = 0;
                uint modeOffsetRegisterAddress = 0x2E0 + (4 * (uint)mode);
                try
                {
                    modeOffset = m_camera.ReadRegister(modeOffsetRegisterAddress);
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine("Failed to get mode offset. {0}", ex.Message);
                    ex.Dispose();
                    return false;
                }

                modeOffset *= 4;
                modeOffset &= 0x000FFFFF;

                // Get pixel format
                uint regVal = 0;
                try
                {
                    regVal = m_camera.ReadRegister(modeOffset + 0x010);
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine("Failed to get pixel format value from register. {0}", ex.Message);
                    ex.Dispose();
                    return false;
                }

                pixelFormat = (PixelFormat)(0x1 << (int)(31 - (regVal >> 24)));

                // Get packet size
                try
                {
                    regVal = m_camera.ReadRegister(modeOffset + 0x044);
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine("Failed to get packet size value from register. {0}", ex.Message);
                    ex.Dispose();
                    return false;
                }

                packetSize = regVal >> 16;
                return true;
            }
            else
            {
                return false;
            }
        }

        private void DisableImageResizeInformation()
        {          
            /*
            m_preColorProcessingSubsampling.Visible = isVisible;
            m_postColorProcessingSubsampling.Visible = isVisible;
            m_standardBinning.Visible = isVisible;
            m_bayerBinning.Visible = isVisible;
            m_colsRowsLabel.Visible = isVisible;
             * */
            m_preColorProcessingSubsampling.Text = "Pre color processing subsampling: N/A";
            m_postColorProcessingSubsampling.Text = "Post color processing subsampling: N/A";
            m_standardBinning.Text = "Standard binning: Unknown";
            m_bayerBinning.Text = "Bayer binning: Unknown";
            m_colsRowsLabel.Text = "Cols: N/A     Rows: N/A";
        }

        private void OnPacketSizeSpinButtonValueChanged(object sender, EventArgs e)
        {
            try
            {
                m_packetSizeTrackBar.Value = Convert.ToInt32(m_packetSizeSpinButton.Value);
                ResetBandwidthString();

                if (!m_initilizing)
                {
                    m_gigEPacketDelayTrackBar.Enabled = false;
                    m_gigEPacketDelaySpinButton.Enabled = false;

                    if (IsGEV())
                    {
                        lbl_PacketDelayEnable.Visible = true;
                    }
                }
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("The Packet Size trackbar value is out of range. {0}", ex.Message);
            }
        }

        private void OnPixelFormatComboBoxSelectedIndexChanged(object sender, EventArgs e)
        {
            ValidateSettings();
            ResetBandwidthString();
            UpdateImageSize();
        }

        private void ValidateSettings()
        {
            if (IsIIDC())
            {
                ManagedCamera camera = (ManagedCamera)m_camera;

                // Get the values from the screen
                Format7ImageSettings imageSettings = GetF7InfoFromPage();
                if (imageSettings.mode == Mode.NumberOfModes ||
                    imageSettings.width == 0 ||
                    imageSettings.height == 0 ||
                    imageSettings.pixelFormat == PixelFormat.NumberOfPixelFormats)
                {
                    return;
                }

                // Validate the values received 
                bool supported = false;
                Format7PacketInfo packetInfo = new Format7PacketInfo();
                try
                {
                    packetInfo = camera.ValidateFormat7Settings(imageSettings, ref supported);
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine("Packet information is invalid. It might be a bug. Please check ValidateSettings function in Format7Page.cs .{0}", ex.Message);
                    Debug.WriteLine("StackTrace: {0}", ex.StackTrace);
                    ex.Dispose();
                    return;
                }
                ////packetInfo = camera.ValidateFormat7Settings(imageSettings, ref supported);

                // Update the packet info
                if (supported == true)
                {
                    UpdateF7PacketInfo(imageSettings, packetInfo);
                    m_applyButton.Enabled = true;
                }
                else
                {
                    m_applyButton.Enabled = false;
                }
            }
            else if (IsGEV())
            {
                m_applyButton.Enabled = true;
            }
        }

        private Format7ImageSettings GetF7InfoFromPage()
        {
            Format7ImageSettings imageSettings = new Format7ImageSettings();
            if (m_modeComboBox.Items.Count > 0)
            {
                imageSettings.mode = (Mode)m_modeComboBox.SelectedItem;
            }
            else
            {
                imageSettings.mode = Mode.NumberOfModes;
            }

            imageSettings.offsetX = Convert.ToUInt32(m_imageLeftSpinButton.Value);
            imageSettings.offsetY = Convert.ToUInt32(m_imageTopSpinButton.Value);
            imageSettings.width = Convert.ToUInt32(m_imageWidthSpinButton.Value);
            imageSettings.height = Convert.ToUInt32(m_imageHeightSpinButton.Value);
            if (m_pixelFormatComboBox.Items.Count > 0)
            {
                try
                {
                    imageSettings.pixelFormat = m_pixelFormatDictionary[(string)m_pixelFormatComboBox.SelectedItem];
                }
                catch (SystemException ex)
                {
                    imageSettings.pixelFormat = PixelFormat.NumberOfPixelFormats;
                    Debug.WriteLine(ex.Message);
                }
            }
            else
            {
                imageSettings.pixelFormat = PixelFormat.NumberOfPixelFormats;
            }

            return imageSettings;
        }

        private GigEImageSettings GetGigEImageInfoFromPage()
        {
            GigEImageSettings imageSettings = new GigEImageSettings();
            imageSettings.offsetX = Convert.ToUInt32(m_imageLeftSpinButton.Value);
            imageSettings.offsetY = Convert.ToUInt32(m_imageTopSpinButton.Value);
            imageSettings.width = Convert.ToUInt32(m_imageWidthSpinButton.Value);
            imageSettings.height = Convert.ToUInt32(m_imageHeightSpinButton.Value);
            if (m_pixelFormatComboBox.Items.Count > 0)
            {
                try
                {
                    imageSettings.pixelFormat = m_pixelFormatDictionary[(string)m_pixelFormatComboBox.SelectedItem];
                }
                catch (SystemException ex)
                {
                    imageSettings.pixelFormat = PixelFormat.NumberOfPixelFormats;
                    Debug.WriteLine(ex.Message);
                }
            }
            else
            {
                imageSettings.pixelFormat = PixelFormat.NumberOfPixelFormats;
            }

            return imageSettings;
        }

        private bool ValidatePacketSize()
        {
            ulong max = Convert.ToUInt64(m_packetSizeMaxLabel.Text);
            ulong min = Convert.ToUInt64(m_packetSizeMinLabel.Text);
            ulong curr = Convert.ToUInt64(m_packetSizeSpinButton.Value);
            if (min == 0)
            {
                min = 8;
            }

            if (curr > max ||
                curr < min ||
                curr % min != 0)
            {
                m_packetSizeSpinButton.BackColor = Color.Red;
                return false;
            }
            else if (curr == 0)
            {
                m_packetSizeSpinButton.BackColor = Color.Red;
                return false;
            }
            else
            {
                m_packetSizeSpinButton.BackColor = Color.PaleGreen;
                return true;
            }
        }

        private void OnApplyButtonClick(object sender, EventArgs e)
        {
            OnApply();
            UpdateBandwidthInformation();
            m_bNeedReset = true;
        }

        private void OnApply()
        {
            if (m_packetSizeSpinButton.BackColor == Color.Red ||
                m_gigEPacketDelaySpinButton.BackColor == Color.Red ||
                m_imageWidthSpinButton.BackColor == Color.Red ||
                m_imageHeightSpinButton.BackColor == Color.Red ||
                m_imageLeftSpinButton.BackColor == Color.Red ||
                m_imageTopSpinButton.BackColor == Color.Red ||
                m_binningHSpinBtn.BackColor == Color.Red ||
                m_binningVSpinBtn.BackColor == Color.Red)
            {
                MessageBox.Show(
                    "Can not apply this Custom Image setting. Some parameter is invalid.",
                    "Error Applying Custom Image",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
                return;
            }

            if (IsIIDC())
            {
                ApplyF7Settings();
            }
            else if (IsGEV())
            {
                ApplyGigESettings();
            }

            UpdateResizeInformation();
            UpdateModeSettings();
        }

        private void ApplyF7Settings()
        {
            // Cache the current settings
            VideoMode currVideoMode = VideoMode.NumberOfVideoModes;
            FrameRate currFrameRate = FrameRate.NumberOfFrameRates;
            Format7ImageSettings currFmt7Settings = new Format7ImageSettings();
            uint currPacketSize = 0;
            ManagedCamera camera = (ManagedCamera)m_camera;
            try
            {
                camera.GetVideoModeAndFrameRate(ref currVideoMode, ref currFrameRate);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting current video mode and frame rate", ex);
                ex.Dispose();
                return;
            }

            if (currVideoMode == VideoMode.NumberOfVideoModes || currFrameRate == FrameRate.NumberOfFrameRates)
            {
                Debug.WriteLine("Bug: video mode or frame rate is invalid, this should not happen.");
                return;
            }

            if (currVideoMode == VideoMode.VideoModeFormat7)
            {
                // Get the current Format 7 settings
                float percentage = 0.0f; // Don't need to keep this
                try
                {
                    camera.GetFormat7Configuration(currFmt7Settings, ref currPacketSize, ref percentage);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error getting current Format7 configuration", ex);
                    ex.Dispose();
                    return;
                }
            }

            bool needToRestartCamera = true;

            // Stop the camera
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
                    ex.Dispose();
                }
                else
                {
                    string error = string.Format("Error stopping capture. {0}", ex.Message);
                    Debug.WriteLine(error);
                    DialogResult result = MessageBox.Show(
                                          string.Format(
                                          "{0}\r\n Do you wish to continue change the mode? Click ok to continue",
                                          error),
                                          "FlyCapture2 Camera Control", 
                                          MessageBoxButtons.OKCancel, 
                                          MessageBoxIcon.Error);
                    if (result == DialogResult.Cancel)
                    {
                        ex.Dispose();
                        return;
                    }
                    ex.Dispose();
                }
            }

            try
            {
                // Get the image settings from the page
                Format7ImageSettings newFmt7Settings = GetF7InfoFromPage();
                camera.SetFormat7Configuration(newFmt7Settings, (uint)m_packetSizeSpinButton.Value);
            }
            catch (FC2Exception settingFormat7Exception)
            {
                ShowErrorMessageDialog("There was an error setting the Format7 settings, attempting to revert to previous mode...", settingFormat7Exception);

                try
                {
                    if (currVideoMode == VideoMode.VideoModeFormat7)
                    {
                        camera.SetFormat7Configuration(currFmt7Settings, currPacketSize);
                    }
                    else
                    {
                        camera.SetVideoModeAndFrameRate(currVideoMode, currFrameRate);
                    }
                }
                catch (FC2Exception revertingException)
                {
                    ShowErrorMessageDialog("Error reverting to previous mode.", revertingException);
                    revertingException.Dispose();
                } 
            }

            // Settings were applied, or reverted to previous mode
            // Either way, the camera should be able to be restarted successfully
            if (needToRestartCamera)
            {
                try
                {
                    // Restart the camera if it was running beforehand.
                    camera.StartCapture();
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("There was an error restarting the camera.", ex);
                    ex.Dispose();
                }
            }
        }

        private void ApplyGigESettings()
        {
            Debug.Assert(m_camera is ManagedGigECamera, "The interface type must be GigE.");

            ManagedGigECamera camera = (ManagedGigECamera)m_camera;

            // Cache the current image settings in case there is a need
            // to revert back
            GigEImageSettings currImageSettings;
            try
            {                
                currImageSettings = camera.GetGigEImageSettings();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting current image settings", ex);
                ex.Dispose();
                return;
            }

            try
            {                
                // Get the packet size from the GUI
                uint packetSize = (uint)m_packetSizeSpinButton.Value;

                // Get the packet delay from the GUI
                uint packetDelay = (uint)m_gigEPacketDelaySpinButton.Value;

                // Get the binning values from the GUI
                uint horzBinning = (uint)m_binningHSpinBtn.Value;
                uint vertBinning = (uint)m_binningVSpinBtn.Value;

                bool needToRestartCamera = true;

                // Stop the camera
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
                        ex.Dispose();
                    }
                    else
                    {
                        string error = string.Format("Error stopping capture: {0}", ex.Message);
                        Debug.WriteLine(error);
                        DialogResult result = MessageBox.Show(
                            error + Environment.NewLine + "Do you wish to continue to set the image settings?",
                            "FlyCapture2 Camera Control",
                            MessageBoxButtons.YesNo,
                            MessageBoxIcon.Error);
                        if (result == DialogResult.No)
                        {
                            ex.Dispose();
                            return;
                        }
                        ex.Dispose();
                    }
                }

                // Get the current binning settings and decide if there is a need
                // to write the binning settings to the camera
                uint currHorzBinning = 0;
                uint currVertBinning = 0;
                camera.GetGigEImageBinningSettings(ref currHorzBinning, ref currVertBinning);

                if (currHorzBinning != horzBinning || currVertBinning != vertBinning)
                {
                    camera.SetGigEImageBinningSettings(horzBinning, vertBinning);
                }

                // Set the image settings
                GigEImageSettings newImageSettings = GetGigEImageInfoFromPage();
                camera.SetGigEImageSettings(newImageSettings);

                // Set the packet size and packet delay
                GigEProperty packetSizeProp = new GigEProperty();
                packetSizeProp.propType = GigEPropertyType.PacketSize;
                packetSizeProp.value = packetSize;
                camera.SetGigEProperty(packetSizeProp);

                GigEProperty packetDelayProp = new GigEProperty();
                packetDelayProp.propType = GigEPropertyType.PacketDelay;
                packetDelayProp = camera.GetGigEProperty(GigEPropertyType.PacketDelay);
                if (packetDelayProp.max < packetDelay)
                {
                    packetDelayProp.value = packetDelayProp.max;
                }
                else
                {
                    packetDelayProp.value = packetDelay;
                }
                camera.SetGigEProperty(packetDelayProp);

                if (needToRestartCamera)
                {
                    camera.StartCapture();
                }

                UpdateGigEPacketDelaySpinButtonValue();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error applying image settings - attempting to revert to previous mode", ex);
                camera.SetGigEImageSettings(currImageSettings);
                ex.Dispose();
                return;
            }             
        }

        private void UpdateGigEPacketDelaySpinButtonValue()
        {
            try
            {
                Debug.Assert(m_camera is ManagedGigECamera, "The interface type must be GigE.");

                UpdateGigEPacketDelay();

                m_gigEPacketDelayTrackBar.Enabled = true;
                m_gigEPacketDelaySpinButton.Enabled = true;
                lbl_PacketDelayEnable.Visible = false;
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
        }
        
        private void OnMaxImageSizeClick(object sender, EventArgs e)
        {
            ResetBandwidthString();
            Mode selectedMode = (Mode)m_modeComboBox.SelectedItem;
            if (selectedMode == Mode.NumberOfModes)
            {
                return;
            }

            if (IsIIDC())
            {
                ManagedCamera camera = (ManagedCamera)m_camera;
                bool supported = false;
                Format7Info fmt7Info = new Format7Info();
                try
                {
                    fmt7Info = camera.GetFormat7Info(selectedMode, ref supported);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying Format7 information", ex);
                    ex.Dispose();
                }

                ResetImageSize(fmt7Info);
                UpdateImageInformation(fmt7Info);
            }
            else if (IsGEV())
            {
                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                GigEImageSettingsInfo imageSettingsInfo;
                try
                {
                    imageSettingsInfo = camera.GetGigEImageSettingsInfo();
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying GigE image settings information", ex);
                    imageSettingsInfo = new GigEImageSettingsInfo();
                    ex.Dispose();
                }

                ResetImageSize(imageSettingsInfo);
                UpdateGigEImageInfo(imageSettingsInfo);
            }

            ValidateSettings();
            UpdateImageSize();
        }

        private void OnGigEPacketDelaySpinButtonValueChanged(object sender, EventArgs e)
        {
            try
            {
                m_gigEPacketDelayTrackBar.Value = Convert.ToInt32(m_gigEPacketDelaySpinButton.Value);
                ResetBandwidthString();
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("The Packet Size trackbar value is out of range. {0}", ex.Message);
            }
        }

        private void OnGigEPacketDelayTrackBarScroll(object sender, EventArgs e)
        {
            try
            {
                m_gigEPacketDelaySpinButton.Value = m_gigEPacketDelayTrackBar.Value;
                ResetBandwidthString();
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("The Packet Size spin button value is out of range. {0}", ex.Message);
            }
        }

        private void OnBinningSpinBtnValueChanged(object sender, EventArgs e)
        {
            if (IsIIDC() == true || m_skippSpinBtnEvent)
            {
                return;
            }

            ManagedGigECamera camera = (ManagedGigECamera)m_camera;

            // Get the binning values from the GUI
            uint horzBinningVal = (uint)m_binningHSpinBtn.Value;
            uint vertBinningVal = (uint)m_binningVSpinBtn.Value;

            // Get the binning values from the camera
            uint camHorzBinningVal = 0;
            uint camVertBinningVal = 0;

            try
            {
                camera.GetGigEImageBinningSettings(ref camHorzBinningVal, ref camVertBinningVal);
            }
            catch (FC2Exception ex)
            {
                // Error
                ShowErrorMessageDialog("Error getting current binning settings from camera.", ex);
                ex.Dispose();
                return;
            }

            if (camHorzBinningVal == horzBinningVal && camVertBinningVal == vertBinningVal)
            {
                // The camera is already has the correct binning values
                // Set the spin buttons to the right colour
                m_binningVSpinBtn.BackColor = Color.PaleGreen;
                m_binningHSpinBtn.BackColor = Color.PaleGreen;
                m_applyButton.Enabled = true;
                return;
            }

            try
            {
                camera.SetGigEImageBinningSettings(horzBinningVal, vertBinningVal);
            }
            catch (FC2Exception ex)
            {

                m_binningVSpinBtn.BackColor = Color.Red;
                m_binningHSpinBtn.BackColor = Color.Red;
                m_applyButton.Enabled = false;
                ex.Dispose();
                return; 
            }

            // No error
            m_binningVSpinBtn.BackColor = Color.PaleGreen;
            m_binningHSpinBtn.BackColor = Color.PaleGreen;
            m_applyButton.Enabled = true;

            // Get the new imaging mode
            Mode mode;
            try
            {
                mode = camera.GetGigEImagingMode();
                SetActiveModeComboBox(mode);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine(ex.Message);
                ex.Dispose();
            }

            UpdateGigEImageInfo();
            ResetBandwidthString();
            UpdateImageSize();
            OnApply();
        }

        private void UpdateGigEImageInfo()
        {
            ManagedGigECamera camera = (ManagedGigECamera)m_camera;
            GigEImageSettingsInfo imageSettingsInfo;
            try
            {
                imageSettingsInfo = camera.GetGigEImageSettingsInfo();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error querying GigE image information.", ex);
                imageSettingsInfo = new GigEImageSettingsInfo();
                ex.Dispose();
            }

            // Update the GUI with the new settings
            UpdateGigEImageInfo(imageSettingsInfo);
        }

        private void m_imageWidthSpinButton_ValueChanged(object sender, EventArgs e)
        {
            if (!m_disableValidation)
            {
                ValidateSettings();
            }
        }

        private void m_imageHeightSpinButton_ValueChanged(object sender, EventArgs e)
        {
            if (!m_disableValidation)
            {
                ValidateSettings();
            }
        }

        private void OnCaptureAreaControMouseLeave(object sender, EventArgs e)
        {
            string text = string.Format(
                    "Start: ({0},{1}) End:({2},{3}){4}Dimensions: {5} x {6}{7}Cursor: ({8})",
                    m_captureArea.X,
                    m_captureArea.Y,
                    m_captureArea.Right,
                    m_captureArea.Bottom,
                    Environment.NewLine,
                    m_captureArea.Width,
                    m_captureArea.Height,
                    Environment.NewLine,
                    "N/A");
            m_captureAreaAndCursorInfoLabel.Text = text;
            m_maxDrawingAreaSize.Refresh();
        }
    }
}
