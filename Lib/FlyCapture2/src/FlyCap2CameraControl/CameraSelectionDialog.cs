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
using System.Diagnostics;
using System.Text;
using System.Windows.Forms;
using FlyCap2CameraControl;

namespace FlyCapture2Managed
{
    namespace Gui
    {
        public class CameraSelectionDialog
        {
            private CameraSelectionWindow m_selectionDialog;

            public CameraSelectionDialog()
            {
                Application.EnableVisualStyles();
                ////Application.DoEvents();
                m_selectionDialog = new CameraSelectionWindow();
            }

            public bool ShowModal()
            {
                DialogResult result;
                try
                {
                    result = m_selectionDialog.ShowDialog();
                }
                catch (Exception ex)
                {
#if DEBUG
                    string errorStr = String.Format(
                        "Unhandled exception - {0}{1}{2}",
                        ex.Message,
                        Environment.NewLine,
                        ex.StackTrace);
#else
                    string errorStr = String.Format("Unhandled exception - {0}",
                        ex.Message);
#endif
                    MessageBox.Show(errorStr, "Camera Selection Dialog Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Debug.WriteLine(errorStr);
                    return false;
                }

                if (result == DialogResult.OK)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            public ManagedPGRGuid[] GetSelectedCameraGuids()
            {
                return m_selectionDialog.GetCurrentSelectedGuids();
            }

            public bool IsVisible()
            {
                return m_selectionDialog.Visible;
            }

            public void SetTitle(string title)
            {
                m_selectionDialog.SetTitle(title);
            }

            public void Show()
            {
                m_selectionDialog.Show();
            }

            public void Hide()
            {
                m_selectionDialog.Hide();
            }
        }
    }
}
