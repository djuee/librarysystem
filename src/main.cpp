#include <iostream>
#include <memory>
#include <User.h>
#include <TextBook.h>
#include <Reader.h>
#include <Novel.h>
#include <ResearchPaper.h>
#include <DatabaseManager.h>

int main()
{
    DatabaseManager &db = DatabaseManager::getInstance();
    Admin adm(1, "Alexey", "12345");
    Reader user(1, "Sveta", "1506");
    user.returnBook(1);
}
