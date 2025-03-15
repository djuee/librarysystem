#include <iostream>
#include <Reader.h>
#include <memory>
#include <list>

Reader::Reader(std::string uname, std::string pass)
    : User(uname, pass, Role::READER) {}

bool Reader::takeBook(std::shared_ptr<Book> book)
{
    if (book == nullptr)
    {
        return false;
    }

    book->markAsBorrowed();
    m_bookList.push_back(book);
    return true;
}
