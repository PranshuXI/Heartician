#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char *ssid = "OPPO F11 Pro";
const char *password = "Khaitan@1234";

WiFiClient client;

const char *serverAddress = "http:/192.168.99.12:5000/post";


const int analogPin = A0;


const int normalThreshold = 600; 
const int lvhThreshold = 900;    

void setup() {
  Serial.begin(115200);

  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  
  int ecgValue = analogRead(analogPin);

  
  //int classification = classifyECG(ecgValue);
  int classification = 1;

  String dummyData = "0,0,230," + String(classification) + ",0,120,0,156";
  
  HTTPClient http;

  
  http.begin(client, serverAddress);


  
  int httpResponseCode = http.POST(dummyData);

  
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("HTTP Request failed. Error code: ");
    Serial.println(httpResponseCode);
  }

  // 0,0,230,ecg,0,120,0,156
  http.end();

  
  delay(20000);
}

int classifyECG(int ecgValue) {
  if (ecgValue < normalThreshold) {
    return 0; 
  } else if (ecgValue < lvhThreshold) {
    return 1; 
  } else {
    return 2; 
  }
}
