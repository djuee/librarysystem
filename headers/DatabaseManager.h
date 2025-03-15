#pragma once
#include <TextBook.h>
#include <Novel.h>>
#include <ResearchPaper.h>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

class DatabaseManager {
public:
    static DatabaseManager& getInstance();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    bool addBook(const std::shared_ptr<Book>& book);
    bool deleteBook(int id);

private:
    DatabaseManager();

    SQLite::Database db;
    std::string dbName;
};
