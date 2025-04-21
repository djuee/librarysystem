#pragma once
#include <iostream>
#include <Admin.h>
#include <DatabaseManager.h>
#include <list>

class Controller
{
public:
    Controller();

    void refresh();

    std::list<LazyReader> getLazyReaders();
    std::list<LazyBook> getLazyBooks();
    void initializationAdmin();

    bool registrationReader(const std::string &uname, const std::string &pass);
    bool loginUser(const std::string &userName, const std::string &pass);
    bool getUserFromLazyUser();
    std::shared_ptr<User> loginAndGetUser(const std::string& userName, const std::string& pass);
    std::list<std::shared_ptr<Book>> getBooksByUserId(int userId);

    std::shared_ptr<Admin> getAdmin(int adminId);
    bool createBookText(int adminId, const std::string& title, const std::string& author,
                        Subject subject, Level level, const std::string& edition);

    bool createBookNovel(int adminId, const std::string& title, const std::string& author,
                         Genre genre, int year, int pages);

    bool createBookResearch(int adminId, const std::string& title, const std::string& author,
                            Field field, const std::string& conf, const std::string& doi);


    std::shared_ptr<Reader> getReader(int readerId);
    bool borrowBook(int userId, int bookId);
    bool returnBook(int userId, int bookId);

private:
    DatabaseManager &db = DatabaseManager::getInstance();
    std::list<LazyReader> readerList{};
    std::list<LazyBook> bookList{};
    std::list<std::shared_ptr<Admin>> adminList{};
};
