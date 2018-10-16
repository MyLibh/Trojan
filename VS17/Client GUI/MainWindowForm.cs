using System;
using System.Windows.Forms;
using System.Net;

using Client_GUI.MainWindowInputForms;

namespace Client_GUI
{
    public partial class MainWindowForm : Form
    {
        NativeClient.NativeMethods m_client;

        public MainWindowForm(IPEndPoint endpoint)
        {       
            m_client = new NativeClient.NativeMethods(endpoint);
          
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
    }
}
