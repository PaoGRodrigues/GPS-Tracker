#include <Arduino.h>
#include "handlers/WiFiController.hpp"
#include "handlers/SDController.hpp"
#include "handlers/GPSController.hpp"
#include "core/Core.hpp"

using namespace handlers;

std::string ssid = "gps_tracker";
std::string password = "rekcart_spg";
WiFiController *wifiController;
core::Core *core_;

void setup()
{
  Serial.begin(115200);
  delay(4000);
  wifiController = new WiFiController();
  wifiController->setAccessPoint(ssid, password);
  //SDController *sdController = new SDController();
  GPSController *gpsController = new GPSController();
  core_ = new core::Core(wifiController, 0, gpsController);
}

void loop()
{
  core_->loop();
  delay(200);
}
