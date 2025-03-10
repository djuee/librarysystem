#include <iostream>
#include <User.h>

class Admin final : public User {
public:
    Admin(std::string uname, std::string pass);
};
