#include <WiFi.h>
#include <WebServer.h>
#include <SD_MMC.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_password";

WebServer server(80); // HTTP server on port 80

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the SD card using SD_MMC
  if (!SD_MMC.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.println("SD card initialized.");

  // Set up routes
  server.on("/", HTTP_GET, handleRoot); // Handle root URL
  server.on("/upload", HTTP_POST, handleUpload); // Handle POST requests to /upload

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32!");
}

void handleUpload() {
  if (server.hasArg("plain")) {
    String plain = server.arg("plain");
    Serial.print("Received data: ");
    Serial.println(plain);

    // Save the received data to the SD card
    saveToSDCard(plain);

    server.send(200, "text/plain", "Data received and saved successfully");
  } else {
    server.send(400, "text/plain", "No data received");
  }
}

void saveToSDCard(String data) {
  File file = SD_MMC.open("/data.gcode", FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(data)) {
    Serial.println("Data saved successfully");
  } else {
    Serial.println("Failed to write data to file");
  }
  file.close();
}
