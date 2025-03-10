#include <iostream>
#include <Book.h>

enum Subject { Math, Physics, Biology, Chemistry, Geography, History, Literature };
enum Level { beginner, intermidate, advanced };

class TextBook final : public Book {
private:
    Subject subject;
    Level level;
    std::string edition;

public:
    TextBook(int id, std::string title, std::string author, Subject subject, Level level, std::string edition);
};
