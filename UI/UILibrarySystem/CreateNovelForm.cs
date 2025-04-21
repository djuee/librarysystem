using System;
using System.Drawing;
using System.Windows.Forms;
using UILibrarySystem.Models;

namespace UILibrarySystem
{
    public partial class CreateNovelForm : Form
    {
        public string Title => txtTitle.Text;
        public string Author => txtAuthor.Text;
        public Genre Genre => (Genre)cbGenre.SelectedItem;
        public int Year => int.Parse(txtYear.Text);
        public int Pages => int.Parse(txtPages.Text);

        private TextBox txtTitle;
        private TextBox txtAuthor;
        private ComboBox cbGenre;
        private TextBox txtYear;
        private TextBox txtPages;
        private Button btnCreate;
        private Button btnCancel;

        public CreateNovelForm()
        {
            Text = "Создание романа";
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

            var lblGenre = new Label() { Text = "Жанр:", Location = new Point(20, 100), AutoSize = true };
            cbGenre = new ComboBox() { Location = new Point(150, 100), Width = 200, DropDownStyle = ComboBoxStyle.DropDownList };
            cbGenre.DataSource = Enum.GetValues(typeof(Genre));

            var lblYear = new Label() { Text = "Год издания:", Location = new Point(20, 140), AutoSize = true };
            txtYear = new TextBox() { Location = new Point(150, 140), Width = 200 };

            var lblPages = new Label() { Text = "Количество страниц:", Location = new Point(20, 180), AutoSize = true };
            txtPages = new TextBox() { Location = new Point(150, 180), Width = 200 };

            btnCreate = new Button() { Text = "Создать", Location = new Point(80, 230), Width = 100 };
            btnCreate.Click += BtnCreate_Click;

            btnCancel = new Button() { Text = "Отмена", Location = new Point(200, 230), Width = 100 };
            btnCancel.Click += (s, e) => { DialogResult = DialogResult.Cancel; Close(); };

            Controls.AddRange(new Control[] {
                lblTitle, txtTitle,
                lblAuthor, txtAuthor,
                lblGenre, cbGenre,
                lblYear, txtYear,
                lblPages, txtPages,
                btnCreate, btnCancel
            });
        }

        private void BtnCreate_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(Title) || string.IsNullOrWhiteSpace(Author) || string.IsNullOrWhiteSpace(txtYear.Text) || string.IsNullOrWhiteSpace(txtPages.Text))
            {
                MessageBox.Show("Пожалуйста, заполните все поля", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (!int.TryParse(txtYear.Text, out _) || !int.TryParse(txtPages.Text, out _))
            {
                MessageBox.Show("Год и количество страниц должны быть числом", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
