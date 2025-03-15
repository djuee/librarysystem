#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager()
    : db("sqlite.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS Books (
            id INTEGER PRIMARY KEY,
            title TEXT NOT NULL,
            author TEXT NOT NULL,
            typeBook INTEGER NOT NULL,
            isAvailable BOOLEAN NOT NULL DEFAULT 1,
            bookPath TEXT,
            subject INTEGER,
            level INTEGER,
            edition TEXT,
            genre INTEGER,
            publishedYear INTEGER,
            countPages INTEGER,
            field INTEGER,
            conference TEXT,
            doi TEXT
        );
    )");

    db.exec(R"(
        CREATE TABLE IF NOT EXISTS Users (
            user_id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            passwordHash TEXT NOT NULL,
            passwordKey INTEGER NOT NULL,
            role INTEGER NOT NULL
        );
    )");

    db.exec(R"(
        CREATE TABLE IF NOT EXISTS ChangesBook (
            change_id INTEGER PRIMARY KEY AUTOINCREMENT,
            book_id INTEGER NOT NULL,
            user_id INTEGER,
            action TEXT NOT NULL,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
            notes TEXT,
            FOREIGN KEY(book_id) REFERENCES Books(book_id),
            FOREIGN KEY(user_id) REFERENCES Users(user_id)
        );
    )");

    db.exec(R"(
        CREATE TABLE IF NOT EXISTS BookUser (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            book_id INTEGER NOT NULL UNIQUE,
            user_id INTEGER NOT NULL,
            borrowDate DATETIME DEFAULT CURRENT_TIMESTAMP,
            returnDeadline DATETIME,
            FOREIGN KEY(book_id) REFERENCES Books(book_id),
            FOREIGN KEY(user_id) REFERENCES Users(user_id)
        );
    )");
}

bool DatabaseManager::addBook(const std::shared_ptr<Book>& book) {
    try {
        SQLite::Statement query(db, book->getInsertSQL());
        book->bindInsertParameters(query);
        return query.exec() > 0;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка добавления книги: " << e.what() << std::endl;
        return false;
    }
}


DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}
