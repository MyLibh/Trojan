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
                client.Dispose();
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
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.clientToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.updateIPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.functionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.messageBoxToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.remoteDesktopViewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewWebcamToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.keyboardControlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.keyboardControlOnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.keyboardControlOffToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mouseControlToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mouseControlOnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mouseControlOffToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.executeShellToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fIleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.encryptToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.decryptToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.importToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.blockInputToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.blockInputOnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.blockInputOffToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.playSoundToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startToolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.stopToolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.clientToolStripMenuItem,
            this.functionsToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(800, 24);
            this.menuStrip.TabIndex = 0;
            // 
            // clientToolStripMenuItem
            // 
            this.clientToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.updateIPToolStripMenuItem,
            this.toolStripSeparator1,
            this.exitToolStripMenuItem});
            this.clientToolStripMenuItem.Name = "clientToolStripMenuItem";
            this.clientToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.clientToolStripMenuItem.Text = "Client";
            // 
            // updateIPToolStripMenuItem
            // 
            this.updateIPToolStripMenuItem.Name = "updateIPToolStripMenuItem";
            this.updateIPToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.updateIPToolStripMenuItem.Text = "Update IP";
            this.updateIPToolStripMenuItem.Click += new System.EventHandler(this.updateIPToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(134, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // functionsToolStripMenuItem
            // 
            this.functionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.messageBoxToolStripMenuItem,
            this.remoteDesktopViewToolStripMenuItem,
            this.viewWebcamToolStripMenuItem,
            this.keyboardControlToolStripMenuItem,
            this.mouseControlToolStripMenuItem,
            this.executeShellToolStripMenuItem,
            this.fIleToolStripMenuItem,
            this.blockInputToolStripMenuItem,
            this.playSoundToolStripMenuItem});
            this.functionsToolStripMenuItem.Name = "functionsToolStripMenuItem";
            this.functionsToolStripMenuItem.Size = new System.Drawing.Size(82, 20);
            this.functionsToolStripMenuItem.Text = "Functions";
            // 
            // messageBoxToolStripMenuItem
            // 
            this.messageBoxToolStripMenuItem.Name = "messageBoxToolStripMenuItem";
            this.messageBoxToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.messageBoxToolStripMenuItem.Text = "MessageBox";
            this.messageBoxToolStripMenuItem.Click += new System.EventHandler(this.messageBoxToolStripMenuItem_Click);
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
            this.startToolStripMenuItem.Size = new System.Drawing.Size(109, 22);
            this.startToolStripMenuItem.Text = "Start";
            // 
            // stopToolStripMenuItem
            // 
            this.stopToolStripMenuItem.Name = "stopToolStripMenuItem";
            this.stopToolStripMenuItem.Size = new System.Drawing.Size(109, 22);
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
            this.startToolStripMenuItem1.Size = new System.Drawing.Size(109, 22);
            this.startToolStripMenuItem1.Text = "Start";
            // 
            // stopToolStripMenuItem1
            // 
            this.stopToolStripMenuItem1.Name = "stopToolStripMenuItem1";
            this.stopToolStripMenuItem1.Size = new System.Drawing.Size(109, 22);
            this.stopToolStripMenuItem1.Text = "Stop";
            // 
            // keyboardControlToolStripMenuItem
            // 
            this.keyboardControlToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.keyboardControlOnToolStripMenuItem,
            this.keyboardControlOffToolStripMenuItem});
            this.keyboardControlToolStripMenuItem.Name = "keyboardControlToolStripMenuItem";
            this.keyboardControlToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.keyboardControlToolStripMenuItem.Text = "KeyboardControl";
            // 
            // keyboardControlOnToolStripMenuItem
            // 
            this.keyboardControlOnToolStripMenuItem.Name = "keyboardControlOnToolStripMenuItem";
            this.keyboardControlOnToolStripMenuItem.Size = new System.Drawing.Size(95, 22);
            this.keyboardControlOnToolStripMenuItem.Text = "On";
            this.keyboardControlOnToolStripMenuItem.Click += new System.EventHandler(this.keyboardControlOnToolStripMenuItem_Click);
            // 
            // keyboardControlOffToolStripMenuItem
            // 
            this.keyboardControlOffToolStripMenuItem.Enabled = false;
            this.keyboardControlOffToolStripMenuItem.Name = "keyboardControlOffToolStripMenuItem";
            this.keyboardControlOffToolStripMenuItem.Size = new System.Drawing.Size(95, 22);
            this.keyboardControlOffToolStripMenuItem.Text = "Off";
            this.keyboardControlOffToolStripMenuItem.Click += new System.EventHandler(this.keyboardControlOffToolStripMenuItem_Click);
            // 
            // mouseControlToolStripMenuItem
            // 
            this.mouseControlToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mouseControlOnToolStripMenuItem,
            this.mouseControlOffToolStripMenuItem});
            this.mouseControlToolStripMenuItem.Name = "mouseControlToolStripMenuItem";
            this.mouseControlToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.mouseControlToolStripMenuItem.Text = "MouseControl";
            // 
            // mouseControlOnToolStripMenuItem
            // 
            this.mouseControlOnToolStripMenuItem.Name = "mouseControlOnToolStripMenuItem";
            this.mouseControlOnToolStripMenuItem.Size = new System.Drawing.Size(95, 22);
            this.mouseControlOnToolStripMenuItem.Text = "On";
            this.mouseControlOnToolStripMenuItem.Click += new System.EventHandler(this.mouseControlOnToolStripMenuItem_Click);
            // 
            // mouseControlOffToolStripMenuItem
            // 
            this.mouseControlOffToolStripMenuItem.Enabled = false;
            this.mouseControlOffToolStripMenuItem.Name = "mouseControlOffToolStripMenuItem";
            this.mouseControlOffToolStripMenuItem.Size = new System.Drawing.Size(95, 22);
            this.mouseControlOffToolStripMenuItem.Text = "Off";
            this.mouseControlOffToolStripMenuItem.Click += new System.EventHandler(this.mouseControlOffToolStripMenuItem_Click);
            // 
            // executeShellToolStripMenuItem
            // 
            this.executeShellToolStripMenuItem.Name = "executeShellToolStripMenuItem";
            this.executeShellToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.executeShellToolStripMenuItem.Text = "ExecuteCmd";
            this.executeShellToolStripMenuItem.Click += new System.EventHandler(this.executeCmdToolStripMenuItem_Click);
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
            this.encryptToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
            this.encryptToolStripMenuItem.Text = "Encrypt";
            // 
            // decryptToolStripMenuItem
            // 
            this.decryptToolStripMenuItem.Name = "decryptToolStripMenuItem";
            this.decryptToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
            this.decryptToolStripMenuItem.Text = "Decrypt";
            // 
            // importToolStripMenuItem
            // 
            this.importToolStripMenuItem.Name = "importToolStripMenuItem";
            this.importToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
            this.importToolStripMenuItem.Text = "Import";
            // 
            // exportToolStripMenuItem
            // 
            this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
            this.exportToolStripMenuItem.Size = new System.Drawing.Size(123, 22);
            this.exportToolStripMenuItem.Text = "Export";
            // 
            // blockInputToolStripMenuItem
            // 
            this.blockInputToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.blockInputOnToolStripMenuItem,
            this.blockInputOffToolStripMenuItem});
            this.blockInputToolStripMenuItem.Name = "blockInputToolStripMenuItem";
            this.blockInputToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.blockInputToolStripMenuItem.Text = "BlockInput";
            // 
            // blockInputOnToolStripMenuItem
            // 
            this.blockInputOnToolStripMenuItem.Name = "blockInputOnToolStripMenuItem";
            this.blockInputOnToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.blockInputOnToolStripMenuItem.Text = "On";
            this.blockInputOnToolStripMenuItem.Click += new System.EventHandler(this.blockInputOnToolStripMenuItem_Click);
            // 
            // blockInputOffToolStripMenuItem
            // 
            this.blockInputOffToolStripMenuItem.Enabled = false;
            this.blockInputOffToolStripMenuItem.Name = "blockInputOffToolStripMenuItem";
            this.blockInputOffToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.blockInputOffToolStripMenuItem.Text = "Off";
            this.blockInputOffToolStripMenuItem.Click += new System.EventHandler(this.blockInputOffToolStripMenuItem_Click);
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
            this.startToolStripMenuItem4.Size = new System.Drawing.Size(109, 22);
            this.startToolStripMenuItem4.Text = "Start";
            // 
            // stopToolStripMenuItem4
            // 
            this.stopToolStripMenuItem4.Name = "stopToolStripMenuItem4";
            this.stopToolStripMenuItem4.Size = new System.Drawing.Size(109, 22);
            this.stopToolStripMenuItem4.Text = "Stop";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Enabled = false;
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.aboutToolStripMenuItem.Text = "About";
            // 
            // MainWindowForm
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "MainWindowForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Trojan Client GUI";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem functionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem messageBoxToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem clientToolStripMenuItem;
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
        private System.Windows.Forms.ToolStripMenuItem keyboardControlOnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem keyboardControlOffToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mouseControlToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mouseControlOnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mouseControlOffToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem executeShellToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fIleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem encryptToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem decryptToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem importToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem blockInputToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem blockInputOnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem blockInputOffToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem playSoundToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startToolStripMenuItem4;
        private System.Windows.Forms.ToolStripMenuItem stopToolStripMenuItem4;
    }
}

