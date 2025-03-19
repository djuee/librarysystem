#pragma once
#include <iostream>
#include <User.h>
#include <memory>
#include <list>
#include <Book.h>

class Reader final : public User {
public:
    Reader(int id, std::string uname, std::string pass);
    Reader(int id, std::string uname, std::string passwordHash, char passwordKey);

    bool takeBook(std::shared_ptr<Book> book);
    bool returnBook(std::shared_ptr<Book> book);
    std::list<std::shared_ptr<Book>> getBookList();
    void setBookList(const std::list<std::shared_ptr<Book>>& books);

private:
    std::list<std::shared_ptr<Book>> m_bookList;
};
