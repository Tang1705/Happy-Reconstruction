namespace FlyCap2CameraControl
{
    partial class BusTopologyPage
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.m_mainGroupBox = new System.Windows.Forms.GroupBox();
            this.m_busTopologyLayout = new System.Windows.Forms.TableLayoutPanel();
            this.m_phyRegDisplayGroupBox = new System.Windows.Forms.GroupBox();
            this.phyRegDisplayPanel = new System.Windows.Forms.SplitContainer();
            this.m_nodeTreeView = new System.Windows.Forms.TreeView();
            this.m_phyRegNodeLabel = new System.Windows.Forms.Label();
            this.m_nodeInformationDataGridView = new System.Windows.Forms.DataGridView();
            this.m_phyRegRegisterColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_phyRegValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_nodeInfoGroupBox = new System.Windows.Forms.GroupBox();
            this.m_nodeInfoTableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_nodeCurrentsValue = new System.Windows.Forms.Label();
            this.m_nodeCurrentsLabel = new System.Windows.Forms.Label();
            this.m_nodeVoltagesValue = new System.Windows.Forms.Label();
            this.m_nodeVoltageLabel = new System.Windows.Forms.Label();
            this.m_nodeProductIDValue = new System.Windows.Forms.Label();
            this.m_nodeProductIDLabel = new System.Windows.Forms.Label();
            this.m_nodeModelValue = new System.Windows.Forms.Label();
            this.m_nodeModelLabel = new System.Windows.Forms.Label();
            this.m_imagePanel = new System.Windows.Forms.Panel();
            this.m_drawingArea = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.m_legendAdditionalNotesLabel = new System.Windows.Forms.Label();
            this.m_legendCameraColor = new System.Windows.Forms.Panel();
            this.m_legendPCLabel = new System.Windows.Forms.Label();
            this.m_legendNodeColor = new System.Windows.Forms.Panel();
            this.m_legendBusLabel = new System.Windows.Forms.Label();
            this.m_legendBusColor = new System.Windows.Forms.Panel();
            this.m_legendNodeLabel = new System.Windows.Forms.Label();
            this.m_legendPCColor = new System.Windows.Forms.Panel();
            this.m_legendCameraLabel = new System.Windows.Forms.Label();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.m_phyDisplayControlButton = new System.Windows.Forms.Button();
            this.m_refreshButton = new System.Windows.Forms.Button();
            this.m_imageController = new System.Windows.Forms.TableLayoutPanel();
            this.m_zoomInBtn = new System.Windows.Forms.Button();
            this.m_zoomOutBtn = new System.Windows.Forms.Button();
            this.m_zoomResetBtn = new System.Windows.Forms.Button();
            this.cameraInfoToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.m_mainGroupBox.SuspendLayout();
            this.m_busTopologyLayout.SuspendLayout();
            this.m_phyRegDisplayGroupBox.SuspendLayout();
            this.phyRegDisplayPanel.Panel1.SuspendLayout();
            this.phyRegDisplayPanel.Panel2.SuspendLayout();
            this.phyRegDisplayPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nodeInformationDataGridView)).BeginInit();
            this.m_nodeInfoGroupBox.SuspendLayout();
            this.m_nodeInfoTableLayoutPanel.SuspendLayout();
            this.m_imagePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_drawingArea)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.m_imageController.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_busTopologyLayout);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(637, 557);
            this.m_mainGroupBox.TabIndex = 3;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Bus Topology";
            // 
            // m_busTopologyLayout
            // 
            this.m_busTopologyLayout.AutoSize = true;
            this.m_busTopologyLayout.ColumnCount = 2;
            this.m_busTopologyLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.m_busTopologyLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 60F));
            this.m_busTopologyLayout.Controls.Add(this.m_phyRegDisplayGroupBox, 1, 2);
            this.m_busTopologyLayout.Controls.Add(this.m_nodeInfoGroupBox, 0, 3);
            this.m_busTopologyLayout.Controls.Add(this.m_imagePanel, 0, 0);
            this.m_busTopologyLayout.Controls.Add(this.groupBox1, 0, 2);
            this.m_busTopologyLayout.Controls.Add(this.tableLayoutPanel3, 0, 4);
            this.m_busTopologyLayout.Controls.Add(this.m_imageController, 0, 1);
            this.m_busTopologyLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_busTopologyLayout.Location = new System.Drawing.Point(3, 16);
            this.m_busTopologyLayout.Name = "m_busTopologyLayout";
            this.m_busTopologyLayout.RowCount = 5;
            this.m_busTopologyLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_busTopologyLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_busTopologyLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_busTopologyLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_busTopologyLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_busTopologyLayout.Size = new System.Drawing.Size(631, 538);
            this.m_busTopologyLayout.TabIndex = 9;
            // 
            // m_phyRegDisplayGroupBox
            // 
            this.m_phyRegDisplayGroupBox.AutoSize = true;
            this.m_phyRegDisplayGroupBox.Controls.Add(this.phyRegDisplayPanel);
            this.m_phyRegDisplayGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_phyRegDisplayGroupBox.Location = new System.Drawing.Point(255, 225);
            this.m_phyRegDisplayGroupBox.Name = "m_phyRegDisplayGroupBox";
            this.m_busTopologyLayout.SetRowSpan(this.m_phyRegDisplayGroupBox, 3);
            this.m_phyRegDisplayGroupBox.Size = new System.Drawing.Size(373, 310);
            this.m_phyRegDisplayGroupBox.TabIndex = 3;
            this.m_phyRegDisplayGroupBox.TabStop = false;
            this.m_phyRegDisplayGroupBox.Text = "Phy Register Display";
            this.m_phyRegDisplayGroupBox.Visible = false;
            // 
            // phyRegDisplayPanel
            // 
            this.phyRegDisplayPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.phyRegDisplayPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.phyRegDisplayPanel.Location = new System.Drawing.Point(3, 16);
            this.phyRegDisplayPanel.Name = "phyRegDisplayPanel";
            // 
            // phyRegDisplayPanel.Panel1
            // 
            this.phyRegDisplayPanel.Panel1.Controls.Add(this.m_nodeTreeView);
            this.phyRegDisplayPanel.Panel1.Controls.Add(this.m_phyRegNodeLabel);
            // 
            // phyRegDisplayPanel.Panel2
            // 
            this.phyRegDisplayPanel.Panel2.Controls.Add(this.m_nodeInformationDataGridView);
            this.phyRegDisplayPanel.Size = new System.Drawing.Size(364, 287);
            this.phyRegDisplayPanel.SplitterDistance = 186;
            this.phyRegDisplayPanel.TabIndex = 0;
            // 
            // m_nodeTreeView
            // 
            this.m_nodeTreeView.Location = new System.Drawing.Point(3, 19);
            this.m_nodeTreeView.Name = "m_nodeTreeView";
            this.m_nodeTreeView.Size = new System.Drawing.Size(177, 245);
            this.m_nodeTreeView.TabIndex = 0;
            this.m_nodeTreeView.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.OnNodeTreeViewMouseClick);
            // 
            // m_phyRegNodeLabel
            // 
            this.m_phyRegNodeLabel.AutoSize = true;
            this.m_phyRegNodeLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_phyRegNodeLabel.Location = new System.Drawing.Point(3, 3);
            this.m_phyRegNodeLabel.Name = "m_phyRegNodeLabel";
            this.m_phyRegNodeLabel.Size = new System.Drawing.Size(35, 13);
            this.m_phyRegNodeLabel.TabIndex = 6;
            this.m_phyRegNodeLabel.Text = "Node";
            // 
            // m_nodeInformationDataGridView
            // 
            this.m_nodeInformationDataGridView.AllowUserToAddRows = false;
            this.m_nodeInformationDataGridView.AllowUserToDeleteRows = false;
            this.m_nodeInformationDataGridView.AllowUserToResizeRows = false;
            this.m_nodeInformationDataGridView.BackgroundColor = System.Drawing.Color.White;
            this.m_nodeInformationDataGridView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.m_nodeInformationDataGridView.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.None;
            this.m_nodeInformationDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_nodeInformationDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.m_phyRegRegisterColumn,
            this.m_phyRegValueColumn});
            this.m_nodeInformationDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_nodeInformationDataGridView.Location = new System.Drawing.Point(0, 0);
            this.m_nodeInformationDataGridView.Name = "m_nodeInformationDataGridView";
            this.m_nodeInformationDataGridView.ReadOnly = true;
            this.m_nodeInformationDataGridView.RowHeadersVisible = false;
            this.m_nodeInformationDataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.m_nodeInformationDataGridView.Size = new System.Drawing.Size(172, 285);
            this.m_nodeInformationDataGridView.TabIndex = 0;
            // 
            // m_phyRegRegisterColumn
            // 
            this.m_phyRegRegisterColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.m_phyRegRegisterColumn.HeaderText = "Register";
            this.m_phyRegRegisterColumn.Name = "m_phyRegRegisterColumn";
            this.m_phyRegRegisterColumn.ReadOnly = true;
            this.m_phyRegRegisterColumn.Width = 71;
            // 
            // m_phyRegValueColumn
            // 
            this.m_phyRegValueColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.m_phyRegValueColumn.HeaderText = "Value";
            this.m_phyRegValueColumn.MinimumWidth = 40;
            this.m_phyRegValueColumn.Name = "m_phyRegValueColumn";
            this.m_phyRegValueColumn.ReadOnly = true;
            // 
            // m_nodeInfoGroupBox
            // 
            this.m_nodeInfoGroupBox.AutoSize = true;
            this.m_nodeInfoGroupBox.Controls.Add(this.m_nodeInfoTableLayoutPanel);
            this.m_nodeInfoGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_nodeInfoGroupBox.Location = new System.Drawing.Point(3, 340);
            this.m_nodeInfoGroupBox.Name = "m_nodeInfoGroupBox";
            this.m_nodeInfoGroupBox.Size = new System.Drawing.Size(246, 147);
            this.m_nodeInfoGroupBox.TabIndex = 8;
            this.m_nodeInfoGroupBox.TabStop = false;
            this.m_nodeInfoGroupBox.Text = "Node Information";
            // 
            // m_nodeInfoTableLayoutPanel
            // 
            this.m_nodeInfoTableLayoutPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nodeInfoTableLayoutPanel.ColumnCount = 2;
            this.m_nodeInfoTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_nodeInfoTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.m_nodeInfoTableLayoutPanel.Controls.Add(this.m_nodeCurrentsValue, 1, 3);
            this.m_nodeInfoTableLayoutPanel.Controls.Add(this.m_nodeCurrentsLabel, 0, 3);
            this.m_nodeInfoTableLayoutPanel.Controls.Add(this.m_nodeVoltagesValue, 1, 2);
            this.m_nodeInfoTableLayoutPanel.Controls.Add(this.m_nodeVoltageLabel, 0, 2);
            this.m_nodeInfoTableLayoutPanel.Controls.Add(this.m_nodeProductIDValue, 1, 1);
            this.m_nodeInfoTableLayoutPanel.Controls.Add(this.m_nodeProductIDLabel, 0, 1);
            this.m_nodeInfoTableLayoutPanel.Controls.Add(this.m_nodeModelValue, 1, 0);
            this.m_nodeInfoTableLayoutPanel.Controls.Add(this.m_nodeModelLabel, 0, 0);
            this.m_nodeInfoTableLayoutPanel.Location = new System.Drawing.Point(8, 16);
            this.m_nodeInfoTableLayoutPanel.Name = "m_nodeInfoTableLayoutPanel";
            this.m_nodeInfoTableLayoutPanel.RowCount = 4;
            this.m_nodeInfoTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_nodeInfoTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_nodeInfoTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_nodeInfoTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_nodeInfoTableLayoutPanel.Size = new System.Drawing.Size(230, 112);
            this.m_nodeInfoTableLayoutPanel.TabIndex = 6;
            // 
            // m_nodeCurrentsValue
            // 
            this.m_nodeCurrentsValue.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nodeCurrentsValue.Location = new System.Drawing.Point(70, 95);
            this.m_nodeCurrentsValue.Name = "m_nodeCurrentsValue";
            this.m_nodeCurrentsValue.Size = new System.Drawing.Size(157, 19);
            this.m_nodeCurrentsValue.TabIndex = 7;
            this.m_nodeCurrentsValue.Text = "N/A";
            // 
            // m_nodeCurrentsLabel
            // 
            this.m_nodeCurrentsLabel.AutoSize = true;
            this.m_nodeCurrentsLabel.Location = new System.Drawing.Point(3, 95);
            this.m_nodeCurrentsLabel.Name = "m_nodeCurrentsLabel";
            this.m_nodeCurrentsLabel.Size = new System.Drawing.Size(49, 13);
            this.m_nodeCurrentsLabel.TabIndex = 6;
            this.m_nodeCurrentsLabel.Text = "Currents:";
            // 
            // m_nodeVoltagesValue
            // 
            this.m_nodeVoltagesValue.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nodeVoltagesValue.Location = new System.Drawing.Point(70, 57);
            this.m_nodeVoltagesValue.Name = "m_nodeVoltagesValue";
            this.m_nodeVoltagesValue.Size = new System.Drawing.Size(157, 38);
            this.m_nodeVoltagesValue.TabIndex = 5;
            this.m_nodeVoltagesValue.Text = "N/A";
            this.m_nodeVoltagesValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_nodeVoltageLabel
            // 
            this.m_nodeVoltageLabel.AutoSize = true;
            this.m_nodeVoltageLabel.Dock = System.Windows.Forms.DockStyle.Left;
            this.m_nodeVoltageLabel.Location = new System.Drawing.Point(3, 57);
            this.m_nodeVoltageLabel.Name = "m_nodeVoltageLabel";
            this.m_nodeVoltageLabel.Size = new System.Drawing.Size(46, 38);
            this.m_nodeVoltageLabel.TabIndex = 4;
            this.m_nodeVoltageLabel.Text = "Voltage:";
            this.m_nodeVoltageLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_nodeProductIDValue
            // 
            this.m_nodeProductIDValue.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nodeProductIDValue.Location = new System.Drawing.Point(70, 38);
            this.m_nodeProductIDValue.Name = "m_nodeProductIDValue";
            this.m_nodeProductIDValue.Size = new System.Drawing.Size(157, 19);
            this.m_nodeProductIDValue.TabIndex = 3;
            this.m_nodeProductIDValue.Text = "N/A";
            // 
            // m_nodeProductIDLabel
            // 
            this.m_nodeProductIDLabel.AutoSize = true;
            this.m_nodeProductIDLabel.Location = new System.Drawing.Point(3, 38);
            this.m_nodeProductIDLabel.Name = "m_nodeProductIDLabel";
            this.m_nodeProductIDLabel.Size = new System.Drawing.Size(61, 13);
            this.m_nodeProductIDLabel.TabIndex = 2;
            this.m_nodeProductIDLabel.Text = "Product ID:";
            // 
            // m_nodeModelValue
            // 
            this.m_nodeModelValue.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nodeModelValue.Location = new System.Drawing.Point(70, 0);
            this.m_nodeModelValue.Name = "m_nodeModelValue";
            this.m_nodeModelValue.Size = new System.Drawing.Size(157, 38);
            this.m_nodeModelValue.TabIndex = 1;
            this.m_nodeModelValue.Text = "N/A";
            this.m_nodeModelValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_nodeModelLabel
            // 
            this.m_nodeModelLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_nodeModelLabel.Location = new System.Drawing.Point(3, 0);
            this.m_nodeModelLabel.Name = "m_nodeModelLabel";
            this.m_nodeModelLabel.Size = new System.Drawing.Size(61, 38);
            this.m_nodeModelLabel.TabIndex = 0;
            this.m_nodeModelLabel.Text = "Model:";
            this.m_nodeModelLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_imagePanel
            // 
            this.m_imagePanel.AutoScroll = true;
            this.m_busTopologyLayout.SetColumnSpan(this.m_imagePanel, 2);
            this.m_imagePanel.Controls.Add(this.m_drawingArea);
            this.m_imagePanel.Location = new System.Drawing.Point(3, 3);
            this.m_imagePanel.Name = "m_imagePanel";
            this.m_imagePanel.Size = new System.Drawing.Size(625, 181);
            this.m_imagePanel.TabIndex = 2;
            // 
            // m_drawingArea
            // 
            this.m_drawingArea.BackColor = System.Drawing.Color.White;
            this.m_drawingArea.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.m_drawingArea.Location = new System.Drawing.Point(0, 0);
            this.m_drawingArea.Name = "m_drawingArea";
            this.m_drawingArea.Size = new System.Drawing.Size(600, 178);
            this.m_drawingArea.TabIndex = 0;
            this.m_drawingArea.TabStop = false;
            this.m_drawingArea.MouseMove += new System.Windows.Forms.MouseEventHandler(this.OnDrawingAreaMouseMove);
            this.m_drawingArea.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OnDrawingAreaMousePress);
            this.m_drawingArea.Paint += new System.Windows.Forms.PaintEventHandler(this.OnTopologyGraphicPaint);
            // 
            // groupBox1
            // 
            this.groupBox1.AutoSize = true;
            this.groupBox1.Controls.Add(this.m_legendAdditionalNotesLabel);
            this.groupBox1.Controls.Add(this.m_legendCameraColor);
            this.groupBox1.Controls.Add(this.m_legendPCLabel);
            this.groupBox1.Controls.Add(this.m_legendNodeColor);
            this.groupBox1.Controls.Add(this.m_legendBusLabel);
            this.groupBox1.Controls.Add(this.m_legendBusColor);
            this.groupBox1.Controls.Add(this.m_legendNodeLabel);
            this.groupBox1.Controls.Add(this.m_legendPCColor);
            this.groupBox1.Controls.Add(this.m_legendCameraLabel);
            this.groupBox1.Location = new System.Drawing.Point(3, 225);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(243, 109);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Legend";
            // 
            // m_legendAdditionalNotesLabel
            // 
            this.m_legendAdditionalNotesLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_legendAdditionalNotesLabel.AutoSize = true;
            this.m_legendAdditionalNotesLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_legendAdditionalNotesLabel.Location = new System.Drawing.Point(8, 80);
            this.m_legendAdditionalNotesLabel.Name = "m_legendAdditionalNotesLabel";
            this.m_legendAdditionalNotesLabel.Size = new System.Drawing.Size(180, 13);
            this.m_legendAdditionalNotesLabel.TabIndex = 6;
            this.m_legendAdditionalNotesLabel.Text = "* - Selectable node on a FirePro bus";
            // 
            // m_legendCameraColor
            // 
            this.m_legendCameraColor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_legendCameraColor.BackColor = System.Drawing.SystemColors.Control;
            this.m_legendCameraColor.Location = new System.Drawing.Point(90, 64);
            this.m_legendCameraColor.Name = "m_legendCameraColor";
            this.m_legendCameraColor.Size = new System.Drawing.Size(91, 12);
            this.m_legendCameraColor.TabIndex = 7;
            // 
            // m_legendPCLabel
            // 
            this.m_legendPCLabel.AutoSize = true;
            this.m_legendPCLabel.Location = new System.Drawing.Point(8, 16);
            this.m_legendPCLabel.Name = "m_legendPCLabel";
            this.m_legendPCLabel.Size = new System.Drawing.Size(24, 13);
            this.m_legendPCLabel.TabIndex = 6;
            this.m_legendPCLabel.Text = "PC:";
            // 
            // m_legendNodeColor
            // 
            this.m_legendNodeColor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_legendNodeColor.BackColor = System.Drawing.SystemColors.Control;
            this.m_legendNodeColor.Location = new System.Drawing.Point(90, 48);
            this.m_legendNodeColor.Name = "m_legendNodeColor";
            this.m_legendNodeColor.Size = new System.Drawing.Size(91, 12);
            this.m_legendNodeColor.TabIndex = 7;
            // 
            // m_legendBusLabel
            // 
            this.m_legendBusLabel.AutoSize = true;
            this.m_legendBusLabel.Location = new System.Drawing.Point(8, 32);
            this.m_legendBusLabel.Name = "m_legendBusLabel";
            this.m_legendBusLabel.Size = new System.Drawing.Size(28, 13);
            this.m_legendBusLabel.TabIndex = 6;
            this.m_legendBusLabel.Text = "Bus:";
            // 
            // m_legendBusColor
            // 
            this.m_legendBusColor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_legendBusColor.BackColor = System.Drawing.SystemColors.Control;
            this.m_legendBusColor.Location = new System.Drawing.Point(90, 32);
            this.m_legendBusColor.Name = "m_legendBusColor";
            this.m_legendBusColor.Size = new System.Drawing.Size(91, 12);
            this.m_legendBusColor.TabIndex = 7;
            // 
            // m_legendNodeLabel
            // 
            this.m_legendNodeLabel.AutoSize = true;
            this.m_legendNodeLabel.Location = new System.Drawing.Point(8, 48);
            this.m_legendNodeLabel.Name = "m_legendNodeLabel";
            this.m_legendNodeLabel.Size = new System.Drawing.Size(36, 13);
            this.m_legendNodeLabel.TabIndex = 6;
            this.m_legendNodeLabel.Text = "Node:";
            // 
            // m_legendPCColor
            // 
            this.m_legendPCColor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_legendPCColor.BackColor = System.Drawing.SystemColors.Control;
            this.m_legendPCColor.Location = new System.Drawing.Point(90, 16);
            this.m_legendPCColor.Name = "m_legendPCColor";
            this.m_legendPCColor.Size = new System.Drawing.Size(91, 12);
            this.m_legendPCColor.TabIndex = 7;
            // 
            // m_legendCameraLabel
            // 
            this.m_legendCameraLabel.AutoSize = true;
            this.m_legendCameraLabel.Location = new System.Drawing.Point(8, 64);
            this.m_legendCameraLabel.Name = "m_legendCameraLabel";
            this.m_legendCameraLabel.Size = new System.Drawing.Size(46, 13);
            this.m_legendCameraLabel.TabIndex = 6;
            this.m_legendCameraLabel.Text = "Camera:";
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.AutoSize = true;
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.m_phyDisplayControlButton, 1, 0);
            this.tableLayoutPanel3.Controls.Add(this.m_refreshButton, 0, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 493);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.Size = new System.Drawing.Size(246, 29);
            this.tableLayoutPanel3.TabIndex = 9;
            // 
            // m_phyDisplayControlButton
            // 
            this.m_phyDisplayControlButton.Location = new System.Drawing.Point(126, 3);
            this.m_phyDisplayControlButton.Name = "m_phyDisplayControlButton";
            this.m_phyDisplayControlButton.Size = new System.Drawing.Size(112, 23);
            this.m_phyDisplayControlButton.TabIndex = 2;
            this.m_phyDisplayControlButton.Text = "Show Phy Registers";
            this.m_phyDisplayControlButton.UseVisualStyleBackColor = true;
            this.m_phyDisplayControlButton.Click += new System.EventHandler(this.OnPhyDisplayControlButton_Click);
            // 
            // m_refreshButton
            // 
            this.m_refreshButton.Location = new System.Drawing.Point(3, 3);
            this.m_refreshButton.Name = "m_refreshButton";
            this.m_refreshButton.Size = new System.Drawing.Size(112, 23);
            this.m_refreshButton.TabIndex = 1;
            this.m_refreshButton.Text = "Refresh";
            this.m_refreshButton.UseVisualStyleBackColor = true;
            this.m_refreshButton.Click += new System.EventHandler(this.OnRefreshButtonClick);
            // 
            // m_imageController
            // 
            this.m_imageController.ColumnCount = 3;
            this.m_busTopologyLayout.SetColumnSpan(this.m_imageController, 2);
            this.m_imageController.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.m_imageController.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.m_imageController.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.m_imageController.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_imageController.Controls.Add(this.m_zoomInBtn, 0, 0);
            this.m_imageController.Controls.Add(this.m_zoomOutBtn, 1, 0);
            this.m_imageController.Controls.Add(this.m_zoomResetBtn, 2, 0);
            this.m_imageController.Location = new System.Drawing.Point(3, 190);
            this.m_imageController.Name = "m_imageController";
            this.m_imageController.RowCount = 1;
            this.m_imageController.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.m_imageController.Size = new System.Drawing.Size(625, 29);
            this.m_imageController.TabIndex = 10;
            // 
            // m_zoomInBtn
            // 
            this.m_zoomInBtn.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.m_zoomInBtn.Location = new System.Drawing.Point(54, 3);
            this.m_zoomInBtn.Name = "m_zoomInBtn";
            this.m_zoomInBtn.Size = new System.Drawing.Size(100, 23);
            this.m_zoomInBtn.TabIndex = 0;
            this.m_zoomInBtn.Text = "Zoom In";
            this.m_zoomInBtn.UseVisualStyleBackColor = true;
            this.m_zoomInBtn.Click += new System.EventHandler(this.OnZoomInBtnClick);
            // 
            // m_zoomOutBtn
            // 
            this.m_zoomOutBtn.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.m_zoomOutBtn.Location = new System.Drawing.Point(262, 3);
            this.m_zoomOutBtn.Name = "m_zoomOutBtn";
            this.m_zoomOutBtn.Size = new System.Drawing.Size(100, 23);
            this.m_zoomOutBtn.TabIndex = 1;
            this.m_zoomOutBtn.Text = "Zoom Out";
            this.m_zoomOutBtn.UseVisualStyleBackColor = true;
            this.m_zoomOutBtn.Click += new System.EventHandler(this.OnZoomOutBtnClick);
            // 
            // m_zoomResetBtn
            // 
            this.m_zoomResetBtn.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.m_zoomResetBtn.Location = new System.Drawing.Point(470, 3);
            this.m_zoomResetBtn.Name = "m_zoomResetBtn";
            this.m_zoomResetBtn.Size = new System.Drawing.Size(100, 23);
            this.m_zoomResetBtn.TabIndex = 2;
            this.m_zoomResetBtn.Text = "Reset";
            this.m_zoomResetBtn.UseVisualStyleBackColor = true;
            this.m_zoomResetBtn.Click += new System.EventHandler(this.OnZoomResetBtnClick);
            // 
            // BusTopologyPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "BusTopologyPage";
            this.Size = new System.Drawing.Size(640, 560);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_mainGroupBox.PerformLayout();
            this.m_busTopologyLayout.ResumeLayout(false);
            this.m_busTopologyLayout.PerformLayout();
            this.m_phyRegDisplayGroupBox.ResumeLayout(false);
            this.phyRegDisplayPanel.Panel1.ResumeLayout(false);
            this.phyRegDisplayPanel.Panel1.PerformLayout();
            this.phyRegDisplayPanel.Panel2.ResumeLayout(false);
            this.phyRegDisplayPanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_nodeInformationDataGridView)).EndInit();
            this.m_nodeInfoGroupBox.ResumeLayout(false);
            this.m_nodeInfoTableLayoutPanel.ResumeLayout(false);
            this.m_nodeInfoTableLayoutPanel.PerformLayout();
            this.m_imagePanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_drawingArea)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.m_imageController.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.PictureBox m_drawingArea;
        private System.Windows.Forms.Label m_legendAdditionalNotesLabel;
        private System.Windows.Forms.Label m_legendCameraLabel;
        private System.Windows.Forms.Label m_legendNodeLabel;
        private System.Windows.Forms.Label m_legendBusLabel;
        private System.Windows.Forms.Label m_legendPCLabel;
        private System.Windows.Forms.Panel m_legendCameraColor;
        private System.Windows.Forms.Panel m_legendNodeColor;
        private System.Windows.Forms.Panel m_legendBusColor;
        private System.Windows.Forms.Panel m_legendPCColor;
        private System.Windows.Forms.TableLayoutPanel m_nodeInfoTableLayoutPanel;
        private System.Windows.Forms.Label m_nodeCurrentsValue;
        private System.Windows.Forms.Label m_nodeCurrentsLabel;
        private System.Windows.Forms.Label m_nodeVoltagesValue;
        private System.Windows.Forms.Label m_nodeVoltageLabel;
        private System.Windows.Forms.Label m_nodeProductIDValue;
        private System.Windows.Forms.Label m_nodeProductIDLabel;
        private System.Windows.Forms.Label m_nodeModelValue;
        private System.Windows.Forms.Label m_nodeModelLabel;
        private System.Windows.Forms.Button m_phyDisplayControlButton;
        private System.Windows.Forms.Button m_refreshButton;
        private System.Windows.Forms.GroupBox m_phyRegDisplayGroupBox;
        private System.Windows.Forms.SplitContainer phyRegDisplayPanel;
        private System.Windows.Forms.Label m_phyRegNodeLabel;
        private System.Windows.Forms.TreeView m_nodeTreeView;
        private System.Windows.Forms.DataGridView m_nodeInformationDataGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_phyRegRegisterColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_phyRegValueColumn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox m_nodeInfoGroupBox;
        private System.Windows.Forms.TableLayoutPanel m_busTopologyLayout;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.ToolTip cameraInfoToolTip;
        private System.Windows.Forms.TableLayoutPanel m_imageController;
        private System.Windows.Forms.Button m_zoomInBtn;
        private System.Windows.Forms.Button m_zoomOutBtn;
        private System.Windows.Forms.Panel m_imagePanel;
        private System.Windows.Forms.Button m_zoomResetBtn;
    }
}
