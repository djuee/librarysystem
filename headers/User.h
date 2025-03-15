#pragma once
#include <Book.h>
#include <iostream>
#include <string>
#include <memory>
#include <list>

enum class Role {
    ADMIN,
    READER,
};

class User {
public:
    User(std::string uname, std::string pass, Role r);
    virtual ~User() = default;

    std::string getUsername() const;
    Role getRole() const;
    bool checkPassword(const std::string& inputPassword);
    void changeUsername(std::string uname);

protected:
    std::string m_username;
    char m_passwordKey;
    std::string m_passwordHash;
    Role m_role;
    std::list<std::shared_ptr<Book>> bookList;
};
