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
using System.Drawing;
using System.Security.Permissions;
using System.Text;
using System.Windows.Forms;

namespace FlyCap2CameraControl
{
    internal partial class LoadingWindow : Form
    {
        public LoadingWindow()
        {
            InitializeComponent();
        }
        
        protected override CreateParams CreateParams
        {
            [SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
            get
            {
                //Disable the close button on the title
                CreateParams param = base.CreateParams;
                param.ClassStyle = param.ClassStyle | 0x200;
                return param;
            }
        }

        public void SetProgressBar(int percentage)
        {
            if (Visible == false)
            {
                return;
            }

            if (percentage > m_loadingProgressBar.Maximum)
            {
                m_loadingProgressBar.Value = m_loadingProgressBar.Maximum;
            }
            else if (percentage < m_loadingProgressBar.Minimum)
            {
                m_loadingProgressBar.Value = m_loadingProgressBar.Minimum;
            }
            else
            {
                m_loadingProgressBar.Value = percentage;
            }

            m_loadingProgressBar.Refresh();
        }

        public void SetProgressBar(int percentage, string informationText)
        {
            if (Visible == false)
            {
                return;
            }

            SetInformationText(informationText);
            SetProgressBar(percentage);
        }

        public void SetInformationText(string text)
        {
            if (Visible == false)
            {
                return;
            }

            m_loadingInformationLabel.Text = text;
            m_loadingInformationLabel.Refresh();
        }        
    }
}