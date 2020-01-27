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
using System.Globalization;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /* If you can not open the design view of this class, try to modify base class
     * to "UserControl" instead of "BasePage". VS2005 probably has issue of opening 
     * design view for inherited user control. The reason is still investigating.
     * */

    //internal partial class CameraRegistersPage : UserControl
    internal partial class CameraRegistersPage : BasePage
    {
        private RegisterSet m_registerSet;
        private BinaryBitsControl[] m_regBitVal;
        private uint m_lastRegBlockOffset;
        private bool m_isReadingRegister = false;
        private bool m_updatingDatagridview = false;
        private string m_cellOldValue = string.Empty;
        public EventHandler OnTriggerParameterChanged;

        public CameraRegistersPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            m_lastRegBlockOffset = 0;
            InitializeComponent();
            InitializePage();
        }

        private enum RegisterSet
        {
            REGISTER_SET_IIDC,
            REGISTER_SET_GEV
        }

        private void InitializePage()
        {
            if (m_camera == null)
            {
                // Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            InitializeCameraData();

            m_regEntryTextBox.Text = "0";
            m_regBlockEntryTextBox.Text = "0";

            OnEntryRegisterChanged();

            m_regBitVal = new BinaryBitsControl[4];
            m_regBitVal[0] = new BinaryBitsControl(8, "0 - 7");
            m_regBitVal[1] = new BinaryBitsControl(8, "8 - 15");
            m_regBitVal[2] = new BinaryBitsControl(8, "16 - 23");
            m_regBitVal[3] = new BinaryBitsControl(8, "24 - 31");

            m_regValueBlock.CellValueChanged +=new DataGridViewCellEventHandler(m_regValueBlock_CellValueChanged);
            m_regValueBlock.CellBeginEdit +=new DataGridViewCellCancelEventHandler(m_regValueBlock_CellBeginEdit);

            for (int i = 0; i < 4; i++)
            {
                int xPos = i + 1;
                int yPos = 3;

                // Add the event handler
                m_regBitVal[i].Validated += new EventHandler(RegisterBitValueValidated);
                m_regBitVal[i].TabIndex = 10;

                // Add the control to the layout panel
                m_registerTableLayoutPanel.Controls.Add(m_regBitVal[i], xPos, yPos);
                
                // Get the control back to set the row span
                Control currControl = m_registerTableLayoutPanel.GetControlFromPosition(xPos, yPos);
                m_registerTableLayoutPanel.SetRowSpan(currControl, 2);
            }
        }

        private void InitializeCameraData()
        {
            m_iIDCRegSetButton.Checked = true;
            
            CameraInfo camInfo;
            
            try
            {
                camInfo = m_camera.GetCameraInfo();
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Unable to get Camera Info. {0}", ex.Message);
                ex.Dispose();
                return;
            }

            if (camInfo.interfaceType == InterfaceType.GigE)
            {
                m_regSetLabel.Visible = true;
                m_gigERegSetButton.Visible = true;
                m_iIDCRegSetButton.Visible = true;
            }
            else
            {
                m_regSetLabel.Visible = false;
                m_gigERegSetButton.Visible = false;
                m_iIDCRegSetButton.Visible = false;
            }
        }

        private void OnEntryRegisterTextChanged(object sender, EventArgs e)
        {
            OnEntryRegisterChanged();
        }

        private void OnEntryRegisterChanged()
        {
            if (m_regEntryTextBox.Text.Length == 0)
            {
                // if nothing in the text box
                m_registerName.Text = string.Empty;

                // m_registerName.Text = ("Enter register value in the text box above.");
                m_regEntryTextBox.BackColor = Color.PaleGreen;
                return;
            }

            if (m_registerSet == RegisterSet.REGISTER_SET_IIDC)
            {
                uint registerVal = 0;
                try
                {
                    // Get the text in the box
                    registerVal = Convert.ToUInt32(m_regEntryTextBox.Text, 16);
                }
                catch (Exception ex)
                {
                    m_registerName.Text = "Invalid";
                    m_regEntryTextBox.BackColor = Color.Red;
                    return;
                }

                string regValString = ManagedCameraBase.GetRegisterString(registerVal);
                if (regValString.Equals("Invalid"))
                {
                    m_regEntryTextBox.BackColor = Color.Red;
                }
                else
                {
                    m_regEntryTextBox.BackColor = Color.PaleGreen;
                }

                m_registerName.Text = regValString;
            }
            else if (m_registerSet == RegisterSet.REGISTER_SET_GEV)
            {
                m_registerName.Text = "Unknown";
                m_regEntryTextBox.BackColor = Color.PaleGreen;
            }
        }

        private void OnRegisterSetButtonCheckedStatusChanged(object sender, EventArgs e)
        {
            if (m_iIDCRegSetButton.Checked)
            {
                m_registerSet = RegisterSet.REGISTER_SET_IIDC;
            }
            else if (m_gigERegSetButton.Checked)
            {
                m_registerSet = RegisterSet.REGISTER_SET_GEV;
            }

            OnEntryRegisterChanged();
        }

        private void RegisterBitValueValidated(object sender, EventArgs e)
        {
            UpdateIEEE754TextBox();
        }

        private void UpdateIEEE754TextBox()
        {
            uint value = 0;
            try
            {
                value = GetRegisterValueFromPage();
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                ShowErrorMessageDialog("Invalid argument in function ReadRegisterValueFromCamera().", ex);
                return;
            }
            catch (FormatException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "Register value is invalid.",
                    "Invalid Value",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                SetRegisterValueToPage(0);
                return;
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "The number you entered is too large. Register value is invalid.",
                    "Invalid Value",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                SetRegisterValueToPage(0);
                return;
            }

            if (!m_isReadingRegister)
            {
                m_ieee754TextBox.TextChanged -= new System.EventHandler(this.OnIEEE754TextChanged);
            }
            
            double ieeeVal = MathUtilities.Convert32bitIEEEToFloat(value);
            m_ieee754TextBox.Text = string.Format("{0:0.000000}", ieeeVal);

            if (!m_isReadingRegister)
            {
                m_ieee754TextBox.TextChanged += new System.EventHandler(this.OnIEEE754TextChanged);
            }     
        }

        private uint GetRegisterValueFromPage()
        {
            uint reg0 = 0;
            uint reg8 = 0;
            uint reg16 = 0;
            uint reg24 = 0;

            reg0 = m_regBitVal[0].GetRegisterValue();
            reg8 = m_regBitVal[1].GetRegisterValue();
            reg16 = m_regBitVal[2].GetRegisterValue();
            reg24 = m_regBitVal[3].GetRegisterValue();

            uint value = (reg0 << 24) + (reg8 << 16) + (reg16 << 8) + (reg24 << 0);
            return value;
        }

        private void OnIEEE754TextChanged(object sender, EventArgs e)
        {
            if (m_isReadingRegister == true)
            {
                // this function will be called when IEEE754 text box value changes
                // We need to avoid this call when reading register is in progress,
                // because that will overwrite the Register Value on the UI 
                return;
            }

            ValidateIEEE754TextBox();
            float ieeeValue = 0.0f;
            try
            {
                ieeeValue = (float)Convert.ToDouble(m_ieee754TextBox.Text);
            }
            catch (InvalidCastException ex)
            {
                Debug.WriteLine("Invalid Cast: " + ex.Message);
                MessageBox.Show("Please enter a valid IEEE754 number.", "Invalid IEEE754 Number", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                ShowErrorMessageDialog("Invalid argument in function OnIEEE754TextChanged().", ex);
                return;
            }
            catch (FormatException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "The value in IEEE754 text box is invalid.",
                    "Invalid Value",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                return;
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "The number you entered is too large. The value in IEEE754 text box is invalid.",
                    "Invalid Value",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                return;
            }

            uint value = BitConverter.ToUInt32(BitConverter.GetBytes(ieeeValue), 0);
            SetRegisterValueToPage(value);
        }

        private void ValidateIEEE754TextBox()
        {
            m_ieee754TextBox.TextChanged -= new EventHandler(OnIEEE754TextChanged);
            if (m_ieee754TextBox.Text.Equals(string.Empty))
            {
                m_ieee754TextBox.Text = "0.000000";
            }
            else
            {
                bool isNegative = false;
                if (m_ieee754TextBox.Text[0] == '-')
                {
                    isNegative = true;
                }

                m_ieee754TextBox.Text = Regex.Replace(m_ieee754TextBox.Text, @"[^0-9.]", string.Empty);

                if (isNegative)
                {
                    m_ieee754TextBox.Text = string.Format("-{0}", m_ieee754TextBox.Text);
                }
            }

            m_ieee754TextBox.TextChanged += new EventHandler(OnIEEE754TextChanged);
        }

        private void SetRegisterValueToPage(uint value)
        {
            m_regBitVal[0].SetValue(value >> 24 & 0xFF);
            m_regBitVal[1].SetValue(value >> 16 & 0xFF);
            m_regBitVal[2].SetValue(value >> 8 & 0xFF);
            m_regBitVal[3].SetValue(value >> 0 & 0xFF);
        }

        private void OnReadRegButtonClick(object sender, EventArgs e)
        {
            ReadRegisterValueFromCamera();
        }

        private void ReadRegisterValueFromCamera()
        {
            m_isReadingRegister = true;

            // Get the text in the box
            uint registerVal = 0;
            try
            {
                // Get the text in the box
                registerVal = Convert.ToUInt32(m_regEntryTextBox.Text, 16);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                ShowErrorMessageDialog("Invalid argument in function ReadRegisterValueFromCamera().", ex);
                return;
            }
            catch (FormatException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "Please enter a valid register address.", 
                    "Invalid Register Address", 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Information);
                return;
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "The number you entered is too large. Please enter a valid register address.", 
                    "Invalid Register Address", 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Information);
                return;
            }

            uint value = 0;

            if (m_registerSet == RegisterSet.REGISTER_SET_IIDC)
            {
                try
                {
                    value = m_camera.ReadRegister(registerVal);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog(
                        string.Format(
                        "There was an error reading register 0x{0:X8}.",
                        registerVal), 
                        ex);
                    ex.Dispose();
                    return;
                }
            }
            else if (m_registerSet == RegisterSet.REGISTER_SET_GEV)
            {
                if (IsGEV() != true)
                {
                    return;
                }

                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                try
                {
                    value = camera.ReadGVCPRegister(registerVal);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog(
                        string.Format(
                        "There was an error reading GVCP register 0x{0:X8}.",
                        registerVal), 
                        ex);
                    ex.Dispose();
                    return;
                }
            }

            SetRegisterValueToPage(value);
            UpdateIEEE754TextBox();
            m_isReadingRegister = false;
        }

        private void OnWriteRegButtonClick(object sender, EventArgs e)
        {
            // Get the text in the box
            uint registerVal = 0;
            try
            {
                // Get the text in the box
                registerVal = Convert.ToUInt32(m_regEntryTextBox.Text, 16);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                ShowErrorMessageDialog("Invalid argument in function OnWriteRegButtonClick().", ex);
                return;
            }
            catch (FormatException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "Please enter a valid register address.", 
                    "Invalid Register Address", 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Information);
                return;
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "The number you entered is too large. Please enter a valid register address.", 
                    "Invalid Register Address", 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Information);
                return;
            }

            uint value = 0;
            try
            {
                value = GetRegisterValueFromPage();
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                ShowErrorMessageDialog("Invalid argument in function ReadRegisterValueFromCamera().", ex);
                return;
            }
            catch (FormatException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "Register value is invalid.",
                    "Invalid Value",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                return;
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "The number you entered is too large. Register value is invalid.",
                    "Invalid Value",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
                return;
            }

            if (m_registerSet == RegisterSet.REGISTER_SET_IIDC)
            {
                try
                {
                    m_camera.WriteRegister(registerVal, value);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("There was an error writing IIDC register", ex);
                    ex.Dispose();
                    return;
                }
            }
            else if (m_registerSet == RegisterSet.REGISTER_SET_GEV)
            {
                if (IsGEV() != true)
                {
                    return;
                }

                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                try
                {
                    camera.WriteGVCPRegister(registerVal, value);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog(
                        string.Format(
                        "There was an error writing GVCP register 0x{0:X8} with the value {1:X8}.",
                        registerVal, 
                        value), 
                        ex);
                    ex.Dispose();
                }
            }

            if (registerVal == 0x830 || registerVal == 0x834)
            {
                UpdateGPIOPage(EventArgs.Empty);
            }

        }

        private void UpdateGPIOPage(EventArgs e)
        {
            if (OnTriggerParameterChanged != null)
            {
                OnTriggerParameterChanged(this, e);
            }
        }

        private void OnReadRegBlockButtonClick(object sender, EventArgs e)
        {
            ReadRegisterBlockValueFromCamera();
        }

        private void ReadRegisterBlockValueFromCamera()
        {
            // Get the text in the box
            uint regBlockOffset = 0;
            try
            {
                // Get the text in the box
                regBlockOffset = Convert.ToUInt32(m_regBlockEntryTextBox.Text, 16);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                ShowErrorMessageDialog("Invalid argument in function ReadRegisterBlockValueFromCamera().", ex);
                return;
            }
            catch (FormatException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "Please enter a valid register address.", 
                    "Invalid Register Address", 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Information);
                return;
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine(ex.Message);
                MessageBox.Show(
                    "The number you entered is too large. Please enter a valid register address.", 
                    "Invalid Register Address", 
                    MessageBoxButtons.OK, 
                    MessageBoxIcon.Information);
                return;
            }
            
            int numQuadlets = Convert.ToInt32(m_numOfQuadletsToReadSpinButton.Value);
            uint[] values = new uint[numQuadlets];
            if (m_registerSet == RegisterSet.REGISTER_SET_IIDC)
            {
                try
                {
                    m_camera.ReadRegisterBlock(0xFFFF, regBlockOffset + 0xF0F00000, values);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog(
                        string.Format(
                        "There was an error reading IIDC register block 0x{0:X8} - 0x{1:X8}.",
                        regBlockOffset, 
                        regBlockOffset + (4 * numQuadlets)), 
                        ex);
                    ex.Dispose();
                    return;
                }              
            }
            else if (m_registerSet == RegisterSet.REGISTER_SET_GEV)
            {
                if (IsGEV() != true)
                {
                    return;
                }

                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                try
                {
                    camera.ReadGVCPRegisterBlock(regBlockOffset, values);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog(
                        string.Format(
                        "There was an error reading GVCP register block 0x{0:X8} - 0x{1:X8}.",
                        regBlockOffset, 
                        regBlockOffset + (4 * numQuadlets)), 
                        ex);
                    ex.Dispose();
                    return;
                }
            }

            m_lastRegBlockOffset = regBlockOffset;
            m_regValueBlock.Rows.Clear();
            m_updatingDatagridview = true;
            for (int i = 0; i < numQuadlets; i++)
            {
                uint currentRegVal = (uint)(regBlockOffset + (i * 4));
                m_regValueBlock.Rows.Add(new DataGridViewRow());
                m_regValueBlock.Rows[i].Cells[0].Value = string.Format("0x{0:X}", currentRegVal);
                m_regValueBlock.Rows[i].Cells[1].Value = string.Format("0x{0:X8}", values[i]);
                double ieeeVal = MathUtilities.Convert32bitIEEEToFloat(values[i]);
                m_regValueBlock.Rows[i].Cells[2].Value = ieeeVal;
                m_regValueBlock.Rows[i].Cells[3].Value = ManagedCameraBase.GetRegisterString(currentRegVal);
            }
            m_updatingDatagridview = false;
        }

        private void m_regValueBlock_CellBeginEdit(object sender, EventArgs e)
        {
            DataGridViewCell cell = m_regValueBlock.CurrentCell;

            if (cell.Value != null)
            {
                m_cellOldValue = cell.Value.ToString();
            }
        }

        private void m_regValueBlock_CellValueChanged(object sender, EventArgs e)
        {
            if (!m_updatingDatagridview)
            {
                m_regValueBlock.CellValueChanged -= new DataGridViewCellEventHandler(m_regValueBlock_CellValueChanged);

                DataGridViewCell cell = m_regValueBlock.CurrentCell;

                // Hex Value was changed
                if (cell.ColumnIndex == 1)
                {
                    try
                    {
                        if (cell.Value == null || cell.Value.ToString().Length == 0)
                        {
                            m_regValueBlock.CancelEdit();
                            if (m_cellOldValue.Length > 0)
                            {
                                cell.Value = m_cellOldValue;
                            }
                            return;
                        }
                        uint result = 0;

                        string hex = cell.Value.ToString();
                        if (hex.StartsWith("0x", StringComparison.CurrentCultureIgnoreCase))
                        {
                            hex = hex.Substring(2);
                        }

                        Convert.ToUInt32(hex, 16);

                        bool parsedSuccessfully = uint.TryParse(hex,
                                NumberStyles.HexNumber,
                                CultureInfo.CurrentCulture,
                                out result);

                        if (parsedSuccessfully)
                        {
                            double ieeeVal = MathUtilities.Convert32bitIEEEToFloat(result);
                            m_regValueBlock.Rows[cell.RowIndex].Cells[2].Value = ieeeVal;
                        }
                    }
                    catch (ArgumentException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        Debug.WriteLine(ex.StackTrace);
                        ShowErrorMessageDialog("Invalid argument in function OnCellValueChanged().", ex);
                        return;
                    }
                    catch (FormatException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        MessageBox.Show(
                            "Register value is invalid.",
                            "Invalid Value",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
                        if (m_cellOldValue.Length > 0)
                        {
                            cell.Value = m_cellOldValue;
                        }
                        return;
                    }
                    catch (OverflowException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        MessageBox.Show(
                            "The number you entered is too large. Register value is invalid.",
                            "Invalid Value",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
                        if (m_cellOldValue.Length > 0)
                        {
                            cell.Value = m_cellOldValue;
                        }
                        return;
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine(ex.Message);
                        MessageBox.Show(
                            "Register value is invalid.",
                            "Invalid Value",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
                        if (m_cellOldValue.Length > 0)
                        {
                            cell.Value = m_cellOldValue;
                        }
                        return;
                    }
                    finally
                    {
                        m_regValueBlock.CellValueChanged += new DataGridViewCellEventHandler(m_regValueBlock_CellValueChanged);
                    }
                }

                // IEEE 754 value was changed
                if (cell.ColumnIndex == 2)
                {
                    try
                    {
                        if (cell.Value == null || cell.Value.ToString().Length == 0)
                        {
                            m_regValueBlock.CancelEdit();
                            if (m_cellOldValue.Length > 0)
                            {
                                cell.Value = m_cellOldValue;
                            }
                            return;
                        }
                        string result = ValidateIEEE754String(cell.Value.ToString());
                        float ieeeValue = 0.0f;
                        ieeeValue = (float)Convert.ToDouble(result);
                        cell.Value = ieeeValue.ToString();
                        uint value = BitConverter.ToUInt32(BitConverter.GetBytes(ieeeValue), 0);
                        m_regValueBlock.Rows[cell.RowIndex].Cells[1].Value = String.Format("0x{0:X8}", value);
                    }
                    catch (InvalidCastException ex)
                    {
                        Debug.WriteLine("Invalid Cast: " + ex.Message);
                        MessageBox.Show("Please enter a valid IEEE754 number.", "Invalid IEEE754 Number", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        if (m_cellOldValue.Length > 0)
                        {
                            cell.Value = m_cellOldValue;
                        }
                        return;
                    }
                    catch (ArgumentException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        Debug.WriteLine(ex.StackTrace);
                        ShowErrorMessageDialog("Invalid argument in function CellValueChanged().", ex);
                        return;
                    }
                    catch (FormatException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        MessageBox.Show(
                            "The value in IEEE754 cell is invalid.",
                            "Invalid Value",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
                        if (m_cellOldValue.Length > 0)
                        {
                            cell.Value = m_cellOldValue;
                        }
                        return;
                    }
                    catch (OverflowException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        MessageBox.Show(
                            "The number you entered is too large. The value in IEEE754 cell is invalid.",
                            "Invalid Value",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
                        if (m_cellOldValue.Length > 0)
                        {
                            cell.Value = m_cellOldValue;
                        }
                        return;
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine(ex.Message);
                        MessageBox.Show(
                            "The value in IEEE754 cell is invalid.",
                            "Invalid Value",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
                        if (m_cellOldValue.Length > 0)
                        {
                            cell.Value = m_cellOldValue;
                        }
                        return;
                    }
                    finally
                    {
                        m_regValueBlock.CellValueChanged += new DataGridViewCellEventHandler(m_regValueBlock_CellValueChanged);
                    }
                }
                
            }
        }

        private string ValidateIEEE754String(string input)
        {
            if (input.Equals(string.Empty))
            {
                return "0.000000";
            }
            else
            {
                bool isNegative = false;
                string result;
                if (input.Contains("-"))
                {
                    isNegative = true;
                }

                result = Regex.Replace(input, @"[^0-9.]", string.Empty);

                if (isNegative)
                {
                    result = string.Format("-{0}", input);
                }
                return result;
            }
        }

        private void OnRegBlockEntryTextChanged(object sender, EventArgs e)
        {
            if (m_regBlockEntryTextBox.Text.Length == 0)
            {
                // if nothing in the text box
                m_registerName.Text = string.Empty;

                // m_registerName.Text = ("Enter register value in the text box above.");
                m_regBlockEntryTextBox.BackColor = Color.PaleGreen;
                return;
            }

            if (m_registerSet == RegisterSet.REGISTER_SET_IIDC)
            {
                uint registerVal = 0;
                try
                {
                    // Get the text in the box
                    registerVal = Convert.ToUInt32(m_regBlockEntryTextBox.Text, 16);
                }
                catch (Exception ex)
                {
                    m_regBlockEntryTextBox.BackColor = Color.Red;
                    return;
                }

                string regValString = ManagedCameraBase.GetRegisterString(registerVal);
                if (regValString.Equals("Invalid"))
                {
                    m_regBlockEntryTextBox.BackColor = Color.Red;
                }
                else
                {
                    m_regBlockEntryTextBox.BackColor = Color.PaleGreen;
                }
            }
            else if (m_registerSet == RegisterSet.REGISTER_SET_GEV)
            {
                m_regBlockEntryTextBox.BackColor = Color.PaleGreen;
            }
        }

        private void OnWriteRegBlockButtonClick(object sender, EventArgs e)
        {
            uint numQuadlets = (uint)m_regValueBlock.Rows.Count;
            uint[] regBlockArray = new uint[numQuadlets];

            for (int i = 0; i < (int)numQuadlets; i++)
            {
                string valStr = (string)m_regValueBlock.Rows[i].Cells[1].Value;
                try
                {
                    regBlockArray[i] = Convert.ToUInt32(valStr.Substring(2), 16);
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine(ex.Message);
                    MessageBox.Show(
                        "The value is invalid. Please enter a valid hex number.",
                        "Invalid Value",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
                    return;
                }
                catch (FormatException ex)
                {
                    Debug.WriteLine(ex.Message);
                    MessageBox.Show(
                        "The value \"" + valStr.Substring(2) + "\" is invalid.",
                        "Invalid Value",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
                    return;
                }
                catch (OverflowException ex)
                {
                    Debug.WriteLine(ex.Message);
                    MessageBox.Show(
                       "The value \"" + valStr.Substring(2) + "\" is too large. Please enter a valid register address.",
                        "Invalid Value",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
                    return;
                }
            }

            if (m_registerSet == RegisterSet.REGISTER_SET_IIDC)
            {
                try
                {
                    m_camera.WriteRegisterBlock(0xFFFF, m_lastRegBlockOffset + 0xF0F00000, regBlockArray);
                }
                catch (FC2Exception ex)
                {
                    string error = string.Format(
                                    "There was an error writing register block {0:x} - {1:x}.",
                                    m_lastRegBlockOffset, 
                                    m_lastRegBlockOffset + (4 * numQuadlets));
                    ShowErrorMessageDialog(error, ex);
                    ex.Dispose();
                    return;
                }
            }
            else if (m_registerSet == RegisterSet.REGISTER_SET_GEV)
            {
                if (IsGEV() != true)
                {
                    return;
                }

                ManagedGigECamera camera = (ManagedGigECamera)m_camera;
                try
                {
                    camera.WriteGVCPRegisterBlock(m_lastRegBlockOffset, regBlockArray);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog(
                        string.Format(
                        "There was an error writing GVCP register block 0x{0:X8} - 0x{1:X8}.",
                        m_lastRegBlockOffset, 
                        m_lastRegBlockOffset + (4 * numQuadlets)), 
                        ex);
                    ex.Dispose();
                }
            }
        }
    }
}
