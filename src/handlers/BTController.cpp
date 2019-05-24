#include "Arduino.h"
#include "BTController.hpp"
#include <string>
#include <sstream>
#include <BLEServer.h>

using namespace handlers;
using namespace std;

BTController::BTController(){

    BLEDevice::init("BLE Server");
    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
                                     "7fb78cd6-4fa2-4289-8da4-fa4785e90659",
                                     BLECharacteristic::PROPERTY_READ |
                                     BLECharacteristic::PROPERTY_WRITE
                                     );
    pCharacteristic->setValue("Hello!!");
    pServer->setCallbacks(this);
}


void BTController::onConnect(BLEServer* pServer) {
    _BLEClientConnected = true;
    };

void BTController::onDisconnect(BLEServer* pServer) {
    _BLEClientConnected = false;
}

void BTController::setup(char *nombre){

  Serial.begin(9600); //Inicio del Serial monitor en 9600
  Serial.println("Bluetooth Device is Ready to Pair");
}

string BTController::readData(){

  // stringstream input;
  // while () //Corrobora si está activo
  // {
  //    input << ESP_BT->read(); //Lee lo que está recibiendo
  //   Serial.print("Received:"); 
  //   Serial.println(input.str().c_str());
  // }
}