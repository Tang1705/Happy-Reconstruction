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
using System.Windows.Forms;

using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /* If you can not open the design view of this class, try to modify base class
     * to "UserControl" instead of "BasePage". VS2005 probably has issue of opening 
     * design view for inherited user control. The reason is still investigating.
     * */

    // public partial class SystemInfoPage : UserControl
    internal partial class SystemInfoPage : BasePage
    {
        public SystemInfoPage()
        {
            InitializeComponent();
            InitializePage();
        }

        private void InitializePage()
        {
            SystemInfo infoStruct = ManagedUtilities.systemInfo;
            m_cpuValue.Text = infoStruct.cpuDescription;
            m_numOfCpuCoresValue.Text = infoStruct.numCpuCores.ToString();
            m_memorySizeValue.Text = string.Format("{0} MB", infoStruct.systemMemorySize);
            if (infoStruct.byteOrder == ByteOrder.LittleEndian)
            {
                m_byteOrderValue.Text = "Little endian";
            }
            else if (infoStruct.byteOrder == ByteOrder.BigEndian)
            {
                m_byteOrderValue.Text = "Big endian";
            }
            else
            {
                m_byteOrderValue.Text = "Unknown";
            }

            m_osValue.Text = infoStruct.osDescription;
            m_gpuValue.Text = infoStruct.gpuDescription;
            uint screenWidth = infoStruct.screenWidth;
            uint screenHeight = infoStruct.screenHeight;
            if (screenHeight > 0 && screenWidth > 0)
            {
                m_resolutionValue.Text = string.Format("{0} x {1}", screenWidth, screenHeight);
            }
            else
            {
                m_resolutionValue.Text = "Unknown";
            }
        }

        private void OnCopyButtonClick(object sender, EventArgs e)
        {
            string clipboardString = "*** FlyCapture2 System Information ***\r\n";
            clipboardString += string.Format("{0} {1}\r\n", m_cpuLabel.Text, m_cpuValue.Text);
            clipboardString += string.Format("{0} {1}\r\n", m_numOfCpuCoresLabel.Text, m_numOfCpuCoresValue.Text);
            clipboardString += string.Format("{0} {1}\r\n", m_memorySizeLabel.Text, m_memorySizeValue.Text);
            clipboardString += string.Format("{0} {1}\r\n", m_byteOrderLabel.Text, m_byteOrderValue.Text);
            clipboardString += string.Format("{0} {1}\r\n", m_osLabel.Text, m_osValue.Text);
            clipboardString += string.Format("{0} {1}\r\n", m_gpuLabel.Text, m_gpuValue.Text);
            clipboardString += string.Format("{0} {1}\r\n", m_resolutionLabel.Text, m_resolutionValue.Text);
            Clipboard.SetText(clipboardString);
        }
    }
}
