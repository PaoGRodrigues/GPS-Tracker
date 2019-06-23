#include "Arduino.h"
#include "BTController.hpp"
#include <string>
#include <sstream>
#include <BLEServer.h>

using namespace handlers;
using namespace std;

BTController::BTController(string *ssid, string *password, string *user)
{
  ssid_ = ssid;
  password_ = password;
  user_ = user;
  BLEDevice::init("GPS Tracker Config");
  BLEServer_ = BLEDevice::createServer();
  onConfigCharacteristic_ = createCharacteristic(ONCONFIG_SERVICE_UUID, ONCONFIG_CHARACTERISTIC_UUID, onConfigDefaultValue_);
  onConfigCharacteristic_->setCallbacks(new OnConfigHandler(this));
  ssidCharacteristic_ = createCharacteristic(SSID_SERVICE_UUID, SSID_CHARACTERISTIC_UUID, string(ssid_->c_str()));
  passwordCharacteristic_ = createCharacteristic(PASSWORD_SERVICE_UUID, PASSWORD_CHARACTERISTIC_UUID, password_->c_str());
  userCharacteristic_ = createCharacteristic(USER_SERVICE_UUID, USER_CHARACTERISTIC_UUID, user_->c_str());
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06);
  advertising->setMinPreferred(0x12);
  advertising->addServiceUUID(ONCONFIG_SERVICE_UUID);
  advertising->addServiceUUID(SSID_SERVICE_UUID);
  advertising->addServiceUUID(PASSWORD_SERVICE_UUID);
  advertising->addServiceUUID(USER_SERVICE_UUID);
  BLEDevice::startAdvertising();
}

void BTController::listenForConfig(unsigned long timeout)
{
  unsigned long now = millis();
  unsigned long tiempoLimite = now + timeout * 1000;
  Serial.println("InicioEspera");
  // Espera hasta que se llegue al timeout o se desactive la configuracion, lo que pase despues
  while (millis() < tiempoLimite || onConfig_)
  {
    delay(1000);
  }
  Serial.print("Config:");
  Serial.println(onConfigCharacteristic_->getValue().c_str());
  Serial.print("SSID:");
  *ssid_ = ssidCharacteristic_->getValue();
  Serial.println(ssid_->c_str());
  Serial.print("Password:");
  *password_ = passwordCharacteristic_->getValue();
  Serial.println(password_->c_str());
  Serial.print("User:");
  *user_ = userCharacteristic_->getValue();
  Serial.println(user_->c_str());
  Serial.println("FinEspera");
  BLEDevice::deinit(true);
}

BLECharacteristic *BTController::createCharacteristic(const char *serviceUUID, const char *characteristicUUID, string initialValue)
{
  BLEService *service = BLEServer_->createService(serviceUUID);
  BLECharacteristic *characteristic = service->createCharacteristic(characteristicUUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  characteristic->setValue(initialValue);
  service->start();
  return characteristic;
}

BTController::OnConfigHandler::OnConfigHandler(BTController *BTController)
{
  BTController_ = BTController;
}

void BTController::OnConfigHandler::onRead(BLECharacteristic *onConfigCharacteristic)
{
}

void BTController::OnConfigHandler::onWrite(BLECharacteristic *onConfigCharacteristic)
{
  Serial.print("Config:");
  Serial.println(onConfigCharacteristic->getValue().c_str());
  bool onConfig = BTController_->onConfigDefaultValue_.compare(onConfigCharacteristic->getValue());
  BTController_->onConfig_ = onConfig;
}
