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
    internal partial class LadybugPropertyControl : UserControl
    {                                        
        private const int NumberOfCameras = 6;

        private ManagedCameraBase m_camera;
        private PropertyType m_propertyType;        

        private LadybugType m_ladybugType = LadybugType.None;

        private List<LadybugPropertyControlHolder> m_properties;

        private bool m_independentExposureSupported = false;
        private uint m_independentExposureRegBase = 0;

        public LadybugPropertyControl(ManagedCameraBase initialCamera, PropertyType type, LadybugType ladybugType)
        {
            m_camera = initialCamera;
            m_propertyType = type;
            m_ladybugType = ladybugType;
            
            m_properties = new List<LadybugPropertyControlHolder>(NumberOfCameras);
            for (int i = 0; i < NumberOfCameras; i++)
            {
                m_properties.Add(new LadybugPropertyControlHolder());
            }

            InitializeComponent();
            InitializeControl();
        }

        internal enum LadybugType
        {
            None = 0,
            Ladybug2,
            Ladybug3,
            Ladybug5,
        }

        public override void Refresh()
        {
            if (m_camera == null || Enabled == false)
            {
                return;
            }

            UpdateControl();
            base.Refresh();
        }

        private void InitializeControl()
        {
            switch (m_propertyType)
            {
                case PropertyType.AutoExposure:
                    m_controlTitleLabel.Text = "Auto Exposure";
                    break;
                case PropertyType.Shutter:
                    m_controlTitleLabel.Text = "Shutter";
                    break;
                case PropertyType.Gain:
                    m_controlTitleLabel.Text = "Gain";
                    break;
                default:
                    m_controlTitleLabel.Text = "Unknown Property Type";
                    break;
            }
            
            for (int i = 0; i < NumberOfCameras; i++)
            {
                //Initialize Camera Name Labels
                Label cameraName = new Label();
                cameraName.Text = string.Format("Camera {0}", i);
                cameraName.AutoSize = false;
                cameraName.Width = 55;
                cameraName.Height = 20;
                cameraName.TextAlign = ContentAlignment.MiddleCenter;
                m_propertyControlFlowTabel.Controls.Add(cameraName, 0, i);

                //Initialize property value slider
                m_properties[i].PropertyValueTrackBar.TickStyle = TickStyle.None;
                m_properties[i].PropertyValueTrackBar.Anchor = AnchorStyles.Left | AnchorStyles.Right;
                m_properties[i].PropertyValueTrackBar.Tag = i; //Camera index 
                m_properties[i].PropertyValueTrackBar.Maximum = 1000;
                m_properties[i].PropertyValueTrackBar.Scroll += new EventHandler(OnTrackbarScroll);
                m_propertyControlFlowTabel.Controls.Add(m_properties[i].PropertyValueTrackBar, 1, i);                     

                //Initialize spin button
                m_properties[i].PropertyValueSpinButton.AutoSize = false;
                m_properties[i].PropertyValueSpinButton.Width = 55;
                m_properties[i].PropertyValueSpinButton.Tag = i; //Camera index 
                m_properties[i].PropertyValueSpinButton.Maximum = 1000;
                m_properties[i].PropertyValueSpinButton.ValueChanged += new EventHandler(OnSpinButtonValueChanged);
                m_propertyControlFlowTabel.Controls.Add(m_properties[i].PropertyValueSpinButton, 2, i);

                //Initialize auto check box
                m_properties[i].AutoCheckBox.Tag = i; //Camera index 
                m_properties[i].AutoCheckBox.CheckedChanged += new EventHandler(OnPropertyAutoCheckedChanged);
                m_propertyControlFlowTabel.Controls.Add(m_properties[i].AutoCheckBox, 3, i);

                //Initialize on/off check box
                m_properties[i].OnOffCheckBox.Tag = i; //Camera index 
                m_properties[i].OnOffCheckBox.CheckedChanged += new EventHandler(OnPropertyOnOffCheckedChanged);
                m_propertyControlFlowTabel.Controls.Add(m_properties[i].OnOffCheckBox, 4, i);
            }

            if (NeedsCCDsCheckBoxes())
            {
                //Initialize CCDs of Interest Labels
                for (int currProp = 0; currProp < m_properties.Count; currProp++)
                {
                    Label ccdName = new Label();
                    ccdName.Text = string.Format("{0}", currProp);
                    ccdName.AutoSize = false;
                    ccdName.Dock = DockStyle.Fill;
                    ccdName.TextAlign = ContentAlignment.BottomLeft;
                    m_ccdsOfInterestTableLayout.Controls.Add(ccdName, currProp, 0);
                }

                // Initialize CCDs of Interest Check Boxes
                for (int currProp = 0; currProp < m_properties.Count; currProp++)
                {
                    for (int currCcdIdx = 0; currCcdIdx < m_properties[currProp].CcdCheckBoxes.Count; currCcdIdx++) 
                    {
                        m_properties[currProp].CcdCheckBoxes[currCcdIdx].AutoCheck = true;
                        m_properties[currProp].CcdCheckBoxes[currCcdIdx].Tag = new Point(currCcdIdx, currProp); //Camera index: X = column, Y = row
                        m_properties[currProp].CcdCheckBoxes[currCcdIdx].CheckedChanged += new EventHandler(OnCCDCheckedChanged);
                        m_ccdsOfInterestTableLayout.Controls.Add(
                            m_properties[currProp].CcdCheckBoxes[currCcdIdx], 
                            currCcdIdx, 
                            currProp + 1);
                    }
                }
            }
            else
            {
                //Hide CCD of interest controls
                m_ccdsOfInterestTableLayout.Visible = false;
                m_ccdsOfInterestLabel.Visible = false;
                m_basicControlPanel.Width += 171;
            }

            if (m_camera == null)
            {
                Debug.WriteLine("Camera object is null!");
                m_propertyControlFlowTabel.Enabled = false;
                return;
            }

            // Check if Independent Exposure is supported
            m_independentExposureSupported = false;
            if (   m_ladybugType == LadybugType.Ladybug3
                || m_ladybugType == LadybugType.Ladybug5)
            {
                uint uiRegVal = 0;
                try
                {
                    // Independent Exposure Inquiry. Ladybug3 only.
                    // The quadlet offset of the base address of the per sensor 
                    // independent exposure controls
                    const uint IndependentExposureInq = 0x1e94;

                    uiRegVal = m_camera.ReadRegister(IndependentExposureInq);

                    // Get the offset
                    m_independentExposureRegBase = (uiRegVal * 4) & 0xFFFF;
                }
                catch (FC2Exception ex)
                {
                    m_independentExposureSupported = false;
                    BasePage.ShowErrorMessageDialog("Error reading independent exposure  inquiry register", ex);
                    ex.Dispose();
                }

                // Supported if offset is not 0
                m_independentExposureSupported = m_independentExposureRegBase != 0;
            }
            else if (m_ladybugType == LadybugType.Ladybug2)
            {
                m_independentExposureSupported = true;
                
                // Base address of Ladybug2 Independent exposure control registers
                const uint LD2IndependentExposureRegBase = 0x1800;
                m_independentExposureRegBase = LD2IndependentExposureRegBase;
            }
            else
            {
                m_independentExposureSupported = false;
                m_independentExposureRegBase = 0;
            }            
        }
        
        private void UpdateControl()
        {
            CameraPropertyInfo camPropInfo;
            try
            {
                camPropInfo = m_camera.GetPropertyInfo(m_propertyType);
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog("Error getting camera property information.", ex);
                ex.Dispose();
                return;
            }

            foreach (LadybugPropertyControlHolder currHolder in m_properties)
            {
                currHolder.PropertyValueSpinButton.Minimum = (decimal)camPropInfo.min;
                currHolder.PropertyValueSpinButton.Maximum = (decimal)camPropInfo.max;

                currHolder.PropertyValueTrackBar.Minimum = (int)camPropInfo.min;
                currHolder.PropertyValueTrackBar.Maximum = (int)camPropInfo.max;
            }

            UpdatePropertyValues();
        }

        private void OnPropertyAutoCheckedChanged(object sender, EventArgs e)
        {
            CheckBox checkBox = sender as CheckBox;
            int index = (int)checkBox.Tag;

            // Bit mask for auto bit
            const uint AutoBitMask = 0x01000000;
            SetPropertyCheckedBitInReg(index, checkBox.Checked, AutoBitMask);
        }

        private void OnPropertyOnOffCheckedChanged(object sender, EventArgs e)
        {
            CheckBox checkBox = sender as CheckBox;
            int index = (int)checkBox.Tag;

            // Bit mask for on/off bit
            const uint OnOffBitMask = 0x02000000;
            SetPropertyCheckedBitInReg(index, checkBox.Checked, OnOffBitMask);
        }

        private void SetPropertyCheckedBitInReg(int index, bool active, uint bitMask)
        {            
            try
            {
                uint uiValue = 0;
                uint address = GetPropertyValueRegAddress(index);
                uint regValue = m_camera.ReadRegister(address);

                if (active)
                {
                    uiValue = regValue | bitMask;
                }
                else
                {
                    uiValue = regValue & (~bitMask);
                }

                m_camera.WriteRegister(address, uiValue);
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog(
                    "Error setting independent property(" + m_propertyType.ToString() + ") control register.",
                    ex);
                ex.Dispose();
                return;
            }           
        }

        private void OnCCDCheckedChanged(object sender, EventArgs e)
        {
            CheckBox checkBox = sender as CheckBox;
            Point index = (Point)checkBox.Tag;
            int cameraIdx = index.Y;
            int ccdIdx = index.X;
                        
            uint propValRegVal = 0;
            uint propValReg = GetPropertyValueRegAddress(cameraIdx);
            try
            {
                propValRegVal = m_camera.ReadRegister(propValReg);
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog(
                    "Error reading independent property(" + m_propertyType.ToString() + ") control register.",
                    ex);
                ex.Dispose();
                return;
            }

            uint bitMask = 0;
            try
            {
                bitMask = checked((uint)(0x00001000 << ccdIdx));
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine("Invalid CCD index.");
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                return;
            }            

            try
            {
                uint uiValue = 0;

                // Bit-14:19 Sensor_Mask
                if (checkBox.Checked == true)
                {
                    uiValue = propValRegVal | bitMask;
                }
                else
                {
                    uiValue = propValRegVal & (~bitMask);
                }

                m_camera.WriteRegister(propValReg, uiValue);
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog(
                    "Error writing independent property(" + m_propertyType.ToString() + ") control register.",
                    ex);
                ex.Dispose();
            }           
        }

        private void OnTrackbarScroll(object sender, EventArgs e)
        {
            TrackBar trackbar = sender as TrackBar;
            int index = (int)trackbar.Tag;
            try
            {
                SetSpinButtonValueSafeMethod(Convert.ToDecimal(trackbar.Value), index);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("Property spin button [" + index + "] is out of range. " + ex.Message);
            }
        }

        private void OnSpinButtonValueChanged(object sender, EventArgs e)
        {
            NumericUpDown button = sender as NumericUpDown;
            int index = (int)button.Tag;
            try
            {
                m_properties[index].PropertyValueTrackBar.Value = Convert.ToInt32(button.Value);
                uint valueToSet = Convert.ToUInt32(button.Value);
                SetPropertyValueInReg(index, valueToSet);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("Property trackbar [" + index + "] is out of range. " + ex.Message);
            }            
        }

        private void SetPropertyValueInReg(int index, uint valueToSet)
        {            
            try
            {
                uint propValRegAddress = GetPropertyValueRegAddress(index);
                uint propValRegVal = m_camera.ReadRegister(propValRegAddress);

                uint valueToWrite = propValRegVal & 0xFFFFF000;
                valueToWrite = valueToWrite | (valueToSet & 0xFFF);

                m_camera.WriteRegister(propValRegAddress, valueToWrite);
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog(
                    "Error setting independent property (" + m_propertyType.ToString() + ") control register.",
                    ex);
                ex.Dispose();
            }
        }
        
        private uint GetPropertyValueRegAddress(int index)
        {
            // Independent exposure control register offsets
            const uint GainOffset = 0x00;
            const uint ShutterOffset = 0x04;
            const uint ExposureOffset = 0x08;

            uint propertyRegVal = (uint)(m_independentExposureRegBase + (0x20 * index));
            switch (m_propertyType)
            {
                case PropertyType.AutoExposure:
                    propertyRegVal += ExposureOffset;
                    break;
                case PropertyType.Shutter:
                    propertyRegVal += ShutterOffset;
                    break;
                case PropertyType.Gain:
                    propertyRegVal += GainOffset;
                    break;
                default:
                    Debug.WriteLine("Unknown Property Type.");
                    propertyRegVal = 0;
                    break;
            }

            return propertyRegVal;
        }

        private void UpdatePropertyValues()
        {
            uint propValRegVal = 0;
            for (int currCameraIdx = 0; currCameraIdx < NumberOfCameras; currCameraIdx++)
            {
                try
                {
                    uint propValReg = GetPropertyValueRegAddress(currCameraIdx);
                    propValRegVal = m_camera.ReadRegister(propValReg);
                }
                catch (FC2Exception ex)
                {
                    BasePage.ShowErrorMessageDialog(
                        "Error reading independent exposure inquiry register", 
                        ex);
                    ex.Dispose();
                    return;
                }

                if ((propValRegVal & 0x80000000) == 0)
                {
                    // Not present
                    SetWidgetStatus(currCameraIdx, false);
                    if (NeedsCCDsCheckBoxes())
                    {
                        for (int currCcdIdx = 0; currCcdIdx < m_properties[currCameraIdx].CcdCheckBoxes.Count; currCcdIdx++)
                        {
                            m_properties[currCameraIdx].CcdCheckBoxes[currCcdIdx].Enabled = false;
                        }
                    }

                    continue;
                }
                else
                {
                    // Make sure widget is enabled
                    SetWidgetStatus(currCameraIdx, true);
                }                

                 // Bit-6 is On/Off 
                m_properties[currCameraIdx].OnOffCheckBox.Checked = (propValRegVal & 0x02000000) > 0;

                // Bit-7 is Auto
                m_properties[currCameraIdx].AutoCheckBox.Checked = (propValRegVal & 0x01000000) > 0;

                // Bit-20:31 is the auto exposure value
                uint autoExposureValue = propValRegVal & 0xFFF;
                SetSpinButtonValueSafeMethod((decimal)autoExposureValue, currCameraIdx);

                // Bit-14:19 Sensor_Mask
                //if ( m_independentExposureSensorMaskSupported == true)
                if (NeedsCCDsCheckBoxes())
                {
                    for (int currCcdIdx = 0; currCcdIdx < m_properties[currCameraIdx].CcdCheckBoxes.Count; currCcdIdx++)
                    {
                        bool isCCDsOfInterestOn = (propValRegVal & (0x1 << (12 + currCcdIdx))) != 0;
                        m_properties[currCameraIdx].CcdCheckBoxes[currCcdIdx].Checked = isCCDsOfInterestOn;
                    }
                }
            }
        }

        private void SetSpinButtonValueSafeMethod(decimal spinButtonValue, int spinButtonIndex)
        {
            if (m_properties[spinButtonIndex].PropertyValueSpinButton.Value != spinButtonValue)
            {
                if (spinButtonValue < m_properties[spinButtonIndex].PropertyValueSpinButton.Minimum)
                {
                    m_properties[spinButtonIndex].PropertyValueSpinButton.Value = m_properties[spinButtonIndex].PropertyValueSpinButton.Minimum;
                }
                else if (spinButtonValue > m_properties[spinButtonIndex].PropertyValueSpinButton.Maximum)
                {
                    m_properties[spinButtonIndex].PropertyValueSpinButton.Value = m_properties[spinButtonIndex].PropertyValueSpinButton.Maximum;
                }
                else
                {
                    m_properties[spinButtonIndex].PropertyValueSpinButton.Value = spinButtonValue;
                }
            }
        }

        private void SetWidgetStatus(int camIdx, bool enable)
        {
            m_properties[camIdx].PropertyValueSpinButton.Enabled = enable;
            m_properties[camIdx].PropertyValueTrackBar.Enabled = enable;
            m_properties[camIdx].AutoCheckBox.Enabled = enable;
            m_properties[camIdx].OnOffCheckBox.Enabled = enable;

            foreach (CheckBox ccdCheckBox in m_properties[camIdx].CcdCheckBoxes)
            {
                ccdCheckBox.Enabled = enable;
            }
        }

        private bool NeedsCCDsCheckBoxes()
        {
            //return whether this control need CCD CheckBoxes
            return m_propertyType == PropertyType.AutoExposure;
        }
    }

    /** Simple class to hold controls related to a single camera. */
    internal class LadybugPropertyControlHolder
    {
        public readonly TrackBar PropertyValueTrackBar;
        public readonly NumericUpDown PropertyValueSpinButton;
        public readonly CheckBox AutoCheckBox;
        public readonly CheckBox OnOffCheckBox;
        public readonly List<CheckBox> CcdCheckBoxes;

        internal LadybugPropertyControlHolder()
        {
            PropertyValueTrackBar = new TrackBar();
            PropertyValueSpinButton = new NumericUpDown();
            AutoCheckBox = new CheckBox();
            OnOffCheckBox = new CheckBox();
            CcdCheckBoxes = new List<CheckBox>(6);
            for (int i = 0; i < 6; i++)
            {
                CcdCheckBoxes.Add(new CheckBox());
            }
        }
    }
}
