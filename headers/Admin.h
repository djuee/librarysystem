#pragma once
#include <iostream>
#include <User.h>
#include <Book.h>
#include "TextBook.h"
#include "Novel.h"
#include "ResearchPaper.h"

class Admin final : public User
{
public:
    Admin(std::string uname, std::string pass);

    std::shared_ptr<Book> createBook(int id, const std::string& title, const std::string& author,
                                     Subject subject, Level level, const std::string& edition); // TextBook

    std::shared_ptr<Book> createBook(int id, const std::string& title, const std::string& author,
                                     Genre genre, int publishedYear, int countPages); // Novel

    std::shared_ptr<Book> createBook(int id, const std::string& title, const std::string& author,
                                     Field field, const std::string& conference, const std::string& doi); // ResearchPaper
    bool deleteBook(std::shared_ptr<Book>);
private:

};
