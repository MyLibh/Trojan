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

namespace Client_GUI
{
    public partial class InitProgramForm : Form
    {
        public IPEndPoint endpoint { get; set; }

        public InitProgramForm()
        {
            InitializeComponent();
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

            ip_maskedTextBox.ValidatingType = typeof(System.Net.IPAddress);
            ip_maskedTextBox.Text = "127.000.000.001";

            port_maskedTextBox.ValidatingType = typeof(Int16);
            port_maskedTextBox.Text = "20000";
        }

        private void maskedTextBox1_TextChanged(object sender, EventArgs e)
        {
            ip_port_label.Text = ip_maskedTextBox.Text + ":" + port_maskedTextBox.Text;
        }

        private void confirm_button_Click(object sender, EventArgs e)
        {
            IPAddress ip;
            if (IPAddress.TryParse(ip_maskedTextBox.Text, out ip))
            {
                Int16 port;
                if(Int16.TryParse(port_maskedTextBox.Text, out port))
                {
                    IPEndPoint endpoint = new IPEndPoint(ip, port);
                    File.WriteAllText("Connection.properties", endpoint.ToString());
                    this.endpoint = endpoint;
                    this.Close();
                }
                else
                {
                    ip_port_label.Text = "Wrong port";
                }
            }
            else
            {
                ip_port_label.Text = "Wrong IP";
            }
        }

        private void port_maskedTextBox_TextChanged(object sender, EventArgs e)
        {
            ip_port_label.Text = ip_maskedTextBox.Text + ":" + port_maskedTextBox.Text;
        }
    }
}
