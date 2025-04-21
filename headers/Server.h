#pragma once

#include <iostream>

#include <crow.h>
#include <Controller.h>

class Server
{
private:
    Controller controller();

public:
    void run(int port = 10000);
};
