#include "GPSController.hpp"
#include "HardwareSerial.h"
#include <sstream>
#define RXD2 16
#define TXD2 17

using namespace handlers;
using namespace std;

GPSController::GPSController()
{
}

bool GPSController::isUpdated()
{
    return false;
}

string crearJson(string GPSString)
{
    DynamicJsonDocument json(1024);

// Documentacion: https://www.winsystems.com/wp-content/uploads/software/nmea.pdf
    // Ejemplo
    // $GPGGA,012010.813,5231.067,N,01323.931,E,1,12,1.0,0.0,M,0.0,M,,*6A\r\n,
    // !LOS VALORES DECIMALES DESPUES DEL PUNTO SON OPCIONALES, VALIDAR CON NUESTRO GPS!
    // Dato, Posicion, longitud
    // Fecha, 7, 10
    // Latitud, 18, 8
    // Norte-Sur, 27, 1
    // Longitud, 29, 9
    // Este-Oeste, 39, 1
    // LongitudTotal 29

    std::replace(GPSString.begin(), GPSString.end(), ':', ' ');  // replace ':' by ' '

    vector<string> array;
    std::stringstream ss(GPSString);
    string temp;

    string keys[16] = {"$GPGGA", "horario", "latitud", "latitudhemisferio", "longitud", "longitudhemisferio",
        "indicadorcalidad", "satelites", "HDOP", "alturaantena", "MetersM", "separacion", "MetersM2",
        "diferenciahoraria", "diferenciaestacion", "checksum"};

    int i = 0;
    while (ss >> temp)
        json[i] = temp;
        i++;

    //falta convertir el json a string
    return json;
}

string GPSController::getData()
{
    //For Holding the GPS Serial Data
    char buffer[256];
    int count = 0;
    
    HardwareSerial gps_serial(2);

    gps_serial.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial.begin(115200);
    
    while (gps_serial.available()) {
        buffer[count++] = gps_serial.read();
        if (count == 256) {
        break;
        }
    }

    string stringBuffer = (const char*)buffer;

    string json = crearJson(stringBuffer);

    return json;
}
