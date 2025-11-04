#include "DatabaseManager.h"
#include <iostream>
#include <string>

DatabaseManager::DatabaseManager(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS DeviceState ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "LightIsOn      BOOL,"
        "LightColor     TEXT,"
        "CondIsOn       BOOL,"
        "CondTemp       INT,"
        "DoorIsOpen     BOOL,"
        "DoorIsLocked   BOOL);";

    char* zErrMsg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &zErrMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else {
        std::cout << "Table created or already exists" << std::endl;
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
}

void DatabaseManager::saveState(const DeviceState& state) {
    const char* sql =
        "INSERT OR REPLACE INTO DeviceState (ID, LightIsOn, LightColor, CondIsOn, CondTemp, DoorIsOpen, DoorIsLocked) "
        "VALUES (1, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, state.light_isOn);
    sqlite3_bind_text(stmt, 2, state.light_color.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, state.conditioner_isOn);
    sqlite3_bind_int(stmt, 4, state.conditioner_temp);
    sqlite3_bind_int(stmt, 5, state.door_isOpen);
    sqlite3_bind_int(stmt, 6, state.door_isLocked);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "State saved to DB." << std::endl;
    }

    sqlite3_finalize(stmt);
}

DeviceState DatabaseManager::loadState() {
    DeviceState state = { false, "white", false, 20, false, true };
    const char* sql = "SELECT LightIsOn, LightColor, CondIsOn, CondTemp, DoorIsOpen, DoorIsLocked FROM DeviceState WHERE ID = 1;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare select: " << sqlite3_errmsg(db) << std::endl;
        return state;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        state.light_isOn = sqlite3_column_int(stmt, 0);
        state.light_color = (const char*)sqlite3_column_text(stmt, 1);
        state.conditioner_isOn = sqlite3_column_int(stmt, 2);
        state.conditioner_temp = sqlite3_column_int(stmt, 3);
        state.door_isOpen = sqlite3_column_int(stmt, 4);
        state.door_isLocked = sqlite3_column_int(stmt, 5);

        std::cout << "State loaded from DB." << std::endl;
    }
    else {
        std::cout << "No saved state found. Using default state." << std::endl;
        saveState(state);
    }

    sqlite3_finalize(stmt);
    return state;
}