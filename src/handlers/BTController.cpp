#include "Arduino.h"
#include "BTController.hpp"
#include <string>
#include <sstream>
#include <BLEServer.h>

using namespace handlers;
using namespace std;

BTController::BTController(string *ssid, string *password)
{
  ssid_ = ssid;
  password_ = password;
  BLEDevice::init("GPS Tracker Config");
  BLEServer_ = BLEDevice::createServer();
  onConfigCharacteristic_ = createCharacteristic(ONCONFIG_SERVICE_UUID, ONCONFIG_CHARACTERISTIC_UUID, onConfigDefaultValue_, new OnConfigHandler(this));
  createCharacteristic(SSID_SERVICE_UUID, SSID_CHARACTERISTIC_UUID, string(ssid_->c_str()), new SSIDHandler(this));
  createCharacteristic(PASSWORD_SERVICE_UUID, PASSWORD_CHARACTERISTIC_UUID, password_->c_str(), new PasswordHandler(this));
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06);
  advertising->setMinPreferred(0x12);
  advertising->addServiceUUID(ONCONFIG_SERVICE_UUID);
  advertising->addServiceUUID(SSID_SERVICE_UUID);
  advertising->addServiceUUID(PASSWORD_SERVICE_UUID);
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
  Serial.println("FinEspera");
  BLEDevice::deinit(true);
}

BLECharacteristic *BTController::createCharacteristic(const char *serviceUUID, const char *characteristicUUID, string initialValue, BLECharacteristicCallbacks *handler)
{
  BLEService *service = BLEServer_->createService(serviceUUID);
  BLECharacteristic *characteristic = service->createCharacteristic(characteristicUUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  characteristic->setValue(initialValue);
  characteristic->setCallbacks(handler);
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
  Serial.println(onConfigCharacteristic->getValue().c_str());
  bool onConfig = BTController_->onConfigDefaultValue_.compare(onConfigCharacteristic->getValue());
  BTController_->onConfig_ = onConfig;
}

BTController::SSIDHandler::SSIDHandler(BTController *BTController)
{
  BTController_ = BTController;
}

void BTController::SSIDHandler::onRead(BLECharacteristic *SSIDCharacteristic)
{
}

void BTController::SSIDHandler::onWrite(BLECharacteristic *SSIDCharacteristic)
{
  Serial.println(SSIDCharacteristic->getValue().c_str());
  string ssid = SSIDCharacteristic->getValue();
  *(BTController_->ssid_) = ssid;
}

BTController::PasswordHandler::PasswordHandler(BTController *BTController)
{
  BTController_ = BTController;
}

void BTController::PasswordHandler::onRead(BLECharacteristic *passwordCharacteristic)
{
}

void BTController::PasswordHandler::onWrite(BLECharacteristic *passwordCharacteristic)
{
  Serial.println(passwordCharacteristic->getValue().c_str());
  string password = passwordCharacteristic->getValue();
  *(BTController_->password_) = password;
}
