namespace FlyCap2CameraControl
{
    partial class SystemInfoPage
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
            this.m_copyButton = new System.Windows.Forms.Button();
            this.m_basicInfoLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_numOfCpuCoresLabel = new System.Windows.Forms.Label();
            this.m_cpuValue = new System.Windows.Forms.Label();
            this.m_cpuLabel = new System.Windows.Forms.Label();
            this.m_memorySizeLabel = new System.Windows.Forms.Label();
            this.m_byteOrderLabel = new System.Windows.Forms.Label();
            this.m_osLabel = new System.Windows.Forms.Label();
            this.m_gpuLabel = new System.Windows.Forms.Label();
            this.m_resolutionLabel = new System.Windows.Forms.Label();
            this.m_numOfCpuCoresValue = new System.Windows.Forms.Label();
            this.m_memorySizeValue = new System.Windows.Forms.Label();
            this.m_byteOrderValue = new System.Windows.Forms.Label();
            this.m_osValue = new System.Windows.Forms.Label();
            this.m_gpuValue = new System.Windows.Forms.Label();
            this.m_resolutionValue = new System.Windows.Forms.Label();
            this.m_mainGroupBox.SuspendLayout();
            this.m_basicInfoLayoutPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_copyButton);
            this.m_mainGroupBox.Controls.Add(this.m_basicInfoLayoutPanel);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(471, 435);
            this.m_mainGroupBox.TabIndex = 5;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "System Information";
            // 
            // m_copyButton
            // 
            this.m_copyButton.Location = new System.Drawing.Point(17, 175);
            this.m_copyButton.Name = "m_copyButton";
            this.m_copyButton.Size = new System.Drawing.Size(104, 23);
            this.m_copyButton.TabIndex = 1;
            this.m_copyButton.Text = "Copy to Clipboard";
            this.m_copyButton.UseVisualStyleBackColor = true;
            this.m_copyButton.Click += new System.EventHandler(this.OnCopyButtonClick);
            // 
            // m_basicInfoLayoutPanel
            // 
            this.m_basicInfoLayoutPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_basicInfoLayoutPanel.AutoSize = true;
            this.m_basicInfoLayoutPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_basicInfoLayoutPanel.ColumnCount = 2;
            this.m_basicInfoLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_basicInfoLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_numOfCpuCoresLabel, 0, 1);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_cpuValue, 1, 0);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_cpuLabel, 0, 0);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_memorySizeLabel, 0, 2);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_byteOrderLabel, 0, 3);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_osLabel, 0, 4);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_gpuLabel, 0, 5);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_resolutionLabel, 0, 6);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_numOfCpuCoresValue, 1, 1);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_memorySizeValue, 1, 2);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_byteOrderValue, 1, 3);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_osValue, 1, 4);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_gpuValue, 1, 5);
            this.m_basicInfoLayoutPanel.Controls.Add(this.m_resolutionValue, 1, 6);
            this.m_basicInfoLayoutPanel.Location = new System.Drawing.Point(18, 30);
            this.m_basicInfoLayoutPanel.Name = "m_basicInfoLayoutPanel";
            this.m_basicInfoLayoutPanel.RowCount = 7;
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_basicInfoLayoutPanel.Size = new System.Drawing.Size(193, 140);
            this.m_basicInfoLayoutPanel.TabIndex = 7;
            // 
            // m_numOfCpuCoresLabel
            // 
            this.m_numOfCpuCoresLabel.AutoSize = true;
            this.m_numOfCpuCoresLabel.Location = new System.Drawing.Point(3, 20);
            this.m_numOfCpuCoresLabel.Name = "m_numOfCpuCoresLabel";
            this.m_numOfCpuCoresLabel.Size = new System.Drawing.Size(113, 13);
            this.m_numOfCpuCoresLabel.TabIndex = 1;
            this.m_numOfCpuCoresLabel.Text = "Number of CPU cores:";
            // 
            // m_cpuValue
            // 
            this.m_cpuValue.AutoSize = true;
            this.m_cpuValue.Location = new System.Drawing.Point(122, 0);
            this.m_cpuValue.Name = "m_cpuValue";
            this.m_cpuValue.Size = new System.Drawing.Size(53, 13);
            this.m_cpuValue.TabIndex = 2;
            this.m_cpuValue.Text = "Unknown";
            // 
            // m_CpuLabel
            // 
            this.m_cpuLabel.AutoSize = true;
            this.m_cpuLabel.Location = new System.Drawing.Point(3, 0);
            this.m_cpuLabel.Name = "m_CpuLabel";
            this.m_cpuLabel.Size = new System.Drawing.Size(32, 13);
            this.m_cpuLabel.TabIndex = 0;
            this.m_cpuLabel.Text = "CPU:";
            // 
            // m_memorySizeLabel
            // 
            this.m_memorySizeLabel.AutoSize = true;
            this.m_memorySizeLabel.Location = new System.Drawing.Point(3, 40);
            this.m_memorySizeLabel.Name = "m_memorySizeLabel";
            this.m_memorySizeLabel.Size = new System.Drawing.Size(92, 13);
            this.m_memorySizeLabel.TabIndex = 0;
            this.m_memorySizeLabel.Text = "Available memory:";
            // 
            // m_byteOrderLabel
            // 
            this.m_byteOrderLabel.AutoSize = true;
            this.m_byteOrderLabel.Location = new System.Drawing.Point(3, 60);
            this.m_byteOrderLabel.Name = "m_byteOrderLabel";
            this.m_byteOrderLabel.Size = new System.Drawing.Size(58, 13);
            this.m_byteOrderLabel.TabIndex = 0;
            this.m_byteOrderLabel.Text = "Byte order:";
            // 
            // m_osLabel
            // 
            this.m_osLabel.AutoSize = true;
            this.m_osLabel.Location = new System.Drawing.Point(3, 80);
            this.m_osLabel.Name = "m_osLabel";
            this.m_osLabel.Size = new System.Drawing.Size(91, 13);
            this.m_osLabel.TabIndex = 0;
            this.m_osLabel.Text = "Operating system:";
            // 
            // m_gpuLabel
            // 
            this.m_gpuLabel.AutoSize = true;
            this.m_gpuLabel.Location = new System.Drawing.Point(3, 100);
            this.m_gpuLabel.Name = "m_gpuLabel";
            this.m_gpuLabel.Size = new System.Drawing.Size(84, 13);
            this.m_gpuLabel.TabIndex = 0;
            this.m_gpuLabel.Text = "Graphic chipset:";
            // 
            // m_resulutionLabel
            // 
            this.m_resolutionLabel.AutoSize = true;
            this.m_resolutionLabel.Location = new System.Drawing.Point(3, 120);
            this.m_resolutionLabel.Name = "m_resulutionLabel";
            this.m_resolutionLabel.Size = new System.Drawing.Size(92, 13);
            this.m_resolutionLabel.TabIndex = 0;
            this.m_resolutionLabel.Text = "Screen resolution:";
            // 
            // m_numOfCpuCoresValue
            // 
            this.m_numOfCpuCoresValue.AutoSize = true;
            this.m_numOfCpuCoresValue.Location = new System.Drawing.Point(122, 20);
            this.m_numOfCpuCoresValue.Name = "m_numOfCpuCoresValue";
            this.m_numOfCpuCoresValue.Size = new System.Drawing.Size(53, 13);
            this.m_numOfCpuCoresValue.TabIndex = 2;
            this.m_numOfCpuCoresValue.Text = "Unknown";
            // 
            // m_memorySizeValue
            // 
            this.m_memorySizeValue.AutoSize = true;
            this.m_memorySizeValue.Location = new System.Drawing.Point(122, 40);
            this.m_memorySizeValue.Name = "m_memorySizeValue";
            this.m_memorySizeValue.Size = new System.Drawing.Size(53, 13);
            this.m_memorySizeValue.TabIndex = 2;
            this.m_memorySizeValue.Text = "Unknown";
            // 
            // m_byteOrderValue
            // 
            this.m_byteOrderValue.AutoSize = true;
            this.m_byteOrderValue.Location = new System.Drawing.Point(122, 60);
            this.m_byteOrderValue.Name = "m_byteOrderValue";
            this.m_byteOrderValue.Size = new System.Drawing.Size(53, 13);
            this.m_byteOrderValue.TabIndex = 2;
            this.m_byteOrderValue.Text = "Unknown";
            // 
            // m_osValue
            // 
            this.m_osValue.AutoSize = true;
            this.m_osValue.Location = new System.Drawing.Point(122, 80);
            this.m_osValue.Name = "m_osValue";
            this.m_osValue.Size = new System.Drawing.Size(53, 13);
            this.m_osValue.TabIndex = 2;
            this.m_osValue.Text = "Unknown";
            // 
            // m_gpuValue
            // 
            this.m_gpuValue.AutoSize = true;
            this.m_gpuValue.Location = new System.Drawing.Point(122, 100);
            this.m_gpuValue.Name = "m_gpuValue";
            this.m_gpuValue.Size = new System.Drawing.Size(68, 13);
            this.m_gpuValue.TabIndex = 2;
            this.m_gpuValue.Text = "Unsupported";
            // 
            // m_resolutionValue
            // 
            this.m_resolutionValue.AutoSize = true;
            this.m_resolutionValue.Location = new System.Drawing.Point(122, 120);
            this.m_resolutionValue.Name = "m_resolutionValue";
            this.m_resolutionValue.Size = new System.Drawing.Size(53, 13);
            this.m_resolutionValue.TabIndex = 2;
            this.m_resolutionValue.Text = "Unknown";
            // 
            // SystemInfoPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "SystemInfoPage";
            this.Size = new System.Drawing.Size(474, 438);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_mainGroupBox.PerformLayout();
            this.m_basicInfoLayoutPanel.ResumeLayout(false);
            this.m_basicInfoLayoutPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.Button m_copyButton;
        private System.Windows.Forms.TableLayoutPanel m_basicInfoLayoutPanel;
        private System.Windows.Forms.Label m_numOfCpuCoresLabel;
        private System.Windows.Forms.Label m_cpuValue;
        private System.Windows.Forms.Label m_cpuLabel;
        private System.Windows.Forms.Label m_memorySizeLabel;
        private System.Windows.Forms.Label m_byteOrderLabel;
        private System.Windows.Forms.Label m_osLabel;
        private System.Windows.Forms.Label m_gpuLabel;
        private System.Windows.Forms.Label m_resolutionLabel;
        private System.Windows.Forms.Label m_numOfCpuCoresValue;
        private System.Windows.Forms.Label m_memorySizeValue;
        private System.Windows.Forms.Label m_byteOrderValue;
        private System.Windows.Forms.Label m_osValue;
        private System.Windows.Forms.Label m_gpuValue;
        private System.Windows.Forms.Label m_resolutionValue;
    }
}
