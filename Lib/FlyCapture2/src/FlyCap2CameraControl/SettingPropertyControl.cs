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
    internal partial class SinglePropertyControl : UserControl
    {
        private PropertyType m_propType;
        private ManagedCameraBase m_camera;
        private CameraPropertyInfo m_propInfo;

        private bool m_isAbsMode = false;
        private bool m_isEnabled = false;
        private bool m_pauseUpdates = false;
        private bool m_useValueB = false;
        private bool m_isSpinBtnEventActivated = false;

        public SinglePropertyControl(ManagedCameraBase initCamera, PropertyType property)
        {
            m_propType = property;
            m_camera = initCamera;
            
            InitializeComponent();
            InitializePropertyData(property.ToString());
        }

        public SinglePropertyControl(ManagedCameraBase initCamera, PropertyType property, string propertyName)
        {
            m_propType = property;
            m_camera = initCamera;

            InitializeComponent();
            InitializePropertyData(propertyName);
        }

        public SinglePropertyControl(ManagedCameraBase initCamera, PropertyType property, string propertyName, bool isUsingValueB)
        {
            m_propType = property;
            m_camera = initCamera;
            m_useValueB = isUsingValueB;
            InitializeComponent();
            InitializePropertyData(propertyName);
        }

        public void SetPropertyAbsoluteMode(bool isAbsModeOn)
        {
            if (m_isEnabled)
            {
                // Switch mode Need to change value
                // We don't want change-value event bother the
                // value in the camera, so we need to detach
                // this event now.
                DetachSpinButtonEvent();

                if (m_propInfo.absValSupported && isAbsModeOn)
                {
                    EnableAbsoluteMode();
                }
                else
                {
                    DisableAbsoluteMode();
                }

                UpdateSpinButtonValueFromCamera();
                UpdateTrackBarValueFromSpinButton();

                // After the value update finish, attach change value event.
                AttachSpinButtonEvent();
            }
        }

        public void UpdateComponentValues()
        {
            if (!m_pauseUpdates)
            {
                UpdateControls();
            }
        }

        private void SetPropertyVisibility(bool show)
        {
            m_propertyTrackBar.Visible = show;
            m_propertySpinButton.Visible = show;
            TabStop = show;
            if (m_isAbsMode == true)
            {
                m_propertyAbsUnitLabel.Visible = show;
            }
            else
            {
                m_propertyAbsUnitLabel.Visible = false;
            }

            SetCheckBoxVisibility(show);
        }

        private void SetCheckBoxVisibility(bool show)
        {
            if (m_propertyAutoCheckBox.Visible != show)
            {
                m_propertyAutoCheckBox.Visible = show;
            }

            if (m_propertyOnOffCheckBox.Visible != show)
            {
                m_propertyOnOffCheckBox.Visible = show;
            }

            if (m_propertyOnePushButton.Visible != show)
            {
                m_propertyOnePushButton.Visible = show;
            }
        }

        private void EnableAbsoluteMode()
        {
            m_isAbsMode = true;
            m_propertyAbsUnitLabel.Visible = true;
            m_propertySpinButton.DecimalPlaces = 3;            
            UpdateSpinButtonRange(m_propInfo);
            m_propertyAbsUnitLabel.Visible = true;
        }

        private void DisableAbsoluteMode()
        {
            m_isAbsMode = false;
            m_propertyAbsUnitLabel.Visible = false;
            m_propertySpinButton.DecimalPlaces = 0;
            UpdateSpinButtonRange(m_propInfo);
            m_propertyAbsUnitLabel.Visible = false;
        }
        
        private void InitializePropertyData(string propertyName)
        {
            m_propertyLabel.Text = propertyName;
            if (m_camera == null)
            {
                SetPropertyVisibility(false);
                return;
            }

            if (UpdateControls())
            {
                m_propertyAbsUnitLabel.Text = m_propInfo.unitAbbr;
                InitializeCheckBoxes(m_propInfo);
                SetPropertyAbsoluteMode(true);
            }
            else
            {
                Debug.WriteLine("The " + m_propType + " property is not supported in this camera.");
            }

            InitializeControlEvents();
        }

        private void InitializeControlEvents()
        {
            /*
             * See UpdateCheckBoxes(bool) function
             * 
            m_propertyOnePushCheckBox.CheckedChanged += new EventHandler(OnPropertyOnePushCheckedStatusChanged);
            m_propertyOnOffCheckBox.CheckedChanged += new EventHandler(OnPropertyOnOffCheckedStatusChanged);
            m_propertyAutoCheckBox.CheckedChanged += new EventHandler(OnPropertyAutoCheckedStatusChanged);
            */
            m_propertyTrackBar.Scroll += new EventHandler(OnPropertyTrackBarScroll);
            m_propertySpinButton.Leave += new EventHandler(OnPropertySpinButtonLeave);
            m_propertySpinButton.KeyDown += new KeyEventHandler(OnPropertySpinButtonKeyDown);
        }

        private bool UpdateSpinButtonValue(CameraProperty camProp)
        {
            DetachSpinButtonEvent();
            decimal newValue = 0;
            if (m_isAbsMode)
            {
                newValue = Convert.ToDecimal(camProp.absValue);

                if (newValue == m_propertySpinButton.Value)
                {
                    AttachSpinButtonEvent();
                    return false;
                }
            }
            else
            {
                uint rawValueToUse = 0;
                if (camProp.type == PropertyType.Shutter)
                {
                    // Bug 19306
                    rawValueToUse = camProp.valueA + (camProp.valueB << 12);
                }
                else
                {
                    rawValueToUse = m_useValueB ? camProp.valueB : camProp.valueA;
                }

                newValue = Convert.ToDecimal(rawValueToUse);

                if (newValue == m_propertySpinButton.Value)
                {
                    AttachSpinButtonEvent();
                    return false;
                }
            }

            SetSpinButtonValue(newValue);
            AttachSpinButtonEvent();
            return true;
        }

        private void UpdateTrackBarValueFromSpinButton()
        {
            float trackBarRangeValue = (float)(m_propertyTrackBar.Maximum - m_propertyTrackBar.Minimum);
            float spinButtonRangeValue = (float)(m_propertySpinButton.Maximum - m_propertySpinButton.Minimum);
            if (spinButtonRangeValue == 0)
            {
                return;
            }

            int newValue = Convert.ToInt32(((float)(m_propertySpinButton.Value - m_propertySpinButton.Minimum) * trackBarRangeValue / spinButtonRangeValue)) + m_propertyTrackBar.Minimum;
            SetTrackBarValue(newValue);
        }

        private void SetTrackBarValue(int newValue)
        {
            if (newValue > m_propertyTrackBar.Maximum)
            {
                m_propertyTrackBar.Value = m_propertyTrackBar.Maximum;
            }
            else if (newValue < m_propertyTrackBar.Minimum)
            {
                m_propertyTrackBar.Value = m_propertyTrackBar.Minimum;
            }
            else
            {
                try
                {
                    m_propertyTrackBar.Value = newValue;
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine(string.Format("Bug: {0} property value is invalid. This should not happen. {1}", m_propType, ex.Message));
                }
            }
        }

        private void UpdateSpinButtonValueFromCamera()
        {
            CameraProperty camProp = m_camera.GetProperty(m_propType);
            UpdateSpinButtonValue(camProp);
        }

        private void UpdateSpinButtonValueFromTrackBar()
        {
            DetachSpinButtonEvent();
            // Forcing +/-1 increment for PAN control - Bug 18670
            if (m_propType == PropertyType.Pan)
            {
                if (m_propertyTrackBar.Value > m_propertySpinButton.Value)
                {
                    if ((m_propertyTrackBar.Value + 1) > m_propertyTrackBar.Maximum)
                    {
                        m_propertyTrackBar.Value = m_propertyTrackBar.Maximum;
                    }
                    else
                    {
                        m_propertyTrackBar.Value = (int)m_propertySpinButton.Value + 1;
                    }
                }
                else
                {
                    if ((m_propertyTrackBar.Value - 1) < m_propertyTrackBar.Minimum)
                    {
                        m_propertyTrackBar.Value = m_propertyTrackBar.Minimum;
                    }
                    else
                    {
                        m_propertyTrackBar.Value = (int)m_propertySpinButton.Value - 1;
                    }
                }
            }
            float spinButtonRangeValue = (float)(m_propertySpinButton.Maximum - m_propertySpinButton.Minimum);
            float trackBarRangeValue = (float)(m_propertyTrackBar.Maximum - m_propertyTrackBar.Minimum);
            if (trackBarRangeValue == 0)
            {
                return;
            }

            decimal newValue = Convert.ToDecimal(((float)(m_propertyTrackBar.Value * spinButtonRangeValue) / trackBarRangeValue)) + m_propertySpinButton.Minimum;
            SetSpinButtonValue(newValue);
            SetPropertyValue();
            AttachSpinButtonEvent();
        }

        private void SetSpinButtonValue(decimal newValue)
        {
            if (newValue > m_propertySpinButton.Maximum)
            {
                Debug.WriteLine(String.Format("Warning: {0} - {1} is greater than max value of {2}", m_propType, newValue, m_propertySpinButton.Maximum));
                m_propertySpinButton.Value = m_propertySpinButton.Maximum;
            }
            else if (newValue < m_propertySpinButton.Minimum)
            {
                Debug.WriteLine(String.Format("Warning: {0} - {1} is less than max value of {2}", m_propType, newValue, m_propertySpinButton.Minimum));
                m_propertySpinButton.Value = m_propertySpinButton.Minimum;
            }
            else
            {
                try
                {
                    m_propertySpinButton.Value = newValue;
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine(string.Format("Bug: {0} property value is invalid. {1}", m_propType, ex.Message));
                    return;
                }
            }
        }

        private bool UpdateControls()
        {
            try
            {
                m_propInfo = m_camera.GetPropertyInfo(m_propType);
                if (!m_propInfo.present)
                {
                    m_isEnabled = false;
                    SetPropertyVisibility(false);
                    return false;
                }

                m_isEnabled = true;
                SetPropertyVisibility(true);
                InitializeCheckBoxes(m_propInfo);
                CameraProperty camProp = m_camera.GetProperty(m_propType);

                UpdateSpinButtonRange(m_propInfo);

                if (UpdateSpinButtonValue(camProp))
                {
                    // If UpdateSpinButtonValue() returns true, it means the value has been changed
                    UpdateTrackBarValueFromSpinButton();
                }

                UpdateCheckBoxes(camProp);
                UpdateUnitText(m_propInfo);
            }
            catch (FC2Exception ex)
            {
                if (ex.Type != ErrorType.PropertyNotPresent)
                {
                    Debug.WriteLine(DateTime.Now + " - Update for " + m_propType + " failed with: " + ex.CauseType + " (" + ex.Message + ")");
                    Debug.WriteLine(ex.NativeErrorTrace);
                }

                m_isEnabled = false;
                SetPropertyVisibility(false);
                ex.Dispose();
                return false;
            }
            // This was added to disable controls on a convert to decimal exception. Bug# 26376.
            catch (ArgumentException ex)
            {
                m_isEnabled = false;
                SetPropertyVisibility(false);
                return false;
            }

            return true;
        }

        private void UpdateUnitText(CameraPropertyInfo camPropInfo)
        {
            m_propertyAbsUnitLabel.Text = camPropInfo.unitAbbr;
        }

        private void UpdateSpinButtonRange(CameraPropertyInfo camPropInfo)
        {
            try
            {
                if (m_isAbsMode)
                {
                    decimal newMin = Convert.ToDecimal(camPropInfo.absMin);
                    decimal newMax = Convert.ToDecimal(camPropInfo.absMax);

                    if (newMin != m_propertySpinButton.Minimum ||
                        newMax != m_propertySpinButton.Maximum)
                    {
                        m_propertySpinButton.Minimum = newMin;
                        m_propertySpinButton.Maximum = newMax;
                    }
                }
                else
                {
                    decimal newMin = Convert.ToDecimal(camPropInfo.min);
                    decimal newMax = Convert.ToDecimal(camPropInfo.max);

                    if (newMin != m_propertySpinButton.Minimum ||
                        newMax != m_propertySpinButton.Maximum)
                    {
                        m_propertySpinButton.Minimum = newMin;
                        m_propertySpinButton.Maximum = newMax;
                    }
                }

            }
            catch (System.OverflowException ex)
            {
                throw new ArgumentException("Camera property min/max value was either too large or too small.");
            }

            // Forcing +/-1 increment for PAN control - Bug 18670
            if (camPropInfo.type == PropertyType.Pan)
            {
                m_propertyTrackBar.Maximum = (int)m_propertySpinButton.Maximum;
                m_propertyTrackBar.Minimum = (int)m_propertySpinButton.Minimum;
                m_propertyTrackBar.LargeChange = 1;
                m_propertyTrackBar.SmallChange = 1;
            }
        }


        private void UpdateCheckBoxes(CameraProperty camProp)
        {
            InitializeCheckBoxes(m_propInfo);

            m_propertyOnOffCheckBox.CheckedChanged -= OnPropertyOnOffCheckedStatusChanged;
            m_propertyAutoCheckBox.CheckedChanged -= OnPropertyAutoCheckedStatusChanged;
            m_propertyOnePushButton.Click -= OnPropertyOnePushClick;
            
            m_propertyAutoCheckBox.Checked = camProp.autoManualMode;
            m_propertyOnOffCheckBox.Checked = camProp.onOff;

            m_propertyOnOffCheckBox.CheckedChanged += new EventHandler(OnPropertyOnOffCheckedStatusChanged);
            m_propertyAutoCheckBox.CheckedChanged += new EventHandler(OnPropertyAutoCheckedStatusChanged);
            m_propertyOnePushButton.Click += new EventHandler(OnPropertyOnePushClick);
        }

        private void InitializeCheckBoxes(CameraPropertyInfo camPropInfo)
        {
            if (m_propType == PropertyType.WhiteBalance && m_useValueB == true)
            {
                //white balance blue, the check boxes is shared with red
                SetCheckBoxVisibility(false);
                return;
            }

            if (m_propertyAutoCheckBox.Visible != camPropInfo.autoSupported)
            {
                m_propertyAutoCheckBox.Visible = camPropInfo.autoSupported;
            }

            if (m_propertyOnOffCheckBox.Visible != camPropInfo.onOffSupported)
            {
                m_propertyOnOffCheckBox.Visible = camPropInfo.onOffSupported;
            }

            if (m_propertyOnePushButton.Visible != camPropInfo.onePushSupported)
            {
                m_propertyOnePushButton.Visible = camPropInfo.onePushSupported;
            }
            //if (m_propertyOnePushButton.Visible)
            //{
            //    tooltip1.SetToolTip(m_propertyOnePushButton, "One Push");
            //}
        }

        /** This is called from the click handlers. */
        private void SetPropertyValue()
        {
            CameraProperty camProp;

            try
            {
                camProp = m_camera.GetProperty(m_propType);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Failed to read " + m_propType + " from camera. Error: " + ex.Message);
                ex.Dispose();
                return;
            }

            //check to see if this property is Manual Mode or not
            //if it is auto mode, then skip this
            if (!camProp.autoManualMode && m_propInfo.manualSupported)
            {
                if (m_isAbsMode)
                {
                    float value = (float)m_propertySpinButton.Value;
                    camProp.absControl = true;
                    float difference = camProp.absValue - value;
                    if (difference != 0)
                    {
                        // The brightness abs register sometimes starts drifting
                        // due to a rounding error between the camera and the
                        // actual value being held by the adjustment. To prevent
                        // this, only apply the change to the camera if the
                        // difference is greater than a specified amount.

                        // Check if the difference is greater than 0.005f. 
                        if (m_propType == PropertyType.Brightness &&
                            Math.Abs(difference) <= 0.005f)
                        {
                            return;
                        }

                        camProp.absValue = value;
                    }
                }
                else
                {
                    uint value;
                    value = Convert.ToUInt32(m_propertySpinButton.Value);

                    camProp.absControl = false;
                    if (m_useValueB)
                    {
                        if (value != camProp.valueB)
                        {
                            camProp.valueB = value;
                        }
                    }
                    else
                    {
                        if (value != camProp.valueA)
                        {
                            // Bug 19306
                            if (camProp.type == PropertyType.Shutter)
                            {
                                camProp.valueB = value >> 12;
                            }
                            camProp.valueA = value;
                        }
                    }
                }

                try
                {
                    m_camera.SetProperty(camProp);
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine("Failed to write " + m_propType + " to camera. Error:" + ex.Message);
                    ex.Dispose();
                }
            }
        }

        private void SetPropertyToCamera(CameraProperty camProp)
        {
            //change values in camera
            try
            {
                m_camera.SetProperty(camProp, false);
                Debug.WriteLine("Set new value to proerty: " + m_propType);
            }
            catch (FC2Exception ex)
            {
                string error = string.Format("Error setting camera {0} property value. {1}", camProp.type, ex.ToString());
                Debug.WriteLine(error);
                ex.Dispose();
            }
        }

        /*
         * SpinButton behavior is a little complex, because the 
         * OnPropertySpinButtonValueChanged(value change event handler)
         * is not working well in this case
         * */
        private void OnPropertySpinButtonValueChanged(object sender, EventArgs e)
        {
            //when this control detect value changing, update camera property value
            SetPropertyValue();
            UpdateTrackBarValueFromSpinButton();
        }

        private void OnPropertySpinButtonKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape ||
                m_propertyAutoCheckBox.Checked == true)
            {
                //when user press esc key, then cancel editing
                UpdateSpinButtonValueFromCamera();
                m_pauseUpdates = false;
                AttachSpinButtonEvent();
                m_propertySpinButton.BackColor = System.Drawing.Color.White;
            }
            else if (e.KeyCode == Keys.Return ||
                     e.KeyCode == Keys.Enter ||
                     e.KeyCode == Keys.Space)
            {
                //when user press enter or space key, then finish editing
                m_pauseUpdates = false;
                SetPropertyValue();
                UpdateTrackBarValueFromSpinButton();
                AttachSpinButtonEvent();
                m_propertySpinButton.BackColor = System.Drawing.Color.White;
            }
            else
            {
                //when any other key press, then start editing
                m_pauseUpdates = true;
                DetachSpinButtonEvent();
                m_propertySpinButton.BackColor = System.Drawing.Color.LightCyan;
            }
        }

       private void OnPropertySpinButtonLeave(object sender, EventArgs e)
        {
            //When spin button lost focus, then finish editing
            m_pauseUpdates = false;
            SetPropertyValue();
            UpdateTrackBarValueFromSpinButton();
            AttachSpinButtonEvent();
            m_propertySpinButton.BackColor = System.Drawing.Color.White;
        }

        private void DetachSpinButtonEvent()
        {
            m_propertySpinButton.ValueChanged -= OnPropertySpinButtonValueChanged;
            m_isSpinBtnEventActivated = false;
        }

        private void AttachSpinButtonEvent()
        {
            //make sure the event is attached only once
            if (m_isSpinBtnEventActivated == false)
            {
                m_propertySpinButton.ValueChanged += new EventHandler(OnPropertySpinButtonValueChanged);
                m_isSpinBtnEventActivated = true;
            }
        }

        private void OnPropertyTrackBarScroll(object sender, EventArgs e)
        {
            UpdateSpinButtonValueFromTrackBar();
        }

        private void OnPropertyAutoCheckedStatusChanged(object sender, EventArgs e)
        {
            if (m_propInfo.manualSupported && m_propInfo.autoSupported)
            {
                try
                {
                    CameraProperty camProp = m_camera.GetProperty(m_propType);
                    
                    if (m_propInfo.absValSupported)
                    {
                        camProp.absControl = m_isAbsMode;
                    }          
          
                    camProp.autoManualMode = m_propertyAutoCheckBox.Checked;

                    m_camera.SetProperty(camProp);
                }
                catch (FC2Exception ex)
                {
                    Debug.WriteLine(string.Format("Unable to set {0} auto status.", m_propType));
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                    ex.Dispose();
                }
            }

            m_pauseUpdates = false;
            m_propertySpinButton.BackColor = System.Drawing.Color.White;
        }

        private void OnPropertyOnOffCheckedStatusChanged(object sender, EventArgs e)
        {
            try
            {
                CameraProperty camProp = m_camera.GetProperty(m_propType);

                if (m_propInfo.absValSupported)
                {
                    camProp.absControl = m_isAbsMode;
                } 

                camProp.onOff = m_propertyOnOffCheckBox.Checked;

                m_camera.SetProperty(camProp);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine(string.Format("Unable to set {0} on/off status.", m_propType));
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                ex.Dispose();
            }
        }

        private void OnPropertyOnePushClick(object sender, EventArgs e)
        {
            try
            {
                CameraProperty camProp = m_camera.GetProperty(m_propType);

                if (m_propInfo.absValSupported)
                {
                    camProp.absControl = m_isAbsMode;
                }

                camProp.onePush = true;

                m_camera.SetProperty(camProp);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine(string.Format("Unable to set {0} one push status.", m_propType));
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                ex.Dispose();
            }
        }
    }
}
