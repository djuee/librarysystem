#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

enum TypeBook {textBook, novel, researchPaper};
enum Subject {Math, Physics, Biology, Chemistry, Geography, History, Literature};
enum Level {beginner, intermidate, advanced};
enum Genre {Mystery, Thriller, Fantasy, Romance, Historical, Horror, Biography, Drama, Comedy};
enum Field {Humanities, Biological, Natural, Public, Technique};

class Book
{
public:
    Book(int id, std::string title, std::string author)
        : m_id(id), m_title(title), m_author(author) {}
        
    virtual ~Book() = default;

    void markAsBorrowed() 
    {
        m_isAvailable = false;
    }

    std::string getBookText(const std::string& filePath) const
    {
        std::ifstream file(filePath);
        if (!file)
        {
            std::cerr << "Не удалось открыть файл: " << filePath << std::endl;
        }
        return "";
    }

    void markAsAvailable()
    {
        m_isAvailable = true;
    }
    
    bool isAvailable() const
    {
        return m_isAvailable;
    }

protected:
    // Доступ к этим переменным сделать через методы
    int m_id;
    std::string m_title;
    std::string m_author;
    bool m_isAvailable{true};

    TypeBook m_typeBook;
    std::string m_bookPath;
};

class TextBook final : public Book 
{
public:
    Subject subject; // Предмет
    Level level; // Уровень сложности
    std::string edition; // Издание

    TextBook(int id, std::string title, std::string author, Subject subject, Level level, std::string edition)
        : Book(id, title, author)
        , subject(subject)
        , level(level)
        , edition(edition)
    {
        m_typeBook = textBook;
    }
};

class Novel final : public Book 
{
public:
    Genre genre; // Жанр
    int publishedYear; // Год издания
    int countPages; // Количество страниц

    Novel(int id, std::string title, std::string author, Genre genre, int publishedYear, int countPages)
        : Book(id, title, author)
        , genre(genre)
        , publishedYear(publishedYear)
        , countPages(countPages)
    {
        m_typeBook = TypeBook::novel;
    }
};

class ResearchPaper : public Book
{
public:
    Field field; // Область исследования
    std::string conference; // Конференция или журнал, где опубликована статья
    std::string doi; // Уникальный идентификатор статьи

    ResearchPaper(int id, std::string title, std::string author, Field field, std::string conference, std::string doi)
        : Book(id, title, author), field(field), conference(conference), doi(doi)
    {
        m_typeBook = TypeBook::researchPaper;
    }
};


