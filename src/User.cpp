#include "User.h"
#include <PasswordManager.h>

User::User(int id, std::string uname, std::string pass, Role r)
    : m_id(id), m_username(uname), m_role(r) {
    m_passwordKey = PasswordManager::generateRandomKey();
    m_passwordHash = PasswordManager::encryptPassword(pass, m_passwordKey);
}

User::User(int id, std::string uname, std::string passwordHash, int passwordKey, Role r)
    : m_id(id), m_username(uname), m_passwordHash(passwordHash), m_passwordKey(passwordKey), m_role(r) {}

User::User(User&& other) noexcept
    : m_id(other.m_id),
      m_username(std::move(other.m_username)),
      m_passwordKey(other.m_passwordKey),
      m_passwordHash(std::move(other.m_passwordHash)),
      m_role(other.m_role)
{
    other.m_id = 0;
    other.m_username.clear();
    other.m_passwordKey = 0;
    other.m_passwordHash.clear();
}

int User::getId() const
{
    return m_id;
}

std::string User::getUsername() const
{
    return m_username;
}

int User::getPassKey() const
{
    return m_passwordKey;
}

std::string User::getPassHash() const
{
    return m_passwordHash;
}

int User::getRole() const
{
    return static_cast<int>(m_role);
}

bool User::checkPassword(const std::string& inputPassword) {
    return PasswordManager::checkPassword(inputPassword, m_passwordHash, m_passwordKey);
}

void User::changeUsername(std::string uname) {
    m_username = uname;
}
