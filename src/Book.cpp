#include "Book.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

Book::Book(int id, std::string title, std::string author)
    : m_id(id), m_title(title), m_author(author) {}

int Book::getId()
{
    return m_id;
}

std::string Book::getAuthor()
{
    return m_author;
}

std::string Book::getTitle()
{
    return m_title;
}

std::string Book::getTypeBook()
{
    return std::to_string(m_typeBook);
}

void Book::markAsBorrowed() {
    m_isAvailable = false;
}

void Book::markAsAvailable() {
    m_isAvailable = true;
}

bool Book::isAvailable() const {
    return m_isAvailable;
}
