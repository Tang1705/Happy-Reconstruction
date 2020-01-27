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

     //internal partial class FrameBufferPage : UserControl
    internal partial class FrameBufferPage : BasePage
    {
        private const uint k_frameBufferRegIIDC = 0x634;
        private const uint k_frameBufferReg = 0x12E8;
        private bool m_isIIDC;

        private Timer m_updateTimer = new Timer();

        public FrameBufferPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitalizePage();
        }

        private void OnTimer(object o, EventArgs eventArgs)
        {

            if (m_camera == null ||
                IsFrameBufferSupported() == false)
            {
                //Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            if (m_isPageSelected)
            {
                if (m_enableImageHoldCheckBox.Checked == true)
                {
                    uint numOfBuffers = GetNumBuffers();
                    if (m_isIIDC)
                    {
                        m_currentSelectedImageTrackbar.Minimum = 1;
                        m_currentSelectedImageTrackbar.Maximum = (int)numOfBuffers;
                    }
                    else
                    {
                        m_currentSelectedImageTrackbar.Minimum = 0;
                        m_currentSelectedImageTrackbar.Maximum = (int)numOfBuffers - 1;
                    }

                    // Fix for Bug 21553
                    m_currentSelectedImageValue.Text = m_currentSelectedImageTrackbar.Value.ToString();
    
                    m_currentSelectedImageTrackbar.TickFrequency = m_currentSelectedImageTrackbar.Maximum / 10;
                    m_totalBufferValue.Text = numOfBuffers.ToString();
                    m_bufferUsedValue.Text = GetNumUsedBuffers().ToString();
                }
            }
        }

        private void InitalizePage()
        {
            if (m_camera == null)
            {
                //Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            m_isIIDC = false;
            if (IsFrameBufferSupported() == false)
            {
                m_enableImageHoldCheckBox.Enabled = false;
                return;
            }

            m_enableImageHoldCheckBox.Checked = IsFrameBufferEnabled();
            if (m_isIIDC)
            {
                m_frameBufferTypeValue.Text = "IIDC 1.32";
            }
            else
            {
                m_frameBufferTypeValue.Text = "PGR";
            }

            m_totalBufferValue.Text = GetNumBuffers().ToString();
            m_bufferUsedValue.Text = GetNumUsedBuffers().ToString();

            if (m_isIIDC)
            {
                m_currentSelectedImageTrackbar.Minimum = 1;
            }
            else
            {
                m_currentSelectedImageTrackbar.Minimum = 0;
            }

            // Fix for Bug 21553
            m_currentSelectedImageValue.Text = m_currentSelectedImageTrackbar.Value.ToString();

            m_updateTimer.Tick += new EventHandler(OnTimer);
            m_updateTimer.Interval = 100;
            m_updateTimer.Start();
        }

        private uint GetFrameBufferRegister()
        {
            uint frameBufferReg;
            if (m_isIIDC == true)
            {
                frameBufferReg = k_frameBufferRegIIDC;
            }
            else
            {
                frameBufferReg = k_frameBufferReg;
            }

            return frameBufferReg;
        }

        private bool IsFrameBufferSupported()
        {
            uint value = 0;
            const uint k_basicFuncInq = 0x400;
            try
            {
                value = m_camera.ReadRegister(k_basicFuncInq);
            }
            catch (FC2Exception ex)
            {
                ex.Dispose();
                return false;
            }

            if ((value & (0x1 << 10)) != 0)
            {
                m_isIIDC = true;
                return true;
            }
            else
            {
                m_isIIDC = false;

                // Check if the PGR mode is supported as a fallback for the 
                // IIDC mode
                try
                {
                    value = m_camera.ReadRegister(k_frameBufferReg);
                }
                catch (FC2Exception ex)
                {
                    ex.Dispose();
                    return false;
                }

                return (value >> 31) != 0;
            }
        }

        private bool IsFrameBufferEnabled()
        {
            uint value = 0;
            uint frameBufferReg = GetFrameBufferRegister();

            try
            {
                value = m_camera.ReadRegister(frameBufferReg);
            }
            catch (FC2Exception ex)
            {
                ex.Dispose();
                return false;
            }

            if (m_isIIDC)
            {
                return (value >> 31) != 0;
            }
            else
            {
                return (value & (0x1 << 25)) != 0;
            }
        }        

        private void OnEnableImageHoldCheckedStatusChanged(object sender, EventArgs e)
        {
            uint value = 0;
            uint frameBufferReg = GetFrameBufferRegister();
            try
            {
                value = m_camera.ReadRegister(frameBufferReg);
            }
            catch (FC2Exception ex)
            {
                m_imageSelectionControlPanel.Enabled = false;
                m_enableImageHoldCheckBox.Checked = false;
                ex.Dispose();
                return;
            }

            bool enableImageHold = m_enableImageHoldCheckBox.Checked;
            m_imageSelectionControlPanel.Enabled = enableImageHold;
            if (m_isIIDC)
            {
                if (enableImageHold == true)
                {
                    value |= 0xC0000000;
                    DisableIso();
                }
                else
                {
                    value &= ~0xC0000000;
                    EnableIso();
                }
            }
            else
            {
                if (enableImageHold == true)
                {
                    value |= (uint)(0x1 << 25);
                }
                else
                {
                    value &= ~(uint)(0x1 << 25);
                }
            }

            try
            {
                m_camera.WriteRegister(frameBufferReg, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing frame buffer register", ex);
                ex.Dispose();
            }
        }

        private void DisableIso()
        {
            if (m_isIIDC == false)
            {
                return;
            }

            const uint k_isoReg = 0x614;
            try
            {
                m_camera.WriteRegister(k_isoReg, 0x00000000);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error disabling isochronous transfer", ex);
                ex.Dispose();
            }
        }

        private void EnableIso()
        {
            if (m_isIIDC == false)
            {
                return;
            }

            const uint k_isoReg = 0x614;
            try
            {
                m_camera.WriteRegister(k_isoReg, 0x80000000);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error enabling isochronous transfer", ex);
                ex.Dispose();
            }
        }

        private uint GetNumBuffers()
        {
            uint value = 0;
            uint frameBufferReg = GetFrameBufferRegister();

            try
            {
                value = m_camera.ReadRegister(frameBufferReg);
            }
            catch (FC2Exception ex)
            {
                Debug.Write("fail to read frame buffer value from register.");
                ex.Dispose();
                return 0;
            }

            if (m_isIIDC)
            {
                return (value & 0x00FFF000) >> 12;
            }
            else
            {
                return (value & 0x0000FF00) >> 8;
            }
        }

        private uint GetNumUsedBuffers()
        {
            uint value = 0;
            uint frameBufferReg = GetFrameBufferRegister();

            try
            {
                value = m_camera.ReadRegister(frameBufferReg);
            }
            catch (FC2Exception ex)
            {
                Debug.Write("fail to read frame buffer value from register.");
                ex.Dispose();
                return 0;
            }

            if (m_isIIDC)
            {
                return value & 0x00000FFF;
            }
            else
            {
                return value & 0x000000FF;
            }
        }

        private void OnTransmitImageTrackbarValueChanged(object sender, EventArgs e)
        {
            m_currentSelectedImageValue.Text = m_currentSelectedImageTrackbar.Value.ToString();
        }

        private void OnTransmitSelectedImage(object sender, EventArgs e)
        {
            uint position = (uint)m_currentSelectedImageTrackbar.Value;
            uint value = 0;
            const uint k_oneShotReg = 0x61C;
            uint frameBufferReg;
            if (m_isIIDC)
            {
                frameBufferReg = k_oneShotReg;
            }
            else
            {
                frameBufferReg = k_frameBufferReg;
            }

            try
            {
                value = m_camera.ReadRegister(frameBufferReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading frame buffer register", ex);
                ex.Dispose();
                return;
            }

            if (m_isIIDC)
            {
                // Make sure one shot is disabled, and multishot is enabled
                value &= ~((uint)0x1 << 31);
                value |= (uint)0x1 << 30;

                value &= ~(uint)0xFFFF;
                value += position;
            }
            else
            {
                value &= ~(uint)0xFF;
                value += position;
            }

            try
            {
                m_camera.WriteRegister(frameBufferReg, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing frame buffer register", ex);
                ex.Dispose();
                return;
            }
        }

        private void OnRetransmitSelectedImage(object sender, EventArgs e)
        {
            uint value = 0;
            const uint k_oneShotReg = 0x61C;
            uint frameBufferReg;
            if (m_isIIDC)
            {
                frameBufferReg = k_oneShotReg;
            }
            else
            {
                frameBufferReg = k_frameBufferReg; 
            }

            try
            {
                value = m_camera.ReadRegister(frameBufferReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading frame buffer register", ex);
                ex.Dispose();
                return;
            }

            if (m_isIIDC)
            {
                // Make sure multishot is disabled, and one shot is enabled
                value &= ~((uint)0x1 << 30);
                value |= (uint)0x1 << 31;

                value &= ~(uint)0xFFFF;
            }
            else
            {
                value &= ~(uint)0xFF;
            } 

            try
            {
                m_camera.WriteRegister(frameBufferReg, value);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error writing frame buffer register", ex);
                ex.Dispose();
                return;
            }
        }
    }
}
