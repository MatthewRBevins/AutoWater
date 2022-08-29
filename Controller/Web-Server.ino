#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "USERNAME"
#define STAPSK  "PASSWORD"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // prepare output pin
  pinMode(D7, OUTPUT);
  digitalWrite(D7, 0);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("new client"));

  client.setTimeout(5000);

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

  // Match the request
  int val;
  if (req.indexOf(F("/gpio/0")) != -1) {
    val = 0;
  } else if (req.indexOf(F("/gpio/1")) != -1) {
    val = 1;
  } else {
    Serial.println(F("invalid request"));
    val = digitalRead(D7);
  }

  // Set output pin
  digitalWrite(D7, val)
  
  while (client.available()) {
    client.read();
  }

  // Send the response to the client
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nAccess-Control-Allow-Origin:*\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n"));
  client.print(val);
  client.print(F("<script>let get = window.location.href.split('=')[1]; if(get) { window.location.href = 'http://10.0.0.186/gpio/' + get; }</script></body></html>"));

  Serial.println(F("Disconnecting from client"));
}
