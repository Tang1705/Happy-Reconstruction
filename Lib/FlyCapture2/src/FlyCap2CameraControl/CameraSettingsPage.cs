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

    // internal partial class CameraSettingsPage : UserControl   //this line is only for opening design view
    internal partial class CameraSettingsPage : BasePage
    {
        private const int SpacingPixels = 25;
        private const uint NumProperties = 16;
        private const uint MaxPowerRegRetryCount = 10;

        private bool m_isTemperatureAvailable = false;
        private bool m_needToCheckPowerReg = false;
        private uint m_powerRegCheckCount = 0;
         
        private SinglePropertyControl[] m_properties;

        private Timer m_updateTimer = new Timer();

        public CameraSettingsPage(ManagedCameraBase initCamera)
        {
            SetCamera(initCamera);
            InitializeComponent();
            InitializePage();
        }

        private void OnTimer(Object o, EventArgs eventArgs)
        {
            if (m_camera == null)
            {
                //Bad!
                return;
            }

            if (m_isPageSelected)
            {
                UpdatePropertyValues();
            }
        }

        private void InitializePage()
        {
            InitializeAllPropertyControls();
            AddAllControlsToGroupBox();
            if (m_camera == null)
            {
                //Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            InitializePageData();
            InitializeControlEvents();

            m_updateTimer.Tick += new EventHandler(OnTimer);
            m_updateTimer.Interval = 100;
            m_updateTimer.Start();
        }

        private void InitializeControlEvents()
        {
            m_absoluteModeCheckBox.CheckedChanged += new EventHandler(AbsoluteModeCheckBox_CheckedChanged);
            m_powerCheckBox.Click += new EventHandler(OnPowerCheckedStatusChanged);
        }

        private void InitializePageData()
        {
            m_absoluteModeCheckBox.Checked = true;
            m_powerCheckBox.Checked = GetCameraPower();
            m_powerCheckBox.Enabled = IsCameraPowerAvailable();
            m_isTemperatureAvailable = InitializeCameraTemperatureInformation();
        }

        private void AddAllControlsToGroupBox()
        {
            // Add all controller to the Main Group Box
            m_mainGroupBox.Controls.Add(m_absoluteModeCheckBox);
            m_mainGroupBox.Controls.Add(m_onePushLabel);
            m_mainGroupBox.Controls.Add(m_onOffLabel);
            m_mainGroupBox.Controls.Add(m_autoLabel);
            for (int i = 0; i < NumProperties; i++)
            {
                m_mainGroupBox.Controls.Add(m_properties[i]);
            }

            m_mainGroupBox.Controls.Add(m_powerCheckBox);
            m_mainGroupBox.Controls.Add(m_temperatureLabel);
            m_mainGroupBox.Controls.Add(m_temperatureValue);
        }

        private void InitializeAllPropertyControls()
        {
            int initialYLocation = 45;
            initialYLocation = InitialzePropertyControlsWithTrackbar(initialYLocation);
            InitialzePowerControl(initialYLocation);
            initialYLocation += SpacingPixels;
            InitializeTemperatureControl(initialYLocation);
        }

        private void InitializeTemperatureControl(int controlPositionY)
        {
            // Add Temperature Label
            this.m_temperatureLabel.AutoSize = true;
            this.m_temperatureLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, (byte)0);
            this.m_temperatureLabel.Location = new System.Drawing.Point(11, controlPositionY);
            this.m_temperatureLabel.Name = "m_temperatureLabel";
            this.m_temperatureLabel.Text = "Temperature";

            this.m_temperatureValue.AutoSize = true;
            this.m_temperatureValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, (byte)0);
            this.m_temperatureValue.Location = new System.Drawing.Point(this.m_temperatureLabel.Size.Width, controlPositionY);
            this.m_temperatureValue.Name = "m_temperatureValue";
            this.m_temperatureValue.Text = "N/A";
        }

        private void InitialzePowerControl(int controlPositionY)
        {
            // m_powerCheckBox
            this.m_powerCheckBox.AutoSize = true;
            this.m_powerCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, (byte)0);
            this.m_powerCheckBox.Location = new System.Drawing.Point(11, controlPositionY);
            this.m_powerCheckBox.Name = "m_propertyLabel";
            this.m_powerCheckBox.Size = new System.Drawing.Size(100, 20);

            this.m_powerCheckBox.Text = "Power";
            this.m_powerCheckBox.AutoSize = false;
            this.m_powerCheckBox.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.m_powerCheckBox.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
        }

        private int InitialzePropertyControlsWithTrackbar(int controlPositionY)
        {
            //property controls
            m_properties = new SinglePropertyControl[NumProperties];
            this.m_properties[0] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Brightness);
            this.m_properties[1] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.AutoExposure, "Exposure");
            this.m_properties[2] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Sharpness);
            this.m_properties[3] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Hue);
            this.m_properties[4] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Saturation);
            this.m_properties[5] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Gamma);
            this.m_properties[6] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Iris);
            this.m_properties[7] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Focus);
            this.m_properties[8] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Zoom);
            this.m_properties[9] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Pan);
            this.m_properties[10] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Tilt);
            this.m_properties[11] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Shutter);
            this.m_properties[12] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.Gain);
            this.m_properties[13] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.FrameRate);
            this.m_properties[14] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.WhiteBalance, "W.B.(Red)");
            this.m_properties[15] = new SinglePropertyControl(m_camera, FlyCapture2Managed.PropertyType.WhiteBalance, "W.B.(Blue)", true);

            for (int i = 0; i < m_properties.Length; i++)
            {
                this.m_properties[i].Location = new System.Drawing.Point(7, controlPositionY);
                this.m_properties[i].Anchor = (System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right | System.Windows.Forms.AnchorStyles.Left);
                controlPositionY += SpacingPixels;
            }

            return controlPositionY;
        }

        private void AbsoluteModeCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            UpdatePropertyMode();
        }

        private void OnPowerCheckedStatusChanged(object sender, EventArgs e)
        {
            SetCameraPower(m_powerCheckBox.Checked);
        }

        private void UpdatePropertyMode()
        {
            for (int i = 0; i < m_properties.Length; i++)
            {
                m_properties[i].SetPropertyAbsoluteMode(m_absoluteModeCheckBox.Checked);
            }
        }
        
        private void UpdatePropertyValues()
        {
            for (int i = 0; i < m_properties.Length; i++)
            {
                m_properties[i].UpdateComponentValues();
            }

            if (m_powerCheckBox.Enabled)
            {
                bool powerRegVal = GetCameraPower();
                if (m_needToCheckPowerReg == true)
                {
                    if (powerRegVal == m_powerCheckBox.Checked)
                    {
                        m_needToCheckPowerReg = false;
                        m_powerRegCheckCount = 0;
                    }
                    else
                    {
                        m_powerRegCheckCount++;
                        if (m_powerRegCheckCount > MaxPowerRegRetryCount)
                        {
                            MessageBox.Show(
                                "Failed to turn on camera.",
                                "Error setting power",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);

                            //set current power check box to the value which is in the camera
                            m_needToCheckPowerReg = false;
                            m_powerRegCheckCount = 0;
                            m_powerCheckBox.Checked = powerRegVal;
                        }
                    }
                }
                else
                {
                    m_powerCheckBox.Checked = powerRegVal;
                }
            }

            if (m_isTemperatureAvailable)
            {
                UpdateTemperatureValue();
            }
        }

        private void UpdateTemperatureValue()
        {
            Debug.Assert(m_camera != null, "Camera can not be null.");
            try
            {
                CameraProperty camProp = m_camera.GetProperty(PropertyType.Temperature);
                if (camProp != null && camProp.present)
                {
                    double kelvins = camProp.valueA / 10.0;
                    double celcius = kelvins - 273.15;
                    double fahrenheit = ((celcius * 9.0) / 5.0) + 32.0;
                    m_temperatureValue.Text = string.Format(" {0:0.##}K / {1:0.##}°C / {2:0.##}°F", kelvins, celcius, fahrenheit);
                }
                else
                {
                    m_temperatureValue.Text = "Not available";
                }
            }
            catch (FC2Exception ex)
            {
                if (ex.Type == ErrorType.PropertyNotPresent)
                {
                    m_temperatureValue.Text = "Not available";
                }
                else
                {
                    m_temperatureValue.Text = "N/A";
                }
                ex.Dispose();
            }            
        }

        private bool GetCameraPower()
        {
            Debug.Assert(m_camera != null, "Camera can not be null.");
            const uint PowerReg = 0x610;
            uint powerRegVal = 0;
            try
            {
                powerRegVal = m_camera.ReadRegister(PowerReg);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine(string.Format("Error reading camera power register. {0}", ex.Message));
                ex.Dispose();
                return false;
            }

            return (powerRegVal & (0x1 << 31)) != 0;
        }

        private bool IsCameraPowerAvailable()
        {
            Debug.Assert(m_camera != null, "Camera can not be null.");
            const uint PowerInqReg = 0x400;
            uint powerInqRegVal = 0;
            try
            {
                powerInqRegVal = m_camera.ReadRegister(PowerInqReg);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine(string.Format("Error reading camera power register. {0}", ex.Message));
                ex.Dispose();
                return false;
            }

            return (powerInqRegVal & 0x00008000) != 0;
        }

        private void SetCameraPower(bool isOn)
        {
            Debug.Assert(m_camera != null, "Camera can not be null.");
            const uint PowerReg = 0x610;
            uint powerRegValue = (isOn == true) ? 0x80000000 : 0x0;
            try
            {
                m_camera.WriteRegister(PowerReg, powerRegValue);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine(string.Format("Error writing camera power register. {0}", ex.Message));
                ex.Dispose();
                return;
            }

            Debug.WriteLine("Set power: " + (isOn ? "On" : "Off"));
            m_needToCheckPowerReg = true;
        }

        private bool InitializeCameraTemperatureInformation()
        {
            Debug.Assert(m_camera != null, "Camera can not be null.");
            try
            {
                m_camera.GetPropertyInfo(PropertyType.Temperature);
            }
            catch (FC2Exception ex)
            {
                if (ex.CauseType == ErrorType.Undefined)
                {
                    //hide temperature control
                    m_temperatureLabel.Visible = false;
                    m_temperatureValue.Visible = false;
                    ex.Dispose();
                    return false;
                }
                else
                {
                    string error = "Error getting camera temperature.";
                    Debug.WriteLine(error);
                    ShowErrorMessageDialog(error, ex);
                    ex.Dispose();
                    return false;
                }
            }

            return true;
        }
    }
}
