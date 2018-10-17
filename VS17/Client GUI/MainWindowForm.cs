using System;
using System.Windows.Forms;
using System.Net;
using System.IO;

using Client_GUI.MainWindowInputForms;

namespace Client_GUI
{
    public partial class MainWindowForm : Form
    {
        #region Fields

        private NativeClient.Client client;

        #endregion

        #region Properties

        public bool Reinit { get; set; }

        #endregion

        #region Events

        private void MainWindow_Load(object sender, EventArgs e)
        {
            
        }

        private void messageBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetMessageForm form = new GetMessageForm();
            form.ShowDialog();
            if(form.Message != string.Empty)
                this.client.SendCommand("message " + form.Message);
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void updateIPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            File.Delete("Connection.properties");
            this.Reinit = true;

            this.Close();
        }

        private void keyboardControlOnToolStripMenuItem_Click(object sender, EventArgs e)
        {
            keyboardControlOnToolStripMenuItem.Enabled = false;
            keyboardControlOffToolStripMenuItem.Enabled = true;

            this.client.SendCommand("kbon"); // TODO: in thread
        }

        private void keyboardControlOffToolStripMenuItem_Click(object sender, EventArgs e)
        {
            keyboardControlOffToolStripMenuItem.Enabled = false;
            keyboardControlOnToolStripMenuItem.Enabled = true;

            this.client.SendCommand("kboff");
        }

        private void mouseControlOnToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mouseControlOnToolStripMenuItem.Enabled = false;
            mouseControlOffToolStripMenuItem.Enabled = true;

            this.client.SendCommand("mon"); // TODO: in thread
        }

        private void mouseControlOffToolStripMenuItem_Click(object sender, EventArgs e)
        {
            mouseControlOffToolStripMenuItem.Enabled = false;
            mouseControlOnToolStripMenuItem.Enabled = true;

            this.client.SendCommand("moff");
        }

        private void executeCmdToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GetMessageForm form = new GetMessageForm();
            form.ShowDialog();
            if (form.Message != string.Empty)
                this.client.SendCommand("cmd " + form.Message);
        }

        private void blockInputOnToolStripMenuItem_Click(object sender, EventArgs e)
        {
            blockInputOnToolStripMenuItem.Enabled = false;
            blockInputOffToolStripMenuItem.Enabled = true;

            this.client.SendCommand("bion");
        }

        private void blockInputOffToolStripMenuItem_Click(object sender, EventArgs e)
        {
            blockInputOffToolStripMenuItem.Enabled = false;
            blockInputOnToolStripMenuItem.Enabled = true;

            this.client.SendCommand("bioff");
        }

        #endregion

        #region Constructors

        public MainWindowForm(IPEndPoint ipEndPoint)
        {
            this.client = new NativeClient.Client(ipEndPoint);
            this.Reinit   = false;

            InitializeComponent();
        }

        #endregion
    }
}
