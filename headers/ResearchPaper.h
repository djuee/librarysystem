#include <iostream>
#include <Book.h>

enum Field { Humanities, Biological, Natural, Public, Technique };

class ResearchPaper : public Book {
public:
    Field field;
    std::string conference;
    std::string doi;

    ResearchPaper(int id, std::string title, std::string author, Field field, std::string conference, std::string doi);
};
