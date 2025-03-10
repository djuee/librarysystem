#include <iostream>
#include <Book.h>

enum Genre { Mystery, Thriller, Fantasy, Romance, Historical, Horror, Biography, Drama, Comedy };

class Novel final : public Book {
private:
    Genre genre;
    int publishedYear;
    int countPages;

public:
    Novel(int id, std::string title, std::string author, Genre genre, int publishedYear, int countPages);
};
