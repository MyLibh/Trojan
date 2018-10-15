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
            try
            {
                m_client = new NativeClient.NativeMethods(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 20000));
            }
            catch (System.NullReferenceException excpt)
            {
                MessageBox.Show(excpt.Message);
            }

            InitializeComponent();
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            
        }

        private void messageBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_client.SendCommand("message Hello");
            Console.WriteLine("send");
        }
    }
}
