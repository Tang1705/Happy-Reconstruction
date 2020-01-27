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

    //internal partial class GPIOPage : UserControl
    internal partial class GPIOPage : BasePage
    {
        private const int k_numOfPins = 4;
        private RadioButton[] m_inDirectionRadioButtons;
        private RadioButton[] m_outDirectionRadioButtons;
        private StrobePropertyControl[] m_strobeControls;

        public GPIOPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitializePage();
        }

        public override void Refresh()
        {
            // Detach trigger delay events as it enables absolute control by default
            m_tiggerDelaySpinButton.ValueChanged -= new EventHandler(OnTriggerDelaySpinButtonValueChanged);
            m_triggerDelayTrackbar.Scroll -= new EventHandler(OnTriggerDelayTrackbarScroll);

            UpdatePinDirection();
            UpdateTrigger();
            base.Refresh();

            // Update strobe controls
            for (int i = 0; i < k_numOfPins; i++)
            {
                try
                {
                    m_strobeControls[i].UpdateStrobeControl();
                }
                catch
                { }
            }

            // Update pin direction
            try
            {
                UpdatePinDirection();
            }
            catch
            { 
            }

            // atttach trigger delay events
            m_tiggerDelaySpinButton.ValueChanged += new EventHandler(OnTriggerDelaySpinButtonValueChanged);
            m_triggerDelayTrackbar.Scroll += new EventHandler(OnTriggerDelayTrackbarScroll);
        }

        private void InitializePage()
        {
            if (m_camera == null)
            {
                //Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            SetTooltips();
            InitializePinDirectionControls();
            InitializeStrobeControls();
            UpdateTrigger();
            InitializeControlEvents();
        }

        private void SetTooltips()
        {
            // Set tooltips
            ToolTip highPolarityTooltip = new ToolTip();
            ToolTip lowPolarityTooltip = new ToolTip();

            highPolarityTooltip.SetToolTip(m_highPolarityButton, "Rising Edge");
            lowPolarityTooltip.SetToolTip(m_lowPolarityButton, "Falling Edge");
        }

        private void InitializeControlEvents()
        {
            m_enableTriggerDelayCheckBox.CheckedChanged += new EventHandler(OnEnableTriggerDelayCheckedStatusChanged);
            m_triggerSource_0_Button.CheckedChanged += new EventHandler(OnSourceTiggerRadioButtonChanged);
            m_triggerSource_1_Button.CheckedChanged += new EventHandler(OnSourceTiggerRadioButtonChanged);
            m_triggerSource_2_Button.CheckedChanged += new EventHandler(OnSourceTiggerRadioButtonChanged);
            m_triggerSource_3_Button.Click += new EventHandler(OnSourceTiggerRadioButtonChanged);
            m_triggerSource_None_Button.Click += new EventHandler(OnSourceTiggerRadioButtonChanged);
            m_enableTriggerCheckBox.CheckedChanged += new EventHandler(OnEnableTriggerCheckedStatusChanged);
            m_highPolarityButton.CheckedChanged += new EventHandler(TriggerPolarityButton_CheckedChanged);
            m_lowPolarityButton.CheckedChanged += new EventHandler(TriggerPolarityButton_CheckedChanged);
            m_triggerParameterTextBox.TextChanged += new EventHandler(OnTriggerParameterTextChanged);
            m_triggerModeComboBox.SelectedIndexChanged += new EventHandler(OnTriggerModeSelectedIndexChanged);
            m_tiggerDelaySpinButton.ValueChanged += new EventHandler(OnTriggerDelaySpinButtonValueChanged);
            m_triggerDelayTrackbar.Scroll += new EventHandler(OnTriggerDelayTrackbarScroll);
            m_fireSoftwareTriggerButton.Click += new EventHandler(OnFireSoftwareTriggerButtonClick);
        }

        private void InitializeStrobeControls()
        {
            m_strobeControls = new StrobePropertyControl[k_numOfPins];
            for (int i = 0; i < k_numOfPins; i++)
            {
                m_strobeControls[i] = new StrobePropertyControl(m_camera, (uint)i);
                m_strobeControls[i].Location = new Point(
                                               10 + (m_strobeControls[i].Width * (i % 2)), 
                                               20 + (m_strobeControls[i].Height * (i / 2)));
                m_mainGroupBox.Controls.Add(m_strobeControls[i]);
                m_strobeControlPanel.Controls.Add(m_strobeControls[i]);
            }
        }

        private void InitializePinDirectionControls()
        {
            m_inDirectionRadioButtons = new RadioButton[4];
            m_outDirectionRadioButtons = new RadioButton[4];
            for (int i = 0; i < k_numOfPins; i++)
            {
                m_inDirectionRadioButtons[i] = new RadioButton();
                m_inDirectionRadioButtons[i].Text = "In";
                m_inDirectionRadioButtons[i].AutoSize = true;
                m_inDirectionRadioButtons[i].AutoCheck = true;
                m_inDirectionRadioButtons[i].Location = new Point(57, 2);
                m_inDirectionRadioButtons[i].Tag = i;
                m_inDirectionRadioButtons[i].CheckedChanged += new EventHandler(OnPinDirectionChanged);

                m_outDirectionRadioButtons[i] = new RadioButton();
                m_outDirectionRadioButtons[i].Text = "Out";
                m_outDirectionRadioButtons[i].Location = new Point(95, 2);
                m_outDirectionRadioButtons[i].Tag = i;
                m_outDirectionRadioButtons[i].AutoSize = true;
                m_outDirectionRadioButtons[i].AutoCheck = true;
                m_outDirectionRadioButtons[i].CheckedChanged += new EventHandler(OnPinDirectionChanged);
            }

            m_gPIO_0_ControlPanel.Controls.Add(m_inDirectionRadioButtons[0]);
            m_gPIO_0_ControlPanel.Controls.Add(m_outDirectionRadioButtons[0]);
            m_gPIO_1_ControlPanel.Controls.Add(m_inDirectionRadioButtons[1]);
            m_gPIO_1_ControlPanel.Controls.Add(m_outDirectionRadioButtons[1]);
            m_gPIO_2_ControlPanel.Controls.Add(m_inDirectionRadioButtons[2]);
            m_gPIO_2_ControlPanel.Controls.Add(m_outDirectionRadioButtons[2]);
            m_gPIO_3_ControlPanel.Controls.Add(m_inDirectionRadioButtons[3]);
            m_gPIO_3_ControlPanel.Controls.Add(m_outDirectionRadioButtons[3]);
            UpdatePinDirection();
        }

        private void UpdatePinDirection()
        {
            for (uint i = 0; i < k_numOfPins; i++)
            {
                uint direction = 0;
                try
                {
                    direction = m_camera.GetGPIOPinDirection(i);
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine(string.Format("Error getting direction of Pin {0}. {1}", i, ex.Message));
                    ex.Dispose();
                    continue;
                }

                if (direction == 0)
                {
                    m_inDirectionRadioButtons[i].Checked = true;
                }
                else if (direction == 1)
                {
                    m_outDirectionRadioButtons[i].Checked = true;
                }
                else
                {
                    //Error
                    Debug.WriteLine(string.Format("Bug: What is \"{0}\" stand for in direction value?", direction));
                    m_inDirectionRadioButtons[i].Checked = false;
                    m_outDirectionRadioButtons[i].Checked = false;
                }
            }
}

        private void UpdateTrigger()
        {
            TriggerModeInfo triggerInfo;
            try
            {
                triggerInfo = m_camera.GetTriggerModeInfo();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting trigger mode information", ex);
                DisableTrigger();
                ex.Dispose();
                return;
            }

            TriggerMode triggerMode;
            try
            {
                triggerMode = m_camera.GetTriggerMode();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting trigger mode", ex);
                DisableTrigger();
                ex.Dispose();
                return;
            }

            EnableTrigger();

            //Seems unnecessary
            /* 
               m_triggleModeComboBox.Enabled = false;
               m_triggleParameterTextBox.Enabled = false;
               m_enableTriggerDelayCheckBox.Enabled = false;
               m_triggerDelayTrackbar.Enabled = false;
               m_tiggerDelaySpinButton.Enabled = false;
            */

            if (triggerInfo.present == true &&
                triggerInfo.readOutSupported == true &&
                triggerInfo.onOffSupported == true)
            {
                m_enableTriggerCheckBox.Enabled = true;
                m_enableTriggerCheckBox.Checked = triggerMode.onOff;

                UpdateModeComboBox(triggerInfo);
                UpdateActiveTriggerSource(triggerMode);
                UpdateTriggerParameter(triggerMode);
                UpdateTriggerPolarity(triggerMode);
                UpdateTriggerDelay();
                SetActiveModeComboBox(triggerMode);
            }
            else
            {
                m_enableTriggerCheckBox.Enabled = false;
                m_triggerModeComboBox.Enabled = false;
                m_triggerParameterTextBox.Enabled = false;
                m_fireSoftwareTriggerButton.Enabled = false;
                m_enableTriggerDelayCheckBox.Enabled = false;
                m_triggerDelayTrackbar.Enabled = false;
                m_tiggerDelaySpinButton.Enabled = false;
                m_sourcePanel.Enabled = false;
                m_lowPolarityButton.Enabled = false;
                m_highPolarityButton.Enabled = false;
            }
        }

        private void SetActiveModeComboBox(TriggerMode triggerMode)
        {
            int mode = (int)triggerMode.mode;

            // Find the selected mode in the list store and set it
            bool found = false;
            for (int i = 0; i < m_triggerModeComboBox.Items.Count; i++)
            {
                if ((int)m_triggerModeComboBox.Items[i] == mode)
                {
                    m_triggerModeComboBox.SelectedItem = m_triggerModeComboBox.Items[i];
                    found = true;
                    break;
                }
            }
#if (DEBUG)
            if (found == false && m_triggerModeComboBox.Items.Count != 0)
            {
                Debug.WriteLine("Bug: the current mode in camera can not be found in the GPIO page in UI.");
            }
#endif
        }

        private void UpdateTriggerPolarity(TriggerMode triggerMode)
        {
            bool isPolarityLow = triggerMode.polarity == 0;
            if (isPolarityLow == true)
            {
                m_lowPolarityButton.Checked = true;
            }
            else
            {
               m_highPolarityButton.Checked = true;
            }
        }

        private void UpdateTriggerParameter(TriggerMode trigger)
        {
            m_triggerParameterTextBox.Text = trigger.parameter.ToString();
            m_triggerParameterTextBox.Enabled = true;
        }

        private void UpdateModeComboBox(TriggerModeInfo triggerInfo)
        {
            m_triggerModeComboBox.Items.Clear();
            if (triggerInfo.present == true)
            {
                const int numTriggerModes = 16;
                for (int i = 0; i < numTriggerModes; i++)
                {
                    int reverse = numTriggerModes - i - 1;
                    bool modeAvailable = ((triggerInfo.modeMask >> reverse) & 0x1) == 1;
                    if (modeAvailable == true)
                    {
                        m_triggerModeComboBox.Items.Add(i);
                    }
                }

                m_triggerModeComboBox.Enabled = true;
            }
            else
            {
                m_triggerModeComboBox.Enabled = false;
            }
        }

        private void OnEnableTriggerCheckedStatusChanged(object sender, EventArgs e)
        {
            TriggerMode triggerMode;
            try
            {
                triggerMode = m_camera.GetTriggerMode();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting trigger mode", ex);
                ex.Dispose();
                return;
            }

            if (triggerMode.onOff == m_enableTriggerCheckBox.Checked)
            {
                return;
            }

            triggerMode.onOff = m_enableTriggerCheckBox.Checked;
            try
            {
                m_camera.SetTriggerMode(triggerMode);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error setting trigger mode", ex);
                ex.Dispose();
                return;
            }

            try
            {
                m_tiggerDelaySpinButton.ValueChanged -= new EventHandler(OnTriggerDelaySpinButtonValueChanged);
                m_triggerDelayTrackbar.Scroll -= new EventHandler(OnTriggerDelayTrackbarScroll);
                OnTiggerDelayCheckBox();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error updating trigger delay", ex);
                ex.Dispose();
                return;
            }
            finally
            {
                m_tiggerDelaySpinButton.ValueChanged += new EventHandler(OnTriggerDelaySpinButtonValueChanged);
                m_triggerDelayTrackbar.Scroll += new EventHandler(OnTriggerDelayTrackbarScroll);
            }
        }

        private void OnTriggerDelayTrackbarScroll(object sender, EventArgs e)
        {
            //the trackbar is in integer range from 0 to 100, so here we need to do some conversion
            decimal spinButtonRangeValue = m_tiggerDelaySpinButton.Maximum - m_tiggerDelaySpinButton.Minimum;
            decimal convertedValue = (decimal)m_triggerDelayTrackbar.Value * spinButtonRangeValue / (m_triggerDelayTrackbar.Maximum - m_triggerDelayTrackbar.Minimum);
            convertedValue += m_tiggerDelaySpinButton.Minimum; // Minimum number is a extremely small number, not zero.
            try
            {
                m_tiggerDelaySpinButton.Value = convertedValue;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Debug.WriteLine("The trigger delay spin button value is out of range or the delay trackbar range is bad." + ex.Message);
                m_tiggerDelaySpinButton.Value = m_tiggerDelaySpinButton.Minimum;
            }
        }

        private void OnEnableTriggerDelayCheckedStatusChanged(object sender, EventArgs e)
        {
            OnTiggerDelayCheckBox();
            //try
            //{
            //    m_tiggerDelaySpinButton.ValueChanged -= new EventHandler(OnTriggerDelaySpinButtonValueChanged);
            //    OnTiggerDelayCheckBox();
            //}
            //catch (FC2Exception ex)
            //{
            //    ShowErrorMessageDialog("Error updating trigger delay", ex);
            //    ex.Dispose();
            //    return;
            //}
            //finally
            //{
            //    m_tiggerDelaySpinButton.ValueChanged += new EventHandler(OnTriggerDelaySpinButtonValueChanged);
            //}
        }

        private void OnTiggerDelayCheckBox()
        {
            if (m_enableTriggerDelayCheckBox.Checked)
            {
                m_triggerDelayTrackbar.Enabled = true;
                m_tiggerDelaySpinButton.Enabled = true;

                // Update the trigger adjustment
                CameraPropertyInfo propInfo;
                try
                {
                    propInfo = m_camera.GetPropertyInfo(PropertyType.TriggerDelay);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error getting trigger property information.", ex);
                    ex.Dispose();
                    return;
                }

                CameraProperty cameraProp;
                try
                {
                    cameraProp = m_camera.GetProperty(PropertyType.TriggerDelay);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error getting trigger property.", ex);
                    ex.Dispose();
                    return;
                }
                
                /*
                  m_triggerDelayTrackbar.Minimum = (int)(propInfo.absMin);
                  m_triggerDelayTrackbar.Maximum = (int)(propInfo.absMax);
                  m_triggerDelayTrackbar.LargeChange = (int)((propInfo.absMax - propInfo.absMin) / 10.0f);
                  m_triggerDelayTrackbar.SmallChange = (int)((propInfo.absMax - propInfo.absMin) / 100.0f);
                  m_triggerDelayTrackbar.TickFrequency = m_triggerDelayTrackbar.LargeChange;
                
                */
                
                m_tiggerDelaySpinButton.Minimum = (decimal)propInfo.absMin;
                m_tiggerDelaySpinButton.Maximum = (decimal)propInfo.absMax;
                try
                {
                    m_tiggerDelaySpinButton.Value = (decimal)cameraProp.absValue;
                }
                catch (ArgumentOutOfRangeException ex)
                {
                    Debug.WriteLine("The delay value (Spin Button) of trigger is out of range. " + ex.Message);
                    m_tiggerDelaySpinButton.Value = m_tiggerDelaySpinButton.Minimum;
                }

                m_tiggerDelaySpinButton.Increment = (decimal)((propInfo.absMax - propInfo.absMin) / 100.0f);
                m_minTriggerDelay.Text = string.Format("Min trigger delay: {0:0.00000}s", propInfo.absMin);
                m_maxTriggerDelay.Text = string.Format("Max trigger delay: {0:0.00000}s", propInfo.absMax);
            }
            else
            {
                m_triggerDelayTrackbar.Enabled = false;
                m_tiggerDelaySpinButton.Enabled = false;
                m_minTriggerDelay.Text = "Min trigger delay: 0.00000s";
                m_maxTriggerDelay.Text = "Max trigger delay: 0.00000s";
            }
        }

        private void OnTriggerDelaySpinButtonValueChanged(object sender, EventArgs e)
        {
            //the trackbar is in integer range from 0 to 100, so here we need to do some conversion
            decimal spinButtonRangeValue = m_tiggerDelaySpinButton.Maximum - m_tiggerDelaySpinButton.Minimum;
            if (spinButtonRangeValue == 0)
            {
                //both max and min are zero
                m_triggerDelayTrackbar.Value = m_triggerDelayTrackbar.Minimum;
                return;
            }

            double convertedTrackbarPercentage = Convert.ToDouble((m_tiggerDelaySpinButton.Value - m_tiggerDelaySpinButton.Minimum) / spinButtonRangeValue);
            int convertedTrackbarValue = (int)(convertedTrackbarPercentage * (m_triggerDelayTrackbar.Maximum - m_triggerDelayTrackbar.Minimum));
            convertedTrackbarValue += m_triggerDelayTrackbar.Minimum;
            try
            {
                m_triggerDelayTrackbar.Value = convertedTrackbarValue;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Debug.WriteLine("The delay value (Trackbar) of trigger is out of range. " + ex.Message);
                m_triggerDelayTrackbar.Value = m_triggerDelayTrackbar.Minimum;
            }

            SetCameraTriggerDelay();
        }

        private void SetCameraTriggerDelay()
        {
            CameraProperty triggerDelayProperty;
            try
            {
                triggerDelayProperty = m_camera.GetProperty(PropertyType.TriggerDelay);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting trigger delay. ", ex);
                ex.Dispose();
                return;
            }

            triggerDelayProperty.absControl = true;
            triggerDelayProperty.absValue = (float)Convert.ToDouble(m_tiggerDelaySpinButton.Value);
            triggerDelayProperty.onOff = true;

            try
            {
                m_camera.SetProperty(triggerDelayProperty);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error setting trigger delay", ex);
                ex.Dispose();
            }

            //validate whether the delay value changing is effect or not
            UpdateTriggerDelayValue();
        }

        private void UpdateTriggerDelayValue()
        {
            CameraProperty triggerDelayProperty;
            try
            {
                triggerDelayProperty = m_camera.GetProperty(PropertyType.TriggerDelay);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting trigger delay. ", ex);
                ex.Dispose();
                return;
            }

            try
            {
                m_tiggerDelaySpinButton.Value = (decimal)triggerDelayProperty.absValue;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Debug.WriteLine("The range of trigger delay property is invalid.");
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                return;
            }
        }

        private void OnFireSoftwareTriggerButtonClick(object sender, EventArgs e)
        {
            try
            {
                m_camera.FireSoftwareTrigger(false);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error firing software trigger", ex);
                ex.Dispose();
            }
        }

        private void OnPinDirectionChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (button.Enabled == false ||
                button.Checked == false)
            {
                //avoid call twice for both check and uncheck bottons
                return;
            }

            OnRadioPinDirectionChanged((int)button.Tag);
        }

        private void OnRadioPinDirectionChanged(int pin)
        {
            if (m_inDirectionRadioButtons[pin].Enabled == false
                || m_outDirectionRadioButtons[pin].Enabled == false)
            {
                return;
            }

            uint dirction;
            try
            {
                dirction = m_camera.GetGPIOPinDirection((uint)pin);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting GPIO pin direction", ex);
                ex.Dispose();
                return;
            }

            if (m_inDirectionRadioButtons[pin].Checked == true
                && dirction == 1)
            {
                // Direction is in and it needs to be set to the camera
                try
                {
                    m_camera.SetGPIOPinDirection((uint)pin, 0);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog(string.Format("Error setting GPIO pin {0} to input direction", pin), ex);
                    ex.Dispose();
                    return;
                }
            }
            else if (m_outDirectionRadioButtons[pin].Checked == true
                     && dirction == 0)
            {
                // Direction is out and it needs to be set to the camera
                try
                {
                    m_camera.SetGPIOPinDirection((uint)pin, 1);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog(string.Format("Error setting GPIO pin {0} to output direction", pin), ex);
                    ex.Dispose();
                    return;
                }
            }

            //validate changing, update related controls
            if (m_strobeControls      != null && 
                m_strobeControls[pin] != null)
            {
                m_strobeControls[pin].UpdateStrobeControl();
            }
        }

        private void OnSourceTiggerRadioButtonChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (button.Checked == false)
            {
                //avoid call twice for both check and uncheck actions
                return;
            }

            TriggerMode triggerModeStruct;
            try
            {
                triggerModeStruct = m_camera.GetTriggerMode();
            }
            catch (FC2Exception ex)
            {
                // Error
                ShowErrorMessageDialog("Error getting trigger mode", ex);
                ex.Dispose();
                return;
            }

            uint pin = Convert.ToUInt32(button.Tag.ToString());

            if (triggerModeStruct.source == pin)
            {
                // The selected pin is the current source, nothing to be done here
                return;
            }

            // Test the pin if it can be set as an input
            bool bOk = TestPinInputSuccess((int)pin);
            if (bOk == false)
            {
                button.Enabled = false;
                button.Checked = false;
                return;
            }

            triggerModeStruct.source = pin;
            try
            {
                m_camera.SetTriggerMode(triggerModeStruct);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error setting trigger mode.", ex);
                ex.Dispose();
            }

            UpdateTrigger();
            for (uint i = 0; i < k_numOfPins; i++)
            {
                if (pin == i)
                {
                    m_strobeControls[i].Enabled = false;
                }
                else
                {
                    m_strobeControls[i].Enabled = true;
                }
            }
        }

        private bool TestPinInputSuccess(int pin)
        {
            const uint k_pioDirection = 0x11f8;
            uint pioDirectionVal = 0;
            try
            {
                // Read the GPIO pin direction register
                pioDirectionVal = m_camera.ReadRegister(k_pioDirection);
            }
            catch (FC2Exception ex)
            {
                ex.Dispose();
                return false;
            }

            pioDirectionVal &= ~(0x80000000 >> pin);
            try
            {
                // Set the appropriate pin as an input
                m_camera.WriteRegister(k_pioDirection, pioDirectionVal);
            }
            catch (FC2Exception ex)
            {
                ex.Dispose();
                return false;
            }

            try
            {
                // Read the register back
                pioDirectionVal = m_camera.ReadRegister(k_pioDirection);
            }
            catch (FC2Exception ex)
            {
                ex.Dispose();
                return false;
            }

            // Check if the pin was successfully set as an input
            if ((pioDirectionVal & (0x80000000 >> pin)) != 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        private void TriggerPolarityButton_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (button.Checked == false)
            {
                //avoid call twice for both check and uncheck actions
                return;
            }

            TriggerMode triggerModeStruct;
            try
            {
                triggerModeStruct = m_camera.GetTriggerMode();
            }
            catch (FC2Exception ex)
            {
                this.Enabled = false;
                Debug.WriteLine("Error getting trigger polarity. " + ex.Message);
                ex.Dispose();
                return;
            }

            if (m_highPolarityButton.Checked == true &&
                triggerModeStruct.polarity != 1)
            {
                triggerModeStruct.polarity = 1;
            }
            else if (m_lowPolarityButton.Checked == true &&
                     triggerModeStruct.polarity != 0)
            {
                triggerModeStruct.polarity = 0;
            }

            try
            {
                m_camera.SetTriggerMode(triggerModeStruct);
            }
            catch (FC2Exception ex)
            {
                //Error
                Debug.WriteLine("Error setting trigger mode." + ex.Message);
                ex.Dispose();
            }
        }

        private void UpdateActiveTriggerSource(TriggerMode triggerMode)
        {
            uint pinToDisable = triggerMode.source;

            if (pinToDisable < k_numOfPins)
            {
                switch (pinToDisable)
                {
                    case 0:
                        m_triggerSource_0_Button.Checked = true;
                        break;
                    case 1:
                        m_triggerSource_1_Button.Checked = true;
                        break;
                    case 2:
                        m_triggerSource_2_Button.Checked = true;
                        break;
                    case 3:
                        m_triggerSource_3_Button.Checked = true;
                        break;
                }
            }
            else
            {
                m_triggerSource_None_Button.Checked = true;
            }
        
            for (uint i = 0; i < k_numOfPins; i++)
            {
                if (i == pinToDisable)
                {
                    m_strobeControls[i].Enabled = false;
                }
                else
                {
                    m_strobeControls[i].Enabled = true;
                }
            }
        }

        private void OnTriggerModeSelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_triggerModeComboBox.SelectedItem == null)
            {
                //nothing is selected
                return;
            }

            int mode = (int)m_triggerModeComboBox.SelectedItem;
            TriggerMode triggerModeStruct;
            try
            {
                triggerModeStruct = m_camera.GetTriggerMode();
            }
            catch (FC2Exception ex)
            {
                this.Enabled = false;
                Debug.WriteLine("Error getting trigger mode. " + ex.Message);
                ex.Dispose();
                return;
            }

            triggerModeStruct.mode = (uint)mode;
            try
            {
                m_camera.SetTriggerMode(triggerModeStruct);
            }
            catch (FC2Exception ex)
            {
                //Error
                Debug.WriteLine("Error setting trigger mode." + ex.Message);
                ex.Dispose();
            }
        }

        private void OnTriggerParameterTextChanged(object sender, EventArgs e)
        {
            uint parameter = 0;
            try
            {
                parameter = Convert.ToUInt32(m_triggerParameterTextBox.Text);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Invalid parameter value");
                return;
            }

            TriggerMode triggerModeStruct;
            try
            {
                triggerModeStruct = m_camera.GetTriggerMode();
            }
            catch (FC2Exception ex)
            {
                this.Enabled = false;
                Debug.WriteLine("Error getting trigger mode. " + ex.Message);
                ex.Dispose();
                return;
            }

            triggerModeStruct.parameter = parameter;
            try
            {
                m_camera.SetTriggerMode(triggerModeStruct);
            }
            catch (FC2Exception ex)
            {
                //Error
                Debug.WriteLine("Error setting trigger mode." + ex.Message);
                ex.Dispose();
            }
        }

        private void UpdateTriggerDelay()
        {
            CameraPropertyInfo propInfo;
            try
            {
                propInfo = m_camera.GetPropertyInfo(PropertyType.TriggerDelay);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting trigger information", ex);
                ex.Dispose();
                return;
            }

            CameraProperty cameraProperty;
            try
            {
                cameraProperty = m_camera.GetProperty(PropertyType.TriggerDelay);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting trigger", ex);
                ex.Dispose();
                return;
            }

            if (propInfo.onOffSupported == true)
            {
                m_enableTriggerDelayCheckBox.Checked = cameraProperty.onOff;
                OnTiggerDelayCheckBox();
            }
            else
            {
                DisableTriggerDelay();
            }
        }

        private void EnableTrigger()
        {
            m_enableTriggerCheckBox.Enabled = true;
            m_triggerModeComboBox.Enabled = true;
            m_triggerParameterTextBox.Enabled = true;
            m_sourcePanel.Enabled = true;
            m_lowPolarityButton.Enabled = true;
            m_highPolarityButton.Enabled = true;
            EnableTriggerDelay();
        }

        private void EnableTriggerDelay()
        {
            m_enableTriggerDelayCheckBox.Enabled = true;
            m_triggerDelayTrackbar.Enabled = true;
            m_tiggerDelaySpinButton.Enabled = true;
            m_fireSoftwareTriggerButton.Enabled = true;
        }

        private void DisableTrigger()
        {
            m_enableTriggerCheckBox.Enabled = false;

            m_triggerModeComboBox.Enabled = false;
            m_triggerParameterTextBox.Enabled = false;
            m_sourcePanel.Enabled = false;
            m_lowPolarityButton.Enabled = false;
            m_highPolarityButton.Enabled = false;
            DisableTriggerDelay();
        }

        private void DisableTriggerDelay()
        {
            m_enableTriggerDelayCheckBox.Checked = false;
            m_enableTriggerDelayCheckBox.Enabled = false;
            m_triggerDelayTrackbar.Enabled = false;
            m_tiggerDelaySpinButton.Enabled = false;
            m_fireSoftwareTriggerButton.Enabled = false;
        }        
    }
}
