#pragma once
#include <iostream>
#include <Book.h>

class LazyBook
{
public:
    LazyBook(int id, int typeBook);
    int getId() const;
    int getTypeBook() const;
    bool isLoaded();
    std::shared_ptr<Book> loadBook();
    void freeBook();

private:
    int m_id;
    int m_typeBook;
    std::shared_ptr<Book> m_loadedBook{nullptr};
};
