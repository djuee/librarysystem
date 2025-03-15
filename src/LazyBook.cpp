#include <LazyBook.h>

LazyBook::LazyBook(int id, int typeBook)
    : m_id(id), m_typeBook(typeBook) {}

int LazyBook::getId() const
{
    return m_id;
}

int LazyBook::getTypeBook() const
{
    return m_typeBook;
}

bool LazyBook::isLoaded()
{
    return (m_loadedBook != nullptr);
}

std::shared_ptr<Book> LazyBook::loadBook()
{

}
