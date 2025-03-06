#include <iostream>
#include "Book.cpp"
#include <vector>
#include "PasswordManager.cpp"

enum class Role
{
    ADMIN, 
    READER,
};

class User
{
public:
    User (std::string uname, std::string pass, Role r)
        : m_username(uname), m_role(r) 
    {
        m_passwordKey = PasswordManager::generateRandomKey();
        m_passwordHash = PasswordManager::encryptPassword(pass, m_passwordKey);
    }
    
    virtual ~User() = default;

    std::string getUsername() const 
    {
        return m_username;
    }

    Role getRole() const 
    {
        return m_role;
    }

    bool checkPassword(const std::string& inputPassword) 
    {
        return PasswordManager::checkPassword(inputPassword, m_passwordHash, m_passwordKey);
    }
    
    const std::vector<Book*>& bookList() const
    {
        return m_bookList;
    }

protected:
    std::string m_username;
    char m_passwordKey;
    std::string m_passwordHash;
    Role m_role;
    std::vector<Book*> m_bookList; // Если нужна будет вставка и удаление из середины контейнера то лучше использовать std::list
    // кто и как будет очищать этот контейнер? кто удалять будет Book* ?
   
// Альтернативная реализация, с умными указателями, чтобы не следить за удалением
// #include<memory>
//     using BookPtr = std::unique_ptr<Book>;
//     std::vector<BookPtr> m_bookList;
//     
//     m_bookList.emplace_back(std::make_unique<Book>(new ResearchPaper(....));
    
};

class Reader final : public User
{
public:
    Reader (std::string uname, std::string pass)
        : User (uname, pass, Role::READER) {}

    bool getBook(Book* book)
    {
        if (nullptr == book)
            return false;
        
        if (book->isAvailable())
        {
            book->markAsBorrowed();
            return true;
        }
        return false;
    }

    bool returnBook(Book* book) 
    {
        if (nullptr == book)
            return false;

        if (!book->isAvailable())
        {
            book->markAsAvailable();
            return true;
        }
        return false;
    }
};

class Admin final : public User 
{
public:
    Admin (std::string uname, std::string pass)
        : User (uname, pass, Role::ADMIN) {}
};

