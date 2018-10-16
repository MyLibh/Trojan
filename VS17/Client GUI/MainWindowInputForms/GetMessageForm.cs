using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client_GUI.MainWindowInputForms
{
    public partial class GetMessageForm : Form
    {
        public string message { get; set; }

        public GetMessageForm()
        {
            InitializeComponent();
        }

        private void send_button_Click(object sender, EventArgs e)
        {
            this.message = message_textBox.Text;
            this.Close();
        }

        private void cancel_button_Click(object sender, EventArgs e)
        {
            this.message = "";
            this.Close();
        }
    }
}
