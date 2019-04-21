#pragma once

#include "../handlers/WiFiController.hpp"
#include "../handlers/SDController.hpp"
#include "../handlers/GPSController.hpp"

namespace core
{
using namespace handlers;

class Core
{
public:
  Core(WiFiController *wifiController, SDController *sdController, GPSController *gpsController);
  virtual void loop();

private:
  WiFiController *wifiController_;
  SDController *sdController_;
  GPSController *gpsController_;
};

} // namespace core
