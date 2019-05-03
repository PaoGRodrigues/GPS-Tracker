#include "Core.hpp"
#include <Arduino.h>
#include <string>
#include <sstream>
using namespace core;

Core::Core(WiFiController *wifiController, SDController *sdController, GPSController *gpsController)
{
    wifiController_ = wifiController;
    sdController_ = sdController;
    gpsController_ = gpsController;
    lastCoordinateTransmitted = 0;
    sendingData = false;
}

unsigned long a = 0;

void Core::loop()
{

    
    if(sdController_->checkStart()){
        stringstream strs;
        strs << a;
        sdController_->appendFile(strs.str().c_str());
        sdController_->readFile(a);
        a++;
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
