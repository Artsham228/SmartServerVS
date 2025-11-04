# Smart Home C++ Server & Android Client

This project is a full-stack smart home control system. It features a high-performance, stateful C++ backend server and a native Android client for remote control.

The server manages multiple IoT devices (lights, doors, air conditioning) and persists their state in a database. The API is secured via token authentication.

## 1. Architecture

The system uses a 3-tier architecture:

1.  **Client (Frontend):** A native Android application written in Kotlin. It communicates with the C++ server via a REST API.
2.  **Server (Backend):** A C++ application built with the Crow micro-framework. It handles business logic, authentication, and database communication.
3.  **Database (Persistence):** A lightweight SQLite database (`smarthome.db`) that stores the last known state of all devices, allowing the server to be stateful across restarts.


## 2. Features

* **C++ REST API Server:** A lightweight, multithreaded server built with Crow.
* **Device Control:** Manages a `LightBulb` (on/off, color), `Conditioner` (on/off, temperature), and `Door` (open/close, lock/unlock).
* **Persistent State:** Uses SQLite to save and load the state of all devices on server startup and shutdown.
* **Secure API:** All API endpoints (except the root `/`) are protected by `X-API-Key` token authentication using custom Crow middleware.
* **Native Android Client:** An Android app (Kotlin/Retrofit) that acts as a remote control.
* **Web Test Client:** A simple `index.html` file served from the root (`/`) for basic testing.

## 3. Tech Stack

* **Backend:**
    * C++17
    * Crow (C++ Web Framework)
    * SQLite (Database)
    * CMake (Build System)
* **Frontend (Mobile):**
    * Kotlin
    * Android Studio
    * Retrofit (HTTP Client)
* **Frontend (Web Demo):**
    * HTML
    * JavaScript (ES6 async/await)
* **Security:**
    * `X-API-Key` HTTP Header Authentication.

## 4. Backend Setup & Build (CMake)

### Prerequisites

* Windows 10/11
* Visual Studio 2022 (with C++ and CMake workloads)
* [vcpkg](https://vcpkg.io/en/index.html) (C++ Package Manager)

### Build Steps

1.  **Clone the Repository:**
    ```bash
    git clone <your-repo-url>
    cd <your-repo-folder>
    ```

2.  **Install Dependencies (vcpkg):**
    This project requires `crow`. Install it via vcpkg:
    ```bash
    vcpkg install crow
    ```

3.  **Configure CMake:**
    Configure the project using the vcpkg toolchain file.
    ```bash
    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
    ```
    *Note: If using Visual Studio's CMake integration, it will handle this automatically if configured.*

4.  **Build the Project:**
    ```bash
    cmake --build build
    ```
    This will create `SmartServerVS.exe` inside the build directory (e.g., `build/Debug/`).

5.  **Source Files:**
    The project expects the following structure:
    ```
    /
    ├── CMakeLists.txt
    ├── index.html         <-- Web client, copied on build
    ├── include/
    │   ├── LightBulb.h
    │   ├── Conditioner.h
    │   ├── Door.h
    │   └── DatabaseManager.h
    ├── src/
    │   ├── main.cpp
    │   ├── LightBulb.cpp
    │   ├── Conditioner.cpp
    │   ├── Door.cpp
    │   └── DatabaseManager.cpp
    └── vendor/
        └── sqlite/
            ├── sqlite3.c
            └── sqlite3.h
    ```

## 5. Running the Server

1.  **Run the Executable:**
    Navigate to your build directory and run the server.
    ```bash
    ./build/Debug/SmartServerVS.exe
    ```

2.  **File Generation:**
    On the first run, the server will automatically create `smarthome.db` in the same directory. The `index.html` file is copied from the source directory on build.

3.  **Windows Firewall:**
    On the first run, Windows Defender Firewall will ask for permission. You **must** allow access for **"Private networks"** for the Android app to be able to connect.

4.  **Access:**
    * **Web Client:** `http://localhost:18080/`
    * **API:** `http://<Your-Server-IP>:18080/`

## 6. API Reference (The Contract)

This is the API contract used by the mobile client.

* **Base URL:** `http://<SERVER_IP>:18080`
* **Authentication:** All requests (except `/`) **must** include the following HTTP header:
    * **Header:** `X-API-Key`
    * **Value:** `my-secret-key-12345`

---

### Light Bulb

#### `GET /light/status`
Retrieves the current state of the light.

* **Response (200 OK):**
    ```json
    {
      "status_message": "bulb turned on, color: red",
      "is_on": true
    }
    ```

#### `POST /light/set`
Turns the light on or off.

* **Request Body:**
    ```json
    {
      "state": "on"
    }
    ```
* **Response (200 OK):**
    ```json
    {
      "action_result": "Light turned on",
      "current_status": "bulb turned on, color: red"
    }
    ```

#### `POST /light/set_color`
Sets the color of the light.

* **Request Body:**
    ```json
    {
      "color": "blue"
    }
    ```
* **Response (200 OK):**
    ```json
    {
      "message": "Color changed successfully",
      "new_color": "blue"
    }
    ```
* **Response (on failure):**
    ```json
    {
      "message": "Invalid color: potato",
      "new_color": "red"
    }
    ```

---

### Conditioner

#### `GET /conditioner/status`
Retrieves the current state of the conditioner.

* **Response (200 OK):**
    ```json
    {
      "status message": "conditioner is turned on, temp: 22",
      "is_on": true,
      "current_temperature": 22
    }
    ```

#### `POST /conditioner/set`
Turns the conditioner on or off.

* **Request Body:**
    ```json
    {
      "state": "off"
    }
    ```
* **Response (200 OK):**
    ```json
    {
      "action_result": "Conditioner turned off",
      "current_status": "conditioner is turned off, temp: 22"
    }
    ```

#### `POST /conditioner/set_temp`
Sets the target temperature.

* **Request Body:**
    ```json
    {
      "temp": 24
    }
    ```
* **Response (200 OK):**
    ```json
    {
      "message": "Temperature command sent",
      "new_temperature": 24,
      "status": "conditioner is turned on, temp: 24"
    }
    ```

---

### Door

#### `GET /door/status`
Retrieves the current state of the door.

* **Response (200 OK):**
    ```json
    {
      "status_message": "Door is unlocked",
      "is_open": false,
      "is_locked": false
    }
    ```

#### `POST /door/set_state`
Opens or closes the door.

* **Request Body:**
    ```json
    {
      "state": "open"
    }
    ```
* **Response (200 OK):**
    ```json
    {
      "action_result": "Door opened",
      "current_status": "Door is unlocked"
    }
    ```

#### `POST /door/set_lock`
Locks or unlocks the door.

* **Request Body:**
    ```json
    {
      "lock": true
    }
    ```
* **Response (200 OK):**
    ```json
    {
      "action_result": "Door locked",
      "current_status": "Door is locked"
    }
    ```

---

### Error Codes

* `200 OK`: Request was successful.
* `400 Bad Request`: The request JSON was malformed or missing a required key (e.g., `{"state": ...}`).
* `401 Unauthorized`: The `X-API-Key` header was missing or incorrect.
* `404 Not Found`: The API endpoint does not exist.
