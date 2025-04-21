#pragma once

#include <crow.h>
#include "Controller.h"

class ApiServer {
public:
    ApiServer(int port = 18080);
    void run();

private:
    int port_;
    crow::SimpleApp app_;
    Controller controller_;

    void setupRoutes();
};
