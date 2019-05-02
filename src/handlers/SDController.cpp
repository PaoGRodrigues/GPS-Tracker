/*
* Connect the SD card to the following pins:
*
* SD Card | ESP32
* CS D5
* MOSI D23
* 3.3V 3.3V
* CLK D18
* GND GND
* MISO D19
*/

#include "Arduino.h"
#include "SDController.hpp"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <string>

using namespace handlers;
using namespace std;

SDController::SDController(){}

bool SDController::checkStart()
{
    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return false;
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return false;
    }
    return true;
}

void SDController::readFile(const char *path, int dataNumber)
{
    Serial.printf("Reading file: %s\n", path);

    File file = SD.open(path);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    // dataNumber es el número de registro de dato que quiero leer desde 0.
    int position = dataNumber * dataSize;
    int finalPosition = position + dataSize;
    char *value = new char[dataSize+1];
    file.seek(position);
    while (file.available() && position < finalPosition)
    {
        value[position] = file.read();
        position++;
    }
    value[position] = '\0';
    Serial.println(value);
}

void SDController::writeFile(const char *path, const char *message)
{
    Serial.printf("Writing file: %s\n", path);

    File file = SD.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        Serial.println("File written");
    }
    else
    {
        Serial.println("Write failed");
    }
}

void SDController::appendFile(const char *path, const char *message)
{
    Serial.printf("Appending to file: %s\n", path);

    File file = SD.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message))
    {
        Serial.println("Message appended");
    }
    else
    {
        Serial.println("Append failed");
    }
}

void SDController::deleteFile(const char *path)
{
    Serial.printf("Deleting file: %s\n", path);
    if (SD.remove(path))
    {
        Serial.println("File deleted");
    }
    else
    {
        Serial.println("Delete failed");
    }
}

void SDController::saveData(string data)
{
}

string SDController::getData(unsigned long position)
{
    return "";
}

unsigned long SDController::getNumberOfData()
{
    return 0;
}
