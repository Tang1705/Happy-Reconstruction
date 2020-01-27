namespace FlyCap2CameraControl
{
    partial class DataFlashPage
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
            this.m_progressText = new System.Windows.Forms.Label();
            this.m_operationProgressBar = new System.Windows.Forms.ProgressBar();
            this.m_flashDataPreviewPanel = new System.Windows.Forms.Panel();
            this.m_refreshPreviewButton = new System.Windows.Forms.Button();
            this.m_flashDataPreviewTextbox = new System.Windows.Forms.TextBox();
            this.m_operationsControlPanel = new System.Windows.Forms.Panel();
            this.m_eraseFlashButton = new System.Windows.Forms.Button();
            this.m_flashToFileButton = new System.Windows.Forms.Button();
            this.m_fileToFlashButton = new System.Windows.Forms.Button();
            this.m_previewLabel = new System.Windows.Forms.Label();
            this.m_progressLabel = new System.Windows.Forms.Label();
            this.m_operationsLabel = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.m_dataFlashSizeValue = new System.Windows.Forms.Label();
            this.m_dataFlashSizeLabel = new System.Windows.Forms.Label();
            this.m_statusValue = new System.Windows.Forms.Label();
            this.m_statusLabel = new System.Windows.Forms.Label();
            this.m_saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.m_openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.m_mainGroupBox.SuspendLayout();
            this.m_flashDataPreviewPanel.SuspendLayout();
            this.m_operationsControlPanel.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_progressText);
            this.m_mainGroupBox.Controls.Add(this.m_operationProgressBar);
            this.m_mainGroupBox.Controls.Add(this.m_flashDataPreviewPanel);
            this.m_mainGroupBox.Controls.Add(this.m_operationsControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_previewLabel);
            this.m_mainGroupBox.Controls.Add(this.m_progressLabel);
            this.m_mainGroupBox.Controls.Add(this.m_operationsLabel);
            this.m_mainGroupBox.Controls.Add(this.tableLayoutPanel1);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(471, 435);
            this.m_mainGroupBox.TabIndex = 6;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Data Flash";
            // 
            // m_progressText
            // 
            this.m_progressText.Location = new System.Drawing.Point(13, 161);
            this.m_progressText.Name = "m_progressText";
            this.m_progressText.Size = new System.Drawing.Size(362, 13);
            this.m_progressText.TabIndex = 7;
            this.m_progressText.Text = "Progress status is shown here.";
            this.m_progressText.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.m_progressText.Visible = false;
            // 
            // m_operationProgressBar
            // 
            this.m_operationProgressBar.Location = new System.Drawing.Point(12, 135);
            this.m_operationProgressBar.Name = "m_operationProgressBar";
            this.m_operationProgressBar.Size = new System.Drawing.Size(366, 23);
            this.m_operationProgressBar.TabIndex = 6;
            // 
            // m_flashDataPreviewPanel
            // 
            this.m_flashDataPreviewPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_flashDataPreviewPanel.Controls.Add(this.m_refreshPreviewButton);
            this.m_flashDataPreviewPanel.Controls.Add(this.m_flashDataPreviewTextbox);
            this.m_flashDataPreviewPanel.Location = new System.Drawing.Point(12, 199);
            this.m_flashDataPreviewPanel.Name = "m_flashDataPreviewPanel";
            this.m_flashDataPreviewPanel.Size = new System.Drawing.Size(366, 219);
            this.m_flashDataPreviewPanel.TabIndex = 5;
            // 
            // m_refreshPreviewButton
            // 
            this.m_refreshPreviewButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_refreshPreviewButton.Location = new System.Drawing.Point(1, 193);
            this.m_refreshPreviewButton.Name = "m_refreshPreviewButton";
            this.m_refreshPreviewButton.Size = new System.Drawing.Size(362, 23);
            this.m_refreshPreviewButton.TabIndex = 1;
            this.m_refreshPreviewButton.Text = "Refresh   preview";
            this.m_refreshPreviewButton.UseVisualStyleBackColor = true;
            this.m_refreshPreviewButton.Click += new System.EventHandler(this.OnRefreshPreviewButtonClick);
            // 
            // m_flashDataPreviewTextbox
            // 
            this.m_flashDataPreviewTextbox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_flashDataPreviewTextbox.BackColor = System.Drawing.Color.White;
            this.m_flashDataPreviewTextbox.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_flashDataPreviewTextbox.Location = new System.Drawing.Point(0, 3);
            this.m_flashDataPreviewTextbox.Multiline = true;
            this.m_flashDataPreviewTextbox.Name = "m_flashDataPreviewTextbox";
            this.m_flashDataPreviewTextbox.ReadOnly = true;
            this.m_flashDataPreviewTextbox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.m_flashDataPreviewTextbox.Size = new System.Drawing.Size(363, 184);
            this.m_flashDataPreviewTextbox.TabIndex = 0;
            this.m_flashDataPreviewTextbox.TabStop = false;
            // 
            // m_operationsControlPanel
            // 
            this.m_operationsControlPanel.Controls.Add(this.m_eraseFlashButton);
            this.m_operationsControlPanel.Controls.Add(this.m_flashToFileButton);
            this.m_operationsControlPanel.Controls.Add(this.m_fileToFlashButton);
            this.m_operationsControlPanel.Location = new System.Drawing.Point(12, 70);
            this.m_operationsControlPanel.Name = "m_operationsControlPanel";
            this.m_operationsControlPanel.Size = new System.Drawing.Size(372, 39);
            this.m_operationsControlPanel.TabIndex = 1;
            // 
            // m_eraseFlashButton
            // 
            this.m_eraseFlashButton.Location = new System.Drawing.Point(283, 7);
            this.m_eraseFlashButton.Name = "m_eraseFlashButton";
            this.m_eraseFlashButton.Size = new System.Drawing.Size(80, 25);
            this.m_eraseFlashButton.TabIndex = 3;
            this.m_eraseFlashButton.Tag = "EraseFlash";
            this.m_eraseFlashButton.Text = "Erase Flash";
            this.m_eraseFlashButton.UseVisualStyleBackColor = true;
            this.m_eraseFlashButton.Click += new System.EventHandler(this.OnEraseFlashButtonClick);
            // 
            // m_flashToFileButton
            // 
            this.m_flashToFileButton.Location = new System.Drawing.Point(1, 7);
            this.m_flashToFileButton.Name = "m_flashToFileButton";
            this.m_flashToFileButton.Size = new System.Drawing.Size(80, 25);
            this.m_flashToFileButton.TabIndex = 0;
            this.m_flashToFileButton.Tag = "FlashToFile";
            this.m_flashToFileButton.Text = "Flash -> File";
            this.m_flashToFileButton.UseVisualStyleBackColor = true;
            this.m_flashToFileButton.Click += new System.EventHandler(this.OnFlashToFileButtonClick);
            // 
            // m_fileToFlashButton
            // 
            this.m_fileToFlashButton.Location = new System.Drawing.Point(143, 7);
            this.m_fileToFlashButton.Name = "m_fileToFlashButton";
            this.m_fileToFlashButton.Size = new System.Drawing.Size(80, 25);
            this.m_fileToFlashButton.TabIndex = 2;
            this.m_fileToFlashButton.Tag = "FileToFlash";
            this.m_fileToFlashButton.Text = "File -> Flash";
            this.m_fileToFlashButton.UseVisualStyleBackColor = true;
            this.m_fileToFlashButton.Click += new System.EventHandler(this.OnFileToFlashButtonClick);
            // 
            // m_previewLabel
            // 
            this.m_previewLabel.AutoSize = true;
            this.m_previewLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_previewLabel.Location = new System.Drawing.Point(6, 181);
            this.m_previewLabel.Name = "m_previewLabel";
            this.m_previewLabel.Size = new System.Drawing.Size(52, 13);
            this.m_previewLabel.TabIndex = 4;
            this.m_previewLabel.Text = "Preview";
            // 
            // m_progressLabel
            // 
            this.m_progressLabel.AutoSize = true;
            this.m_progressLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_progressLabel.Location = new System.Drawing.Point(6, 120);
            this.m_progressLabel.Name = "m_progressLabel";
            this.m_progressLabel.Size = new System.Drawing.Size(57, 13);
            this.m_progressLabel.TabIndex = 4;
            this.m_progressLabel.Text = "Progress";
            // 
            // m_operationsLabel
            // 
            this.m_operationsLabel.AutoSize = true;
            this.m_operationsLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_operationsLabel.Location = new System.Drawing.Point(6, 56);
            this.m_operationsLabel.Name = "m_operationsLabel";
            this.m_operationsLabel.Size = new System.Drawing.Size(69, 13);
            this.m_operationsLabel.TabIndex = 4;
            this.m_operationsLabel.Text = "Operations";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.m_dataFlashSizeValue, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_dataFlashSizeLabel, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.m_statusValue, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.m_statusLabel, 0, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(6, 19);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(445, 29);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // m_dataFlashSizeValue
            // 
            this.m_dataFlashSizeValue.AutoSize = true;
            this.m_dataFlashSizeValue.Location = new System.Drawing.Point(88, 13);
            this.m_dataFlashSizeValue.Name = "m_dataFlashSizeValue";
            this.m_dataFlashSizeValue.Size = new System.Drawing.Size(30, 13);
            this.m_dataFlashSizeValue.TabIndex = 3;
            this.m_dataFlashSizeValue.Text = "0 KB";
            // 
            // m_dataFlashSizeLabel
            // 
            this.m_dataFlashSizeLabel.AutoSize = true;
            this.m_dataFlashSizeLabel.Location = new System.Drawing.Point(3, 13);
            this.m_dataFlashSizeLabel.Name = "m_dataFlashSizeLabel";
            this.m_dataFlashSizeLabel.Size = new System.Drawing.Size(79, 13);
            this.m_dataFlashSizeLabel.TabIndex = 2;
            this.m_dataFlashSizeLabel.Text = "Data flash size:";
            // 
            // m_statusValue
            // 
            this.m_statusValue.AutoSize = true;
            this.m_statusValue.Location = new System.Drawing.Point(88, 0);
            this.m_statusValue.Name = "m_statusValue";
            this.m_statusValue.Size = new System.Drawing.Size(69, 13);
            this.m_statusValue.TabIndex = 1;
            this.m_statusValue.Text = "Not available";
            // 
            // m_statusLabel
            // 
            this.m_statusLabel.AutoSize = true;
            this.m_statusLabel.Location = new System.Drawing.Point(3, 0);
            this.m_statusLabel.Name = "m_statusLabel";
            this.m_statusLabel.Size = new System.Drawing.Size(43, 13);
            this.m_statusLabel.TabIndex = 0;
            this.m_statusLabel.Text = "Status: ";
            // 
            // m_saveFileDialog
            // 
            this.m_saveFileDialog.Filter = "Data flash files (*.dat)|*.dat";
            // 
            // m_openFileDialog
            // 
            this.m_openFileDialog.Filter = "Data flash files (*.dat)|*.dat";
            // 
            // DataFlashPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "DataFlashPage";
            this.Size = new System.Drawing.Size(474, 438);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_mainGroupBox.PerformLayout();
            this.m_flashDataPreviewPanel.ResumeLayout(false);
            this.m_flashDataPreviewPanel.PerformLayout();
            this.m_operationsControlPanel.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label m_dataFlashSizeValue;
        private System.Windows.Forms.Label m_dataFlashSizeLabel;
        private System.Windows.Forms.Label m_statusValue;
        private System.Windows.Forms.Label m_statusLabel;
        private System.Windows.Forms.Label m_operationsLabel;
        private System.Windows.Forms.ProgressBar m_operationProgressBar;
        private System.Windows.Forms.Panel m_flashDataPreviewPanel;
        private System.Windows.Forms.Panel m_operationsControlPanel;
        private System.Windows.Forms.Label m_previewLabel;
        private System.Windows.Forms.Label m_progressLabel;
        private System.Windows.Forms.Button m_fileToFlashButton;
        private System.Windows.Forms.Button m_eraseFlashButton;
        private System.Windows.Forms.Button m_flashToFileButton;
        private System.Windows.Forms.Button m_refreshPreviewButton;
        private System.Windows.Forms.TextBox m_flashDataPreviewTextbox;
        private System.Windows.Forms.SaveFileDialog m_saveFileDialog;
        private System.Windows.Forms.OpenFileDialog m_openFileDialog;
        private System.Windows.Forms.Label m_progressText;
    }
}
