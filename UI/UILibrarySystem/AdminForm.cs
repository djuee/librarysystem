using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using UILibrarySystem.Api;
using UILibrarySystem.Api.LibraryClient.Api;

namespace UILibrarySystem
{
    public partial class AdminForm : Form
    {
        private readonly ApiService _api = new();

        public AdminForm()
        {
            InitializeComponent();
        }

        private async void btnCreateTextbook_Click(object sender, EventArgs e)
        {
            var form = new CreateTextbookForm(); 
            if (form.ShowDialog() == DialogResult.OK)
            {
                var success = await _api.CreateTextbookAsync(
                    SessionManager.UserId,
                    form.Title, form.Author,
                    form.Subject, form.Level,
                    form.Edition
                );

                MessageBox.Show(success ? "Учебник создан" : "Ошибка при создании");
            }
        }

        private async void btnCreateNovel_Click(object sender, EventArgs e)
        {
            var form = new CreateNovelForm(); 
            if (form.ShowDialog() == DialogResult.OK)
            {
                var success = await _api.CreateNovelAsync(
                    SessionManager.UserId,
                    form.Title, form.Author,
                    form.Genre, form.Year, form.Pages
                );

                MessageBox.Show(success ? "Роман создан" : "Ошибка при создании");
            }
        }

        private async void btnCreateResearch_Click(object sender, EventArgs e)
        {
            var form = new CreateResearchForm(); 
            if (form.ShowDialog() == DialogResult.OK)
            {
                var success = await _api.CreateResearchBookAsync(
                    SessionManager.UserId,
                    form.Title, form.Author,
                    form.Field, form.Conf, form.Doi
                );

                MessageBox.Show(success ? "Научная книга создана" : "Ошибка при создании");
            }
        }
    }
}
