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
            this.ip_maskedTextBox = new System.Windows.Forms.MaskedTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.confirm_button = new System.Windows.Forms.Button();
            this.ip_port_label = new System.Windows.Forms.Label();
            this.port_maskedTextBox = new System.Windows.Forms.MaskedTextBox();
            this.SuspendLayout();
            // 
            // ip_maskedTextBox
            // 
            this.ip_maskedTextBox.Location = new System.Drawing.Point(118, 79);
            this.ip_maskedTextBox.Mask = "###.###.###.###";
            this.ip_maskedTextBox.Name = "ip_maskedTextBox";
            this.ip_maskedTextBox.Size = new System.Drawing.Size(93, 20);
            this.ip_maskedTextBox.TabIndex = 0;
            this.ip_maskedTextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ip_maskedTextBox.TextChanged += new System.EventHandler(this.maskedTextBox1_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(14, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(378, 39);
            this.label1.TabIndex = 1;
            this.label1.Text = "Enter server ip and port";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // confirm_button
            // 
            this.confirm_button.Location = new System.Drawing.Point(81, 155);
            this.confirm_button.Name = "confirm_button";
            this.confirm_button.Size = new System.Drawing.Size(233, 23);
            this.confirm_button.TabIndex = 2;
            this.confirm_button.Text = "Confirm";
            this.confirm_button.UseVisualStyleBackColor = true;
            this.confirm_button.Click += new System.EventHandler(this.confirm_button_Click);
            // 
            // ip_port_label
            // 
            this.ip_port_label.AutoSize = true;
            this.ip_port_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.ip_port_label.Location = new System.Drawing.Point(124, 107);
            this.ip_port_label.Name = "ip_port_label";
            this.ip_port_label.Size = new System.Drawing.Size(0, 20);
            this.ip_port_label.TabIndex = 4;
            // 
            // port_maskedTextBox
            // 
            this.port_maskedTextBox.Location = new System.Drawing.Point(210, 79);
            this.port_maskedTextBox.Mask = "#####";
            this.port_maskedTextBox.Name = "port_maskedTextBox";
            this.port_maskedTextBox.Size = new System.Drawing.Size(40, 20);
            this.port_maskedTextBox.TabIndex = 5;
            this.port_maskedTextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.port_maskedTextBox.ValidatingType = typeof(int);
            this.port_maskedTextBox.TextChanged += new System.EventHandler(this.port_maskedTextBox_TextChanged);
            // 
            // InitProgramForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(404, 195);
            this.Controls.Add(this.port_maskedTextBox);
            this.Controls.Add(this.ip_port_label);
            this.Controls.Add(this.confirm_button);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ip_maskedTextBox);
            this.Name = "InitProgramForm";
            this.Text = "InitProgramForm";
            this.Load += new System.EventHandler(this.InitProgramForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MaskedTextBox ip_maskedTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button confirm_button;
        private System.Windows.Forms.Label ip_port_label;
        private System.Windows.Forms.MaskedTextBox port_maskedTextBox;
    }
}