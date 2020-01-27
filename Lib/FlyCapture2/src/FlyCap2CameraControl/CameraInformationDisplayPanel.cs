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
    internal partial class CameraInformationDisplayPanel : UserControl
    {
        private ManagedCameraBase m_camera;                
        private bool m_isLadybug2 = false;
        private bool m_driverIsCompatible = true;
        private string m_driverTooltipText = string.Empty;
        private ToolTip m_driverTooltip;

        public CameraInformationDisplayPanel()
        {
            m_camera = null;
            m_isLadybug2 = false;
            InitializeComponent();
        }

        public CameraInformationDisplayPanel(bool isLadybug2)
        {            
            m_camera = null;
            m_isLadybug2 = isLadybug2;
            InitializeComponent();
        }

        public event EventHandler OnCopyClick;

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

        public bool IsLadybug2
        {
            get
            {
                return m_isLadybug2;
            }

            set
            {
                m_isLadybug2 = value;
            }
        }

        internal void SetDriverCompatibilityStatus(bool isCompatible, string tooltip)
        {
            m_driverIsCompatible = isCompatible;
            m_driverTooltipText = tooltip;
        }

        public void UpdateCameraInformation(CameraInfo cameraInfo)
        {
            m_model.Text = cameraInfo.modelName;
            m_vendor.Text = cameraInfo.vendorName;
            m_sensor.Text = cameraInfo.sensorInfo;
            m_resolution.Text = cameraInfo.sensorResolution;
            m_interface.Text = InterfaceTranslator.GetInterfaceString(cameraInfo.interfaceType);
            m_busSpeed.Text = BusSpeedTranslator.GetBusSpeedString(cameraInfo.maximumBusSpeed);
            m_pciEBusSpeed.Text = BusSpeedTranslator.GetPCIeBusSpeedString(cameraInfo.pcieBusSpeed);
            m_iidcVersion.Text = string.Format("{0:0.##}", (float)cameraInfo.iidcVersion / 100.0f);
            m_firmwareVersion.Text = cameraInfo.firmwareVersion;
            m_firmwareBuildTime.Text = cameraInfo.firmwareBuildTime;
            m_driver.Text = cameraInfo.driverName;

            if (m_camera == null || m_camera.IsConnected() == false)
            {
                Debug.WriteLine("Camera not found or disconnected");
                ClearInformation();
                return;
            }

            if (cameraInfo.interfaceType == InterfaceType.Usb3 && 
                cameraInfo.pcieBusSpeed == PCIeBusSpeed.Speed_2_5)
            {
                // Insufficient speed, set the text to red
                m_pciEBusSpeed.ForeColor = Color.Red;
                toolTipPCIeBusSpeed.SetToolTip(m_pciEBusSpeed, "PCIe bus speed is too low - USB 3.0 performance may be degraded");
                toolTipPCIeBusSpeed.Active = true;
            }
            else
            {
                m_pciEBusSpeed.ForeColor = m_pciEBusSpeedLabel.ForeColor;
                toolTipPCIeBusSpeed.Active = false;
            }

            if (cameraInfo.interfaceType == InterfaceType.GigE && !m_driverIsCompatible)
            {
                m_driver.ForeColor = Color.Red;
                if (m_driverTooltip == null)
                {
                    m_driverTooltip = new ToolTip();
                }
                m_driverTooltip.SetToolTip(m_driver, m_driverTooltipText);
                m_driverTooltip.Active = true;
            }
            else
            {
                if (m_driverTooltip == null)
                {
                    m_driverTooltip = new ToolTip();
                }
                m_driver.ForeColor = m_driverLabel.ForeColor;
                m_driverTooltip.Active = false;
            }

            if (IsLadybug2)
            {
                const uint Ladybug2HeadRegAddress = 0x1F80;
                uint uiHeadNumber = 0;
                try
                {
                    uiHeadNumber = m_camera.ReadRegister(Ladybug2HeadRegAddress);
                }
                catch (FC2Exception ex)
                {
                    BasePage.ShowErrorMessageDialog("Unable to read head number in the register. Initialize camera information page failed.", ex);
                    ClearInformation();
                    ex.Dispose();
                    return;
                }

                m_serialNumber.Text = string.Format("{0} (Head S/N.{1}", cameraInfo.serialNumber, uiHeadNumber);
            }
            else
            {
                m_serialNumber.Text = cameraInfo.serialNumber.ToString();
            }            
        }

        public void UpdateBadCameraInformation(CameraInfo cameraInfo)
        {
            m_model.Text = cameraInfo.modelName;
            m_vendor.Text = cameraInfo.vendorName;
            m_sensor.Text = "N/A";
            m_resolution.Text = "N/A";
            m_interface.Text = InterfaceTranslator.GetInterfaceString(cameraInfo.interfaceType);
            m_busSpeed.Text = BusSpeedTranslator.GetBusSpeedString(cameraInfo.maximumBusSpeed);
            m_pciEBusSpeed.Text = BusSpeedTranslator.GetPCIeBusSpeedString(cameraInfo.pcieBusSpeed);
            m_iidcVersion.Text = "N/A";
            m_firmwareVersion.Text = "N/A";
            m_firmwareBuildTime.Text = "N/A";
            m_driver.Text = "N/A";


            if (cameraInfo.interfaceType == InterfaceType.Usb3 &&
                cameraInfo.pcieBusSpeed == PCIeBusSpeed.Speed_2_5)
            {
                // Insufficient speed, set the text to red
                m_pciEBusSpeed.ForeColor = Color.Red;
                toolTipPCIeBusSpeed.SetToolTip(m_pciEBusSpeed, "PCIe bus speed is too low - USB 3.0 performance may be degraded");
                toolTipPCIeBusSpeed.Active = true;
            }
            else
            {
                m_pciEBusSpeed.ForeColor = m_pciEBusSpeedLabel.ForeColor;
                toolTipPCIeBusSpeed.Active = false;
            }

            // Reset tooltip and text color
            if (m_driverTooltip == null)
            {
                m_driverTooltip = new ToolTip();
            }

            m_driver.ForeColor = m_driverLabel.ForeColor;
            m_driverTooltip.Active = false;

            if (IsLadybug2)
            {
                const uint Ladybug2HeadRegAddress = 0x1F80;
                uint uiHeadNumber = 0;
                try
                {
                    uiHeadNumber = m_camera.ReadRegister(Ladybug2HeadRegAddress);
                }
                catch (FC2Exception ex)
                {
                    BasePage.ShowErrorMessageDialog("Unable to read head number in the register. Initialize camera information page failed.", ex);
                    ClearInformation();
                    ex.Dispose();
                    return;
                }

                m_serialNumber.Text = string.Format("{0} (Head S/N.{1}", cameraInfo.serialNumber, uiHeadNumber);
            }
            else
            {
                m_serialNumber.Text = cameraInfo.serialNumber.ToString();
            }
        }

        public void ClearInformation()
        {
            m_serialNumber.Text = "N/A";
            m_model.Text = "N/A";
            m_sensor.Text = "N/A";
            m_vendor.Text = "N/A";
            m_resolution.Text = "N/A";
            m_interface.Text = "N/A";
            m_busSpeed.Text = "N/A";
            m_pciEBusSpeed.Text = "N/A";
            m_pciEBusSpeed.ForeColor = m_pciEBusSpeedLabel.ForeColor;
            m_iidcVersion.Text = "N/A";
            m_firmwareVersion.Text = "N/A";
            m_firmwareBuildTime.Text = "N/A";
            m_driver.Text = "N/A";

            // Reset driver text color and tooltip
            try
            {
                m_driver.ForeColor = m_driverLabel.ForeColor;
                m_driverTooltip.Active = false;
            }
            catch (Exception /*ex*/)
            {
            }
        }

        public void SetCopyButtonVisible(bool isVisible)
        {
            m_copyButton.Visible = isVisible;
        }

        public string GenerateClipboardText()
        {
            StringBuilder clipboardStr = new StringBuilder();
            clipboardStr.AppendFormat("{0} {1}{2}", m_serialNumberLabel.Text, m_serialNumber.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_vendorLabel.Text, m_vendor.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_modelLabel.Text, m_model.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_sensorLabel.Text, m_sensor.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_resolutionLabel.Text, m_resolution.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_interfaceLabel.Text, m_interface.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_busSpeedLabel.Text, m_busSpeed.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_pciEBusSpeedLabel.Text, m_pciEBusSpeed.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_iidcVersionLabel.Text, m_iidcVersion.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_firmwareVersionLabel.Text, m_firmwareVersion.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_firmwareBuildTimeLabel.Text, m_firmwareBuildTime.Text, Environment.NewLine);
            clipboardStr.AppendFormat("{0} {1}{2}", m_driverLabel.Text, m_driver.Text, Environment.NewLine);
            return clipboardStr.ToString();
        }

        private void OnCopyButtonClick(object sender, EventArgs e)
        {
            if (OnCopyClick != null)
            {
                OnCopyClick(sender, e);
            }
            else
            {
                try
                {
                    Clipboard.SetText(GenerateClipboardText());
                }
                catch (ArgumentNullException ex)
                {
                    MessageBox.Show("Nothing in clipboard.", "FlyCapture2", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
                catch (System.Threading.ThreadStateException ex)
                {
                    BasePage.ShowErrorMessageDialog("Error copying text to clipboard. The copying thread is invalid", ex);
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
            }
        }       
    }
}