using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UILibrarySystem.Models
{
    public class Book
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string Author { get; set; }

        public string BookType { get; set; } // "Textbook", "Novel", "Research"

        public Subject? Subject { get; set; } // Только для Textbook
        public Level? Level { get; set; } // Только для Textbook
        public string Edition { get; set; } // Только для Textbook

        public Genre? Genre { get; set; } // Только для Novel
        public int? Year { get; set; } // Только для Novel
        public int? Pages { get; set; } // Только для Novel

        public Field? Field { get; set; } // Только для Research
        public string Conf { get; set; } // Только для Research
        public string Doi { get; set; } // Только для Research
    }
}
