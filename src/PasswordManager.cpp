#include <iostream>
#include <random>

class PasswordManager {
public:
    static char generateRandomKey() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(33, 126);
        return static_cast<char>(dist(gen));
    }

    static std::string encryptPassword(const std::string& password, const char& key) {
        std::string encryptPass = password;
        for (char& symb : encryptPass) {
            symb ^= key;
        }

        return encryptPass;
    }

    static bool checkPassword(const std::string& inputPassword, const std::string& passwordHash, const char& key) {
        std::string encryptPass = inputPassword;
        for (char& symb : encryptPass) {
            symb ^= key;
        }
        if (encryptPass == passwordHash) {
            return true;
        }
        else {
            return false;
        }
    }
};
