#include <Arduino.h>
#include "handlers/WiFiController.hpp"
#include "handlers/SDController.hpp"
#include "handlers/GPSController.hpp"
#include "core/Core.hpp"

using namespace handlers;

std::string ssid = "Nacho";
std::string password = "rayandoelsol";
WiFiController *wifiController;
core::Core* core_;

void setup()
{
  Serial.begin(115200);
  delay(4000); //Delay needed before calling the WiFi.begin
  wifiController = new WiFiController();
  wifiController->addAccessPoint(ssid, password);
  SDController* sdController = new SDController();
  GPSController* gpsController = new GPSController();
  core_ = new core::Core(wifiController, sdController, gpsController);
}

void loop()
{
  //if (wifiController->isConnected())
  //{
  //  Serial.write("Conectado\n");
  //  wifiController->sendData("Hola");
  //}
  //else
  //{
  //  Serial.write("Conectando...\n");
  //  wifiController->tryToConnect();
  //}
  core_->loop();
  delay(200);
}
