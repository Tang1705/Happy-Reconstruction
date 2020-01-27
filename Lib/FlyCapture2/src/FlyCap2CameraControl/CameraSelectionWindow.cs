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
using System.Net;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    internal struct DialogHolder
    {
        public ManagedCameraBase camera;
        public CameraControlMainFrame camCtlMF;

        public DialogHolder(ManagedCameraBase cam, CameraControlMainFrame mainFrame)
        {
            camera = cam;
            camCtlMF = mainFrame;
        }
    }

    internal partial class CameraSelectionWindow : Form
    {
        private Color NO_CCP = Color.LightPink;
        private Color HAS_CCP = Color.White;
        private Color IP_PROBLEM = Color.LightGray;
        private Color IMCOMPATIBLE_DRIVER = Color.LightPink;

        private ManagedBusManager m_busMgr;
        private CameraInformationDisplayPanel m_cameraInfoPanel;
        private GigEInformationDisplayPanel m_gigEInfoPanel;
        private bool m_isLadybugGUI;
        private Dictionary<uint, DialogHolder> m_activeDialogs;
        private IntPtr m_busResetHandle;
        private string m_currentCustomTitle = null;
        private bool m_needShrinkWindowHeight;
        private Dictionary<string, CameraInfo> m_badCameraInfo;
        private Dictionary<ManagedPGRGuid, CameraInfo> m_goodCameraInfo;
        private bool m_GigEEnumerationIsDisabled = false;
        private System.Windows.Forms.Timer m_timer;

        public CameraSelectionWindow()
        {
            InitializeComponent();
            InitializeCameraSelectionData();
            PopulateCameraList();
            m_timer.Start();
        }

        private delegate void CloseDialogCallback(CameraControlMainFrame dialog);

        private delegate void PopulateCameraCallback();

        private delegate void RefreshCameraListCallback();

        private delegate void EnableWindowCallback();

        public void SetTitle(string newTitle)
        {
            m_currentCustomTitle = newTitle;
            this.Text = string.Format("{0} Camera Selection", m_currentCustomTitle);
        }

        public ManagedPGRGuid[] GetCurrentSelectedGuids()
        {
            DataGridViewSelectedRowCollection rows = m_cameraDataGridView.SelectedRows;
            ManagedPGRGuid[] result = new ManagedPGRGuid[rows.Count];
            result.Initialize();
            for (int i = 0; i < result.Length; i++)
            {
                if (GetPGRGuidFromRowIndex(rows[i].Index, out result[i]) == false)
                {
                    Debug.WriteLine("Detected invalid Guid. At row index: " + rows[i].Index);
                }
            }

            return result;
        }

        private void InitializeCameraSelectionData()
        {
            HideGigEInformation();
            m_busMgr = new ManagedBusManager();
            m_cameraInfoPanel = new CameraInformationDisplayPanel();
            m_cameraInfoDisplayPanel.Controls.Add(m_cameraInfoPanel);
            m_GigEEnumerationIsDisabled = EnumerationController.IsEnumerationDisabled(InterfaceType.GigE);
            m_gigEInfoPanel = new GigEInformationDisplayPanel();
            m_gigeInfoDisplayPanel.Controls.Add(m_gigEInfoPanel);

            m_activeDialogs = new Dictionary<uint, DialogHolder>();

            m_timer = new System.Windows.Forms.Timer();
            m_timer.Interval = 2000;
            m_timer.Tick += new EventHandler(m_timer_Tick);

            try
            {
                m_busResetHandle = m_busMgr.RegisterCallback(OnBusReset, ManagedCallbackType.BusReset, IntPtr.Zero);
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog("Error registering bus reset callback.", ex);
                ex.Dispose();
            }

            m_isLadybugGUI = LadybugChecker.IsLadybugDLLPresent();
            if (m_isLadybugGUI == true)
            {
                this.Text = "Ladybug Camera Selection";
            }
            else
            {
                FC2Version version = ManagedUtilities.libraryVersion;
                this.Text = string.Format(
                            "FlyCapture2 Camera Selection {0}.{1}.{2}.{3}",
                            version.major,
                            version.minor,
                            version.type,
                            version.build);
            }
        }

        private void m_timer_Tick(object sender, EventArgs e)
        {
            if (m_goodCameraInfo != null && !m_GigEEnumerationIsDisabled && m_goodCameraInfo.Count > 0)
            {
                foreach (KeyValuePair<ManagedPGRGuid, CameraInfo> pair in m_goodCameraInfo)
                {
                    bool isControlable = true;
                    try
                    {
                        isControlable = m_busMgr.IsCameraControlable(pair.Key);
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine(ex.Message);
                        isControlable = false;
                    }

                    if (!isControlable)
                    {
                        // No CCP
                        foreach (DataGridViewRow row in m_cameraDataGridView.Rows)
                        {
                            if (row.Cells[0].Value.ToString().Contains(pair.Value.serialNumber.ToString()))
                            {
                                // Found the row for this camera
                                row.DefaultCellStyle.BackColor = NO_CCP;
                                foreach (DataGridViewTextBoxCell cell in row.Cells)
                                {
                                    cell.ToolTipText = "This camera cannot be controlled by FlyCapture2 because its CCP \n" +
                                          "is not available)";
                                }

                                if (m_cameraDataGridView.SelectedRows.Contains(row))
                                {
                                    // Current row is selected. Let's update all controls
                                    UpdateControlStatus(m_cameraDataGridView.SelectedRows[0].Index);
                                }
                            }
                        }
                    }
                    else
                    {
                        foreach (DataGridViewRow row in m_cameraDataGridView.Rows)
                        {
                            if (row.Cells[0].Value.ToString().Contains(pair.Value.serialNumber.ToString()))
                            {
                                // Found the row for this camera
                                if (row.DefaultCellStyle.BackColor == NO_CCP)
                                {
                                    row.DefaultCellStyle.BackColor = HAS_CCP;
                                    foreach (DataGridViewTextBoxCell cell in row.Cells)
                                    {
                                        cell.ToolTipText = string.Empty;
                                    }
                                }

                                if (m_cameraDataGridView.SelectedRows.Contains(row))
                                {
                                    // Current row is selected. Let's update all controls
                                    UpdateControlStatus(m_cameraDataGridView.SelectedRows[0].Index);
                                }
                            }
                        }
                    }
                }
            }
            GC.Collect();
        }
        
        private void PopulateCameraList()
        {
            uint numCameras = 0;
            CameraInfo[] discoveredCameras = new CameraInfo[0];

            try
            {
                numCameras = m_busMgr.GetNumOfCameras();
                discoveredCameras = ManagedBusManager.DiscoverGigECameras();
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog("Error getting number of cameras.", ex);
                ex.Dispose();
            }

            if (numCameras == 0 && discoveredCameras.Length == 0)
            {
                m_cameraListLabel.Text = string.Format("Camera List (No cameras detected)"); 
                m_cameraDataGridView.Rows.Clear();
                m_cameraInfoPanel.ClearInformation();
                HideGigEInformation();
                AdjustWindowMinimumSize();
                this.Height = this.MinimumSize.Height;
                m_needShrinkWindowHeight = false;
                return;
            }

            SortedDictionary<uint, CameraInfo> discoveredCameraInfo = new SortedDictionary<uint, CameraInfo>();
            m_badCameraInfo = new Dictionary<string, CameraInfo>();
            m_goodCameraInfo = new Dictionary<ManagedPGRGuid, CameraInfo>();

            for (uint currCamIdx = 0; currCamIdx < discoveredCameras.Length; currCamIdx++)
            {
                try
                {
                    Debug.WriteLine(
                        String.Format(
                        "Discovered camera: {0} ({1})",
                        discoveredCameras[currCamIdx].modelName,
                        discoveredCameras[currCamIdx].serialNumber));

                    // Check if the camera already exists - we sometimes get duplicate cameras
                    // returned from the discover call
                    if (!discoveredCameraInfo.ContainsKey(discoveredCameras[currCamIdx].serialNumber))
                    {
                        discoveredCameraInfo.Add(
                            discoveredCameras[currCamIdx].serialNumber,
                            discoveredCameras[currCamIdx]);
                    }
                }
                catch (ArgumentNullException ex)
                {
                    Debug.WriteLine("A null key was specified for discovered camera lookup.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                    continue;
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine("An element with the same key already exists in the discovered camera dictionary.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                    continue;
                }
                catch (System.Exception ex)
                {
                    Debug.WriteLine("An error occurred while updating the discovered GigE camera list.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                    continue;
                }
            }

            List<DataGridViewRow> goodCameraList = new List<DataGridViewRow>();
            List<DataGridViewRow> badCameraList = new List<DataGridViewRow>();
            for (uint i = 0; i < numCameras; i++)
            {                
                try
                {
                    ManagedPGRGuid guid;
                    guid = m_busMgr.GetCameraFromIndex(i);

                    InterfaceType currInterface;
                    currInterface = m_busMgr.GetInterfaceTypeFromGuid(guid);

                    using (ManagedCamera camera = new ManagedCamera())
                    {
                        bool compatibleDriver = true;
                        string errorMessage = string.Empty;

                        try
                        {
                            camera.Connect(guid);
                        }
                        catch (FC2Exception ex)
                        {
                            if (ex.Type == ErrorType.IncompatibleDriver)
                            {
                                compatibleDriver = false;
                                errorMessage = ex.Message;
                            }
                            ex.Dispose();
                        }

                        CameraInfo camInfo;

                        if (compatibleDriver)
                        {
                            camInfo = camera.GetCameraInfo();

                            if (discoveredCameraInfo.ContainsKey(camInfo.serialNumber) == true)
                            {
                                // Remove good camera from dictionary
                                discoveredCameraInfo.Remove(camInfo.serialNumber);
                                m_goodCameraInfo.Add(guid, camInfo);
                            }

                            // Append the camera to the list
                            try
                            {
                                DataGridViewRow newCamera = new DataGridViewRow();
                                DataGridViewTextBoxCell[] cells = new DataGridViewTextBoxCell[4];
                                for (int ci = 0; ci < cells.Length; ci++)
                                {
                                    cells[ci] = new DataGridViewTextBoxCell();
                                }

                                cells[0].Value = camInfo.serialNumber.ToString();
                                cells[1].Value = camInfo.modelName;
                                cells[2].Value = InterfaceTranslator.GetInterfaceString(currInterface);
                                cells[3].Value = camInfo.ipAddress.Equals(new IPAddress(0))
                                    ? "N/A"
                                    : camInfo.ipAddress.ToString();

                                newCamera.Cells.AddRange(cells);
                                goodCameraList.Add(newCamera);
                            }
                            catch (InvalidOperationException ex)
                            {
                                Debug.WriteLine("Error appending new row to camera list.");
                                Debug.WriteLine(ex.Message);
                                Debug.WriteLine(ex.StackTrace);
                                continue;
                            }
                            catch (ArgumentNullException ex)
                            {
                                Debug.WriteLine("The cell in camera list contains null value.");
                                Debug.WriteLine(ex.Message);
                                Debug.WriteLine(ex.StackTrace);
                                continue;
                            }
                        }
                        else
                        {
                            camInfo = new CameraInfo();

                            DataGridViewRow newCamera = new DataGridViewRow();

                            newCamera.DefaultCellStyle.BackColor = IMCOMPATIBLE_DRIVER;
                            DataGridViewTextBoxCell[] cells = new DataGridViewTextBoxCell[4];
                            for (int ci = 0; ci < cells.Length; ci++)
                            {
                                cells[ci] = new DataGridViewTextBoxCell();
                            }

                            cells[0].Value = "N/A";
                            cells[1].Value = ManagedUtilities.GetDriverDeviceName(guid);
                            cells[2].Value = "Incompatible Driver";
                            cells[3].Value = "N/A";

                            cells[0].ToolTipText = "An incompatible driver is installed on this device.";

                            foreach (DataGridViewTextBoxCell cell in cells)
                            {

                                cell.ToolTipText = errorMessage;
                            }

                            newCamera.Cells.AddRange(cells);
                            badCameraList.Add(newCamera);
                        }
                    }
                }
                catch (FC2Exception ex)
                {
                    BasePage.ShowErrorMessageDialog("Error populating camera list.", ex);
                    ex.Dispose();
                    continue;
                }                                                                                        
            }


            foreach (KeyValuePair<uint, CameraInfo> pair in discoveredCameraInfo)
            {
                try
                {
                    CameraInfo info = pair.Value;

                    m_badCameraInfo.Add(info.serialNumber.ToString(), info);

                    DataGridViewRow newCamera = new DataGridViewRow();

                    newCamera.DefaultCellStyle.BackColor = IP_PROBLEM;
                    DataGridViewTextBoxCell[] cells = new DataGridViewTextBoxCell[4];
                    for (int ci = 0; ci < cells.Length; ci++)
                    {
                        cells[ci] = new DataGridViewTextBoxCell();
                    }

                    cells[0].Value = info.serialNumber.ToString();
                    cells[1].Value = info.modelName;
                    cells[2].Value = "GigE";
                    cells[3].Value = info.ipAddress.Equals(new IPAddress(0)) ? "N/A" : info.ipAddress.ToString();

                    cells[0].ToolTipText = "This camera is discoverable but can not be controlled";

                    foreach (DataGridViewTextBoxCell cell in cells)
                    {
                        if (m_GigEEnumerationIsDisabled)
                        {
                            cell.ToolTipText = "This camera cannot be enumerated by FlyCapture2 because GigE camera enumeration \n" +
                                          "has been disabled)";
                        }
                        else
                        {
                            cell.ToolTipText = "Camera IP settings or local interface is mis-configured. Use \"Force IP\" to \n" +
                                           "correct it" ;
                        }
                    }

                    newCamera.Cells.AddRange(cells);
                    badCameraList.Add(newCamera);
                }
                catch (InvalidOperationException ex)
                {
                    Debug.WriteLine("Error appending new row to camera list.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                    continue;
                }
                catch (ArgumentNullException ex)
                {
                    Debug.WriteLine("The cell in camera list contains null value.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                    continue;
                }
            }

            m_cameraDataGridView.Rows.Clear();
            m_cameraListLabel.Text = string.Format("Camera List ({0} cameras detected)", (goodCameraList.Count+badCameraList.Count));
            for (int i = 0; i < goodCameraList.Count; i++)
            {
                try
                {
                    m_cameraDataGridView.Rows.Add(goodCameraList[i]);
                }
                catch (InvalidOperationException ex)
                {
                    Debug.WriteLine("Error adding camera list to the view.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
                catch (ArgumentNullException ex)
                {
                    Debug.WriteLine("The camera list contains null value.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine("The camera list contains invalid value.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
            }

            for (int i = 0; i < badCameraList.Count; i++)
            {
                try
                {
                    m_cameraDataGridView.Rows.Add(badCameraList[i]);
                }
                catch (InvalidOperationException ex)
                {
                    Debug.WriteLine("Error adding camera list to the view.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
                catch (ArgumentNullException ex)
                {
                    Debug.WriteLine("The camera list contains null value.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
                catch (ArgumentException ex)
                {
                    Debug.WriteLine("The camera list contains invalid value.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
            }

            if (m_cameraDataGridView.Rows.Count > 0)
            {
                // display first camera information
                DisplayCameraInformationFromRowIndex(0);
            }
            else
            {
                // Nothing need to display
                m_cameraInfoPanel.ClearInformation();
            }
        }

        private void OnBusReset(System.IntPtr ptr, uint serialNumber)
        {
            Debug.WriteLine(String.Format("{0} - *** BUS RESET ***", DateTime.Now.ToString()));
            CloseAllDialogs();
            SafePopulateCamera();
            
            // The window is disabled while bus reset start
            // So we must enable window when bus reset finish
            SafeEnableWindow();
        }

        private void SafeEnableWindow()
        {
            if (InvokeRequired == true)
            {
                BeginInvoke(new EnableWindowCallback(SafeEnableWindow));
                return;
            }

            Enabled = true;
        }

        private void SafePopulateCamera()
        {
            if (this.IsDisposed == true)
            {
                // Fixed a bug, when user click Refresh camera list button,
                // and close window immediately, program will crash.
                // when OnBusReset() is invoked, it will call this function
                // regardless camera selection dialog is disposed or not
                return;
            }

            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (m_cameraDataGridView.InvokeRequired)
            {
                Invoke(new PopulateCameraCallback(PopulateCameraList));
            }
            else
            {
                PopulateCameraList();
            }            
        }

        private void OnCameraDataGridViewDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0 || e.ColumnIndex < 0)
            {
                // Ignore as the click happened on a header
                return;
            }

            // Check to see if its a bad GigE camera
            if (m_cameraDataGridView.Rows[e.RowIndex].DefaultCellStyle.BackColor == IP_PROBLEM)
            {
                return;
            }

            // Check to see if its a device with imcompatible driver
            if (m_cameraDataGridView.Rows[e.RowIndex].DefaultCellStyle.BackColor == IMCOMPATIBLE_DRIVER)
            {
                return;
            }

            // Check to see if camera has CCP
            if (m_cameraDataGridView.Rows[e.RowIndex].DefaultCellStyle.BackColor == NO_CCP)
            {
                return;
            }

            // At this point, this will be the equivalent of clicking Ok
            m_okButton.DialogResult = DialogResult.OK;
            m_okButton.PerformClick();
        }

        private void DisplayCameraInformationFromRowIndex(int rowIndex)
        {
            if (rowIndex == -1)
            {
                // Nothing is selected
                return;
            }

            bool badCamera = false;
            string cellContent = m_cameraDataGridView.Rows[rowIndex].Cells[0].Value.ToString();
            if (m_badCameraInfo.ContainsKey(cellContent))
            {
                badCamera = true;
            }

            if (m_cameraDataGridView.Rows[rowIndex].DefaultCellStyle.BackColor == IMCOMPATIBLE_DRIVER)
            {
                badCamera = true;
            }

            if (badCamera)
            {
                try
                {
                    CameraInfo camInfo;
                    m_badCameraInfo.TryGetValue(m_cameraDataGridView.Rows[rowIndex].Cells[0].Value.ToString(), out camInfo);

                    if (camInfo != null)
                    {
                        ShowGigEInformation();
                        m_cameraInfoPanel.Camera = null;
                        m_cameraInfoPanel.UpdateBadCameraInformation(camInfo);

                        m_cameraInfoDisplayPanel.Height = m_cameraInfoPanel.MinimumSize.Height;
                        m_cameraInfoDisplayPanel.Width = m_cameraInfoPanel.MinimumSize.Width;

                        m_gigEInfoPanel.Camera = null;
                        m_gigEInfoPanel.UpdateBadGigECameraInformation(camInfo);
                        m_gigeInfoDisplayPanel.Height = m_gigEInfoPanel.MinimumSize.Height;
                        m_gigeInfoDisplayPanel.Width = m_gigEInfoPanel.MinimumSize.Width;
                        m_needShrinkWindowHeight = true;

                        AdjustWindowMinimumSize();
                    }
                    else
                    {
                        camInfo = new CameraInfo();
                        camInfo.interfaceType = InterfaceType.Unknown;
                        camInfo.maximumBusSpeed = BusSpeed.Unknown;
                        camInfo.pcieBusSpeed = PCIeBusSpeed.Unknown;
                        HideGigEInformation();
                        m_cameraInfoPanel.Camera = null;
                        m_cameraInfoPanel.UpdateBadCameraInformation(camInfo);

                        m_cameraInfoDisplayPanel.Height = m_cameraInfoPanel.MinimumSize.Height;
                        m_cameraInfoDisplayPanel.Width = m_cameraInfoPanel.MinimumSize.Width;

                        m_needShrinkWindowHeight = true;

                        AdjustWindowMinimumSize();
                    }
                    ////if window shrink is needed and current interface
                    ////is not GigE then restore the window height (for bug 14937)
                    //this.Height = this.MinimumSize.Height;
                    //m_needShrinkWindowHeight = false;

                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.ToString());
                }
            }
            else
            {
                ManagedPGRGuid guid;
                if (GetPGRGuidFromRowIndex(rowIndex, out guid) == false)
                {
                    MessageBox.Show("Error getting camera information", "FlyCapture2", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    m_cameraInfoPanel.ClearInformation();
                    return;
                }

                InterfaceType ifType = m_busMgr.GetInterfaceTypeFromGuid(guid);
                ManagedCameraBase camera;
                if (ifType == InterfaceType.GigE)
                {
                    camera = new ManagedGigECamera();
                }
                else
                {
                    camera = new ManagedCamera();
                }

                using (camera)
                {
                    if (ifType == InterfaceType.GigE)
                    {
                        ShowGigEInformation();
                    }
                    else
                    {
                        HideGigEInformation();
                    }

                    try
                    {
                        camera.Connect(guid);
                    }
                    catch (FC2Exception ex)
                    {
                        Debug.WriteLine("Unable to connect to camera.");
                        Debug.WriteLine(ex.Message);
                        ex.Dispose();
                        return;
                    }

                    // cheeck for filter driver compatibility
                    bool compatibleFilterDriverInstalled = true;
                    string errorMessage = string.Empty;

                    if (ifType == InterfaceType.GigE)
                    {
                        try
                        {
                            ManagedUtilities.CheckDriver(guid);
                        }
                        catch (FC2Exception ex)
                        {
                            compatibleFilterDriverInstalled = false;
                            errorMessage = ex.Message;
                            ex.Dispose();
                        }
                    }

                    CameraInfo camInfo;
                    
                    try
                    {
                        camInfo = camera.GetCameraInfo();
                    }
                    catch (FC2Exception ex)
                    {
                        Debug.WriteLine("Unable to get Camera Info. {0}", ex.Message);
                        ex.Dispose();
                        return;
                    }
                    

                    m_cameraInfoPanel.Camera = camera;
                    m_cameraInfoPanel.UpdateCameraInformation(camInfo);

                    m_cameraInfoDisplayPanel.Height = m_cameraInfoPanel.MinimumSize.Height;
                    m_cameraInfoDisplayPanel.Width = m_cameraInfoPanel.MinimumSize.Width;

                    if (ifType == InterfaceType.GigE)
                    {
                        m_gigEInfoPanel.Camera = camera;
                        m_gigEInfoPanel.UpdateGigECameraInformation(camInfo);
                        m_gigeInfoDisplayPanel.Height = m_gigEInfoPanel.MinimumSize.Height;
                        m_gigeInfoDisplayPanel.Width = m_gigEInfoPanel.MinimumSize.Width;
                        m_needShrinkWindowHeight = true;

                        if (!compatibleFilterDriverInstalled)
                        {
                            m_cameraInfoPanel.SetDriverCompatibilityStatus(compatibleFilterDriverInstalled, errorMessage);
                        }
                    }
                }
                AdjustWindowMinimumSize();
                if (m_needShrinkWindowHeight == true &&
                    ifType != InterfaceType.GigE)
                {
                    //if window shrink is needed and current interface
                    //is not GigE then restore the window height (for bug 14937)
                    this.Height = this.MinimumSize.Height;
                    m_needShrinkWindowHeight = false;
                }
            }


        }

        private bool GetPGRGuidFromRowIndex(int rowIndex, out ManagedPGRGuid guid)
        {
            uint cameraSerialNumber = 0;
            if (m_cameraDataGridView.Rows[rowIndex].Cells[0].Value == null)
            {
                Debug.WriteLine("Unable to get camera information. Nothing in row: " + rowIndex);
                guid = new ManagedPGRGuid();
                return false;
            }

            try
            {
                cameraSerialNumber = Convert.ToUInt32(m_cameraDataGridView.Rows[rowIndex].Cells[0].Value);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("Invalid serial number.");
                Debug.WriteLine(ex.Message);
                guid = new ManagedPGRGuid();
                return false;
            }
            catch (FormatException ex)
            {
                Debug.WriteLine("Invalid format for serial number.");
                Debug.WriteLine(ex.Message);
                guid = new ManagedPGRGuid();
                return false;
            }
            catch (OverflowException ex)
            {
                Debug.WriteLine("The serial number is too long.");
                Debug.WriteLine(ex.Message);
                guid = new ManagedPGRGuid();
                return false;
            }

            try
            {
                guid = m_busMgr.GetCameraFromSerialNumber(cameraSerialNumber);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("The camera with serial number not found.");
                Debug.WriteLine(ex.Message);
                guid = new ManagedPGRGuid();
                ex.Dispose();
                return false;
            }

            return true;
        }

        private void HideGigEInformation()
        {
            m_gigeInfoDisplayPanel.Visible = false;
            m_gigeInfoLabel.Visible = false;
        }

        private void ShowGigEInformation()
        {
            m_gigeInfoDisplayPanel.Visible = true;
            m_gigeInfoLabel.Visible = true;
        }

        private void AdjustWindowMinimumSize()
        {
            int minHeight = CalculateMinimumHeight();
            int minWidth = CalculateMinimumWidth();
            this.MinimumSize = new Size(minWidth, minHeight);
        }

        private int CalculateMinimumWidth()
        {
            // Leave some space for better looks
            const int k_widthMargin = 10;

            int minWidth = k_widthMargin;
            minWidth += m_mainTableLayout.MinimumSize.Width;
            return minWidth;
        }

        private int CalculateMinimumHeight()
        {
            // Determine title height
            Rectangle windowRectangle = RectangleToScreen(this.ClientRectangle);
            
            // Leave some space for better looks
            const int k_heightMargin = 50;

            int minHeight = windowRectangle.Top - this.Top;
            minHeight += k_heightMargin;
            minHeight += m_cancelButton.Height;
            minHeight += m_cameraInfoLayout.PreferredSize.Height;

            return minHeight;
        }

        private void OnRefreshButtonClick(object sender, EventArgs e)
        {
            RefreshCameraList();
        }

        private void RefreshCameraList()
        {
            Enabled = false;
            foreach (KeyValuePair<uint, DialogHolder> dialog in m_activeDialogs)
            {
                dialog.Value.camCtlMF.HideWindow();
            }

            try
            {
                m_busMgr.RescanBus();
                Thread.Sleep(1000);
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog("Error rescanning bus.", ex);
                Enabled = true;
                ex.Dispose();
                return;
            }
            this.Activate();
        }

        private void OnCancelButtonClick(object sender, EventArgs e)
        {
            CloseAllDialogs();
        }

        private void OnOkButtonClick(object sender, EventArgs e)
        {
            CloseAllDialogs();
        }

        private bool CheckGigEEnumeration()
        {
            // Prompt to enable GigE enumeration
            bool isDisabled = EnumerationController.IsEnumerationDisabled(InterfaceType.GigE);
            if (isDisabled)
            {
                DialogResult result = MessageBox.Show(
                    "GigE enumeration is currently disabled on the system. Do you wish to enable it?",
                    "Enable GigE enumeration?",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Question);
                if (result == DialogResult.Yes)
                {
                    try
                    {
                        EnumerationController.SetEnumerationDisabled(InterfaceType.GigE, false);
                        m_GigEEnumerationIsDisabled = true;
                        MessageBox.Show(
                            "GigE cameras will now be visible!",
                            "GigE enumeration enabled",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);

                        return true;
                    }
                    catch (System.Security.SecurityException ex)
                    {
                        MessageBox.Show(
                    "Elevated permission is required to perform Force IP. Please restart application as administrator and try again.",
                    "Operation Failed!",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Warning);

                        return false;
                    }
                    catch (System.Exception ex)
                    {
                        MessageBox.Show(
                    "A problem was encountered while performing Force IP. Please try again.",
                    "Operation Failed!",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Warning);

                        return false;
                    }
                }
                else
                {
                    MessageBox.Show(
                        "GigE cameras will not be visible!",
                        "GigE enumeration not enabled",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
                    m_GigEEnumerationIsDisabled = false;
                    return false;
                }
            }
            else
            {
                return true;
            }
        }

        private void OnForceIpButtonClick(object sender, EventArgs e)
        {
            if (!CheckGigEEnumeration())
            {
                return;
            }

            // Default message
            string message = "This will set all GigE cameras discovered to an IP configuration that will allow them to work with FlyCapture2.";

            // Special message for one camera being selected
            if (m_cameraDataGridView.SelectedRows.Count == 1)
            {
                message = "This will set this GigE camera to an IP configuration that will allow it to work with FlyCapture2.";
            }

            DialogResult result = MessageBox.Show(
            message + Environment.NewLine +
            "Do you want to proceed?",
            "Confirm Auto Force IP",
            MessageBoxButtons.YesNo,
            MessageBoxIcon.Question);
            if (result == DialogResult.Yes)
            {
                List<CameraInfo> infos = new List<CameraInfo>();
                
                foreach (DataGridViewRow row in m_cameraDataGridView.SelectedRows)
                {
                    bool cameraFound = false;

                    // search GoodCameraList
                    foreach (KeyValuePair<ManagedPGRGuid, CameraInfo> pair in m_goodCameraInfo)
                    {
                        if (pair.Value.serialNumber.ToString().Contains(row.Cells[0].Value.ToString()))
                        {
                            infos.Add(pair.Value);
                            cameraFound = true;
                            break;
                        }
                    }

                    if (!cameraFound)
                    {
                        // Search Bad Camera List
                        foreach (KeyValuePair<string, CameraInfo> pair in m_badCameraInfo)
                        {
                            if (pair.Key.ToString().Contains(row.Cells[0].Value.ToString()))
                            {
                                infos.Add(pair.Value);
                                break;
                            }
                        }
                    }
                }

                Thread autoForceIPThread = new Thread(new ParameterizedThreadStart(StartForceAutoIP));
                Enabled = false;
                autoForceIPThread.Start(infos);
            }
        }

        private void StartForceAutoIP(object data)
        {
            lock (this)
            {
                List<CameraInfo> infos = (List<CameraInfo>)data;
                LoadingWindow loadingWnd = new LoadingWindow();
                using (loadingWnd)
                {
                    loadingWnd.Show();
                    loadingWnd.SetProgressBar(0, "Start auto forcing IP...");
                    foreach (CameraInfo info in infos)
                    {
                        try
                        {
                            ManagedBusManager.ForceAllIPAddressesAutomatically(info.serialNumber);
                        }
                        catch (FC2Exception ex)
                        {
                            loadingWnd.SetProgressBar(10, "Error auto forcing IP...");
                            MessageBox.Show(
                                ex.Message,
                                "Error auto forcing IP",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error);
                            Enabled = true;
                            ex.Dispose();
                            return;
                        }
                    }

                    loadingWnd.SetProgressBar(30, "Configuration completed... Please wait for 5 second...");

                    // Sleep for 5s before refreshing
                    for (int i = 0; i < 50; i++)
                    {
                        Thread.Sleep(100);
                        loadingWnd.SetProgressBar(30 + i);
                    }

                    loadingWnd.SetProgressBar(90, "Auto forcing IP completed... Refreshing camera list...");
                    loadingWnd.Hide();
                    loadingWnd.Close();

                    // bring to front
                    //this.Activate();

                    if (InvokeRequired == true)
                    {
                        Invoke(new RefreshCameraListCallback(RefreshCameraList));
                    }
                    else
                    {
                        RefreshCameraList();
                    }
                }
            }
        }

        private void CloseAllDialogs()
        {
            foreach (KeyValuePair<uint, DialogHolder> dialog in m_activeDialogs)
            {               
                // InvokeRequired required compares the thread ID of the
                // calling thread to the thread ID of the creating thread.
                // If these threads are different, it returns true.
                if (dialog.Value.camCtlMF.InvokeRequired == true)
                {
                    Invoke(new CloseDialogCallback(CloseDialog), new object[] { dialog.Value.camCtlMF });
                }
                else
                {
                    CloseDialog(dialog.Value.camCtlMF);
                }

                // Explicitly dispose of the camera, since it is not longer used
                dialog.Value.camera.Dispose();
            }

            m_activeDialogs.Clear();
        }

        private void CloseDialog(CameraControlMainFrame dialog)
        {
            dialog.Disconnect();
            dialog.Dispose();
        }

        private void OnConfigurationButtonClick(object sender, EventArgs e)
        {
            ManagedPGRGuid[] guids = GetCurrentSelectedGuids();
            foreach (ManagedPGRGuid guid in guids)
            {                
                try
                {
                    InterfaceType ifType = m_busMgr.GetInterfaceTypeFromGuid(guid);

                    ManagedCameraBase camera;
                    if (ifType == InterfaceType.GigE)
                    {
                        camera = new ManagedGigECamera();
                    }
                    else
                    {
                        camera = new ManagedCamera();
                    }

                    camera.Connect(guid);

                    CameraInfo camInfo = camera.GetCameraInfo();

                    DialogHolder dialogHolder;
                    if (m_activeDialogs.TryGetValue(camInfo.serialNumber, out dialogHolder))
                    {
                        camera.Disconnect();
                        dialogHolder.camCtlMF.ReconnectCamera(guid);
                        dialogHolder.camCtlMF.ShowWindow();
                    }
                    else
                    {
                        CameraControlMainFrame camControlDialog;
                        camControlDialog = new CameraControlMainFrame();
                        camControlDialog.Connect(camera);

                        if (m_currentCustomTitle != null)
                        {
                            camControlDialog.SetTitle(m_currentCustomTitle);
                        }

                        camControlDialog.ShowWindow();
                        dialogHolder = new DialogHolder(camera, camControlDialog);
                        m_activeDialogs.Add(camInfo.serialNumber, dialogHolder);
                    }
                }
                catch (FC2Exception ex)
                {
                    string error = string.Format("Failed to launch camera control dialog for camera: {0}", ex.Message);
                    Debug.WriteLine(error);
                    MessageBox.Show(error, "FlyCapture2", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    ex.Dispose();
                    return;
                }                                             
            }            
        }

        private void CameraSelectionWindowClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
               m_busMgr.UnregisterCallback(m_busResetHandle);
            }
            catch (FC2Exception ex)
            {
                BasePage.ShowErrorMessageDialog("Error unregistering callback.", ex);
                ex.Dispose();
            }
        }

        private void CameraSelectionWindowShown(object sender, EventArgs e)
        {
            AdjustWindowMinimumSize();
            this.Size = this.MinimumSize;
        }

        private void OnCameraListSelectionChanged(object sender, EventArgs e)
        {
            if (m_cameraDataGridView.SelectedRows.Count > 0)
            {
                UpdateControlStatus(m_cameraDataGridView.SelectedRows[0].Index);
                DisplayCameraInformationFromRowIndex(m_cameraDataGridView.SelectedRows[0].Index);
            }
        }

        private void UpdateControlStatus(int rowIndex)
        {
            // No cameras were selected
            if (rowIndex == -1)
            {
                m_okButton.Enabled = false;
                m_configButton.Enabled = false;
                m_forceIpButton.Enabled = false;
            }

            bool badCamera = false;
            bool noCCP = false;
            bool containNoneGigECameras = false;

            foreach (DataGridViewRow row in m_cameraDataGridView.SelectedRows)
            {
                if (m_badCameraInfo.ContainsKey(row.Cells[0].Value.ToString()) && !badCamera)
                {
                    badCamera = true;
                }

                if (row.DefaultCellStyle.BackColor == NO_CCP && !noCCP)
                {
                    noCCP = true;
                }

                if (!row.Cells[2].Value.ToString().Contains("GigE"))
                {
                    containNoneGigECameras = true;
                }
            }

            if (!badCamera && !noCCP)
            {
                if (m_cameraDataGridView.SelectedRows.Count > 1)
                {
                    m_okButton.Enabled = false;
                }
                else
                {
                    m_okButton.Enabled = true;
                }
                m_configButton.Enabled = true;

                if (containNoneGigECameras)
                {
                    m_forceIpButton.Enabled = false;
                }
                else
                {
                    m_forceIpButton.Enabled = true;
                }
            }
            else if (badCamera && !noCCP)
            {
                m_okButton.Enabled &= false;
                m_configButton.Enabled &= false;

                if (containNoneGigECameras)
                {
                    m_forceIpButton.Enabled = false;
                }
                else
                {
                    m_forceIpButton.Enabled = true;
                }
            }
            else// if (!badCamera && noCCP)
            {
                m_okButton.Enabled &= false;
                m_configButton.Enabled &= false;
                m_forceIpButton.Enabled &= false;
            }
        }
    }
}
