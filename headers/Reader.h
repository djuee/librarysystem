#pragma once
#include <iostream>
#include <User.h>
#include <memory>
#include <list>
#include <Book.h>

class Reader final : public User {
public:
    Reader(std::string uname, std::string pass);

    bool takeBook(std::shared_ptr<Book> book);
    bool returnBook(std::shared_ptr<Book> book);
    std::list<std::shared_ptr<Book>> getBookList();


private:
    std::list<std::shared_ptr<Book>> m_bookList;
};
