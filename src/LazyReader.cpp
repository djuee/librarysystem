#include <LazyReader.h>
#include <iostream>

LazyReader::LazyReader(int id, std::string uname)
    : m_id(id), m_uname(uname) {};

int LazyReader::getId() const
{
    return m_id;
}

std::string LazyReader::getUname() const
{
    return m_uname;
}

std::list<std::shared_ptr<LazyBook>> LazyReader::getBookList() const
{
    return m_bookList;
}

void LazyReader::update()
{

}
