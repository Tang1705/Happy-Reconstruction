namespace FlyCap2CameraControl
{
    partial class HDRPage
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
            this.m_hDRangeControlPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_HDRseparateLine1 = new System.Windows.Forms.Label();
            this.m_HDRseparateLine2 = new System.Windows.Forms.Label();
            this.m_HDRseparateLine3 = new System.Windows.Forms.Label();
            this.m_enableHDRCheckBox = new System.Windows.Forms.CheckBox();
            this.m_mainGroupBox.SuspendLayout();
            this.m_hDRangeControlPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_hDRangeControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_enableHDRCheckBox);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(471, 435);
            this.m_mainGroupBox.TabIndex = 3;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "High Dynamic Range";
            // 
            // m_hDRangeControlPanel
            // 
            this.m_hDRangeControlPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_hDRangeControlPanel.ColumnCount = 1;
            this.m_hDRangeControlPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.m_hDRangeControlPanel.Controls.Add(this.m_HDRseparateLine1, 0, 1);
            this.m_hDRangeControlPanel.Controls.Add(this.m_HDRseparateLine2, 0, 3);
            this.m_hDRangeControlPanel.Controls.Add(this.m_HDRseparateLine3, 0, 5);
            this.m_hDRangeControlPanel.Location = new System.Drawing.Point(7, 43);
            this.m_hDRangeControlPanel.Name = "m_hDRangeControlPanel";
            this.m_hDRangeControlPanel.RowCount = 7;
            this.m_hDRangeControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 80F));
            this.m_hDRangeControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 5F));
            this.m_hDRangeControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 80F));
            this.m_hDRangeControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 5F));
            this.m_hDRangeControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 80F));
            this.m_hDRangeControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 5F));
            this.m_hDRangeControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 80F));
            this.m_hDRangeControlPanel.Size = new System.Drawing.Size(432, 362);
            this.m_hDRangeControlPanel.TabIndex = 1;
            // 
            // m_HDRseparateLine1
            // 
            this.m_HDRseparateLine1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_HDRseparateLine1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_HDRseparateLine1.Location = new System.Drawing.Point(3, 80);
            this.m_HDRseparateLine1.Name = "m_HDRseparateLine1";
            this.m_HDRseparateLine1.Size = new System.Drawing.Size(426, 3);
            this.m_HDRseparateLine1.TabIndex = 0;
            this.m_HDRseparateLine1.Text = "Separate Line. Don\'t resize it!";
            // 
            // m_HDRseparateLine2
            // 
            this.m_HDRseparateLine2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_HDRseparateLine2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_HDRseparateLine2.Location = new System.Drawing.Point(3, 165);
            this.m_HDRseparateLine2.Name = "m_HDRseparateLine2";
            this.m_HDRseparateLine2.Size = new System.Drawing.Size(426, 3);
            this.m_HDRseparateLine2.TabIndex = 0;
            this.m_HDRseparateLine2.Text = "Separate Line. Don\'t resize it!";
            // 
            // m_HDRseparateLine3
            // 
            this.m_HDRseparateLine3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_HDRseparateLine3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_HDRseparateLine3.Location = new System.Drawing.Point(3, 250);
            this.m_HDRseparateLine3.Name = "m_HDRseparateLine3";
            this.m_HDRseparateLine3.Size = new System.Drawing.Size(426, 3);
            this.m_HDRseparateLine3.TabIndex = 0;
            this.m_HDRseparateLine3.Text = "Separate Line. Don\'t resize it!";
            // 
            // m_enableHDRCheckBox
            // 
            this.m_enableHDRCheckBox.AutoSize = true;
            this.m_enableHDRCheckBox.Location = new System.Drawing.Point(7, 20);
            this.m_enableHDRCheckBox.Name = "m_enableHDRCheckBox";
            this.m_enableHDRCheckBox.Size = new System.Drawing.Size(154, 17);
            this.m_enableHDRCheckBox.TabIndex = 0;
            this.m_enableHDRCheckBox.Text = "Enable high dynamic range";
            this.m_enableHDRCheckBox.UseVisualStyleBackColor = true;
            this.m_enableHDRCheckBox.CheckedChanged += new System.EventHandler(this.OnEnableHDRCheckedStatusChanged);
            // 
            // HDRPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "HDRPage";
            this.Size = new System.Drawing.Size(474, 438);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_mainGroupBox.PerformLayout();
            this.m_hDRangeControlPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.TableLayoutPanel m_hDRangeControlPanel;
        private System.Windows.Forms.CheckBox m_enableHDRCheckBox;
        private System.Windows.Forms.Label m_HDRseparateLine1;
        private System.Windows.Forms.Label m_HDRseparateLine2;
        private System.Windows.Forms.Label m_HDRseparateLine3;
    }
}
