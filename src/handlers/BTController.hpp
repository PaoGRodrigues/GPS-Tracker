#pragma once

#include <string>
#include "BLEDevice.h"

namespace handlers
{
using namespace std;

class BTController : public BLEServerCallbacks
{
public:
  BTController();
  // Recibe el nombre del BT
  virtual void setup(char *nombre);
  // Lee la data enviada por el device
  virtual string readData();
  virtual void onConnect(BLEServer *pServer);
  virtual void onDisconnect(BLEServer *pServer);

private:
  BLEDevice *ESP_BT;
  bool _BLEClientConnected = false;
  char *SERVICE_UUID;
  BLECharacteristic *pCharacteristic;
};

} // namespace handlers
