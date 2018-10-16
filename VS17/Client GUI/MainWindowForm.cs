using System;
using System.Windows.Forms;
using System.Net;
using System.IO;

using Client_GUI.MainWindowInputForms;

namespace Client_GUI
{
    public partial class MainWindowForm : Form
    {
        public bool reinit { get; set; }

        NativeClient.NativeMethods m_client;

        public MainWindowForm(IPEndPoint endpoint)
        {       
            m_client = new NativeClient.NativeMethods(endpoint);
            reinit = false;

            InitializeComponent();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            
        }

        private void messageBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetMessageForm form = new GetMessageForm();
            form.ShowDialog();
            if(form.message != "")
                m_client.SendCommand("message " + form.message);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void updateIPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            File.Delete("Connection.properties");
            this.reinit = true;

            this.Close();
        }
    }
}
