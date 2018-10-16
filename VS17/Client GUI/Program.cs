using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client_GUI
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            InitProgramForm initProgramForm = new InitProgramForm();
            Application.Run(initProgramForm);

            MainWindowForm mainWindowForm = new MainWindowForm(initProgramForm.endpoint);
            Application.Run(mainWindowForm);
            mainWindowForm.Dispose();
        }
    }
}
