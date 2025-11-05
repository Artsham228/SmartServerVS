Smart Home Android Client
This is the native Android client for the custom smart home system. It acts as a remote control, communicating with the C++ backend server via a secured REST API to manage IoT devices in real-time.

1. Architecture
The application follows a clean client-server architecture:

UI Layer: XML layouts define the user interface, providing intuitive controls for each device type (LightBulb, Door, Conditioner).

Business Logic Layer: The MainActivity handles user interactions and manages the application lifecycle.

Network Layer: Powered by Retrofit 2, this layer handles all HTTP communication. It automatically serializes JSON data and injects the required security tokens into every request.

2. Features
Real-time Control: Instantly toggle lights, lock/unlock doors, and adjust air conditioner temperature.

Live Status Updates: The app fetches and displays the current state of all devices directly from the server.

Secure Communication: All API requests are authenticated using a custom X-API-Key header.

Robust Error Handling: Provides clear feedback to the user in case of network issues or server errors.

3. Tech Stack
Kotlin: The primary programming language, ensuring modern and type-safe code.

Retrofit 2: A type-safe HTTP client for seamless API integration.

Kotlin Coroutines: Used for efficient, non-blocking asynchronous network operations.

GSON: For reliable JSON serialization and deserialization.

4. Setup & Configuration
Before building the project, you must configure it to match your local network environment.

Server IP Configuration
Open RetrofitClient.kt and update the BASE_URL with your C++ server's local IP address:

Kotlin

// Replace with your actual server IP
private const val BASE_URL = "http://192.168.0.104:18080/"
Security Configuration
Open MainActivity.kt and ensure the API_KEY matches the one configured on your backend:

Kotlin

private val API_KEY = "my-secret-key-12345"
Note: Ensure your Android device is connected to the same Wi-Fi network as your server.
