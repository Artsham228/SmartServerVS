#pragma once
#include <string>
#include "sqlite3.h"

struct DeviceState {
    bool light_isOn;
    std::string light_color;
    int conditioner_temp;
    bool conditioner_isOn;
    bool door_isOpen;
    bool door_isLocked;
};

class DatabaseManager {
private:
    sqlite3* db;

public:
    DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();

    void saveState(const DeviceState& state);
    DeviceState loadState();
};