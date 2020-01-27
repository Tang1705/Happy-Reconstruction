namespace FlyCap2CameraControl
{
    partial class CameraSettingsPage
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
            this.m_onePushLabel = new System.Windows.Forms.Label();
            this.m_onOffLabel = new System.Windows.Forms.Label();
            this.m_autoLabel = new System.Windows.Forms.Label();
            this.m_absoluteModeCheckBox = new System.Windows.Forms.CheckBox();
            this.m_powerCheckBox = new System.Windows.Forms.CheckBox();
            this.m_temperatureLabel = new System.Windows.Forms.Label();
            this.m_temperatureValue = new System.Windows.Forms.Label();
            this.m_mainGroupBox = new System.Windows.Forms.GroupBox();
            this.SuspendLayout();
            // 
            // m_onePushLabel
            // 
            this.m_onePushLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_onePushLabel.AutoSize = true;
            this.m_onePushLabel.Location = new System.Drawing.Point(403, 24);
            this.m_onePushLabel.Name = "m_onePushLabel";
            this.m_onePushLabel.Size = new System.Drawing.Size(54, 13);
            this.m_onePushLabel.TabIndex = 4;
            this.m_onePushLabel.Text = "One Push";
            // 
            // m_onOffLabel
            // 
            this.m_onOffLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_onOffLabel.AutoSize = true;
            this.m_onOffLabel.Location = new System.Drawing.Point(363, 24);
            this.m_onOffLabel.Name = "m_onOffLabel";
            this.m_onOffLabel.Size = new System.Drawing.Size(40, 13);
            this.m_onOffLabel.TabIndex = 4;
            this.m_onOffLabel.Text = "On/Off";
            // 
            // m_autoLabel
            // 
            this.m_autoLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_autoLabel.AutoSize = true;
            this.m_autoLabel.Location = new System.Drawing.Point(320, 24);
            this.m_autoLabel.Name = "m_autoLabel";
            this.m_autoLabel.Size = new System.Drawing.Size(29, 13);
            this.m_autoLabel.TabIndex = 4;
            this.m_autoLabel.Text = "Auto";
            // 
            // m_absoluteModeCheckBox
            // 
            this.m_absoluteModeCheckBox.AutoSize = true;
            this.m_absoluteModeCheckBox.Location = new System.Drawing.Point(6, 19);
            this.m_absoluteModeCheckBox.Name = "m_absoluteModeCheckBox";
            this.m_absoluteModeCheckBox.Size = new System.Drawing.Size(97, 17);
            this.m_absoluteModeCheckBox.TabIndex = 0;
            this.m_absoluteModeCheckBox.Text = "Absolute Mode";
            this.m_absoluteModeCheckBox.UseVisualStyleBackColor = true;
            // 
            // m_powerCheckBox
            // 
            this.m_powerCheckBox.Location = new System.Drawing.Point(0, 0);
            this.m_powerCheckBox.Name = "m_powerCheckBox";
            this.m_powerCheckBox.Size = new System.Drawing.Size(104, 24);
            this.m_powerCheckBox.TabIndex = 0;
            // 
            // m_temperatureLabel
            // 
            this.m_temperatureLabel.Location = new System.Drawing.Point(0, 0);
            this.m_temperatureLabel.Name = "m_temperatureLabel";
            this.m_temperatureLabel.Size = new System.Drawing.Size(100, 23);
            this.m_temperatureLabel.TabIndex = 0;
            // 
            // m_temperatureValue
            // 
            this.m_temperatureValue.Location = new System.Drawing.Point(0, 0);
            this.m_temperatureValue.Name = "m_temperatureValue";
            this.m_temperatureValue.Size = new System.Drawing.Size(100, 23);
            this.m_temperatureValue.TabIndex = 0;
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(471, 435);
            this.m_mainGroupBox.TabIndex = 0;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Camera Settings";
            // 
            // CameraSettingsPage
            // 
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "CameraSettingsPage";
            this.Size = new System.Drawing.Size(474, 438);
            this.ResumeLayout(false);

        }
        #endregion


        private System.Windows.Forms.CheckBox m_absoluteModeCheckBox;

        private System.Windows.Forms.Label m_onePushLabel;
        private System.Windows.Forms.Label m_onOffLabel;
        private System.Windows.Forms.Label m_autoLabel;
        private System.Windows.Forms.CheckBox m_powerCheckBox;
        private System.Windows.Forms.Label m_temperatureLabel;
        private System.Windows.Forms.Label m_temperatureValue;
        private System.Windows.Forms.GroupBox m_mainGroupBox;
    }
}
