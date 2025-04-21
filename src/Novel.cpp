#include <Novel.h>
#include <iostream>
#include <string>
#include <sstream>

Novel::Novel(int id, std::string title, std::string author, Genre genre, int publishedYear, int countPages)
    : Book(id, title, author), m_genre(genre), m_publishedYear(publishedYear), m_countPages(countPages)
{
    m_typeBook = novel;
}

std::string Novel::getGenre()
{
    return std::to_string(m_genre);
}

int Novel::getCountPages()
{
    return m_countPages;
}

int Novel::getPublishedYear()
{
    return m_publishedYear;
}

std::string Novel::getInsertSQL() const {
    return R"(
        INSERT INTO Books (
            id, title, author, typeBook, isAvailable,
            genre, publishedYear, countPages
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?)
    )";
}

void Novel::bindInsertParameters(SQLite::Statement& query) const {
    query.bind(1, m_id);
    query.bind(2, m_title);
    query.bind(3, m_author);
    query.bind(4, TypeBook::novel);
    query.bind(5, m_isAvailable);
    query.bind(6, m_genre);
    query.bind(7, m_publishedYear);
    query.bind(8, m_countPages);
}

