#include "User.h"
#include <PasswordManager.h>

User::User(std::string uname, std::string pass, Role r)
    : m_username(uname), m_role(r) {
    m_passwordKey = PasswordManager::generateRandomKey();
    m_passwordHash = PasswordManager::encryptPassword(pass, m_passwordKey);
}

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
