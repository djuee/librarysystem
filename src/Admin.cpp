#include <iostream>
#include <Admin.h>

Admin::Admin(std::string uname, std::string pass)
    : User(uname, pass, Role::ADMIN) {}
