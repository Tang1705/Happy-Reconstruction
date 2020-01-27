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
    internal partial class BasePage : UserControl
    {        
        protected const uint iidcVersion = 132;
        protected ManagedCameraBase m_camera = null;
        protected CameraInfo m_camInfo = null;
        protected bool m_isConnected = false;
        protected bool m_isPageSelected = false;

        private static ManagedCamera blankCamera = new ManagedCamera();
        private static ManagedGigECamera blankGigECamera = new ManagedGigECamera();
        
        public BasePage()
        {
            InitializeComponent();
        }

        public BasePage(ManagedCameraBase camera)
        {
            SetCamera(camera);
            InitializeComponent();
        }

        public static void ShowErrorMessageDialog(string customMessage, Exception ex)
        {
#if DEBUG
            string error = customMessage + Environment.NewLine + ex.Message + Environment.NewLine + ex.StackTrace;
#else
            string error = customMessage + Environment.NewLine + ex.Message;
#endif

            MessageBox.Show(
                    error,
                    "FlyCapture2 Camera Control",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
        }   

        public void SetCamera(ManagedCameraBase camera)
        {
            Debug.Assert(camera != null, "Camera object is null!");

            m_camera = camera;
            SetCameraInfo(m_camera);
        }

        public void SetConnectStatus(bool isConnected)
        {
            m_isConnected = isConnected;
            if (isConnected == false && m_camera != null)
            {
                m_camera = null;
                m_camInfo = null;
            }
        }

        public void SetCameraInfo(ManagedCameraBase camera)
        {
            try
            {
                m_camInfo = camera.GetCameraInfo();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error getting camera information.", ex);
                ex.Dispose();
                return;
            }
        }

        public void IsPageSelected(bool isSelected)
        {
            m_isPageSelected = isSelected;
        }

        protected bool IsIIDC()
        {
            Debug.Assert(m_camera != null, "Current camera can not be null.");
            if (m_camera == null)
            {
                // Bad!
                return false;
            }

            bool isIIDC = m_camera.GetType() == blankCamera.GetType();
            
            return isIIDC;
        }

        protected bool IsGEV()
        {
            Debug.Assert(m_camera != null, "Current camera can not be null.");
            if (m_camera == null)
            {
                // Bad!
                return false;
            }

            bool isGEV = m_camera.GetType() == blankGigECamera.GetType();

            return isGEV;
        }

        protected bool IsPacketResendSupported()
        {
            try
            {
                ManagedGigECamera gigECam = (ManagedGigECamera)m_camera;
                uint regVal = gigECam.ReadGVCPRegister(0x0934);
                if ((regVal & 0x4) != 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch
            {
                return false;
            }
        }

        protected bool IsLadybugModel()
        {
            return LadybugChecker.IsLadybug(m_camInfo);
        }

        protected bool IsLadybug2()
        {
            return LadybugChecker.IsLadybug2(m_camInfo);
        }

        protected bool IsLadybug3()
        {
            return LadybugChecker.IsLadybug3(m_camInfo);
        }

        protected bool IsLadybug5()
        {
            return LadybugChecker.IsLadybug5(m_camInfo);
        }
        
        protected bool IsCameraStreaming()
        {
            uint isoRegVal = 0;
            try
            {
                const uint isoReg = 0x614;
                isoRegVal = m_camera.ReadRegister(isoReg);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine(string.Format("Error reading ISO_EN register. {0}", ex.Message));
                ex.Dispose();
                return false;
            }

            return (isoRegVal & 0x80000000) != 0;
        }             
    }    
}
