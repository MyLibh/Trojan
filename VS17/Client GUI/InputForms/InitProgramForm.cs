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
        #region Constants

        public static readonly IPEndPoint BAD_IPENDPOINT = new IPEndPoint(IPAddress.Parse("255.255.255.255"), 65535);

        #endregion

        #region Properties

        public IPEndPoint IPEndPoint { get; set; }

        #endregion

        #region Methods
 
        private bool CheckInput(string str)
        {
            Regex rgx = new Regex(@"\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)[:](6553[0-5]|655[0-2][0-9]|65[0-4][0-9][0-9]|6[0-4][0-9][0-9][0-9]|[1-5][0-9][0-9][0-9][0-9]|[1-9][0-9][0-9][0-9]|[1-9][0-9][0-9]|[1-9][0-9]|[1-9]?)\b");

            return rgx.IsMatch(str);
        }

        #endregion

        #region Events

        private void InitProgramForm_Load(object sender, EventArgs e)
        {

        }

        private void confirmButton_Click(object sender, EventArgs e)
        {
            if(!this.CheckInput(ipAndPortTextBox.Text))
                ip_port_label.Text = "Wrong input";
            else
            {
                File.WriteAllText("Connection.properties", ipAndPortTextBox.Text);

                string[] ip_port = ipAndPortTextBox.Text.Split(':');
                this.IPEndPoint = new IPEndPoint(IPAddress.Parse(ip_port.First()), Int16.Parse(ip_port.Last()));

                this.Close();
            }
        }

        private void ipAndPortTextBox_Click(object sender, EventArgs e)
        {
            ipAndPortTextBox.Text = "";
        }

        #endregion

        #region Constructors

        public InitProgramForm()
        {
            if (File.Exists("Connection.properties"))
            {
                string   connectionLine = File.ReadAllText("Connection.properties");
                string[] ipAndPort      = connectionLine.Split(':');

                this.IPEndPoint = new IPEndPoint(IPAddress.Parse(ipAndPort.First()), int.Parse(ipAndPort.Last()));
            }
            else
                this.IPEndPoint = BAD_IPENDPOINT;

            InitializeComponent();  
        }


        #endregion
    }
}
