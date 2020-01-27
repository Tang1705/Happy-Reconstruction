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
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Text;

using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    internal class NodeSurface
    {
        private const int NodeWidth = 120;
        private const int NodeHeight = 60;
        private const int PortWidth = 20;
        private const int PortHeight = 10;
        private const int RoundedRectangleMargin = 10;

        private double k_pi = 4.0 * Math.Atan(1.0);
        private int m_xPos = 0;
        private int m_yPos = 0;
        private int m_deviceId = 0;
        private ManagedPGRGuid m_guid;
        private Bitmap m_surface;

        public NodeSurface()
        {
            m_xPos = 0;
            m_yPos = 0;
            m_guid = new ManagedPGRGuid();
            m_deviceId = 0;
            m_surface = new Bitmap(NodeWidth, NodeHeight);
        }

        public static void GetDimensions(out int width, out int height)
        {
            width = NodeWidth;
            height = NodeHeight;
        }

        public static void GetPortDimensions(out int width, out int height)
        {
            width = PortWidth;
            height = PortHeight;
        }

        public static Color GetNodeColor(ManagedTopologyNode.NodeType type)
        {
            Color resultBrush;
            switch (type)
            {
                case ManagedTopologyNode.NodeType.Computer:
                    resultBrush = Color.DarkTurquoise;
                    break;
                case ManagedTopologyNode.NodeType.Bus:
                    resultBrush = Color.DodgerBlue;
                    break;
                case ManagedTopologyNode.NodeType.Node:
                    resultBrush = Color.Orange;
                    break;
                case ManagedTopologyNode.NodeType.Camera:
                    resultBrush = Color.Gray;
                    break;
                default:
                    resultBrush = Color.White;
                    break;
            }

            return resultBrush;
        }

        public Bitmap GetBitmapImage()
        {
            return m_surface;
        }

        public void Update(ManagedTopologyNode node, bool selected)
        {
            Debug.Assert(node != null, "node paramter is null");
            if (node == null)
            {                
                return;
            }

            // Store the PGRGuid so we can handle device information on clicks
            m_guid = node.GetGuid();
            m_deviceId = node.GetDeviceId();

            // Create a context for the surface
            Graphics surfaceGraphics = Graphics.FromImage(m_surface);
            surfaceGraphics.Clear(Color.White);            
            
            Pen pen;
            if (selected == true)
            {
                pen = new Pen(Color.Red, 3);
            }
            else
            {
                pen = new Pen(Color.Black, 1);
            }

            using (pen)
            {
                int width = m_surface.Width;
                int height = m_surface.Height;

                Rectangle surfaceRectangle = new Rectangle(
                       0 + RoundedRectangleMargin,
                       0 + RoundedRectangleMargin,
                       width - (2 * RoundedRectangleMargin),
                       height - (2 * RoundedRectangleMargin));

                const int Radius = 20;
                DrawRoundedRectangle(surfaceGraphics, surfaceRectangle, Radius, pen, GetNodeColor(node.GetNodeType()));

                DrawTextToGraphics(GetNodeText(node), surfaceGraphics, width, height);

                DrawPorts(node, surfaceGraphics);
            }            
        }

        public void SetPosition(int x, int y)
        {
            m_xPos = x;
            m_yPos = y;
        }

        public void GetPosition(out int x, out int y)
        {
            x = m_xPos;
            y = m_yPos;
        }

        public int GetRoundedRectangleMargin()
        {
            return RoundedRectangleMargin;
        }

        public ManagedPGRGuid GetGuid()
        {
            return m_guid;
        }

        private static void DrawPorts(ManagedTopologyNode node, Graphics graphics)
        {
            int numChildren = 0;
            for (uint i = 0; i < node.GetNumPorts(); i++)
            {
                if (node.GetPortType(i) == ManagedTopologyNode.PortType.ConnectedToChild)
                {
                    numChildren++;
                }
            }

            int childIndex = 0;
            for (uint i = 0; i < node.GetNumPorts(); i++)
            {
                ManagedTopologyNode.PortType currPort = node.GetPortType(i);
                switch (currPort)
                {
                    case ManagedTopologyNode.PortType.NotConnected:
                        break;
                    case ManagedTopologyNode.PortType.ConnectedToParent:
                        graphics.FillRectangle(
                            Brushes.Black, 
                            (NodeWidth / 2) - (PortWidth / 2), 
                            0, 
                            PortWidth, 
                            PortHeight);
                        break;
                    case ManagedTopologyNode.PortType.ConnectedToChild:
                        int startX = (NodeWidth / (numChildren + 1)) * (childIndex + 1);
                        graphics.FillRectangle(
                            Brushes.Black, 
                            startX - (PortWidth / 2), 
                            NodeHeight - PortHeight, 
                            PortWidth, 
                            PortHeight);
                        childIndex++;
                        break;
                    default:
                        break;
                }
            }
        }

        private static void DrawTextToGraphics(string text, Graphics surfaceGraphics, int width, int height)
        {
            Font font = new Font("Tahoma", 14F, FontStyle.Bold, GraphicsUnit.Pixel);
            StringFormat format = new StringFormat();
            format.Alignment = StringAlignment.Center;
            format.LineAlignment = StringAlignment.Center;
            surfaceGraphics.DrawString(text, font, Brushes.Black, width / 2, height / 2, format);
        }

        private static string GetNodeText(ManagedTopologyNode node)
        {
            string result;
            ManagedTopologyNode.NodeType nodeType = node.GetNodeType();
            switch (nodeType)
            {
                case ManagedTopologyNode.NodeType.Computer:
                    result = "PC";
                    break;
                case ManagedTopologyNode.NodeType.Bus:
                    InterfaceType ifType = node.GetInterfaceType();
                    switch (ifType)
                    {
                        case InterfaceType.Ieee1394:
                            result = "1394 Bus";
                            break;
                        case InterfaceType.Usb2:
                            result = "USB 2.0 Bus";
                            break;
                        case InterfaceType.Usb3:
                            result = "USB 3.0 Bus";
                            break;
                        case InterfaceType.GigE:
                            result = "GigE Bus";
                            break;
                        default:
                            result = "Bus";
                            break;
                    }

                    break;
                case ManagedTopologyNode.NodeType.Camera:
                    result = string.Format("ID: {0}", node.GetDeviceId());
                    break;
                case ManagedTopologyNode.NodeType.Node:
                    if (node.GetGuid().Equals(new ManagedPGRGuid()))
                    {
                        result = "Node";
                    }
                    else
                    {
                        result = "Node*";
                    }

                    break;
                default:
                    result = "Unknown";
                    break;
            }

            return result;
        }

        private void DrawRoundedRectangle(Graphics surfaceGraphics, Rectangle bounds, int cornerRadius, Pen drawPen, Color fillColor)
        {
            GraphicsPath graphicsPath = new GraphicsPath();
            drawPen.EndCap = drawPen.StartCap = LineCap.Round;
            graphicsPath.AddArc(bounds.X, bounds.Y, cornerRadius, cornerRadius, 180, 90);
            graphicsPath.AddArc(bounds.X + bounds.Width - cornerRadius, bounds.Y, cornerRadius, cornerRadius, 270, 90);
            graphicsPath.AddArc(bounds.X + bounds.Width - cornerRadius, bounds.Y + bounds.Height - cornerRadius, cornerRadius, cornerRadius, 0, 90);
            graphicsPath.AddArc(bounds.X, bounds.Y + bounds.Height - cornerRadius, cornerRadius, cornerRadius, 90, 90);
            graphicsPath.CloseAllFigures();
            surfaceGraphics.FillPath(new SolidBrush(fillColor), graphicsPath);
            surfaceGraphics.DrawPath(drawPen, graphicsPath);
        }
    }

    internal class Line
    {
        private int m_startX;
        private int m_startY;
        private int m_endX;
        private int m_endY;

        public Line()
        {
            m_startX = 0;
            m_startY = 0;
            m_endX = 0;
            m_endY = 0;
        }

        public Line(int startX, int startY, int endX, int endY)
        {
            m_startX = startX;
            m_startY = startY;
            m_endX = endX;
            m_endY = endY;
        }

        public int StartX
        {
            get
            {
                return m_startX;
            }

            set
            {
                m_startX = value;
            }
        }

        public int StartY
        {
            get
            {
                return m_startY;
            }

            set
            {
                m_startY = value;
            }
        }

        public int EndX
        {
            get
            {
                return m_endX;
            }

            set
            {
                m_endX = value;
            }
        }

        public int EndY
        {
            get
            {
                return m_endY;
            }

            set
            {
                m_endY = value;
            }
        }
    }
}
