#include <EIoTCloudRestApi.h>
#include <EIoTCloudRestApiConfig.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

const char* ssid = "jeinternet";
const char* pass = "supergeheim";
WiFiClient client;

// IoT
EIoTCloudRestApi eiotcloud;
const char* parameter1 = "5707983bc943a022c0d2c42b/j5rDe1IhOEODiQaG";
const char* parameter2 = "5707983bc943a022c0d2c42b/FNuCL2fjdscKSz5y";

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

  Serial.print("ldrValue: ");
  Serial.println(ldrValue);

  Serial.print("pirValue: ");
  Serial.println(pirValue);

  ThingSpeak.writeField(channel, 1, ldrValue, api_key);
  ThingSpeak.writeField(channel, 2, pirValue, api_key);
  eiotcloud.sendParameter(parameter1, pirValue);
  eiotcloud.sendParameter(parameter2, ldrValue);
  
  delay(1);
}

