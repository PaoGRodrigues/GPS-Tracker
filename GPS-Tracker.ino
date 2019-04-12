#include "handlers/WiFiController.cpp"
#include "handlers/WiFiController.hpp"
#include "handlers/SDController.cpp"
#include "handlers/SDController.hpp"

using namespace handlers;

char* ssid = "Nacho";
char* password = "rayandoelsol";
WiFiController* wifi;
SDController* sd;

void setup() {
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  wifi = new WiFiController();
  sd = new SDController();
  wifi->addAccessPoint(ssid, password);
  sd->checkStart();
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
