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
        public class CameraControlDialog
        {
            private CameraControlMainFrame m_mainFrame;
            ////private bool m_isFirstTimeRun;
            public CameraControlDialog()
            {
                //// m_isFirstTimeRun = true;
                Application.EnableVisualStyles();
                //// Application.DoEvents();
                m_mainFrame = new CameraControlMainFrame();
            }

            public void Connect(ManagedCameraBase camera)
            {
                m_mainFrame.Connect(camera);
            }

            public void Disconnect()
            {
                m_mainFrame.Disconnect();
            }

            public void Hide()
            {
                m_mainFrame.HideWindow();
            }

            public void Show()
            {
                m_mainFrame.ShowWindow();
            }

            public void Show(int owner)
            {
               IntPtr parentWindowHandle = new IntPtr(owner);
               IWin32Window parent = Control.FromHandle(parentWindowHandle);
               m_mainFrame.ShowWindow(parent);
            }

            public void ShowModal()
            {
                m_mainFrame.ShowModal();
            }

            public void ShowModal(int owner)
            {
                IntPtr parentWindowHandle = new IntPtr(owner);
                IWin32Window parent = Control.FromHandle(parentWindowHandle);
                m_mainFrame.ShowModal(parent);
            }

            public bool IsVisible()
            {
                return m_mainFrame.Visible;
            }

            public void SetTitle(string title)
            {
                m_mainFrame.SetTitle(title);
            }
        }
    }
}
