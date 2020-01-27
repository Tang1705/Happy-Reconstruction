namespace FlyCap2CameraControl
{
    partial class LadybugSettingsPage
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
            this.m_bandiwdthLabel = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.m_packetSizeMaxLabel = new System.Windows.Forms.Label();
            this.m_packetSizeMinLabel = new System.Windows.Forms.Label();
            this.m_packetSizeSpinButtonLabel = new System.Windows.Forms.Label();
            this.m_packetSizeSpinButton = new System.Windows.Forms.NumericUpDown();
            this.m_packetSizeTrackBar = new System.Windows.Forms.TrackBar();
            this.m_independentSensorControlPanel = new System.Windows.Forms.Panel();
            this.m_shutterAndGainControlPanel = new System.Windows.Forms.SplitContainer();
            this.m_shutterControlPanel = new System.Windows.Forms.Panel();
            this.m_gainControlPanel = new System.Windows.Forms.Panel();
            this.m_autoExposureControlPanel = new System.Windows.Forms.Panel();
            this.m_sensorUsedForAutoExposureStaticsControlPanel = new System.Windows.Forms.Panel();
            this.m_sensorAutStatControlPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_sensorUsedForAutoExposureStatCam5Label = new System.Windows.Forms.Label();
            this.m_sensorUsedForAutoExposureStatCam4Label = new System.Windows.Forms.Label();
            this.m_sensorUsedForAutoExposureStatCam3Label = new System.Windows.Forms.Label();
            this.m_sensorUsedForAutoExposureStatCam2Label = new System.Windows.Forms.Label();
            this.m_sensorUsedForAutoExposureStatCam1Label = new System.Windows.Forms.Label();
            this.m_sensorUsedForAutoExposureStatCam0Label = new System.Windows.Forms.Label();
            this.m_compressionControlPanel = new System.Windows.Forms.Panel();
            this.m_autoBufferUsageTrackbarValue = new System.Windows.Forms.Label();
            this.m_jpegQualityTrackbarValue = new System.Windows.Forms.Label();
            this.m_autoBufferUsageTrackbar = new System.Windows.Forms.TrackBar();
            this.m_jpegQualityTrackbar = new System.Windows.Forms.TrackBar();
            this.m_jpegAutoQualityCheckBox = new System.Windows.Forms.CheckBox();
            this.m_autoBuffInUsageLabel = new System.Windows.Forms.Label();
            this.m_jpegQualityLabel = new System.Windows.Forms.Label();
            this.m_sensorUsedForAutoExposureStaticsControlLabel = new System.Windows.Forms.Label();
            this.m_independentSensorControlLabel = new System.Windows.Forms.Label();
            this.m_separateLine2 = new System.Windows.Forms.Label();
            this.m_compressionControlLabel = new System.Windows.Forms.Label();
            this.m_separateLine1 = new System.Windows.Forms.Label();
            this.m_mainGroupBox.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_packetSizeSpinButton)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_packetSizeTrackBar)).BeginInit();
            this.m_independentSensorControlPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_shutterAndGainControlPanel)).BeginInit();
            this.m_shutterAndGainControlPanel.Panel1.SuspendLayout();
            this.m_shutterAndGainControlPanel.Panel2.SuspendLayout();
            this.m_shutterAndGainControlPanel.SuspendLayout();
            this.m_sensorUsedForAutoExposureStaticsControlPanel.SuspendLayout();
            this.m_sensorAutStatControlPanel.SuspendLayout();
            this.m_compressionControlPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_autoBufferUsageTrackbar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_jpegQualityTrackbar)).BeginInit();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_bandiwdthLabel);
            this.m_mainGroupBox.Controls.Add(this.panel1);
            this.m_mainGroupBox.Controls.Add(this.m_independentSensorControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_sensorUsedForAutoExposureStaticsControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_compressionControlPanel);
            this.m_mainGroupBox.Controls.Add(this.m_sensorUsedForAutoExposureStaticsControlLabel);
            this.m_mainGroupBox.Controls.Add(this.m_independentSensorControlLabel);
            this.m_mainGroupBox.Controls.Add(this.m_separateLine2);
            this.m_mainGroupBox.Controls.Add(this.m_compressionControlLabel);
            this.m_mainGroupBox.Controls.Add(this.m_separateLine1);
            this.m_mainGroupBox.Location = new System.Drawing.Point(2, 2);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(635, 569);
            this.m_mainGroupBox.TabIndex = 5;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Ladybug Settings";
            // 
            // m_bandiwdthLabel
            // 
            this.m_bandiwdthLabel.AutoSize = true;
            this.m_bandiwdthLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_bandiwdthLabel.Location = new System.Drawing.Point(322, 487);
            this.m_bandiwdthLabel.Name = "m_bandiwdthLabel";
            this.m_bandiwdthLabel.Size = new System.Drawing.Size(110, 13);
            this.m_bandiwdthLabel.TabIndex = 10;
            this.m_bandiwdthLabel.Text = "Bandwidth Control";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.m_packetSizeMaxLabel);
            this.panel1.Controls.Add(this.m_packetSizeMinLabel);
            this.panel1.Controls.Add(this.m_packetSizeSpinButtonLabel);
            this.panel1.Controls.Add(this.m_packetSizeSpinButton);
            this.panel1.Controls.Add(this.m_packetSizeTrackBar);
            this.panel1.Location = new System.Drawing.Point(325, 503);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(300, 60);
            this.panel1.TabIndex = 9;
            // 
            // m_packetSizeMaxLabel
            // 
            this.m_packetSizeMaxLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_packetSizeMaxLabel.AutoSize = true;
            this.m_packetSizeMaxLabel.Location = new System.Drawing.Point(238, 5);
            this.m_packetSizeMaxLabel.Name = "m_packetSizeMaxLabel";
            this.m_packetSizeMaxLabel.Size = new System.Drawing.Size(27, 13);
            this.m_packetSizeMaxLabel.TabIndex = 13;
            this.m_packetSizeMaxLabel.Text = "Max";
            this.m_packetSizeMaxLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_packetSizeMinLabel
            // 
            this.m_packetSizeMinLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_packetSizeMinLabel.AutoSize = true;
            this.m_packetSizeMinLabel.Location = new System.Drawing.Point(21, 6);
            this.m_packetSizeMinLabel.Name = "m_packetSizeMinLabel";
            this.m_packetSizeMinLabel.Size = new System.Drawing.Size(24, 13);
            this.m_packetSizeMinLabel.TabIndex = 12;
            this.m_packetSizeMinLabel.Text = "Min";
            this.m_packetSizeMinLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // m_packetSizeSpinButtonLabel
            // 
            this.m_packetSizeSpinButtonLabel.AutoSize = true;
            this.m_packetSizeSpinButtonLabel.Location = new System.Drawing.Point(64, 37);
            this.m_packetSizeSpinButtonLabel.Name = "m_packetSizeSpinButtonLabel";
            this.m_packetSizeSpinButtonLabel.Size = new System.Drawing.Size(67, 13);
            this.m_packetSizeSpinButtonLabel.TabIndex = 11;
            this.m_packetSizeSpinButtonLabel.Text = "Packet Size:";
            // 
            // m_packetSizeSpinButton
            // 
            this.m_packetSizeSpinButton.BackColor = System.Drawing.Color.PaleGreen;
            this.m_packetSizeSpinButton.Location = new System.Drawing.Point(137, 33);
            this.m_packetSizeSpinButton.Name = "m_packetSizeSpinButton";
            this.m_packetSizeSpinButton.Size = new System.Drawing.Size(86, 20);
            this.m_packetSizeSpinButton.TabIndex = 10;
            // 
            // m_packetSizeTrackBar
            // 
            this.m_packetSizeTrackBar.AutoSize = false;
            this.m_packetSizeTrackBar.Location = new System.Drawing.Point(52, 3);
            this.m_packetSizeTrackBar.Maximum = 10000;
            this.m_packetSizeTrackBar.Name = "m_packetSizeTrackBar";
            this.m_packetSizeTrackBar.Size = new System.Drawing.Size(180, 30);
            this.m_packetSizeTrackBar.TabIndex = 9;
            this.m_packetSizeTrackBar.TickFrequency = 1000;
            // 
            // m_independentSensorControlPanel
            // 
            this.m_independentSensorControlPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_independentSensorControlPanel.Controls.Add(this.m_shutterAndGainControlPanel);
            this.m_independentSensorControlPanel.Controls.Add(this.m_autoExposureControlPanel);
            this.m_independentSensorControlPanel.Location = new System.Drawing.Point(22, 102);
            this.m_independentSensorControlPanel.Name = "m_independentSensorControlPanel";
            this.m_independentSensorControlPanel.Size = new System.Drawing.Size(603, 380);
            this.m_independentSensorControlPanel.TabIndex = 3;
            // 
            // m_shutterAndGainControlPanel
            // 
            this.m_shutterAndGainControlPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_shutterAndGainControlPanel.Location = new System.Drawing.Point(5, 190);
            this.m_shutterAndGainControlPanel.Name = "m_shutterAndGainControlPanel";
            // 
            // m_shutterAndGainControlPanel.Panel1
            // 
            this.m_shutterAndGainControlPanel.Panel1.Controls.Add(this.m_shutterControlPanel);
            // 
            // m_shutterAndGainControlPanel.Panel2
            // 
            this.m_shutterAndGainControlPanel.Panel2.Controls.Add(this.m_gainControlPanel);
            this.m_shutterAndGainControlPanel.Size = new System.Drawing.Size(594, 189);
            this.m_shutterAndGainControlPanel.SplitterDistance = 288;
            this.m_shutterAndGainControlPanel.SplitterWidth = 10;
            this.m_shutterAndGainControlPanel.TabIndex = 2;
            this.m_shutterAndGainControlPanel.TabStop = false;
            // 
            // m_shutterControlPanel
            // 
            this.m_shutterControlPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_shutterControlPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_shutterControlPanel.Location = new System.Drawing.Point(0, 0);
            this.m_shutterControlPanel.MinimumSize = new System.Drawing.Size(200, 189);
            this.m_shutterControlPanel.Name = "m_shutterControlPanel";
            this.m_shutterControlPanel.Size = new System.Drawing.Size(288, 189);
            this.m_shutterControlPanel.TabIndex = 3;
            // 
            // m_gainControlPanel
            // 
            this.m_gainControlPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_gainControlPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_gainControlPanel.Location = new System.Drawing.Point(0, 0);
            this.m_gainControlPanel.MinimumSize = new System.Drawing.Size(200, 189);
            this.m_gainControlPanel.Name = "m_gainControlPanel";
            this.m_gainControlPanel.Size = new System.Drawing.Size(296, 189);
            this.m_gainControlPanel.TabIndex = 4;
            // 
            // m_autoExposureControlPanel
            // 
            this.m_autoExposureControlPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_autoExposureControlPanel.Location = new System.Drawing.Point(5, 0);
            this.m_autoExposureControlPanel.Name = "m_autoExposureControlPanel";
            this.m_autoExposureControlPanel.Size = new System.Drawing.Size(595, 190);
            this.m_autoExposureControlPanel.TabIndex = 1;
            // 
            // m_sensorUsedForAutoExposureStaticsControlPanel
            // 
            this.m_sensorUsedForAutoExposureStaticsControlPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_sensorUsedForAutoExposureStaticsControlPanel.Controls.Add(this.m_sensorAutStatControlPanel);
            this.m_sensorUsedForAutoExposureStaticsControlPanel.Location = new System.Drawing.Point(20, 503);
            this.m_sensorUsedForAutoExposureStaticsControlPanel.Name = "m_sensorUsedForAutoExposureStaticsControlPanel";
            this.m_sensorUsedForAutoExposureStaticsControlPanel.Size = new System.Drawing.Size(295, 45);
            this.m_sensorUsedForAutoExposureStaticsControlPanel.TabIndex = 4;
            // 
            // m_sensorAutStatControlPanel
            // 
            this.m_sensorAutStatControlPanel.ColumnCount = 6;
            this.m_sensorAutStatControlPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.m_sensorAutStatControlPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.m_sensorAutStatControlPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.m_sensorAutStatControlPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.m_sensorAutStatControlPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.m_sensorAutStatControlPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.m_sensorAutStatControlPanel.Controls.Add(this.m_sensorUsedForAutoExposureStatCam5Label, 5, 0);
            this.m_sensorAutStatControlPanel.Controls.Add(this.m_sensorUsedForAutoExposureStatCam4Label, 4, 0);
            this.m_sensorAutStatControlPanel.Controls.Add(this.m_sensorUsedForAutoExposureStatCam3Label, 3, 0);
            this.m_sensorAutStatControlPanel.Controls.Add(this.m_sensorUsedForAutoExposureStatCam2Label, 2, 0);
            this.m_sensorAutStatControlPanel.Controls.Add(this.m_sensorUsedForAutoExposureStatCam1Label, 1, 0);
            this.m_sensorAutStatControlPanel.Controls.Add(this.m_sensorUsedForAutoExposureStatCam0Label, 0, 0);
            this.m_sensorAutStatControlPanel.Location = new System.Drawing.Point(10, 0);
            this.m_sensorAutStatControlPanel.Name = "m_sensorAutStatControlPanel";
            this.m_sensorAutStatControlPanel.RowCount = 2;
            this.m_sensorAutStatControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_sensorAutStatControlPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_sensorAutStatControlPanel.Size = new System.Drawing.Size(176, 45);
            this.m_sensorAutStatControlPanel.TabIndex = 0;
            // 
            // m_sensorUsedForAutoExposureStatCam5Label
            // 
            this.m_sensorUsedForAutoExposureStatCam5Label.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_sensorUsedForAutoExposureStatCam5Label.Location = new System.Drawing.Point(148, 0);
            this.m_sensorUsedForAutoExposureStatCam5Label.Name = "m_sensorUsedForAutoExposureStatCam5Label";
            this.m_sensorUsedForAutoExposureStatCam5Label.Size = new System.Drawing.Size(25, 22);
            this.m_sensorUsedForAutoExposureStatCam5Label.TabIndex = 5;
            this.m_sensorUsedForAutoExposureStatCam5Label.Text = "5";
            this.m_sensorUsedForAutoExposureStatCam5Label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_sensorUsedForAutoExposureStatCam4Label
            // 
            this.m_sensorUsedForAutoExposureStatCam4Label.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_sensorUsedForAutoExposureStatCam4Label.Location = new System.Drawing.Point(119, 0);
            this.m_sensorUsedForAutoExposureStatCam4Label.Name = "m_sensorUsedForAutoExposureStatCam4Label";
            this.m_sensorUsedForAutoExposureStatCam4Label.Size = new System.Drawing.Size(23, 22);
            this.m_sensorUsedForAutoExposureStatCam4Label.TabIndex = 4;
            this.m_sensorUsedForAutoExposureStatCam4Label.Text = "4";
            this.m_sensorUsedForAutoExposureStatCam4Label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_sensorUsedForAutoExposureStatCam3Label
            // 
            this.m_sensorUsedForAutoExposureStatCam3Label.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_sensorUsedForAutoExposureStatCam3Label.Location = new System.Drawing.Point(90, 0);
            this.m_sensorUsedForAutoExposureStatCam3Label.Name = "m_sensorUsedForAutoExposureStatCam3Label";
            this.m_sensorUsedForAutoExposureStatCam3Label.Size = new System.Drawing.Size(23, 22);
            this.m_sensorUsedForAutoExposureStatCam3Label.TabIndex = 3;
            this.m_sensorUsedForAutoExposureStatCam3Label.Text = "3";
            this.m_sensorUsedForAutoExposureStatCam3Label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_sensorUsedForAutoExposureStatCam2Label
            // 
            this.m_sensorUsedForAutoExposureStatCam2Label.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_sensorUsedForAutoExposureStatCam2Label.Location = new System.Drawing.Point(61, 0);
            this.m_sensorUsedForAutoExposureStatCam2Label.Name = "m_sensorUsedForAutoExposureStatCam2Label";
            this.m_sensorUsedForAutoExposureStatCam2Label.Size = new System.Drawing.Size(23, 22);
            this.m_sensorUsedForAutoExposureStatCam2Label.TabIndex = 2;
            this.m_sensorUsedForAutoExposureStatCam2Label.Text = "2";
            this.m_sensorUsedForAutoExposureStatCam2Label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_sensorUsedForAutoExposureStatCam1Label
            // 
            this.m_sensorUsedForAutoExposureStatCam1Label.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_sensorUsedForAutoExposureStatCam1Label.Location = new System.Drawing.Point(32, 0);
            this.m_sensorUsedForAutoExposureStatCam1Label.Name = "m_sensorUsedForAutoExposureStatCam1Label";
            this.m_sensorUsedForAutoExposureStatCam1Label.Size = new System.Drawing.Size(23, 22);
            this.m_sensorUsedForAutoExposureStatCam1Label.TabIndex = 1;
            this.m_sensorUsedForAutoExposureStatCam1Label.Text = "1";
            this.m_sensorUsedForAutoExposureStatCam1Label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_sensorUsedForAutoExposureStatCam0Label
            // 
            this.m_sensorUsedForAutoExposureStatCam0Label.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_sensorUsedForAutoExposureStatCam0Label.Location = new System.Drawing.Point(3, 0);
            this.m_sensorUsedForAutoExposureStatCam0Label.Name = "m_sensorUsedForAutoExposureStatCam0Label";
            this.m_sensorUsedForAutoExposureStatCam0Label.Size = new System.Drawing.Size(23, 22);
            this.m_sensorUsedForAutoExposureStatCam0Label.TabIndex = 0;
            this.m_sensorUsedForAutoExposureStatCam0Label.Text = "0";
            this.m_sensorUsedForAutoExposureStatCam0Label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // m_compressionControlPanel
            // 
            this.m_compressionControlPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_compressionControlPanel.Controls.Add(this.m_autoBufferUsageTrackbarValue);
            this.m_compressionControlPanel.Controls.Add(this.m_jpegQualityTrackbarValue);
            this.m_compressionControlPanel.Controls.Add(this.m_autoBufferUsageTrackbar);
            this.m_compressionControlPanel.Controls.Add(this.m_jpegQualityTrackbar);
            this.m_compressionControlPanel.Controls.Add(this.m_jpegAutoQualityCheckBox);
            this.m_compressionControlPanel.Controls.Add(this.m_autoBuffInUsageLabel);
            this.m_compressionControlPanel.Controls.Add(this.m_jpegQualityLabel);
            this.m_compressionControlPanel.Location = new System.Drawing.Point(23, 34);
            this.m_compressionControlPanel.Name = "m_compressionControlPanel";
            this.m_compressionControlPanel.Size = new System.Drawing.Size(603, 45);
            this.m_compressionControlPanel.TabIndex = 1;
            // 
            // m_autoBufferUsageTrackbarValue
            // 
            this.m_autoBufferUsageTrackbarValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_autoBufferUsageTrackbarValue.AutoSize = true;
            this.m_autoBufferUsageTrackbarValue.Location = new System.Drawing.Point(568, 23);
            this.m_autoBufferUsageTrackbarValue.Name = "m_autoBufferUsageTrackbarValue";
            this.m_autoBufferUsageTrackbarValue.Size = new System.Drawing.Size(22, 13);
            this.m_autoBufferUsageTrackbarValue.TabIndex = 3;
            this.m_autoBufferUsageTrackbarValue.Text = "1.0";
            // 
            // m_jpegQualityTrackbarValue
            // 
            this.m_jpegQualityTrackbarValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_jpegQualityTrackbarValue.AutoSize = true;
            this.m_jpegQualityTrackbarValue.Location = new System.Drawing.Point(568, 4);
            this.m_jpegQualityTrackbarValue.Name = "m_jpegQualityTrackbarValue";
            this.m_jpegQualityTrackbarValue.Size = new System.Drawing.Size(22, 13);
            this.m_jpegQualityTrackbarValue.TabIndex = 3;
            this.m_jpegQualityTrackbarValue.Text = "1.0";
            // 
            // m_autoBufferUsageTrackbar
            // 
            this.m_autoBufferUsageTrackbar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_autoBufferUsageTrackbar.AutoSize = false;
            this.m_autoBufferUsageTrackbar.LargeChange = 100;
            this.m_autoBufferUsageTrackbar.Location = new System.Drawing.Point(163, 24);
            this.m_autoBufferUsageTrackbar.Maximum = 1000;
            this.m_autoBufferUsageTrackbar.Minimum = 10;
            this.m_autoBufferUsageTrackbar.Name = "m_autoBufferUsageTrackbar";
            this.m_autoBufferUsageTrackbar.Size = new System.Drawing.Size(393, 19);
            this.m_autoBufferUsageTrackbar.TabIndex = 3;
            this.m_autoBufferUsageTrackbar.TickFrequency = 100;
            this.m_autoBufferUsageTrackbar.TickStyle = System.Windows.Forms.TickStyle.None;
            this.m_autoBufferUsageTrackbar.Value = 10;
            this.m_autoBufferUsageTrackbar.Scroll += new System.EventHandler(this.OnAutoBufferUsageTrackbar_Scroll);
            this.m_autoBufferUsageTrackbar.ValueChanged += new System.EventHandler(this.OnAutoBufferUsageTrackbar_ValueChanged);
            // 
            // m_jpegQualityTrackbar
            // 
            this.m_jpegQualityTrackbar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_jpegQualityTrackbar.AutoSize = false;
            this.m_jpegQualityTrackbar.LargeChange = 100;
            this.m_jpegQualityTrackbar.Location = new System.Drawing.Point(163, 3);
            this.m_jpegQualityTrackbar.Maximum = 1000;
            this.m_jpegQualityTrackbar.Minimum = 10;
            this.m_jpegQualityTrackbar.Name = "m_jpegQualityTrackbar";
            this.m_jpegQualityTrackbar.Size = new System.Drawing.Size(393, 19);
            this.m_jpegQualityTrackbar.TabIndex = 2;
            this.m_jpegQualityTrackbar.TickFrequency = 100;
            this.m_jpegQualityTrackbar.TickStyle = System.Windows.Forms.TickStyle.None;
            this.m_jpegQualityTrackbar.Value = 10;
            this.m_jpegQualityTrackbar.Scroll += new System.EventHandler(this.OnJpegQualityTrackbar_Scroll);
            this.m_jpegQualityTrackbar.ValueChanged += new System.EventHandler(this.OnJpegQualityTrackbar_ValueChanged);
            // 
            // m_jpegAutoQualityCheckBox
            // 
            this.m_jpegAutoQualityCheckBox.AutoSize = true;
            this.m_jpegAutoQualityCheckBox.Location = new System.Drawing.Point(108, 4);
            this.m_jpegAutoQualityCheckBox.Name = "m_jpegAutoQualityCheckBox";
            this.m_jpegAutoQualityCheckBox.Size = new System.Drawing.Size(48, 17);
            this.m_jpegAutoQualityCheckBox.TabIndex = 1;
            this.m_jpegAutoQualityCheckBox.Text = "Auto";
            this.m_jpegAutoQualityCheckBox.UseVisualStyleBackColor = true;
            this.m_jpegAutoQualityCheckBox.CheckedChanged += new System.EventHandler(this.OnAutoQualityCheckedChanged);
            // 
            // m_autoBuffInUsageLabel
            // 
            this.m_autoBuffInUsageLabel.AutoSize = true;
            this.m_autoBuffInUsageLabel.Location = new System.Drawing.Point(4, 23);
            this.m_autoBuffInUsageLabel.Name = "m_autoBuffInUsageLabel";
            this.m_autoBuffInUsageLabel.Size = new System.Drawing.Size(119, 13);
            this.m_autoBuffInUsageLabel.TabIndex = 0;
            this.m_autoBuffInUsageLabel.Text = "Auto buffer usage (in %)";
            // 
            // m_jpegQualityLabel
            // 
            this.m_jpegQualityLabel.AutoSize = true;
            this.m_jpegQualityLabel.Location = new System.Drawing.Point(4, 4);
            this.m_jpegQualityLabel.Name = "m_jpegQualityLabel";
            this.m_jpegQualityLabel.Size = new System.Drawing.Size(97, 13);
            this.m_jpegQualityLabel.TabIndex = 0;
            this.m_jpegQualityLabel.Text = "JPEG Quality (in %)";
            // 
            // m_sensorUsedForAutoExposureStaticsControlLabel
            // 
            this.m_sensorUsedForAutoExposureStaticsControlLabel.AutoSize = true;
            this.m_sensorUsedForAutoExposureStaticsControlLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_sensorUsedForAutoExposureStaticsControlLabel.Location = new System.Drawing.Point(6, 487);
            this.m_sensorUsedForAutoExposureStaticsControlLabel.Name = "m_sensorUsedForAutoExposureStaticsControlLabel";
            this.m_sensorUsedForAutoExposureStaticsControlLabel.Size = new System.Drawing.Size(245, 13);
            this.m_sensorUsedForAutoExposureStaticsControlLabel.TabIndex = 8;
            this.m_sensorUsedForAutoExposureStaticsControlLabel.Text = "Sensors Used For Auto Exposure Statistics";
            // 
            // m_independentSensorControlLabel
            // 
            this.m_independentSensorControlLabel.AutoSize = true;
            this.m_independentSensorControlLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_independentSensorControlLabel.Location = new System.Drawing.Point(6, 86);
            this.m_independentSensorControlLabel.Name = "m_independentSensorControlLabel";
            this.m_independentSensorControlLabel.Size = new System.Drawing.Size(166, 13);
            this.m_independentSensorControlLabel.TabIndex = 8;
            this.m_independentSensorControlLabel.Text = "Independent Sensor Control";
            // 
            // m_separateLine2
            // 
            this.m_separateLine2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_separateLine2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_separateLine2.Location = new System.Drawing.Point(8, 484);
            this.m_separateLine2.Name = "m_separateLine2";
            this.m_separateLine2.Size = new System.Drawing.Size(619, 3);
            this.m_separateLine2.TabIndex = 7;
            this.m_separateLine2.Text = "Separate Line. Don\'t resize it!";
            // 
            // m_compressionControlLabel
            // 
            this.m_compressionControlLabel.AutoSize = true;
            this.m_compressionControlLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_compressionControlLabel.Location = new System.Drawing.Point(6, 16);
            this.m_compressionControlLabel.Name = "m_compressionControlLabel";
            this.m_compressionControlLabel.Size = new System.Drawing.Size(124, 13);
            this.m_compressionControlLabel.TabIndex = 6;
            this.m_compressionControlLabel.Text = "Compression Control";
            // 
            // m_separateLine1
            // 
            this.m_separateLine1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.m_separateLine1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.m_separateLine1.Location = new System.Drawing.Point(8, 82);
            this.m_separateLine1.Name = "m_separateLine1";
            this.m_separateLine1.Size = new System.Drawing.Size(619, 3);
            this.m_separateLine1.TabIndex = 1;
            this.m_separateLine1.Text = "Separate Line. Don\'t resize it!";
            // 
            // LadybugSettingsPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "LadybugSettingsPage";
            this.Size = new System.Drawing.Size(640, 579);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_mainGroupBox.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_packetSizeSpinButton)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_packetSizeTrackBar)).EndInit();
            this.m_independentSensorControlPanel.ResumeLayout(false);
            this.m_shutterAndGainControlPanel.Panel1.ResumeLayout(false);
            this.m_shutterAndGainControlPanel.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.m_shutterAndGainControlPanel)).EndInit();
            this.m_shutterAndGainControlPanel.ResumeLayout(false);
            this.m_sensorUsedForAutoExposureStaticsControlPanel.ResumeLayout(false);
            this.m_sensorAutStatControlPanel.ResumeLayout(false);
            this.m_compressionControlPanel.ResumeLayout(false);
            this.m_compressionControlPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_autoBufferUsageTrackbar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_jpegQualityTrackbar)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.Label m_separateLine1;
        private System.Windows.Forms.Label m_compressionControlLabel;
        private System.Windows.Forms.Label m_independentSensorControlLabel;
        private System.Windows.Forms.Label m_separateLine2;
        private System.Windows.Forms.Panel m_independentSensorControlPanel;
        private System.Windows.Forms.Panel m_sensorUsedForAutoExposureStaticsControlPanel;
        private System.Windows.Forms.Panel m_compressionControlPanel;
        private System.Windows.Forms.Label m_sensorUsedForAutoExposureStaticsControlLabel;
        private System.Windows.Forms.Label m_autoBuffInUsageLabel;
        private System.Windows.Forms.Label m_jpegQualityLabel;
        private System.Windows.Forms.Label m_autoBufferUsageTrackbarValue;
        private System.Windows.Forms.Label m_jpegQualityTrackbarValue;
        private System.Windows.Forms.TrackBar m_autoBufferUsageTrackbar;
        private System.Windows.Forms.TrackBar m_jpegQualityTrackbar;
        private System.Windows.Forms.CheckBox m_jpegAutoQualityCheckBox;
        private System.Windows.Forms.Panel m_autoExposureControlPanel;
        private System.Windows.Forms.Panel m_shutterControlPanel;
        private System.Windows.Forms.Panel m_gainControlPanel;
        private System.Windows.Forms.SplitContainer m_shutterAndGainControlPanel;
        private System.Windows.Forms.TableLayoutPanel m_sensorAutStatControlPanel;
        private System.Windows.Forms.Label m_sensorUsedForAutoExposureStatCam0Label;
        private System.Windows.Forms.Label m_sensorUsedForAutoExposureStatCam5Label;
        private System.Windows.Forms.Label m_sensorUsedForAutoExposureStatCam4Label;
        private System.Windows.Forms.Label m_sensorUsedForAutoExposureStatCam3Label;
        private System.Windows.Forms.Label m_sensorUsedForAutoExposureStatCam2Label;
        private System.Windows.Forms.Label m_sensorUsedForAutoExposureStatCam1Label;
        private System.Windows.Forms.Label m_bandiwdthLabel;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TrackBar m_packetSizeTrackBar;
        private System.Windows.Forms.NumericUpDown m_packetSizeSpinButton;
        private System.Windows.Forms.Label m_packetSizeSpinButtonLabel;
        private System.Windows.Forms.Label m_packetSizeMinLabel;
        private System.Windows.Forms.Label m_packetSizeMaxLabel;
    }
}
