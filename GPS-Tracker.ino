#include "handlers/WiFiController.cpp"
#include "handlers/WiFiController.hpp"

using namespace handlers;

char* ssid = "Nacho";
char* password = "rayandoelsol";
WiFiController* wifi;

void setup() {
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  wifi = new WiFiController();
  wifi->addAccessPoint(ssid, password);
}

void loop() {
  if (wifi->isConnected()) {
    Serial.write("Conectado\n");
    wifi->sendData("Hola");
  } else {
    Serial.write("Conectando...\n");
    wifi->tryToConnect();
  }
  delay(200);
}
