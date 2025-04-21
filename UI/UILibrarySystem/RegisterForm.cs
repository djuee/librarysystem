using System;
using System.Windows.Forms;
using UILibrarySystem.Api.LibraryClient.Api;

namespace UILibrarySystem
{
    public partial class RegisterForm : Form
    {
        private readonly ApiService _api = new();

        public RegisterForm()
        {
            InitializeComponent();
        }

        private async void btnRegister_Click(object sender, EventArgs e)
        {
            string username = txtUsername.Text.Trim();
            string password = txtPassword.Text.Trim();

            if (string.IsNullOrWhiteSpace(username) || string.IsNullOrWhiteSpace(password))
            {
                MessageBox.Show("Введите имя пользователя и пароль", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            bool success = await _api.RegisterAsync(username, password);
            if (success)
            {
                MessageBox.Show("Регистрация успешна!", "Готово", MessageBoxButtons.OK, MessageBoxIcon.Information);
                new LoginForm().Show();
                this.Hide();
            }
            else
            {
                MessageBox.Show("Имя пользователя занято", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            new LoginForm().Show();
            this.Hide();
        }
    }
}
