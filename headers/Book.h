#pragma once
#include <iostream>

enum TypeBook { textBook, novel, researchPaper };

class Book {
public:
    Book(int id, std::string title, std::string author);
    virtual ~Book() = default;

    void markAsBorrowed();
    void markAsAvailable();
    bool isAvailable() const;
    std::string getBookText(const std::string& filePath) const;

protected:
    int m_id;
    std::string m_title;
    std::string m_author;
    bool m_isAvailable{true};
    TypeBook m_typeBook;
    std::string m_bookPath;
};


