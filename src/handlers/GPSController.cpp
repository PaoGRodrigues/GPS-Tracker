#include "GPSController.hpp"
#include "HardwareSerial.h"
#include "string"
#include "sstream"

using namespace handlers;
using namespace std;

HardwareSerial gps_serial(2);

GPSController::GPSController()
{
    lastMessage = "";
    gps_serial.begin(9600);
}

string GPSController::createJson(string GPSString, int frameNumber)
{
    // Documentacion: https://www.winsystems.com/wp-content/uploads/software/nmea.pdf
    // Ejemplo: $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A

    int indexes[12];
    indexes[0] = 0;
    for (int i = 0; i < 11; i++)
    {
        indexes[i + 1] = GPSString.find(",", indexes[i]) + 1;
    }

    stringstream value;
    value << "{\"TrackNumber\":" << frameNumber
          << ",\"Time\":\"" << GPSString.substr(indexes[1], indexes[2] - indexes[1] - 1)
          << "\",\"Status\":\"" << GPSString.substr(indexes[2], indexes[3] - indexes[2] - 1);

    const char *latitudeString = GPSString.substr(indexes[3], indexes[4] - indexes[3] - 1).c_str();
    const char *latitudeHemisphere = GPSString.substr(indexes[4], indexes[5] - indexes[4] - 1).c_str();
    float latitude = atof(latitudeString) / 100;
    int intLat = static_cast<int>(latitude);
    float floatLat = ((latitude - intLat) / 60) * 100;
    latitude = (intLat + floatLat);
    if (strcmp(latitudeHemisphere, "N"))
    {
        latitude = -latitude;
    }
    value << "\",\"Latitude\":\"" << latitude << "\",\"LatitudeHemisphere\":\"" << latitudeHemisphere;

    const char *longitudeString = GPSString.substr(indexes[5], indexes[6] - indexes[5] - 1).c_str();
    const char *longitudeHemisphere = GPSString.substr(indexes[6], indexes[7] - indexes[6] - 1).c_str();
    float longitude = atof(longitudeString) / 100;
    int intLon = static_cast<int>(longitude);
    float floatLon = ((longitude - intLon) / 60) * 100;
    longitude = (intLon + floatLon);
    if (strcmp(longitudeHemisphere, "E"))
    {
        longitude = -longitude;
    }
    value << "\",\"Longitude\":\"" << longitude << "\",\"LongitudeHemisphere\":\"" << longitudeHemisphere;

    value << "\",\"EarthVelocity\":\"" << GPSString.substr(indexes[7], indexes[8] - indexes[7] - 1)
          << "\",\"Track\":\"" << GPSString.substr(indexes[8], indexes[9] - indexes[8] - 1)
          << "\",\"Date\":\"" << GPSString.substr(indexes[9], indexes[10] - indexes[9] - 1)
          << "\",\"MagneticVariation\":\"" << GPSString.substr(indexes[10], indexes[11] - indexes[10] - 1);

    value << "\",\"DirectionVariation\":\"" << GPSString.substr(indexes[11], 1);
    value << "\",\"SystemPosition\":\"\",\"Checksum\":\"" << GPSString.substr(indexes[11] + 1, 3) << "\"}";
    Serial.println(value.str().c_str());
    return value.str().c_str();
}

bool GPSController::getData(string *data, int frameNumber)
{
    bool newData = false;

    if (gps_serial.available())
    {
        string readed = gps_serial.readStringUntil('\r').c_str();
        gps_serial.read();
        newData = readed.compare(lastMessage) != 0 && validarTrama(readed);
        if (newData)
        {
            lastMessage = readed;
            *data = createJson(readed, frameNumber);
        }
    }
    return newData;
}

bool GPSController::validarTrama(string data)
{
    char messageType[] = "$GPRMC";
    bool valido = memcmp(messageType, data.c_str(), sizeof(messageType) - 1) == 0;
    if (valido)
    {
        Serial.println(data.c_str());
        int pos = data.find(",", 0) + 1;
        pos = data.find(",", pos) + 1;
        char status = data.at(pos);
        Serial.print("Status: ");
        Serial.println(status);
        valido = status == 'A';
    }
    return valido;
}
