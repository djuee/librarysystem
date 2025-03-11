#include <TextBook.h>

TextBook::TextBook(int id, std::string title, std::string author, Subject subject, Level level, std::string edition)
    : Book(id, title, author), subject(subject), level(level), edition(edition)
{
    m_typeBook = textBook;
}
