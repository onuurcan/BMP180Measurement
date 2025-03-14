#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 //reset pin # (or -1 if sharing Arduino reset pin)

void setup();
void loop();
void handleRoot();
void handleData();

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //create a SSD1306 object
Adafruit_BMP085 bmp; //create a BMP180 object

const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

ESP8266WebServer server(80); //create a server object

int buttonPin = 0; // On board button pin

float temperature = 0.0; //temperature variable
float pressure = 0.0; //pressure variable

void setup() {
    Serial.begin(115200); //initialize serial communication
    Wire.begin(); //initialize I2C communication
    pinMode(buttonPin, INPUT_PULLUP);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //initialize with the I2C addr 0x3C (for the 128x64)
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay(); 
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Starting BMP180 Sensor...");
    display.display();

    if (!bmp.begin()) { //initialize BMP180 sensor
        Serial.println("Could not find a valid BMP180 sensor, check wiring!");
        while (1)
            ;
    }

    WiFi.begin(ssid, password); //connect to WiFi
    while (WiFi.status() != WL_CONNECTED) { //wait for connection
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot); 
    server.on("/data", handleData); 
    server.begin();
}

void loop() {
    temperature = bmp.readTemperature(); //read temperature
    pressure = bmp.readPressure(); //read pressure

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("BMP180 SENSOR");
    display.setCursor(0, 15);
    display.print("Temperature: ");
    display.print(temperature);
    display.println(" C");
    display.print("Pressure: ");
    display.print(pressure / 100.0);
    display.println(" hPa");
    display.setCursor(0, 40);
    display.println("Press the button to");
    display.print("get the IP Address");
    display.display(); //display data

    if (digitalRead(buttonPin) == LOW) {
        Serial.println("Button Pressed");
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.print("IP: ");
        display.println(WiFi.localIP()); //print IP address
        display.display(); //display data
        delay(500);
    }

    server.handleClient(); //handle client requests
    delay(200);
}

void handleRoot() {
  server.send(200, "text/html", "<!DOCTYPE html><html><head><title>ESP32 BMP180</title></head><body><h1>ESP32 BMP180 Data</h1><p>Temperature: <span id='temp'></span> C</p><p>Pressure: <span id='pressure'></span> hPa</p><script>setInterval(function() { fetch('/data').then(response => response.json()).then(data => { document.getElementById('temp').textContent = data.temperature; document.getElementById('pressure').textContent = (data.pressure / 100).toFixed(2); }); }, 1000);</script></body></html>");
}
  
void handleData() {
  JsonDocument doc; //use JsonDocument
  doc["temperature"] = temperature; //add data to JsonDocument
  doc["pressure"] = pressure; //add data to JsonDocument
  String json; //create a string to store the JSON data
  serializeJson(doc, json); //serialize the JSON data
  server.send(200, "application/json", json); //send the JSON data
}
