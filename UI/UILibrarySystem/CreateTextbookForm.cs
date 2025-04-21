using System;
using System.Drawing;
using System.Windows.Forms;
using UILibrarySystem.Models;

namespace UILibrarySystem
{
    public partial class CreateTextbookForm : Form
    {
        public string Title => txtTitle.Text;
        public string Author => txtAuthor.Text;
        public Subject Subject => (Subject)cbSubject.SelectedItem;
        public Level Level => (Level)cbLevel.SelectedItem;
        public string Edition => txtEdition.Text;

        private TextBox txtTitle;
        private TextBox txtAuthor;
        private ComboBox cbSubject;
        private ComboBox cbLevel;
        private TextBox txtEdition;
        private Button btnCreate;
        private Button btnCancel;

        public CreateTextbookForm()
        {
            Text = "Создание учебника";
            Size = new Size(400, 350);
            StartPosition = FormStartPosition.CenterScreen;
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            InitializeForm();
        }

        private void InitializeForm()
        {
            // Заголовки
            var lblTitle = new Label() { Text = "Название:", Location = new Point(20, 20), AutoSize = true };
            txtTitle = new TextBox() { Location = new Point(150, 20), Width = 200 };

            var lblAuthor = new Label() { Text = "Автор:", Location = new Point(20, 60), AutoSize = true };
            txtAuthor = new TextBox() { Location = new Point(150, 60), Width = 200 };

            var lblSubject = new Label() { Text = "Предмет:", Location = new Point(20, 100), AutoSize = true };
            cbSubject = new ComboBox() { Location = new Point(150, 100), Width = 200, DropDownStyle = ComboBoxStyle.DropDownList };
            cbSubject.DataSource = Enum.GetValues(typeof(Subject));

            var lblLevel = new Label() { Text = "Уровень:", Location = new Point(20, 140), AutoSize = true };
            cbLevel = new ComboBox() { Location = new Point(150, 140), Width = 200, DropDownStyle = ComboBoxStyle.DropDownList };
            cbLevel.DataSource = Enum.GetValues(typeof(Level));

            var lblEdition = new Label() { Text = "Издание:", Location = new Point(20, 180), AutoSize = true };
            txtEdition = new TextBox() { Location = new Point(150, 180), Width = 200 };

            btnCreate = new Button() { Text = "Создать", Location = new Point(80, 230), Width = 100 };
            btnCreate.Click += BtnCreate_Click;

            btnCancel = new Button() { Text = "Отмена", Location = new Point(200, 230), Width = 100 };
            btnCancel.Click += (s, e) => { DialogResult = DialogResult.Cancel; Close(); };

            Controls.AddRange(new Control[] {
                lblTitle, txtTitle,
                lblAuthor, txtAuthor,
                lblSubject, cbSubject,
                lblLevel, cbLevel,
                lblEdition, txtEdition,
                btnCreate, btnCancel
            });
        }

        private void BtnCreate_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(Title) || string.IsNullOrWhiteSpace(Author) || string.IsNullOrWhiteSpace(Edition))
            {
                MessageBox.Show("Пожалуйста, заполните все поля", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
