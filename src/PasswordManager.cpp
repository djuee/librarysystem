#include "PasswordManager.h"
#include <random>

char PasswordManager::generateRandomKey() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(33, 126); // видимые символы ASCII
    return static_cast<char>(dist(gen));
}

std::string PasswordManager::encryptPassword(const std::string& password, const char& key) {
    std::string encryptPass = password;
    for (char& symb : encryptPass) {
        symb ^= key;
    }
    return encryptPass;
}

bool PasswordManager::checkPassword(const std::string& inputPassword, const std::string& passwordHash, const char& key) {
    std::string encryptPass = inputPassword;
    for (char& symb : encryptPass) {
        symb ^= key;
    }
    return encryptPass == passwordHash;
}
