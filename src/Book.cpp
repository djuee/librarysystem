#include "Book.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Book::Book(int id, std::string title, std::string author)
    : m_id(id), m_title(title), m_author(author) {}

void Book::markAsBorrowed() {
    m_isAvailable = false;
}

void Book::markAsAvailable() {
    m_isAvailable = true;
}

bool Book::isAvailable() const {
    return m_isAvailable;
}

std::string Book::getBookText(const std::string& filePath) const {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Не удалось открыть файл: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
