#include <iostream>
#include <memory>
#include <User.h>
#include <TextBook.h>
#include <Reader.h>
#include <Novel.h>
#include <ResearchPaper.h>

int main()
{
    std::shared_ptr<Reader> user1 = std::make_shared<Reader>("Alexey", "12345678");
    std::shared_ptr<Book> book1 = std::make_shared<TextBook>(1, "Война и мир", "Лев Толстой", Subject::Literature, (Level)0, "4.5");
    user1->takeBook(book1);
    std::cout << book1->isAvailable() << std::endl;
}
