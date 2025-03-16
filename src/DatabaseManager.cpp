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

bool DatabaseManager::addBook(const std::shared_ptr<Book>& book)
{
    try {
        SQLite::Statement query(db, book->getInsertSQL());
        book->bindInsertParameters(query);
        return query.exec() > 0;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка добавления книги: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::addUser(const std::string& username,
                              const std::string& passwordHash,
                              int passwordKey,
                              int role)
{
    try {
        SQLite::Statement query(db, R"(
            INSERT INTO Users (username, passwordHash, passwordKey, role)
            VALUES (?, ?, ?, ?)
        )");

        query.bind(1, username);
        query.bind(2, passwordHash);
        query.bind(3, passwordKey);
        query.bind(4, role);

        query.exec();
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

std::shared_ptr<Book> DatabaseManager::loadBook(int bookId)
{
    try {
        SQLite::Statement query(db, "SELECT * FROM Books WHERE id = ?");
        query.bind(1, bookId);

        if (query.executeStep()) {
            int type = query.getColumn("typeBook").getInt();

            std::string title = query.getColumn("title").getString();
            std::string author = query.getColumn("author").getString();
            bool isAvailable = query.getColumn("isAvailable").getInt();
            std::string path = query.getColumn("bookPath").getString();

            if (type == TypeBook::textBook) {
                Subject subject = static_cast<Subject>(query.getColumn("subject").getInt());
                Level level = static_cast<Level>(query.getColumn("level").getInt());
                std::string edition = query.getColumn("edition").getString();

                auto book = std::make_shared<TextBook>(bookId, title, author, subject, level, edition);
                return book;
            }
            else if (type == TypeBook::novel) {
                Genre genre = static_cast<Genre>(query.getColumn("genre").getInt());
                int year = query.getColumn("publishedYear").getInt();
                int pages = query.getColumn("countPages").getInt();

                auto book = std::make_shared<Novel>(bookId, title, author, genre, year, pages);
                return book;
            }
            else if (type == TypeBook::researchPaper) {
                Field field = static_cast<Field>(query.getColumn("field").getInt());
                std::string conf = query.getColumn("conference").getString();
                std::string doi = query.getColumn("doi").getString();

                auto book = std::make_shared<ResearchPaper>(bookId, title, author, field, conf, doi);
                return book;
            }
            else {
                return nullptr;
            }
        } else {
            return nullptr;
        }

    } catch (const std::exception& e) {
        return nullptr;
    }
}

bool DatabaseManager::markBookAsBorrowed(int bookId)
{
    try {
        SQLite::Statement query(db, R"(
            UPDATE Books
            SET isAvailable = 0
            WHERE id = ?
        )");

        query.bind(1, bookId);
        query.exec();

        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool DatabaseManager::markBookAsAvailable(int bookId)
{
    try {
        SQLite::Statement query(db, R"(
            UPDATE Books
            SET isAvailable = 1
            WHERE id = ?
        )");

        query.bind(1, bookId);
        query.exec();

        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool DatabaseManager::deleteBook(int id)
{
    try {
        {
            SQLite::Statement stmt(db, "DELETE FROM BookUser WHERE book_id = ?");
            stmt.bind(1, id);
            stmt.exec();
        }

        {
            SQLite::Statement stmt(db, "DELETE FROM ChangesBook WHERE book_id = ?");
            stmt.bind(1, id);
            stmt.exec();
        }
        {
            SQLite::Statement stmt(db, "DELETE FROM Books WHERE id = ?");
            stmt.bind(1, id);
            stmt.exec();
        }

        return true;
    } catch (const std::exception& e) {
        std::cerr << "❌ Ошибка при удалении книги: " << e.what() << std::endl;
        return false;
    }
}

std::shared_ptr<User> DatabaseManager::loadUserById(int id)
{
    try
    {
        SQLite::Statement stmt(db, "SELECT username, passwordHash, passwordKey, role FROM Users WHERE user_id = ?");
        stmt.bind(1, id);

        if (stmt.executeStep()) {
            std::string username = stmt.getColumn(0).getString();
            std::string passwordHash = stmt.getColumn(1).getString();
            int passwordKey = stmt.getColumn(2).getInt();
            Role role = static_cast<Role>(stmt.getColumn(3).getInt());

            if (role == Role::ADMIN)
                return std::make_shared<Admin>(id, username, passwordHash, passwordKey);
            else
                return std::make_shared<Reader>(id, username, passwordHash, passwordKey);
        }
    }
    catch (const std::exception& e)
        {
        }

    return nullptr;
}



DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager instance;
    return instance;
}
