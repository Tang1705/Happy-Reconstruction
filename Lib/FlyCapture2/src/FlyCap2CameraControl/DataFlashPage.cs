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
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /* If you can not open the design view of this class, try to modify base class
     * to "UserControl" instead of "BasePage". VS2005 probably has issue of opening 
     * design view for inherited user control. The reason is still investigating.
     * */

    // public partial class DataFlashPage : UserControl
    internal partial class DataFlashPage : BasePage
    {
        private const uint DataFlashReg = 0x1240;
        private const uint DataFlashOffsetReg = 0x1244;

        private BackgroundWorker m_operationThread;

        public DataFlashPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitializePage();
        }

        private void InitializePage()
        {
            if (m_camera == null)
            {
                //Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            if (m_camInfo == null)
            {
                SetCameraInfo(m_camera);
            }

            // Check if the camera is a Dragonfly (as it is not supported)
            if (m_camInfo.modelName.Equals("Dragonfly"))
            {
                DisableWidgets();
                return;
            }

            if (IsDataFlashSupported() == false)
            {
                DisableWidgets();
                return;
            }

            EnableWidgets();

            // Get flash size
            m_dataFlashSizeValue.Text = string.Format("{0} KB", GetDataFlashSize() / 1024);
            RefreshTextViewPreview();
            InitializeBackgroundWorker();
        }

        private void InitializeBackgroundWorker()
        {
            m_operationThread = new BackgroundWorker();
            m_operationThread.WorkerReportsProgress = true;
            m_operationThread.DoWork += new DoWorkEventHandler(DoOperationWork);
            m_operationThread.ProgressChanged += new ProgressChangedEventHandler(UpdateProgressBar);
            m_operationThread.RunWorkerCompleted += new RunWorkerCompletedEventHandler(RunWorkerCompleted);
        }

        private void DisableWidgets()
        {
            m_operationsControlPanel.Enabled = false;
            m_flashDataPreviewPanel.Enabled = false;
            m_statusValue.Text = "Not Available";
        }

        private void EnableWidgets()
        {
            m_operationsControlPanel.Enabled = true;
            m_flashDataPreviewPanel.Enabled = true;
            m_statusValue.Text = "Available";
        }

        private bool IsDataFlashSupported()
        {
            uint value;
            try
            {
                value = m_camera.ReadRegister(DataFlashReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading data flash register", ex);
                ex.Dispose();
                return false;
            }

            return (value >> 31) != 0;
        }

        private uint GetDataFlashSize()
        {
            return GetPageSize() * GetNumPages();
        }

        private uint GetPageSize()
        {
            uint value;
            try
            {
                value = m_camera.ReadRegister(DataFlashReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading data flash register", ex);
                ex.Dispose();
                return 0;
            }

            double exponent = Convert.ToDouble((value & 0x00FFF000) >> 12);
            return (uint)Math.Pow(2.0, exponent);
        }

        private uint GetNumPages()
        {
            uint value;
            try
            {
                value = m_camera.ReadRegister(DataFlashReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading data flash register", ex);
                ex.Dispose();
                return 0;
            }

            double exponent = Convert.ToDouble(value & 0x00000FFF);
            return (uint)Math.Pow(2.0, exponent);
        }

        private void RefreshTextViewPreview()
        {
            uint value;
            try
            {
                value = m_camera.ReadRegister(DataFlashOffsetReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading data flash offset register", ex);
                ex.Dispose();
                return;
            }

            const uint PreviewSize = 256;

            // Read the first kilobyte (1024 bytes/256 quadlets) of data and display it
            uint[] flashData = new uint[PreviewSize];
            try
            {
                m_camera.ReadRegisterBlock(
                            0xFFFF,
                            0xF0000000 + (value * 4),
                            flashData);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error performing block read", ex);
                ex.Dispose();
                return;
            }

            string previewString = string.Empty;
            for (uint i = 0; i < PreviewSize - 4; i += 4)
            {
                string temp = string.Format(
                                "{0:x8} {1:x8} {2:x8} {3:x8}\r\n",
                                flashData[i + 0],
                                flashData[i + 1],
                                flashData[i + 2],
                                flashData[i + 3]);
                previewString += temp.ToUpper();                
            }

            m_flashDataPreviewTextbox.Text = previewString;
        }

        private void OnRefreshPreviewButtonClick(object sender, EventArgs e)
        {
            RefreshTextViewPreview();
        }

        private void OnFlashToFileButtonClick(object sender, EventArgs e)
        {
            string initialFileName;
            
            try
            {
                initialFileName = m_camera.GetCameraInfo().serialNumber.ToString();
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Unable to get Camera Info. {0}", ex.Message);
                ex.Dispose();
                return;
            }
            
            m_saveFileDialog.FileName = initialFileName + "-flash.dat";

            if (m_saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                InitializeOperation();
                m_operationThread.RunWorkerAsync("FlashToFile");
            }
        }

        private void OnFileToFlashButtonClick(object sender, EventArgs e)
        {
            if (m_openFileDialog.ShowDialog() == DialogResult.OK)
            {
                InitializeOperation();
                m_operationThread.RunWorkerAsync("FileToFlash");
            }
        }

        private void OnEraseFlashButtonClick(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show(
                                  "This process is irreversible! Do you wish to continue?",
                                  "Permanent loss of data",
                                  MessageBoxButtons.YesNo,
                                  MessageBoxIcon.Warning);
            if (result == DialogResult.Yes)
            {
                InitializeOperation();
                m_operationThread.RunWorkerAsync("EraseFlash");
            }
        }

        private void InitializeOperation()
        {
            DisableWidgets();
            m_operationProgressBar.Value = 0;
            m_progressText.Visible = true;
            m_operationProgressBar.Maximum = (int)GetNumPages();
        }

        private void DoOperationWork(object sender, DoWorkEventArgs e)
        {
            switch (e.Argument.ToString())
            {
                case "FlashToFile":
                    FlashToFileWorker();
                    break;
                case "FileToFlash":
                    FileToFlashWorker();
                    break;
                case "EraseFlash":
                    EraseFlashWorker();
                    break;
            }
        }

        private void FlashToFileWorker()
        {
            FileStream fileStream;
            try
            {
                fileStream = new FileStream(m_saveFileDialog.FileName, FileMode.Create);
            }
            catch (UnauthorizedAccessException ex)
            {
                ShowErrorMessageDialog(
                    "Can not save the file. The access is unauthorized. \r\n" +                 
                    "Please contact administrator for more information.", 
                    ex);
                return;
            }
            catch (System.Security.SecurityException ex)
            {
                ShowErrorMessageDialog("Can not save the file due to security policy.\r\n", ex);
                return;
            }
            catch (ArgumentException ex)
            {
                ShowErrorMessageDialog("Can not save the file. Invalid file name or mode.\r\n", ex);
                return;
            }
            catch (System.IO.IOException ex)
            {
                ShowErrorMessageDialog("Can not save the file. Write file data failed.", ex);
                return;
            }
           
            uint offsetVal = 0;
            try
            {
                offsetVal = m_camera.ReadRegister(DataFlashOffsetReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading register. The operation was not completed successfully.", ex);
                ex.Dispose();
                return;
            }

            uint startOffset = 0xF0000000 + (offsetVal * 4);
            uint currOffset = startOffset;
            uint pageSize = GetPageSize();
            uint numPages = GetNumPages();
            uint availableFlashSize = GetDataFlashSize();
            uint[] flashData = new uint[availableFlashSize / 4];

            for (uint i = 0; i < numPages; i++)
            {
                uint[] buffer = new uint[pageSize / 4];
                try
                {
                    m_camera.ReadRegisterBlock(
                               0xFFFF,
                               currOffset,
                               buffer);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error reading register block. The operation was not completed successfully.", ex);
                    ex.Dispose();
                    return;
                }
                
                for (uint j = 0; j < buffer.Length; j++)
                {
                    flashData[((i * pageSize) / 4) + j] = buffer[j];
                }

                currOffset += pageSize;
                m_operationThread.ReportProgress((int)i);
            }

            for (int i = 0; i < flashData.Length; i++)
            {
                byte[] dataByte = BitConverter.GetBytes(flashData[i]);
                for (int j = 0; j < dataByte.Length; j++)
                {
                    try
                    {
                        fileStream.WriteByte(dataByte[j]);
                    }
                    catch (ObjectDisposedException ex)
                    {
                        ShowErrorMessageDialog("Error writing the data flash to file due to object disposed. Aborting file write.", ex);
                        fileStream.Close();
                        return;
                    }
                    catch (NotSupportedException ex)
                    {
                        ShowErrorMessageDialog("The writing method (FileStream::WriteByte()) is not supported for this computer. Aborting file write.", ex);
                        fileStream.Close();
                        return;
                    }
                }
            }

            fileStream.Close();
        }

        private void FileToFlashWorker()
        {
            FileStream fileStream;
            try
            {
                fileStream = new FileStream(m_openFileDialog.FileName, FileMode.Open);
            }
            catch (UnauthorizedAccessException ex)
            {
                ShowErrorMessageDialog(
                        "Can not open the file. The access is unauthorized. \r\n" +
                        "Please contact administrator for more information.",
                        ex);
                return;
            }
            catch (System.Security.SecurityException ex)
            {
                ShowErrorMessageDialog("Can not open the file due to security policy.\r\n", ex);
                return;
            }
            catch (ArgumentException ex)
            {
                ShowErrorMessageDialog("Can not open the file. Invalid file name or mode.\r\n", ex);
                return;
            }
            catch (System.IO.IOException ex)
            {
                ShowErrorMessageDialog("Can not open the file. Read file data failed.", ex);
                return;
            }
            
            uint offsetVal = 0;
            try
            {
                offsetVal = m_camera.ReadRegister(DataFlashOffsetReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading register. The operation was not completed successfully.", ex);
                ex.Dispose();
                return;
            }

            uint startOffset = 0xF0000000 + (offsetVal * 4);
            uint currOffset = startOffset;
            uint pageSize = GetPageSize();
            uint numPages = GetNumPages();
            uint availableFlashSize = GetDataFlashSize();
            uint[] flashData = new uint[availableFlashSize / 4];


            long fileLength = fileStream.Length;
            long byteCounter = 0;

            for (uint i = 0; i < numPages; i++)
            {
                if (byteCounter >= fileLength)
                {
                    break;
                }

                uint[] buffer;
                long remainingBytes = fileLength - byteCounter;
                if (remainingBytes >= pageSize)
                {
                    buffer = new uint[pageSize / 4];
                }
                else
                {
                    long numWords = remainingBytes / 4;

                    if (remainingBytes % 4 > 0)
                    {
                        numWords++;
                    }

                    buffer = new uint[numWords];
                }
                
                for (uint j = 0; j < buffer.Length; j++)
                {
                    byte[] dataByte = new byte[4];
                    for (uint k = 0; k < 4; k++)
                    {
                        dataByte[k] = (byte)fileStream.ReadByte();
                    }

                    buffer[j] = BitConverter.ToUInt32(dataByte, 0);
                }

                try
                {
                    m_camera.WriteRegisterBlock(
                                0xFFFF,
                                currOffset,
                                buffer);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error writing register block. The operation was not completed successfully.", ex);
                    ex.Dispose();
                    return;
                }
                
                currOffset += pageSize;
                byteCounter += pageSize;
                m_operationThread.ReportProgress((int)i);
            }

            fileStream.Close();
        }

        private void EraseFlashWorker()
        {
            uint offsetVal = 0;
            try
            {
                offsetVal = m_camera.ReadRegister(DataFlashOffsetReg);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error reading register. The operation was not completed successfully.", ex);
                ex.Dispose();
                return;
            }

            uint startOffset = 0xF0000000 + (offsetVal * 4);
            uint currOffset = startOffset;
            uint pageSize = GetPageSize();
            uint numPages = GetNumPages();
            uint availableFlashSize = GetDataFlashSize();
            uint[] flashData = new uint[availableFlashSize / 4];
            for (uint i = 0; i < numPages; i++)
            {
                uint[] buffer = new uint[pageSize / 4];
                for (uint j = 0; j < buffer.Length; j++)
                {
                    buffer[j] = 0xFFFFFFFF;
                }

                try
                {
                    m_camera.WriteRegisterBlock(
                                0xFFFF,
                                currOffset,
                                buffer);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error writing register block. The writing operation was not completed successfully.", ex);
                    ex.Dispose();
                    return;
                }
               
                currOffset += pageSize;
                m_operationThread.ReportProgress((int)i);
            }
        }

        private void RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            m_progressText.Text = "Progress status: Done.";
            m_operationProgressBar.Value = m_operationProgressBar.Minimum;
            EnableWidgets();
            RefreshTextViewPreview();
        }

        private void UpdateProgressBar(object sender, ProgressChangedEventArgs e)
        {
            try
            {
                m_operationProgressBar.Value = e.ProgressPercentage;
                m_progressText.Text = string.Format(
                                        "Progress status: {0}/{1}, Percentage: {2}%",
                                        m_operationProgressBar.Value + 1,
                                        m_operationProgressBar.Maximum,
                                        (m_operationProgressBar.Value + 1) * 100 / m_operationProgressBar.Maximum);
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine("Invalid progress percentage value.");
                Debug.WriteLine(ex.Message);
            }
            catch (FormatException ex)
            {
                Debug.WriteLine("There is a argument does not meet the parameter specifications of the sting::format() method.");
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }
        }
    }
}
