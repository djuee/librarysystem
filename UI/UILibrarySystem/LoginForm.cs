using System;
using System.Windows.Forms;
using UILibrarySystem.Api;
using UILibrarySystem.Api.LibraryClient.Api;

namespace UILibrarySystem
{
    public partial class LoginForm : Form
    {
        private readonly ApiService _api = new();

        public LoginForm()
        {
            InitializeComponent();
        }

        private async void btnLogin_Click(object sender, EventArgs e)
        {
            string username = txtUsername.Text;
            string password = txtPassword.Text;

            var result = await _api.LoginAndGetInfoAsync(username, password);
            if (result != null)
            {
                SessionManager.UserId = result.Id;
                SessionManager.Username = result.Username;
                SessionManager.IsAdmin = result.Role == 0;
                if (SessionManager.IsAdmin)
                {
                    MessageBox.Show("ТЫ АДМИН", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                MessageBox.Show("Успешный вход", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
                new ReaderForm().Show();
                this.Hide();
            }
            else
            {
                MessageBox.Show("Неверные данные", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnRegister_Click(object sender, EventArgs e)
        {
            new RegisterForm().Show();
            this.Hide();
        }
    }
}