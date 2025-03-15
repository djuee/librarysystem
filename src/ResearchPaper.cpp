#include <ResearchPaper.h>
#include <iostream>
#include <string>
#include <sstream>

ResearchPaper::ResearchPaper(int id, std::string title, std::string author, Field field, std::string conference, std::string doi)
    : Book(id, title, author), m_field(field), m_conference(conference), m_doi(doi)
{
    m_typeBook = researchPaper;
}

std::string ResearchPaper::getConference()
{
    return m_conference;
}

std::string ResearchPaper::getDoi()
{
    return m_doi;
}

std::string ResearchPaper::getField()
{
    return std::to_string(m_field);
}

std::string ResearchPaper::getInsertSQL() const {
    return R"(
        INSERT INTO Books (
            id, title, author, typeBook, isAvailable, bookPath,
            field, conference, doi
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
    )";
}

void ResearchPaper::bindInsertParameters(SQLite::Statement& query) const {
    query.bind(1, m_id);
    query.bind(2, m_title);
    query.bind(3, m_author);
    query.bind(4, TypeBook::researchPaper);
    query.bind(5, m_isAvailable);
    query.bind(6, m_bookPath);
    query.bind(7, m_field);
    query.bind(8, m_conference);
    query.bind(9, m_doi);
}
