#pragma once
#include <TextBook.h>
#include <Novel.h>>
#include <ResearchPaper.h>
#include <Reader.h>
#include <Admin.h>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

class DatabaseManager {
public:
    static DatabaseManager& getInstance();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    bool addBook(const std::shared_ptr<Book>& book);
    bool deleteBook(int id);
    bool addUser(const std::string& username,
                 const std::string& passwordHash,
                 int passwordKey,
                 int role);
    std::shared_ptr<Book> DatabaseManager::loadBook(int bookId);
    bool markBookAsBorrowed(int bookId);
    bool markBookAsAvailable(int bookId);
    std::shared_ptr<User> loadUserById(int id);

private:
    DatabaseManager();

    SQLite::Database db;
    std::string dbName;
};
