#include <iostream>
#include <vector>
#include "crow.h"

// �������� ������ ��������� ��� ��������� ����� ��� ��������
struct Task {
    int id;
    std::string title;
    bool is_done;
};

int main()
{
    crow::SimpleApp app;


    std::vector<Task> tasks = {
        {1, "������ ������", false},
        {2, "������� �����������", true},
        {3, "�������������� ���", false}
    };

    
    CROW_ROUTE(app, "/")([]() {
        return "SERVER IS WORKING!";
        });

    
    CROW_ROUTE(app, "/tasks")([&tasks]() {
        
        crow::json::wvalue response;
        for (size_t i = 0; i < tasks.size(); ++i) {
            response[i]["id"] = tasks[i].id;
            response[i]["title"] = tasks[i].title;
            response[i]["is_done"] = tasks[i].is_done;
        }
        return response;
        });

    
    std::cout << "Starting server on port 18080..." << std::endl;
    app.port(18080).multithreaded().run();

    return 0;
}