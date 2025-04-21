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
using UILibrarySystem.Models;

namespace UILibrarySystem
{
    public partial class ReaderForm : Form
    {
        private readonly ApiService _api = new();
        private List<Book> _availableBooks = new();
        private List<Book> _myBooks = new();

        public ReaderForm()
        {
            InitializeComponent();
            if (SessionManager.IsAdmin)
                btnAdmin.Show();
        }

        private async void btnAvailableBooks_Click(object sender, EventArgs e)
        {
            _availableBooks = await _api.GetBooksAsync();
            availableBooksGrid.DataSource = _availableBooks;

        }

        private async void ReaderForm_Load(object sender, EventArgs e)
        {
            if (!SessionManager.IsAdmin)
                await LoadMyBooks();
        }

        private async Task LoadMyBooks()
        {
            if (!SessionManager.IsAdmin)
            {
                _myBooks = await _api.GetMyBooksAsync(SessionManager.UserId);
                myBooksGrid.DataSource = null;
                myBooksGrid.DataSource = _myBooks;
            }
        }

        private async void btnBorrow_Click(object sender, EventArgs e)
        {
            if (availableBooksGrid.SelectedRows.Count == 0)
            {
                MessageBox.Show("Выберите книгу для взятия.");
                return;
            }

            var book = (Book)availableBooksGrid.SelectedRows[0].DataBoundItem;
            bool success = await _api.BorrowBookAsync(SessionManager.UserId, book.Id);

            MessageBox.Show(success ? "Книга взята!" : "Ошибка при взятии книги");
            await LoadMyBooks();
        }

        private async void btnReturn_Click(object sender, EventArgs e)
        {
            if (myBooksGrid.SelectedRows.Count == 0)
            {
                MessageBox.Show("Выберите книгу для возврата.");
                return;
            }

            var book = (Book)myBooksGrid.SelectedRows[0].DataBoundItem;
            bool success = await _api.ReturnBookAsync(SessionManager.UserId, book.Id);

            MessageBox.Show(success ? "Книга возвращена!" : "Ошибка при возврате книги");
            await LoadMyBooks();
        }

        private void btnAdmin_Click(object sender, EventArgs e)
        {
            new AdminForm().Show();
        }
    }
}
