#pragma once

#include <string>
#include <ArduinoJson.h>
#include <TinyGPS++.h>


namespace handlers
{
using namespace std;

class GPSController
{
  public:
    GPSController();
    // Retorna true si la informacion que contiene no fue leida por getData
    virtual bool isUpdated();
    // Retorna la informacion almacenada
    virtual string getData();
    // Convierte un dato de GPS en un string Json
    virtual string createJson(string GPSString);
};
 // namespace handlers
}