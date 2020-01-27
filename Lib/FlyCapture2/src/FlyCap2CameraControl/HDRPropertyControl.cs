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
    internal partial class HDRPropertyControl : UserControl
    {
        private ManagedCameraBase m_camera;
        private HDRPage m_parent;
        private int m_imageNumber;

        public HDRPropertyControl(HDRPage initialParent)
        {
            m_parent = initialParent;
            m_camera = m_parent.Camera;
            m_imageNumber = 0;
            InitializeComponent();
            InitializeControl();
        }

        public HDRPropertyControl(HDRPage initialParent, int imageNumber)
        {
            m_parent = initialParent;
            m_camera = m_parent.Camera;
            m_imageNumber = imageNumber;
            InitializeComponent();
            InitializeControl();
        }

        public void SetTitle(string newPropertyControlTitle)
        {
            m_propertyControlLabel.Text = newPropertyControlTitle;
        }

        public void DisableControl()
        {
            m_gainTrackbar.Enabled = false;
            m_shutterTrackbar.Enabled = false;
            m_gainValue.Enabled = false;
            m_shutterValue.Enabled = false;
        }

        public void EnableControl()
        {
            m_gainTrackbar.Enabled = true;
            m_shutterTrackbar.Enabled = true;
            m_gainValue.Enabled = true;
            m_shutterValue.Enabled = true;
        }

        public void UpdateControl()
        {
            if (m_gainTrackbar.Enabled == true)
            {
                UpdateGainProperty();
            }

            if (m_shutterTrackbar.Enabled == true)
            {
                UpdateShutterProperty();
            }
        }

        private void InitializeControl()
        {
            if (m_camera == null)
            {
                //Bad!
                this.Enabled = false;
                return;
            }

            m_propertyControlLabel.Text = string.Format("HDR Image {0}", m_imageNumber + 1);
            if (m_parent.IsHDRSupported())
            {
                UpdateGainProperty();
                UpdateShutterProperty();
            }
            else
            {
                m_gainValue.Text = "N/A";
                m_shutterValue.Text = "N/A";
                DisableControl();
            }
        }

        private void UpdateGainProperty()
        {
            CameraPropertyInfo gainPropInfo;
            try
            {
                gainPropInfo = m_camera.GetPropertyInfo(PropertyType.Gain);
            }
            catch (FC2Exception ex)
            {
                // BasePage.ShowErrorMessageDialog("Error reading gain property", ex); 
                // The message dialog will hang if user unplug camera, so I think we should use debug message instead.
                Debug.WriteLine("Error reading gain property:" + ex.Message);
                m_gainTrackbar.Enabled = false;
                m_gainValue.Enabled = false;
                ex.Dispose();
                return;
            }

            m_gainTrackbar.Maximum = (int)gainPropInfo.max;
            m_gainTrackbar.Minimum = (int)gainPropInfo.min;

            int gainValue = (int)m_parent.GetGain(m_imageNumber);
            if (gainValue > m_gainTrackbar.Maximum)
            {
                gainValue = m_gainTrackbar.Maximum;
            }
            else if (gainValue < m_gainTrackbar.Minimum)
            {
                gainValue = m_gainTrackbar.Minimum;
            }

            m_gainTrackbar.Value = gainValue;
            m_gainValue.Text = m_gainTrackbar.Value.ToString();
        }

        private void UpdateShutterProperty()
        {
            CameraPropertyInfo shutterPropInfo;
            try
            {
                shutterPropInfo = m_camera.GetPropertyInfo(PropertyType.Shutter);
            }
            catch (FC2Exception ex)
            {
                // BasePage.ShowErrorMessageDialog("Error reading Shutter property", ex);
                // The message dialog will hang if user unplug camera, so I think we should use debug message instead.
                Debug.WriteLine("Error reading Shutter property:" + ex.Message);

                m_shutterTrackbar.Enabled = false;
                m_shutterValue.Enabled = false;
                ex.Dispose();
                return;
            }

            m_shutterTrackbar.Maximum = (int)shutterPropInfo.max;
            m_shutterTrackbar.Minimum = (int)shutterPropInfo.min;

            int shutterValue = (int)m_parent.GetShutter(m_imageNumber);
            if (shutterValue > m_shutterTrackbar.Maximum)
            {
                shutterValue = m_shutterTrackbar.Maximum;
            }
            else if (shutterValue < m_shutterTrackbar.Minimum)
            {
                shutterValue = m_shutterTrackbar.Minimum;
            }

            m_shutterTrackbar.Value = shutterValue;
            m_shutterValue.Text = m_shutterTrackbar.Value.ToString();
        }

        private void OnGainTrackbarScroll(object sender, EventArgs e)
        {
            m_parent.SetGain(m_imageNumber, (uint)m_gainTrackbar.Value);
        }

        private void OnShutterTrackbarScroll(object sender, EventArgs e)
        {
            m_parent.SetShutter(m_imageNumber, (uint)m_shutterTrackbar.Value);
        }
    }
}
