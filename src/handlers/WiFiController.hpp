#pragma once

#include <string>
#include <vector>

namespace handlers
{
using namespace std;

class WiFiController
{
public:
  WiFiController();
  // Asigna el ssid y pass para utilizar al conectarse a una red
  virtual void setAccessPoint(string ssid, string pass);
  // Retorna true si esta conectado a una red
  virtual bool isConnected();
  // Inicia la rutina para conectarse a una red
  virtual bool tryToConnect();
  // Envia el string "data" al host asignado
  virtual bool sendData(string data);
  // Obtiene del host la ultima coordenada almacenada
  virtual bool getLastCoordinateTransmitted(unsigned long *lastCoordinateTransmitted);

private:
  int timeout_ = 0;

  string ssid;
  string pass;
  string url_base = "http://192.168.43.1:8080/tracker/";
  string url_get;
  string url_post;
};

} // namespace handlers
