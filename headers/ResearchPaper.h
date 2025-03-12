#include <iostream>
#include <Book.h>

enum Field { Humanities, Biological, Natural, Public, Technique };

class ResearchPaper : public Book {
public:
    ResearchPaper(int id, std::string title, std::string author, Field field, std::string conference, std::string doi);

    std::string getField();
    std::string getConference();
    std::string getDoi();

    std::string getInsertSQL() const override;
    void bindInsertParameters(SQLite::Statement& query) const override;

private:
    Field m_field;
    std::string m_conference;
    std::string m_doi;
};
