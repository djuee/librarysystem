#pragma once
#include <iostream>
#include <Reader.h>
#include <LazyBook.h>

class LazyReader
{
public:
    LazyReader(int id, std::string uname);

    int getId() const;
    std::string getUname() const;
    std::list<std::shared_ptr<LazyBook>> getBookList() const;
    void update();

private:
    int m_id;
    std::string m_uname;
    std::list<std::shared_ptr<LazyBook>> m_bookList;
};
