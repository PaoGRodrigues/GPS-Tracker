#include <Arduino.h>
#include "handlers/WiFiController.hpp"
#include "handlers/SDController.hpp"
#include "handlers/GPSController.hpp"
#include "core/Core.hpp"

using namespace handlers;
using namespace core;

std::string ssid = "Nacho";
std::string password = "rayandoelsol";
WiFiController *wifiController;
Core* core;

void setup()
{
  Serial.begin(115200);
  delay(4000); //Delay needed before calling the WiFi.begin
  wifiController = new WiFiController();
  wifiController->addAccessPoint(ssid, password);
  SDController* sdController = new SDController();
  GPSController* gpsController = new GPSController();
  Core* core = new Core(wifiController, sdController, gpsController);
}

void loop()
{
  if (wifiController->isConnected())
  {
    Serial.write("Conectado\n");
    wifiController->sendData("Hola");
  }
  else
  {
    Serial.write("Conectando...\n");
    wifiController->tryToConnect();
  }
  delay(200);
}
