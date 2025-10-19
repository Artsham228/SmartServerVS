#include <iostream>
#include <vector>
#include "crow.h"
#include "string"

struct Task {
    int id;
    std::string title;
    bool is_done;
};

int main()
{
    crow::SimpleApp app;
    std::cout << "Starting server on http://localhost:18080..." << std::endl;
    app.port(18080).multithreaded().run();
    return 0;
}