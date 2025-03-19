#pragma once
#include <iostream>
#include <Admin.h>
#include <DatabaseManager.h>

class Controller
{
public:
    Controller();

    bool registrationReader(std::string uname, std::string pass);
    bool loginUser(std::string userName, std::string pass);
    bool addBook();
    bool borrowBook(const User &user);

private:
    DatabaseManager &db = DatabaseManager::getInstance();
    std::list<LazyReader> readerList;
    std::list<LazyBook> bookList;
    std::list<Admin> adminList;
};
