# ESP-Wireless-SD-Card
This is a piece of code on the arduino IDE that makes your ESP act like a wireless SD card
Postman Download: https://www.postman.com/downloads/

#Instructions
First, download an app named postman, this is how you'll send data to the ESP
Download Arduino IDE, Select your board and before you upload the project on the line: 6 and 7 replace the "yourSSID" and "password" with your internet name and password.
Now, in postman, create a new http ![image](https://github.com/RLkoi/ESP-Wireless-SD-Card/assets/78034237/abfd663d-6cd3-4714-8cac-26d169184b5e) and then click HTTP
After this, you should be on a page like this: ![image](https://github.com/RLkoi/ESP-Wireless-SD-Card/assets/78034237/8438ac0f-0433-43b2-ae3e-2067cf8d9afe)
 Click on Get and select Post, this changes the mode so that you will post a file onto the esp
 Then, in the link box, type: http://<espIpadress>/upload, replace the <espIPadress> with its IP, heres a piece of code that prints your ESP's IP into the serial monitor:

 
 #include <WiFi.h>

// Replace with your network credentials


const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");

  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Empty loop
}

PS: if you want to upload files to it, on postman, go to raw and it lets you select a file
