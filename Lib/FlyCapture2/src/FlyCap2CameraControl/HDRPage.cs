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
using System.Data;
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

    // internal partial class HDRPage : UserControl
    internal partial class HDRPage : BasePage
    {
        private const uint BumblebeeHDRReg = 0x1400;
        private const uint Ladybug2HDRReg = 0x13FC;
        private const uint HdrReg = 0x1800;
        private uint m_hdrRegIncrement = 0x4;

        private HDRPropertyControl[] m_hdrImageControls;
        private uint m_hdrRegOffset;

        private Timer m_updateTimer = new Timer();

        public HDRPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitializePage();
        }

        public ManagedCameraBase Camera
        {
            get
            {
                return m_camera;
            }
        }

        public bool IsHDRSupported()
        {
            uint value;
            try
            {
                value = m_camera.ReadRegister(m_hdrRegOffset);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading HDR register", ex);
                ex.Dispose();
                return false;
            }

            return (value >> 31) != 0;
        }

        private void OnTimer(object o, EventArgs eventArgs)
        {

            if (m_enableHDRCheckBox.Checked && m_isPageSelected)
            {
                for (int i = 0; i < 4; i++)
                {
                    m_hdrImageControls[i].UpdateControl();
                }
            }
        }

        public uint GetGain(int imageNumber)
        {
            uint regOffset = GetRegisterOffset(m_hdrRegOffset, imageNumber) + m_hdrRegIncrement;
            uint value;
            try
            {
                value = m_camera.ReadRegister(regOffset);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading HDR gain register", ex);
                ex.Dispose();
                return 0;
            }

            return value & 0x00000FFF;
        }

        public void SetGain(int imageNumber, uint gainValue)
        {
            uint regOffset = GetRegisterOffset(m_hdrRegOffset, imageNumber) + m_hdrRegIncrement;
            uint value;
            if (IsLadybug2() == true)
            {
                // LD2 camera
                value = 0x82000000 | gainValue;
            }
            else
            {
                try
                {
                    value = m_camera.ReadRegister(regOffset);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error reading HDR gain register", ex);
                    ex.Dispose();
                    return;
                }

                value &= ~(uint)0xFFF;
                value += gainValue;
            }

            try
            {
                m_camera.WriteRegister(regOffset, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing HDR gain register", ex);
                ex.Dispose();
            }
        }

        public uint GetShutter(int imageNumber)
        {
            uint regOffset = GetRegisterOffset(m_hdrRegOffset, imageNumber);
            uint value;
            try
            {
                value = m_camera.ReadRegister(regOffset);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading HDR shutter register", ex);
                ex.Dispose();
                return 0;
            }

            return value & 0x00000FFF;
        }

        public void SetShutter(int imageNumber, uint shutterValue)
        {
            uint regOffset = GetRegisterOffset(m_hdrRegOffset, imageNumber);
            uint value;
            if (IsLadybug2() == true)
            {
                // LD2 camera
                value = 0x82000000 | shutterValue;
            }
            else
            {
                try
                {
                    value = m_camera.ReadRegister(regOffset);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error reading HDR shutter register", ex);
                    ex.Dispose();
                    return;
                }

                value &= ~(uint)0xFFF;
                value += shutterValue;
            }

            try
            {
                m_camera.WriteRegister(regOffset, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing HDR shutter register", ex);
                ex.Dispose();
            }
        }

        private void InitializePage()
        {
            //add controls to the page
            m_hdrImageControls = new HDRPropertyControl[4];
            for (int i = 0; i < 4; i++)
            {
                m_hdrImageControls[i] = new HDRPropertyControl(this, i);
                m_hdrImageControls[i].Anchor = AnchorStyles.Left | AnchorStyles.Right;
                m_hDRangeControlPanel.Controls.Add(m_hdrImageControls[i], 0, i * 2);
            }

            if (m_camera == null)
            {
                //Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            try
            {
                m_hdrRegOffset = GetHDRRegOffset();
            }
            catch (FC2Exception ex)
            {
                m_mainGroupBox.Enabled = false;
                Debug.WriteLine("Unable to get Camera Info. {0}", ex.Message);
                ex.Dispose();
                return;
            }
            
            if (IsHDRSupported() == false)
            {
                m_enableHDRCheckBox.Enabled = false;
                m_enableHDRCheckBox.Checked = false;
                DisableHDRImageControls();
                return;
            }

            m_enableHDRCheckBox.Checked = IsHDREnabled();
            UpdateHDRImageControls();

            m_updateTimer.Tick += new EventHandler(OnTimer);
            m_updateTimer.Interval = 100;
            m_updateTimer.Start();
        }

        private bool IsHDREnabled()
        {
            uint value;
            try
            {
                value = m_camera.ReadRegister(m_hdrRegOffset);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading HDR register", ex);
                ex.Dispose();
                return false;
            }

            return (value & (0x1 << 25)) != 0; 
        }

        private void OnEnableHDRCheckedStatusChanged(object sender, EventArgs e)
        {
            uint value;
            try
            {
                value = m_camera.ReadRegister(m_hdrRegOffset);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading HDR offset register", ex);
                ex.Dispose();
                return;
            }

            if (m_enableHDRCheckBox.Checked == true)
            {
                value |= (uint)0x1 << 25;
            }
            else
            {
                value &= ~((uint)0x1 << 25);
            }

            try
            {
                m_camera.WriteRegister(m_hdrRegOffset, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing HDR offset register", ex);
                ex.Dispose();
            }

            UpdateHDRImageControls();
        }

        private void UpdateHDRImageControls()
        {
            if (m_enableHDRCheckBox.Checked)
            {
                EnableHDRImageControls();
            }
            else
            {
                DisableHDRImageControls();
            }
        }

        private void EnableHDRImageControls()
        {
            for (int i = 0; i < 4; i++)
            {
                m_hdrImageControls[i].EnableControl();
            }
        }

        private void DisableHDRImageControls()
        {
            for (int i = 0; i < 4; i++)
            {
                m_hdrImageControls[i].DisableControl();
            }
        }

        private uint GetRegisterOffset(uint regBase, int imageNumber)
        {
            uint regOffset = 0;

            switch (imageNumber)
            {
                case 0:
                    regOffset = regBase + 0x20;
                    break;
                case 1:
                    if (IsLadybug2())
                    {
                        regOffset = regBase + 0x60;
                    }
                    else
                    {
                        regOffset = regBase + 0x40;
                    }

                    break;
                case 2:
                    if (IsLadybug2())
                    {
                        regOffset = regBase + 0xA0;
                    }
                    else
                    {
                        regOffset = regBase + 0x60;
                    }

                    break;
                case 3:
                    if (IsLadybug2())
                    {
                        regOffset = regBase + 0xE0;
                    }
                    else
                    {
                        regOffset = regBase + 0x80;
                    }

                    break;
                default:
                    break;
            }

            return regOffset;
        }

        private uint GetHDRRegOffset()
        {
            uint hdrReg;
            ////m_hdrRegIncrement = 0x4;

            CameraInfo camInfo = m_camera.GetCameraInfo();

            if ((camInfo.modelName.Contains("Bumblebee") == true) &&
                (camInfo.modelName.Contains("Bumblebee2") == false))
            {
                // The camera is a Bumblebee, but not a Bumblebee2 or XB3
                hdrReg = BumblebeeHDRReg;
            }
            else
            {
                if (IsLadybug2())
                {
                    hdrReg = Ladybug2HDRReg;
                    m_hdrRegIncrement = 0x20;
                }
                else
                {
                    hdrReg = HdrReg;
                }
            }

            return hdrReg;
        }
    }
}
