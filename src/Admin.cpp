#include <iostream>
#include <Admin.h>
#include <iostream>
#include <memory>
#include <DatabaseManager.h>

Admin::Admin(int id, std::string uname, std::string pass)
    : User(id, uname, pass, Role::ADMIN) {}

Admin::Admin(int id, std::string uname, std::string passwordHash, char passwordKey)
    : User(id, uname, passwordHash, passwordKey, Role::ADMIN) {}

std::shared_ptr<Book> Admin::createBook(int id, const std::string& title, const std::string& author,
                                        Subject subject, Level level, const std::string& edition)
{
    DatabaseManager &db = DatabaseManager::getInstance();
    std::shared_ptr<Book> book = std::make_shared<TextBook>(id, title, author, subject, level, edition);
    db.addBook(book);
    return book;
}

std::shared_ptr<Book> Admin::createBook(int id, const std::string& title, const std::string& author,
                                        Genre genre, int publishedYear, int countPages)
{
    DatabaseManager &db = DatabaseManager::getInstance();
    std::shared_ptr<Book> book = std::make_shared<Novel>(id, title, author, genre, publishedYear, countPages);
    db.addBook(book);
    return book;
}

std::shared_ptr<Book> Admin::createBook(int id, const std::string& title, const std::string& author,
                                        Field field, const std::string& conference, const std::string& doi)
{
    DatabaseManager &db = DatabaseManager::getInstance();
    std::shared_ptr<Book> book = std::make_shared<ResearchPaper>(id, title, author, field, conference, doi);
    db.addBook(book);
    return book;
}
