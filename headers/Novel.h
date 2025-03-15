#pragma once
#include <iostream>
#include <Book.h>

enum Genre { Mystery, Thriller, Fantasy, Romance, Historical, Horror, Biography, Drama, Comedy };

class Novel final : public Book
{
public:
    Novel(int id, std::string title, std::string author, Genre genre, int publishedYear, int countPages);

    std::string getGenre();
    int getPublishedYear();
    int getCountPages();

    std::string getInsertSQL() const override;
    void bindInsertParameters(SQLite::Statement& query) const override;

private:
    Genre m_genre;
    int m_publishedYear;
    int m_countPages;
};
