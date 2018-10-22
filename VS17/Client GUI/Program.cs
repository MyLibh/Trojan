// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

using System;
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
                if(initProgramForm.IPEndPoint == InitProgramForm.BAD_IPENDPOINT)
                    Application.Run(initProgramForm);

                if (initProgramForm.IPEndPoint != InitProgramForm.BAD_IPENDPOINT)
                { 
                    mainWindowForm = new MainWindowForm(initProgramForm.IPEndPoint);
                    Application.Run(mainWindowForm);
                    mainWindowForm.Dispose();

                    if (!mainWindowForm.Reinit)
                        break;
                }
                else
                    break;
            }
        }
    }
}
