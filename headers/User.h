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
    User(User& other) = delete;
    User& operator =(User& other) = delete;
    User(User&& other) noexcept;
    User& operator =(User&& other) = delete;

    int getId() const;
    std::string getUsername() const;
    int getPassKey() const;
    std::string getPassHash() const;
    int getRole() const;

    bool checkPassword(const std::string& inputPassword);
    void changeUsername(std::string uname);

protected:
    User(int id, std::string uname, std::string pass, Role r);
    User(int id, std::string uname, std::string passwordHash, int passwordKey, Role r);
    virtual ~User() = default;

protected:
    int m_id;
    std::string m_username;
    int m_passwordKey;
    std::string m_passwordHash;
    Role m_role;
};
