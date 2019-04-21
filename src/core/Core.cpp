#include "Core.hpp"

using namespace core;

Core::Core(WiFiController *wifiController, SDController *sdController, GPSController *gpsController)
{
    wifiController_ = wifiController;
    sdController_ = sdController;
    gpsController_ = gpsController;
}

void Core::loop()
{
}
