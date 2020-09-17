#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Broken";
const char* password = "happy168";
const char* baseURL = "http://arduinowebservergcs0702.xyz/";

#define unoSignalPin D1

void setup() {
  Serial.begin(115200);
  pinMode(unoSignalPin, INPUT);

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (digitalRead(unoSignalPin) == 1) informServer();
  delay(500);
}

void informServer() {
  Serial.println("\n\n");
  Serial.print("Connecting to ");
  Serial.println(String(baseURL) + "?count=true");

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  HTTPClient http;

  // Send GET request to /
  if (http.begin(client, String(baseURL) + "?count=true")) {  // HTTP
    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) Serial.println("Dispensed times of user has been incremented successfully!");
    } else Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());

    http.end();
  } else Serial.printf("[HTTP} Unable to connect\n");
}
