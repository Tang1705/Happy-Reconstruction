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
using System.Diagnostics;
using System.Windows.Forms;

using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    internal partial class StrobePropertyControl : UserControl
    {
        private ManagedCameraBase m_camera;
        private uint m_pinNumber;

        public StrobePropertyControl()
        {
            m_camera = null;
            m_pinNumber = 0;
            InitializeComponent();
            m_controlGroupBox.Enabled = false;
        }

        public StrobePropertyControl(ManagedCameraBase camera, uint pinNumber)
        {
            InitializeComponent();
            m_controlGroupBox.Text = string.Format("GPIO {0}", pinNumber);
            m_camera = camera;
            m_pinNumber = pinNumber;
            if (camera == null)
            {
                m_controlGroupBox.Enabled = false;
                return;
            }

            UpdateStrobeControl();
            InitializeControlEvents();
        }

        private void SetTooltips()
        {
            ToolTip m_high = new ToolTip();
            ToolTip m_low = new ToolTip();

            m_high.SetToolTip(m_highPolarityButton, "Rising Edge");
            m_low.SetToolTip(m_lowPolarityButton, "Falling Edge");
        }

        public void SetCamera(ManagedCameraBase camera)
        {
            if (camera == null)
            {
                //bad!
                m_controlGroupBox.Enabled = false;
            }
            else
            {
                m_camera = camera;
            }
        }

        public void UpdateStrobeControl()
        {
            StrobeInfo strobeInfo;
            try
            {
                strobeInfo = m_camera.GetStrobeInfo(m_pinNumber);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error getting strobe information (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }

            StrobeControl strobeControl;
            try
            {
                strobeControl = m_camera.GetStrobe(m_pinNumber);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error getting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }

            m_enableStrobeCheckbox.Checked = strobeControl.onOff;
            bool isPolarityLow = strobeControl.polarity == 0;
            if (isPolarityLow)
            {
                m_lowPolarityButton.Checked = true;
            }
            else
            {
                m_highPolarityButton.Checked = true;
            }

            m_delaySpinButton.Minimum = (decimal)strobeInfo.minValue;
            m_delaySpinButton.Maximum = (decimal)strobeInfo.maxValue;

            m_durationSpinButton.Minimum = (decimal)strobeInfo.minValue;
            m_durationSpinButton.Maximum = (decimal)strobeInfo.maxValue;

            try
            {
                m_delaySpinButton.Value = (decimal)strobeControl.delay;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                m_delaySpinButton.Value = m_delaySpinButton.Minimum;
                Debug.WriteLine("The range (or current value in camera) of strobe delay property is invalid.");
                Debug.WriteLine(ex.StackTrace);
            }

            try
            {
                m_durationSpinButton.Value = (decimal)strobeControl.duration;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                m_durationSpinButton.Value = m_durationSpinButton.Minimum;
                Debug.WriteLine("The range (or current value in camera) of strobe duration property is invalid.");
                Debug.WriteLine(ex.StackTrace);
            }

            UpdateChildControls();
            SetTooltips();
        }

        private void UpdateChildControls()
        {
            m_highPolarityButton.Enabled = m_enableStrobeCheckbox.Checked;
            m_lowPolarityButton.Enabled = m_enableStrobeCheckbox.Checked;
            m_durationSpinButton.Enabled = m_enableStrobeCheckbox.Checked;
            m_delaySpinButton.Enabled = m_enableStrobeCheckbox.Checked;
        }

        private void InitializeControlEvents()
        {
            m_enableStrobeCheckbox.CheckedChanged += new EventHandler(OnEnableStrobeCheckedStatusChanged);
            m_durationSpinButton.ValueChanged += new EventHandler(OnDurationSpinButtonValueChanged);
            m_delaySpinButton.ValueChanged += new EventHandler(OnDelaySpinButtonValueChanged);
            m_lowPolarityButton.CheckedChanged += new EventHandler(PolarityButton_CheckedChanged);
            m_highPolarityButton.CheckedChanged += new EventHandler(PolarityButton_CheckedChanged);
        }

        private void OnEnableStrobeCheckedStatusChanged(object sender, EventArgs e)
        {
            StrobeControl strobeControl;
            try
            {
                strobeControl = m_camera.GetStrobe(m_pinNumber);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error getting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }

            if (strobeControl.onOff == m_enableStrobeCheckbox.Checked)
            {
                // Nothing to do here, because the strobe is already in the
                // proper mode
                return;
            }
            else
            {
                strobeControl.onOff = m_enableStrobeCheckbox.Checked;
                UpdateChildControls();
            }

            try
            {
                m_camera.SetStrobe(strobeControl);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error setting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }
        }

        private void PolarityButton_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (button.Enabled == false ||
                button.Checked == false || //avoid call twice for both check and uncheck bottons
                m_enableStrobeCheckbox.Checked == false)
            {
                return;
            }

            StrobeControl strobeControl;
            try
            {
                strobeControl = m_camera.GetStrobe(m_pinNumber);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error getting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }

            if (m_highPolarityButton.Checked == true)
            {
                strobeControl.polarity = 1;
            }
            else if (m_lowPolarityButton.Checked == true)
            {
                strobeControl.polarity = 0;
            }

            try
            {
                m_camera.SetStrobe(strobeControl);
            }
            catch (FC2Exception ex)
            {
                //Error
                Debug.WriteLine(string.Format(
                                "Error setting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }
        }

        private void OnDelaySpinButtonValueChanged(object sender, EventArgs e)
        {
            if (m_enableStrobeCheckbox.Checked == false)
            {
                return;
            }

            StrobeControl strobeControl;
            try
            {
                strobeControl = m_camera.GetStrobe(m_pinNumber);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error getting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }

            strobeControl.delay = (float)Convert.ToDouble(m_delaySpinButton.Value);
            try
            {
                m_camera.SetStrobe(strobeControl);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error setting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }
        }

        private void OnDurationSpinButtonValueChanged(object sender, EventArgs e)
        {
            if (m_enableStrobeCheckbox.Checked == false)
            {
                return;
            }

            StrobeControl strobeControl;
            try
            {
                strobeControl = m_camera.GetStrobe(m_pinNumber);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error getting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }

            strobeControl.duration = (float)Convert.ToDouble(m_durationSpinButton.Value);
            try
            {
                m_camera.SetStrobe(strobeControl);
            }
            catch (FC2Exception ex)
            {
                m_controlGroupBox.Enabled = false;
                Debug.WriteLine(string.Format(
                                "Error setting strobe (Pin number: {0}): {1}",
                                m_pinNumber,
                                ex.Message));
                ex.Dispose();
                return;
            }
        }
    }
}
