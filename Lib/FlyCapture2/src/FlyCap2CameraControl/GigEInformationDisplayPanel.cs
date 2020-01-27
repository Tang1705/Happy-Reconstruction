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
    internal partial class GigEInformationDisplayPanel : UserControl
    {
        private ManagedCameraBase m_camera;
        private ToolTip m_tooltip = new ToolTip();

        public GigEInformationDisplayPanel()
        {
            m_camera = null;
            InitializeComponent();
        }

        public ManagedCameraBase Camera
        {
            get
            {
                return m_camera;
            }

            set
            {
                m_camera = value;
            }
        }

        public void UpdateGigECameraInformation(CameraInfo cameraInfo)
        {
            if (m_camera == null || m_camera.IsConnected() == false)
            {
                Debug.WriteLine("Camera not found or disconnected");
                return;
            }

            if (cameraInfo.interfaceType != InterfaceType.GigE)
            {
                string blankStr = "N/A";
                m_versionValue.Text = blankStr;
                m_userDefNameValue.Text = blankStr;
                m_xmlURL1Value.Text = blankStr;
                m_xmlURL2Value.Text = blankStr;
                m_macAddressValue.Text = blankStr;
                m_ipValue.Text = blankStr;
                m_subnetMaskValue.Text = blankStr;
                m_defaultGatewayValue.Text = blankStr;

                m_lblLLAStatus.Text = blankStr;
                m_lblDHCPStatus.Text =  blankStr;
                m_lblPersistentIPStatus.Text = blankStr;

                return;
            }

            m_versionValue.Text = string.Format("{0}.{1}", cameraInfo.gigEMajorVersion, cameraInfo.gigEMinorVersion);
            m_userDefNameValue.Text = cameraInfo.userDefinedName;
            m_xmlURL1Value.Text = cameraInfo.xmlURL1;
            m_xmlURL2Value.Text = cameraInfo.xmlURL2;
            byte[] macAddrBytes = cameraInfo.macAddress.GetAddressBytes();
            m_macAddressValue.Text = string.Format(
                "{0:X2}:{1:X2}:{2:X2}:{3:X2}:{4:X2}:{5:X2}",
                macAddrBytes[0],
                macAddrBytes[1],
                macAddrBytes[2],
                macAddrBytes[3],
                macAddrBytes[4],
                macAddrBytes[5]);
            m_ipValue.Text = cameraInfo.ipAddress.ToString();
            m_subnetMaskValue.Text = cameraInfo.subnetMask.ToString();
            m_defaultGatewayValue.Text = cameraInfo.defaultGateway.ToString();

            m_ipValue.ForeColor = Color.Black;
            m_subnetMaskValue.ForeColor = Color.Black;
            m_defaultGatewayValue.ForeColor = Color.Black;

            m_tooltip.RemoveAll();

            try
            {
                ManagedGigECamera gigECam = (ManagedGigECamera)m_camera;
                uint ipConfigurationVal = gigECam.ReadGVCPRegister(0x0014);
                m_lblLLAStatus.Text = string.Format("{0}", (ipConfigurationVal & 0x4) != 0 ? "Enabled" : "Disabled");
                m_lblDHCPStatus.Text = string.Format("{0}", (ipConfigurationVal & 0x2) != 0 ? "Enabled" : "Disabled");
                m_lblPersistentIPStatus.Text = string.Format("{0}", (ipConfigurationVal & 0x1) != 0 ? "Enabled" : "Disabled");
            }
            catch (InvalidCastException)
            {
                Debug.WriteLine("Camera is not a GigE camera");
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Failed to read IP configuration status: " + ex.Message);
                ex.Dispose();
            }
        }

        public void UpdateBadGigECameraInformation(CameraInfo cameraInfo)
        {
            if (cameraInfo.interfaceType != InterfaceType.GigE)
            {
                string blankStr = "N/A";
                m_versionValue.Text = blankStr;
                m_userDefNameValue.Text = blankStr;
                m_xmlURL1Value.Text = blankStr;
                m_xmlURL2Value.Text = blankStr;
                m_macAddressValue.Text = blankStr;
                m_ipValue.Text = blankStr;
                m_subnetMaskValue.Text = blankStr;
                m_defaultGatewayValue.Text = blankStr;

                m_lblLLAStatus.Text = blankStr;
                m_lblDHCPStatus.Text = blankStr;
                m_lblPersistentIPStatus.Text = blankStr;

                return;
            }

            m_versionValue.Text = string.Format("{0}.{1}", cameraInfo.gigEMajorVersion, cameraInfo.gigEMinorVersion);
            m_userDefNameValue.Text = cameraInfo.userDefinedName;
            m_xmlURL1Value.Text = "N/A";
            m_xmlURL2Value.Text = "N/A";
            byte[] macAddrBytes = cameraInfo.macAddress.GetAddressBytes();
            m_macAddressValue.Text = string.Format(
                "{0:X2}:{1:X2}:{2:X2}:{3:X2}:{4:X2}:{5:X2}",
                macAddrBytes[0],
                macAddrBytes[1],
                macAddrBytes[2],
                macAddrBytes[3],
                macAddrBytes[4],
                macAddrBytes[5]);
            m_ipValue.Text = cameraInfo.ipAddress.ToString();
            m_subnetMaskValue.Text = cameraInfo.subnetMask.ToString();
            m_defaultGatewayValue.Text = cameraInfo.defaultGateway.ToString();

            m_ipValue.ForeColor = Color.Red;
            m_subnetMaskValue.ForeColor = Color.Red;
            m_defaultGatewayValue.ForeColor = Color.Red;

            m_tooltip.ShowAlways = true;
            m_tooltip.SetToolTip(m_ipValue, "Incorrect IP configuration. Use \"Force IP\" to correct it");
            m_tooltip.SetToolTip(m_subnetMaskValue, "Incorrect IP configuration. Use \"Force IP\" to correct it");
            m_tooltip.SetToolTip(m_defaultGatewayValue, "Incorrect IP configuration. Use \"Force IP\" to correct it");

            m_lblLLAStatus.Text = "N/A";
            m_lblDHCPStatus.Text = "N/A";
            m_lblPersistentIPStatus.Text = "N/A";
        }

        public string GenerateClipboardText()
        {
            StringBuilder clipboardStr = new StringBuilder();
            clipboardStr.AppendFormat("{0} {1}{2}", m_versionLabel.Text, m_versionValue.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_userDefNameLabel.Text, m_userDefNameValue.Text, Environment.NewLine);
            //clipboardStr.AppendFormat("{0} {1}{2}", m_xmlURL1Label.Text, m_xmlURL1Value.Text, Environment.NewLine);
            //clipboardStr.AppendFormat("{0} {1}{2}", m_xmlURL2Label.Text, m_xmlURL2Value.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_macAddressLabel.Text, m_macAddressValue.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_ipLabel.Text, m_ipValue.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_subnetMaskLabel.Text, m_subnetMaskValue.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_defaultGatewayLabel.Text, m_defaultGatewayValue.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}",    m_ipAssignemtLabel.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0}: {1}{2}", m_lblLLA.Text, m_lblLLAStatus.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0}: {1}{2}", m_lblDHCP.Text, m_lblDHCPStatus.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0}: {1}{2}", m_lblPersistentIP.Text, m_lblPersistentIPStatus.Text, Environment.NewLine);
            return clipboardStr.ToString();
        }
    }
}
