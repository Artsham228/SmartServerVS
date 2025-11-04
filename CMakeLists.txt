cmake_minimum_required(VERSION 3.20)
project(SmartServerVS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Crow CONFIG REQUIRED)

add_executable(SmartServerVS
    "src/main.cpp"
    "src/LightBulb.cpp"
    "src/Conditioner.cpp"
    "src/Door.cpp"
    "src/DatabaseManager.cpp"
    "vendor/sqlite/sqlite3.c"
)

target_include_directories(SmartServerVS
    PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/vendor/sqlite"
)

target_link_libraries(SmartServerVS
    PRIVATE
    Crow::Crow
)
add_custom_command(
    TARGET SmartServerVS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/index.html"
    "$<TARGET_FILE_DIR:SmartServerVS>"
)