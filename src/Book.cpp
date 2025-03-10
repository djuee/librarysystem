#include "Book.h"

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

TextBook::TextBook(int id, std::string title, std::string author, Subject subject, Level level, std::string edition)
    : Book(id, title, author), subject(subject), level(level), edition(edition) {
    m_typeBook = textBook;
}

Novel::Novel(int id, std::string title, std::string author, Genre genre, int publishedYear, int countPages)
    : Book(id, title, author), genre(genre), publishedYear(publishedYear), countPages(countPages) {
    m_typeBook = novel;
}

ResearchPaper::ResearchPaper(int id, std::string title, std::string author, Field field, std::string conference, std::string doi)
    : Book(id, title, author), field(field), conference(conference), doi(doi) {
    m_typeBook = researchPaper;
}
