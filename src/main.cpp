#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <list>
#include <memory>
#include "User.cpp"

int main()
{
    std::list<std::shared_ptr<Book>> list1;
    std::list<std::shared_ptr<Book>> list2;

    {
        auto bookPtr = std::make_shared<TextBook>(1, "asd", "dsad", Subject::Biology, Level::advanced, "4.0");
        list1.emplace_back(bookPtr);
        list2.emplace_back(bookPtr);
    }

    Reader reader("a", "2134");
    ///reader.getBook(bookPtr.ge);

    //delete bookPtr;
}
