#include "Core.hpp"
#include <Arduino.h>
#include <string>
#include <sstream>

using namespace core;

Core::Core(WiFiController *wifiController, SDController *sdController, GPSController *gpsController, string* user)
{
    wifiController_ = wifiController;
    sdController_ = sdController;
    gpsController_ = gpsController;
    user_ = user;
    lastCoordinateTransmitted = 0;
    sendingData = false;
}

void Core::loop()
{
    string data;
    if (gpsController_->getData(&data, sdController_->getNumberOfData()))
    {
        sdController_->appendFile(data);
    }
    if (wifiController_->isConnected())
    {
        if (!sendingData)
        {
            sendingData = wifiController_->getLastCoordinateTransmitted(&lastCoordinateTransmitted);
        }
        if (sendingData && sdController_->getNumberOfData() > lastCoordinateTransmitted)
        {
            int coordinate = lastCoordinateTransmitted;
            stringstream data;
            data << "{ \"user\":\"";
            data << user_->c_str();
            data << "\",\"frames\":[";
            data << sdController_->readFile(coordinate);
            coordinate++;
            while (coordinate < sdController_->getNumberOfData() && coordinate - lastCoordinateTransmitted < 10)
            {
                data << ",";
                data << sdController_->readFile(coordinate);
                coordinate++;
            }
            data << "],\"total\":";
            data << (coordinate - lastCoordinateTransmitted);
            data << "}";
            if (wifiController_->sendData(data.str()))
            {
                lastCoordinateTransmitted = coordinate;
            }
        }
    }
    else
    {
        wifiController_->tryToConnect();
        sendingData = false;
    }
}

unsigned char *Core::formatGps(const unsigned char *raw_data)
{
    char messageType[] = "$GPRMC";
    if (memcmp(messageType, raw_data, sizeof(messageType) - 1))
    {
        return 0;
    }

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
    unsigned char *result = new unsigned char[29];
    memcpy(result + 0, raw_data + 7, 10);
    memcpy(result + 10, raw_data + 18, 8);
    memcpy(result + 18, raw_data + 27, 1);
    memcpy(result + 19, raw_data + 29, 9);
    memcpy(result + 28, raw_data + 39, 1);
    return result;
}
