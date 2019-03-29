#include "cliente_wifi.hpp"
#include <WiFi.h>
#include <Arduino.h>

using namespace adaptadores;

WiFiController::WiFiController()
{
    selected_ = 0;
    accessPoints_ = new vector<pair<std::string, std::string>*>();
    timeout_ = 0;
}

void WiFiController::addAccessPoint(std::string ssid, std::string pass){

    pair<std::string, std::string>* aPair = new pair<std::string, std::string>(ssid, pass);
    accessPoints_->push_back(aPair);
}

bool WiFiController::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

bool WiFiController::tryToConnect()
{
    if (this->isConnected())
    {
        return true;
    }

    if (timeout_-- < 0)
    {
        selected_ = (selected_ + 1) % accessPoints_->size();
        WiFi.begin(accessPoints_->[selected_]->first.c_str(), accessPoints_->[selected_]->second.c_str());
        timeout_ = 15;
    }
    return false;
}