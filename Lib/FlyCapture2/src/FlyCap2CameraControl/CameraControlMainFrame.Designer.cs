namespace FlyCap2CameraControl
{
    partial class CameraControlMainFrame
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CameraControlMainFrame));
            this.m_mainTabControl = new System.Windows.Forms.TabControl();
            this.m_cameraSettingsTabPage = new System.Windows.Forms.TabPage();
            this.m_standardVideoModesTabPage = new System.Windows.Forms.TabPage();
            this.m_customVideoModesTabPage = new System.Windows.Forms.TabPage();
            this.m_cameraInfoTabPage = new System.Windows.Forms.TabPage();
            this.m_cameraRegistersTabPage = new System.Windows.Forms.TabPage();
            this.m_gPIOTabPage = new System.Windows.Forms.TabPage();
            this.m_advSettingsTabPage = new System.Windows.Forms.TabPage();
            this.m_hDRangeTabPage = new System.Windows.Forms.TabPage();
            this.m_lookUpTableTabPage = new System.Windows.Forms.TabPage();
            this.m_frameBufferTabPage = new System.Windows.Forms.TabPage();
            this.m_dataFlashTabPage = new System.Windows.Forms.TabPage();
            this.m_systemInfoTabPage = new System.Windows.Forms.TabPage();
            this.m_busTopologyTabPage = new System.Windows.Forms.TabPage();
            this.m_helpSupportTabPage = new System.Windows.Forms.TabPage();
            this.m_ladyBugTabPage = new System.Windows.Forms.TabPage();
            this.m_mainTabControl.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainTabControl
            // 
            this.m_mainTabControl.Alignment = System.Windows.Forms.TabAlignment.Left;
            this.m_mainTabControl.Controls.Add(this.m_cameraSettingsTabPage);
            this.m_mainTabControl.Controls.Add(this.m_standardVideoModesTabPage);
            this.m_mainTabControl.Controls.Add(this.m_customVideoModesTabPage);
            this.m_mainTabControl.Controls.Add(this.m_cameraInfoTabPage);
            this.m_mainTabControl.Controls.Add(this.m_cameraRegistersTabPage);
            this.m_mainTabControl.Controls.Add(this.m_gPIOTabPage);
            this.m_mainTabControl.Controls.Add(this.m_advSettingsTabPage);
            this.m_mainTabControl.Controls.Add(this.m_hDRangeTabPage);
            this.m_mainTabControl.Controls.Add(this.m_lookUpTableTabPage);
            this.m_mainTabControl.Controls.Add(this.m_frameBufferTabPage);
            this.m_mainTabControl.Controls.Add(this.m_dataFlashTabPage);
            this.m_mainTabControl.Controls.Add(this.m_systemInfoTabPage);
            this.m_mainTabControl.Controls.Add(this.m_busTopologyTabPage);
            this.m_mainTabControl.Controls.Add(this.m_helpSupportTabPage);
            this.m_mainTabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_mainTabControl.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.m_mainTabControl.ItemSize = new System.Drawing.Size(25, 150);
            this.m_mainTabControl.Location = new System.Drawing.Point(0, 0);
            this.m_mainTabControl.Multiline = true;
            this.m_mainTabControl.Name = "m_mainTabControl";
            this.m_mainTabControl.Padding = new System.Drawing.Point(3, 6);
            this.m_mainTabControl.SelectedIndex = 0;
            this.m_mainTabControl.Size = new System.Drawing.Size(792, 596);
            this.m_mainTabControl.SizeMode = System.Windows.Forms.TabSizeMode.Fixed;
            this.m_mainTabControl.TabIndex = 0;
            this.m_mainTabControl.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.OnMainTabControlDrawItem);
            this.m_mainTabControl.SelectedIndexChanged += new System.EventHandler(this.OnMainTabControlSelectedIndexChanged);
            // 
            // m_cameraSettingsTabPage
            // 
            this.m_cameraSettingsTabPage.BackColor = System.Drawing.Color.White;
            this.m_cameraSettingsTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_cameraSettingsTabPage.Name = "m_cameraSettingsTabPage";
            this.m_cameraSettingsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_cameraSettingsTabPage.Size = new System.Drawing.Size(634, 588);
            this.m_cameraSettingsTabPage.TabIndex = 0;
            this.m_cameraSettingsTabPage.Text = "Camera Settings";
            // 
            // m_standardVideoModesTabPage
            // 
            this.m_standardVideoModesTabPage.BackColor = System.Drawing.Color.White;
            this.m_standardVideoModesTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_standardVideoModesTabPage.Name = "m_standardVideoModesTabPage";
            this.m_standardVideoModesTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_standardVideoModesTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_standardVideoModesTabPage.TabIndex = 1;
            this.m_standardVideoModesTabPage.Text = "Standard Video Modes";
            // 
            // m_customVideoModesTabPage
            // 
            this.m_customVideoModesTabPage.BackColor = System.Drawing.Color.White;
            this.m_customVideoModesTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_customVideoModesTabPage.Name = "m_customVideoModesTabPage";
            this.m_customVideoModesTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_customVideoModesTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_customVideoModesTabPage.TabIndex = 2;
            this.m_customVideoModesTabPage.Text = "Custom Video Modes";
            // 
            // m_cameraInfoTabPage
            // 
            this.m_cameraInfoTabPage.BackColor = System.Drawing.Color.White;
            this.m_cameraInfoTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_cameraInfoTabPage.Name = "m_cameraInfoTabPage";
            this.m_cameraInfoTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_cameraInfoTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_cameraInfoTabPage.TabIndex = 3;
            this.m_cameraInfoTabPage.Text = "Camera Information";
            // 
            // m_cameraRegistersTabPage
            // 
            this.m_cameraRegistersTabPage.BackColor = System.Drawing.Color.White;
            this.m_cameraRegistersTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_cameraRegistersTabPage.Name = "m_cameraRegistersTabPage";
            this.m_cameraRegistersTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_cameraRegistersTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_cameraRegistersTabPage.TabIndex = 4;
            this.m_cameraRegistersTabPage.Text = "Camera Registers";
            // 
            // m_gPIOTabPage
            // 
            this.m_gPIOTabPage.BackColor = System.Drawing.Color.White;
            this.m_gPIOTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_gPIOTabPage.Name = "m_gPIOTabPage";
            this.m_gPIOTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_gPIOTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_gPIOTabPage.TabIndex = 5;
            this.m_gPIOTabPage.Text = "Trigger / Strobe";
            // 
            // m_advSettingsTabPage
            // 
            this.m_advSettingsTabPage.BackColor = System.Drawing.Color.White;
            this.m_advSettingsTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_advSettingsTabPage.Name = "m_advSettingsTabPage";
            this.m_advSettingsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_advSettingsTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_advSettingsTabPage.TabIndex = 6;
            this.m_advSettingsTabPage.Text = "Advanced Camera Settings";
            // 
            // m_hDRangeTabPage
            // 
            this.m_hDRangeTabPage.BackColor = System.Drawing.Color.White;
            this.m_hDRangeTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_hDRangeTabPage.Name = "m_hDRangeTabPage";
            this.m_hDRangeTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_hDRangeTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_hDRangeTabPage.TabIndex = 14;
            this.m_hDRangeTabPage.Text = "High Dynamic Range";
            // 
            // m_lookUpTableTabPage
            // 
            this.m_lookUpTableTabPage.BackColor = System.Drawing.Color.White;
            this.m_lookUpTableTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_lookUpTableTabPage.Name = "m_lookUpTableTabPage";
            this.m_lookUpTableTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_lookUpTableTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_lookUpTableTabPage.TabIndex = 7;
            this.m_lookUpTableTabPage.Text = "Look Up Table";
            // 
            // m_frameBufferTabPage
            // 
            this.m_frameBufferTabPage.BackColor = System.Drawing.Color.White;
            this.m_frameBufferTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_frameBufferTabPage.Name = "m_frameBufferTabPage";
            this.m_frameBufferTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_frameBufferTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_frameBufferTabPage.TabIndex = 8;
            this.m_frameBufferTabPage.Text = "Frame Buffer";
            // 
            // m_dataFlashTabPage
            // 
            this.m_dataFlashTabPage.BackColor = System.Drawing.Color.White;
            this.m_dataFlashTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_dataFlashTabPage.Name = "m_dataFlashTabPage";
            this.m_dataFlashTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_dataFlashTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_dataFlashTabPage.TabIndex = 9;
            this.m_dataFlashTabPage.Text = "Data Flash";
            // 
            // m_systemInfoTabPage
            // 
            this.m_systemInfoTabPage.BackColor = System.Drawing.Color.White;
            this.m_systemInfoTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_systemInfoTabPage.Name = "m_systemInfoTabPage";
            this.m_systemInfoTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_systemInfoTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_systemInfoTabPage.TabIndex = 10;
            this.m_systemInfoTabPage.Text = "System Information";
            // 
            // m_busTopologyTabPage
            // 
            this.m_busTopologyTabPage.BackColor = System.Drawing.Color.White;
            this.m_busTopologyTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_busTopologyTabPage.Name = "m_busTopologyTabPage";
            this.m_busTopologyTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_busTopologyTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_busTopologyTabPage.TabIndex = 11;
            this.m_busTopologyTabPage.Text = "Bus Topology";
            // 
            // m_helpSupportTabPage
            // 
            this.m_helpSupportTabPage.BackColor = System.Drawing.Color.White;
            this.m_helpSupportTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_helpSupportTabPage.Name = "m_helpSupportTabPage";
            this.m_helpSupportTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_helpSupportTabPage.Size = new System.Drawing.Size(636, 590);
            this.m_helpSupportTabPage.TabIndex = 12;
            this.m_helpSupportTabPage.Text = "Help / Support";
            // 
            // m_ladyBugTabPage
            // 
            this.m_ladyBugTabPage.BackColor = System.Drawing.Color.White;
            this.m_ladyBugTabPage.Location = new System.Drawing.Point(154, 4);
            this.m_ladyBugTabPage.Name = "m_ladyBugTabPage";
            this.m_ladyBugTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.m_ladyBugTabPage.Size = new System.Drawing.Size(634, 588);
            this.m_ladyBugTabPage.TabIndex = 13;
            this.m_ladyBugTabPage.Text = "Ladybug Settings";
            // 
            // CameraControlMainFrame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(792, 596);
            this.Controls.Add(this.m_mainTabControl);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(800, 630);
            this.Name = "CameraControlMainFrame";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "CameraControlDialog";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.OnCameraControlMainFrameFormClosed);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.OnCameraControlFormClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.CameraControlMainFrame_KeyDown);
            this.m_mainTabControl.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl m_mainTabControl;
        private System.Windows.Forms.TabPage m_cameraSettingsTabPage;
        private System.Windows.Forms.TabPage m_standardVideoModesTabPage;
        private System.Windows.Forms.TabPage m_customVideoModesTabPage;
        private System.Windows.Forms.TabPage m_cameraInfoTabPage;
        private System.Windows.Forms.TabPage m_cameraRegistersTabPage;
        private System.Windows.Forms.TabPage m_gPIOTabPage;
        private System.Windows.Forms.TabPage m_advSettingsTabPage;
        private System.Windows.Forms.TabPage m_lookUpTableTabPage;
        private System.Windows.Forms.TabPage m_frameBufferTabPage;
        private System.Windows.Forms.TabPage m_dataFlashTabPage;
        private System.Windows.Forms.TabPage m_systemInfoTabPage;
        private System.Windows.Forms.TabPage m_busTopologyTabPage;
        private System.Windows.Forms.TabPage m_helpSupportTabPage;
        private System.Windows.Forms.TabPage m_ladyBugTabPage;
        private System.Windows.Forms.TabPage m_hDRangeTabPage;

    }
}