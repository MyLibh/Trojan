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
            this.confirm_button = new System.Windows.Forms.Button();
            this.ip_port_label = new System.Windows.Forms.Label();
            this.ip_port_textBox = new System.Windows.Forms.TextBox();
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
            // confirm_button
            // 
            this.confirm_button.BackColor = System.Drawing.Color.Lime;
            this.confirm_button.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.confirm_button.Location = new System.Drawing.Point(81, 155);
            this.confirm_button.Name = "confirm_button";
            this.confirm_button.Size = new System.Drawing.Size(233, 23);
            this.confirm_button.TabIndex = 2;
            this.confirm_button.Text = "Confirm";
            this.confirm_button.UseVisualStyleBackColor = false;
            this.confirm_button.Click += new System.EventHandler(this.confirm_button_Click);
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
            // ip_port_textBox
            // 
            this.ip_port_textBox.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ip_port_textBox.Location = new System.Drawing.Point(81, 74);
            this.ip_port_textBox.MaxLength = 21;
            this.ip_port_textBox.Name = "ip_port_textBox";
            this.ip_port_textBox.Size = new System.Drawing.Size(233, 30);
            this.ip_port_textBox.TabIndex = 6;
            this.ip_port_textBox.Text = "127.0.0.1:20000";
            this.ip_port_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ip_port_textBox.TextChanged += new System.EventHandler(this.ip_port_textBox_TextChanged);
            // 
            // InitProgramForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(400, 195);
            this.Controls.Add(this.ip_port_textBox);
            this.Controls.Add(this.ip_port_label);
            this.Controls.Add(this.confirm_button);
            this.Controls.Add(this.label1);
            this.Name = "InitProgramForm";
            this.Text = "InitProgramForm";
            this.Load += new System.EventHandler(this.InitProgramForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button confirm_button;
        private System.Windows.Forms.Label ip_port_label;
        private System.Windows.Forms.TextBox ip_port_textBox;
    }
}