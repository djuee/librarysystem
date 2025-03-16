#include "User.h"
#include <PasswordManager.h>

User::User(int id, std::string uname, std::string pass, Role r)
    : m_id(id), m_username(uname), m_role(r) {
    m_passwordKey = PasswordManager::generateRandomKey();
    m_passwordHash = PasswordManager::encryptPassword(pass, m_passwordKey);
}

User::User(int id, std::string uname, std::string passwordHash, int passwordKey, Role r)
    : m_id(id), m_username(uname), m_passwordHash(passwordHash), m_passwordKey(passwordKey), m_role(r) {}

std::string User::getUsername() const {
    return m_username;
}

Role User::getRole() const {
    return m_role;
}

bool User::checkPassword(const std::string& inputPassword) {
    return PasswordManager::checkPassword(inputPassword, m_passwordHash, m_passwordKey);
}

void User::changeUsername(std::string uname) {
    m_username = uname;
}
