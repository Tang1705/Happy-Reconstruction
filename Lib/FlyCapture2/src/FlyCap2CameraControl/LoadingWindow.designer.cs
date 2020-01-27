namespace FlyCap2CameraControl
{
    partial class LoadingWindow
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
            this.m_loadingProgressBar = new System.Windows.Forms.ProgressBar();
            this.m_loadingInformationLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // m_loadingProgressBar
            // 
            this.m_loadingProgressBar.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_loadingProgressBar.Location = new System.Drawing.Point(12, 12);
            this.m_loadingProgressBar.Name = "m_loadingProgressBar";
            this.m_loadingProgressBar.Size = new System.Drawing.Size(568, 26);
            this.m_loadingProgressBar.TabIndex = 0;
            // 
            // m_loadingInformationLabel
            // 
            this.m_loadingInformationLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.m_loadingInformationLabel.AutoSize = true;
            this.m_loadingInformationLabel.Location = new System.Drawing.Point(13, 45);
            this.m_loadingInformationLabel.Name = "m_loadingInformationLabel";
            this.m_loadingInformationLabel.Size = new System.Drawing.Size(109, 13);
            this.m_loadingInformationLabel.TabIndex = 1;
            this.m_loadingInformationLabel.Text = "Loading Information...";
            // 
            // LoadingWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(592, 66);
            this.Controls.Add(this.m_loadingInformationLabel);
            this.Controls.Add(this.m_loadingProgressBar);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(600, 100);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(600, 100);
            this.Name = "LoadingWindow";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Loading...";
            this.TopMost = true;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ProgressBar m_loadingProgressBar;
        private System.Windows.Forms.Label m_loadingInformationLabel;
    }
}