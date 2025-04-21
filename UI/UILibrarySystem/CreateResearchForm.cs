using System;
using System.Drawing;
using System.Windows.Forms;
using UILibrarySystem.Models;

namespace UILibrarySystem
{
    public partial class CreateResearchForm : Form
    {
        public string Title => txtTitle.Text;
        public string Author => txtAuthor.Text;
        public Field Field => (Field)cbField.SelectedItem;
        public string Conf => txtConf.Text;
        public string Doi => txtDoi.Text;

        private TextBox txtTitle;
        private TextBox txtAuthor;
        private ComboBox cbField;
        private TextBox txtConf;
        private TextBox txtDoi;
        private Button btnCreate;
        private Button btnCancel;

        public CreateResearchForm()
        {
            Text = "Создание научной книги";
            Size = new Size(400, 350);
            StartPosition = FormStartPosition.CenterScreen;
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MaximizeBox = false;
            InitializeForm();
        }

        private void InitializeForm()
        {
            var lblTitle = new Label() { Text = "Название:", Location = new Point(20, 20), AutoSize = true };
            txtTitle = new TextBox() { Location = new Point(150, 20), Width = 200 };

            var lblAuthor = new Label() { Text = "Автор:", Location = new Point(20, 60), AutoSize = true };
            txtAuthor = new TextBox() { Location = new Point(150, 60), Width = 200 };

            var lblField = new Label() { Text = "Область:", Location = new Point(20, 100), AutoSize = true };
            cbField = new ComboBox() { Location = new Point(150, 100), Width = 200, DropDownStyle = ComboBoxStyle.DropDownList };
            cbField.DataSource = Enum.GetValues(typeof(Field));

            var lblConf = new Label() { Text = "Конференция:", Location = new Point(20, 140), AutoSize = true };
            txtConf = new TextBox() { Location = new Point(150, 140), Width = 200 };

            var lblDoi = new Label() { Text = "DOI:", Location = new Point(20, 180), AutoSize = true };
            txtDoi = new TextBox() { Location = new Point(150, 180), Width = 200 };

            btnCreate = new Button() { Text = "Создать", Location = new Point(80, 230), Width = 100 };
            btnCreate.Click += BtnCreate_Click;

            btnCancel = new Button() { Text = "Отмена", Location = new Point(200, 230), Width = 100 };
            btnCancel.Click += (s, e) => { DialogResult = DialogResult.Cancel; Close(); };

            Controls.AddRange(new Control[] {
                lblTitle, txtTitle,
                lblAuthor, txtAuthor,
                lblField, cbField,
                lblConf, txtConf,
                lblDoi, txtDoi,
                btnCreate, btnCancel
            });
        }

        private void BtnCreate_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(Title) || string.IsNullOrWhiteSpace(Author) || string.IsNullOrWhiteSpace(Conf) || string.IsNullOrWhiteSpace(Doi))
            {
                MessageBox.Show("Пожалуйста, заполните все поля", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
