#pragma once
#include <iostream>
#include <LazyReader.h>
#include <LazyBook.h>
#include <Admin.h>
#include <DatabaseManager.h>

class Controller
{
public:
    Controller();



private:
    DatabaseManager &db = DatabaseManager::getInstance();
    std::list<LazyReader> readerList;
    std::list<LazyBook> bookList;
    std::list<Admin> adminList;
};
