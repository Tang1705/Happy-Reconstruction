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
using System.Threading;
using System.Windows.Forms;
using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    internal partial class CameraControlMainFrame : Form
    {
        private int sk_maxNumberOfPages = 15;
        private ManagedCameraBase m_camera = null;
        private CameraInfo m_camInfo = null;
        private BasePage[] m_pages;

        private bool m_isConnected = false;
        private int m_previousSeletectPageIndex = 0;
        private string m_currentCustomTitle = null;

        private Format7Page m_fmt7Page;
        private AdvCameraSettingsPage m_advPage;
        private CameraRegistersPage m_regPage;

        public ManagedCameraBase GetCamera()
        {
            return m_camera;
        }

        public CameraControlMainFrame()
        {
            InitializeComponent();
        }

        private delegate void UpdateDelegate();

        public bool Initialize()
        {
            if (InitializeUI() == false)
            {
                return false;
            }

            return true;
        }

        public void Connect(ManagedCameraBase camera)
        {
            lock (this)
            {
                Debug.Assert(camera != null, "Can not connect to a null camera.");
                if (camera == null)
                {
                    // Bad!
                    Debug.WriteLine("Connecting a null camera.");
                    return;
                }

                if (m_isConnected == true)
                {
                    //if this camera control dialog has already connected
                    //we need to disconnect the old camera first
                    Disconnect();
                }

                m_camera = camera;

                try
                {
                    m_camInfo = m_camera.GetCameraInfo();
                }
                catch (FC2Exception ex)
                {
                    m_isConnected = false;
                    Debug.WriteLine("Connect: Unable to get Camera Info. {0}", ex.Message);
                    ex.Dispose();
                    return;
                }
                
                if (Initialize() == false)
                {
                    m_isConnected = false;
                    Debug.WriteLine("Unable to start initialization");
                    return;
                }

                m_isConnected = true;
                Debug.WriteLine("Connected to camera");
            }
        }

        public void ReconnectCamera(ManagedPGRGuid guid)
        {
            lock (this)
            {
                if (m_isConnected == true)
                {
                    try
                    {
                        if (m_camera.IsConnected())
                        {
                            m_camera.Disconnect();
                            m_camera.Connect(guid);
                        }
                        else
                        {
                            m_camera.Connect(guid);
                        }
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine(ex.Message);
                    }
                }

                Debug.WriteLine("Reconnected to camera");
            }
        }

        public void Disconnect()
        {
            lock (this)
            {
                if (m_isConnected == true)
                {
                    // Set all pages to disconnect status
                    for (int i = 0; i < m_pages.Length; i++)
                    {
                        if (m_pages[i] != null)
                        {
                            m_pages[i].SetConnectStatus(false);
                        }
                    }

                    m_camera = null;
                    m_camInfo = null;
                    m_isConnected = false;
                }

                Debug.WriteLine("Disconnected from camera");
            }
        }

        public void MemoryChannelRestored(object sender, EventArgs e)
        {
            m_fmt7Page.InitializeCameraInformation();
            m_pages[5].Refresh();
        }

        void m_advPage_ISOSpeedChanged(object sender, EventArgs e)
        {
            m_fmt7Page.InitializeCameraInformation();
        }

        public void TriggerParameterChanged(object sender, EventArgs e)
        {
            m_pages[5].Refresh();
        }

        public void SetTitle(string title)
        {
            m_currentCustomTitle = title;
            if (m_currentCustomTitle == null)
            {
                m_currentCustomTitle = "FlyCapture2"; // Set to default string
            }

            string cameraInfoString;
            if (m_camInfo == null)
            {
                cameraInfoString = string.Empty;
            }
            else
            {
                cameraInfoString = string.Format(
                                    "{0} {1} ({2})",
                                    m_camInfo.vendorName,
                                    m_camInfo.modelName,
                                    m_camInfo.serialNumber);
            }

            this.Text = string.Format(
                "{0}  {1}",
                m_currentCustomTitle,
                cameraInfoString);
        }

        public void ShowWindow()
        {
            Debug.Assert(m_camera != null, "The current camera is null.");
            if (m_camera == null)
            {
                // Bad!
                return;
            }

            if (m_isConnected)
            {
                // Check whether its ran from ladybuggui
                if (!IsLadybugGUI())
                {
                    m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                }
                else
                {
                    // Ran from ladybuggui
                    if (m_mainTabControl.SelectedIndex == 0)
                    {
                        m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                    }
                    else
                    {
                        m_pages[m_mainTabControl.SelectedIndex + 2].IsPageSelected(true);
                    }
                }
            }

            Show();
        }

        public void ShowWindow(IWin32Window owner)
        {
            Debug.Assert(m_camera != null, "The current camera is null.");
            if (m_camera == null)
            {
                // Bad!
                return;
            }

            if (m_isConnected)
            {
                // Check whether its ran from ladybuggui
                if (!IsLadybugGUI())
                {
                    m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                }
                else
                {
                    // Ran from ladybuggui
                    if (m_mainTabControl.SelectedIndex == 0)
                    {
                        m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                    }
                    else
                    {
                        m_pages[m_mainTabControl.SelectedIndex + 2].IsPageSelected(true);
                    }
                }
            }

            Show(owner);
            BringToFront();
        }

        public void ShowModal()
        {
            Debug.Assert(m_camera != null, "The current camera is null.");
            if (m_camera == null)
            {
                // Bad!
                return;
            }

            if (m_isConnected)
            {
                // Check whether its ran from ladybuggui
                if (!IsLadybugGUI())
                {
                    m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                }
                else
                {
                    // Ran from ladybuggui
                    if (m_mainTabControl.SelectedIndex == 0)
                    {
                        m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                    }
                    else
                    {
                        m_pages[m_mainTabControl.SelectedIndex + 2].IsPageSelected(true);
                    }
                }
            }

            ShowDialog();
        }

        public void ShowModal(IWin32Window owner)
        {
            Debug.Assert(m_camera != null, "The current camera is null.");
            if (m_camera == null)
            {
                // Bad!
                return;
            }

            if (m_isConnected)
            {
                // Check whether its ran from ladybuggui
                if (!IsLadybugGUI())
                {
                    m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                }
                else
                {
                    // Ran from ladybuggui
                    if (m_mainTabControl.SelectedIndex == 0)
                    {
                        m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                    }
                    else
                    {
                        m_pages[m_mainTabControl.SelectedIndex + 2].IsPageSelected(true);
                    }
                }
            }

            ShowDialog(owner);
        }

        public void HideWindow()
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new UpdateDelegate(HideWindow));
                return;
            }

            // turn off the timer and save CPU usage.
            if (m_isConnected)
            {
                // Check whether its ran from ladybuggui
                if (!IsLadybugGUI())
                {
                    m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(false);
                }
                else
                {
                    // Ran from ladybuggui
                    if (m_mainTabControl.SelectedIndex == 0)
                    {
                        m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(false);
                    }
                    else
                    {
                        m_pages[m_mainTabControl.SelectedIndex + 2].IsPageSelected(false);
                    }
                }
            }

            Hide();
        }

        private bool InitializeUI()
        {
            Debug.Assert(m_camera != null, "The current camera is null.");
            Debug.Assert(m_camInfo != null, "The current camera information is null.");
            FC2Version version = ManagedUtilities.libraryVersion;
            string defaultTitle = string.Format(
                                 "FlyCapture2 {0}.{1}.{2}.{3}",
                                 version.major,
                                 version.minor,
                                 version.type,
                                 version.build);
            SetTitle(defaultTitle);
            CreatePages();
            return true;
        }

        private void CreatePages()
        {
            m_pages = new BasePage[sk_maxNumberOfPages];

            // Using an index allows us to rearrange pages easily simply
            // by moving the page initialization up and down
            int index = 0;
            InitializeCameraSettingPage(index++);
            InitializeDCAMFormatPage(index++);
            InitializeFormat7Page(index++);
            InitializeCameraInformationPage(index++);
            InitializeCameraRegistersPage(index++);
            InitializeGPIOPage(index++);
            InitializeAdvSettingsPage(index++);
            InitializeHighDynamicRangePage(index++);
            InitializeLookUpTablePage(index++);
            InitializeFrameBufferPage(index++);
            InitializeDataFlashPage(index++);
            InitializeSystemInformationPage(index++);
            InitializeBusTopologyPage(index++);
            InitializeHelpSupportPage(index++);

            // Dynamically add Ladybug page according to camera type
            if (LadybugChecker.IsLadybug(m_camInfo) == false)
            {
                if (m_mainTabControl.TabPages.Contains(m_ladyBugTabPage) == true)
                {
                    // Delete ladybug tab page if it already exists
                    m_mainTabControl.TabPages.Remove(m_ladyBugTabPage);
                    m_ladyBugTabPage.Controls.Clear();
                }
            }
            else
            {
                if (m_mainTabControl.TabPages.Contains(m_ladyBugTabPage) == false)
                {
                    // add Ladybug tab page if main tab control does not have this page
                    m_mainTabControl.TabPages.Add(m_ladyBugTabPage);
                }

                InitializeLadybugSettingsPage(index++);

                // Check whether we are being run from Ladybuggui module
                if (LadybugChecker.IsLadybugDLLPresent())
                {
                    // Remove DCAM and Format7 pages when ran from ladybuggui
                    if (m_mainTabControl.TabPages.Contains(m_standardVideoModesTabPage))
                    {
                        m_mainTabControl.TabPages.Remove(m_standardVideoModesTabPage);
                        m_standardVideoModesTabPage.Controls.Clear();
                    }

                    if (m_mainTabControl.TabPages.Contains(m_customVideoModesTabPage))
                    {
                        m_mainTabControl.TabPages.Remove(m_customVideoModesTabPage);
                        m_customVideoModesTabPage.Controls.Clear();
                    }
                }
            }
        }

        private void InitializeCameraSettingPage(int index)
        {
            m_cameraSettingsTabPage.Controls.Clear();
            m_pages[index] = new CameraSettingsPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_cameraSettingsTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeDCAMFormatPage(int index)
        {
            m_standardVideoModesTabPage.Controls.Clear();
            m_pages[index] = new DCAMFormatPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_standardVideoModesTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeFormat7Page(int index)
        {
            m_customVideoModesTabPage.Controls.Clear();
            m_fmt7Page = new Format7Page(m_camera);

            m_pages[index] = m_fmt7Page;
            m_pages[index].Dock = DockStyle.Fill;
            m_customVideoModesTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeCameraInformationPage(int index)
        {
            m_cameraInfoTabPage.Controls.Clear();
            m_pages[index] = new CameraInformationPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_cameraInfoTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeCameraRegistersPage(int index)
        {
            m_cameraRegistersTabPage.Controls.Clear();
            m_regPage = new CameraRegistersPage(m_camera);
            m_regPage.OnTriggerParameterChanged += new EventHandler(TriggerParameterChanged);
            m_pages[index] = m_regPage;
            m_pages[index].Dock = DockStyle.Fill;
            m_cameraRegistersTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeGPIOPage(int index)
        {
            m_gPIOTabPage.Controls.Clear();
            m_pages[index] = new GPIOPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_gPIOTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeAdvSettingsPage(int index)
        {
            m_advSettingsTabPage.Controls.Clear();
            m_advPage = new AdvCameraSettingsPage(m_camera);
            m_advPage.MemoryChannelRestored += new EventHandler(MemoryChannelRestored);
            m_advPage.ISOSpeedChanged += new EventHandler(m_advPage_ISOSpeedChanged);
            m_pages[index] = m_advPage;
            m_pages[index].Dock = DockStyle.Fill;
            m_advSettingsTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeHighDynamicRangePage(int index)
        {
            m_hDRangeTabPage.Controls.Clear();
            m_pages[index] = new HDRPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_hDRangeTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeLookUpTablePage(int index)
        {
            m_lookUpTableTabPage.Controls.Clear();
            m_pages[index] = new LUTPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_lookUpTableTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeFrameBufferPage(int index)
        {
            m_frameBufferTabPage.Controls.Clear();
            m_pages[index] = new FrameBufferPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_frameBufferTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeDataFlashPage(int index)
        {
            m_dataFlashTabPage.Controls.Clear();
            m_pages[index] = new DataFlashPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_dataFlashTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeSystemInformationPage(int index)
        {
            m_systemInfoTabPage.Controls.Clear();
            m_pages[index] = new SystemInfoPage();
            m_pages[index].Dock = DockStyle.Fill;
            m_systemInfoTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeBusTopologyPage(int index)
        {
            m_busTopologyTabPage.Controls.Clear();
            m_pages[index] = new BusTopologyPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_busTopologyTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeHelpSupportPage(int index)
        {
            m_helpSupportTabPage.Controls.Clear();
            m_pages[index] = new HelpSupportPage();
            m_pages[index].Dock = DockStyle.Fill;
            m_helpSupportTabPage.Controls.Add(m_pages[index]);
        }

        private void InitializeLadybugSettingsPage(int index)
        {
            m_ladyBugTabPage.Controls.Clear();
            m_pages[index] = new LadybugSettingsPage(m_camera);
            m_pages[index].Dock = DockStyle.Fill;
            m_ladyBugTabPage.Controls.Add(m_pages[index]);
        }

        // See http://msdn.microsoft.com/en-us/library/ms404305(v=VS.100).aspx
        // for why we have to draw it manually
        private void OnMainTabControlDrawItem(object sender, DrawItemEventArgs e)
        {
            Graphics g = e.Graphics;
            Brush currentTextBrush;

            // Get the item from the collection.
            TabPage currentTabPage = m_mainTabControl.TabPages[e.Index];

            // Get the real bounds for the tab rectangle.
            Rectangle tabBounds = m_mainTabControl.GetTabRect(e.Index);

            if (e.State == DrawItemState.Selected)
            {
                // Draw a different background color, and don't paint a focus rectangle.
                currentTextBrush = SystemBrushes.ActiveCaptionText;
                g.FillRectangle(SystemBrushes.ActiveCaption, e.Bounds);
            }
            else
            {
                currentTextBrush = new System.Drawing.SolidBrush(e.ForeColor);
                e.DrawBackground();
            }

            Font currentTabFont = new Font("Tahoma", 11F, FontStyle.Regular, GraphicsUnit.Pixel);

            // Draw string. Center the text.
            StringFormat stringFlags = new StringFormat();
            stringFlags.Alignment = StringAlignment.Center;
            stringFlags.LineAlignment = StringAlignment.Center;
            g.DrawString(
                currentTabPage.Text,
                currentTabFont,
                currentTextBrush,
                tabBounds,
                new StringFormat(stringFlags));
        }

        private void OnCameraControlFormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            HideWindow();
        }

        private void OnCameraControlMainFrameFormClosed(object sender, FormClosedEventArgs e)
        {
            HideWindow();
            Disconnect();
        }

        private void OnMainTabControlSelectedIndexChanged(object sender, EventArgs e)
        {
            m_pages[m_previousSeletectPageIndex].IsPageSelected(false);

            // Check whether its ran from ladybuggui
            if (!IsLadybugGUI())
            {
                m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
            }
            else
            {
                // Ran from ladybuggui
                if (m_mainTabControl.SelectedIndex == 0)
                {
                    m_pages[m_mainTabControl.SelectedIndex].IsPageSelected(true);
                }
                else
                {
                    m_pages[m_mainTabControl.SelectedIndex + 2].IsPageSelected(true);
                }
            }

            m_previousSeletectPageIndex = m_mainTabControl.SelectedIndex;

            // Check whether its ran from ladybuggui
            if (!IsLadybugGUI())
            {
                switch (m_mainTabControl.SelectedIndex)
                {
                    case 1:
                        try
                        {
                            ((DCAMFormatPage)m_pages[1]).UpdateRadioButtonStatusFromCamera();
                        }
                        catch (InvalidCastException ex)
                        {
                            Debug.WriteLine("Page 1 is not Camera Information Page.");
                            Debug.WriteLine(ex);
                            return;
                        }

                        break;
                    case 5:
                        try
                        {
                            ((GPIOPage)m_pages[5]).Refresh();
                        }
                        catch (InvalidCastException ex)
                        {
                            Debug.WriteLine("Page 6 is not GPIO Page.");
                            Debug.WriteLine(ex);
                            return;
                        }
                        catch (Exception ex)
                        {
                            Debug.WriteLine(ex);
                            return;
                        }
                        break;
                    case 8:
                        try
                        {
                            ((LUTPage)m_pages[8]).UpdateLUTChannel();
                        }
                        catch (InvalidCastException ex)
                        {
                            Debug.WriteLine("Page 8 is not Look Up Table Page.");
                            Debug.WriteLine(ex);
                            return;
                        }

                        break;
                }
            }
            else
            {
                // Ran from ladybuggui
                switch (m_mainTabControl.SelectedIndex)
                {
                    case 6:
                        try
                        {
                            ((LUTPage)m_pages[6]).UpdateLUTChannel();
                        }
                        catch (InvalidCastException ex)
                        {
                            Debug.WriteLine("Page 6 is not Look Up Table Page.");
                            Debug.WriteLine(ex);
                            return;
                        }

                        break;
                }
            }
        }

        private void CameraControlMainFrame_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.C && e.Control && e.Shift)
            {
                try
                {
                    ((CameraInformationPage)m_pages[3]).ToggleConsoleLogVisibility();
                }
                catch (InvalidCastException ex)
                {
                    Debug.WriteLine("Page 3 is not Camera Information Page.");
                    Debug.WriteLine(ex);
                    return;
                }
            }
        }

        private bool IsLadybugGUI()
        {
            return !m_mainTabControl.TabPages.Contains(m_standardVideoModesTabPage) && !m_mainTabControl.TabPages.Contains(m_customVideoModesTabPage);
        }
    }
}