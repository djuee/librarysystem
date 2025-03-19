#pragma once
#include <TextBook.h>
#include <Novel.h>>
#include <ResearchPaper.h>
#include <Reader.h>
#include <Admin.h>
#include <string>
#include <LazyBook.h>
#include <LazyReader.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <optional>

class DatabaseManager {
public:
    static DatabaseManager& getInstance();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    bool addBook(const std::shared_ptr<Book>& book);
    bool deleteBook(int id);
    bool addUser(int id,
                 const std::string& username,
                 const std::string& passwordHash,
                 int passwordKey,
                 int role);
    std::shared_ptr<Book> DatabaseManager::loadBook(int bookId);
    bool markBookAsBorrowed(int bookId, int userId);
    bool markBookAsAvailable(int bookId);
    std::shared_ptr<User> loadUserById(int id);
    bool logBookAction(int bookId, std::optional<int> userId, const std::string& action, const std::string& notes = "");
    std::list<LazyBook> getLazyBooks();
    std::list<LazyReader> getLazyReaders();
    int getLastIdFromTable(const std::string& tableName, const std::string& idColumn = "id");
    std::list<std::shared_ptr<LazyBook>> getBooksByUserId(int userId);
    std::shared_ptr<User> loadUserByName(std::string name);
private:
    DatabaseManager();

    SQLite::Database db;
    std::string dbName;
};
