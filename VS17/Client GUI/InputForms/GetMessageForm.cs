// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

using System;
using System.Windows.Forms;

namespace Client_GUI.MainWindowInputForms
{
    public partial class GetMessageForm : Form
    {
        #region Properties

        public string Message { get; set; }

        #endregion

        #region Events

        private void GetMessageForm_Load(object sender, EventArgs e)
        {

        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            this.Message = messageTextBox.Text;

            this.Close();
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            this.Message = string.Empty;

            this.Close();
        }

        #endregion

        #region Constructors

        public GetMessageForm()
        {
            this.Message = string.Empty;

            InitializeComponent();
        }

        #endregion
    }
}
