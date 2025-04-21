#include <iostream>
#include "ApiServer.h"

int main()
{
    ApiServer server(18080);
    server.run();
    return 0;
}
