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
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /* If you can not open the design view of this class, try to modify base class
     * to "UserControl" instead of "BasePage". VS2005 probably has issue of opening 
     * design view for inherited user control. The reason is still investigating.
     * */

     //internal partial class LUTPage : UserControl
    internal partial class LUTPage : BasePage
    {
        private const uint NumGridPartitions = 4;
        private const float MinPointRange = 10;
        private int LUTInputSize = 512;
        private int LUTOutputSize = 512;
        private uint[] m_lutEntries = null;
        private ArrayList m_keyPoints = new ArrayList();
        private PointF m_currentSelectedPoint = new PointF();
        private bool m_isCurrentlyMovingPoint = false;
        private int m_currentSelectedPointPosition = -1;
        private float m_pointRangeMax = 0;
        private float m_pointRangeMin = 0;
        private int m_graphicWidth = 0;
        private int m_graphicHeight = 0;
        private bool m_stopUpdateEntries = false;
        private Dictionary<string, int> m_channelDictionary = new Dictionary<string, int>();

        public LUTPage(ManagedCameraBase initialCamera)
        {
            SetCamera(initialCamera);
            InitializeComponent();
            InitializePage();
        }

        public void UpdateLUTChannel()
        {
            InitializePage();
        }

        private static void DrawTableGrid(Graphics lutGraphics, int width, int height)
        {
            Pen pen = Pens.LightGray;
            for (uint i = 0; i <= NumGridPartitions; i++)
            {
                //draw vertical lines
                lutGraphics.DrawLine(
                    pen,
                    (width - 1) * i / NumGridPartitions,
                    0f,
                    (width - 1) * i / NumGridPartitions,
                    height);
            }

            for (uint i = 0; i <= NumGridPartitions; i++)
            {
                //draw horizontal lines
                lutGraphics.DrawLine(
                    pen,
                    0f,
                    (height - 1) * i / NumGridPartitions,
                    width,
                    (height - 1) * i / NumGridPartitions);
            }
        }

        private void InitializePage()
        {
            if (m_camera == null)
            {
                //Bad!
                m_mainGroupBox.Enabled = false;
                return;
            }

            LutData data;
            try
            {
                data = m_camera.GetLUTInfo();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error querying LUT support", ex);
                m_lookUpTabelControlPanel.Enabled = false;
                m_lookUpTableDrawingPanel.Enabled = false;
                return;
            }

            if (data.supported == false)
            {
                m_lookUpTabelControlPanel.Enabled = false;
                m_lookUpTableDrawingPanel.Enabled = false;
                m_outputMinLabel.Text = "N/A";
                m_outputMidLabel.Text = "N/A";
                m_outputMaxLabel.Text = "N/A";
                m_inputMinLabel.Text = "N/A";
                m_inputMidLabel.Text = "N/A";
                m_inputMaxLabel.Text = "N/A";
                return;
            }
            else
            {
                m_lookUpTabelControlPanel.Enabled = true;
            }

            uint advFeatureInqRegVal = 0;
            bool isIIDC132Mode = false;
            try
            {
                advFeatureInqRegVal = m_camera.ReadRegister(0x40C);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
            }

            isIIDC132Mode = (advFeatureInqRegVal & 0x08000000) != 0;
            if (isIIDC132Mode == true)
            {
                // There is a non zero value in the IIDC LUT quadlet offset
                // register, assume that this is valid and return
                m_enableLUTInfomation.Text = "(IIDC 1.32 mode)";
                isIIDC132Mode = true;
            }
            else
            {
                // Looks like IIDC is not supported, try PGR
                uint pgrRegVal = 0;
                try
                {
                    pgrRegVal = m_camera.ReadRegister(0x1A40);

                    //if there is no exception above, then it means current mode is PGR
                    m_enableLUTInfomation.Text = "(PGR mode)";
                }
                catch (FC2Exception ex)
                {
                    m_enableLUTInfomation.Text = String.Empty;
                }
            }

            PopulateBankComboBox(data.numBanks);
            UpdateSelectedBank();

            PopulateChannelComboBox(data.numChannels);

            int inputMax = 0;
            inputMax = (int)data.numEntries - 1;
            LUTInputSize = (int)data.numEntries;

            // Set input data
            m_inputMinLabel.Text = "0";
            m_inputMidLabel.Text = string.Format("{0}", inputMax / 2);
            m_inputMaxLabel.Text = string.Format("{0}", inputMax);
            m_inputMaxLabel.AutoSize = true;
            m_graphicWidth = inputMax;

            // Set output data
            double bitDepth = data.outputBitDepth;
            LUTOutputSize = (int)Math.Pow(2, bitDepth);
            int outputMax = LUTOutputSize - 1;
            

            m_outputMinLabel.Text = "0";
            m_outputMidLabel.Text = string.Format("{0}", outputMax / 2);
            m_outputMaxLabel.Text = string.Format("{0}", outputMax);
            m_graphicHeight = outputMax;

            // make sure graphic dimension is valid
            if (m_graphicHeight == 0 || m_graphicWidth == 0)
            {
                m_lookUpTabelControlPanel.Enabled = false;
                m_lookUpTableDrawingPanel.Enabled = false;
                return;
            }

            OnLoadFromCamera();

            m_enableLookUpTableCheckBox.Checked = data.enabled;
        }

        private void PopulateChannelComboBox(uint numChannels)
        {
            m_channelComboBox.Items.Clear();
            m_channelDictionary.Clear();
            Debug.Assert(numChannels == 1 || numChannels == 3, "The number of channel must be either 1 or 3.");

            if (numChannels == 1)
            {
                AddToChannelComboBox("All", 0);
            }
            else if (numChannels == 3)
            {
                AddToChannelComboBox("All", -1);
                AddToChannelComboBox("Red", 0);
                AddToChannelComboBox("Green", 1);
                AddToChannelComboBox("Blue", 2);
            }

            if (m_channelComboBox.Items.Count > 0)
            {
                m_channelComboBox.SelectedIndex = 0;
            }
        }

        private void AddToChannelComboBox(string description, int channel)
        {
            m_channelDictionary.Add(description, channel);
            m_channelComboBox.Items.Add(description);
        }

        private void PopulateBankComboBox(uint numBanks)
        {
            m_bankComboBox.Items.Clear();
            for (int i = 0; i < (int)numBanks; i++)
            {
                m_bankComboBox.Items.Add(i);
            }
        }

        private void UpdateSelectedBank()
        {
            if (m_bankComboBox.Items.Count > 0)
            {
                try
                {
                    int currBank = (int)m_camera.GetActiveLUTBank();
                    if (m_bankComboBox.SelectedIndex != currBank)
                    {
                        m_bankComboBox.SelectedIndex = currBank;
                    }
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying LUT support", ex);
                }
                catch (ArgumentOutOfRangeException /*ex*/)
                {
                    Debug.WriteLine("LUT bank index out of range! Setting to -1 as backup.");
                    m_bankComboBox.SelectedIndex = -1;
                }
            }
        }

        private void OnEnableLookUpTableCheckedStatusChanged(object sender, EventArgs e)
        {
            try
            {
                //this function seems not working
                m_camera.EnableLUT(m_enableLookUpTableCheckBox.Checked);
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error toggling LUT", ex);
            }
        }

        private void OnLoadFromCameraButtonClick(object sender, EventArgs e)
        {
            OnLoadFromCamera();
        }

        private void OnLoadFromCamera()
        {
            LutData data;
            try
            {
                data = m_camera.GetLUTInfo();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error querying LUT support", ex);
                return;
            }

            uint bank;
            try
            {
                bank = m_camera.GetActiveLUTBank();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error querying LUT bank", ex);
                return;
            }

            string currentSelectedChannelString = m_channelComboBox.SelectedItem.ToString();
            int channel = m_channelDictionary[currentSelectedChannelString];
            if (channel == -1)
            {
                // If we're on the "All" channels setting, just get the zeroth channel.
                channel = 0;
            }

            uint[] entries = new uint[data.numEntries];
            try
            {
                m_camera.GetLUTChannel(bank, (uint)channel, data.numEntries, entries);
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Error getting LUT channel. " + ex.Message);
                Debug.WriteLine(ex.StackTrace);
                Debug.WriteLine(ex.TargetSite);
                ////ShowErrorMessageDialog("Error getting LUT channel", ex);
                ResetLUTEntries();
                ex.Dispose();
                return;
            }

            SetLutEntries(entries);
        }

        private void SetLutEntries(uint[] entries)
        {
            m_lutEntries = new uint[entries.Length];
            for (uint i = 0; i < m_lutEntries.Length; i++)
            {
                m_lutEntries[i] = (uint)entries[i];
            }

            //set defualt line style to free mode.
            m_lineStyleFreeRadioButton.Checked = true;
            m_drawingArea.Refresh();
        }

        private void ResetLUTEntries()
        {
            float slope = (float)LUTOutputSize / (float)LUTInputSize;
            m_lutEntries = new uint[LUTInputSize];
            for (int i = 0; i < m_lutEntries.Length; i++)
            {
                m_lutEntries[i] = (uint)((float)i * slope);
            }

            m_lineStyleFreeRadioButton.Checked = true;
            m_drawingArea.Refresh();
        }

        private void OnLookUpTableDrawingPanelPaint(object sender, PaintEventArgs e)
        {
            Graphics drawingPanelGraphics = e.Graphics;
            Font font = m_inputLabel.Font; //new Font("Microsoft Sans Serif", 8F, FontStyle.Bold, GraphicsUnit.Point, ((byte)(0)));
            drawingPanelGraphics.RotateTransform(270f);
            Brush brush;
            if (m_lookUpTableDrawingPanel.Enabled == false)
            {
                brush = Brushes.DimGray;
            }
            else
            {
                brush = Brushes.Black;
            }

            drawingPanelGraphics.DrawString("Output", font, brush, -m_lookUpTableDrawingPanel.Height / 2.0f, 0f);
        }

        private void PressMouseButton(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left || m_graphicHeight == 0 || m_graphicWidth == 0 || m_lookUpTabelControlPanel.Enabled == false)
            {
                return;
            }

            float x = (float)e.X * m_graphicWidth / m_drawingArea.Width;
            float y = (float)e.Y * m_graphicHeight / m_drawingArea.Height;
            if (m_lineStyleFreeRadioButton.Checked == true)
            {
                //do nothing
            }
            else if (m_lineStyleLinearRadioButton.Checked == true ||
                     m_lineStyleSplineRadioButton.Checked == true)
            {
                if (m_isCurrentlyMovingPoint)
                {
                    int tempIndex = FindClosestPoint(x);
                    m_keyPoints.RemoveAt(tempIndex);
                }

                int pointIndex;
                for (pointIndex = 0; pointIndex < m_keyPoints.Count; pointIndex++)
                {
                    float px = ((PointF)m_keyPoints[pointIndex]).X;
                    if (px > x)
                    {
                        //find the position which the point should insert
                        break;
                    }
                }

                m_currentSelectedPointPosition = pointIndex;
                if (pointIndex == 0)
                {
                    m_pointRangeMin = 0;

                    //TODO: fix no key point bug
                    m_pointRangeMax = ((PointF)m_keyPoints[0]).X;
                }
                else if (pointIndex > m_keyPoints.Count - 1)
                {
                    m_pointRangeMax = m_graphicWidth;
                    m_pointRangeMin = ((PointF)m_keyPoints[pointIndex - 1]).X;
                }
                else
                {
                    m_pointRangeMax = ((PointF)m_keyPoints[pointIndex]).X;
                    m_pointRangeMin = ((PointF)m_keyPoints[pointIndex - 1]).X;
                }
            }

            m_drawingArea.Refresh();
        }

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            int x = e.X * m_graphicWidth / m_drawingArea.Width;
            int y = e.Y * m_graphicHeight / m_drawingArea.Height;
            RectangleF bound = new RectangleF(0.0f, 0.0f, (float)m_graphicWidth, (float)m_graphicHeight);
            if (x > bound.Right)
            {
                x = (int)bound.Right;
            }
            else if (x < bound.Left)
            {
                x = (int)bound.Left;
            }

            if (y > bound.Bottom)
            {
                y = (int)bound.Bottom;
            }
            else if (y < bound.Top)
            {
                y = (int)bound.Top;
            }

            if (m_lineStyleFreeRadioButton.Checked == true)
            {
                Cursor.Current = Cursors.Default;
                if (e.Button == MouseButtons.Left && !m_stopUpdateEntries)
                {
                    int endIndex = (int)x;
                    int startIndex = (int)m_currentSelectedPoint.X;
                    while (startIndex != endIndex)
                    {
                        m_lutEntries[startIndex] = (uint)(m_graphicHeight - y);
                        if (startIndex > endIndex)
                        {
                            startIndex--;
                        }
                        else
                        {
                            startIndex++;
                        }
                    }

                    m_currentSelectedPoint.X = x;
                    m_drawingArea.Refresh();
                }
                else
                {
                    m_currentSelectedPoint.X = x;
                    m_stopUpdateEntries = false;
                }
            }
            else
            {
                if (m_keyPoints.Count == 0)
                {
                    //TODO: add some functions to deal with camera when is not streaming
                    return;
                }

                float distance = Math.Abs(((PointF)m_keyPoints[FindClosestPoint(x)]).X - x);
                if (distance < MinPointRange)
                {
                    m_isCurrentlyMovingPoint = true;
                    Cursor.Current = Cursors.SizeAll;
                }
                else
                {
                    m_isCurrentlyMovingPoint = false;
                    Cursor.Current = Cursors.Cross;
                }

                if (m_currentSelectedPointPosition != -1)
                {
                    m_currentSelectedPoint.X = x;
                    m_currentSelectedPoint.Y = y;
                    if (m_currentSelectedPoint.X < m_pointRangeMax &&
                        m_currentSelectedPoint.X > m_pointRangeMin)
                    {
                        m_keyPoints.Insert(m_currentSelectedPointPosition, m_currentSelectedPoint);
                        Cursor.Current = Cursors.SizeAll;

                        //update normal points
                        UpdateLutEntries();
                        m_keyPoints.Remove(m_currentSelectedPoint);
                        m_drawingArea.Refresh();
                    }
                    else
                    {
                        UpdateLutEntries();
                        m_drawingArea.Refresh();
                    }
                }
            }
        }

        private void ReleaseMouseButton(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left || m_graphicHeight == 0 || m_graphicWidth == 0 || m_lookUpTabelControlPanel.Enabled == false)
            {
                return;
            }

            if (m_lineStyleFreeRadioButton.Checked == true)
            {
                //do nothing
            }
            else
            {
                //start to insert a key point
                if (m_currentSelectedPointPosition != -1 &&
                    m_currentSelectedPoint.X < m_pointRangeMax &&
                    m_currentSelectedPoint.X > m_pointRangeMin)
                {
                    if (m_currentSelectedPoint.Y < 0)
                    {
                        m_currentSelectedPoint.Y = 0;
                    }
                    else if (m_currentSelectedPoint.Y > (float)m_graphicHeight)
                    {
                        m_currentSelectedPoint.Y = m_graphicHeight;
                    }

                    m_keyPoints.Insert(m_currentSelectedPointPosition, m_currentSelectedPoint);
                }

                m_currentSelectedPointPosition = -1;
                if (m_keyPoints.Count < 2)
                {
                    //if there is less than 2 key points, 
                    //it will cause problem of update LUT entries 
                    UpdateKeyPoints(2);
                }

                UpdateLutEntries();
            }

            m_drawingArea.Refresh();
        }

        private void UpdateLutEntries()
        {
            if (m_keyPoints.Count < 2)
            {
                //should have at least 2 key point, otherwise set all value zero
                m_lutEntries.Initialize();
                return;
            }

            if (m_lineStyleLinearRadioButton.Checked == true)
            {
                int keyPointIndex = 0;
                PointF startKeyPoint = (PointF)m_keyPoints[keyPointIndex];
                PointF endKeyPoint = (PointF)m_keyPoints[keyPointIndex + 1];

                //line up dots
                for (int index = 0; index < m_lutEntries.Length - 1; index++)
                {
                    int coordinateXForGraphic = (index * m_graphicWidth) / m_lutEntries.Length;
                    if (coordinateXForGraphic < startKeyPoint.X)
                    {
                        m_lutEntries[index] = 0;
                        continue;
                    }

                    if (coordinateXForGraphic > endKeyPoint.X)
                    {
                        keyPointIndex++;
                        if (keyPointIndex < m_keyPoints.Count - 1)
                        {
                            startKeyPoint = (PointF)m_keyPoints[keyPointIndex];
                            endKeyPoint = (PointF)m_keyPoints[keyPointIndex + 1];
                        }
                        else
                        {
                            m_lutEntries[index] = 0;
                            continue;
                        }
                    }

                    float relatedHeight = -(startKeyPoint.Y - endKeyPoint.Y); // this equation is from (outputMax- startKeyPoint.Y) -(outputMax - endKeyPoint.Y);
                    float relatedYoffsetToStartKeyPoint = (coordinateXForGraphic - startKeyPoint.X) * relatedHeight / (startKeyPoint.X - endKeyPoint.X);
                    m_lutEntries[index] = (uint)((int)relatedYoffsetToStartKeyPoint + m_graphicHeight - (int)startKeyPoint.Y);
                }
            }
            else if (m_lineStyleSplineRadioButton.Checked == true)
            {
                //spline mode
                int numOfKeyPoints = m_keyPoints.Count;
                float[] keyPointX = new float[numOfKeyPoints];
                float[] keyPointY = new float[numOfKeyPoints];

                for (int i = 0; i < numOfKeyPoints; i++)
                {
                    keyPointX[i] = ((PointF)m_keyPoints[i]).X;
                    keyPointY[i] = ((PointF)m_keyPoints[i]).Y;
                }

                float[] tangentValueOfKeyPointY = MathUtilities.GetTangentPoints(keyPointY, numOfKeyPoints);
                for (float i = keyPointX[0]; i < keyPointX[numOfKeyPoints - 1]; i++)
                {
                    int index = Convert.ToInt32(i);
                    float entryValue = MathUtilities.SplineFunction(keyPointX, keyPointY, tangentValueOfKeyPointY, i, numOfKeyPoints);
                    m_lutEntries[index] = (uint)(m_graphicHeight - (int)entryValue);
                }

                //finalize the entries' data
                PointF startKeyPoint = (PointF)m_keyPoints[0];
                PointF endKeyPoint = (PointF)m_keyPoints[m_keyPoints.Count - 1];
                for (int i = 0; i < m_lutEntries.Length; i++)
                {
                    float coordinateXForGraphic = (i * m_graphicWidth) / m_lutEntries.Length;
                    if (coordinateXForGraphic < startKeyPoint.X ||
                        coordinateXForGraphic > endKeyPoint.X)
                    {
                        m_lutEntries[i] = 0;
                        continue;
                    }

                    if (m_lutEntries[i] < 0)
                    {
                        m_lutEntries[i] = 0;
                    }
                    else if (m_lutEntries[i] > m_graphicHeight)
                    {
                        m_lutEntries[i] = (uint)m_graphicHeight;
                    }
                }
            }
            else
            {
                //free mode!?
                //actually if it is free mode, this function will never called
                //so it might be a bug if code goes here and current line style is free.
            }
        }

        private int FindClosestPoint(float x)
        {
            int index = 0;
            for (int i = 1; i < m_keyPoints.Count; i++)
            {
                float distance = Math.Abs(((PointF)m_keyPoints[i]).X - x);
                float minDistance = Math.Abs(((PointF)m_keyPoints[index]).X - x);
                if (distance < minDistance)
                {
                    index = i;
                }
            }

            return index;
        }

        private void OnDrawingAreaPaint(object sender, PaintEventArgs e)
        {
            Graphics lutGraphics = e.Graphics;
            if (m_graphicHeight == 0 || m_graphicWidth == 0 || m_lookUpTabelControlPanel.Enabled == false)
            {
                DrawTableGrid(lutGraphics, m_drawingArea.Width, m_drawingArea.Height);
                Font font = new Font("Tahoma", 8F, FontStyle.Regular, GraphicsUnit.Point, (byte)0);
                StringFormat format = new StringFormat();
                format.Alignment = StringAlignment.Center;
                format.LineAlignment = StringAlignment.Center;
                lutGraphics.DrawString(
                    "This camera does not support look up table.",
                    font,
                    Brushes.Black,
                    m_drawingArea.Width / 2,
                    m_drawingArea.Height / 2,
                    format);
                return;
            }

            // Draw table Grid first
            lutGraphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
            lutGraphics.ScaleTransform(
                (float)m_drawingArea.Width / m_graphicWidth,
                (float)m_drawingArea.Height / m_graphicHeight);
            DrawTableGrid(lutGraphics, m_graphicWidth, m_graphicHeight);
            if (m_lutEntries == null || m_lutEntries.Length == 0)
            {
                //there is no need to draw LUT Data
                return;
            }

            DrawLUTEntries(lutGraphics);
        }       

        private void DrawLUTEntries(Graphics lutGraphics)
        {
            if (m_lineStyleFreeRadioButton.Checked == false)
            {
                DrawKeyPoints(lutGraphics);
            }

            DrawPoints(lutGraphics);
        }

        private void DrawKeyPoints(Graphics lutGraphics)
        {
            foreach (PointF point in m_keyPoints)
            {
                lutGraphics.FillEllipse(
                    Brushes.Red,
                    point.X - 3, 
                    point.Y - 3, 
                    6, 
                    6);
            }
        }

        private void DrawPoints(Graphics lutGraphics)
        {
            if (m_graphicHeight == 0 || m_graphicWidth == 0)
            {
                Debug.WriteLine("Bug: this page has not initialized yet. Invalid output max value.");
                return;
            }

            float outputMax = m_graphicHeight;
            for (uint i = 0; i < m_lutEntries.Length; i++)
            {
                PointF point = new PointF(
                               (i * m_graphicWidth) / (m_lutEntries.Length - 1), 
                               m_graphicHeight - ((m_lutEntries[i] * m_graphicHeight) / outputMax));
                point.Y = point.Y - 1.0f; //move up a little bit, and user can see the point y is zero
                lutGraphics.FillEllipse(
                    Brushes.Red,
                    point.X - 1.0f, 
                    point.Y - 1.0f, 
                    2.0f, 
                    2.0f);
            }
        }

        private void UpdateKeyPoints(uint numOfKeyPoints)
        {
            //TODO: add some functions to deal with camera when is not streaming
            if (m_graphicHeight == 0 || m_graphicWidth == 0 || m_lutEntries == null)
            {
                Debug.WriteLine("Bug: this page has not initialized yet. Invalid output max value.");
                return;
            }

            m_keyPoints.Clear();
            float outputMax = m_graphicHeight;
            for (int i = 0; i < numOfKeyPoints; i++)
            {
                float entryValue = m_lutEntries[(m_lutEntries.Length - 1) * i / (numOfKeyPoints - 1)];
                m_keyPoints.Add(
                new PointF(
                (i * m_graphicWidth) / (numOfKeyPoints - 1),
                m_graphicHeight - ((entryValue * m_graphicHeight) / outputMax)));
            }
        }

        private void OnLineStyleChanged(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            if (button.Checked == false)
            {
                return;
            }

            if (button != m_lineStyleFreeRadioButton)
            {
                UpdateKeyPoints((NumGridPartitions * 2) + 1);
                UpdateLutEntries();
            }

            m_drawingArea.Refresh();
        }

        private void OnSetToCamera(object sender, EventArgs e)
        {
            // Fix for Bug 15500 to get around the firmware issue
            // Make sure LUT has been enabled prior to setting LUT
            // to camera
            if (!m_enableLookUpTableCheckBox.Checked)
            {
                m_enableLookUpTableCheckBox.Checked = true;
            }

            LutData data;
            try
            {
                data = m_camera.GetLUTInfo();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error querying LUT support", ex);
                return;
            }

            uint bank;
            try
            {
                bank = m_camera.GetActiveLUTBank();
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Error querying LUT bank", ex);
                return;
            }

            string currentSelectedChannelString = m_channelComboBox.SelectedItem.ToString();
            int channel = m_channelDictionary[currentSelectedChannelString];
            uint[] entries = new uint[data.numEntries];

            for (int i = 0; i < data.numEntries; i++)
            {
                entries[i] = (uint)m_lutEntries[i];
            }

            if (channel == -1)
            {
                for (uint i = 0; i < 3; i++)
                {
                    try
                    {
                        m_camera.SetLUTChannel(bank, i, data.numEntries, entries);
                    }
                    catch (FC2Exception ex)
                    {
                        ShowErrorMessageDialog("Error setting LUT channel", ex);
                        return;
                    }
                }
            }
            else
            {
                try
                {
                    m_camera.SetLUTChannel(bank, (uint)channel, data.numEntries, entries);
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error setting LUT channel", ex);
                    return;
                }
            }
        }

        private void OnLineStyleClearButtonClick(object sender, EventArgs e)
        {
            ResetLUTEntries();
        }

        private void OnOpenFileButtonClick(object sender, EventArgs e)
        {
            if (m_openFileDialog.ShowDialog() == DialogResult.OK)
            {
                //fix a bug: when user click close dialog and mouse is on the drawing area, 
                //the data in m_lutEntries will be overwrite (it means that click will also affect to drawing area), 
                //so the update from drawing area should stop now when open File Dialog shows up
                m_stopUpdateEntries = true;
                StreamReader fileStream;
                try
                {
                    fileStream = new StreamReader(m_openFileDialog.FileName);
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

                LutData data;
                try
                {
                    data = m_camera.GetLUTInfo();
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying LUT support", ex);
                    fileStream.Close();
                    return;
                }

                uint[] entries = new uint[data.numEntries];
                for (uint i = 0; i < entries.Length; i++)
                {
                    uint currInput = 0;
                    uint currResult = 0;
                    string currLine = fileStream.ReadLine();
                    if (currLine == null)
                    {
                        entries[i] = 0;
                        continue;
                    }

                    string[] numbersFromCurrLine = currLine.Split(new char[] { ',' });
                    if (numbersFromCurrLine.Length != 2)
                    {
                        MessageBox.Show(
                            "Required format not found. Aborting file load.",
                            "Error reading LUT data from file",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Error);
                        fileStream.Close();
                        return;
                    }

                    try
                    {
                        currInput = Convert.ToUInt32(numbersFromCurrLine[0]);
                        currResult = Convert.ToUInt32(numbersFromCurrLine[1]);
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine("Invalid LUT data detected.");
                        entries[i] = 0;
                        continue;
                    }

                    if (currInput < 0 ||
                        currInput >= data.numEntries ||
                        currInput != i)
                    {
                        DialogResult result;
                        result = MessageBox.Show(
                            "LUT data appears to be invalid\r\n. Do you wish to abort file load.",
                            "Invalid LUT data detected",
                            MessageBoxButtons.YesNo,
                            MessageBoxIcon.Error);

                        if (result == DialogResult.No)
                        {
                            entries[i] = 0;
                            continue;
                        }
                        else
                        {
                            fileStream.Close();
                            return;
                        }
                    }

                    // Data passed validation check, add it to the list of entries
                    entries[i] = currResult;
                }

                fileStream.Close();
                SetLutEntries(entries);
            }
        }

        private void OnSaveFileButtonClick(object sender, EventArgs e)
        {
            string initialFileName;
            
            try
            {
                initialFileName = m_camera.GetCameraInfo().serialNumber.ToString();
            }
            catch (FC2Exception ex)
            {
                Debug.WriteLine("Unable to get Camera Info. {0}", ex.Message);
                return;
            }
            
            m_saveFileDialog.FileName = initialFileName + ".lut";

            if (m_saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                //fix a bug: when user click close dialog and mouse is on the drawing area, 
                //the data in m_lutEntries will be overwrite (it means that click will also affect to drawing area), 
                //so the update from drawing area should stop now when save File Dialog shows up
                m_stopUpdateEntries = true;
                StreamWriter fileStream;
                try
                {
                    fileStream = new StreamWriter(m_saveFileDialog.FileName);
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

                LutData data;
                try
                {
                    data = m_camera.GetLUTInfo();
                }
                catch (FC2Exception ex)
                {
                    ShowErrorMessageDialog("Error querying LUT support", ex);
                    fileStream.Close();
                    return;
                }


                for (uint i = 0; i < data.numEntries; i++)
                {
                    string currLine;
                    try
                    {
                        currLine = string.Format("{0},{1}", i, m_lutEntries[i]);
                        fileStream.WriteLine(currLine);
                    }
                    catch (FormatException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        Debug.WriteLine(ex.StackTrace);
                        fileStream.Close();
                        ShowErrorMessageDialog(
                        "There was an argument which does not meet the parameter specifications. Aborting file write.", ex);
                        break;
                    }
                    catch (IOException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        Debug.WriteLine(ex.StackTrace);
                        fileStream.Close();
                        ShowErrorMessageDialog(
                        "Error writing the current string to file. Aborting file write.", ex);
                        break;
                    }
                    catch (ArgumentNullException ex)
                    {
                        Debug.WriteLine(ex.Message);
                        Debug.WriteLine(ex.StackTrace);
                        fileStream.Close();
                        ShowErrorMessageDialog(
                        "Error writing to file. The current string is null. Aborting file write.", ex);
                        break;
                    }
                }

                fileStream.Close();
            }
        }

        private void OnChannelComboBoxSelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_channelComboBox.Items.Count == 0)
            {
                return;
            }

            OnLoadFromCamera();
        }

        private void OnBankComboBoxSelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                if (m_bankComboBox.Items.Count == 0 || m_bankComboBox.SelectedIndex == -1)
                {
                    return;
                }

                int currentActiveBank = (int)m_bankComboBox.SelectedItem;
                if ((uint)currentActiveBank != m_camera.GetActiveLUTBank())
                {
                    m_camera.SetActiveLUTBank((uint)currentActiveBank);
                    OnLoadFromCamera();
                }
            }
            catch (FC2Exception ex)
            {
                ShowErrorMessageDialog("Failed to set LUT bank", ex);
            }
        }
    }
}
