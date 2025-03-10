#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include "Book.h"


class DatabaseManager {
public:
    DatabaseManager(std::string dbName) :
        db(dbName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE),
        dbName(dbName)
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
                role INTEGER NOT NULL  -- 0: ADMIN, 1: READER
            );
        )");

        db.exec(R"(
            CREATE TABLE IF NOT EXISTS ChangesBook (
                change_id INTEGER PRIMARY KEY AUTOINCREMENT,
                book_id INTEGER NOT NULL,
                user_id INTEGER,  -- Кто произвел действие (может быть NULL, если действие не связано с пользователем)
                action TEXT NOT NULL,  -- описание действия (например: 'borrowed', 'returned', 'updated info', etc.)
                timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
                notes TEXT, -- Дополнительные заметки (опционально)

                FOREIGN KEY(book_id) REFERENCES Books(book_id),
                FOREIGN KEY(user_id) REFERENCES Users(user_id)
            );
        )");

        db.exec(R"(
            CREATE TABLE IF NOT EXISTS BookUser (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                book_id INTEGER NOT NULL UNIQUE, -- уникальность гарантирует, что книгу держит один пользователь
                user_id INTEGER NOT NULL,
                borrowDate DATETIME DEFAULT CURRENT_TIMESTAMP,
                returnDeadline DATETIME, -- дата, до которой нужно вернуть книгу (опционально)

                FOREIGN KEY(book_id) REFERENCES Books(book_id),
                FOREIGN KEY(user_id) REFERENCES Users(user_id)
            );
        )");
    }

    static void createBook(int id, std::string title, std::string author, Subject)
    {

    }

private:
    SQLite::Database db;
    std::string dbName;
};
