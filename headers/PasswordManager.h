#pragma once
#include <string>

class PasswordManager {
public:
    static char generateRandomKey();
    static std::string encryptPassword(const std::string& password, const char& key);
    static bool checkPassword(const std::string& inputPassword, const std::string& passwordHash, const char& key);
};
