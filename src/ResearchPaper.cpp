#include <ResearchPaper.h>

ResearchPaper::ResearchPaper(int id, std::string title, std::string author, Field field, std::string conference, std::string doi)
    : Book(id, title, author), field(field), conference(conference), doi(doi)
{
    m_typeBook = researchPaper;
}
