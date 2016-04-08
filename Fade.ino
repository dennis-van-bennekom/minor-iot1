#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

const char* ssid = "jeinternet";
const char* pass = "supergeheim";
WiFiClient client;

// IoT
EIoTCloudRestApi eiotcloud;
const char* parameter = "5707983bc943a022c0d2c42b/j5rDe1IhOEODiQaG";

// ThingSpeak
unsigned long channel = 106886;
const char* api_key = "YAANEN39DKRFCW56";

const int ldr = A0;
int ldrValue = 0;

const int pir = D5;
int pirValue = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting connection...");
  
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting connection...");
  
    delay(500);
  }

  Serial.println("Connected!");

  eiotcloud.begin();
  ThingSpeak.begin(client);
}

void loop() {
  ldrValue = analogRead(ldr);
  pirValue = digitalRead(pir);

  ThingSpeak.writeField(channel, 1, ldrValue, api_key);
  eiotcloud.sendParameter(parameter, pirValue);
  
  delay(500);
}

