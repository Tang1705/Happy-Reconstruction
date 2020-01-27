namespace FlyCap2CameraControl
{
    partial class CameraInformationPage
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
            this.m_mainGroupBox = new System.Windows.Forms.GroupBox();
            this.m_mainTableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_gigeLabel = new System.Windows.Forms.Label();
            this.m_basicLabel = new System.Windows.Forms.Label();
            this.m_advancedLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_timeSinceInitLabel = new System.Windows.Forms.Label();
            this.m_resetButton = new System.Windows.Forms.Button();
            this.m_HorizontalLineFreqLabel = new System.Windows.Forms.Label();
            this.m_timeSinceLastBusResetLabel = new System.Windows.Forms.Label();
            this.m_pixelClockFreqLabel = new System.Windows.Forms.Label();
            this.m_transmitFailuresLabel = new System.Windows.Forms.Label();
            this.m_timeSinceInit = new System.Windows.Forms.Label();
            this.m_timeSinceLastBusReset = new System.Windows.Forms.Label();
            this.m_pixelClockFreq = new System.Windows.Forms.Label();
            this.m_transmitFailures = new System.Windows.Forms.Label();
            this.m_horizontalLineFreq = new System.Windows.Forms.Label();
            this.m_advancedLabel = new System.Windows.Forms.Label();
            this.m_consoleLabel = new System.Windows.Forms.Label();
            this.m_consoleLogPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_refreshConsoleLog = new System.Windows.Forms.Button();
            this.m_consoleLogTextBox = new System.Windows.Forms.TextBox();
            this.m_copyConsoleLogButton = new System.Windows.Forms.Button();
            this.m_gigEInfoPanel = new System.Windows.Forms.Panel();
            this.m_basicInfoLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_basicInfoPanel = new System.Windows.Forms.Panel();
            this.m_mainGroupBox.SuspendLayout();
            this.m_mainTableLayoutPanel.SuspendLayout();
            this.m_advancedLayoutPanel.SuspendLayout();
            this.m_consoleLogPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_mainTableLayoutPanel);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(587, 502);
            this.m_mainGroupBox.TabIndex = 4;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Camera Information";
            // 
            // m_mainTableLayoutPanel
            // 
            this.m_mainTableLayoutPanel.ColumnCount = 2;
            this.m_mainTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_mainTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_mainTableLayoutPanel.Controls.Add(this.m_gigeLabel, 1, 0);
            this.m_mainTableLayoutPanel.Controls.Add(this.m_basicLabel, 0, 0);
            this.m_mainTableLayoutPanel.Controls.Add(this.m_advancedLayoutPanel, 0, 3);
            this.m_mainTableLayoutPanel.Controls.Add(this.m_advancedLabel, 0, 2);
            this.m_mainTableLayoutPanel.Controls.Add(this.m_consoleLabel, 1, 2);
            this.m_mainTableLayoutPanel.Controls.Add(this.m_consoleLogPanel, 1, 3);
            this.m_mainTableLayoutPanel.Controls.Add(this.m_gigEInfoPanel, 1, 1);
            this.m_mainTableLayoutPanel.Controls.Add(this.m_basicInfoPanel, 0, 1);
            this.m_mainTableLayoutPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_mainTableLayoutPanel.Location = new System.Drawing.Point(3, 16);
            this.m_mainTableLayoutPanel.Name = "m_mainTableLayoutPanel";
            this.m_mainTableLayoutPanel.RowCount = 4;
            this.m_mainTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_mainTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_mainTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_mainTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_mainTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_mainTableLayoutPanel.Size = new System.Drawing.Size(581, 483);
            this.m_mainTableLayoutPanel.TabIndex = 10;
            // 
            // m_gigeLabel
            // 
            this.m_gigeLabel.AutoSize = true;
            this.m_gigeLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_gigeLabel.Location = new System.Drawing.Point(293, 0);
            this.m_gigeLabel.Name = "m_gigeLabel";
            this.m_gigeLabel.Size = new System.Drawing.Size(31, 13);
            this.m_gigeLabel.TabIndex = 16;
            this.m_gigeLabel.Text = "GigE";
            // 
            // m_basicLabel
            // 
            this.m_basicLabel.AutoSize = true;
            this.m_basicLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_basicLabel.Location = new System.Drawing.Point(3, 0);
            this.m_basicLabel.Name = "m_basicLabel";
            this.m_basicLabel.Size = new System.Drawing.Size(36, 13);
            this.m_basicLabel.TabIndex = 13;
            this.m_basicLabel.Text = "Basic";
            // 
            // m_advancedLayoutPanel
            // 
            this.m_advancedLayoutPanel.ColumnCount = 3;
            this.m_advancedLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_advancedLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_advancedLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_advancedLayoutPanel.Controls.Add(this.m_timeSinceInitLabel, 0, 0);
            this.m_advancedLayoutPanel.Controls.Add(this.m_resetButton, 2, 2);
            this.m_advancedLayoutPanel.Controls.Add(this.m_HorizontalLineFreqLabel, 0, 4);
            this.m_advancedLayoutPanel.Controls.Add(this.m_timeSinceLastBusResetLabel, 0, 1);
            this.m_advancedLayoutPanel.Controls.Add(this.m_pixelClockFreqLabel, 0, 3);
            this.m_advancedLayoutPanel.Controls.Add(this.m_transmitFailuresLabel, 0, 2);
            this.m_advancedLayoutPanel.Controls.Add(this.m_timeSinceInit, 1, 0);
            this.m_advancedLayoutPanel.Controls.Add(this.m_timeSinceLastBusReset, 1, 1);
            this.m_advancedLayoutPanel.Controls.Add(this.m_pixelClockFreq, 1, 3);
            this.m_advancedLayoutPanel.Controls.Add(this.m_transmitFailures, 1, 2);
            this.m_advancedLayoutPanel.Controls.Add(this.m_horizontalLineFreq, 1, 4);
            this.m_advancedLayoutPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_advancedLayoutPanel.Location = new System.Drawing.Point(3, 273);
            this.m_advancedLayoutPanel.Name = "m_advancedLayoutPanel";
            this.m_advancedLayoutPanel.RowCount = 5;
            this.m_advancedLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_advancedLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_advancedLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_advancedLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_advancedLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_advancedLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_advancedLayoutPanel.Size = new System.Drawing.Size(284, 207);
            this.m_advancedLayoutPanel.TabIndex = 8;
            // 
            // m_timeSinceInitLabel
            // 
            this.m_timeSinceInitLabel.AutoSize = true;
            this.m_timeSinceInitLabel.Location = new System.Drawing.Point(3, 0);
            this.m_timeSinceInitLabel.Name = "m_timeSinceInitLabel";
            this.m_timeSinceInitLabel.Size = new System.Drawing.Size(120, 13);
            this.m_timeSinceInitLabel.TabIndex = 4;
            this.m_timeSinceInitLabel.Text = "Time since initialization: ";
            // 
            // m_resetButton
            // 
            this.m_resetButton.AutoSize = true;
            this.m_resetButton.Location = new System.Drawing.Point(168, 43);
            this.m_resetButton.Name = "m_resetButton";
            this.m_advancedLayoutPanel.SetRowSpan(this.m_resetButton, 3);
            this.m_resetButton.Size = new System.Drawing.Size(45, 23);
            this.m_resetButton.TabIndex = 2;
            this.m_resetButton.Text = "Reset";
            this.m_resetButton.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.m_resetButton.UseVisualStyleBackColor = true;
            this.m_resetButton.Click += new System.EventHandler(this.OnResetButtonClick);
            // 
            // m_HorizontalLineFreqLabel
            // 
            this.m_HorizontalLineFreqLabel.AutoSize = true;
            this.m_HorizontalLineFreqLabel.Location = new System.Drawing.Point(3, 80);
            this.m_HorizontalLineFreqLabel.Name = "m_HorizontalLineFreqLabel";
            this.m_HorizontalLineFreqLabel.Size = new System.Drawing.Size(126, 13);
            this.m_HorizontalLineFreqLabel.TabIndex = 4;
            this.m_HorizontalLineFreqLabel.Text = "Horizontal line frequency:";
            // 
            // m_timeSinceLastBusResetLabel
            // 
            this.m_timeSinceLastBusResetLabel.AutoSize = true;
            this.m_timeSinceLastBusResetLabel.Location = new System.Drawing.Point(3, 20);
            this.m_timeSinceLastBusResetLabel.Name = "m_timeSinceLastBusResetLabel";
            this.m_timeSinceLastBusResetLabel.Size = new System.Drawing.Size(126, 13);
            this.m_timeSinceLastBusResetLabel.TabIndex = 4;
            this.m_timeSinceLastBusResetLabel.Text = "Time since last bus reset:";
            // 
            // m_pixelClockFreqLabel
            // 
            this.m_pixelClockFreqLabel.AutoSize = true;
            this.m_pixelClockFreqLabel.Location = new System.Drawing.Point(3, 60);
            this.m_pixelClockFreqLabel.Name = "m_pixelClockFreqLabel";
            this.m_pixelClockFreqLabel.Size = new System.Drawing.Size(111, 13);
            this.m_pixelClockFreqLabel.TabIndex = 4;
            this.m_pixelClockFreqLabel.Text = "Pixel clock frequency:";
            // 
            // m_transmitFailuresLabel
            // 
            this.m_transmitFailuresLabel.AutoSize = true;
            this.m_transmitFailuresLabel.Location = new System.Drawing.Point(3, 40);
            this.m_transmitFailuresLabel.Name = "m_transmitFailuresLabel";
            this.m_transmitFailuresLabel.Size = new System.Drawing.Size(89, 13);
            this.m_transmitFailuresLabel.TabIndex = 4;
            this.m_transmitFailuresLabel.Text = "Transmit failures: ";
            // 
            // m_timeSinceInit
            // 
            this.m_timeSinceInit.AutoSize = true;
            this.m_timeSinceInit.Location = new System.Drawing.Point(135, 0);
            this.m_timeSinceInit.Name = "m_timeSinceInit";
            this.m_timeSinceInit.Size = new System.Drawing.Size(27, 13);
            this.m_timeSinceInit.TabIndex = 5;
            this.m_timeSinceInit.Text = "N/A";
            // 
            // m_timeSinceLastBusReset
            // 
            this.m_timeSinceLastBusReset.AutoSize = true;
            this.m_timeSinceLastBusReset.Location = new System.Drawing.Point(135, 20);
            this.m_timeSinceLastBusReset.Name = "m_timeSinceLastBusReset";
            this.m_timeSinceLastBusReset.Size = new System.Drawing.Size(27, 13);
            this.m_timeSinceLastBusReset.TabIndex = 5;
            this.m_timeSinceLastBusReset.Text = "N/A";
            // 
            // m_pixelClockFreq
            // 
            this.m_pixelClockFreq.AutoSize = true;
            this.m_pixelClockFreq.Location = new System.Drawing.Point(135, 60);
            this.m_pixelClockFreq.Name = "m_pixelClockFreq";
            this.m_pixelClockFreq.Size = new System.Drawing.Size(27, 13);
            this.m_pixelClockFreq.TabIndex = 5;
            this.m_pixelClockFreq.Text = "N/A";
            // 
            // m_transmitFailures
            // 
            this.m_transmitFailures.AutoSize = true;
            this.m_transmitFailures.Location = new System.Drawing.Point(135, 40);
            this.m_transmitFailures.Name = "m_transmitFailures";
            this.m_transmitFailures.Size = new System.Drawing.Size(27, 13);
            this.m_transmitFailures.TabIndex = 5;
            this.m_transmitFailures.Text = "N/A";
            // 
            // m_horizontalLineFreq
            // 
            this.m_horizontalLineFreq.AutoSize = true;
            this.m_horizontalLineFreq.Location = new System.Drawing.Point(135, 80);
            this.m_horizontalLineFreq.Name = "m_horizontalLineFreq";
            this.m_horizontalLineFreq.Size = new System.Drawing.Size(27, 13);
            this.m_horizontalLineFreq.TabIndex = 5;
            this.m_horizontalLineFreq.Text = "N/A";
            // 
            // m_advancedLabel
            // 
            this.m_advancedLabel.AutoSize = true;
            this.m_advancedLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_advancedLabel.Location = new System.Drawing.Point(3, 257);
            this.m_advancedLabel.Name = "m_advancedLabel";
            this.m_advancedLabel.Size = new System.Drawing.Size(63, 13);
            this.m_advancedLabel.TabIndex = 2;
            this.m_advancedLabel.Text = "Advanced";
            // 
            // m_consoleLabel
            // 
            this.m_consoleLabel.AutoSize = true;
            this.m_consoleLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_consoleLabel.Location = new System.Drawing.Point(293, 257);
            this.m_consoleLabel.Name = "m_consoleLabel";
            this.m_consoleLabel.Size = new System.Drawing.Size(74, 13);
            this.m_consoleLabel.TabIndex = 14;
            this.m_consoleLabel.Text = "Console Log";
            this.m_consoleLabel.Visible = false;
            // 
            // m_consoleLogPanel
            // 
            this.m_consoleLogPanel.ColumnCount = 2;
            this.m_consoleLogPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_consoleLogPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_consoleLogPanel.Controls.Add(this.m_refreshConsoleLog, 1, 1);
            this.m_consoleLogPanel.Controls.Add(this.m_consoleLogTextBox, 0, 0);
            this.m_consoleLogPanel.Controls.Add(this.m_copyConsoleLogButton, 0, 1);
            this.m_consoleLogPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_consoleLogPanel.Location = new System.Drawing.Point(293, 273);
            this.m_consoleLogPanel.Name = "m_consoleLogPanel";
            this.m_consoleLogPanel.RowCount = 2;
            this.m_consoleLogPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_consoleLogPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_consoleLogPanel.Size = new System.Drawing.Size(285, 207);
            this.m_consoleLogPanel.TabIndex = 15;
            // 
            // m_refreshConsoleLog
            // 
            this.m_refreshConsoleLog.AutoSize = true;
            this.m_refreshConsoleLog.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_refreshConsoleLog.Dock = System.Windows.Forms.DockStyle.Top;
            this.m_refreshConsoleLog.Location = new System.Drawing.Point(145, 102);
            this.m_refreshConsoleLog.Name = "m_refreshConsoleLog";
            this.m_refreshConsoleLog.Padding = new System.Windows.Forms.Padding(3);
            this.m_refreshConsoleLog.Size = new System.Drawing.Size(137, 29);
            this.m_refreshConsoleLog.TabIndex = 0;
            this.m_refreshConsoleLog.TabStop = false;
            this.m_refreshConsoleLog.Text = "Refresh";
            this.m_refreshConsoleLog.UseVisualStyleBackColor = true;
            this.m_refreshConsoleLog.Visible = false;
            this.m_refreshConsoleLog.Click += new System.EventHandler(this.OnRefreshConsoleLogButtonClick);
            // 
            // m_consoleLogTextBox
            // 
            this.m_consoleLogTextBox.BackColor = System.Drawing.Color.White;
            this.m_consoleLogPanel.SetColumnSpan(this.m_consoleLogTextBox, 2);
            this.m_consoleLogTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_consoleLogTextBox.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_consoleLogTextBox.Location = new System.Drawing.Point(3, 3);
            this.m_consoleLogTextBox.Multiline = true;
            this.m_consoleLogTextBox.Name = "m_consoleLogTextBox";
            this.m_consoleLogTextBox.ReadOnly = true;
            this.m_consoleLogTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.m_consoleLogTextBox.Size = new System.Drawing.Size(279, 93);
            this.m_consoleLogTextBox.TabIndex = 2;
            this.m_consoleLogTextBox.TabStop = false;
            this.m_consoleLogTextBox.Visible = false;
            // 
            // m_copyConsoleLogButton
            // 
            this.m_copyConsoleLogButton.AutoSize = true;
            this.m_copyConsoleLogButton.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_copyConsoleLogButton.Dock = System.Windows.Forms.DockStyle.Top;
            this.m_copyConsoleLogButton.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.m_copyConsoleLogButton.Location = new System.Drawing.Point(3, 102);
            this.m_copyConsoleLogButton.Name = "m_copyConsoleLogButton";
            this.m_copyConsoleLogButton.Padding = new System.Windows.Forms.Padding(3);
            this.m_copyConsoleLogButton.Size = new System.Drawing.Size(136, 29);
            this.m_copyConsoleLogButton.TabIndex = 1;
            this.m_copyConsoleLogButton.TabStop = false;
            this.m_copyConsoleLogButton.Text = "Copy to Clipboard";
            this.m_copyConsoleLogButton.UseVisualStyleBackColor = true;
            this.m_copyConsoleLogButton.Visible = false;
            this.m_copyConsoleLogButton.Click += new System.EventHandler(this.OnCopyConsoleLogButtonClick);
            // 
            // m_gigEInfoPanel
            // 
            this.m_gigEInfoPanel.Location = new System.Drawing.Point(293, 16);
            this.m_gigEInfoPanel.Name = "m_gigEInfoPanel";
            this.m_gigEInfoPanel.Size = new System.Drawing.Size(283, 238);
            this.m_gigEInfoPanel.TabIndex = 19;
            // 
            // m_basicInfoLayoutPanel
            // 
            this.m_basicInfoLayoutPanel.ColumnCount = 2;
            this.m_basicInfoLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_basicInfoLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_basicInfoLayoutPanel.Location = new System.Drawing.Point(0, 0);
            this.m_basicInfoLayoutPanel.Name = "m_basicInfoLayoutPanel";
            this.m_basicInfoLayoutPanel.RowCount = 2;
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.Size = new System.Drawing.Size(200, 100);
            this.m_basicInfoLayoutPanel.TabIndex = 0;
            // 
            // m_basicInfoPanel
            // 
            this.m_basicInfoPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_basicInfoPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_basicInfoPanel.Location = new System.Drawing.Point(3, 16);
            this.m_basicInfoPanel.Name = "m_basicInfoPanel";
            this.m_basicInfoPanel.Size = new System.Drawing.Size(284, 238);
            this.m_basicInfoPanel.TabIndex = 20;
            // 
            // CameraInformationPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "CameraInformationPage";
            this.Size = new System.Drawing.Size(590, 505);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_mainTableLayoutPanel.ResumeLayout(false);
            this.m_mainTableLayoutPanel.PerformLayout();
            this.m_advancedLayoutPanel.ResumeLayout(false);
            this.m_advancedLayoutPanel.PerformLayout();
            this.m_consoleLogPanel.ResumeLayout(false);
            this.m_consoleLogPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.Label m_advancedLabel;
        private System.Windows.Forms.Label m_HorizontalLineFreqLabel;
        private System.Windows.Forms.Label m_pixelClockFreqLabel;
        private System.Windows.Forms.Label m_transmitFailuresLabel;
        private System.Windows.Forms.Label m_timeSinceLastBusResetLabel;
        private System.Windows.Forms.Label m_timeSinceInitLabel;
        private System.Windows.Forms.Button m_copyConsoleLogButton;
        private System.Windows.Forms.TableLayoutPanel m_advancedLayoutPanel;
        private System.Windows.Forms.Label m_timeSinceInit;
        private System.Windows.Forms.Label m_timeSinceLastBusReset;
        private System.Windows.Forms.Label m_pixelClockFreq;
        private System.Windows.Forms.Label m_transmitFailures;
        private System.Windows.Forms.Label m_horizontalLineFreq;
        private System.Windows.Forms.Button m_resetButton;
        private System.Windows.Forms.Button m_refreshConsoleLog;
        private System.Windows.Forms.TextBox m_consoleLogTextBox;        
        private System.Windows.Forms.TableLayoutPanel m_basicInfoLayoutPanel;

        private System.Windows.Forms.TableLayoutPanel m_mainTableLayoutPanel;
        private System.Windows.Forms.Label m_basicLabel;
        private System.Windows.Forms.TableLayoutPanel m_consoleLogPanel;
        private System.Windows.Forms.Label m_gigeLabel;
        private System.Windows.Forms.Label m_consoleLabel;
        private System.Windows.Forms.Panel m_gigEInfoPanel;
        private System.Windows.Forms.Panel m_basicInfoPanel;
    }
}
