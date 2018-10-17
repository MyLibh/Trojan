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

            MainWindowForm mainWindowForm;
            while (true)
            { 
                InitProgramForm initProgramForm = new InitProgramForm();
                Application.Run(initProgramForm);

                if (initProgramForm.endpoint != InitProgramForm.BAD_IPENDPOINT)
                {
                    mainWindowForm = new MainWindowForm(initProgramForm.endpoint);
                    Application.Run(mainWindowForm);
                    mainWindowForm.Dispose();

                    if (!mainWindowForm.reinit)
                        break;
                }
                else
                    break;
            }
        }
    }
}
