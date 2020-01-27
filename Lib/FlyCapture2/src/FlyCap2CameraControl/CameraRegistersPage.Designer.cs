namespace FlyCap2CameraControl
{
    partial class CameraRegistersPage
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.m_mainGroupBox = new System.Windows.Forms.GroupBox();
            this.m_pageTableLayout = new System.Windows.Forms.TableLayoutPanel();
            this.m_regSetLabel = new System.Windows.Forms.Label();
            this.m_registerControlPanel = new System.Windows.Forms.Panel();
            this.m_pageLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_readWriteRegisterBlockLabel = new System.Windows.Forms.Label();
            this.m_regBlockEntryLabel = new System.Windows.Forms.Label();
            this.m_regValueBlock = new System.Windows.Forms.DataGridView();
            this.m_numOfQuadletsToReadSpinButton = new System.Windows.Forms.NumericUpDown();
            this.m_regBlockEntryTextBox = new System.Windows.Forms.TextBox();
            this.m_numOfQuadletsToReadLabel = new System.Windows.Forms.Label();
            this.m_buttonForRegBlockTableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_writeRegBlockButton = new System.Windows.Forms.Button();
            this.m_readRegBlockButton = new System.Windows.Forms.Button();
            this.m_registerTableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_readWriteRegLabel = new System.Windows.Forms.Label();
            this.m_regEntryLabel = new System.Windows.Forms.Label();
            this.m_registerNameLabel = new System.Windows.Forms.Label();
            this.m_regEntryTextBox = new System.Windows.Forms.TextBox();
            this.m_registerName = new System.Windows.Forms.Label();
            this.m_valueLabel = new System.Windows.Forms.Label();
            this.m_ieee754TextBox = new System.Windows.Forms.TextBox();
            this.m_iEEE754Label = new System.Windows.Forms.Label();
            this.m_buttonForRegTableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.m_writeRegButton = new System.Windows.Forms.Button();
            this.m_readRegButton = new System.Windows.Forms.Button();
            this.m_iIDCRegSetButton = new System.Windows.Forms.RadioButton();
            this.m_gigERegSetButton = new System.Windows.Forms.RadioButton();
            this.m_regValBlockOffset = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_regValBlockValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ieee754 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_regValBlockName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.m_mainGroupBox.SuspendLayout();
            this.m_pageTableLayout.SuspendLayout();
            this.m_registerControlPanel.SuspendLayout();
            this.m_pageLayoutPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_regValueBlock)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOfQuadletsToReadSpinButton)).BeginInit();
            this.m_buttonForRegBlockTableLayoutPanel.SuspendLayout();
            this.m_registerTableLayoutPanel.SuspendLayout();
            this.m_buttonForRegTableLayoutPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_pageTableLayout);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(731, 550);
            this.m_mainGroupBox.TabIndex = 3;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Camera Register Manipulation";
            // 
            // m_pageTableLayout
            // 
            this.m_pageTableLayout.ColumnCount = 3;
            this.m_pageTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_pageTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_pageTableLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_pageTableLayout.Controls.Add(this.m_regSetLabel, 0, 0);
            this.m_pageTableLayout.Controls.Add(this.m_registerControlPanel, 0, 1);
            this.m_pageTableLayout.Controls.Add(this.m_iIDCRegSetButton, 1, 0);
            this.m_pageTableLayout.Controls.Add(this.m_gigERegSetButton, 2, 0);
            this.m_pageTableLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_pageTableLayout.Location = new System.Drawing.Point(3, 16);
            this.m_pageTableLayout.Name = "m_pageTableLayout";
            this.m_pageTableLayout.RowCount = 2;
            this.m_pageTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_pageTableLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_pageTableLayout.Size = new System.Drawing.Size(725, 531);
            this.m_pageTableLayout.TabIndex = 8;
            // 
            // m_regSetLabel
            // 
            this.m_regSetLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_regSetLabel.Location = new System.Drawing.Point(3, 0);
            this.m_regSetLabel.Name = "m_regSetLabel";
            this.m_regSetLabel.Size = new System.Drawing.Size(98, 17);
            this.m_regSetLabel.TabIndex = 3;
            this.m_regSetLabel.Text = "   Register Set:";
            this.m_regSetLabel.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // m_registerControlPanel
            // 
            this.m_registerControlPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_pageTableLayout.SetColumnSpan(this.m_registerControlPanel, 3);
            this.m_registerControlPanel.Controls.Add(this.m_pageLayoutPanel);
            this.m_registerControlPanel.Controls.Add(this.m_registerTableLayoutPanel);
            this.m_registerControlPanel.Location = new System.Drawing.Point(3, 26);
            this.m_registerControlPanel.Name = "m_registerControlPanel";
            this.m_registerControlPanel.Size = new System.Drawing.Size(719, 502);
            this.m_registerControlPanel.TabIndex = 7;
            // 
            // m_pageLayoutPanel
            // 
            this.m_pageLayoutPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.m_pageLayoutPanel.ColumnCount = 2;
            this.m_pageLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_pageLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_pageLayoutPanel.Controls.Add(this.m_readWriteRegisterBlockLabel, 0, 0);
            this.m_pageLayoutPanel.Controls.Add(this.m_regBlockEntryLabel, 0, 1);
            this.m_pageLayoutPanel.Controls.Add(this.m_regValueBlock, 0, 3);
            this.m_pageLayoutPanel.Controls.Add(this.m_numOfQuadletsToReadSpinButton, 1, 2);
            this.m_pageLayoutPanel.Controls.Add(this.m_regBlockEntryTextBox, 1, 1);
            this.m_pageLayoutPanel.Controls.Add(this.m_numOfQuadletsToReadLabel, 0, 2);
            this.m_pageLayoutPanel.Controls.Add(this.m_buttonForRegBlockTableLayoutPanel, 0, 4);
            this.m_pageLayoutPanel.Location = new System.Drawing.Point(8, 185);
            this.m_pageLayoutPanel.Name = "m_pageLayoutPanel";
            this.m_pageLayoutPanel.RowCount = 5;
            this.m_pageLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_pageLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_pageLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_pageLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.m_pageLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_pageLayoutPanel.Size = new System.Drawing.Size(712, 314);
            this.m_pageLayoutPanel.TabIndex = 21;
            // 
            // m_readWriteRegisterBlockLabel
            // 
            this.m_readWriteRegisterBlockLabel.AutoSize = true;
            this.m_pageLayoutPanel.SetColumnSpan(this.m_readWriteRegisterBlockLabel, 2);
            this.m_readWriteRegisterBlockLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_readWriteRegisterBlockLabel.Location = new System.Drawing.Point(3, 0);
            this.m_readWriteRegisterBlockLabel.Name = "m_readWriteRegisterBlockLabel";
            this.m_readWriteRegisterBlockLabel.Padding = new System.Windows.Forms.Padding(0, 6, 6, 6);
            this.m_readWriteRegisterBlockLabel.Size = new System.Drawing.Size(169, 25);
            this.m_readWriteRegisterBlockLabel.TabIndex = 3;
            this.m_readWriteRegisterBlockLabel.Text = "Read / Write Register Block";
            // 
            // m_regBlockEntryLabel
            // 
            this.m_regBlockEntryLabel.AutoSize = true;
            this.m_regBlockEntryLabel.Location = new System.Drawing.Point(3, 25);
            this.m_regBlockEntryLabel.Name = "m_regBlockEntryLabel";
            this.m_regBlockEntryLabel.Size = new System.Drawing.Size(77, 13);
            this.m_regBlockEntryLabel.TabIndex = 6;
            this.m_regBlockEntryLabel.Text = "Register (Hex):";
            // 
            // m_regValueBlock
            // 
            this.m_regValueBlock.AllowUserToAddRows = false;
            this.m_regValueBlock.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.m_regValueBlock.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.m_regValBlockOffset,
            this.m_regValBlockValue,
            this.ieee754,
            this.m_regValBlockName});
            this.m_pageLayoutPanel.SetColumnSpan(this.m_regValueBlock, 2);
            this.m_regValueBlock.Dock = System.Windows.Forms.DockStyle.Left;
            this.m_regValueBlock.GridColor = System.Drawing.SystemColors.ControlDarkDark;
            this.m_regValueBlock.Location = new System.Drawing.Point(3, 80);
            this.m_regValueBlock.Name = "m_regValueBlock";
            this.m_regValueBlock.RowHeadersWidth = 20;
            this.m_regValueBlock.ShowCellErrors = false;
            this.m_regValueBlock.ShowCellToolTips = false;
            this.m_regValueBlock.ShowEditingIcon = false;
            this.m_regValueBlock.ShowRowErrors = false;
            this.m_regValueBlock.Size = new System.Drawing.Size(421, 195);
            this.m_regValueBlock.TabIndex = 17;
            this.m_regValueBlock.TabStop = false;
            // 
            // m_numOfQuadletsToReadSpinButton
            // 
            this.m_numOfQuadletsToReadSpinButton.Location = new System.Drawing.Point(147, 54);
            this.m_numOfQuadletsToReadSpinButton.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.m_numOfQuadletsToReadSpinButton.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.m_numOfQuadletsToReadSpinButton.Name = "m_numOfQuadletsToReadSpinButton";
            this.m_numOfQuadletsToReadSpinButton.Size = new System.Drawing.Size(64, 20);
            this.m_numOfQuadletsToReadSpinButton.TabIndex = 16;
            this.m_numOfQuadletsToReadSpinButton.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // m_regBlockEntryTextBox
            // 
            this.m_regBlockEntryTextBox.BackColor = System.Drawing.Color.PaleGreen;
            this.m_regBlockEntryTextBox.Location = new System.Drawing.Point(147, 28);
            this.m_regBlockEntryTextBox.Name = "m_regBlockEntryTextBox";
            this.m_regBlockEntryTextBox.Size = new System.Drawing.Size(64, 20);
            this.m_regBlockEntryTextBox.TabIndex = 15;
            this.m_regBlockEntryTextBox.TextChanged += new System.EventHandler(this.OnRegBlockEntryTextChanged);
            // 
            // m_numOfQuadletsToReadLabel
            // 
            this.m_numOfQuadletsToReadLabel.AutoSize = true;
            this.m_numOfQuadletsToReadLabel.Location = new System.Drawing.Point(3, 51);
            this.m_numOfQuadletsToReadLabel.Name = "m_numOfQuadletsToReadLabel";
            this.m_numOfQuadletsToReadLabel.Size = new System.Drawing.Size(138, 13);
            this.m_numOfQuadletsToReadLabel.TabIndex = 6;
            this.m_numOfQuadletsToReadLabel.Text = "Number of quadlets to read:";
            // 
            // m_buttonForRegBlockTableLayoutPanel
            // 
            this.m_buttonForRegBlockTableLayoutPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.m_buttonForRegBlockTableLayoutPanel.ColumnCount = 2;
            this.m_pageLayoutPanel.SetColumnSpan(this.m_buttonForRegBlockTableLayoutPanel, 2);
            this.m_buttonForRegBlockTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_buttonForRegBlockTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_buttonForRegBlockTableLayoutPanel.Controls.Add(this.m_writeRegBlockButton, 0, 0);
            this.m_buttonForRegBlockTableLayoutPanel.Controls.Add(this.m_readRegBlockButton, 1, 0);
            this.m_buttonForRegBlockTableLayoutPanel.Location = new System.Drawing.Point(3, 281);
            this.m_buttonForRegBlockTableLayoutPanel.Name = "m_buttonForRegBlockTableLayoutPanel";
            this.m_buttonForRegBlockTableLayoutPanel.RowCount = 1;
            this.m_buttonForRegBlockTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_buttonForRegBlockTableLayoutPanel.Size = new System.Drawing.Size(421, 30);
            this.m_buttonForRegBlockTableLayoutPanel.TabIndex = 18;
            // 
            // m_writeRegBlockButton
            // 
            this.m_writeRegBlockButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.m_writeRegBlockButton.Location = new System.Drawing.Point(45, 3);
            this.m_writeRegBlockButton.Name = "m_writeRegBlockButton";
            this.m_writeRegBlockButton.Size = new System.Drawing.Size(119, 23);
            this.m_writeRegBlockButton.TabIndex = 18;
            this.m_writeRegBlockButton.Text = "Write Register Block";
            this.m_writeRegBlockButton.UseVisualStyleBackColor = true;
            this.m_writeRegBlockButton.Click += new System.EventHandler(this.OnWriteRegBlockButtonClick);
            // 
            // m_readRegBlockButton
            // 
            this.m_readRegBlockButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.m_readRegBlockButton.Location = new System.Drawing.Point(256, 3);
            this.m_readRegBlockButton.Name = "m_readRegBlockButton";
            this.m_readRegBlockButton.Size = new System.Drawing.Size(119, 23);
            this.m_readRegBlockButton.TabIndex = 19;
            this.m_readRegBlockButton.Text = "Read Register Block";
            this.m_readRegBlockButton.UseVisualStyleBackColor = true;
            this.m_readRegBlockButton.Click += new System.EventHandler(this.OnReadRegBlockButtonClick);
            // 
            // m_registerTableLayoutPanel
            // 
            this.m_registerTableLayoutPanel.ColumnCount = 6;
            this.m_registerTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_registerTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_registerTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_registerTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_registerTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_registerTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.m_registerTableLayoutPanel.Controls.Add(this.m_readWriteRegLabel, 0, 0);
            this.m_registerTableLayoutPanel.Controls.Add(this.m_regEntryLabel, 0, 1);
            this.m_registerTableLayoutPanel.Controls.Add(this.m_registerNameLabel, 0, 2);
            this.m_registerTableLayoutPanel.Controls.Add(this.m_regEntryTextBox, 1, 1);
            this.m_registerTableLayoutPanel.Controls.Add(this.m_registerName, 1, 2);
            this.m_registerTableLayoutPanel.Controls.Add(this.m_valueLabel, 0, 3);
            this.m_registerTableLayoutPanel.Controls.Add(this.m_ieee754TextBox, 5, 3);
            this.m_registerTableLayoutPanel.Controls.Add(this.m_iEEE754Label, 5, 4);
            this.m_registerTableLayoutPanel.Controls.Add(this.m_buttonForRegTableLayoutPanel, 0, 6);
            this.m_registerTableLayoutPanel.Location = new System.Drawing.Point(8, 3);
            this.m_registerTableLayoutPanel.Name = "m_registerTableLayoutPanel";
            this.m_registerTableLayoutPanel.RowCount = 6;
            this.m_registerTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_registerTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_registerTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_registerTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_registerTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_registerTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.m_registerTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.m_registerTableLayoutPanel.Size = new System.Drawing.Size(712, 176);
            this.m_registerTableLayoutPanel.TabIndex = 20;
            // 
            // m_readWriteRegLabel
            // 
            this.m_readWriteRegLabel.AutoSize = true;
            this.m_registerTableLayoutPanel.SetColumnSpan(this.m_readWriteRegLabel, 6);
            this.m_readWriteRegLabel.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_readWriteRegLabel.Location = new System.Drawing.Point(3, 0);
            this.m_readWriteRegLabel.Name = "m_readWriteRegLabel";
            this.m_readWriteRegLabel.Padding = new System.Windows.Forms.Padding(0, 6, 6, 6);
            this.m_readWriteRegLabel.Size = new System.Drawing.Size(136, 25);
            this.m_readWriteRegLabel.TabIndex = 3;
            this.m_readWriteRegLabel.Text = "Read / Write Register";
            // 
            // m_regEntryLabel
            // 
            this.m_regEntryLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_regEntryLabel.AutoSize = true;
            this.m_regEntryLabel.Location = new System.Drawing.Point(3, 31);
            this.m_regEntryLabel.Name = "m_regEntryLabel";
            this.m_regEntryLabel.Size = new System.Drawing.Size(77, 13);
            this.m_regEntryLabel.TabIndex = 6;
            this.m_regEntryLabel.Text = "Register (Hex):";
            // 
            // m_registerNameLabel
            // 
            this.m_registerNameLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_registerNameLabel.AutoSize = true;
            this.m_registerNameLabel.Location = new System.Drawing.Point(3, 51);
            this.m_registerNameLabel.Name = "m_registerNameLabel";
            this.m_registerNameLabel.Size = new System.Drawing.Size(77, 13);
            this.m_registerNameLabel.TabIndex = 7;
            this.m_registerNameLabel.Text = "Name: ";
            // 
            // m_regEntryTextBox
            // 
            this.m_regEntryTextBox.BackColor = System.Drawing.Color.PaleGreen;
            this.m_registerTableLayoutPanel.SetColumnSpan(this.m_regEntryTextBox, 5);
            this.m_regEntryTextBox.Location = new System.Drawing.Point(86, 28);
            this.m_regEntryTextBox.Name = "m_regEntryTextBox";
            this.m_regEntryTextBox.Size = new System.Drawing.Size(56, 20);
            this.m_regEntryTextBox.TabIndex = 4;
            this.m_regEntryTextBox.TextChanged += new System.EventHandler(this.OnEntryRegisterTextChanged);
            // 
            // m_registerName
            // 
            this.m_registerName.AutoSize = true;
            this.m_registerTableLayoutPanel.SetColumnSpan(this.m_registerName, 5);
            this.m_registerName.Dock = System.Windows.Forms.DockStyle.Fill;
            this.m_registerName.Location = new System.Drawing.Point(86, 51);
            this.m_registerName.Name = "m_registerName";
            this.m_registerName.Size = new System.Drawing.Size(623, 13);
            this.m_registerName.TabIndex = 8;
            this.m_registerName.Text = "[ Register Name Shows Here...]";
            // 
            // m_valueLabel
            // 
            this.m_valueLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.m_valueLabel.AutoSize = true;
            this.m_valueLabel.Location = new System.Drawing.Point(3, 77);
            this.m_valueLabel.Name = "m_valueLabel";
            this.m_registerTableLayoutPanel.SetRowSpan(this.m_valueLabel, 2);
            this.m_valueLabel.Size = new System.Drawing.Size(77, 13);
            this.m_valueLabel.TabIndex = 9;
            this.m_valueLabel.Text = "Value: ";
            // 
            // m_ieee754TextBox
            // 
            this.m_ieee754TextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.m_ieee754TextBox.Location = new System.Drawing.Point(179, 67);
            this.m_ieee754TextBox.Name = "m_ieee754TextBox";
            this.m_ieee754TextBox.Size = new System.Drawing.Size(63, 20);
            this.m_ieee754TextBox.TabIndex = 12;
            this.m_ieee754TextBox.Text = "0.000000";
            this.m_ieee754TextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.m_ieee754TextBox.TextChanged += new System.EventHandler(this.OnIEEE754TextChanged);
            // 
            // m_iEEE754Label
            // 
            this.m_iEEE754Label.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.m_iEEE754Label.AutoSize = true;
            this.m_iEEE754Label.Location = new System.Drawing.Point(179, 90);
            this.m_iEEE754Label.Name = "m_iEEE754Label";
            this.m_iEEE754Label.Size = new System.Drawing.Size(52, 13);
            this.m_iEEE754Label.TabIndex = 11;
            this.m_iEEE754Label.Text = "IEEE 754";
            // 
            // m_buttonForRegTableLayoutPanel
            // 
            this.m_buttonForRegTableLayoutPanel.ColumnCount = 2;
            this.m_registerTableLayoutPanel.SetColumnSpan(this.m_buttonForRegTableLayoutPanel, 6);
            this.m_buttonForRegTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_buttonForRegTableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.m_buttonForRegTableLayoutPanel.Controls.Add(this.m_writeRegButton, 0, 0);
            this.m_buttonForRegTableLayoutPanel.Controls.Add(this.m_readRegButton, 1, 0);
            this.m_buttonForRegTableLayoutPanel.Location = new System.Drawing.Point(3, 106);
            this.m_buttonForRegTableLayoutPanel.Name = "m_buttonForRegTableLayoutPanel";
            this.m_buttonForRegTableLayoutPanel.RowCount = 1;
            this.m_buttonForRegTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.m_buttonForRegTableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.m_buttonForRegTableLayoutPanel.Size = new System.Drawing.Size(421, 27);
            this.m_buttonForRegTableLayoutPanel.TabIndex = 13;
            // 
            // m_writeRegButton
            // 
            this.m_writeRegButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.m_writeRegButton.AutoSize = true;
            this.m_writeRegButton.Location = new System.Drawing.Point(63, 3);
            this.m_writeRegButton.Margin = new System.Windows.Forms.Padding(12, 3, 12, 3);
            this.m_writeRegButton.Name = "m_writeRegButton";
            this.m_writeRegButton.Size = new System.Drawing.Size(84, 21);
            this.m_writeRegButton.TabIndex = 13;
            this.m_writeRegButton.Text = "Write Register";
            this.m_writeRegButton.UseVisualStyleBackColor = true;
            this.m_writeRegButton.Click += new System.EventHandler(this.OnWriteRegButtonClick);
            // 
            // m_readRegButton
            // 
            this.m_readRegButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.m_readRegButton.AutoSize = true;
            this.m_readRegButton.Location = new System.Drawing.Point(273, 3);
            this.m_readRegButton.Margin = new System.Windows.Forms.Padding(12, 3, 12, 3);
            this.m_readRegButton.Name = "m_readRegButton";
            this.m_readRegButton.Size = new System.Drawing.Size(85, 21);
            this.m_readRegButton.TabIndex = 14;
            this.m_readRegButton.Text = "Read Register";
            this.m_readRegButton.UseVisualStyleBackColor = true;
            this.m_readRegButton.Click += new System.EventHandler(this.OnReadRegButtonClick);
            // 
            // m_iIDCRegSetButton
            // 
            this.m_iIDCRegSetButton.AutoSize = true;
            this.m_iIDCRegSetButton.CheckAlign = System.Drawing.ContentAlignment.TopLeft;
            this.m_iIDCRegSetButton.Checked = true;
            this.m_iIDCRegSetButton.Location = new System.Drawing.Point(107, 3);
            this.m_iIDCRegSetButton.Name = "m_iIDCRegSetButton";
            this.m_iIDCRegSetButton.Size = new System.Drawing.Size(46, 17);
            this.m_iIDCRegSetButton.TabIndex = 5;
            this.m_iIDCRegSetButton.TabStop = true;
            this.m_iIDCRegSetButton.Text = "IIDC";
            this.m_iIDCRegSetButton.UseVisualStyleBackColor = true;
            this.m_iIDCRegSetButton.CheckedChanged += new System.EventHandler(this.OnRegisterSetButtonCheckedStatusChanged);
            // 
            // m_gigERegSetButton
            // 
            this.m_gigERegSetButton.AutoSize = true;
            this.m_gigERegSetButton.Location = new System.Drawing.Point(159, 3);
            this.m_gigERegSetButton.Name = "m_gigERegSetButton";
            this.m_gigERegSetButton.Size = new System.Drawing.Size(48, 17);
            this.m_gigERegSetButton.TabIndex = 5;
            this.m_gigERegSetButton.Text = "GigE";
            this.m_gigERegSetButton.UseVisualStyleBackColor = true;
            this.m_gigERegSetButton.CheckedChanged += new System.EventHandler(this.OnRegisterSetButtonCheckedStatusChanged);
            // 
            // m_regValBlockOffset
            // 
            this.m_regValBlockOffset.HeaderText = "Offset";
            this.m_regValBlockOffset.MinimumWidth = 50;
            this.m_regValBlockOffset.Name = "m_regValBlockOffset";
            this.m_regValBlockOffset.ReadOnly = true;
            this.m_regValBlockOffset.Width = 70;
            // 
            // m_regValBlockValue
            // 
            dataGridViewCellStyle1.NullValue = null;
            this.m_regValBlockValue.DefaultCellStyle = dataGridViewCellStyle1;
            this.m_regValBlockValue.HeaderText = "Value";
            this.m_regValBlockValue.MinimumWidth = 50;
            this.m_regValBlockValue.Name = "m_regValBlockValue";
            this.m_regValBlockValue.Width = 90;
            // 
            // ieee754
            // 
            this.ieee754.HeaderText = "IEEE 754";
            this.ieee754.MinimumWidth = 30;
            this.ieee754.Name = "ieee754";
            this.ieee754.Width = 90;
            // 
            // m_regValBlockName
            // 
            this.m_regValBlockName.HeaderText = "Name";
            this.m_regValBlockName.MinimumWidth = 50;
            this.m_regValBlockName.Name = "m_regValBlockName";
            this.m_regValBlockName.ReadOnly = true;
            this.m_regValBlockName.Width = 178;
            // 
            // CameraRegistersPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "CameraRegistersPage";
            this.Size = new System.Drawing.Size(734, 551);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_pageTableLayout.ResumeLayout(false);
            this.m_pageTableLayout.PerformLayout();
            this.m_registerControlPanel.ResumeLayout(false);
            this.m_pageLayoutPanel.ResumeLayout(false);
            this.m_pageLayoutPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_regValueBlock)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOfQuadletsToReadSpinButton)).EndInit();
            this.m_buttonForRegBlockTableLayoutPanel.ResumeLayout(false);
            this.m_registerTableLayoutPanel.ResumeLayout(false);
            this.m_registerTableLayoutPanel.PerformLayout();
            this.m_buttonForRegTableLayoutPanel.ResumeLayout(false);
            this.m_buttonForRegTableLayoutPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.Label m_readWriteRegLabel;
        private System.Windows.Forms.TextBox m_regEntryTextBox;
        private System.Windows.Forms.Label m_regSetLabel;
        private System.Windows.Forms.RadioButton m_gigERegSetButton;
        private System.Windows.Forms.RadioButton m_iIDCRegSetButton;
        private System.Windows.Forms.Label m_regEntryLabel;
        private System.Windows.Forms.Panel m_registerControlPanel;
        private System.Windows.Forms.Label m_registerName;
        private System.Windows.Forms.Label m_registerNameLabel;
        private System.Windows.Forms.Label m_valueLabel;
        private System.Windows.Forms.Label m_iEEE754Label;
        private System.Windows.Forms.TextBox m_ieee754TextBox;
        private System.Windows.Forms.Button m_writeRegButton;
        private System.Windows.Forms.Button m_readRegButton;
        private System.Windows.Forms.DataGridView m_regValueBlock;
        private System.Windows.Forms.Label m_readWriteRegisterBlockLabel;
        private System.Windows.Forms.Label m_regBlockEntryLabel;
        private System.Windows.Forms.TextBox m_regBlockEntryTextBox;
        private System.Windows.Forms.NumericUpDown m_numOfQuadletsToReadSpinButton;
        private System.Windows.Forms.Label m_numOfQuadletsToReadLabel;
        private System.Windows.Forms.Button m_writeRegBlockButton;
        private System.Windows.Forms.Button m_readRegBlockButton;
        private System.Windows.Forms.TableLayoutPanel m_registerTableLayoutPanel;
        private System.Windows.Forms.TableLayoutPanel m_pageLayoutPanel;
        private System.Windows.Forms.TableLayoutPanel m_buttonForRegBlockTableLayoutPanel;
        private System.Windows.Forms.TableLayoutPanel m_buttonForRegTableLayoutPanel;
        private System.Windows.Forms.TableLayoutPanel m_pageTableLayout;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_regValBlockOffset;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_regValBlockValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn ieee754;
        private System.Windows.Forms.DataGridViewTextBoxColumn m_regValBlockName;
    }
}
