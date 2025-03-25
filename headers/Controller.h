#pragma once
#include <iostream>
#include <Admin.h>
#include <DatabaseManager.h>

class Controller
{
public:
    Controller();

    void refresh();

    bool registrationReader(const std::string &uname, const std::string &pass);
    bool loginUser(const std::string &userName, const std::string &pass);
    bool getUserFromLazyUser();

    std::shared_ptr<Admin> getAdmin(int adminId);
    bool createBookText(int adminId, const std::string& title, const std::string& author,
                        Subject subject, Level level, const std::string& edition);

    bool createBookNovel(int adminId, const std::string& title, const std::string& author,
                         Genre genre, int year, int pages);

    bool createBookResearch(int adminId, const std::string& title, const std::string& author,
                            Field field, const std::string& conf, const std::string& doi);


    bool borrowBook(int userId);
    bool returnBook();

private:
    DatabaseManager &db = DatabaseManager::getInstance();
    std::list<LazyReader> readerList;
    std::list<LazyBook> bookList;
    std::list<Admin> adminList;
};
