#pragma once

#include <TextBook.h>
#include <Novel.h>
#include <ResearchPaper.h>
#include <Reader.h>
#include <Admin.h>
#include <LazyBook.h>
#include <LazyReader.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <memory>
#include <list>
#include <optional>

class DatabaseManager {
public:
    static DatabaseManager& getInstance();

    DatabaseManager(const DatabaseManager& other) = delete;
    DatabaseManager& operator=(const DatabaseManager& other) = delete;
    DatabaseManager(const DatabaseManager&& other) = delete;
    DatabaseManager& operator=(const DatabaseManager&& other) = delete;

    bool addBook(const std::shared_ptr<Book>& book);
    bool deleteBook(int id);

    bool addUser(int id,
                 const std::string& username,
                 const std::string& passwordHash,
                 int passwordKey,
                 int role);

    std::shared_ptr<Book> loadBook(int bookId);
    std::shared_ptr<User> loadUserById(int id);
    std::shared_ptr<User> loadUserByName(const std::string& name);

    bool markBookAsBorrowed(int bookId, int userId);
    bool markBookAsAvailable(int bookId);

    bool logBookAction(int bookId,
                       std::optional<int> userId,
                       const std::string& action);

    std::list<LazyBook> getLazyBooks();
    std::list<LazyReader> getLazyReaders();
    std::list<std::shared_ptr<LazyBook>> getLazyBooksByUserId(int userId);

    int getLastIdFromTable(const std::string& tableName,
                           const std::string& idColumn = "id");

private:
    DatabaseManager();
    ~DatabaseManager() = default;

    std::list<std::shared_ptr<Book>> getBooksForUser(int userId);

    SQLite::Database db;
};
