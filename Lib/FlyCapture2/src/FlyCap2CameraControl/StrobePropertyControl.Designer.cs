namespace FlyCap2CameraControl
{
    partial class StrobePropertyControl
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
            this.m_controlGroupBox = new System.Windows.Forms.GroupBox();
            this.m_polarityLabel = new System.Windows.Forms.Label();
            this.m_lowPolarityButton = new System.Windows.Forms.RadioButton();
            this.m_highPolarityButton = new System.Windows.Forms.RadioButton();
            this.m_durationLabel = new System.Windows.Forms.Label();
            this.m_delayLabel = new System.Windows.Forms.Label();
            this.m_durationSpinButton = new System.Windows.Forms.NumericUpDown();
            this.m_delaySpinButton = new System.Windows.Forms.NumericUpDown();
            this.m_enableStrobeCheckbox = new System.Windows.Forms.CheckBox();
            this.m_controlGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_durationSpinButton)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_delaySpinButton)).BeginInit();
            this.SuspendLayout();
            // 
            // m_controlGroupBox
            // 
            this.m_controlGroupBox.Controls.Add(this.m_polarityLabel);
            this.m_controlGroupBox.Controls.Add(this.m_lowPolarityButton);
            this.m_controlGroupBox.Controls.Add(this.m_highPolarityButton);
            this.m_controlGroupBox.Controls.Add(this.m_durationLabel);
            this.m_controlGroupBox.Controls.Add(this.m_delayLabel);
            this.m_controlGroupBox.Controls.Add(this.m_durationSpinButton);
            this.m_controlGroupBox.Controls.Add(this.m_delaySpinButton);
            this.m_controlGroupBox.Controls.Add(this.m_enableStrobeCheckbox);
            this.m_controlGroupBox.Location = new System.Drawing.Point(4, 4);
            this.m_controlGroupBox.Name = "m_controlGroupBox";
            this.m_controlGroupBox.Size = new System.Drawing.Size(213, 73);
            this.m_controlGroupBox.TabIndex = 0;
            this.m_controlGroupBox.TabStop = false;
            this.m_controlGroupBox.Text = "GPIO Title";
            // 
            // m_polarityLabel
            // 
            this.m_polarityLabel.AutoSize = true;
            this.m_polarityLabel.Location = new System.Drawing.Point(6, 41);
            this.m_polarityLabel.Name = "m_polarityLabel";
            this.m_polarityLabel.Size = new System.Drawing.Size(41, 13);
            this.m_polarityLabel.TabIndex = 4;
            this.m_polarityLabel.Text = "Polarity";
            // 
            // m_lowPolarityButton
            // 
            this.m_lowPolarityButton.AutoSize = true;
            this.m_lowPolarityButton.Location = new System.Drawing.Point(52, 49);
            this.m_lowPolarityButton.Name = "m_lowPolarityButton";
            this.m_lowPolarityButton.Size = new System.Drawing.Size(45, 17);
            this.m_lowPolarityButton.TabIndex = 2;
            this.m_lowPolarityButton.TabStop = true;
            this.m_lowPolarityButton.Text = "Low";
            this.m_lowPolarityButton.UseVisualStyleBackColor = true;
            // 
            // m_highPolarityButton
            // 
            this.m_highPolarityButton.AutoSize = true;
            this.m_highPolarityButton.Location = new System.Drawing.Point(52, 30);
            this.m_highPolarityButton.Name = "m_highPolarityButton";
            this.m_highPolarityButton.Size = new System.Drawing.Size(47, 17);
            this.m_highPolarityButton.TabIndex = 1;
            this.m_highPolarityButton.TabStop = true;
            this.m_highPolarityButton.Text = "High";
            this.m_highPolarityButton.UseVisualStyleBackColor = true;
            // 
            // m_durationLabel
            // 
            this.m_durationLabel.AutoSize = true;
            this.m_durationLabel.Location = new System.Drawing.Point(97, 51);
            this.m_durationLabel.Name = "m_durationLabel";
            this.m_durationLabel.Size = new System.Drawing.Size(50, 13);
            this.m_durationLabel.TabIndex = 2;
            this.m_durationLabel.Text = "Duration:";
            // 
            // m_delayLabel
            // 
            this.m_delayLabel.AutoSize = true;
            this.m_delayLabel.Location = new System.Drawing.Point(97, 32);
            this.m_delayLabel.Name = "m_delayLabel";
            this.m_delayLabel.Size = new System.Drawing.Size(37, 13);
            this.m_delayLabel.TabIndex = 2;
            this.m_delayLabel.Text = "Delay:";
            // 
            // m_durationSpinButton
            // 
            this.m_durationSpinButton.DecimalPlaces = 2;
            this.m_durationSpinButton.Location = new System.Drawing.Point(153, 49);
            this.m_durationSpinButton.Name = "m_durationSpinButton";
            this.m_durationSpinButton.Size = new System.Drawing.Size(53, 20);
            this.m_durationSpinButton.TabIndex = 4;
            // 
            // m_delaySpinButton
            // 
            this.m_delaySpinButton.DecimalPlaces = 2;
            this.m_delaySpinButton.Location = new System.Drawing.Point(153, 28);
            this.m_delaySpinButton.Name = "m_delaySpinButton";
            this.m_delaySpinButton.Size = new System.Drawing.Size(53, 20);
            this.m_delaySpinButton.TabIndex = 3;
            // 
            // m_enableStrobeCheckbox
            // 
            this.m_enableStrobeCheckbox.AutoSize = true;
            this.m_enableStrobeCheckbox.Location = new System.Drawing.Point(6, 12);
            this.m_enableStrobeCheckbox.Name = "m_enableStrobeCheckbox";
            this.m_enableStrobeCheckbox.Size = new System.Drawing.Size(142, 17);
            this.m_enableStrobeCheckbox.TabIndex = 0;
            this.m_enableStrobeCheckbox.Text = "Enable strobe for this pin";
            this.m_enableStrobeCheckbox.UseVisualStyleBackColor = true;
            // 
            // StrobePropertyControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_controlGroupBox);
            this.Name = "StrobePropertyControl";
            this.Size = new System.Drawing.Size(220, 80);
            this.m_controlGroupBox.ResumeLayout(false);
            this.m_controlGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_durationSpinButton)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_delaySpinButton)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_controlGroupBox;
        private System.Windows.Forms.NumericUpDown m_durationSpinButton;
        private System.Windows.Forms.NumericUpDown m_delaySpinButton;
        private System.Windows.Forms.CheckBox m_enableStrobeCheckbox;
        private System.Windows.Forms.RadioButton m_lowPolarityButton;
        private System.Windows.Forms.RadioButton m_highPolarityButton;
        private System.Windows.Forms.Label m_durationLabel;
        private System.Windows.Forms.Label m_delayLabel;
        private System.Windows.Forms.Label m_polarityLabel;
    }
}
