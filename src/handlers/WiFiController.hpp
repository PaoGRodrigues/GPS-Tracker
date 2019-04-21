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
  virtual void addAccessPoint(string ssid, string pass);
  // Retorna true si esta conectado a una red
  virtual bool isConnected();
  // Inicia la rutina para conectarse a una red
  virtual bool tryToConnect();
  // Envia el string "data" al host asignado
  virtual void sendData(string data);
  // Obtiene del host la ultima coordenada almacenada
  virtual unsigned long getLastCoordinateTransmitted();

private:
  vector<pair<string, string> *> *accessPoints_;
  int timeout_;
  int selected_;
};

} // namespace handlers
