using System;
using System.Windows.Forms;
using System.Net;

namespace Client_GUI
{
    public partial class MainWindow : Form
    {
        NativeClient.NativeMethods m_client;

        public MainWindow()
        {       
            m_client = new NativeClient.NativeMethods(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 20000));
          
            InitializeComponent();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            
        }

        private void messageBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_client.SendCommand("message Hello");
        }
    }
}
