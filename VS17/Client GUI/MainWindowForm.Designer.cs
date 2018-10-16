namespace Client_GUI
{
    partial class MainWindowForm
    {
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
                m_client.Dispose();
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
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.trojanToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.messageBoxToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.blockInputToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.onToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.offToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.remoteDesktopViewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewWebcamToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.keyboardControlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.mouseControlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startToolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.executeShellToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fIleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.encryptToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.decryptToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.playSoundToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startToolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.serverToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.updateIPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.serverToolStripMenuItem,
            this.trojanToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // trojanToolStripMenuItem
            // 
            this.trojanToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.messageBoxToolStripMenuItem,
            this.remoteDesktopViewToolStripMenuItem,
            this.viewWebcamToolStripMenuItem,
            this.keyboardControlToolStripMenuItem,
            this.mouseControlToolStripMenuItem,
            this.executeShellToolStripMenuItem,
            this.fIleToolStripMenuItem,
            this.blockInputToolStripMenuItem,
            this.playSoundToolStripMenuItem});
            this.trojanToolStripMenuItem.Name = "trojanToolStripMenuItem";
            this.trojanToolStripMenuItem.Size = new System.Drawing.Size(66, 20);
            this.trojanToolStripMenuItem.Text = "Function";
            // 
            // messageBoxToolStripMenuItem
            // 
            this.messageBoxToolStripMenuItem.Name = "messageBoxToolStripMenuItem";
            this.messageBoxToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.messageBoxToolStripMenuItem.Text = "MessageBox";
            this.messageBoxToolStripMenuItem.Click += new System.EventHandler(this.messageBoxToolStripMenuItem_Click);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.aboutToolStripMenuItem.Text = "About";
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // blockInputToolStripMenuItem
            // 
            this.blockInputToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.onToolStripMenuItem,
            this.offToolStripMenuItem});
            this.blockInputToolStripMenuItem.Enabled = false;
            this.blockInputToolStripMenuItem.Name = "blockInputToolStripMenuItem";
            this.blockInputToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.blockInputToolStripMenuItem.Text = "BlockInput";
            // 
            // onToolStripMenuItem
            // 
            this.onToolStripMenuItem.Name = "onToolStripMenuItem";
            this.onToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.onToolStripMenuItem.Text = "On";
            // 
            // offToolStripMenuItem
            // 
            this.offToolStripMenuItem.Name = "offToolStripMenuItem";
            this.offToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.offToolStripMenuItem.Text = "Off";
            // 
            // remoteDesktopViewToolStripMenuItem
            // 
            this.remoteDesktopViewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startToolStripMenuItem,
            this.stopToolStripMenuItem});
            this.remoteDesktopViewToolStripMenuItem.Enabled = false;
            this.remoteDesktopViewToolStripMenuItem.Name = "remoteDesktopViewToolStripMenuItem";
            this.remoteDesktopViewToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.remoteDesktopViewToolStripMenuItem.Text = "ViewDesktop";
            // 
            // startToolStripMenuItem
            // 
            this.startToolStripMenuItem.Name = "startToolStripMenuItem";
            this.startToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.startToolStripMenuItem.Text = "Start";
            // 
            // stopToolStripMenuItem
            // 
            this.stopToolStripMenuItem.Name = "stopToolStripMenuItem";
            this.stopToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.stopToolStripMenuItem.Text = "Stop";
            // 
            // viewWebcamToolStripMenuItem
            // 
            this.viewWebcamToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startToolStripMenuItem1,
            this.stopToolStripMenuItem1});
            this.viewWebcamToolStripMenuItem.Enabled = false;
            this.viewWebcamToolStripMenuItem.Name = "viewWebcamToolStripMenuItem";
            this.viewWebcamToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.viewWebcamToolStripMenuItem.Text = "ViewWebcam";
            // 
            // startToolStripMenuItem1
            // 
            this.startToolStripMenuItem1.Name = "startToolStripMenuItem1";
            this.startToolStripMenuItem1.Size = new System.Drawing.Size(180, 22);
            this.startToolStripMenuItem1.Text = "Start";
            // 
            // stopToolStripMenuItem1
            // 
            this.stopToolStripMenuItem1.Name = "stopToolStripMenuItem1";
            this.stopToolStripMenuItem1.Size = new System.Drawing.Size(180, 22);
            this.stopToolStripMenuItem1.Text = "Stop";
            // 
            // keyboardControlToolStripMenuItem
            // 
            this.keyboardControlToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startToolStripMenuItem2,
            this.stopToolStripMenuItem2});
            this.keyboardControlToolStripMenuItem.Enabled = false;
            this.keyboardControlToolStripMenuItem.Name = "keyboardControlToolStripMenuItem";
            this.keyboardControlToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.keyboardControlToolStripMenuItem.Text = "KeyboardControl";
            // 
            // startToolStripMenuItem2
            // 
            this.startToolStripMenuItem2.Name = "startToolStripMenuItem2";
            this.startToolStripMenuItem2.Size = new System.Drawing.Size(180, 22);
            this.startToolStripMenuItem2.Text = "Start";
            // 
            // stopToolStripMenuItem2
            // 
            this.stopToolStripMenuItem2.Name = "stopToolStripMenuItem2";
            this.stopToolStripMenuItem2.Size = new System.Drawing.Size(180, 22);
            this.stopToolStripMenuItem2.Text = "Stop";
            // 
            // mouseControlToolStripMenuItem
            // 
            this.mouseControlToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startToolStripMenuItem3,
            this.stopToolStripMenuItem3});
            this.mouseControlToolStripMenuItem.Enabled = false;
            this.mouseControlToolStripMenuItem.Name = "mouseControlToolStripMenuItem";
            this.mouseControlToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.mouseControlToolStripMenuItem.Text = "MouseControl";
            // 
            // startToolStripMenuItem3
            // 
            this.startToolStripMenuItem3.Name = "startToolStripMenuItem3";
            this.startToolStripMenuItem3.Size = new System.Drawing.Size(180, 22);
            this.startToolStripMenuItem3.Text = "Start";
            // 
            // stopToolStripMenuItem3
            // 
            this.stopToolStripMenuItem3.Name = "stopToolStripMenuItem3";
            this.stopToolStripMenuItem3.Size = new System.Drawing.Size(180, 22);
            this.stopToolStripMenuItem3.Text = "Stop";
            // 
            // executeShellToolStripMenuItem
            // 
            this.executeShellToolStripMenuItem.Enabled = false;
            this.executeShellToolStripMenuItem.Name = "executeShellToolStripMenuItem";
            this.executeShellToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.executeShellToolStripMenuItem.Text = "ExecuteShell";
            // 
            // fIleToolStripMenuItem
            // 
            this.fIleToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.encryptToolStripMenuItem,
            this.decryptToolStripMenuItem,
            this.importToolStripMenuItem,
            this.exportToolStripMenuItem});
            this.fIleToolStripMenuItem.Enabled = false;
            this.fIleToolStripMenuItem.Name = "fIleToolStripMenuItem";
            this.fIleToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.fIleToolStripMenuItem.Text = "File";
            // 
            // encryptToolStripMenuItem
            // 
            this.encryptToolStripMenuItem.Name = "encryptToolStripMenuItem";
            this.encryptToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.encryptToolStripMenuItem.Text = "Encrypt";
            // 
            // decryptToolStripMenuItem
            // 
            this.decryptToolStripMenuItem.Name = "decryptToolStripMenuItem";
            this.decryptToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.decryptToolStripMenuItem.Text = "Decrypt";
            // 
            // importToolStripMenuItem
            // 
            this.importToolStripMenuItem.Name = "importToolStripMenuItem";
            this.importToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.importToolStripMenuItem.Text = "Import";
            // 
            // exportToolStripMenuItem
            // 
            this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
            this.exportToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.exportToolStripMenuItem.Text = "Export";
            // 
            // playSoundToolStripMenuItem
            // 
            this.playSoundToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startToolStripMenuItem4,
            this.stopToolStripMenuItem4});
            this.playSoundToolStripMenuItem.Enabled = false;
            this.playSoundToolStripMenuItem.Name = "playSoundToolStripMenuItem";
            this.playSoundToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.playSoundToolStripMenuItem.Text = "PlaySound";
            // 
            // startToolStripMenuItem4
            // 
            this.startToolStripMenuItem4.Name = "startToolStripMenuItem4";
            this.startToolStripMenuItem4.Size = new System.Drawing.Size(180, 22);
            this.startToolStripMenuItem4.Text = "Start";
            // 
            // stopToolStripMenuItem4
            // 
            this.stopToolStripMenuItem4.Name = "stopToolStripMenuItem4";
            this.stopToolStripMenuItem4.Size = new System.Drawing.Size(180, 22);
            this.stopToolStripMenuItem4.Text = "Stop";
            // 
            // serverToolStripMenuItem
            // 
            this.serverToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.updateIPToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
            this.serverToolStripMenuItem.Name = "serverToolStripMenuItem";
            this.serverToolStripMenuItem.Size = new System.Drawing.Size(51, 20);
            this.serverToolStripMenuItem.Text = "Server";
            // 
            // updateIPToolStripMenuItem
            // 
            this.updateIPToolStripMenuItem.Name = "updateIPToolStripMenuItem";
            this.updateIPToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.updateIPToolStripMenuItem.Text = "Update IP";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(177, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // MainWindowForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainWindowForm";
            this.Text = "Trojan Client GUI";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem trojanToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem messageBoxToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem serverToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem updateIPToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem remoteDesktopViewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewWebcamToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem keyboardControlToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem mouseControlToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startToolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem executeShellToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fIleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem encryptToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem decryptToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem blockInputToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem onToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem offToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem playSoundToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startToolStripMenuItem4;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem4;
    }
}

