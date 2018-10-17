namespace Client_GUI
{
    partial class InitProgramForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.confirmButton = new System.Windows.Forms.Button();
            this.ip_port_label = new System.Windows.Forms.Label();
            this.ipAndPortTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Consolas", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(14, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(375, 32);
            this.label1.TabIndex = 1;
            this.label1.Text = "Enter server ip and port";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // confirmButton
            // 
            this.confirmButton.BackColor = System.Drawing.Color.Lime;
            this.confirmButton.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.confirmButton.Location = new System.Drawing.Point(81, 155);
            this.confirmButton.Name = "confirmButton";
            this.confirmButton.Size = new System.Drawing.Size(233, 23);
            this.confirmButton.TabIndex = 2;
            this.confirmButton.Text = "Confirm";
            this.confirmButton.UseVisualStyleBackColor = false;
            this.confirmButton.Click += new System.EventHandler(this.confirmButton_Click);
            // 
            // ip_port_label
            // 
            this.ip_port_label.AutoSize = true;
            this.ip_port_label.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ip_port_label.Location = new System.Drawing.Point(81, 121);
            this.ip_port_label.MinimumSize = new System.Drawing.Size(233, 0);
            this.ip_port_label.Name = "ip_port_label";
            this.ip_port_label.Size = new System.Drawing.Size(233, 22);
            this.ip_port_label.TabIndex = 4;
            this.ip_port_label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ipAndPortTextBox
            // 
            this.ipAndPortTextBox.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ipAndPortTextBox.Location = new System.Drawing.Point(81, 74);
            this.ipAndPortTextBox.MaxLength = 21;
            this.ipAndPortTextBox.Name = "ipAndPortTextBox";
            this.ipAndPortTextBox.Size = new System.Drawing.Size(233, 30);
            this.ipAndPortTextBox.TabIndex = 6;
            this.ipAndPortTextBox.Text = "127.0.0.1:20000";
            this.ipAndPortTextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ipAndPortTextBox.Click += new System.EventHandler(this.ipAndPortTextBox_Click);
            // 
            // InitProgramForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Bisque;
            this.ClientSize = new System.Drawing.Size(400, 195);
            this.Controls.Add(this.ipAndPortTextBox);
            this.Controls.Add(this.ip_port_label);
            this.Controls.Add(this.confirmButton);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "InitProgramForm";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Initialization";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.InitProgramForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button confirmButton;
        private System.Windows.Forms.Label ip_port_label;
        private System.Windows.Forms.TextBox ipAndPortTextBox;
    }
}