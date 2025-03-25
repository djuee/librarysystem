#include "DatabaseManager.h"
#include <iostream>

static void logError(const std::string& context, const std::exception& e) {
    std::cerr << "DatabaseManager❌ " << context << ": " << e.what() << std::endl;
}

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
            user_id INTEGER PRIMARY KEY,
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
            FOREIGN KEY(book_id) REFERENCES Books(id),
            FOREIGN KEY(user_id) REFERENCES Users(user_id)
        );
    )");

    db.exec(R"(
        CREATE TABLE IF NOT EXISTS BookUser (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            book_id INTEGER NOT NULL UNIQUE,
            user_id INTEGER NOT NULL,
            FOREIGN KEY(book_id) REFERENCES Books(id),
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
        logError("addBook", e);
        return false;
    }
}

bool DatabaseManager::addUser(int id,
                              const std::string& username,
                              const std::string& passwordHash,
                              int passwordKey,
                              int role) {
    try {
        SQLite::Statement query(db, R"(
            INSERT INTO Users (user_id, username, passwordHash, passwordKey, role)
            VALUES (?, ?, ?, ?, ?)
        )");

        query.bind(1, id);
        query.bind(2, username);
        query.bind(3, passwordHash);
        query.bind(4, passwordKey);
        query.bind(5, role);

        return query.exec() > 0;
    } catch (const std::exception& e) {
        logError("addUser", e);
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

    } catch (const std::exception& e)
    {
        logError("loadBook", e);
        return nullptr;
    }
}

bool DatabaseManager::deleteBook(int id) {
    try {
        SQLite::Statement deleteBookUser(db, "DELETE FROM BookUser WHERE book_id = ?");
        deleteBookUser.bind(1, id);
        deleteBookUser.exec();

        SQLite::Statement deleteChanges(db, "DELETE FROM ChangesBook WHERE book_id = ?");
        deleteChanges.bind(1, id);
        deleteChanges.exec();

        SQLite::Statement deleteBookStmt(db, "DELETE FROM Books WHERE id = ?");
        deleteBookStmt.bind(1, id);
        deleteBookStmt.exec();

        return true;
    } catch (const std::exception& e)
    {
        logError("deleteBook", e);
        return false;
    }
}


bool DatabaseManager::markBookAsBorrowed(int bookId, int userId) {
    try {
        SQLite::Statement query(db, R"(
            UPDATE Books SET isAvailable = 0 WHERE id = ?
        )");
        query.bind(1, bookId);
        query.exec();

        SQLite::Statement insertStmt(db, R"(
            INSERT OR REPLACE INTO BookUser (book_id, user_id) VALUES (?, ?)
        )");
        insertStmt.bind(1, bookId);
        insertStmt.bind(2, userId);
        insertStmt.exec();

        logBookAction(bookId, userId, "borrowed");

        return true;
    } catch (const std::exception& e)
    {
        logError("markBookAsBorrowed", e);
        return false;
    }
}

bool DatabaseManager::markBookAsAvailable(int bookId) {
    try {
        SQLite::Statement getUserStmt(db, "SELECT user_id FROM BookUser WHERE book_id = ?");
        getUserStmt.bind(1, bookId);

        std::optional<int> userId;
        if (getUserStmt.executeStep()) {
            userId = getUserStmt.getColumn(0).getInt();
        }

        SQLite::Statement deleteStmt(db, "DELETE FROM BookUser WHERE book_id = ?");
        deleteStmt.bind(1, bookId);
        deleteStmt.exec();

        SQLite::Statement query(db, "UPDATE Books SET isAvailable = 1 WHERE id = ?");
        query.bind(1, bookId);
        query.exec();

        logBookAction(bookId, userId, "returned");

        return true;
    } catch (const std::exception& e)
    {
        logError("markBookAsAvailable", e);
        return false;
    }
}

bool DatabaseManager::logBookAction(int bookId, std::optional<int> userId, const std::string& action, const std::string& notes) {
    try {
        SQLite::Statement stmt(db, R"(
            INSERT INTO ChangesBook (book_id, user_id, action, notes)
            VALUES (?, ?, ?, ?)
        )");

        stmt.bind(1, bookId);
        userId ? stmt.bind(2, *userId) : stmt.bind(2);
        stmt.bind(3, action);
        stmt.bind(4, notes);

        return stmt.exec() > 0;
    } catch (const std::exception& e)
    {
        logError("logBookAction", e);
        return false;
    }
}

std::list<std::shared_ptr<Book>> DatabaseManager::getBooksForUser(int userId) {
    std::list<std::shared_ptr<Book>> books;

    try
    {
        SQLite::Statement stmt(db, R"(
            SELECT book_id FROM BookUser WHERE user_id = ?
        )");
        stmt.bind(1, userId);

        while (stmt.executeStep())
        {
            int bookId = stmt.getColumn(0).getInt();
            auto book = loadBook(bookId);
            if (book) books.push_back(book);
        }
    } catch (const std::exception& e)
    {
        logError("getBooksForUser", e);
    }

    return books;
}

std::shared_ptr<User> DatabaseManager::loadUserById(int id)
{
    try
    {
        SQLite::Statement stmt(db, "SELECT username, passwordHash, passwordKey, role FROM Users WHERE user_id = ?");
        stmt.bind(1, id);

        if (stmt.executeStep())
        {
            std::string username = stmt.getColumn(0).getString();
            std::string passwordHash = stmt.getColumn(1).getString();
            int passwordKey = (stmt.getColumn(2).getInt());
            Role role = static_cast<Role>(stmt.getColumn(3).getInt());

            if (role == Role::ADMIN)
            {
                return std::make_shared<Admin>(id, username, passwordHash, passwordKey);
            } else {
                auto reader = std::make_shared<Reader>(id, username, passwordHash, passwordKey);
                reader->setBookList(getBooksForUser(id));
                return reader;
            }
        }
    } catch (const std::exception& e)
    {
        logError("loadUserById", e);
    }

    return nullptr;
}

std::shared_ptr<User> DatabaseManager::loadUserByName(const std::string& name)
{
    try
    {
        SQLite::Statement stmt(db, "SELECT user_id FROM Users WHERE username = ?");
        stmt.bind(1, name);

        if (stmt.executeStep())
        {
            int id = stmt.getColumn(0).getInt();
            return loadUserById(id);
        }
    } catch (const std::exception& e)
    {
        logError("loadUserByName", e);
    }

    return nullptr;
}

std::list<LazyBook> DatabaseManager::getLazyBooks()
{
    std::list<LazyBook> result;

    try {
        SQLite::Statement stmt(db, "SELECT id, typeBook FROM Books");

        while (stmt.executeStep()) {
            int id = stmt.getColumn(0).getInt();
            int type = stmt.getColumn(1).getInt();
            result.emplace_back(id, type);
        }
    } catch (const std::exception& e)
    {
        logError("getLazyBooks", e);
    }

    return result;
}

std::list<LazyReader> DatabaseManager::getLazyReaders() {
    std::list<LazyReader> result;

    try {
        SQLite::Statement stmt(db, "SELECT user_id, username FROM Users WHERE role = ?");

        stmt.bind(1, static_cast<int>(Role::READER));

        while (stmt.executeStep())
        {
            int id = stmt.getColumn(0).getInt();
            std::string username = stmt.getColumn(1).getString();

            result.emplace_back(id, username);
        }
    } catch (const std::exception& e)
    {
        logError("getLazyReaders", e);
    }

    return result;
}

std::list<std::shared_ptr<LazyBook>> DatabaseManager::getLazyBooksByUserId(int userId) {
    std::list<std::shared_ptr<LazyBook>> result;

    try {
        SQLite::Statement stmt(db, R"(
            SELECT Books.id, Books.typeBook
            FROM Books
            JOIN BookUser ON Books.id = BookUser.book_id
            WHERE BookUser.user_id = ?
        )");

        stmt.bind(1, userId);

        while (stmt.executeStep()) {
            int bookId = stmt.getColumn(0).getInt();
            int type = stmt.getColumn(1).getInt();
            result.emplace_back(std::make_shared<LazyBook>(bookId, type));
        }
    } catch (const std::exception& e) {
        logError("getBooksByUserId", e);
    }

    return result;
}


int DatabaseManager::getLastIdFromTable(const std::string& tableName, const std::string& idColumn) {
    try {
        std::string queryStr = "SELECT MAX(" + idColumn + ") FROM " + tableName;
        SQLite::Statement query(db, queryStr);

        if (query.executeStep())
        {
            return query.getColumn(0).isNull() ? 0 : query.getColumn(0).getInt();
        }
    } catch (const std::exception& e)
    {
        logError("getLastIdFromTable", e);
    }

    return 0;
}

DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}
