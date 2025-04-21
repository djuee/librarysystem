namespace UILibrarySystem
{
    partial class ReaderForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            availableBooksGrid = new DataGridView();
            btnAvailableBooks = new Button();
            myBooksGrid = new DataGridView();
            btnBorrow = new Button();
            btnReturn = new Button();
            btnAdmin = new Button();
            ((System.ComponentModel.ISupportInitialize)availableBooksGrid).BeginInit();
            ((System.ComponentModel.ISupportInitialize)myBooksGrid).BeginInit();
            SuspendLayout();
            // 
            // availableBooksGrid
            // 
            availableBooksGrid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            availableBooksGrid.Location = new Point(12, 12);
            availableBooksGrid.Name = "availableBooksGrid";
            availableBooksGrid.Size = new Size(534, 507);
            availableBooksGrid.TabIndex = 0;
            // 
            // btnAvailableBooks
            // 
            btnAvailableBooks.Location = new Point(12, 538);
            btnAvailableBooks.Name = "btnAvailableBooks";
            btnAvailableBooks.Size = new Size(134, 23);
            btnAvailableBooks.TabIndex = 1;
            btnAvailableBooks.Text = "Доступные книги";
            btnAvailableBooks.UseVisualStyleBackColor = true;
            btnAvailableBooks.Click += btnAvailableBooks_Click;
            // 
            // myBooksGrid
            // 
            myBooksGrid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            myBooksGrid.Location = new Point(672, 12);
            myBooksGrid.Name = "myBooksGrid";
            myBooksGrid.Size = new Size(534, 507);
            myBooksGrid.TabIndex = 2;
            // 
            // btnBorrow
            // 
            btnBorrow.Location = new Point(152, 538);
            btnBorrow.Name = "btnBorrow";
            btnBorrow.Size = new Size(134, 23);
            btnBorrow.TabIndex = 3;
            btnBorrow.Text = "Взять книгу";
            btnBorrow.UseVisualStyleBackColor = true;
            btnBorrow.Click += btnBorrow_Click;
            // 
            // btnReturn
            // 
            btnReturn.Location = new Point(672, 538);
            btnReturn.Name = "btnReturn";
            btnReturn.Size = new Size(134, 23);
            btnReturn.TabIndex = 4;
            btnReturn.Text = "Вернуть книгу";
            btnReturn.UseVisualStyleBackColor = true;
            btnReturn.Click += btnReturn_Click;
            // 
            // btnAdmin
            // 
            btnAdmin.Location = new Point(926, 538);
            btnAdmin.Name = "btnAdmin";
            btnAdmin.Size = new Size(103, 44);
            btnAdmin.TabIndex = 5;
            btnAdmin.Text = "Открыть админ-панель";
            btnAdmin.UseVisualStyleBackColor = true;
            btnAdmin.Visible = false;
            btnAdmin.Click += btnAdmin_Click;
            // 
            // ReaderForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1307, 655);
            Controls.Add(btnAdmin);
            Controls.Add(btnReturn);
            Controls.Add(btnBorrow);
            Controls.Add(myBooksGrid);
            Controls.Add(btnAvailableBooks);
            Controls.Add(availableBooksGrid);
            Name = "ReaderForm";
            Text = "ReaderForm";
            Load += ReaderForm_Load;
            ((System.ComponentModel.ISupportInitialize)availableBooksGrid).EndInit();
            ((System.ComponentModel.ISupportInitialize)myBooksGrid).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private DataGridView availableBooksGrid;
        private Button btnAvailableBooks;
        private DataGridView myBooksGrid;
        private Button btnBorrow;
        private Button btnReturn;
        private Button btnAdmin;
    }
}