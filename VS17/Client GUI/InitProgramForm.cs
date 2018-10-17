using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.IO;
using System.Text.RegularExpressions;

namespace Client_GUI
{
    public partial class InitProgramForm : Form
    {
        public static readonly IPEndPoint BAD_IPENDPOINT = new IPEndPoint(IPAddress.Parse("0.0.0.0"), 0);

        public IPEndPoint endpoint { get; set; }

        public InitProgramForm()
        {
            InitializeComponent();
            this.endpoint = BAD_IPENDPOINT;
        }

        private bool CheckInput(string str)
        {
            Regex rgx = new Regex(@"\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)[:](6553[0-5]|655[0-2][0-9]|65[0-4][0-9][0-9]|6[0-4][0-9][0-9][0-9]|[1-5][0-9][0-9][0-9][0-9]|[1-9][0-9][0-9][0-9]|[1-9][0-9][0-9]|[1-9][0-9]|[1-9]?)\b");

            return rgx.IsMatch(str);
        }

        private void InitProgramForm_Load(object sender, EventArgs e)
        {
            if (File.Exists("Connection.properties"))
            {
                string connection_line = File.ReadAllText("Connection.properties");
                string[] ip_port = connection_line.Split(':');

                this.endpoint = new IPEndPoint(IPAddress.Parse(ip_port.First()), int.Parse(ip_port.Last()));
                this.Close();
            }            
        }

        private void confirm_button_Click(object sender, EventArgs e)
        {
            if(!this.CheckInput(ip_port_textBox.Text))
                ip_port_label.Text = "Wrong input";
            else
            {
                File.WriteAllText("Connection.properties", ip_port_label.Text);

                string[] ip_port = ip_port_textBox.Text.Split(':');
                this.endpoint = new IPEndPoint(IPAddress.Parse(ip_port.First()), int.Parse(ip_port.Last()));
                this.Close();
            }
        }

        private void ip_port_textBox_TextChanged(object sender, EventArgs e)
        {
            ip_port_label.Text = ip_port_textBox.Text;
        }
    }
}
