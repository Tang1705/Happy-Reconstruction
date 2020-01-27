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
using System.Text;
using System.Windows.Forms;

using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /* If you can not open the design view of this class, try to modify base class
     * to "UserControl" instead of "BasePage". VS2005 probably has issue of opening 
     * design view for inherited user control. The reason is still investigating.
     * */

    // public partial class HelpSupportPage : UserControl
    internal partial class HelpSupportPage : BasePage
    {
        public HelpSupportPage()
        {
            InitializeComponent();
        }

        private void OnLinkLabelClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            LinkLabel label = sender as LinkLabel;
            string url = label.Tag.ToString();
            if (e.Button == MouseButtons.Right)
            {
                m_copyURLItem.Tag = url;
                m_copyMenuStrip.Show(MousePosition);
            }
            else
            {
                ManagedUtilities.LaunchBrowser(url);
            }
        }

        private void OnCopyURLClick(object sender, EventArgs e)
        {
            try
            {
                Clipboard.SetText(m_copyURLItem.Tag.ToString());
            }
            catch (ArgumentNullException ex)
            {
                ShowErrorMessageDialog("Error copying URL to clipboad. The URL is null value.", ex);
            }
            catch (System.Threading.ThreadStateException ex)
            {
                ShowErrorMessageDialog("Error copying URL to clipboad. The copying thread is invalid", ex);
            }
        }
    }
}
