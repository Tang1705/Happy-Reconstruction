namespace FlyCap2CameraControl
{
    partial class FrameBufferPage
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
            this.m_frameBufferInfoSplitContainer = new System.Windows.Forms.SplitContainer();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.m_bufferUsedValue = new System.Windows.Forms.Label();
            this.m_bufferUsedLabel = new System.Windows.Forms.Label();
            this.m_totalBufferValue = new System.Windows.Forms.Label();
            this.m_totalBufferLabel = new System.Windows.Forms.Label();
            this.m_frameBufferTypeValue = new System.Windows.Forms.Label();
            this.m_frameBufferTypeLabel = new System.Windows.Forms.Label();
            this.m_frameBufferAdditionalNotesLabel = new System.Windows.Forms.Label();
            this.m_imageSelectionControlPanel = new System.Windows.Forms.Panel();
            this.m_currentSelectedImageValue = new System.Windows.Forms.Label();
            this.m_imageSelectionAdditionalNotesLabel = new System.Windows.Forms.Label();
            this.m_trackBarLabel = new System.Windows.Forms.Label();
            this.m_currentSelectedImageTrackbar = new System.Windows.Forms.TrackBar();
            this.m_transmitLastImageButton = new System.Windows.Forms.Button();
            this.m_transmitSelectedImageButton = new System.Windows.Forms.Button();
            this.m_enableImageHoldCheckBox = new System.Windows.Forms.CheckBox();
            this.m_imageSelectionLabel = new System.Windows.Forms.Label();
            this.m_mainGroupBox.SuspendLayout();
            this.m_frameBufferInfoSplitContainer.Panel1.SuspendLayout();
            this.m_frameBufferInfoSplitContainer.Panel2.SuspendLayout();
            this.m_frameBufferInfoSplitContainer.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.m_imageSelectionControlPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_currentSelectedImageTrackbar)).BeginInit();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_frameBufferInfoSplitContainer);
            this.m_mainGroupBox.Controls.Add(this.m_imageSelectionControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_enableImageHoldCheckBox);
            this.m_mainGroupBox.Controls.Add(this.m_imageSelectionLabel);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(471, 435);
            this.m_mainGroupBox.TabIndex = 5;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Frame Buffer";
            // 
            // m_frameBufferInfoSplitContainer
            // 
            this.m_frameBufferInfoSplitContainer.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_frameBufferInfoSplitContainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.m_frameBufferInfoSplitContainer.IsSplitterFixed = true;
            this.m_frameBufferInfoSplitContainer.Location = new System.Drawing.Point(28, 43);
            this.m_frameBufferInfoSplitContainer.Name = "m_frameBufferInfoSplitContainer";
            // 
            // m_frameBufferInfoSplitContainer.Panel1
            // 
            this.m_frameBufferInfoSplitContainer.Panel1.Controls.Add(this.tableLayoutPanel1);
            // 
            // m_frameBufferInfoSplitContainer.Panel2
            // 
            this.m_frameBufferInfoSplitContainer.Panel2.Controls.Add(this.m_frameBufferAdditionalNotesLabel);
            this.m_frameBufferInfoSplitContainer.Size = new System.Drawing.Size(402, 135);
            this.m_frameBufferInfoSplitContainer.SplitterDistance = 207;
            this.m_frameBufferInfoSplitContainer.TabIndex = 9;
            this.m_frameBufferInfoSplitContainer.TabStop = false;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 51.20773F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 48.79227F));
            this.tableLayoutPanel1.Controls.Add(this.m_bufferUsedValue, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_bufferUsedLabel, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.m_totalBufferValue, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_totalBufferLabel, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_frameBufferTypeValue, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_frameBufferTypeLabel, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 34F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(207, 135);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // m_bufferUsedValue
            // 
            this.m_bufferUsedValue.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_bufferUsedValue.Location = new System.Drawing.Point(108, 89);
            this.m_bufferUsedValue.Name = "m_bufferUsedValue";
            this.m_bufferUsedValue.Size = new System.Drawing.Size(96, 46);
            this.m_bufferUsedValue.TabIndex = 5;
            this.m_bufferUsedValue.Text = "0";
            this.m_bufferUsedValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_bufferUsedLabel
            // 
            this.m_bufferUsedLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_bufferUsedLabel.Location = new System.Drawing.Point(3, 89);
            this.m_bufferUsedLabel.Name = "m_bufferUsedLabel";
            this.m_bufferUsedLabel.Size = new System.Drawing.Size(99, 46);
            this.m_bufferUsedLabel.TabIndex = 4;
            this.m_bufferUsedLabel.Text = "Buffers used:";
            this.m_bufferUsedLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_totalBufferValue
            // 
            this.m_totalBufferValue.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_totalBufferValue.Location = new System.Drawing.Point(108, 45);
            this.m_totalBufferValue.Name = "m_totalBufferValue";
            this.m_totalBufferValue.Size = new System.Drawing.Size(96, 44);
            this.m_totalBufferValue.TabIndex = 3;
            this.m_totalBufferValue.Text = "0";
            this.m_totalBufferValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_totalBufferLabel
            // 
            this.m_totalBufferLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_totalBufferLabel.Location = new System.Drawing.Point(3, 45);
            this.m_totalBufferLabel.Name = "m_totalBufferLabel";
            this.m_totalBufferLabel.Size = new System.Drawing.Size(99, 44);
            this.m_totalBufferLabel.TabIndex = 2;
            this.m_totalBufferLabel.Text = "Total buffers:";
            this.m_totalBufferLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_frameBufferTypeValue
            // 
            this.m_frameBufferTypeValue.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_frameBufferTypeValue.Location = new System.Drawing.Point(108, 0);
            this.m_frameBufferTypeValue.Name = "m_frameBufferTypeValue";
            this.m_frameBufferTypeValue.Size = new System.Drawing.Size(96, 45);
            this.m_frameBufferTypeValue.TabIndex = 1;
            this.m_frameBufferTypeValue.Text = "N/A";
            this.m_frameBufferTypeValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_frameBufferTypeLabel
            // 
            this.m_frameBufferTypeLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_frameBufferTypeLabel.Location = new System.Drawing.Point(3, 0);
            this.m_frameBufferTypeLabel.Name = "m_frameBufferTypeLabel";
            this.m_frameBufferTypeLabel.Size = new System.Drawing.Size(99, 45);
            this.m_frameBufferTypeLabel.TabIndex = 0;
            this.m_frameBufferTypeLabel.Text = "Frame buffer type (PGR or IIDC 1.32):";
            this.m_frameBufferTypeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_frameBufferAdditionalNotesLabel
            // 
            this.m_frameBufferAdditionalNotesLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_frameBufferAdditionalNotesLabel.Location = new System.Drawing.Point(0, 0);
            this.m_frameBufferAdditionalNotesLabel.Name = "m_frameBufferAdditionalNotesLabel";
            this.m_frameBufferAdditionalNotesLabel.Size = new System.Drawing.Size(191, 135);
            this.m_frameBufferAdditionalNotesLabel.TabIndex = 0;
            this.m_frameBufferAdditionalNotesLabel.Text = "In PGR mode, images can be skipped(i.e sent the nth image, discarding image 0 to " +
                "n-1).\r\n\r\nIn IIDC 1.32 mode, images cannot be skipped. In order to send the nth i" +
                "mage, all n images must be transmitted.";
            this.m_frameBufferAdditionalNotesLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_imageSelectionControlPanel
            // 
            this.m_imageSelectionControlPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_imageSelectionControlPanel.Controls.Add(this.m_currentSelectedImageValue);
            this.m_imageSelectionControlPanel.Controls.Add(this.m_imageSelectionAdditionalNotesLabel);
            this.m_imageSelectionControlPanel.Controls.Add(this.m_trackBarLabel);
            this.m_imageSelectionControlPanel.Controls.Add(this.m_currentSelectedImageTrackbar);
            this.m_imageSelectionControlPanel.Controls.Add(this.m_transmitLastImageButton);
            this.m_imageSelectionControlPanel.Controls.Add(this.m_transmitSelectedImageButton);
            this.m_imageSelectionControlPanel.Enabled = false;
            this.m_imageSelectionControlPanel.Location = new System.Drawing.Point(28, 227);
            this.m_imageSelectionControlPanel.Name = "m_imageSelectionControlPanel";
            this.m_imageSelectionControlPanel.Size = new System.Drawing.Size(402, 124);
            this.m_imageSelectionControlPanel.TabIndex = 8;
            // 
            // m_currentSelectedImageValue
            // 
            this.m_currentSelectedImageValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_currentSelectedImageValue.Location = new System.Drawing.Point(361, 31);
            this.m_currentSelectedImageValue.Name = "m_currentSelectedImageValue";
            this.m_currentSelectedImageValue.Size = new System.Drawing.Size(38, 45);
            this.m_currentSelectedImageValue.TabIndex = 2;
            this.m_currentSelectedImageValue.Text = "0";
            this.m_currentSelectedImageValue.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // m_imageSelectionAdditionalNotesLabel
            // 
            this.m_imageSelectionAdditionalNotesLabel.AutoSize = true;
            this.m_imageSelectionAdditionalNotesLabel.Location = new System.Drawing.Point(3, 79);
            this.m_imageSelectionAdditionalNotesLabel.Name = "m_imageSelectionAdditionalNotesLabel";
            this.m_imageSelectionAdditionalNotesLabel.Size = new System.Drawing.Size(317, 13);
            this.m_imageSelectionAdditionalNotesLabel.TabIndex = 2;
            this.m_imageSelectionAdditionalNotesLabel.Text = "Image index starts at 0 for PGR mode and at 1 for IIDC 1.32 mode";
            // 
            // m_trackBarLabel
            // 
            this.m_trackBarLabel.AutoSize = true;
            this.m_trackBarLabel.Location = new System.Drawing.Point(3, 4);
            this.m_trackBarLabel.Name = "m_trackBarLabel";
            this.m_trackBarLabel.Size = new System.Drawing.Size(167, 13);
            this.m_trackBarLabel.TabIndex = 2;
            this.m_trackBarLabel.Text = "Select an image to be transmitted:";
            // 
            // m_currentSelectedImageTrackbar
            // 
            this.m_currentSelectedImageTrackbar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_currentSelectedImageTrackbar.Location = new System.Drawing.Point(3, 31);
            this.m_currentSelectedImageTrackbar.Maximum = 30;
            this.m_currentSelectedImageTrackbar.Name = "m_currentSelectedImageTrackbar";
            this.m_currentSelectedImageTrackbar.Size = new System.Drawing.Size(366, 45);
            this.m_currentSelectedImageTrackbar.TabIndex = 1;
            this.m_currentSelectedImageTrackbar.TickFrequency = 5;
            this.m_currentSelectedImageTrackbar.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.m_currentSelectedImageTrackbar.ValueChanged += new System.EventHandler(this.OnTransmitImageTrackbarValueChanged);
            // 
            // m_transmitLastImageButton
            // 
            this.m_transmitLastImageButton.Location = new System.Drawing.Point(158, 97);
            this.m_transmitLastImageButton.Name = "m_transmitLastImageButton";
            this.m_transmitLastImageButton.Size = new System.Drawing.Size(162, 23);
            this.m_transmitLastImageButton.TabIndex = 3;
            this.m_transmitLastImageButton.Text = "Retransmit last image";
            this.m_transmitLastImageButton.UseVisualStyleBackColor = true;
            this.m_transmitLastImageButton.Click += new System.EventHandler(this.OnRetransmitSelectedImage);
            // 
            // m_transmitSelectedImageButton
            // 
            this.m_transmitSelectedImageButton.Location = new System.Drawing.Point(6, 97);
            this.m_transmitSelectedImageButton.Name = "m_transmitSelectedImageButton";
            this.m_transmitSelectedImageButton.Size = new System.Drawing.Size(146, 23);
            this.m_transmitSelectedImageButton.TabIndex = 2;
            this.m_transmitSelectedImageButton.Text = "Transmit selected image";
            this.m_transmitSelectedImageButton.UseVisualStyleBackColor = true;
            this.m_transmitSelectedImageButton.Click += new System.EventHandler(this.OnTransmitSelectedImage);
            // 
            // m_enableImageHoldCheckBox
            // 
            this.m_enableImageHoldCheckBox.AutoSize = true;
            this.m_enableImageHoldCheckBox.Location = new System.Drawing.Point(6, 19);
            this.m_enableImageHoldCheckBox.Name = "m_enableImageHoldCheckBox";
            this.m_enableImageHoldCheckBox.Size = new System.Drawing.Size(113, 17);
            this.m_enableImageHoldCheckBox.TabIndex = 1;
            this.m_enableImageHoldCheckBox.Text = "Enable image hold";
            this.m_enableImageHoldCheckBox.UseVisualStyleBackColor = true;
            this.m_enableImageHoldCheckBox.CheckedChanged += new System.EventHandler(this.OnEnableImageHoldCheckedStatusChanged);
            // 
            // m_imageSelectionLabel
            // 
            this.m_imageSelectionLabel.AutoSize = true;
            this.m_imageSelectionLabel.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_imageSelectionLabel.Location = new System.Drawing.Point(25, 207);
            this.m_imageSelectionLabel.Name = "m_imageSelectionLabel";
            this.m_imageSelectionLabel.Size = new System.Drawing.Size(94, 15);
            this.m_imageSelectionLabel.TabIndex = 6;
            this.m_imageSelectionLabel.Text = "Image Selection";
            // 
            // FrameBufferPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "FrameBufferPage";
            this.Size = new System.Drawing.Size(474, 438);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_mainGroupBox.PerformLayout();
            this.m_frameBufferInfoSplitContainer.Panel1.ResumeLayout(false);
            this.m_frameBufferInfoSplitContainer.Panel2.ResumeLayout(false);
            this.m_frameBufferInfoSplitContainer.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.m_imageSelectionControlPanel.ResumeLayout(false);
            this.m_imageSelectionControlPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_currentSelectedImageTrackbar)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.Label m_imageSelectionLabel;
        private System.Windows.Forms.CheckBox m_enableImageHoldCheckBox;
        private System.Windows.Forms.Panel m_imageSelectionControlPanel;
        private System.Windows.Forms.Button m_transmitLastImageButton;
        private System.Windows.Forms.Button m_transmitSelectedImageButton;
        private System.Windows.Forms.SplitContainer m_frameBufferInfoSplitContainer;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label m_frameBufferTypeLabel;
        private System.Windows.Forms.Label m_bufferUsedValue;
        private System.Windows.Forms.Label m_bufferUsedLabel;
        private System.Windows.Forms.Label m_totalBufferValue;
        private System.Windows.Forms.Label m_totalBufferLabel;
        private System.Windows.Forms.Label m_frameBufferTypeValue;
        private System.Windows.Forms.TrackBar m_currentSelectedImageTrackbar;
        private System.Windows.Forms.Label m_currentSelectedImageValue;
        private System.Windows.Forms.Label m_imageSelectionAdditionalNotesLabel;
        private System.Windows.Forms.Label m_trackBarLabel;
        private System.Windows.Forms.Label m_frameBufferAdditionalNotesLabel;
    }
}
