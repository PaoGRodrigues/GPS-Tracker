#pragma once

#include <string>
#include "BLEDevice.h"

namespace handlers
{
using namespace std;

class BTController
{
public:
  BTController(string *ssid, string *password);
  // Espera a ser configurado, timeout: Tiempo en segundos que espera antes de devolver los valores default
  virtual void listenForConfig(unsigned long timeout);

private:
  BLECharacteristic *createCharacteristic(const char *serviceUUID, const char *characteristicUUID, string initialValue, BLECharacteristicCallbacks *handler);

  BLEServer *BLEServer_;
  string *ssid_;
  string *password_;
  bool BLEClientConnected_ = false;
  bool onConfig_ = false;

  BLECharacteristic *onConfigCharacteristic_;
  string onConfigDefaultValue_ = "False";
  const char *const ONCONFIG_SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
  const char *const ONCONFIG_CHARACTERISTIC_UUID = "7fb78cd6-4fa2-4289-8da4-fa4785e90657";

  const char *const SSID_SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914c";
  const char *const SSID_CHARACTERISTIC_UUID = "7fb78cd6-4fa2-4289-8da4-fa4785e90658";

  const char *const PASSWORD_SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914d";
  const char *const PASSWORD_CHARACTERISTIC_UUID = "7fb78cd6-4fa2-4289-8da4-fa4785e90659";

  class OnConfigHandler : public BLECharacteristicCallbacks
  {
  public:
    OnConfigHandler(BTController *BTController);
    void onRead(BLECharacteristic *onConfigCharacteristic);
    void onWrite(BLECharacteristic *onConfigCharacteristic);

  private:
    BTController *BTController_;
  };

  class SSIDHandler : public BLECharacteristicCallbacks
  {
  public:
    SSIDHandler(BTController *BTController);
    void onRead(BLECharacteristic *SSIDCharacteristic);
    void onWrite(BLECharacteristic *SSIDCharacteristic);

  private:
    BTController *BTController_;
  };

  class PasswordHandler : public BLECharacteristicCallbacks
  {
  public:
    PasswordHandler(BTController *BTController);
    void onRead(BLECharacteristic *passwordCharacteristic);
    void onWrite(BLECharacteristic *passwordCharacteristic);

  private:
    BTController *BTController_;
  };
};

} // namespace handlers
