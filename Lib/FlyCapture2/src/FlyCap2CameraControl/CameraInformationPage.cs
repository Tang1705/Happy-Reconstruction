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

    // internal partial class CameraInformationPage : UserControl
    internal partial class CameraInformationPage : BasePage
    {
        private CameraInformationDisplayPanel m_cameraInformationTable;
        private GigEInformationDisplayPanel m_gigEInformationTable;

        private Timer m_updateTimer = new Timer();

        public CameraInformationPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitializePage();
        }

        private void OnTimer(Object o, EventArgs eventArgs)
        {
            if (m_isPageSelected)
            {
                UpdatePage();
            }
        }

        public void ToggleConsoleLogVisibility()
        {
            m_consoleLabel.Visible = !m_consoleLabel.Visible;
            m_consoleLogTextBox.Visible = !m_consoleLogTextBox.Visible;
            m_copyConsoleLogButton.Visible = !m_copyConsoleLogButton.Visible;
            m_refreshConsoleLog.Visible = !m_refreshConsoleLog.Visible;
        }

        private static void ParseTimeRegister(uint timeRegVal, out uint hours, out uint mins, out uint seconds)
        {
            hours = timeRegVal / (60 * 60);
            mins = (timeRegVal - (hours * 60 * 60)) / 60;
            seconds = timeRegVal - (hours * 60 * 60) - (mins * 60);
        }        

        private void InitializePage()
        {
            InitializeBasicInformation();
            UpdatePage();
            m_updateTimer.Tick += new EventHandler(OnTimer);
            m_updateTimer.Interval = 100;
            m_updateTimer.Start();
        }

        private void InitializeBasicInformation()
        {
            m_cameraInformationTable = new CameraInformationDisplayPanel();
            m_cameraInformationTable.SetCopyButtonVisible(true);
            m_cameraInformationTable.OnCopyClick += new EventHandler(OnCopyButtonClick);
            m_cameraInformationTable.Dock = DockStyle.Fill;
            m_basicInfoPanel.Controls.Add(m_cameraInformationTable);

            m_gigEInformationTable = new GigEInformationDisplayPanel();
            m_gigEInformationTable.Dock = DockStyle.Fill;
            m_gigEInfoPanel.Controls.Add(m_gigEInformationTable);

            if (m_camera == null || m_camera.IsConnected() == false)
            {
                return;
            }          

            m_cameraInformationTable.Camera = m_camera;
            m_cameraInformationTable.UpdateCameraInformation(m_camInfo);
            m_basicInfoPanel.Height = m_cameraInformationTable.MinimumSize.Height;
            if (m_camInfo.interfaceType != InterfaceType.GigE)
            {
                m_gigeLabel.Hide();
                m_gigEInformationTable.Hide();
                m_mainTableLayoutPanel.Controls.Remove(m_gigEInfoPanel);
                m_mainTableLayoutPanel.SetColumnSpan(m_basicInfoPanel, 2);
            }
            else
            {
                m_gigEInformationTable.Camera = m_camera;
                m_gigEInformationTable.UpdateGigECameraInformation(m_camInfo);
                m_gigEInfoPanel.Height = m_gigEInformationTable.MinimumSize.Height;
                m_gigeLabel.Show();
                m_gigEInformationTable.Show();
            }
        }

        private void OnCopyButtonClick(object sender, EventArgs e)
        {
            string stringToCopy;
            if (m_camInfo.interfaceType == InterfaceType.GigE)
            {
                stringToCopy = string.Format(
                "{0}{1}{1}{2}",
                m_cameraInformationTable.GenerateClipboardText(),
                Environment.NewLine,
                m_gigEInformationTable.GenerateClipboardText());
            }
            else
            {
                stringToCopy = m_cameraInformationTable.GenerateClipboardText();
            }

            try
            {
                Clipboard.SetText(stringToCopy);
            }
            catch (ArgumentNullException ex)
            {
                MessageBox.Show("Nothing in clipboard.", "FlyCapute2 message", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }
            catch (System.Threading.ThreadStateException ex)
            {
                BasePage.ShowErrorMessageDialog("Error copying text to clipboad. The copying thread is invalid", ex);
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }
        }

        private void UpdatePage()
        {
            if (m_camera == null)
            {
                // Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            UpdateInitializeTime();
            UpdateBusResetTime();
            UpdateTransmitFailures();
            UpdatePixelClockFreq();
            UpdateHorizontalLineFreq();
        }

        private void UpdateInitializeTime()
        {
            const uint k_initializeTimeReg = 0x12E0;
            uint initializeTimeRegVal = 0;
            try
            {
                initializeTimeRegVal = m_camera.ReadRegister(k_initializeTimeReg);
            }
            catch (FC2Exception ex)
            {
                m_timeSinceInit.Text = "N/A";
                Debug.WriteLine("Error reading value of \"time since initialization\".");
                ex.Dispose();
                return;
            }

            uint numHours, numMins, numSeconds;
            ParseTimeRegister(initializeTimeRegVal, out numHours, out numMins, out numSeconds);
            m_timeSinceInit.Text = string.Format("{0}h {1}m {2}s", numHours, numMins, numSeconds);
        }

        private void UpdateBusResetTime()
        {
            uint k_busResetTimeReg = 0x12E4;  
            uint busResetTimeRegVal = 0;

            try
            {
                busResetTimeRegVal = m_camera.ReadRegister(k_busResetTimeReg);
            }
            catch (FC2Exception ex)
            {
               m_timeSinceLastBusReset.Text = "N/A";
               Debug.WriteLine("Error reading value of \"time since last bus reset\".");
                ex.Dispose();
                return;
            }

            uint numHours, numMins, numSeconds;
            ParseTimeRegister(busResetTimeRegVal, out numHours, out numMins, out numSeconds);
            m_timeSinceLastBusReset.Text = string.Format("{0}h {1}m {2}s", numHours, numMins, numSeconds);       
        }

        private void UpdateTransmitFailures()
        {
            uint k_transmitFailureReg = 0x12FC;
            uint transmitFailureRegVal = 0;
            CameraInfo cameraInfo;
            try
            {
                cameraInfo = m_camera.GetCameraInfo();
            }
            catch (FC2Exception ex)
            {
                m_transmitFailures.Text = "N/A";
                Debug.WriteLine("Error getting camera information.");
                ex.Dispose();
                return;
            }

            try
            {
                transmitFailureRegVal = m_camera.ReadRegister(k_transmitFailureReg);
            }
            catch (FC2Exception ex)
            {
                m_transmitFailures.Text = "N/A";
                Debug.WriteLine("Error reading value of \"transmit failures\".");
                ex.Dispose();
                return;
            }

            if (cameraInfo.iidcVersion >= 132 && (transmitFailureRegVal & 0x80000000) == 0)
            {
                m_transmitFailures.Text = "N/A";
                return;
            }

            transmitFailureRegVal &= 0x7FFFFFFF;
            m_transmitFailures.Text = transmitFailureRegVal.ToString();
        }

        private void UpdatePixelClockFreq()
        {
            const uint k_pixelClockFreqReg = 0x1AF0;
            uint pixelClockFreqRegVal = 0;
            try
            {
                pixelClockFreqRegVal = m_camera.ReadRegister(k_pixelClockFreqReg);
            }
            catch (FC2Exception ex)
            {
                m_pixelClockFreq.Text = "N/A";
                Debug.WriteLine("Error reading value of \"Pixel clock frequency\".");
                ex.Dispose();
                return;
            }

            double pixelClockFreq = MathUtilities.Convert32bitIEEEToFloat(pixelClockFreqRegVal);
            pixelClockFreq /= 1000000.0f;
            m_pixelClockFreq.Text = string.Format("{0:0.00000} MHz", pixelClockFreq);
        }

        private void UpdateHorizontalLineFreq()
        {
            const uint k_horizontalLineFreqReg = 0x1AF4;
            uint horizontalLineFreqRegVal = 0;

            try
            {
                horizontalLineFreqRegVal = m_camera.ReadRegister(k_horizontalLineFreqReg);
            }
            catch (FC2Exception ex)
            {
                m_horizontalLineFreq.Text = "N/A";
                Debug.WriteLine("Error reading value of \"horizontal line frequency\".");
                ex.Dispose();
                return;
            }

            double horizontalLineFreq = MathUtilities.Convert32bitIEEEToFloat(horizontalLineFreqRegVal);
            m_horizontalLineFreq.Text = string.Format("{0:0.#} Hz", horizontalLineFreq);
        }    

        private void OnResetButtonClick(object sender, EventArgs e)
        {
            const uint k_transmitFailureReg = 0x12FC;
            try
            {
                m_camera.WriteRegister(k_transmitFailureReg, 0);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Unable to reset. Error writing register. {0}", ex.Message);
                ex.Dispose();
                return;
            }
        }

        private void OnRefreshConsoleLog()
        {
            const uint consoleStartLoc = 0x1D00;
            const uint consoleEndLoc = 0x1E00;
            const uint consoleLength = consoleEndLoc - consoleStartLoc;
            uint[] consoleData = new uint[consoleLength];
            try
            {
                m_camera.ReadRegisterBlock(
                    0xFFFF,
                    0xF0F00000 + consoleStartLoc,
                    consoleData);
            }
            catch (FC2Exception ex)
            {
                m_consoleLogTextBox.Text = "Error reading console log.";
                Debug.WriteLine(ex.Message);
                ex.Dispose();
                return;
            }

            // Data is stored backwards, reverse it for display
            StringBuilder consoleLogString = new StringBuilder();
            for (uint i = 0; i < consoleLength / 4; i++)
            {
                byte[] b = BitConverter.GetBytes(consoleData[63 - i]);

                for (uint j = 0; j < b.Length; j++)
                {
                    char c = (char)b[3 - j];

                    if (c.Equals('\r'))
                    {
                        consoleLogString.Append(Environment.NewLine);
                    }
                    else if ((int)c <= 127)
                    {
                        consoleLogString.Append(c);
                    }
                    else
                    {
                        consoleLogString.Append(" ");
                    }
                }
            }

            consoleLogString.Append(Environment.NewLine);
            m_consoleLogTextBox.Text = consoleLogString.ToString();
        }

        private void OnCopyConsoleLogButtonClick(object sender, EventArgs e)
        {
            try
            {
                Clipboard.SetText(m_consoleLogTextBox.Text);
            }
            catch (ArgumentNullException ex)
            {
                MessageBox.Show("Nothing in clipboard.", "FlyCapute2 message", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }
            catch (System.Threading.ThreadStateException ex)
            {
                ShowErrorMessageDialog("Error copying text to clipboad. The copying thread is invalid", ex);
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }
        }

        private void OnRefreshConsoleLogButtonClick(object sender, EventArgs e)
        {
            OnRefreshConsoleLog();
        }
    }
}
