namespace FlyCap2CameraControl
{
    partial class HelpSupportPage
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
            this.components = new System.ComponentModel.Container();
            this.m_mainGroupBox = new System.Windows.Forms.GroupBox();
            this.m_downloadsAndUpdatesGroupBox = new System.Windows.Forms.GroupBox();
            this.m_downloadLinkLabel = new System.Windows.Forms.LinkLabel();
            this.m_copyMenuStrip = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.m_copyURLItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label3 = new System.Windows.Forms.Label();
            this.m_supportTicketsGroupBox = new System.Windows.Forms.GroupBox();
            this.m_supportTicketLinkLabel = new System.Windows.Forms.LinkLabel();
            this.label2 = new System.Windows.Forms.Label();
            this.m_knowledgeBaseGroupBox = new System.Windows.Forms.GroupBox();
            this.m_knowledgeBaseLinkLabel = new System.Windows.Forms.LinkLabel();
            this.label1 = new System.Windows.Forms.Label();
            this.m_mainGroupBox.SuspendLayout();
            this.m_downloadsAndUpdatesGroupBox.SuspendLayout();
            this.m_copyMenuStrip.SuspendLayout();
            this.m_supportTicketsGroupBox.SuspendLayout();
            this.m_knowledgeBaseGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_mainGroupBox
            // 
            this.m_mainGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_mainGroupBox.Controls.Add(this.m_downloadsAndUpdatesGroupBox);
            this.m_mainGroupBox.Controls.Add(this.m_supportTicketsGroupBox);
            this.m_mainGroupBox.Controls.Add(this.m_knowledgeBaseGroupBox);
            this.m_mainGroupBox.Location = new System.Drawing.Point(0, 0);
            this.m_mainGroupBox.Name = "m_mainGroupBox";
            this.m_mainGroupBox.Size = new System.Drawing.Size(471, 435);
            this.m_mainGroupBox.TabIndex = 4;
            this.m_mainGroupBox.TabStop = false;
            this.m_mainGroupBox.Text = "Help / Support";
            // 
            // m_downloadsAndUpdatesGroupBox
            // 
            this.m_downloadsAndUpdatesGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_downloadsAndUpdatesGroupBox.Controls.Add(this.m_downloadLinkLabel);
            this.m_downloadsAndUpdatesGroupBox.Controls.Add(this.label3);
            this.m_downloadsAndUpdatesGroupBox.Location = new System.Drawing.Point(6, 198);
            this.m_downloadsAndUpdatesGroupBox.Name = "m_downloadsAndUpdatesGroupBox";
            this.m_downloadsAndUpdatesGroupBox.Size = new System.Drawing.Size(458, 85);
            this.m_downloadsAndUpdatesGroupBox.TabIndex = 3;
            this.m_downloadsAndUpdatesGroupBox.TabStop = false;
            this.m_downloadsAndUpdatesGroupBox.Text = "Downloads / Updates";
            // 
            // m_downloadLinkLabel
            // 
            this.m_downloadLinkLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_downloadLinkLabel.Location = new System.Drawing.Point(10, 52);
            this.m_downloadLinkLabel.Name = "m_downloadLinkLabel";
            this.m_downloadLinkLabel.Size = new System.Drawing.Size(442, 29);
            this.m_downloadLinkLabel.TabIndex = 3;
            this.m_downloadLinkLabel.TabStop = true;
            this.m_downloadLinkLabel.Tag = "http://www.ptgrey.com/support/downloads";
            this.m_downloadLinkLabel.Text = "Visit the Downloads page";
            this.m_downloadLinkLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.m_downloadLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.OnLinkLabelClicked);
            // 
            // m_copyMenuStrip
            // 
            this.m_copyMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.m_copyURLItem});
            this.m_copyMenuStrip.Name = "m_copyMenuStrip";
            this.m_copyMenuStrip.Size = new System.Drawing.Size(133, 26);
            // 
            // m_copyURLItem
            // 
            this.m_copyURLItem.Name = "m_copyURLItem";
            this.m_copyURLItem.Size = new System.Drawing.Size(132, 22);
            this.m_copyURLItem.Tag = "http://www.ptgrey.com/support/kb";
            this.m_copyURLItem.Text = "Copy URL";
            this.m_copyURLItem.Click += new System.EventHandler(this.OnCopyURLClick);
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.Location = new System.Drawing.Point(7, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(445, 33);
            this.label3.TabIndex = 2;
            this.label3.Text = "Get the latest software and downloads for your camera from the Downloads page";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // m_supportTicketsGroupBox
            // 
            this.m_supportTicketsGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_supportTicketsGroupBox.Controls.Add(this.m_supportTicketLinkLabel);
            this.m_supportTicketsGroupBox.Controls.Add(this.label2);
            this.m_supportTicketsGroupBox.Location = new System.Drawing.Point(7, 109);
            this.m_supportTicketsGroupBox.Name = "m_supportTicketsGroupBox";
            this.m_supportTicketsGroupBox.Size = new System.Drawing.Size(458, 83);
            this.m_supportTicketsGroupBox.TabIndex = 2;
            this.m_supportTicketsGroupBox.TabStop = false;
            this.m_supportTicketsGroupBox.Text = "Support Tickets";
            // 
            // m_supportTicketLinkLabel
            // 
            this.m_supportTicketLinkLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_supportTicketLinkLabel.Location = new System.Drawing.Point(6, 51);
            this.m_supportTicketLinkLabel.Name = "m_supportTicketLinkLabel";
            this.m_supportTicketLinkLabel.Size = new System.Drawing.Size(445, 27);
            this.m_supportTicketLinkLabel.TabIndex = 2;
            this.m_supportTicketLinkLabel.TabStop = true;
            this.m_supportTicketLinkLabel.Tag = "http://www.ptgrey.com/support/contact/contact.asp";
            this.m_supportTicketLinkLabel.Text = "Click here to create a Support Ticket";
            this.m_supportTicketLinkLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.m_supportTicketLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.OnLinkLabelClicked);
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.Location = new System.Drawing.Point(1, 14);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(456, 33);
            this.label2.TabIndex = 2;
            this.label2.Text = "If your question cannot be answered by the Knowledge Base, please create a Suppor" +
                "t Ticket.";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // m_knowledgeBaseGroupBox
            // 
            this.m_knowledgeBaseGroupBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_knowledgeBaseGroupBox.Controls.Add(this.m_knowledgeBaseLinkLabel);
            this.m_knowledgeBaseGroupBox.Controls.Add(this.label1);
            this.m_knowledgeBaseGroupBox.Location = new System.Drawing.Point(7, 20);
            this.m_knowledgeBaseGroupBox.Name = "m_knowledgeBaseGroupBox";
            this.m_knowledgeBaseGroupBox.Size = new System.Drawing.Size(458, 83);
            this.m_knowledgeBaseGroupBox.TabIndex = 0;
            this.m_knowledgeBaseGroupBox.TabStop = false;
            this.m_knowledgeBaseGroupBox.Text = "Knowledge Base";
            // 
            // m_knowledgeBaseLinkLabel
            // 
            this.m_knowledgeBaseLinkLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_knowledgeBaseLinkLabel.Location = new System.Drawing.Point(10, 52);
            this.m_knowledgeBaseLinkLabel.Name = "m_knowledgeBaseLinkLabel";
            this.m_knowledgeBaseLinkLabel.Size = new System.Drawing.Size(442, 27);
            this.m_knowledgeBaseLinkLabel.TabIndex = 1;
            this.m_knowledgeBaseLinkLabel.TabStop = true;
            this.m_knowledgeBaseLinkLabel.Tag = "https://www.ptgrey.com/support/knowledge-base";
            this.m_knowledgeBaseLinkLabel.Text = "Click here to access the Knowledge Base";
            this.m_knowledgeBaseLinkLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.m_knowledgeBaseLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.OnLinkLabelClicked);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.Location = new System.Drawing.Point(7, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(445, 33);
            this.label1.TabIndex = 0;
            this.label1.Text = "Answers to commonly asked questions can often be found in our Knowledge Base.";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // HelpSupportPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_mainGroupBox);
            this.Name = "HelpSupportPage";
            this.Size = new System.Drawing.Size(474, 438);
            this.m_mainGroupBox.ResumeLayout(false);
            this.m_downloadsAndUpdatesGroupBox.ResumeLayout(false);
            this.m_copyMenuStrip.ResumeLayout(false);
            this.m_supportTicketsGroupBox.ResumeLayout(false);
            this.m_knowledgeBaseGroupBox.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_mainGroupBox;
        private System.Windows.Forms.GroupBox m_knowledgeBaseGroupBox;
        private System.Windows.Forms.GroupBox m_downloadsAndUpdatesGroupBox;
        private System.Windows.Forms.GroupBox m_supportTicketsGroupBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.LinkLabel m_knowledgeBaseLinkLabel;
        private System.Windows.Forms.LinkLabel m_downloadLinkLabel;
        private System.Windows.Forms.LinkLabel m_supportTicketLinkLabel;
        private System.Windows.Forms.ContextMenuStrip m_copyMenuStrip;
        private System.Windows.Forms.ToolStripMenuItem m_copyURLItem;
    }
}
