Smart Home Android Client
This application acts as a remote control for your smart home system. It's a native Android app written in Kotlin that communicates with your C++ backend server via standard HTTP requests.

 Key Technologies
Kotlin: Modern programming language for Android development.

Retrofit 2: A type-safe HTTP client for Android that simplifies sending network requests and parsing JSON responses into Kotlin objects.

Kotlin Coroutines: Used for managing background threads to perform network operations asynchronously without freezing the main UI thread.

 Setup Before Running
Since the app communicates with a local server on your Wi-Fi network, you need to configure it before building.

Server IP Address: Open app/src/main/java/com/example/smarthomeapp/RetrofitClient.kt. Find the BASE_URL constant and replace it with the local IP address of the PC running your C++ server:

private const val BASE_URL = "http://192.168.X.X:18080/"
API Key: Open MainActivity.kt. Ensure the API_KEY variable matches the one configured in your C++ server:

private val API_KEY = "my-secret-key-12345"
 How It Works (Architecture)
The app follows a simple client-server model:

UI Layer: The user interface is defined in activity_main.xml.

Business Logic (MainActivity): Handles user interactions (button clicks) and initiates network requests.

Network Layer (Retrofit): Sends GET or POST requests to the defined server endpoints. It automatically includes the secure X-API-Key header in every request.

Data Handling: Receives JSON responses from the server, deserializes them into data objects, and updates the UI with the new device status.
 Troubleshooting Common Issues
"Network Error": Ensure both your phone and PC are connected to the same Wi-Fi network, and the IP address in RetrofitClient.kt is correct. Also, check your Windows Firewall settings on the PC.

"Cleartext traffic not permitted": Android blocks unencrypted HTTP traffic by default. Verify that android:usesCleartextTraffic="true" is present in your AndroidManifest.xml file.
