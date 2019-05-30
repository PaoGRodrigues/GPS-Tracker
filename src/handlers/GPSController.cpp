#include "GPSController.hpp"
#include "HardwareSerial.h"
#include <sstream>
using namespace handlers;
using namespace std;

// int THE_WALL = 0;

HardwareSerial gps_serial(2);

GPSController::GPSController()
{
    lastMessage = "";
    gps_serial.begin(9600);
}

bool GPSController::isUpdated()
{
    return false;
}

string GPSController::createJson(string GPSString)
{
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

    string keys[16] = {"{\"$GPRMC\":\"", "\",\"horario\":\"", "\",\"estado\":\"", "\",\"latitud\":\"", "\",\"latitudhemisferio\":\"", "\",\"longitud\":\"",
        "\",\"longitudhemisferio\":\"", "\",\"velocidadtierra\":\"", "\",\"track\":\"", "\",\"diacalendario\":\"", "\",\"variacionmagnetica\":\"", "\",\"variaciondireccion\":\"", 
        "\",\"posicionsistema\":\"","\",\"checksum\":\""};
    String gpsString = GPSString.c_str();
    int from = 0;
    String value = "";
    int pos = 0;
    String temp = "";

    while(from != -1) {
        int to = gpsString.indexOf(",", from);
        if (to != -1){
            value = gpsString.substring(from, to);
            to+=1;
        } else {
            value = gpsString.substring(from);
        }
        String key = keys[pos].c_str();
        pos++;
        temp += key+value;
        from = to;
    }
    temp += "\"}";
    return temp.c_str();
}

bool GPSController::getData(string* data)
{
    char buffer[256];
    int count = 0;
    bool newData = false;

    string readed;

    // Serial.println("START----------");
    // Serial.println(gps_serial.available());
    if(gps_serial.available())
    {
        readed = gps_serial.readStringUntil('\r').c_str();
        gps_serial.read();
        // Serial.println(readed.c_str());
        newData = readed.compare(lastMessage) != 0 && validarTrama(readed);
        if(newData) {
            lastMessage = readed;
            *data = createJson(readed);
        }
        //while (gps_serial.available()) {
        //Serial.println(gps_serial.readStringUntil('\n'));
        // buffer[count++] = gps_serial.readStringUntil("\n");
        // Serial.println(buffer[count-1]);
        // if (count == 256) {
        //     break;
        // }
    }

    //string stringBuffer = (const char*)buffer;

    // string json = createJson(stringBuffer);

    return newData;
}

bool GPSController::validarTrama(string data)
{
    char messageType[] = "$GPRMC";
    bool valido = memcmp(messageType, data.c_str(), sizeof(messageType) - 1) == 0;
    // THE_WALL++;
    // if (THE_WALL == 10)
    if(valido)
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