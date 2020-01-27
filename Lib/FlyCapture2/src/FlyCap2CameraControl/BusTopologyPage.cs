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
    /* If you can not open the design view of this class, try to modify base class
     * to "UserControl" instead of "BasePage". VS2005 probably has issue of opening 
     * design view for inherited user control. The reason is still investigating.
     * */

    //public partial class BusTopologyPage : UserControl
    internal partial class BusTopologyPage : BasePage
    {
        private ManagedBusManager m_busMgr;
        private ManagedTopologyNode m_baseNode;
        private List<NodeSurface> m_nodeSurfaces = new List<NodeSurface>();
        private List<Line> m_lines = new List<Line>();
        private int m_usedWidth = 0;
        private int m_usedHeight = 0;
        private int m_imageWidth = 0;
        private int m_imageHeight = 0;
        private bool m_redrawTree = false;
        private float m_currAspectRatio = 1.0f;
        private int m_prevMousePosX = 0;
        private int m_prevMousePosY = 0;
        private int m_offsetX = 0;
        private int m_offsetY = 0;
        private float m_imageZoom = 1.0f;

        private ManagedPGRGuid m_selectedGuid = new ManagedPGRGuid(); // empty GUID
        private bool m_isSelectionValid = false;
        private NodeDesc m_nodeDesc = new NodeDesc();

        // Tooltip related variables
        private ManagedPGRGuid m_currCameraGuid;
        private ManagedPGRGuid m_lastTooltipGuid = new ManagedPGRGuid();
        private string m_tooltipString = String.Empty;

        public BusTopologyPage(ManagedCameraBase initCamera)
        {
            SetCamera(initCamera);
            InitializeComponent();
            InitializePage();
        }

        private static int CountLevels(ManagedTopologyNode node, int seed)
        {
            if (node == null)
            {
                return -1;
            }

            int result = seed;

            for (uint i = 0; i < node.GetNumChildren(); i++)
            {
                ManagedTopologyNode childNode = node.GetChild(i);
                int newSeed = CountLevels(childNode, seed + 1);
                if (newSeed > result)
                {
                    result = newSeed;
                }
            }

            return result;
        }

        private static int CountNum2ndGenChildren(ManagedTopologyNode node)
        {
            int num2ndGenChildren = 0;
            for (uint i = 0; i < node.GetNumChildren(); i++)
            {
                num2ndGenChildren += (int)node.GetChild(i).GetNumChildren();
                if (node.GetChild(i).GetNumChildren() == 0)
                {
                    num2ndGenChildren++;
                }
            }

            return num2ndGenChildren;
        }

        private static uint GetField(Register field, uint regVal)
        {
            int shiftCount = 0;
            uint tempMask = field.Mask;
            while ((tempMask & 0x01) == 0)
            {
                tempMask = tempMask >> 1;
                shiftCount++;
            }

            return (regVal & field.Mask) >> shiftCount;
        }

        private static bool IsGuidValid(ManagedPGRGuid guid)
        {
            if (guid.Equals(new ManagedPGRGuid()) == false)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        private void InitializePage()
        {
            m_busMgr = new ManagedBusManager();
            m_imageWidth = m_drawingArea.Width;
            m_imageHeight = m_drawingArea.Height;
            ResetNodeInformation();
            OnRefreshTopology();
            SetColors();

            if (m_camInfo != null)
            {
                m_currCameraGuid = m_busMgr.GetCameraFromSerialNumber(m_camInfo.serialNumber);
            }
        }

        private void OnRefreshTopology()
        {
            try
            {
                m_baseNode = m_busMgr.GetTopology();
                m_redrawTree = true;
            }
            catch (FC2Exception ex)
            {
                // Error
                Debug.WriteLine("Error getting topology." + ex.Message);
                ex.Dispose();
            }

            m_drawingArea.Refresh();

            if (m_selectedGuid.Equals(new ManagedPGRGuid()) == false)
            {
                // If current selected node is not a null node,
                // We need to update node information as well
                UpdateNodeInformation(m_selectedGuid);
            }
        }

        private void SetColors()
        {
            m_legendPCColor.BackColor = NodeSurface.GetNodeColor(ManagedTopologyNode.NodeType.Computer);
            m_legendBusColor.BackColor = NodeSurface.GetNodeColor(ManagedTopologyNode.NodeType.Bus);
            m_legendNodeColor.BackColor = NodeSurface.GetNodeColor(ManagedTopologyNode.NodeType.Node);
            m_legendCameraColor.BackColor = NodeSurface.GetNodeColor(ManagedTopologyNode.NodeType.Camera);
        }

        private void OnPhyDisplayControlButton_Click(object sender, EventArgs e)
        {
            m_phyRegDisplayGroupBox.Visible = !m_phyRegDisplayGroupBox.Visible;
            if (m_phyRegDisplayGroupBox.Visible == true)
            {
                m_phyDisplayControlButton.Text = "Hide Phy Registers";
            }
            else
            {
                m_phyDisplayControlButton.Text = "Show Phy Registers";
            }
        }

        private void OnTopologyGraphicPaint(object sender, PaintEventArgs e)
        {
            if (m_baseNode == null)
            {
                // Bad!
                return;
            }

            Graphics drawingAreaGraphics = e.Graphics;
                
            if (m_redrawTree == true)
            {
                CreateTree();
                m_redrawTree = false;
            }
            
            float finalRatio = 1.0f / k_multiplier;
            float widthRatio = (float)m_usedWidth / m_imageWidth;
            float heightRatio = (float)m_usedHeight / m_imageHeight;
            finalRatio = 1 / Math.Max(widthRatio, heightRatio);
            m_currAspectRatio = finalRatio;
            int finalWidth = (int)(finalRatio * m_usedWidth);
            int finalHeight = (int)(finalRatio * m_usedHeight);
            m_offsetX = (m_imageWidth / 2) - (finalWidth / 2);
            m_offsetY = (m_imageHeight / 2) - (finalHeight / 2);

            // move graphics to center
            drawingAreaGraphics.TranslateTransform(m_offsetX, m_offsetY);

            // Scale the surface to fit on the widget
            drawingAreaGraphics.ScaleTransform(finalRatio, finalRatio);
            drawingAreaGraphics.ScaleTransform(m_imageZoom, m_imageZoom);   

            // start to draw the image graph
            DrawTree(drawingAreaGraphics);
        }

        private void CreateTree()
        {
            // Get width / height of node surface
            int nodeSurfaceWidth, nodeSurfaceHeight;
            NodeSurface.GetDimensions(out nodeSurfaceWidth, out nodeSurfaceHeight);

            // Count the depth of the topology
            int numLevels = CountLevels(m_baseNode, 1);
            int heightPerLevel = m_usedHeight / numLevels;
            if (heightPerLevel < (nodeSurfaceHeight + k_vertSpacing))
            {
                m_usedHeight = numLevels * (nodeSurfaceHeight + k_vertSpacing);
                heightPerLevel = m_usedHeight / numLevels;
            }

            int overlap = -1;
            while (overlap != 0)
            {
                ClearVectors();
                overlap = ParseNode(m_baseNode, m_usedWidth, heightPerLevel, 0, 0);
                m_usedWidth += overlap;
            }
        }

        private void DrawTree(Graphics drawingAreaGraphics)
        {
            drawingAreaGraphics.Clear(Color.White);
            drawingAreaGraphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;

            // Get width / height of node surface
            int nodeSurfaceWidth, nodeSurfaceHeight;
            NodeSurface.GetDimensions(out nodeSurfaceWidth, out nodeSurfaceHeight);

            // Draw node surfaces
            for (int i = 0; i < m_nodeSurfaces.Count; i++)
            {
                NodeSurface currNodeSurface = m_nodeSurfaces[i];
                int xPos, yPos;
                currNodeSurface.GetPosition(out xPos, out yPos);
                xPos -= nodeSurfaceWidth / 2;
                yPos -= nodeSurfaceHeight / 2;
                drawingAreaGraphics.DrawImage(currNodeSurface.GetBitmapImage(), xPos, yPos);
            }

            // Draw Draw Node Connector
            for (int i = 0; i < m_lines.Count; i++)
            {
                Line line = m_lines[i];
                Pen pen = new Pen(Brushes.Black, 4.0f);
                int portWidth, portHeight;
                NodeSurface.GetPortDimensions(out portWidth, out portHeight);
                Point[] points = new Point[]
                {
                    new Point(line.StartX, line.StartY - (portHeight / 2)),
                    new Point(line.StartX, line.StartY + 5),
                    new Point(line.EndX, line.EndY - 5),
                    new Point(line.EndX, line.EndY + (portHeight / 2))
                };
                drawingAreaGraphics.DrawLines(pen, points);
            }
        }

        private void ClearVectors()
        {
            m_nodeSurfaces.Clear();
            m_lines.Clear();
        }

        private int ParseNode(ManagedTopologyNode node, int width, int height, int horzOffset, int vertOffset)
        {
            // To improve the layout of the tree, the allocation of width is
            // determined by the number of second generation children rather than
            // just immediate children.
            int num2ndGenChildren = CountNum2ndGenChildren(node);
            int widthUnit;
            if (num2ndGenChildren == 0)
            {
                widthUnit = width;
            }
            else
            {
                widthUnit = width / num2ndGenChildren;
            }

            int nextHorzOffset = horzOffset;

            // Calculate the position of the node
            int nodeXPos = horzOffset + (width / 2);
            int nodeYPos = vertOffset + (height / 2);

            // Add this node to the list of surfaces to be drawn   
            InsertNewNodeSurface(node, nodeXPos, nodeYPos);

            // Figure out there are any children to be recursively drawn
            int accumOverlap = 0;
            uint childIndex = 0;
            for (uint portIndex = 0; portIndex < node.GetNumPorts(); portIndex++)
            {
                ManagedTopologyNode.PortType currPort = node.GetPortType(portIndex);
                if (currPort == ManagedTopologyNode.PortType.ConnectedToChild)
                {
                    ManagedTopologyNode currChild = node.GetChild(childIndex);
                    int thisWidth = widthUnit * ((int)currChild.GetNumChildren());
                    if (thisWidth == 0)
                    {
                        thisWidth = widthUnit;
                    }

                    int thisCenterX = nextHorzOffset + (thisWidth / 2);
                    int thisCenterY = vertOffset + height + (height / 2);

                    int surfaceWidth, surfaceHeight;
                    NodeSurface.GetDimensions(out surfaceWidth, out surfaceHeight);

                    // There might be more than 1 child, so perform some
                    // calculations so that the lines don't start from
                    // the same point  
                    int numChildren = (int)node.GetNumChildren();
                    int startX = unchecked((int)(nodeXPos + ((surfaceWidth / (numChildren + 1)) * (childIndex + 1)) - (surfaceWidth / 2)));
                    int startY = nodeYPos + (surfaceHeight / 2);

                    int endX = thisCenterX;
                    int endY = thisCenterY - (surfaceHeight / 2);

                    // Start a line to be drawn later
                    Line newLine = new Line(startX, startY, endX, endY);
                    m_lines.Add(newLine);

                    ManagedTopologyNode nextChild = node.GetChild(childIndex++);
                    accumOverlap += ParseNode(
                                    nextChild,
                                    thisWidth,
                                    height,
                                    nextHorzOffset,
                                    vertOffset + height);

                    nextHorzOffset += thisWidth;
                }
            }

            int nodeWidth, nodeHeight;
            NodeSurface.GetDimensions(out nodeWidth, out nodeHeight);
            if (width < nodeWidth)
            {
                accumOverlap += nodeWidth - width;
            }

            if (m_usedWidth < (horzOffset + width))
            {
                accumOverlap += (horzOffset + width) - m_usedWidth;
            }

            return accumOverlap;
        }        

        private void InsertNewNodeSurface(ManagedTopologyNode node, int xPos, int yPos)
        {
            NodeSurface nodeSurface = new NodeSurface();
            bool selected = false;
            if (m_selectedGuid.Equals(node.GetGuid()) && m_isSelectionValid == true)
            {
                selected = true;
            }

            nodeSurface.Update(node, selected);
            nodeSurface.SetPosition(xPos, yPos);
            m_nodeSurfaces.Add(nodeSurface);
        }

        /** Checks if the position specified is over a camera node surface. */
        private bool IsSelectionValid(MouseEventArgs e, ref ManagedPGRGuid selectedGuid)
        {
            float displayAspectRatio = 1 / (m_currAspectRatio * m_imageZoom);
            float actualX = (float)e.X * displayAspectRatio;
            float actualY = (float)e.Y * displayAspectRatio;

            // Get the node surface width
            int surfaceWidth, surfaceHeight;
            NodeSurface.GetDimensions(out surfaceWidth, out surfaceHeight);
            actualX += (surfaceWidth / 2) - (m_offsetX * displayAspectRatio);
            actualY += (surfaceHeight / 2) - (m_offsetY * displayAspectRatio);

            selectedGuid = new ManagedPGRGuid();

            foreach (NodeSurface currentNodeSurface in m_nodeSurfaces)
            {
                int xPos, yPos;
                currentNodeSurface.GetPosition(out xPos, out yPos);
                int roundedRectangleMargin = currentNodeSurface.GetRoundedRectangleMargin();
                ManagedPGRGuid currGuid = currentNodeSurface.GetGuid();
                if (actualX >= xPos + roundedRectangleMargin &&
                    actualX <= xPos + surfaceWidth - roundedRectangleMargin &&
                    actualY >= yPos + roundedRectangleMargin &&
                    actualY <= yPos + surfaceHeight - roundedRectangleMargin &&
                    IsGuidValid(currGuid) == true)
                {
                    // Store the guid so we can draw something around
                    // the current selection
                    selectedGuid = currGuid;
                    return true;                    
                }
            }

            return false;
        }

        private void OnDrawingAreaMousePress(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                m_isSelectionValid = IsSelectionValid(e, ref m_selectedGuid);
                
                if (m_isSelectionValid == true)
                {
                    UpdateNodeInformation(m_selectedGuid);
                }
                else
                {
                    ResetNodeInformation();
                }

                m_redrawTree = true;
                m_drawingArea.Refresh();

                m_prevMousePosX = Cursor.Position.X;
                m_prevMousePosY = Cursor.Position.Y;
                Cursor.Current = Cursors.SizeAll;
            }
        }

        private void OnDrawingAreaMouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                // In this case, we can not use e.X and e.Y for calculation 
                // because e.X and e.Y are the value which is a related value (not abs value).
                // The picture box scroll position will be changed, and that will effect e.X and e.Y.
                // We must use absolute mouse position here, so I use Cursor.Position instead.
                int x = -m_imagePanel.AutoScrollPosition.X - (Cursor.Position.X - m_prevMousePosX);
                int y = -m_imagePanel.AutoScrollPosition.Y - (Cursor.Position.Y - m_prevMousePosY);
                m_imagePanel.AutoScrollPosition = new Point(x, y);
                m_prevMousePosX = Cursor.Position.X;
                m_prevMousePosY = Cursor.Position.Y;
                m_drawingArea.Refresh();
            }
            else
            {
                Cursor.Current = Cursors.Default;
            }  

            ManagedPGRGuid mouseOverGuid = new ManagedPGRGuid();
            bool isMouseOverValid = IsSelectionValid(e, ref mouseOverGuid);

            if (!isMouseOverValid)
            {
                cameraInfoToolTip.Active = false;
                return;
            }

            Control ctlSender = (Control)sender;
            string currentTooltipString = cameraInfoToolTip.GetToolTip(ctlSender);
            string newTooltipString = string.Empty;
            try
            {
                newTooltipString = GenerateToolTipString(mouseOverGuid);
            }
            catch (FC2Exception ex)
            {
                cameraInfoToolTip.Active = false;
                ex.Dispose();
                return;
            }

            // Only set the tooltip string if the string has changed, this
            // prevents a nasty flicker problem that can occur as the
            // string is drawn repeatedly
            if (currentTooltipString != newTooltipString)
            {
                cameraInfoToolTip.SetToolTip(ctlSender, newTooltipString);                
            }

            cameraInfoToolTip.Active = true;
        }

        private string GenerateToolTipString(ManagedPGRGuid guid)
        {
            if (guid.Equals(m_lastTooltipGuid))
            {
                return m_tooltipString;
            }

            m_lastTooltipGuid = guid;

            if (guid.Equals(m_currCameraGuid))
            {
                StringBuilder tooltipStr = new StringBuilder();
                tooltipStr.AppendFormat("Camera: {0} {1} ({2})", m_camInfo.vendorName, m_camInfo.modelName, m_camInfo.serialNumber).AppendLine();
                tooltipStr.AppendFormat("Sensor: {0}", m_camInfo.sensorInfo).AppendLine();
                tooltipStr.AppendFormat("Firmware: {0} Built: {1}", m_camInfo.firmwareVersion, m_camInfo.firmwareBuildTime).AppendLine();
                tooltipStr.AppendFormat("Driver: {0}", m_camInfo.driverName).AppendLine();

                m_tooltipString = tooltipStr.ToString();
                return m_tooltipString;
            }

            ManagedCameraBase tempCamera = null;
            if (m_busMgr.GetInterfaceTypeFromGuid(guid) == InterfaceType.GigE)
            {
                tempCamera = new ManagedGigECamera();                
            }
            else
            {
                tempCamera = new ManagedCamera();
            }

            using (tempCamera)
            {
                tempCamera.Connect(guid);
                CameraInfo camInfo = tempCamera.GetCameraInfo();

                StringBuilder tooltipStr = new StringBuilder();
                tooltipStr.AppendFormat("Camera: {0} {1} ({2})", camInfo.vendorName, camInfo.modelName, camInfo.serialNumber).AppendLine();
                tooltipStr.AppendFormat("Sensor: {0}", camInfo.sensorInfo).AppendLine();
                tooltipStr.AppendFormat("Firmware: {0} Built: {1}", camInfo.firmwareVersion, camInfo.firmwareBuildTime).AppendLine();
                tooltipStr.AppendFormat("Driver: {0}", camInfo.driverName).AppendLine();

                m_tooltipString = tooltipStr.ToString();
                return m_tooltipString;
            }                   
        }        

        private void ResetNodeInformation()
        {
            m_nodeModelValue.Text = "N/A";
            m_nodeProductIDValue.Text = "N/A";
            m_nodeVoltagesValue.Text = "N/A";
            m_nodeCurrentsValue.Text = "N/A";
        }

        private void UpdateNodeInformation(ManagedPGRGuid guidToUse)
        {
            // Fix for Bug 22724
            if(guidToUse.Equals(m_currCameraGuid))
            {
                UpdateNodeModelInformation(m_camInfo);
                UpdateNodeProductIDInformation();
                UpdateNodeVoltageInformation(m_camera);
                UpdateNodeCurrentInformation(m_camera, m_camInfo);
                UpdatePhyRegisters();
            }
            else
            {
                using (ManagedCamera camera = new ManagedCamera())
                {
                    CameraInfo camInfo;

                    try
                    {
                        camera.Connect(guidToUse);
                        camInfo = camera.GetCameraInfo();
                    }
                    catch (FC2Exception ex)
                    {
                        UpdatePhyRegisters();
                        ex.Dispose();
                        return;
                    }

                    UpdateNodeModelInformation(camInfo);
                    UpdateNodeProductIDInformation();
                    UpdateNodeVoltageInformation(camera);
                    UpdateNodeCurrentInformation(camera, camInfo);
                    UpdatePhyRegisters();
                }           
            }
        }

        private void UpdatePhyRegisters()
        {
            ManagedPGRGuid nullGuid = new ManagedPGRGuid();
            if (m_selectedGuid.Equals(m_nodeDesc.Guid))
            {
                return;
            }

            ResetRegisterPane();

            if (m_selectedGuid.Equals(nullGuid))
            {
                m_nodeDesc.Guid = nullGuid;
                return;
            }

            Field vendorID;
            if (GetVendorID(m_selectedGuid, out vendorID) == false)
            {
                m_nodeDesc.Guid = nullGuid;
                ResetRegisterPane();
                return; 
            }

            try
            {
                m_nodeTreeView.BeginUpdate();
                TreeNode currentTreeNode = m_nodeTreeView.Nodes.Add(string.Format("{0} Chipset", vendorID.Name));

                // add base register heading
                TreeNode tempNode = currentTreeNode.Nodes.Add("Base Registers");
                tempNode.Tag = "B#0"; // B#0 is id for this new node
                uint numPorts = GetNumberOfPorts(m_selectedGuid);

                // add port headings
                for (uint i = 0; i < numPorts; i++)
                {
                    tempNode = currentTreeNode.Nodes.Add(string.Format("Port {0}", i));
                    tempNode.Tag = string.Format("P#{0}", i); // this is id for this new node
                }

                m_nodeTreeView.ExpandAll();
                m_nodeTreeView.EndUpdate();
            }
            catch (ArgumentException ex)
            {
                Debug.WriteLine(ex.Message);
                Debug.WriteLine(ex.StackTrace);
                return;
            }
        }

        private void ResetRegisterPane()
        {
            m_nodeTreeView.Nodes.Clear();
            m_nodeInformationDataGridView.Rows.Clear();
        }

        private void UpdateNodeModelInformation(CameraInfo camInfo)
        {
            m_nodeModelValue.Text = string.Format(
                "{0} {1} ({2})",
                camInfo.vendorName,
                camInfo.modelName,
                camInfo.serialNumber);
        }

        private bool GetVendorID(ManagedPGRGuid guid, out Field vendorID)
        {
            vendorID = new Field("Node", 0);

            uint regVal = 0;
            uint vendorVal = 0;

            // read vendor id registers
            for (uint i = 10; i <= 12; i++)
            {
                try
                {
                    regVal = m_busMgr.ReadPhyRegister(guid, k_vendorPage, 0, i);
                }
                catch (FC2Exception ex)
                {
                    ex.Dispose();
                    return false;
                }

                vendorVal = (vendorVal << 8) | regVal;
            }

            vendorID.ID = vendorVal;

            uint count;
            for (count = 0; count < k_vendorList.Length; count++)
            {
                if (vendorVal == k_vendorList[count].ID)
                {
                    vendorID.Name = k_vendorList[count].Name;
                    break;
                }
            }
            
            return true;
        }

        private uint GetNumberOfPorts(ManagedPGRGuid guid)
        {
            uint regVal;
            try
            {
                regVal = m_busMgr.ReadPhyRegister(
                    guid,
                    k_basePage,
                    0,
                    k_baseRegisterInfo[k_totalPortsField].Address);
            }
            catch (FC2Exception ex)
            {
                ex.Dispose();
                return 0;
            }

            return GetField(k_baseRegisterInfo[k_totalPortsField], regVal);        
        }        

        private void UpdateNodeProductIDInformation()
        {
            // TODO: Get product id and figure out the revision
            m_nodeProductIDValue.Text = "N/A";
        }

        private void UpdateNodeVoltageInformation(ManagedCameraBase cam)
        {            
            try
            {
                const uint VoltageReg = 0x1A50;
                uint voltageRegVal = cam.ReadRegister(VoltageReg);

                if (voltageRegVal >> 31 == 0)
                {
                    m_nodeVoltagesValue.Text = "N/A";
                    return;
                }

                int numAvailableVoltages = (int)((voltageRegVal & 0x00FFF000) >> 12);

                if (numAvailableVoltages == 0)
                {
                    m_nodeVoltagesValue.Text = "N/A";
                    return;
                }

                const uint VoltageOffsetReg = 0x1A54;
                uint voltageOffsetRegVal = 0;

                voltageOffsetRegVal = cam.ReadRegister(VoltageOffsetReg);

                List<double> voltageList = new List<double>();
                uint properVoltageOffset = (voltageOffsetRegVal * 4) & 0xFFFF;
                for (uint i = 0; i < numAvailableVoltages; i++)
                {
                    uint currVoltageOffset = properVoltageOffset + (i * 4);
                    uint currVoltageRegVal = cam.ReadRegister(currVoltageOffset);

                    double voltage = MathUtilities.Convert32bitIEEEToFloat(currVoltageRegVal);
                    voltageList.Add(voltage);
                }

                string voltageStr = string.Empty;
                foreach (double voltage in voltageList)
                {
                    voltageStr += string.Format(" | {0:0.000}V", voltage);
                }

                m_nodeVoltagesValue.Text = voltageStr.Substring(3);
            }
            catch (FC2Exception ex)
            {
                m_nodeVoltagesValue.Text = "N/A";
                ex.Dispose();
                return;
            }            
        }

        private void UpdateNodeCurrentInformation(ManagedCameraBase cam, CameraInfo camInfo)
        {
            if (camInfo.iidcVersion < iidcVersion)
            {
                m_nodeCurrentsValue.Text = "N/A";
                return;
            }

            const uint CurrentReg = 0x1A58;
            uint currentRegVal = 0;

            try
            {
                currentRegVal = cam.ReadRegister(CurrentReg);
            }
            catch (FC2Exception ex)
            {
                m_nodeCurrentsValue.Text = "N/A";
                ex.Dispose();
                return;
            }

            if (currentRegVal >> 31 == 0)
            {
                m_nodeCurrentsValue.Text = "N/A";
                return;
            }

            int numAvailableCurrents = (int)((currentRegVal & 0x00FFF000) >> 12);

            if (numAvailableCurrents == 0)
            {
                m_nodeCurrentsValue.Text = "N/A";
                return;
            }

            const uint CurrentOffsetReg = 0x1A5C;
            uint currentOffsetRegVal = 0;

            try
            {
                currentOffsetRegVal = cam.ReadRegister(CurrentOffsetReg);
            }
            catch (FC2Exception ex)
            {
                m_nodeCurrentsValue.Text = "N/A";
                ex.Dispose();
                return;
            }

            List<double> currentsList = new List<double>();
            uint properCurrentOffset = (currentOffsetRegVal * 4) & 0xFFFF;

            for (uint i = 0; i < numAvailableCurrents; i++)
            {
                uint currCurrentOffset = properCurrentOffset + (i * 4);
                uint currCurrentRegVal = 0;
                try
                {
                    currCurrentRegVal = cam.ReadRegister(currCurrentOffset);
                }
                catch (FC2Exception ex)
                {
                    m_nodeCurrentsValue.Text = "N/A";
                    ex.Dispose();
                    return;
                }

                double current = MathUtilities.Convert32bitIEEEToFloat(currCurrentRegVal);
                currentsList.Add(current);
            }

            string currentStr = string.Empty;
            foreach (double current in currentsList)
            {
                currentStr += string.Format(" | {0:0.000}A", current);
            }

            m_nodeCurrentsValue.Text = currentStr.Substring(3);
        }
        
        private void OnNodeTreeViewMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            object id = e.Node.Tag;
            if (id == null)
            {
                m_nodeInformationDataGridView.Rows.Clear();
                return;
            }

            string idStr = id.ToString();
            string[] idParseString = idStr.Split('#');           
            uint port;
            switch (idParseString[0])
            {
                case "B":
                    // base register
                    port = 0;
                    PopulateRegisterPage(port, k_baseRegisterInfo);
                    break;
                case "P":
                    // port status register
                    try
                    {
                        port = Convert.ToUInt32(idParseString[1]);
                    }
                    catch (ArgumentException ex)
                    {
                        Debug.WriteLine("Invalid port number to convert int 32.");
                        Debug.WriteLine(ex.Message);
                        Debug.WriteLine(ex.StackTrace);
                        return;
                    }
                    catch (OverflowException ex)
                    {
                        Debug.WriteLine("Unable to convert port number. The value is overflow.");
                        Debug.WriteLine(ex.Message);
                        Debug.WriteLine(ex.StackTrace);
                        return;
                    }
                    catch (FormatException ex)
                    {
                        Debug.WriteLine("Invalid value format of port number..");
                        Debug.WriteLine(ex.Message);
                        Debug.WriteLine(ex.StackTrace);
                        return;
                    }

                    PopulateRegisterPage(port, k_portStatusInfo);                    
                    break;
                default:
                    // Invalid ID
                    Debug.Write("Invalid ID found!");
                    return;
            }           
        }

        private void PopulateRegisterPage(uint port, Register[] registerInfoArray)
        {
            ManagedBusManager busMgr = new ManagedBusManager();
            m_nodeInformationDataGridView.Rows.Clear();
            uint currAddr = 0;
            uint prevAddr = 0;
            uint regValue = 0;
            bool isFirst = true;
            foreach (Register iter in registerInfoArray)
            {
                prevAddr = currAddr;
                currAddr = iter.Address;
                if (isFirst || currAddr != prevAddr)
                {
                    try
                    {
                        regValue = busMgr.ReadPhyRegister(m_selectedGuid, 0, port, iter.Address);
                    }
                    catch (FC2Exception ex)
                    {
                        Debug.WriteLine(ex.Message);
                        ex.Dispose();
                        return;
                    }

                    isFirst = false;
                }

                // add result to table
                try
                {
                    int rowNum = m_nodeInformationDataGridView.Rows.Add(new DataGridViewRow());
                    m_nodeInformationDataGridView.Rows[rowNum].Cells[0].Value = iter.Name;
                    m_nodeInformationDataGridView.Rows[rowNum].Cells[1].Value = GetField(iter, regValue);
                }
                catch (InvalidOperationException ex)
                {
                    Debug.WriteLine("Error appending new row.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
                catch (ArgumentOutOfRangeException ex)
                {
                    Debug.WriteLine("The information data table is full.");
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                }
            }
        }

        private void OnRefreshButtonClick(object sender, EventArgs e)
        {
             OnRefreshTopology();
        }

        private void ResizeImageDrawingArea()
        {
            HScrollProperties hScroll = m_imagePanel.HorizontalScroll;
            VScrollProperties vScroll = m_imagePanel.VerticalScroll;
            int prevHMax = hScroll.Maximum;
            int prevVMax = vScroll.Maximum;
            bool isHScrollVisible = hScroll.Visible;
            bool isVScrollVisible = vScroll.Visible;
            m_drawingArea.Width = (int)((float)m_imageWidth * m_imageZoom);
            m_drawingArea.Height = (int)((float)m_imageHeight * m_imageZoom);

            if (isHScrollVisible)
            {
                int hNewValue = hScroll.Value + ((hScroll.Maximum - prevHMax) / 2);
                if (hNewValue < hScroll.Minimum)
                {
                    hScroll.Value = hScroll.Minimum;
                }
                else if (hNewValue > hScroll.Maximum)
                {
                    hScroll.Value = hScroll.Maximum;
                }
                else
                {
                    hScroll.Value = hNewValue;
                }
            }
            else
            {
                hScroll.Value = (hScroll.Maximum - hScroll.LargeChange) / 2;
            }

            if (isVScrollVisible)
            {
                int vNewValue = vScroll.Value + ((vScroll.Maximum - prevVMax) / 2);
                if (vNewValue < vScroll.Minimum)
                {
                    vScroll.Value = vScroll.Minimum;
                }
                else if (vNewValue > vScroll.Maximum)
                {
                    vScroll.Value = vScroll.Maximum;
                }
                else
                {
                    vScroll.Value = vNewValue;
                }
            }
            else
            {
                vScroll.Value = (vScroll.Maximum - vScroll.LargeChange) / 2;
            }
           
            m_drawingArea.Refresh();
        }

        private void OnZoomInBtnClick(object sender, EventArgs e)
        {
            if (m_imageZoom < 3.0f)
            {
                m_imageZoom += 0.1f;
            }

            ResizeImageDrawingArea();
        }

        private void OnZoomOutBtnClick(object sender, EventArgs e)
        {
            if (m_imageZoom > 1.0f)
            {
                m_imageZoom -= 0.1f;
                ResizeImageDrawingArea();
            }
        }

        private void OnZoomResetBtnClick(object sender, EventArgs e)
        {
            m_imageZoom = 1.0f;
            ResizeImageDrawingArea();
        }
    }
}
