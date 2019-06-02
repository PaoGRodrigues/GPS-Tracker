#pragma once

#include <string>
#include "BLEDevice.h"

namespace handlers
{
using namespace std;

class BTController : public BLEServerCallbacks
{
public:
  BTController(string *ssid, string *password);
  // Espera a ser configurado, timeout: Tiempo en segundos que espera antes de devolver los valores default
  virtual void listenForConfig(unsigned long timeout);
  // Callbacks del BLEServer
  virtual void onConnect(BLEServer *pServer);
  virtual void onDisconnect(BLEServer *pServer);

private:
  string readData();

  BLEDevice *BLEDevice_;
  BLECharacteristic *readCharacteristic_;
  BLECharacteristic *writeCharacteristic_;

  bool BLEClientConnected_ = false;
  string *ssid_;
  string *password_;
};

} // namespace handlers
