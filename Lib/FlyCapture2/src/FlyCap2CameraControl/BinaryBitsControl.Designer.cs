namespace FlyCap2CameraControl
{
    partial class BinaryBitsControl
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
            this.m_regValTextBox = new System.Windows.Forms.TextBox();
            this.m_relatedLocationLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // m_regValTextBox
            // 
            this.m_regValTextBox.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.m_regValTextBox.Location = new System.Drawing.Point(16, 3);
            this.m_regValTextBox.MaxLength = 2;
            this.m_regValTextBox.Name = "m_regValTextBox";
            this.m_regValTextBox.Size = new System.Drawing.Size(40, 20);
            this.m_regValTextBox.TabIndex = 11;
            this.m_regValTextBox.Text = "00";
            this.m_regValTextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.m_regValTextBox.TextChanged += new System.EventHandler(this.OnRegisterValueTextChanged);
            // 
            // m_relatedLocationLabel
            // 
            this.m_relatedLocationLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.m_relatedLocationLabel.Location = new System.Drawing.Point(0, 40);
            this.m_relatedLocationLabel.Name = "m_relatedLocationLabel";
            this.m_relatedLocationLabel.Size = new System.Drawing.Size(72, 16);
            this.m_relatedLocationLabel.TabIndex = 12;
            this.m_relatedLocationLabel.Text = "start - end";
            this.m_relatedLocationLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // BinaryBitsControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_relatedLocationLabel);
            this.Controls.Add(this.m_regValTextBox);
            this.Name = "BinaryBitsControl";
            this.Size = new System.Drawing.Size(70, 54);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox m_regValTextBox;
        private System.Windows.Forms.Label m_relatedLocationLabel;

    }
}
