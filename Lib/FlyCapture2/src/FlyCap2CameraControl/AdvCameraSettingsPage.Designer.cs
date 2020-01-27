namespace FlyCap2CameraControl
{
    partial class AdvCameraSettingsPage
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
            this.m_speedControlPanel = new System.Windows.Forms.Panel();
            this.m_IsochSpeedCombo = new System.Windows.Forms.ComboBox();
            this.m_IsochSpeedLabel = new System.Windows.Forms.Label();
            this.m_AsyncSpeedCombo = new System.Windows.Forms.ComboBox();
            this.m_AsyncSpeedLabel = new System.Windows.Forms.Label();
            this.m_busSpeedControlLabel = new System.Windows.Forms.Label();
            this.m_embedImageInformationControlPanel = new System.Windows.Forms.Panel();
            this.m_embeddedImageInfoLabel = new System.Windows.Forms.Label();
            this.m_selectAllEmbeddedImageInfoButton = new System.Windows.Forms.Button();
            this.m_embeddedImageInfoDescriptionTextBox = new System.Windows.Forms.TextBox();
            this.m_embeddedImageInfoSelectionPanel = new System.Windows.Forms.Panel();
            this.m_unselectAllEmbeddedImageInfoButton = new System.Windows.Forms.Button();
            this.m_gigEPacketResendControlPanel = new System.Windows.Forms.Panel();
            this.m_pktResendEnableLabel = new System.Windows.Forms.Label();
            this.m_packetResendMaxPacketToResendSpinButton = new System.Windows.Forms.NumericUpDown();
            this.m_packetResendTimeoutSpinButton = new System.Windows.Forms.NumericUpDown();
            this.m_packetResendLoadButton = new System.Windows.Forms.Button();
            this.m_packetResendSaveButton = new System.Windows.Forms.Button();
            this.m_maxPacketToResendLabel = new System.Windows.Forms.Label();
            this.m_timeoutLabel = new System.Windows.Forms.Label();
            this.m_enableGigEPacketResendCheckBox = new System.Windows.Forms.CheckBox();
            this.m_gigEPacketResendLabel = new System.Windows.Forms.Label();
            this.m_autoRangeControlPanel = new System.Windows.Forms.Panel();
            this.m_setAutoRangeValueButton = new System.Windows.Forms.Button();
            this.m_getAutoRangeValueButton = new System.Windows.Forms.Button();
            this.m_autoRangeMaxLabel = new System.Windows.Forms.Label();
            this.m_autoRangeMinLabel = new System.Windows.Forms.Label();
            this.m_autoRangeMaxTextBox = new System.Windows.Forms.TextBox();
            this.m_autoRangeMinTextBox = new System.Windows.Forms.TextBox();
            this.m_autoRangePropertyComboBox = new System.Windows.Forms.ComboBox();
            this.m_autoRangePropertyLabel = new System.Windows.Forms.Label();
            this.m_autoRangeLabel = new System.Windows.Forms.Label();
            this.m_memoryChannelControlPanel = new System.Windows.Forms.Panel();
            this.m_memoryChannelsRestoreButton = new System.Windows.Forms.Button();
            this.m_memoryChannelsSaveButton = new System.Windows.Forms.Button();
            this.m_memoryChannelsComboBox = new System.Windows.Forms.ComboBox();
            this.m_channelLabel = new System.Windows.Forms.Label();
            this.m_memoryChannelsNotes = new System.Windows.Forms.TextBox();
            this.m_memoryChannelsLabel = new System.Windows.Forms.Label();
            this.m_testPatternSelectionPanel = new System.Windows.Forms.Panel();
            this.m_testPatternNoneRadioButton = new System.Windows.Forms.RadioButton();
            this.m_testPattern2RadioButton = new System.Windows.Forms.RadioButton();
            this.m_testPattern1RadioButton = new System.Windows.Forms.RadioButton();
            this.m_displayTestPatternLabel = new System.Windows.Forms.Label();
            this.m_y16EndiannessSelectionPanel = new System.Windows.Forms.Panel();
            this.m_y16LittleEndianRadioButton = new System.Windows.Forms.RadioButton();
            this.m_y16BigEndianRadioButton = new System.Windows.Forms.RadioButton();
            this.m_y16EndiannessLabel = new System.Windows.Forms.Label();
            this.m_rawBayerOutputHintTextLabel = new System.Windows.Forms.Label();
            this.m_mirrorImageCheckBox = new System.Windows.Forms.CheckBox();
            this.m_rawBayerOutputCheckBox = new System.Windows.Forms.CheckBox();
            this.m_IsochHelperLabel = new System.Windows.Forms.Label();
            this.m_mainGroupBox.SuspendLayout();
            this.m_speedControlPanel.SuspendLayout();
            this.m_embedImageInformationControlPanel.SuspendLayout();
            this.m_gigEPacketResendControlPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_packetResendMaxPacketToResendSpinButton)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_packetResendTimeoutSpinButton)).BeginInit();
            this.m_autoRangeControlPanel.SuspendLayout();
            this.m_memoryChannelControlPanel.SuspendLayout();
            this.m_testPatternSelectionPanel.SuspendLayout();
            this.m_y16EndiannessSelectionPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_speedControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_embedImageInformationControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_gigEPacketResendControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_autoRangeControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_memoryChannelControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_testPatternSelectionPanel);
            this.m_mainGroupBox.Controls.Add(this.m_y16EndiannessSelectionPanel);
            this.m_mainGroupBox.Controls.Add(this.m_rawBayerOutputHintTextLabel);
            this.m_mainGroupBox.Controls.Add(this.m_mirrorImageCheckBox);
            this.m_mainGroupBox.Controls.Add(this.m_rawBayerOutputCheckBox);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(471, 495);
            this.m_mainGroupBox.TabIndex = 3;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Advanced Camera Settings";
            // 
            // m_speedControlPanel
            // 
            this.m_speedControlPanel.Controls.Add(this.m_IsochHelperLabel);
            this.m_speedControlPanel.Controls.Add(this.m_IsochSpeedCombo);
            this.m_speedControlPanel.Controls.Add(this.m_IsochSpeedLabel);
            this.m_speedControlPanel.Controls.Add(this.m_AsyncSpeedCombo);
            this.m_speedControlPanel.Controls.Add(this.m_AsyncSpeedLabel);
            this.m_speedControlPanel.Controls.Add(this.m_busSpeedControlLabel);
            this.m_speedControlPanel.Location = new System.Drawing.Point(243, 350);
            this.m_speedControlPanel.Name = "m_speedControlPanel";
            this.m_speedControlPanel.Size = new System.Drawing.Size(212, 88);
            this.m_speedControlPanel.TabIndex = 14;
            // 
            // m_IsochSpeedCombo
            // 
            this.m_IsochSpeedCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_IsochSpeedCombo.FormattingEnabled = true;
            this.m_IsochSpeedCombo.Location = new System.Drawing.Point(97, 53);
            this.m_IsochSpeedCombo.Name = "m_IsochSpeedCombo";
            this.m_IsochSpeedCombo.Size = new System.Drawing.Size(79, 21);
            this.m_IsochSpeedCombo.TabIndex = 11;
            this.m_IsochSpeedCombo.SelectedIndexChanged += new System.EventHandler(this.m_IsochSpeedCombo_SelectedIndexChanged);
            // 
            // m_IsochSpeedLabel
            // 
            this.m_IsochSpeedLabel.AutoSize = true;
            this.m_IsochSpeedLabel.Location = new System.Drawing.Point(5, 56);
            this.m_IsochSpeedLabel.Name = "m_IsochSpeedLabel";
            this.m_IsochSpeedLabel.Padding = new System.Windows.Forms.Padding(0, 1, 0, 2);
            this.m_IsochSpeedLabel.Size = new System.Drawing.Size(70, 16);
            this.m_IsochSpeedLabel.TabIndex = 10;
            this.m_IsochSpeedLabel.Text = "Isoch Speed:";
            // 
            // m_AsyncSpeedCombo
            // 
            this.m_AsyncSpeedCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_AsyncSpeedCombo.FormattingEnabled = true;
            this.m_AsyncSpeedCombo.Location = new System.Drawing.Point(97, 19);
            this.m_AsyncSpeedCombo.Name = "m_AsyncSpeedCombo";
            this.m_AsyncSpeedCombo.Size = new System.Drawing.Size(79, 21);
            this.m_AsyncSpeedCombo.TabIndex = 9;
            this.m_AsyncSpeedCombo.SelectedIndexChanged += new System.EventHandler(this.m_AsyncSpeedCombo_SelectedIndexChanged);
            // 
            // m_AsyncSpeedLabel
            // 
            this.m_AsyncSpeedLabel.AutoSize = true;
            this.m_AsyncSpeedLabel.Location = new System.Drawing.Point(5, 22);
            this.m_AsyncSpeedLabel.Name = "m_AsyncSpeedLabel";
            this.m_AsyncSpeedLabel.Padding = new System.Windows.Forms.Padding(0, 1, 0, 2);
            this.m_AsyncSpeedLabel.Size = new System.Drawing.Size(73, 16);
            this.m_AsyncSpeedLabel.TabIndex = 7;
            this.m_AsyncSpeedLabel.Text = "Async Speed:";
            // 
            // m_busSpeedControlLabel
            // 
            this.m_busSpeedControlLabel.AutoSize = true;
            this.m_busSpeedControlLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_busSpeedControlLabel.Location = new System.Drawing.Point(0, 0);
            this.m_busSpeedControlLabel.Name = "m_busSpeedControlLabel";
            this.m_busSpeedControlLabel.Size = new System.Drawing.Size(109, 13);
            this.m_busSpeedControlLabel.TabIndex = 5;
            this.m_busSpeedControlLabel.Text = "Bus Speed Control";
            // 
            // m_embedImageInformationControlPanel
            // 
            this.m_embedImageInformationControlPanel.Controls.Add(this.m_embeddedImageInfoLabel);
            this.m_embedImageInformationControlPanel.Controls.Add(this.m_selectAllEmbeddedImageInfoButton);
            this.m_embedImageInformationControlPanel.Controls.Add(this.m_embeddedImageInfoDescriptionTextBox);
            this.m_embedImageInformationControlPanel.Controls.Add(this.m_embeddedImageInfoSelectionPanel);
            this.m_embedImageInformationControlPanel.Controls.Add(this.m_unselectAllEmbeddedImageInfoButton);
            this.m_embedImageInformationControlPanel.Location = new System.Drawing.Point(240, 16);
            this.m_embedImageInformationControlPanel.Name = "m_embedImageInformationControlPanel";
            this.m_embedImageInformationControlPanel.Size = new System.Drawing.Size(216, 200);
            this.m_embedImageInformationControlPanel.TabIndex = 7;
            // 
            // m_embeddedImageInfoLabel
            // 
            this.m_embeddedImageInfoLabel.AutoSize = true;
            this.m_embeddedImageInfoLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_embeddedImageInfoLabel.Location = new System.Drawing.Point(2, 0);
            this.m_embeddedImageInfoLabel.Name = "m_embeddedImageInfoLabel";
            this.m_embeddedImageInfoLabel.Size = new System.Drawing.Size(177, 13);
            this.m_embeddedImageInfoLabel.TabIndex = 4;
            this.m_embeddedImageInfoLabel.Text = "Embedded Image Information";
            // 
            // m_selectAllEmbeddedImageInfoButton
            // 
            this.m_selectAllEmbeddedImageInfoButton.Location = new System.Drawing.Point(16, 176);
            this.m_selectAllEmbeddedImageInfoButton.Name = "m_selectAllEmbeddedImageInfoButton";
            this.m_selectAllEmbeddedImageInfoButton.Size = new System.Drawing.Size(81, 23);
            this.m_selectAllEmbeddedImageInfoButton.TabIndex = 9;
            this.m_selectAllEmbeddedImageInfoButton.Text = "Select All";
            this.m_selectAllEmbeddedImageInfoButton.UseVisualStyleBackColor = true;
            this.m_selectAllEmbeddedImageInfoButton.Click += new System.EventHandler(this.OnSelectAllEmbeddedImageInfoButtonClick);
            // 
            // m_embeddedImageInfoDescriptionTextBox
            // 
            this.m_embeddedImageInfoDescriptionTextBox.BackColor = System.Drawing.Color.White;
            this.m_embeddedImageInfoDescriptionTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.m_embeddedImageInfoDescriptionTextBox.Location = new System.Drawing.Point(5, 16);
            this.m_embeddedImageInfoDescriptionTextBox.Multiline = true;
            this.m_embeddedImageInfoDescriptionTextBox.Name = "m_embeddedImageInfoDescriptionTextBox";
            this.m_embeddedImageInfoDescriptionTextBox.ReadOnly = true;
            this.m_embeddedImageInfoDescriptionTextBox.Size = new System.Drawing.Size(208, 29);
            this.m_embeddedImageInfoDescriptionTextBox.TabIndex = 7;
            this.m_embeddedImageInfoDescriptionTextBox.TabStop = false;
            this.m_embeddedImageInfoDescriptionTextBox.Text = "Select the frame-specific information to be embedded in the image.";
            // 
            // m_embeddedImageInfoSelectionPanel
            // 
            this.m_embeddedImageInfoSelectionPanel.Location = new System.Drawing.Point(5, 48);
            this.m_embeddedImageInfoSelectionPanel.Name = "m_embeddedImageInfoSelectionPanel";
            this.m_embeddedImageInfoSelectionPanel.Size = new System.Drawing.Size(208, 123);
            this.m_embeddedImageInfoSelectionPanel.TabIndex = 1;
            // 
            // m_unselectAllEmbeddedImageInfoButton
            // 
            this.m_unselectAllEmbeddedImageInfoButton.Location = new System.Drawing.Point(120, 176);
            this.m_unselectAllEmbeddedImageInfoButton.Name = "m_unselectAllEmbeddedImageInfoButton";
            this.m_unselectAllEmbeddedImageInfoButton.Size = new System.Drawing.Size(82, 23);
            this.m_unselectAllEmbeddedImageInfoButton.TabIndex = 10;
            this.m_unselectAllEmbeddedImageInfoButton.Text = "Unselect All";
            this.m_unselectAllEmbeddedImageInfoButton.UseVisualStyleBackColor = true;
            this.m_unselectAllEmbeddedImageInfoButton.Click += new System.EventHandler(this.OnUnselectAllEmbeddedImageInfoButtonClick);
            // 
            // m_gigEPacketResendControlPanel
            // 
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_pktResendEnableLabel);
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_packetResendMaxPacketToResendSpinButton);
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_packetResendTimeoutSpinButton);
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_packetResendLoadButton);
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_packetResendSaveButton);
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_maxPacketToResendLabel);
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_timeoutLabel);
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_enableGigEPacketResendCheckBox);
            this.m_gigEPacketResendControlPanel.Controls.Add(this.m_gigEPacketResendLabel);
            this.m_gigEPacketResendControlPanel.Location = new System.Drawing.Point(6, 368);
            this.m_gigEPacketResendControlPanel.Name = "m_gigEPacketResendControlPanel";
            this.m_gigEPacketResendControlPanel.Size = new System.Drawing.Size(225, 120);
            this.m_gigEPacketResendControlPanel.TabIndex = 13;
            // 
            // m_pktResendEnableLabel
            // 
            this.m_pktResendEnableLabel.Location = new System.Drawing.Point(21, 42);
            this.m_pktResendEnableLabel.Name = "m_pktResendEnableLabel";
            this.m_pktResendEnableLabel.Size = new System.Drawing.Size(177, 42);
            this.m_pktResendEnableLabel.TabIndex = 12;
            this.m_pktResendEnableLabel.Text = "Camera must be stopped to enable/disable packet resend";
            // 
            // m_packetResendMaxPacketToResendSpinButton
            // 
            this.m_packetResendMaxPacketToResendSpinButton.Location = new System.Drawing.Point(128, 70);
            this.m_packetResendMaxPacketToResendSpinButton.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.m_packetResendMaxPacketToResendSpinButton.Name = "m_packetResendMaxPacketToResendSpinButton";
            this.m_packetResendMaxPacketToResendSpinButton.Size = new System.Drawing.Size(91, 20);
            this.m_packetResendMaxPacketToResendSpinButton.TabIndex = 9;
            this.m_packetResendMaxPacketToResendSpinButton.Visible = false;
            // 
            // m_packetResendTimeoutSpinButton
            // 
            this.m_packetResendTimeoutSpinButton.Location = new System.Drawing.Point(128, 50);
            this.m_packetResendTimeoutSpinButton.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.m_packetResendTimeoutSpinButton.Name = "m_packetResendTimeoutSpinButton";
            this.m_packetResendTimeoutSpinButton.Size = new System.Drawing.Size(91, 20);
            this.m_packetResendTimeoutSpinButton.TabIndex = 8;
            this.m_packetResendTimeoutSpinButton.Visible = false;
            // 
            // m_packetResendLoadButton
            // 
            this.m_packetResendLoadButton.Location = new System.Drawing.Point(123, 88);
            this.m_packetResendLoadButton.Name = "m_packetResendLoadButton";
            this.m_packetResendLoadButton.Size = new System.Drawing.Size(75, 23);
            this.m_packetResendLoadButton.TabIndex = 11;
            this.m_packetResendLoadButton.Text = "Load";
            this.m_packetResendLoadButton.UseVisualStyleBackColor = true;
            this.m_packetResendLoadButton.Visible = false;
            this.m_packetResendLoadButton.Click += new System.EventHandler(this.OnPacketResendLoadButtonClicked);
            // 
            // m_packetResendSaveButton
            // 
            this.m_packetResendSaveButton.Location = new System.Drawing.Point(30, 88);
            this.m_packetResendSaveButton.Name = "m_packetResendSaveButton";
            this.m_packetResendSaveButton.Size = new System.Drawing.Size(75, 23);
            this.m_packetResendSaveButton.TabIndex = 10;
            this.m_packetResendSaveButton.Text = "Save";
            this.m_packetResendSaveButton.UseVisualStyleBackColor = true;
            this.m_packetResendSaveButton.Visible = false;
            this.m_packetResendSaveButton.Click += new System.EventHandler(this.OnPacketResendSaveButtonClicked);
            // 
            // m_maxPacketToResendLabel
            // 
            this.m_maxPacketToResendLabel.AutoSize = true;
            this.m_maxPacketToResendLabel.Location = new System.Drawing.Point(8, 72);
            this.m_maxPacketToResendLabel.Name = "m_maxPacketToResendLabel";
            this.m_maxPacketToResendLabel.Size = new System.Drawing.Size(118, 13);
            this.m_maxPacketToResendLabel.TabIndex = 6;
            this.m_maxPacketToResendLabel.Text = "Max packets to resend:";
            this.m_maxPacketToResendLabel.Visible = false;
            // 
            // m_timeoutLabel
            // 
            this.m_timeoutLabel.AutoSize = true;
            this.m_timeoutLabel.Location = new System.Drawing.Point(8, 64);
            this.m_timeoutLabel.Name = "m_timeoutLabel";
            this.m_timeoutLabel.Size = new System.Drawing.Size(73, 13);
            this.m_timeoutLabel.TabIndex = 6;
            this.m_timeoutLabel.Text = "Timeout (ms) :";
            this.m_timeoutLabel.Visible = false;
            // 
            // m_enableGigEPacketResendCheckBox
            // 
            this.m_enableGigEPacketResendCheckBox.AutoSize = true;
            this.m_enableGigEPacketResendCheckBox.Location = new System.Drawing.Point(8, 22);
            this.m_enableGigEPacketResendCheckBox.Name = "m_enableGigEPacketResendCheckBox";
            this.m_enableGigEPacketResendCheckBox.Size = new System.Drawing.Size(130, 17);
            this.m_enableGigEPacketResendCheckBox.TabIndex = 5;
            this.m_enableGigEPacketResendCheckBox.Text = "Enable packet resend";
            this.m_enableGigEPacketResendCheckBox.UseVisualStyleBackColor = true;
            this.m_enableGigEPacketResendCheckBox.CheckedChanged += new System.EventHandler(this.m_enableGigEPacketResendCheckBox_CheckedChanged);
            // 
            // m_gigEPacketResendLabel
            // 
            this.m_gigEPacketResendLabel.AutoSize = true;
            this.m_gigEPacketResendLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_gigEPacketResendLabel.Location = new System.Drawing.Point(4, 4);
            this.m_gigEPacketResendLabel.Name = "m_gigEPacketResendLabel";
            this.m_gigEPacketResendLabel.Size = new System.Drawing.Size(118, 13);
            this.m_gigEPacketResendLabel.TabIndex = 4;
            this.m_gigEPacketResendLabel.Text = "GigE Packet Resend";
            // 
            // m_autoRangeControlPanel
            // 
            this.m_autoRangeControlPanel.Controls.Add(this.m_setAutoRangeValueButton);
            this.m_autoRangeControlPanel.Controls.Add(this.m_getAutoRangeValueButton);
            this.m_autoRangeControlPanel.Controls.Add(this.m_autoRangeMaxLabel);
            this.m_autoRangeControlPanel.Controls.Add(this.m_autoRangeMinLabel);
            this.m_autoRangeControlPanel.Controls.Add(this.m_autoRangeMaxTextBox);
            this.m_autoRangeControlPanel.Controls.Add(this.m_autoRangeMinTextBox);
            this.m_autoRangeControlPanel.Controls.Add(this.m_autoRangePropertyComboBox);
            this.m_autoRangeControlPanel.Controls.Add(this.m_autoRangePropertyLabel);
            this.m_autoRangeControlPanel.Controls.Add(this.m_autoRangeLabel);
            this.m_autoRangeControlPanel.Location = new System.Drawing.Point(240, 232);
            this.m_autoRangeControlPanel.Name = "m_autoRangeControlPanel";
            this.m_autoRangeControlPanel.Size = new System.Drawing.Size(216, 104);
            this.m_autoRangeControlPanel.TabIndex = 9;
            // 
            // m_setAutoRangeValueButton
            // 
            this.m_setAutoRangeValueButton.Location = new System.Drawing.Point(123, 72);
            this.m_setAutoRangeValueButton.Name = "m_setAutoRangeValueButton";
            this.m_setAutoRangeValueButton.Size = new System.Drawing.Size(84, 23);
            this.m_setAutoRangeValueButton.TabIndex = 5;
            this.m_setAutoRangeValueButton.Text = "Set Range";
            this.m_setAutoRangeValueButton.UseVisualStyleBackColor = true;
            this.m_setAutoRangeValueButton.Click += new System.EventHandler(this.OnSetAutoRangeValueButtonClick);
            // 
            // m_getAutoRangeValueButton
            // 
            this.m_getAutoRangeValueButton.Location = new System.Drawing.Point(11, 72);
            this.m_getAutoRangeValueButton.Name = "m_getAutoRangeValueButton";
            this.m_getAutoRangeValueButton.Size = new System.Drawing.Size(84, 23);
            this.m_getAutoRangeValueButton.TabIndex = 4;
            this.m_getAutoRangeValueButton.Text = "Get Range";
            this.m_getAutoRangeValueButton.UseVisualStyleBackColor = true;
            this.m_getAutoRangeValueButton.Click += new System.EventHandler(this.OnGetAutoRangeValueButtonClick);
            // 
            // m_autoRangeMaxLabel
            // 
            this.m_autoRangeMaxLabel.AutoSize = true;
            this.m_autoRangeMaxLabel.Location = new System.Drawing.Point(111, 52);
            this.m_autoRangeMaxLabel.Name = "m_autoRangeMaxLabel";
            this.m_autoRangeMaxLabel.Size = new System.Drawing.Size(30, 13);
            this.m_autoRangeMaxLabel.TabIndex = 3;
            this.m_autoRangeMaxLabel.Text = "Max:";
            // 
            // m_autoRangeMinLabel
            // 
            this.m_autoRangeMinLabel.AutoSize = true;
            this.m_autoRangeMinLabel.Location = new System.Drawing.Point(7, 52);
            this.m_autoRangeMinLabel.Name = "m_autoRangeMinLabel";
            this.m_autoRangeMinLabel.Size = new System.Drawing.Size(27, 13);
            this.m_autoRangeMinLabel.TabIndex = 3;
            this.m_autoRangeMinLabel.Text = "Min:";
            // 
            // m_autoRangeMaxTextBox
            // 
            this.m_autoRangeMaxTextBox.Location = new System.Drawing.Point(144, 48);
            this.m_autoRangeMaxTextBox.Name = "m_autoRangeMaxTextBox";
            this.m_autoRangeMaxTextBox.Size = new System.Drawing.Size(58, 20);
            this.m_autoRangeMaxTextBox.TabIndex = 3;
            // 
            // m_autoRangeMinTextBox
            // 
            this.m_autoRangeMinTextBox.Location = new System.Drawing.Point(37, 48);
            this.m_autoRangeMinTextBox.Name = "m_autoRangeMinTextBox";
            this.m_autoRangeMinTextBox.Size = new System.Drawing.Size(58, 20);
            this.m_autoRangeMinTextBox.TabIndex = 2;
            // 
            // m_autoRangePropertyComboBox
            // 
            this.m_autoRangePropertyComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_autoRangePropertyComboBox.FormattingEnabled = true;
            this.m_autoRangePropertyComboBox.Items.AddRange(new object[] {
            "Exposure",
            "Shutter",
            "Gain"});
            this.m_autoRangePropertyComboBox.Location = new System.Drawing.Point(64, 17);
            this.m_autoRangePropertyComboBox.Name = "m_autoRangePropertyComboBox";
            this.m_autoRangePropertyComboBox.Size = new System.Drawing.Size(125, 21);
            this.m_autoRangePropertyComboBox.TabIndex = 1;
            this.m_autoRangePropertyComboBox.SelectedIndexChanged += new System.EventHandler(this.OnAutoRangePropertySelectedIndexChanged);
            // 
            // m_autoRangePropertyLabel
            // 
            this.m_autoRangePropertyLabel.AutoSize = true;
            this.m_autoRangePropertyLabel.Location = new System.Drawing.Point(8, 20);
            this.m_autoRangePropertyLabel.Name = "m_autoRangePropertyLabel";
            this.m_autoRangePropertyLabel.Size = new System.Drawing.Size(49, 13);
            this.m_autoRangePropertyLabel.TabIndex = 0;
            this.m_autoRangePropertyLabel.Text = "Property:";
            // 
            // m_autoRangeLabel
            // 
            this.m_autoRangeLabel.AutoSize = true;
            this.m_autoRangeLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_autoRangeLabel.Location = new System.Drawing.Point(0, 0);
            this.m_autoRangeLabel.Name = "m_autoRangeLabel";
            this.m_autoRangeLabel.Size = new System.Drawing.Size(117, 13);
            this.m_autoRangeLabel.TabIndex = 4;
            this.m_autoRangeLabel.Text = "Auto Range Control";
            // 
            // m_memoryChannelControlPanel
            // 
            this.m_memoryChannelControlPanel.Controls.Add(this.m_memoryChannelsRestoreButton);
            this.m_memoryChannelControlPanel.Controls.Add(this.m_memoryChannelsSaveButton);
            this.m_memoryChannelControlPanel.Controls.Add(this.m_memoryChannelsComboBox);
            this.m_memoryChannelControlPanel.Controls.Add(this.m_channelLabel);
            this.m_memoryChannelControlPanel.Controls.Add(this.m_memoryChannelsNotes);
            this.m_memoryChannelControlPanel.Controls.Add(this.m_memoryChannelsLabel);
            this.m_memoryChannelControlPanel.Location = new System.Drawing.Point(7, 248);
            this.m_memoryChannelControlPanel.Name = "m_memoryChannelControlPanel";
            this.m_memoryChannelControlPanel.Size = new System.Drawing.Size(224, 112);
            this.m_memoryChannelControlPanel.TabIndex = 8;
            // 
            // m_memoryChannelsRestoreButton
            // 
            this.m_memoryChannelsRestoreButton.Location = new System.Drawing.Point(127, 80);
            this.m_memoryChannelsRestoreButton.Name = "m_memoryChannelsRestoreButton";
            this.m_memoryChannelsRestoreButton.Size = new System.Drawing.Size(75, 23);
            this.m_memoryChannelsRestoreButton.TabIndex = 3;
            this.m_memoryChannelsRestoreButton.Text = "Restore";
            this.m_memoryChannelsRestoreButton.UseVisualStyleBackColor = true;
            this.m_memoryChannelsRestoreButton.Click += new System.EventHandler(this.OnMemoryChannelsRestoreButtonClick);
            // 
            // m_memoryChannelsSaveButton
            // 
            this.m_memoryChannelsSaveButton.Location = new System.Drawing.Point(11, 80);
            this.m_memoryChannelsSaveButton.Name = "m_memoryChannelsSaveButton";
            this.m_memoryChannelsSaveButton.Size = new System.Drawing.Size(75, 23);
            this.m_memoryChannelsSaveButton.TabIndex = 2;
            this.m_memoryChannelsSaveButton.Text = "Save";
            this.m_memoryChannelsSaveButton.UseVisualStyleBackColor = true;
            this.m_memoryChannelsSaveButton.Click += new System.EventHandler(this.OnMemoryChannelsSaveButtonClick);
            // 
            // m_memoryChannelsComboBox
            // 
            this.m_memoryChannelsComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_memoryChannelsComboBox.FormattingEnabled = true;
            this.m_memoryChannelsComboBox.Location = new System.Drawing.Point(64, 16);
            this.m_memoryChannelsComboBox.Name = "m_memoryChannelsComboBox";
            this.m_memoryChannelsComboBox.Size = new System.Drawing.Size(147, 21);
            this.m_memoryChannelsComboBox.TabIndex = 1;
            // 
            // m_channelLabel
            // 
            this.m_channelLabel.AutoSize = true;
            this.m_channelLabel.Location = new System.Drawing.Point(8, 20);
            this.m_channelLabel.Name = "m_channelLabel";
            this.m_channelLabel.Size = new System.Drawing.Size(49, 13);
            this.m_channelLabel.TabIndex = 0;
            this.m_channelLabel.Text = "Channel:";
            // 
            // m_memoryChannelsNotes
            // 
            this.m_memoryChannelsNotes.BackColor = System.Drawing.Color.White;
            this.m_memoryChannelsNotes.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.m_memoryChannelsNotes.Location = new System.Drawing.Point(3, 48);
            this.m_memoryChannelsNotes.Multiline = true;
            this.m_memoryChannelsNotes.Name = "m_memoryChannelsNotes";
            this.m_memoryChannelsNotes.ReadOnly = true;
            this.m_memoryChannelsNotes.Size = new System.Drawing.Size(215, 29);
            this.m_memoryChannelsNotes.TabIndex = 7;
            this.m_memoryChannelsNotes.TabStop = false;
            this.m_memoryChannelsNotes.Text = "Note: Saving to the default memory channel restores the camera to factory default" +
                "s.";
            // 
            // m_memoryChannelsLabel
            // 
            this.m_memoryChannelsLabel.AutoSize = true;
            this.m_memoryChannelsLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_memoryChannelsLabel.Location = new System.Drawing.Point(0, 0);
            this.m_memoryChannelsLabel.Name = "m_memoryChannelsLabel";
            this.m_memoryChannelsLabel.Size = new System.Drawing.Size(108, 13);
            this.m_memoryChannelsLabel.TabIndex = 4;
            this.m_memoryChannelsLabel.Text = "Memory Channels";
            // 
            // m_testPatternSelectionPanel
            // 
            this.m_testPatternSelectionPanel.Controls.Add(this.m_testPatternNoneRadioButton);
            this.m_testPatternSelectionPanel.Controls.Add(this.m_testPattern2RadioButton);
            this.m_testPatternSelectionPanel.Controls.Add(this.m_testPattern1RadioButton);
            this.m_testPatternSelectionPanel.Controls.Add(this.m_displayTestPatternLabel);
            this.m_testPatternSelectionPanel.Location = new System.Drawing.Point(7, 152);
            this.m_testPatternSelectionPanel.Name = "m_testPatternSelectionPanel";
            this.m_testPatternSelectionPanel.Size = new System.Drawing.Size(224, 88);
            this.m_testPatternSelectionPanel.TabIndex = 6;
            // 
            // m_testPatternNoneRadioButton
            // 
            this.m_testPatternNoneRadioButton.AutoSize = true;
            this.m_testPatternNoneRadioButton.Location = new System.Drawing.Point(8, 64);
            this.m_testPatternNoneRadioButton.Name = "m_testPatternNoneRadioButton";
            this.m_testPatternNoneRadioButton.Size = new System.Drawing.Size(51, 17);
            this.m_testPatternNoneRadioButton.TabIndex = 0;
            this.m_testPatternNoneRadioButton.TabStop = true;
            this.m_testPatternNoneRadioButton.Tag = "0";
            this.m_testPatternNoneRadioButton.Text = "None";
            this.m_testPatternNoneRadioButton.UseVisualStyleBackColor = true;
            this.m_testPatternNoneRadioButton.CheckedChanged += new System.EventHandler(this.OnTestPatternRadioButton_CheckedChanged);
            // 
            // m_testPattern2RadioButton
            // 
            this.m_testPattern2RadioButton.AutoSize = true;
            this.m_testPattern2RadioButton.Location = new System.Drawing.Point(8, 40);
            this.m_testPattern2RadioButton.Name = "m_testPattern2RadioButton";
            this.m_testPattern2RadioButton.Size = new System.Drawing.Size(68, 17);
            this.m_testPattern2RadioButton.TabIndex = 0;
            this.m_testPattern2RadioButton.TabStop = true;
            this.m_testPattern2RadioButton.Tag = "2";
            this.m_testPattern2RadioButton.Text = "Pattern 2";
            this.m_testPattern2RadioButton.UseVisualStyleBackColor = true;
            this.m_testPattern2RadioButton.CheckedChanged += new System.EventHandler(this.OnTestPatternRadioButton_CheckedChanged);
            // 
            // m_testPattern1RadioButton
            // 
            this.m_testPattern1RadioButton.AutoSize = true;
            this.m_testPattern1RadioButton.Location = new System.Drawing.Point(8, 16);
            this.m_testPattern1RadioButton.Name = "m_testPattern1RadioButton";
            this.m_testPattern1RadioButton.Size = new System.Drawing.Size(68, 17);
            this.m_testPattern1RadioButton.TabIndex = 0;
            this.m_testPattern1RadioButton.TabStop = true;
            this.m_testPattern1RadioButton.Tag = "1";
            this.m_testPattern1RadioButton.Text = "Pattern 1";
            this.m_testPattern1RadioButton.UseVisualStyleBackColor = true;
            this.m_testPattern1RadioButton.CheckedChanged += new System.EventHandler(this.OnTestPatternRadioButton_CheckedChanged);
            // 
            // m_displayTestPatternLabel
            // 
            this.m_displayTestPatternLabel.AutoSize = true;
            this.m_displayTestPatternLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_displayTestPatternLabel.Location = new System.Drawing.Point(0, 0);
            this.m_displayTestPatternLabel.Name = "m_displayTestPatternLabel";
            this.m_displayTestPatternLabel.Size = new System.Drawing.Size(122, 13);
            this.m_displayTestPatternLabel.TabIndex = 4;
            this.m_displayTestPatternLabel.Text = "Display Test Pattern";
            // 
            // m_y16EndiannessSelectionPanel
            // 
            this.m_y16EndiannessSelectionPanel.Controls.Add(this.m_y16LittleEndianRadioButton);
            this.m_y16EndiannessSelectionPanel.Controls.Add(this.m_y16BigEndianRadioButton);
            this.m_y16EndiannessSelectionPanel.Controls.Add(this.m_y16EndiannessLabel);
            this.m_y16EndiannessSelectionPanel.Location = new System.Drawing.Point(7, 80);
            this.m_y16EndiannessSelectionPanel.Name = "m_y16EndiannessSelectionPanel";
            this.m_y16EndiannessSelectionPanel.Size = new System.Drawing.Size(224, 64);
            this.m_y16EndiannessSelectionPanel.TabIndex = 5;
            // 
            // m_y16LittleEndianRadioButton
            // 
            this.m_y16LittleEndianRadioButton.AutoSize = true;
            this.m_y16LittleEndianRadioButton.Location = new System.Drawing.Point(8, 40);
            this.m_y16LittleEndianRadioButton.Name = "m_y16LittleEndianRadioButton";
            this.m_y16LittleEndianRadioButton.Size = new System.Drawing.Size(204, 17);
            this.m_y16LittleEndianRadioButton.TabIndex = 0;
            this.m_y16LittleEndianRadioButton.TabStop = true;
            this.m_y16LittleEndianRadioButton.Text = "Little endian (PGR-specific Y16 mode)";
            this.m_y16LittleEndianRadioButton.UseVisualStyleBackColor = true;
            this.m_y16LittleEndianRadioButton.CheckedChanged += new System.EventHandler(this.OnY16EndiannessRadioButtonCheckedChanged);
            // 
            // m_y16BigEndianRadioButton
            // 
            this.m_y16BigEndianRadioButton.AutoSize = true;
            this.m_y16BigEndianRadioButton.Location = new System.Drawing.Point(8, 16);
            this.m_y16BigEndianRadioButton.Name = "m_y16BigEndianRadioButton";
            this.m_y16BigEndianRadioButton.Size = new System.Drawing.Size(217, 17);
            this.m_y16BigEndianRadioButton.TabIndex = 0;
            this.m_y16BigEndianRadioButton.TabStop = true;
            this.m_y16BigEndianRadioButton.Text = "Big endian (IIDC 1394 DCAM Y16 mode)";
            this.m_y16BigEndianRadioButton.UseVisualStyleBackColor = true;
            this.m_y16BigEndianRadioButton.CheckedChanged += new System.EventHandler(this.OnY16EndiannessRadioButtonCheckedChanged);
            // 
            // m_y16EndiannessLabel
            // 
            this.m_y16EndiannessLabel.AutoSize = true;
            this.m_y16EndiannessLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_y16EndiannessLabel.Location = new System.Drawing.Point(0, 0);
            this.m_y16EndiannessLabel.Name = "m_y16EndiannessLabel";
            this.m_y16EndiannessLabel.Size = new System.Drawing.Size(94, 13);
            this.m_y16EndiannessLabel.TabIndex = 4;
            this.m_y16EndiannessLabel.Text = "Y16 Endianness";
            // 
            // m_rawBayerOutputHintTextLabel
            // 
            this.m_rawBayerOutputHintTextLabel.AutoSize = true;
            this.m_rawBayerOutputHintTextLabel.Location = new System.Drawing.Point(32, 35);
            this.m_rawBayerOutputHintTextLabel.Name = "m_rawBayerOutputHintTextLabel";
            this.m_rawBayerOutputHintTextLabel.Size = new System.Drawing.Size(108, 13);
            this.m_rawBayerOutputHintTextLabel.TabIndex = 1;
            this.m_rawBayerOutputHintTextLabel.Text = "(Only for Y8 and Y16)";
            // 
            // m_mirrorImageCheckBox
            // 
            this.m_mirrorImageCheckBox.AutoSize = true;
            this.m_mirrorImageCheckBox.Location = new System.Drawing.Point(16, 56);
            this.m_mirrorImageCheckBox.Name = "m_mirrorImageCheckBox";
            this.m_mirrorImageCheckBox.Size = new System.Drawing.Size(153, 17);
            this.m_mirrorImageCheckBox.TabIndex = 1;
            this.m_mirrorImageCheckBox.Text = "Mirror image (horizontal flip)";
            this.m_mirrorImageCheckBox.UseVisualStyleBackColor = true;
            this.m_mirrorImageCheckBox.CheckedChanged += new System.EventHandler(this.OnMirrorImageCheckedStatusChanged);
            // 
            // m_rawBayerOutputCheckBox
            // 
            this.m_rawBayerOutputCheckBox.AutoSize = true;
            this.m_rawBayerOutputCheckBox.Location = new System.Drawing.Point(16, 20);
            this.m_rawBayerOutputCheckBox.Name = "m_rawBayerOutputCheckBox";
            this.m_rawBayerOutputCheckBox.Size = new System.Drawing.Size(111, 17);
            this.m_rawBayerOutputCheckBox.TabIndex = 0;
            this.m_rawBayerOutputCheckBox.Text = "Raw Bayer output";
            this.m_rawBayerOutputCheckBox.UseVisualStyleBackColor = true;
            this.m_rawBayerOutputCheckBox.CheckedChanged += new System.EventHandler(this.RawBayerOutputCheckedStatusChanged);
            // 
            // m_IsochHelperLabel
            // 
            this.m_IsochHelperLabel.AutoSize = true;
            this.m_IsochHelperLabel.Location = new System.Drawing.Point(94, 75);
            this.m_IsochHelperLabel.Name = "m_IsochHelperLabel";
            this.m_IsochHelperLabel.Size = new System.Drawing.Size(101, 13);
            this.m_IsochHelperLabel.TabIndex = 15;
            this.m_IsochHelperLabel.Text = "Camera is streaming";
            // 
            // AdvCameraSettingsPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "AdvCameraSettingsPage";
            this.Size = new System.Drawing.Size(474, 498);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_mainGroupBox.PerformLayout();
            this.m_speedControlPanel.ResumeLayout(false);
            this.m_speedControlPanel.PerformLayout();
            this.m_embedImageInformationControlPanel.ResumeLayout(false);
            this.m_embedImageInformationControlPanel.PerformLayout();
            this.m_gigEPacketResendControlPanel.ResumeLayout(false);
            this.m_gigEPacketResendControlPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_packetResendMaxPacketToResendSpinButton)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_packetResendTimeoutSpinButton)).EndInit();
            this.m_autoRangeControlPanel.ResumeLayout(false);
            this.m_autoRangeControlPanel.PerformLayout();
            this.m_memoryChannelControlPanel.ResumeLayout(false);
            this.m_memoryChannelControlPanel.PerformLayout();
            this.m_testPatternSelectionPanel.ResumeLayout(false);
            this.m_testPatternSelectionPanel.PerformLayout();
            this.m_y16EndiannessSelectionPanel.ResumeLayout(false);
            this.m_y16EndiannessSelectionPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.CheckBox m_rawBayerOutputCheckBox;
        private System.Windows.Forms.Label m_rawBayerOutputHintTextLabel;
        private System.Windows.Forms.CheckBox m_mirrorImageCheckBox;
        private System.Windows.Forms.Panel m_y16EndiannessSelectionPanel;
        private System.Windows.Forms.RadioButton m_y16LittleEndianRadioButton;
        private System.Windows.Forms.RadioButton m_y16BigEndianRadioButton;
        private System.Windows.Forms.Label m_y16EndiannessLabel;
        private System.Windows.Forms.Panel m_testPatternSelectionPanel;
        private System.Windows.Forms.RadioButton m_testPatternNoneRadioButton;
        private System.Windows.Forms.RadioButton m_testPattern2RadioButton;
        private System.Windows.Forms.RadioButton m_testPattern1RadioButton;
        private System.Windows.Forms.Label m_displayTestPatternLabel;
        private System.Windows.Forms.TextBox m_embeddedImageInfoDescriptionTextBox;
        private System.Windows.Forms.Label m_embeddedImageInfoLabel;
        private System.Windows.Forms.Button m_unselectAllEmbeddedImageInfoButton;
        private System.Windows.Forms.Button m_selectAllEmbeddedImageInfoButton;
        private System.Windows.Forms.Panel m_embeddedImageInfoSelectionPanel;
        private System.Windows.Forms.Panel m_memoryChannelControlPanel;
        private System.Windows.Forms.Label m_memoryChannelsLabel;
        private System.Windows.Forms.Label m_channelLabel;
        private System.Windows.Forms.ComboBox m_memoryChannelsComboBox;
        private System.Windows.Forms.Button m_memoryChannelsRestoreButton;
        private System.Windows.Forms.Button m_memoryChannelsSaveButton;
        private System.Windows.Forms.TextBox m_memoryChannelsNotes;
        private System.Windows.Forms.Panel m_autoRangeControlPanel;
        private System.Windows.Forms.Label m_autoRangePropertyLabel;
        private System.Windows.Forms.Label m_autoRangeLabel;
        private System.Windows.Forms.ComboBox m_autoRangePropertyComboBox;
        private System.Windows.Forms.Label m_autoRangeMaxLabel;
        private System.Windows.Forms.Label m_autoRangeMinLabel;
        private System.Windows.Forms.TextBox m_autoRangeMaxTextBox;
        private System.Windows.Forms.TextBox m_autoRangeMinTextBox;
        private System.Windows.Forms.Button m_getAutoRangeValueButton;
        private System.Windows.Forms.Button m_setAutoRangeValueButton;
        private System.Windows.Forms.Label m_gigEPacketResendLabel;
        private System.Windows.Forms.Panel m_gigEPacketResendControlPanel;
        private System.Windows.Forms.Label m_timeoutLabel;
        private System.Windows.Forms.CheckBox m_enableGigEPacketResendCheckBox;
        private System.Windows.Forms.NumericUpDown m_packetResendMaxPacketToResendSpinButton;
        private System.Windows.Forms.NumericUpDown m_packetResendTimeoutSpinButton;
        private System.Windows.Forms.Button m_packetResendLoadButton;
        private System.Windows.Forms.Button m_packetResendSaveButton;
        private System.Windows.Forms.Label m_maxPacketToResendLabel;
        private System.Windows.Forms.Panel m_embedImageInformationControlPanel;
        private System.Windows.Forms.Panel m_speedControlPanel;
        private System.Windows.Forms.Label m_busSpeedControlLabel;
        private System.Windows.Forms.Label m_AsyncSpeedLabel;
        private System.Windows.Forms.ComboBox m_AsyncSpeedCombo;
        private System.Windows.Forms.Label m_IsochSpeedLabel;
        private System.Windows.Forms.ComboBox m_IsochSpeedCombo;
        private System.Windows.Forms.Label m_IsochHelperLabel;
        private System.Windows.Forms.Label m_pktResendEnableLabel;
    }
}
