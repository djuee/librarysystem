#include <Novel.h>

Novel::Novel(int id, std::string title, std::string author, Genre genre, int publishedYear, int countPages)
    : Book(id, title, author), genre(genre), publishedYear(publishedYear), countPages(countPages) {
    m_typeBook = novel;
}
