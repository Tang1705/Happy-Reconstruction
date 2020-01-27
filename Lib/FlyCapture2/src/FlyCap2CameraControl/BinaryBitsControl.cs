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

namespace FlyCap2CameraControl
{
    internal partial class BinaryBitsControl : UserControl
    {
        private Label[] m_bitLabels;

        public BinaryBitsControl(uint initialNumberOfBits, string location)
        {
            InitializeComponent();
            CreateBinaryBits(initialNumberOfBits);
            m_relatedLocationLabel.Text = location;
        }

        public void SetValue(uint newValue)
        {
            if (newValue < 16)
            {
                // keep double digits
                m_regValTextBox.Text = String.Format("0{0:x}", newValue);
            }
            else
            {
                m_regValTextBox.Text = String.Format("{0:x}", newValue);
            }
        }

        public uint GetRegisterValue()
        {
            return Convert.ToUInt32(m_regValTextBox.Text, 16);
        }

        private void CreateBinaryBits(uint numberOfBits)
        {
            int individualBitWidth = 8;
            this.Width = individualBitWidth * (int)numberOfBits;

            // Make sure text box and label are centered
            m_regValTextBox.Left = (this.Width - m_regValTextBox.Width) / 2;
            m_relatedLocationLabel.Left = (this.Width - m_relatedLocationLabel.Width) / 2;

            m_bitLabels = new Label[numberOfBits];
            for (int i = 0; i < numberOfBits; i++)
            {
                Label newBitLabel = new Label();
                newBitLabel.Text = "0";
                newBitLabel.AutoSize = false;
                newBitLabel.Visible = true;
                newBitLabel.Bounds = new Rectangle(0 + (individualBitWidth * i), 25, individualBitWidth, 13);
                newBitLabel.TextAlign = ContentAlignment.TopLeft;
                newBitLabel.Click += new EventHandler(OnBitLabelClick);
                newBitLabel.BackColor = Color.PaleGreen;
                newBitLabel.UseCompatibleTextRendering = true;
                this.Controls.Add(newBitLabel);
                m_bitLabels[i] = newBitLabel;
            }
        }

        private void OnBitLabelClick(object sender, EventArgs e)
        {
            Label label = (Label)sender;
            if (label.Text.Equals("0"))
            {
                label.Text = "1";
            }
            else
            {
                label.Text = "0";
            }

            uint currentValue = GetCurrentBitsValue();
            SetValue(currentValue);
        }

        private uint GetCurrentBitsValue()
        {
            uint result = 0;
            for (int i = 0; i < m_bitLabels.Length; i++)
            {
                result = (result << 1) + Convert.ToUInt32(m_bitLabels[i].Text);
            }

            return result;
        }

        private void OnRegisterValueTextChanged(object sender, EventArgs e)
        {
            TextBox textBox = (TextBox)sender;
            if (ValidateHexValue(textBox) == false)
            {
                Debug.WriteLine("Invalid Hex Value");
                return;
            }

            uint regVal = GetRegisterValue();

            for (int i = 0; i < m_bitLabels.Length; i++)
            {
                uint bit = (regVal >> i) % 2;
                m_bitLabels[m_bitLabels.Length - i - 1].Text = bit.ToString();
            }
        }

        private bool ValidateHexValue(TextBox textBox)
        {          
            try
            {
                Convert.ToUInt32(textBox.Text, 16);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Unrecognized hex value: " + textBox.Text);
                return false;
            }

            return true;
        }
    }
}
