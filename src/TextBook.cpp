#include <TextBook.h>
#include <iostream>
#include <string>
#include <sstream>

TextBook::TextBook(int id, std::string title, std::string author, Subject subject, Level level, std::string edition)
    : Book(id, title, author), m_subject(subject), m_level(level), m_edition(edition)
{
    m_typeBook = textBook;
}

std::string TextBook::getEdition()
{
    return m_edition;
}

std::string TextBook::getLevel()
{
    return std::to_string(m_level);
}

std::string TextBook::getSubject()
{
    return std::to_string(m_subject);
}

std::string TextBook::getInsertSQL() const {
    return R"(
        INSERT INTO Books (
            id, title, author, typeBook, isAvailable, bookPath,
            subject, level, edition
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
    )";
}

void TextBook::bindInsertParameters(SQLite::Statement& query) const {
    query.bind(1, m_id);
    query.bind(2, m_title);
    query.bind(3, m_author);
    query.bind(4, TypeBook::textBook);
    query.bind(5, m_isAvailable);
    query.bind(6, m_bookPath);
    query.bind(7, m_subject);
    query.bind(8, m_level);
    query.bind(9, m_edition);
}
