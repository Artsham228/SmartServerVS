#include "crow.h"
#include <string>
#include <iostream>
#include <mutex>

#include "LightBulb.h"
#include "Conditioner.h"
#include "Door.h"
#include "DatabaseManager.h"

struct ApiSecurityMiddleware {
    const std::string MASTER_TOKEN = "my-secret-key-12345";

    struct context {};

    void before_handle(crow::request& req, crow::response& res, context& ctx) {
        if (req.url == "/") {
            return;
        }

        std::string provided_key = req.get_header_value("X-API-Key");
        if (provided_key != MASTER_TOKEN) {
            res.code = 401;
            res.body = "Unauthorized: Missing or invalid API Key.";
            res.end();
            return;
        }
    }

    void after_handle(crow::request& req, crow::response& res, context& ctx) {
    }
};

int main()
{
    DatabaseManager dbManager("smarthome.db");
    DeviceState initialState = dbManager.loadState();

    crow::App<ApiSecurityMiddleware> app;

    std::mutex db_mutex;

    LightBulb livingRoomLight;
    livingRoomLight.setColor(initialState.light_color);
    if (initialState.light_isOn) livingRoomLight.turnOn();

    Conditioner mainConditioner;
    mainConditioner.setTemperature(initialState.conditioner_temp);
    if (initialState.conditioner_isOn) mainConditioner.turnOn();

    Door mainDoor;
    if (initialState.door_isOpen) mainDoor.Open();
    mainDoor.setLock(initialState.door_isLocked);

    CROW_ROUTE(app, "/")
        ([]() {
        crow::response res;
        res.set_static_file_info("index.html");
        return res;
            });

    CROW_ROUTE(app, "/light/status")
        ([&livingRoomLight]() {
        crow::json::wvalue response;
        response["status_message"] = livingRoomLight.getStatus();
        response["is_on"] = livingRoomLight.getIsOn();
        return response;
            });

    CROW_ROUTE(app, "/light/set")
        .methods("POST"_method)
        ([&](const crow::request& req) {
        std::lock_guard<std::mutex> lock(db_mutex);
        crow::json::rvalue request_body = crow::json::load(req.body);
        if (!request_body || !request_body.has("state")) {
            return crow::response(400, "Bad request:'state' key is missing");
        }
        std::string state = request_body["state"].s();
        std::string message;
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

        DeviceState currentState = { livingRoomLight.getIsOn(), livingRoomLight.getColor(), mainConditioner.getTemperature(), mainConditioner.getIsOn(), mainDoor.getIsOpen(), mainDoor.getIsLocked() };
        dbManager.saveState(currentState);

        crow::json::wvalue response_json;
        response_json["action_result"] = message;
        response_json["current_status"] = livingRoomLight.getStatus();
        return crow::response(200, response_json);
            });

    CROW_ROUTE(app, "/light/set_color")
        .methods("POST"_method)
        ([&](const crow::request& req) {
        std::lock_guard<std::mutex> lock(db_mutex);
        crow::json::rvalue request_body = crow::json::load(req.body);
        if (!request_body || !request_body.has("color")) {
            return crow::response(400, "Bad request:'color' key is missing");
        }
        std::string newColor = request_body["color"].s();
        bool success = livingRoomLight.setColor(newColor);

        crow::json::wvalue response;
        if (success) {
            response["message"] = "Color changed successfully";
            DeviceState currentState = { livingRoomLight.getIsOn(), livingRoomLight.getColor(), mainConditioner.getTemperature(), mainConditioner.getIsOn(), mainDoor.getIsOpen(), mainDoor.getIsLocked() };
            dbManager.saveState(currentState);
        }
        else {
            response["message"] = "Invalid color: " + newColor;
        }
        response["new_color"] = livingRoomLight.getColor();
        return crow::response(200, response);
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
        .methods("POST"_method)
        ([&](const crow::request& req) {
        std::lock_guard<std::mutex> lock(db_mutex);
        crow::json::rvalue request_body = crow::json::load(req.body);
        if (!request_body || !request_body.has("state")) {
            return crow::response(400, "Bad request:'state'key is missing");
        }
        std::string state = request_body["state"].s();
        std::string message = "Unknown state";
        if (state == "on") {
            mainConditioner.turnOn();
            message = "Conditioner turned on";
        }
        else if (state == "off") {
            mainConditioner.turnOff();
            message = "Conditioner turned off";
        }

        DeviceState currentState = { livingRoomLight.getIsOn(), livingRoomLight.getColor(), mainConditioner.getTemperature(), mainConditioner.getIsOn(), mainDoor.getIsOpen(), mainDoor.getIsLocked() };
        dbManager.saveState(currentState);

        crow::json::wvalue response;
        response["action_result"] = message;
        response["current_status"] = mainConditioner.getStatus();
        return crow::response(200, response);
            });

    CROW_ROUTE(app, "/conditioner/set_temp")
        .methods("POST"_method)
        ([&](const crow::request& req) {
        std::lock_guard<std::mutex> lock(db_mutex);
        crow::json::rvalue request_body = crow::json::load(req.body);
        if (!request_body || !request_body.has("temp")) {
            return crow::response(400, "Bad request:'temp' key is missing");
        }
        int newTemp = request_body["temp"].i();
        mainConditioner.setTemperature(newTemp);

        DeviceState currentState = { livingRoomLight.getIsOn(), livingRoomLight.getColor(), mainConditioner.getTemperature(), mainConditioner.getIsOn(), mainDoor.getIsOpen(), mainDoor.getIsLocked() };
        dbManager.saveState(currentState);

        crow::json::wvalue response;
        response["message"] = "Temperature command sent";
        response["new_temperature"] = mainConditioner.getTemperature();
        response["status"] = mainConditioner.getStatus();
        return crow::response(200, response);
            });

    CROW_ROUTE(app, "/door/status")
        ([&mainDoor]() {
        crow::json::wvalue response;
        response["status_message"] = mainDoor.getStatus();
        response["is_open"] = mainDoor.getIsOpen();
        response["is_locked"] = mainDoor.getIsLocked();
        return response;
            });

    CROW_ROUTE(app, "/door/set_state")
        .methods("POST"_method)
        ([&](const crow::request& req) {
        std::lock_guard<std::mutex> lock(db_mutex);
        crow::json::rvalue request_body = crow::json::load(req.body);
        if (!request_body || !request_body.has("state")) {
            return crow::response(400, "Bad request:'state'key is missing");
        }
        std::string state = request_body["state"].s();
        std::string message = "no state provided";
        if (state == "open") {
            mainDoor.Open();
            message = "Door opened";
        }
        else if (state == "close") {
            mainDoor.Close();
            message = "Door closed";
        }

        DeviceState currentState = { livingRoomLight.getIsOn(), livingRoomLight.getColor(), mainConditioner.getTemperature(), mainConditioner.getIsOn(), mainDoor.getIsOpen(), mainDoor.getIsLocked() };
        dbManager.saveState(currentState);

        crow::json::wvalue response;
        response["action_result"] = message;
        response["current_status"] = mainDoor.getStatus();
        return crow::response(200, response);
            });

    CROW_ROUTE(app, "/door/set_lock")
        .methods("POST"_method)
        ([&](const crow::request& req) {
        std::lock_guard<std::mutex> lock(db_mutex);
        crow::json::rvalue request_body = crow::json::load(req.body);
        if (!request_body || !request_body.has("lock")) {
            return crow::response(400, "Bad request:'lock' key is missing");
        }
        bool lock_status = request_body["lock"].b();
        mainDoor.setLock(lock_status);
        std::string message = lock_status ? "Door locked" : "Door unlocked";

        DeviceState currentState = { livingRoomLight.getIsOn(), livingRoomLight.getColor(), mainConditioner.getTemperature(), mainConditioner.getIsOn(), mainDoor.getIsOpen(), mainDoor.getIsLocked() };
        dbManager.saveState(currentState);

        crow::json::wvalue response;
        response["action_result"] = message;
        response["current_status"] = mainDoor.getStatus();
        return crow::response(200, response);
            });

    std::cout << "Starting server on port 18080..." << std::endl;
    app.port(18080).multithreaded().run();
}