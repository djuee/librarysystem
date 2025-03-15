#include <iostream>
#include <Admin.h>
#include <iostream>
#include <memory>

Admin::Admin(std::string uname, std::string pass)
    : User(uname, pass, Role::ADMIN) {}

// TextBook
std::shared_ptr<Book> Admin::createBook(int id, const std::string& title, const std::string& author,
                                        Subject subject, Level level, const std::string& edition)
{
    return std::make_shared<TextBook>(id, title, author, subject, level, edition);
}

// Novel
std::shared_ptr<Book> Admin::createBook(int id, const std::string& title, const std::string& author,
                                        Genre genre, int publishedYear, int countPages)
{
    return std::make_shared<Novel>(id, title, author, genre, publishedYear, countPages);
}

// ResearchPaper
std::shared_ptr<Book> Admin::createBook(int id, const std::string& title, const std::string& author,
                                        Field field, const std::string& conference, const std::string& doi)
{
    return std::make_shared<ResearchPaper>(id, title, author, field, conference, doi);
}
