#include "WiFiController.hpp"
#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>

using namespace handlers;
using namespace std;

WiFiController::WiFiController()
{
    selected_ = 0;
    accessPoints_ = new vector<pair<string, string> *>();
    timeout_ = 0;
}

void WiFiController::addAccessPoint(string ssid, string pass)
{

    pair<string, string> *aPair = new pair<string, string>(ssid, pass);
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
        WiFi.begin((*accessPoints_)[selected_]->first.c_str(), (*accessPoints_)[selected_]->second.c_str());
        timeout_ = 15;
    }
    return false;
}

void WiFiController::sendData(string data)
{
    HTTPClient http;
    http.begin("http://192.168.43.1:8080/");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
        String payload = http.getString();
        const char *payloadComoChar = payload.c_str();
        Serial.println(httpCode);
        Serial.println(payload);

        Serial.println(payloadComoChar);
    }
    else
    {
        Serial.println("Error on HTTP request");
    }

    http.end();
}
