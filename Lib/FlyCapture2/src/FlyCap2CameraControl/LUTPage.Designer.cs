namespace FlyCap2CameraControl
{
    partial class LUTPage
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
            this.m_lookUpTableDrawingPanel = new System.Windows.Forms.Panel();
            this.m_inputMaxLabel = new System.Windows.Forms.Label();
            this.m_inputLabel = new System.Windows.Forms.Label();
            this.m_drawingArea = new System.Windows.Forms.PictureBox();
            this.m_inputMidLabel = new System.Windows.Forms.Label();
            this.m_inputMinLabel = new System.Windows.Forms.Label();
            this.m_outputMinLabel = new System.Windows.Forms.Label();
            this.m_outputMidLabel = new System.Windows.Forms.Label();
            this.m_outputMaxLabel = new System.Windows.Forms.Label();
            this.m_lookUpTabelControlPanel = new System.Windows.Forms.Panel();
            this.m_enableLUTInfomation = new System.Windows.Forms.Label();
            this.m_saveFileButton = new System.Windows.Forms.Button();
            this.m_openFileButton = new System.Windows.Forms.Button();
            this.m_SetToCameraButton = new System.Windows.Forms.Button();
            this.m_loadFromCameraButton = new System.Windows.Forms.Button();
            this.m_enableLookUpTableCheckBox = new System.Windows.Forms.CheckBox();
            this.m_bankComboBox = new System.Windows.Forms.ComboBox();
            this.m_BankLabel = new System.Windows.Forms.Label();
            this.m_lineStyleClearButton = new System.Windows.Forms.Button();
            this.m_channelLabel = new System.Windows.Forms.Label();
            this.m_lineStyleFreeRadioButton = new System.Windows.Forms.RadioButton();
            this.m_fileOperationsLabel = new System.Windows.Forms.Label();
            this.m_cameraOperationsLabel = new System.Windows.Forms.Label();
            this.m_lineStyleLabel = new System.Windows.Forms.Label();
            this.m_lineStyleSplineRadioButton = new System.Windows.Forms.RadioButton();
            this.m_channelComboBox = new System.Windows.Forms.ComboBox();
            this.m_lineStyleLinearRadioButton = new System.Windows.Forms.RadioButton();
            this.m_separateLine = new System.Windows.Forms.Label();
            this.m_openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.m_saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.m_mainGroupBox.SuspendLayout();
            this.m_lookUpTableDrawingPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_drawingArea)).BeginInit();
            this.m_lookUpTabelControlPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_lookUpTableDrawingPanel);
            this.m_mainGroupBox.Controls.Add(this.m_lookUpTabelControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_separateLine);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(471, 435);
            this.m_mainGroupBox.TabIndex = 4;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Look Up Table";
            // 
            // m_lookUpTableDrawingPanel
            // 
            this.m_lookUpTableDrawingPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lookUpTableDrawingPanel.Controls.Add(this.m_inputMaxLabel);
            this.m_lookUpTableDrawingPanel.Controls.Add(this.m_inputLabel);
            this.m_lookUpTableDrawingPanel.Controls.Add(this.m_drawingArea);
            this.m_lookUpTableDrawingPanel.Controls.Add(this.m_inputMidLabel);
            this.m_lookUpTableDrawingPanel.Controls.Add(this.m_inputMinLabel);
            this.m_lookUpTableDrawingPanel.Controls.Add(this.m_outputMinLabel);
            this.m_lookUpTableDrawingPanel.Controls.Add(this.m_outputMidLabel);
            this.m_lookUpTableDrawingPanel.Controls.Add(this.m_outputMaxLabel);
            this.m_lookUpTableDrawingPanel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.m_lookUpTableDrawingPanel.Location = new System.Drawing.Point(143, 19);
            this.m_lookUpTableDrawingPanel.Name = "m_lookUpTableDrawingPanel";
            this.m_lookUpTableDrawingPanel.Size = new System.Drawing.Size(322, 399);
            this.m_lookUpTableDrawingPanel.TabIndex = 2;
            this.m_lookUpTableDrawingPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.OnLookUpTableDrawingPanelPaint);
            // 
            // m_inputMaxLabel
            // 
            this.m_inputMaxLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.m_inputMaxLabel.Location = new System.Drawing.Point(290, 326);
            this.m_inputMaxLabel.Name = "m_inputMaxLabel";
            this.m_inputMaxLabel.Size = new System.Drawing.Size(35, 13);
            this.m_inputMaxLabel.TabIndex = 1;
            this.m_inputMaxLabel.Text = "max";
            this.m_inputMaxLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // m_inputLabel
            // 
            this.m_inputLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_inputLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_inputLabel.Location = new System.Drawing.Point(17, 348);
            this.m_inputLabel.Name = "m_inputLabel";
            this.m_inputLabel.Size = new System.Drawing.Size(295, 31);
            this.m_inputLabel.TabIndex = 2;
            this.m_inputLabel.Text = "Input";
            this.m_inputLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // m_drawingArea
            // 
            this.m_drawingArea.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_drawingArea.BackColor = System.Drawing.Color.White;
            this.m_drawingArea.Cursor = System.Windows.Forms.Cursors.Cross;
            this.m_drawingArea.Location = new System.Drawing.Point(42, 23);
            this.m_drawingArea.Name = "m_drawingArea";
            this.m_drawingArea.Size = new System.Drawing.Size(277, 301);
            this.m_drawingArea.TabIndex = 0;
            this.m_drawingArea.TabStop = false;
            this.m_drawingArea.Paint += new System.Windows.Forms.PaintEventHandler(this.OnDrawingAreaPaint);
            this.m_drawingArea.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PressMouseButton);
            this.m_drawingArea.MouseMove += new System.Windows.Forms.MouseEventHandler(this.OnMouseMove);
            this.m_drawingArea.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ReleaseMouseButton);
            // 
            // m_inputMidLabel
            // 
            this.m_inputMidLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_inputMidLabel.Location = new System.Drawing.Point(69, 327);
            this.m_inputMidLabel.Name = "m_inputMidLabel";
            this.m_inputMidLabel.Size = new System.Drawing.Size(224, 13);
            this.m_inputMidLabel.TabIndex = 1;
            this.m_inputMidLabel.Text = "mid";
            this.m_inputMidLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // m_inputMinLabel
            // 
            this.m_inputMinLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.m_inputMinLabel.AutoSize = true;
            this.m_inputMinLabel.Location = new System.Drawing.Point(33, 327);
            this.m_inputMinLabel.Name = "m_inputMinLabel";
            this.m_inputMinLabel.Size = new System.Drawing.Size(23, 13);
            this.m_inputMinLabel.TabIndex = 1;
            this.m_inputMinLabel.Text = "min";
            // 
            // m_outputMinLabel
            // 
            this.m_outputMinLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.m_outputMinLabel.AutoSize = true;
            this.m_outputMinLabel.Location = new System.Drawing.Point(16, 312);
            this.m_outputMinLabel.Name = "m_outputMinLabel";
            this.m_outputMinLabel.Size = new System.Drawing.Size(23, 13);
            this.m_outputMinLabel.TabIndex = 1;
            this.m_outputMinLabel.Text = "min";
            // 
            // m_outputMidLabel
            // 
            this.m_outputMidLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.m_outputMidLabel.Location = new System.Drawing.Point(14, 37);
            this.m_outputMidLabel.Name = "m_outputMidLabel";
            this.m_outputMidLabel.Size = new System.Drawing.Size(26, 274);
            this.m_outputMidLabel.TabIndex = 1;
            this.m_outputMidLabel.Text = "mid";
            this.m_outputMidLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // m_outputMaxLabel
            // 
            this.m_outputMaxLabel.AutoSize = true;
            this.m_outputMaxLabel.Location = new System.Drawing.Point(14, 16);
            this.m_outputMaxLabel.Name = "m_outputMaxLabel";
            this.m_outputMaxLabel.Size = new System.Drawing.Size(26, 13);
            this.m_outputMaxLabel.TabIndex = 1;
            this.m_outputMaxLabel.Text = "max";
            // 
            // m_lookUpTabelControlPanel
            // 
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_enableLUTInfomation);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_saveFileButton);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_openFileButton);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_SetToCameraButton);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_loadFromCameraButton);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_enableLookUpTableCheckBox);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_bankComboBox);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_BankLabel);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_lineStyleClearButton);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_channelLabel);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_lineStyleFreeRadioButton);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_fileOperationsLabel);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_cameraOperationsLabel);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_lineStyleLabel);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_lineStyleSplineRadioButton);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_channelComboBox);
            this.m_lookUpTabelControlPanel.Controls.Add(this.m_lineStyleLinearRadioButton);
            this.m_lookUpTabelControlPanel.Location = new System.Drawing.Point(6, 19);
            this.m_lookUpTabelControlPanel.MinimumSize = new System.Drawing.Size(130, 400);
            this.m_lookUpTabelControlPanel.Name = "m_lookUpTabelControlPanel";
            this.m_lookUpTabelControlPanel.Size = new System.Drawing.Size(130, 400);
            this.m_lookUpTabelControlPanel.TabIndex = 1;
            // 
            // m_enableLUTInfomation
            // 
            this.m_enableLUTInfomation.AutoSize = true;
            this.m_enableLUTInfomation.Location = new System.Drawing.Point(21, 19);
            this.m_enableLUTInfomation.Name = "m_enableLUTInfomation";
            this.m_enableLUTInfomation.Size = new System.Drawing.Size(90, 13);
            this.m_enableLUTInfomation.TabIndex = 13;
            this.m_enableLUTInfomation.Text = "(more information)";
            // 
            // m_saveFileButton
            // 
            this.m_saveFileButton.Location = new System.Drawing.Point(13, 373);
            this.m_saveFileButton.Name = "m_saveFileButton";
            this.m_saveFileButton.Size = new System.Drawing.Size(114, 23);
            this.m_saveFileButton.TabIndex = 12;
            this.m_saveFileButton.Text = "Save";
            this.m_saveFileButton.UseVisualStyleBackColor = true;
            this.m_saveFileButton.Click += new System.EventHandler(this.OnSaveFileButtonClick);
            // 
            // m_openFileButton
            // 
            this.m_openFileButton.Location = new System.Drawing.Point(13, 343);
            this.m_openFileButton.Name = "m_openFileButton";
            this.m_openFileButton.Size = new System.Drawing.Size(114, 23);
            this.m_openFileButton.TabIndex = 11;
            this.m_openFileButton.Text = "Open";
            this.m_openFileButton.UseVisualStyleBackColor = true;
            this.m_openFileButton.Click += new System.EventHandler(this.OnOpenFileButtonClick);
            // 
            // m_SetToCameraButton
            // 
            this.m_SetToCameraButton.Location = new System.Drawing.Point(13, 294);
            this.m_SetToCameraButton.Name = "m_SetToCameraButton";
            this.m_SetToCameraButton.Size = new System.Drawing.Size(114, 23);
            this.m_SetToCameraButton.TabIndex = 9;
            this.m_SetToCameraButton.Text = "Set to camera";
            this.m_SetToCameraButton.UseVisualStyleBackColor = true;
            this.m_SetToCameraButton.Click += new System.EventHandler(this.OnSetToCamera);
            // 
            // m_loadFromCameraButton
            // 
            this.m_loadFromCameraButton.Location = new System.Drawing.Point(13, 264);
            this.m_loadFromCameraButton.Name = "m_loadFromCameraButton";
            this.m_loadFromCameraButton.Size = new System.Drawing.Size(114, 23);
            this.m_loadFromCameraButton.TabIndex = 8;
            this.m_loadFromCameraButton.Text = "Load from camera";
            this.m_loadFromCameraButton.UseVisualStyleBackColor = true;
            this.m_loadFromCameraButton.Click += new System.EventHandler(this.OnLoadFromCameraButtonClick);
            // 
            // m_enableLookUpTableCheckBox
            // 
            this.m_enableLookUpTableCheckBox.AutoSize = true;
            this.m_enableLookUpTableCheckBox.Location = new System.Drawing.Point(3, 3);
            this.m_enableLookUpTableCheckBox.Name = "m_enableLookUpTableCheckBox";
            this.m_enableLookUpTableCheckBox.Size = new System.Drawing.Size(83, 17);
            this.m_enableLookUpTableCheckBox.TabIndex = 0;
            this.m_enableLookUpTableCheckBox.Text = "Enable LUT";
            this.m_enableLookUpTableCheckBox.UseVisualStyleBackColor = true;
            this.m_enableLookUpTableCheckBox.CheckedChanged += new System.EventHandler(this.OnEnableLookUpTableCheckedStatusChanged);
            // 
            // m_bankComboBox
            // 
            this.m_bankComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_bankComboBox.FormattingEnabled = true;
            this.m_bankComboBox.Location = new System.Drawing.Point(13, 56);
            this.m_bankComboBox.Name = "m_bankComboBox";
            this.m_bankComboBox.Size = new System.Drawing.Size(114, 21);
            this.m_bankComboBox.TabIndex = 2;
            this.m_bankComboBox.SelectedIndexChanged += new System.EventHandler(this.OnBankComboBoxSelectedIndexChanged);
            // 
            // m_BankLabel
            // 
            this.m_BankLabel.AutoSize = true;
            this.m_BankLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_BankLabel.Location = new System.Drawing.Point(3, 38);
            this.m_BankLabel.Name = "m_BankLabel";
            this.m_BankLabel.Size = new System.Drawing.Size(35, 13);
            this.m_BankLabel.TabIndex = 5;
            this.m_BankLabel.Text = "Bank";
            // 
            // m_lineStyleClearButton
            // 
            this.m_lineStyleClearButton.Location = new System.Drawing.Point(13, 216);
            this.m_lineStyleClearButton.Name = "m_lineStyleClearButton";
            this.m_lineStyleClearButton.Size = new System.Drawing.Size(114, 23);
            this.m_lineStyleClearButton.TabIndex = 7;
            this.m_lineStyleClearButton.Text = "Clear";
            this.m_lineStyleClearButton.UseVisualStyleBackColor = true;
            this.m_lineStyleClearButton.Click += new System.EventHandler(this.OnLineStyleClearButtonClick);
            // 
            // m_channelLabel
            // 
            this.m_channelLabel.AutoSize = true;
            this.m_channelLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_channelLabel.Location = new System.Drawing.Point(3, 82);
            this.m_channelLabel.Name = "m_channelLabel";
            this.m_channelLabel.Size = new System.Drawing.Size(52, 13);
            this.m_channelLabel.TabIndex = 5;
            this.m_channelLabel.Text = "Channel";
            // 
            // m_lineStyleFreeRadioButton
            // 
            this.m_lineStyleFreeRadioButton.AutoSize = true;
            this.m_lineStyleFreeRadioButton.Location = new System.Drawing.Point(16, 197);
            this.m_lineStyleFreeRadioButton.Name = "m_lineStyleFreeRadioButton";
            this.m_lineStyleFreeRadioButton.Size = new System.Drawing.Size(46, 17);
            this.m_lineStyleFreeRadioButton.TabIndex = 6;
            this.m_lineStyleFreeRadioButton.TabStop = true;
            this.m_lineStyleFreeRadioButton.Text = "Free";
            this.m_lineStyleFreeRadioButton.UseVisualStyleBackColor = true;
            this.m_lineStyleFreeRadioButton.CheckedChanged += new System.EventHandler(this.OnLineStyleChanged);
            // 
            // m_fileOperationsLabel
            // 
            this.m_fileOperationsLabel.AutoSize = true;
            this.m_fileOperationsLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_fileOperationsLabel.Location = new System.Drawing.Point(3, 326);
            this.m_fileOperationsLabel.Name = "m_fileOperationsLabel";
            this.m_fileOperationsLabel.Size = new System.Drawing.Size(91, 13);
            this.m_fileOperationsLabel.TabIndex = 5;
            this.m_fileOperationsLabel.Text = "File Operations";
            // 
            // m_cameraOperationsLabel
            // 
            this.m_cameraOperationsLabel.AutoSize = true;
            this.m_cameraOperationsLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_cameraOperationsLabel.Location = new System.Drawing.Point(3, 247);
            this.m_cameraOperationsLabel.Name = "m_cameraOperationsLabel";
            this.m_cameraOperationsLabel.Size = new System.Drawing.Size(116, 13);
            this.m_cameraOperationsLabel.TabIndex = 5;
            this.m_cameraOperationsLabel.Text = "Camera Operations";
            // 
            // m_lineStyleLabel
            // 
            this.m_lineStyleLabel.AutoSize = true;
            this.m_lineStyleLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_lineStyleLabel.Location = new System.Drawing.Point(3, 133);
            this.m_lineStyleLabel.Name = "m_lineStyleLabel";
            this.m_lineStyleLabel.Size = new System.Drawing.Size(62, 13);
            this.m_lineStyleLabel.TabIndex = 5;
            this.m_lineStyleLabel.Text = "Line Style";
            // 
            // m_lineStyleSplineRadioButton
            // 
            this.m_lineStyleSplineRadioButton.AutoSize = true;
            this.m_lineStyleSplineRadioButton.Location = new System.Drawing.Point(16, 174);
            this.m_lineStyleSplineRadioButton.Name = "m_lineStyleSplineRadioButton";
            this.m_lineStyleSplineRadioButton.Size = new System.Drawing.Size(54, 17);
            this.m_lineStyleSplineRadioButton.TabIndex = 5;
            this.m_lineStyleSplineRadioButton.TabStop = true;
            this.m_lineStyleSplineRadioButton.Text = "Spline";
            this.m_lineStyleSplineRadioButton.UseVisualStyleBackColor = true;
            this.m_lineStyleSplineRadioButton.CheckedChanged += new System.EventHandler(this.OnLineStyleChanged);
            // 
            // m_channelComboBox
            // 
            this.m_channelComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_channelComboBox.FormattingEnabled = true;
            this.m_channelComboBox.Location = new System.Drawing.Point(13, 100);
            this.m_channelComboBox.Name = "m_channelComboBox";
            this.m_channelComboBox.Size = new System.Drawing.Size(114, 21);
            this.m_channelComboBox.TabIndex = 3;
            this.m_channelComboBox.SelectedIndexChanged += new System.EventHandler(this.OnChannelComboBoxSelectedIndexChanged);
            // 
            // m_lineStyleLinearRadioButton
            // 
            this.m_lineStyleLinearRadioButton.AutoSize = true;
            this.m_lineStyleLinearRadioButton.Location = new System.Drawing.Point(16, 151);
            this.m_lineStyleLinearRadioButton.Name = "m_lineStyleLinearRadioButton";
            this.m_lineStyleLinearRadioButton.Size = new System.Drawing.Size(54, 17);
            this.m_lineStyleLinearRadioButton.TabIndex = 4;
            this.m_lineStyleLinearRadioButton.TabStop = true;
            this.m_lineStyleLinearRadioButton.Text = "Linear";
            this.m_lineStyleLinearRadioButton.UseVisualStyleBackColor = true;
            this.m_lineStyleLinearRadioButton.CheckedChanged += new System.EventHandler(this.OnLineStyleChanged);
            // 
            // m_separateLine
            // 
            this.m_separateLine.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.m_separateLine.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_separateLine.Location = new System.Drawing.Point(141, 8);
            this.m_separateLine.Name = "m_separateLine";
            this.m_separateLine.Size = new System.Drawing.Size(2, 425);
            this.m_separateLine.TabIndex = 9;
            this.m_separateLine.Text = "Separate Line. Don\'t resize it!";
            // 
            // m_openFileDialog
            // 
            this.m_openFileDialog.FileName = "lutdata";
            this.m_openFileDialog.Filter = "Look up table data files (*.lut)|*.lut";
            // 
            // m_saveFileDialog
            // 
            this.m_saveFileDialog.Filter = "Look up table data files (*.lut)|*.lut";
            // 
            // LUTPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "LUTPage";
            this.Size = new System.Drawing.Size(474, 438);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_lookUpTableDrawingPanel.ResumeLayout(false);
            this.m_lookUpTableDrawingPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_drawingArea)).EndInit();
            this.m_lookUpTabelControlPanel.ResumeLayout(false);
            this.m_lookUpTabelControlPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.CheckBox m_enableLookUpTableCheckBox;
        private System.Windows.Forms.ComboBox m_bankComboBox;
        private System.Windows.Forms.Label m_BankLabel;
        private System.Windows.Forms.ComboBox m_channelComboBox;
        private System.Windows.Forms.Label m_channelLabel;
        private System.Windows.Forms.RadioButton m_lineStyleLinearRadioButton;
        private System.Windows.Forms.Label m_lineStyleLabel;
        private System.Windows.Forms.Button m_lineStyleClearButton;
        private System.Windows.Forms.RadioButton m_lineStyleFreeRadioButton;
        private System.Windows.Forms.RadioButton m_lineStyleSplineRadioButton;
        private System.Windows.Forms.Label m_separateLine;
        private System.Windows.Forms.Panel m_lookUpTabelControlPanel;
        private System.Windows.Forms.Button m_SetToCameraButton;
        private System.Windows.Forms.Button m_loadFromCameraButton;
        private System.Windows.Forms.Label m_fileOperationsLabel;
        private System.Windows.Forms.Label m_cameraOperationsLabel;
        private System.Windows.Forms.Panel m_lookUpTableDrawingPanel;
        private System.Windows.Forms.PictureBox m_drawingArea;
        private System.Windows.Forms.Label m_enableLUTInfomation;
        private System.Windows.Forms.Button m_saveFileButton;
        private System.Windows.Forms.Button m_openFileButton;
        private System.Windows.Forms.Label m_inputLabel;
        private System.Windows.Forms.Label m_inputMidLabel;
        private System.Windows.Forms.Label m_inputMaxLabel;
        private System.Windows.Forms.Label m_inputMinLabel;
        private System.Windows.Forms.Label m_outputMinLabel;
        private System.Windows.Forms.Label m_outputMidLabel;
        private System.Windows.Forms.Label m_outputMaxLabel;
        private System.Windows.Forms.OpenFileDialog m_openFileDialog;
        private System.Windows.Forms.SaveFileDialog m_saveFileDialog;
    }
}
