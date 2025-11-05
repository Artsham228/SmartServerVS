# Smart Home Android Client

This is the native Android client for the custom Smart Home control system. It acts as a remote control, communicating with the C++ backend server via a secured REST API to manage IoT devices in real-time.

## 1. Architecture

The application follows a clean client-server model tailored for Android:

1.  **UI Layer (Frontend):** XML layouts define the user interface, providing intuitive controls (Buttons, TextViews, EditTexts) for each device type.
2.  **Business Logic (Activity):** `MainActivity` handles user interactions, validates input (e.g., temperature limits), and manages the application lifecycle.
3.  **Network Layer (Data):** Powered by **Retrofit 2**, this layer handles all HTTP communication. It uses Kotlin Coroutines for asynchronous non-blocking calls and automatically injects the required `X-API-Key` security token into every request.

## 2. Features

* **Real-time Control:** Instantly toggle lights, lock/unlock doors, and adjust air conditioner temperature.
* **Live Status Updates:** The app fetches and displays the current state of all devices directly from the server upon launch and after every action.
* **Secure Communication:** All API requests are authenticated using a custom `X-API-Key` header.
* **Input Validation:** Prevents sending invalid data (e.g., temperature outside the 13-31°C range) to the server.

## 3. Tech Stack

* **Language:** Kotlin
* **Core Components:** Android SDK, AppCompat
* **Networking:** Retrofit 2, OkHttp, GSON (for JSON parsing)
* **Concurrency:** Kotlin Coroutines (suspend functions, lifecycleScope)
* **Build System:** Gradle

## 4. Setup & Configuration

Before building the project, you must configure it to match your local network environment.

### Prerequisites
* Android Studio Iguana (or newer)
* Android SDK (API level 31 or higher recommended)
* An Android device or emulator connected to the same Wi-Fi network as the C++ server.

### Configuration Steps

1.  **Configure Server IP:**
    Open `app/src/main/java/com/example/smarthomeapp/RetrofitClient.kt` and update the `BASE_URL` with your C++ server's local IP address:
    ```kotlin
    // Replace '192.168.0.104' with your actual server IP found via 'ipconfig'
    private const val BASE_URL = "[http://192.168.0.104:18080/](http://192.168.0.104:18080/)"
    ```

2.  **Configure Security Token:**
    Open `app/src/main/java/com/example/smarthomeapp/MainActivity.kt` and ensure the `API_KEY` matches the one configured on your backend:
    ```kotlin
    private val API_KEY = "my-secret-key-12345"
    ```

3.  **Network Permissions:**
    Ensure your `AndroidManifest.xml` includes the necessary permissions for local network communication:
    ```xml
    <uses-permission android:name="android.permission.INTERNET" />
    <application
        ...
        android:usesCleartextTraffic="true"
        ...>
    ```

## 5. Building and Running

1.  **Open Project:** Launch Android Studio and open the project root folder.
2.  **Sync Gradle:** Allow Android Studio to download necessary dependencies.
3.  **Run:** Connect your Android device via USB (ensure USB Debugging is enabled) or launch an AVD (Android Virtual Device). Click the **Run** button (▶) in Android Studio.

## 6. Troubleshooting

* **"Network Error" / Timeout:**
    * Ensure both phone and PC are on the **same Wi-Fi** network.
    * Verify the IP address in `RetrofitClient.kt` matches your PC's current IP.
    * Check **Windows Firewall** on your PC — allow incoming traffic on port `18080` for Private networks.
* **"Cleartext traffic not permitted":**
    * Android blocks unencrypted HTTP by default. Verify that `android:usesCleartextTraffic="true"` is present in your `AndroidManifest.xml` tag.
* **401 Unauthorized:**
    * The `API_KEY` in `MainActivity.kt` does not match the key expected by the C++ server.
