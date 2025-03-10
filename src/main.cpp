#include <Book.h>
#include <iostream>
#include <memory>
#include <User.h>

class Test
{
public:
    int h = 0;
};

int main()
{
    std::shared_ptr<Test> test_ptr = std::make_shared<Test>();
    test_ptr->h = 5;
}
