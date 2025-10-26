#include <iostream>
#include <vector>
#include "crow.h"
#include "string"
#include "LightBulb.h"
#include "Conditioner.h"
#include "Door.h"
int main()
{
    crow::SimpleApp app;
    LightBulb livingRoomLight;
    Conditioner mainConditioner;
    Door mainDoor;
    CROW_ROUTE(app, "/light/status")
        ([&livingRoomLight]() {
        crow::json::wvalue response;
        response["status_message"] = livingRoomLight.getStatus();
        response["is_on"] = livingRoomLight.getIsOn();
        return response;
            });
    CROW_ROUTE(app, "/light/set")
        ([&livingRoomLight](const crow::request& req) {
        char* stateParam = req.url_params.get("state");
        std::string message = "no state provided";
        if (stateParam) {
            std::string state = stateParam;
            if (state == "on") {
                livingRoomLight.turnOn();
                message = "Light turned on";
            }
            else if (state == "off") {
                livingRoomLight.turnOff();
                message = "Light turned off";
            }
            else {
                message = "Unknown state";
            }
        }
        crow::json::wvalue response;
        response["action_result"] = message;
        response["current_status"] = livingRoomLight.getStatus();
        return response;
            });
    CROW_ROUTE(app, "/light/set_color/<string>")
        ([&livingRoomLight](std::string newColor) {
        livingRoomLight.setColor(newColor);
                crow::json::wvalue response;
            response["System message"]="Color command sent";
            response["New color is"] = livingRoomLight.getColor();
            response["status"] = livingRoomLight.getStatus();
            return response;
            });
    CROW_ROUTE(app, "/conditioner/status")
        ([&mainConditioner]() {
        crow::json::wvalue response;
        response["status message"] = mainConditioner.getStatus();
        response["is_on"] = mainConditioner.getIsOn();
        response["current_temperature"] = mainConditioner.getTemperature();
        return response;
            });
    CROW_ROUTE(app, "/conditioner/set")
        ([&mainConditioner](const crow::request& req) {
        char* stateParam = req.url_params.get("state");
        std::string message = "no state provided";
        if (stateParam) {
            std::string state = stateParam;
            if (state == "on") {
                mainConditioner.turnOn();
                message = "Conditioner turned on";
            }
            else if (state == "off") {
                mainConditioner.turnOff();
                message = "Conditioner turned off";
            }
            else {
                message = "Unknown state";

            }
        }
        crow::json::wvalue response;
        response["action_result"] = message;
        response["current_status"] = mainConditioner.getStatus();
        return response;
            });
    CROW_ROUTE(app, "/conditioner/set_temp/<int>")
        ([&mainConditioner](int newTemp){
        mainConditioner.setTemperature(newTemp);
        crow::json::wvalue response;
        response["Temperature command sent.\nNew temperature is:"] = mainConditioner.getTemperature();
        response["status"] = mainConditioner.getStatus();
        return response;
});
    CROW_ROUTE(app,"/door/status")([&mainDoor]() {
        crow::json::wvalue response;
        response["status message"] = mainDoor.getStatus();
        response["is_on"] = mainDoor.getIsOn();
        return response;
    });
    CROW_ROUTE(app,"/door/set")
        ([&mainDoor](const crow::request&req) {
        char* stateParam = req.url_params.get("state");
        std::string message = "no state provided";
        if (stateParam) {
            std::string state = stateParam;
            if (state == "on") {
                mainDoor.turnOn();
                message = "Door turned on";
            }
            else if (state == "off") {
                mainDoor.turnOff();
                message = "Door turned off";
            }
            else {
                message = "Unknown state";

            }
        }
        crow::json::wvalue response;
        response["action_result"] = message;
        response["current_status"] = mainDoor.getStatus();
        return response;
    });
    std::cout << "Starting server on port 18080..." << std::endl;
    app.port(18080).multithreaded().run();
}