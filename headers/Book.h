#pragma once
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>

enum TypeBook { textBook, novel, researchPaper };

class Book {
public:
    int getId();
    std::string getTitle();
    std::string getAuthor();
    std::string getTypeBook();
    bool isAvailable() const;

    virtual std::string getInsertSQL() const = 0;
    virtual void bindInsertParameters(SQLite::Statement& query) const = 0;

    void markAsBorrowed();
    void markAsAvailable();

    std::string getBookText(const std::string& filePath) const;

protected:
    Book(int id, std::string title, std::string author);
    virtual ~Book() = default;

protected:
    int m_id;
    std::string m_title;
    std::string m_author;
    bool m_isAvailable{true};
    TypeBook m_typeBook;
    std::string m_bookPath;
};


