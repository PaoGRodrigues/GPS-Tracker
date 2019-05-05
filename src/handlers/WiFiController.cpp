#include "WiFiController.hpp"
#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>

using namespace handlers;
using namespace std;

WiFiController::WiFiController()
{
    url_get = url_base + "last";
    url_post = url_base + "new-items";
}

void WiFiController::setAccessPoint(string ssid, string pass)
{
    this->ssid = ssid;
    this->pass = pass;
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
        WiFi.begin(ssid.c_str(), pass.c_str());
        timeout_ = 15;
    }
    return false;
}

bool WiFiController::getLastCoordinateTransmitted(unsigned long *lastCoordinateTransmitted)
{
    HTTPClient http;
    Serial.print("GET:");
    Serial.println(url_get.c_str());
    http.begin(url_get.c_str());
    int httpCode = http.GET();

    Serial.print("httpCode:");
    Serial.println(httpCode);
    if (httpCode == 200)
    {
        String payload = http.getString();
        const char *payloadComoChar = payload.c_str();
        Serial.println("Payload:");
        Serial.println(payload);

        Serial.println(payloadComoChar);

        (*lastCoordinateTransmitted) = 0; //OBTENER DEL PAYLOAD
    }
    else
    {
        Serial.println("Error on HTTP request");
    }

    http.end();
    return httpCode == 200;
}

bool WiFiController::sendData(string data)
{
    HTTPClient http;
    Serial.print("POST:");
    Serial.println(url_post.c_str());
    http.begin(url_post.c_str());
    int httpCode = http.POST(data.c_str());

    Serial.print("httpCode:");
    Serial.println(httpCode);
    if (httpCode == 200)
    {
        String payload = http.getString();
        const char *payloadComoChar = payload.c_str();
        Serial.println("Payload:");
        Serial.println(payload);

        Serial.println(payloadComoChar);
    }
    else
    {
        Serial.println("Error on HTTP request");
    }

    http.end();
    return httpCode == 200;
}
