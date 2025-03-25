#include <Reader.h>
#include <DatabaseManager.h>
#include <iostream>
#include <memory>
#include <list>

Reader::Reader(int id, std::string uname, std::string pass)
    : User(id, uname, pass, Role::READER) {}

Reader::Reader(int id, std::string uname, std::string passwordHash, char passwordKey)
    : User(id, uname, passwordHash, passwordKey, Role::READER) {}

Reader::Reader(Reader&& other) noexcept
    : User(std::move(other)),
      m_bookList(std::move(other.m_bookList))
{
    other.m_bookList.clear();
}

bool Reader::takeBook(std::shared_ptr<Book> book)
{
    if (book == nullptr)
    {
        return false;
    }

    book->markAsBorrowed();
    DatabaseManager::getInstance().markBookAsBorrowed(book->getId(), m_id);
    m_bookList.push_back(book);
    return true;
}

bool Reader::returnBook(std::shared_ptr<Book> book) {
    if (!book) return false;

    auto it = std::find_if(m_bookList.begin(), m_bookList.end(),
                           [book](const std::shared_ptr<Book>& b) {
                               return b->getId() == book->getId();
                           });

    if (it != m_bookList.end()) {
        m_bookList.erase(it);
        DatabaseManager::getInstance().markBookAsAvailable(book->getId());
        return true;
    }

    return false;
}

void Reader::setBookList(const std::list<std::shared_ptr<Book>>& books)
{
    m_bookList = books;
}
