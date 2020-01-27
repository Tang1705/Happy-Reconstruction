namespace FlyCap2CameraControl
{
    partial class CameraSelectionWindow
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CameraSelectionWindow));
            this.m_cameraListLabel = new System.Windows.Forms.Label();
            this.m_cameraDataGridView = new System.Windows.Forms.DataGridView();
            this.m_SerialNumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_modelColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_interfaceColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_ipColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_cameraInfoLabel = new System.Windows.Forms.Label();
            this.m_cameraInfoDisplayPanel = new System.Windows.Forms.Panel();
            this.m_gigeInfoLabel = new System.Windows.Forms.Label();
            this.m_gigeInfoDisplayPanel = new System.Windows.Forms.Panel();
            this.m_forceIpButton = new System.Windows.Forms.Button();
            this.m_refreshButton = new System.Windows.Forms.Button();
            this.m_okButton = new System.Windows.Forms.Button();
            this.m_configButton = new System.Windows.Forms.Button();
            this.m_cancelButton = new System.Windows.Forms.Button();
            this.m_cameraInfoLayout = new System.Windows.Forms.TableLayoutPanel();
            this.m_mainTableLayout = new System.Windows.Forms.TableLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.m_cameraDataGridView)).BeginInit();
            this.m_cameraInfoLayout.SuspendLayout();
            this.m_mainTableLayout.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_cameraListLabel
            // 
            this.m_cameraListLabel.AutoSize = true;
            this.m_cameraListLabel.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_cameraListLabel.Location = new System.Drawing.Point(3, 4);
            this.m_cameraListLabel.Margin = new System.Windows.Forms.Padding(3, 4, 3, 0);
            this.m_cameraListLabel.Name = "m_cameraListLabel";
            this.m_cameraListLabel.Size = new System.Drawing.Size(84, 16);
            this.m_cameraListLabel.TabIndex = 6;
            this.m_cameraListLabel.Text = "Camera List";
            // 
            // m_cameraDataGridView
            // 
            this.m_cameraDataGridView.AllowUserToAddRows = false;
            this.m_cameraDataGridView.AllowUserToDeleteRows = false;
            this.m_cameraDataGridView.AllowUserToResizeColumns = false;
            this.m_cameraDataGridView.AllowUserToResizeRows = false;
            this.m_cameraDataGridView.BackgroundColor = System.Drawing.Color.White;
            this.m_cameraDataGridView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.m_cameraDataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.m_SerialNumberColumn,
            this.m_modelColumn,
            this.m_interfaceColumn,
            this.m_ipColumn});
            this.m_cameraDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_cameraDataGridView.Location = new System.Drawing.Point(3, 23);
            this.m_cameraDataGridView.MinimumSize = new System.Drawing.Size(470, 100);
            this.m_cameraDataGridView.Name = "m_cameraDataGridView";
            this.m_cameraDataGridView.ReadOnly = true;
            this.m_cameraDataGridView.RowHeadersVisible = false;
            this.m_cameraDataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.m_cameraDataGridView.Size = new System.Drawing.Size(494, 188);
            this.m_cameraDataGridView.TabIndex = 7;
            this.m_cameraDataGridView.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.OnCameraDataGridViewDoubleClick);
            this.m_cameraDataGridView.SelectionChanged += new System.EventHandler(this.OnCameraListSelectionChanged);
            // 
            // m_SerialNumberColumn
            // 
            this.m_SerialNumberColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.m_SerialNumberColumn.HeaderText = "Serial #";
            this.m_SerialNumberColumn.Name = "m_SerialNumberColumn";
            this.m_SerialNumberColumn.ReadOnly = true;
            this.m_SerialNumberColumn.Width = 68;
            // 
            // m_modelColumn
            // 
            this.m_modelColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.m_modelColumn.HeaderText = "Model";
            this.m_modelColumn.Name = "m_modelColumn";
            this.m_modelColumn.ReadOnly = true;
            // 
            // m_interfaceColumn
            // 
            this.m_interfaceColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.m_interfaceColumn.HeaderText = "Interface";
            this.m_interfaceColumn.Name = "m_interfaceColumn";
            this.m_interfaceColumn.ReadOnly = true;
            this.m_interfaceColumn.Width = 74;
            // 
            // m_ipColumn
            // 
            this.m_ipColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.m_ipColumn.HeaderText = "IP Address";
            this.m_ipColumn.Name = "m_ipColumn";
            this.m_ipColumn.ReadOnly = true;
            this.m_ipColumn.Width = 83;
            // 
            // m_cameraInfoLabel
            // 
            this.m_cameraInfoLabel.AutoSize = true;
            this.m_cameraInfoLabel.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_cameraInfoLabel.Location = new System.Drawing.Point(3, 1);
            this.m_cameraInfoLabel.Margin = new System.Windows.Forms.Padding(3, 1, 3, 0);
            this.m_cameraInfoLabel.Name = "m_cameraInfoLabel";
            this.m_cameraInfoLabel.Size = new System.Drawing.Size(137, 16);
            this.m_cameraInfoLabel.TabIndex = 6;
            this.m_cameraInfoLabel.Text = "Camera Information";
            // 
            // m_cameraInfoDisplayPanel
            // 
            this.m_cameraInfoDisplayPanel.AutoSize = true;
            this.m_cameraInfoDisplayPanel.Location = new System.Drawing.Point(3, 20);
            this.m_cameraInfoDisplayPanel.Name = "m_cameraInfoDisplayPanel";
            this.m_cameraInfoDisplayPanel.Size = new System.Drawing.Size(0, 0);
            this.m_cameraInfoDisplayPanel.TabIndex = 8;
            // 
            // m_gigeInfoLabel
            // 
            this.m_gigeInfoLabel.AutoSize = true;
            this.m_gigeInfoLabel.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_gigeInfoLabel.Location = new System.Drawing.Point(3, 23);
            this.m_gigeInfoLabel.Name = "m_gigeInfoLabel";
            this.m_gigeInfoLabel.Size = new System.Drawing.Size(114, 16);
            this.m_gigeInfoLabel.TabIndex = 6;
            this.m_gigeInfoLabel.Text = "GigE Information";
            // 
            // m_gigeInfoDisplayPanel
            // 
            this.m_gigeInfoDisplayPanel.AutoSize = true;
            this.m_gigeInfoDisplayPanel.Location = new System.Drawing.Point(3, 42);
            this.m_gigeInfoDisplayPanel.Name = "m_gigeInfoDisplayPanel";
            this.m_gigeInfoDisplayPanel.Size = new System.Drawing.Size(0, 0);
            this.m_gigeInfoDisplayPanel.TabIndex = 8;
            // 
            // m_forceIpButton
            // 
            this.m_forceIpButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.m_forceIpButton.Location = new System.Drawing.Point(16, 216);
            this.m_forceIpButton.Name = "m_forceIpButton";
            this.m_forceIpButton.Size = new System.Drawing.Size(106, 32);
            this.m_forceIpButton.TabIndex = 9;
            this.m_forceIpButton.Text = "Force IP";
            this.m_forceIpButton.UseVisualStyleBackColor = true;
            this.m_forceIpButton.Click += new System.EventHandler(this.OnForceIpButtonClick);
            // 
            // m_refreshButton
            // 
            this.m_refreshButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.m_refreshButton.Location = new System.Drawing.Point(128, 216);
            this.m_refreshButton.Name = "m_refreshButton";
            this.m_refreshButton.Size = new System.Drawing.Size(106, 32);
            this.m_refreshButton.TabIndex = 10;
            this.m_refreshButton.Text = "Refresh";
            this.m_refreshButton.UseVisualStyleBackColor = true;
            this.m_refreshButton.Click += new System.EventHandler(this.OnRefreshButtonClick);
            // 
            // m_okButton
            // 
            this.m_okButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.m_okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.m_okButton.Location = new System.Drawing.Point(456, 216);
            this.m_okButton.Name = "m_okButton";
            this.m_okButton.Size = new System.Drawing.Size(106, 32);
            this.m_okButton.TabIndex = 11;
            this.m_okButton.Text = "OK";
            this.m_okButton.UseVisualStyleBackColor = true;
            this.m_okButton.Click += new System.EventHandler(this.OnOkButtonClick);
            // 
            // m_configButton
            // 
            this.m_configButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.m_configButton.Location = new System.Drawing.Point(568, 216);
            this.m_configButton.Name = "m_configButton";
            this.m_configButton.Size = new System.Drawing.Size(106, 32);
            this.m_configButton.TabIndex = 12;
            this.m_configButton.Text = "Configure Selected";
            this.m_configButton.UseVisualStyleBackColor = true;
            this.m_configButton.Click += new System.EventHandler(this.OnConfigurationButtonClick);
            // 
            // m_cancelButton
            // 
            this.m_cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.m_cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.m_cancelButton.Location = new System.Drawing.Point(680, 216);
            this.m_cancelButton.Name = "m_cancelButton";
            this.m_cancelButton.Size = new System.Drawing.Size(106, 32);
            this.m_cancelButton.TabIndex = 13;
            this.m_cancelButton.Text = "Cancel";
            this.m_cancelButton.UseVisualStyleBackColor = true;
            this.m_cancelButton.Click += new System.EventHandler(this.OnCancelButtonClick);
            // 
            // m_cameraInfoLayout
            // 
            this.m_cameraInfoLayout.AutoSize = true;
            this.m_cameraInfoLayout.ColumnCount = 1;
            this.m_cameraInfoLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.m_cameraInfoLayout.Controls.Add(this.m_cameraInfoLabel, 0, 0);
            this.m_cameraInfoLayout.Controls.Add(this.m_cameraInfoDisplayPanel, 0, 1);
            this.m_cameraInfoLayout.Controls.Add(this.m_gigeInfoLabel, 0, 2);
            this.m_cameraInfoLayout.Controls.Add(this.m_gigeInfoDisplayPanel, 0, 3);
            this.m_cameraInfoLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_cameraInfoLayout.Location = new System.Drawing.Point(503, 3);
            this.m_cameraInfoLayout.Name = "m_cameraInfoLayout";
            this.m_cameraInfoLayout.RowCount = 4;
            this.m_mainTableLayout.SetRowSpan(this.m_cameraInfoLayout, 2);
            this.m_cameraInfoLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_cameraInfoLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_cameraInfoLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_cameraInfoLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_cameraInfoLayout.Size = new System.Drawing.Size(294, 208);
            this.m_cameraInfoLayout.TabIndex = 10;
            // 
            // m_mainTableLayout
            // 
            this.m_mainTableLayout.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainTableLayout.ColumnCount = 2;
            this.m_mainTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.m_mainTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 300F));
            this.m_mainTableLayout.Controls.Add(this.m_cameraListLabel, 0, 0);
            this.m_mainTableLayout.Controls.Add(this.m_cameraInfoLayout, 1, 0);
            this.m_mainTableLayout.Controls.Add(this.m_cameraDataGridView, 0, 1);
            this.m_mainTableLayout.Location = new System.Drawing.Point(0, 0);
            this.m_mainTableLayout.MinimumSize = new System.Drawing.Size(800, 210);
            this.m_mainTableLayout.Name = "m_mainTableLayout";
            this.m_mainTableLayout.RowCount = 2;
            this.m_mainTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_mainTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_mainTableLayout.Size = new System.Drawing.Size(800, 210);
            this.m_mainTableLayout.TabIndex = 11;
            // 
            // CameraSelectionWindow
            // 
            this.AcceptButton = this.m_okButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.m_cancelButton;
            this.ClientSize = new System.Drawing.Size(800, 263);
            this.Controls.Add(this.m_mainTableLayout);
            this.Controls.Add(this.m_cancelButton);
            this.Controls.Add(this.m_configButton);
            this.Controls.Add(this.m_okButton);
            this.Controls.Add(this.m_refreshButton);
            this.Controls.Add(this.m_forceIpButton);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Name = "CameraSelectionWindow";
            this.Text = "FlyCapture2 Camera Selection Dialog";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.CameraSelectionWindowClosing);
            this.Shown += new System.EventHandler(this.CameraSelectionWindowShown);
            ((System.ComponentModel.ISupportInitialize)(this.m_cameraDataGridView)).EndInit();
            this.m_cameraInfoLayout.ResumeLayout(false);
            this.m_cameraInfoLayout.PerformLayout();
            this.m_mainTableLayout.ResumeLayout(false);
            this.m_mainTableLayout.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label m_cameraListLabel;
        private System.Windows.Forms.DataGridView m_cameraDataGridView;
        private System.Windows.Forms.Label m_cameraInfoLabel;
        private System.Windows.Forms.Panel m_cameraInfoDisplayPanel;
        private System.Windows.Forms.Label m_gigeInfoLabel;
        private System.Windows.Forms.Panel m_gigeInfoDisplayPanel;
        private System.Windows.Forms.Button m_forceIpButton;
        private System.Windows.Forms.Button m_refreshButton;
        private System.Windows.Forms.Button m_okButton;
        private System.Windows.Forms.Button m_configButton;
        private System.Windows.Forms.Button m_cancelButton;
        private System.Windows.Forms.TableLayoutPanel m_cameraInfoLayout;
        private System.Windows.Forms.TableLayoutPanel m_mainTableLayout;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_SerialNumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_modelColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_interfaceColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_ipColumn;
    }
}