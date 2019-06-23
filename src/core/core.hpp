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
  Core(WiFiController *wifiController, SDController *sdController, GPSController *gpsController, string *user);
  virtual void loop();
  virtual unsigned char *formatGps(const unsigned char *rawInput);

private:
  WiFiController *wifiController_;
  SDController *sdController_;
  GPSController *gpsController_;
  string *user_;
  unsigned long lastCoordinateTransmitted;
  bool sendingData;
};

} // namespace core
