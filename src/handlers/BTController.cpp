#include "Arduino.h"
#include "BTController.hpp"
#include <string>
#include <sstream>
#include <BLEServer.h>

using namespace handlers;
using namespace std;

#define READ_SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define READ_CHARACTERISTIC_UUID "7fb78cd6-4fa2-4289-8da4-fa4785e90658"
#define WRITE_SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914c"
#define WRITE_CHARACTERISTIC_UUID "7fb78cd6-4fa2-4289-8da4-fa4785e90659"

BTController::BTController(string *ssid, string *password)
{
  BLEDevice::init("BLE Server");
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *readService = pServer->createService(READ_SERVICE_UUID);
  readCharacteristic_ = readService->createCharacteristic(READ_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);
  BLEService *writeService = pServer->createService(WRITE_SERVICE_UUID);
  writeCharacteristic_ = writeService->createCharacteristic(WRITE_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_WRITE);
  pServer->setCallbacks(this);
  readService->start();
  writeService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(READ_SERVICE_UUID);
  pAdvertising->addServiceUUID(WRITE_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void BTController::onConnect(BLEServer *pServer)
{
  Serial.println("Alguien se conecto");
  BLEClientConnected_ = true;
};

void BTController::onDisconnect(BLEServer *pServer)
{
  Serial.println("Alguien se desconecto");
  BLEClientConnected_ = false;
}

void BTController::listenForConfig(unsigned long timeout)
{
  unsigned long now = millis();
  unsigned long tiempoLimite = now + timeout * 1000;
  Serial.println("InicioEspera");
  while (millis() < tiempoLimite)
  {
  }
  Serial.println("FinEspera");
}

string BTController::readData()
{
  if (BLEClientConnected_)
  {
    string value = writeCharacteristic_->getValue();
    Serial.println(value.c_str());
    readCharacteristic_->setValue(value);
  }
  return "";
}
