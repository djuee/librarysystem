namespace UILibrarySystem
{
    partial class AdminForm
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
            btnCreateTextbook = new Button();
            btnCreateNovel = new Button();
            btnCreateResearch = new Button();
            SuspendLayout();
            // 
            // btnCreateTextbook
            // 
            btnCreateTextbook.Location = new Point(12, 30);
            btnCreateTextbook.Name = "btnCreateTextbook";
            btnCreateTextbook.Size = new Size(75, 23);
            btnCreateTextbook.TabIndex = 0;
            btnCreateTextbook.Text = "TextBook";
            btnCreateTextbook.UseVisualStyleBackColor = true;
            btnCreateTextbook.Click += btnCreateTextbook_Click;
            // 
            // btnCreateNovel
            // 
            btnCreateNovel.Location = new Point(110, 30);
            btnCreateNovel.Name = "btnCreateNovel";
            btnCreateNovel.Size = new Size(75, 23);
            btnCreateNovel.TabIndex = 1;
            btnCreateNovel.Text = "Novel";
            btnCreateNovel.UseVisualStyleBackColor = true;
            btnCreateNovel.Click += btnCreateNovel_Click;
            // 
            // btnCreateResearch
            // 
            btnCreateResearch.Location = new Point(212, 30);
            btnCreateResearch.Name = "btnCreateResearch";
            btnCreateResearch.Size = new Size(75, 23);
            btnCreateResearch.TabIndex = 2;
            btnCreateResearch.Text = "Research";
            btnCreateResearch.UseVisualStyleBackColor = true;
            btnCreateResearch.Click += btnCreateResearch_Click;
            // 
            // AdminForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(347, 114);
            Controls.Add(btnCreateResearch);
            Controls.Add(btnCreateNovel);
            Controls.Add(btnCreateTextbook);
            Name = "AdminForm";
            Text = "AdminForm";
            ResumeLayout(false);
        }

        #endregion

        private Button btnCreateTextbook;
        private Button btnCreateNovel;
        private Button btnCreateResearch;
    }
}