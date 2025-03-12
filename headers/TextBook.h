#include <iostream>
#include <Book.h>

enum Subject { Math, Physics, Biology, Chemistry, Geography, History, Literature };
enum Level { beginner, intermidate, advanced };

class TextBook final : public Book
{
public:
    TextBook(int id, std::string title, std::string author, Subject subject, Level level, std::string edition);

    std::string getSubject();
    std::string getLevel();
    std::string getEdition();

    std::string getInsertSQL() const override;
    void bindInsertParameters(SQLite::Statement& query) const override;

private:
    Subject m_subject;
    Level m_level;
    std::string m_edition;
};
