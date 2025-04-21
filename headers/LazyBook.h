#pragma once
#include <iostream>
#include <Book.h>

class LazyBook
{
public:
    LazyBook(int id, int typeBook, std::string title);
    int getId() const;
    int getTypeBook() const;
    bool isLoaded();
    std::string getTitle();
    std::shared_ptr<Book> loadBook();
    void freeBook();

private:
    int m_id;
    int m_typeBook;
    std::string m_title;
    std::shared_ptr<Book> m_loadedBook{nullptr};
};
