# ESP8266 BMP180 Sensor with Web Server and OLED Display

This project demonstrates how to use an ESP8266 ESP-12F to read temperature and pressure data from a BMP180 sensor, display it on an OLED screen, and provide it via a web server with JSON data.

## Project Overview

The ESP8266 reads temperature and pressure data from a BMP180 sensor. This data is displayed on an OLED screen and also made available through a web server. The web server provides the data in JSON format, which can be dynamically updated on a web page using JavaScript. A button press on the ESP8266 will display the device's IP address on the OLED screen.

**Key Features:**

* **Sensor Data Display:** Reads temperature and pressure from a BMP180 sensor and displays them on an OLED screen.
* **Web Server:** Provides sensor data via HTTP, allowing access from web browsers or other applications.
* **JSON Data:** Serves sensor data in JSON format for easy parsing.
* **OLED Display:** Shows sensor readings and, upon button press, the ESP8266's IP address.
* **Button Input:** Displays the IP address on the OLED when the onboard button is pressed.
* **Wi-Fi Connectivity:** Connects to a Wi-Fi network to enable web server access.

## Hardware Components

* ESP8266 ESP-12F Development Board
* BMP180 Barometric Pressure and Temperature Sensor
* OLED Display (128x64 pixels, I2C)
* Push Button (onboard GPIO0)

**Connections:**

* **BMP180:**
    * VCC to 3.3V
    * GND to GND
    * SDA to D1 (GPIO 5)
    * SCL to D2 (GPIO 4)
* **OLED Display:**
    * VCC to 3.3V
    * GND to GND
    * SDA to D1 (GPIO 5)
    * SCL to D2 (GPIO 4)
* **Push Button:**
    * One pin to GND
    * The other pin to D3 (GPIO 0)

## Software Requirements

* **Arduino IDE or PlatformIO (VS Code):** Development environment.
* **Libraries:**
    * `Adafruit BMP085 Library`
    * `Adafruit GFX Library`
    * `Adafruit SSD1306`
    * `ArduinoJson`

## Installation and Setup

1.  **Install Arduino IDE or PlatformIO:**
    * If using Arduino IDE, install the ESP8266 board support:
        * Go to "File" > "Preferences" and add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` to "Additional Boards Manager URLs."
        * Go to "Tools" > "Board" > "Boards Manager" and install "esp8266 by ESP8266 Community."
    * If using PlatformIO (recommended), install the PlatformIO IDE extension in VS Code.
2.  **Install Libraries:**
    * **Arduino IDE:** Use the Library Manager ("Sketch" > "Include Library" > "Manage Libraries...") to install the required libraries.
    * **PlatformIO:** Add the library dependencies to your `platformio.ini` file:

        ```ini
        [env:esp12e]
        platform = espressif8266
        board = esp12e
        framework = arduino
        monitor_speed = 115200
        lib_deps =
            adafruit/Adafruit BMP085 Library@^1.2.1
            adafruit/Adafruit GFX Library@^1.11.7
            adafruit/Adafruit SSD1306@^2.5.7
            bblanchon/ArduinoJson@^6.21.3
        ```

3.  **Clone or Download the Project:**
    * Clone this repository or download the ZIP file and extract it.
4.  **Open the Project:**
    * **Arduino IDE:** Open the `main.cpp` file.
    * **PlatformIO:** Open the project in VS Code.
5.  **Configure Wi-Fi Settings:**
    * In `main.cpp`, update the following lines with your Wi-Fi credentials:

        ```cpp
        const char *ssid = "YOUR_WIFI_SSID";
        const char *password = "YOUR_WIFI_PASSWORD";
        ```

6.  **Upload the Code:**
    * **Arduino IDE:** Select the correct board and port, and click "Upload."
    * **PlatformIO:** Click the "Upload" button in VS Code.
7.  **Open Serial Monitor:**
    * Open the serial monitor to view the ESP8266's IP address and debug messages.

![72964169-F555-43D7-9FED-08338D76F340](https://github.com/user-attachments/assets/96adb68f-32a9-45a2-b670-37f31d524bfa)

![Screenshot 2025-03-18 072457](https://github.com/user-attachments/assets/08f5867c-f496-4e2a-8b2c-1d8145b65874)


## Code Explanation

* **Libraries:** Includes necessary libraries for sensor, OLED, Wi-Fi, and web server functionality.
* **Sensor and OLED Initialization:** Sets up the BMP180 sensor and OLED display.
* **Wi-Fi Connection:** Connects to the specified Wi-Fi network.
* **Web Server Setup:** Initializes the web server and defines endpoints for `/` (HTML page) and `/data` (JSON data).
* **Sensor Readings and OLED Display:** Reads sensor data and displays it on the OLED.
* **Button Handling:** Displays the IP address on the OLED when the button is pressed.
* **JSON Handling:** Formats sensor data as JSON and serves it via the `/data` endpoint.
* **HTML Page:** The `/` endpoint serves a basic HTML page that uses JavaScript to dynamically update sensor data from the `/data` endpoint.

## Usage

1.  Connect the hardware components as described.
2.  Upload the code to your ESP8266.
3.  Open the serial monitor to get the ESP8266's IP address.
4.  Open a web browser and navigate to the ESP8266's IP address to view the sensor data.
5.  Press the onboard button to display the IP address on the OLED.

## Future Enhancements

* Add more robust error handling for Wi-Fi and sensor communication.
* Improve the web page's design and functionality.
* Implement more advanced data visualization on the web page.
* Add configuration options via a web interface.
* Add more sensors.

## Contributing

Contributions are welcome! Feel free to submit pull requests or open issues to suggest improvements.

## License

This project is licensed under the MIT License.
