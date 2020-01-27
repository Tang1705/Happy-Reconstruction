namespace FlyCap2CameraControl
{
    partial class HDRPropertyControl
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
            this.m_propertyControlLabel = new System.Windows.Forms.Label();
            this.m_gainTrackbar = new System.Windows.Forms.TrackBar();
            this.m_gainLabel = new System.Windows.Forms.Label();
            this.m_gainValue = new System.Windows.Forms.Label();
            this.m_shutterTrackbar = new System.Windows.Forms.TrackBar();
            this.m_shutterLabel = new System.Windows.Forms.Label();
            this.m_shutterValue = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_gainTrackbar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_shutterTrackbar)).BeginInit();
            this.SuspendLayout();
            // 
            // m_propertyControlLabel
            // 
            this.m_propertyControlLabel.AutoSize = true;
            this.m_propertyControlLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_propertyControlLabel.Location = new System.Drawing.Point(3, 0);
            this.m_propertyControlLabel.Name = "m_propertyControlLabel";
            this.m_propertyControlLabel.Size = new System.Drawing.Size(74, 13);
            this.m_propertyControlLabel.TabIndex = 4;
            this.m_propertyControlLabel.Text = "HDR Image:";
            // 
            // m_gainTrackbar
            // 
            this.m_gainTrackbar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_gainTrackbar.LargeChange = 50;
            this.m_gainTrackbar.Location = new System.Drawing.Point(59, 19);
            this.m_gainTrackbar.Maximum = 1000;
            this.m_gainTrackbar.Name = "m_gainTrackbar";
            this.m_gainTrackbar.Size = new System.Drawing.Size(299, 40);
            this.m_gainTrackbar.TabIndex = 5;
            this.m_gainTrackbar.TickFrequency = 100;
            this.m_gainTrackbar.TickStyle = System.Windows.Forms.TickStyle.None;
            this.m_gainTrackbar.Scroll += new System.EventHandler(this.OnGainTrackbarScroll);
            // 
            // m_gainLabel
            // 
            this.m_gainLabel.AutoSize = true;
            this.m_gainLabel.Location = new System.Drawing.Point(14, 23);
            this.m_gainLabel.Name = "m_gainLabel";
            this.m_gainLabel.Size = new System.Drawing.Size(32, 13);
            this.m_gainLabel.TabIndex = 6;
            this.m_gainLabel.Text = "Gain:";
            // 
            // m_gainValue
            // 
            this.m_gainValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_gainValue.AutoSize = true;
            this.m_gainValue.Location = new System.Drawing.Point(359, 24);
            this.m_gainValue.Name = "m_gainValue";
            this.m_gainValue.Size = new System.Drawing.Size(34, 13);
            this.m_gainValue.TabIndex = 7;
            this.m_gainValue.Text = "Value";
            // 
            // m_shutterTrackbar
            // 
            this.m_shutterTrackbar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_shutterTrackbar.LargeChange = 50;
            this.m_shutterTrackbar.Location = new System.Drawing.Point(59, 43);
            this.m_shutterTrackbar.Maximum = 1000;
            this.m_shutterTrackbar.Name = "m_shutterTrackbar";
            this.m_shutterTrackbar.Size = new System.Drawing.Size(299, 40);
            this.m_shutterTrackbar.TabIndex = 6;
            this.m_shutterTrackbar.TickFrequency = 100;
            this.m_shutterTrackbar.TickStyle = System.Windows.Forms.TickStyle.None;
            this.m_shutterTrackbar.Scroll += new System.EventHandler(this.OnShutterTrackbarScroll);
            // 
            // m_shutterLabel
            // 
            this.m_shutterLabel.AutoSize = true;
            this.m_shutterLabel.Location = new System.Drawing.Point(14, 47);
            this.m_shutterLabel.Name = "m_shutterLabel";
            this.m_shutterLabel.Size = new System.Drawing.Size(44, 13);
            this.m_shutterLabel.TabIndex = 6;
            this.m_shutterLabel.Text = "Shutter:";
            // 
            // m_shutterValue
            // 
            this.m_shutterValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_shutterValue.AutoSize = true;
            this.m_shutterValue.Location = new System.Drawing.Point(359, 48);
            this.m_shutterValue.Name = "m_shutterValue";
            this.m_shutterValue.Size = new System.Drawing.Size(34, 13);
            this.m_shutterValue.TabIndex = 7;
            this.m_shutterValue.Text = "Value";
            // 
            // HDRPropertyControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_shutterValue);
            this.Controls.Add(this.m_gainValue);
            this.Controls.Add(this.m_shutterLabel);
            this.Controls.Add(this.m_gainLabel);
            this.Controls.Add(this.m_shutterTrackbar);
            this.Controls.Add(this.m_gainTrackbar);
            this.Controls.Add(this.m_propertyControlLabel);
            this.Name = "HDRPropertyControl";
            this.Size = new System.Drawing.Size(400, 80);
            ((System.ComponentModel.ISupportInitialize)(this.m_gainTrackbar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_shutterTrackbar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label m_propertyControlLabel;
        private System.Windows.Forms.TrackBar m_gainTrackbar;
        private System.Windows.Forms.Label m_gainLabel;
        private System.Windows.Forms.Label m_gainValue;
        private System.Windows.Forms.TrackBar m_shutterTrackbar;
        private System.Windows.Forms.Label m_shutterLabel;
        private System.Windows.Forms.Label m_shutterValue;
    }
}
