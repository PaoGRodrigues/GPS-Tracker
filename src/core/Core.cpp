#include "Core.hpp"
#include <Arduino.h>
using namespace core;

Core::Core(WiFiController *wifiController, SDController *sdController, GPSController *gpsController)
{
    wifiController_ = wifiController;
    sdController_ = sdController;
    gpsController_ = gpsController;
    lastCoordinateTransmitted = 0;
    sendingData = false;
}

void Core::loop()
{
    if(sdController_->checkStart()){
        sdController_->readFile("/prueba.txt", 0);
    }  /*if (gpsController_->isUpdated())
    {
        string data = gpsController_->getData();
        sdController_->saveData(data);
    }
    if (wifiController_->isConnected())
    {
        if (!sendingData)
        {
            lastCoordinateTransmitted = wifiController_->getLastCoordinateTransmitted();
            sendingData = true;
        }
        if (sdController_->getNumberOfData() >= lastCoordinateTransmitted)
        {
            string data = sdController_->getData(lastCoordinateTransmitted++);
            wifiController_->sendData(data);
        }
    }
    else
    {
        wifiController_->tryToConnect();
        sendingData = false;
    }*/
}
