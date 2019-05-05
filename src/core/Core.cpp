#include "Core.hpp"
#include <Arduino.h>
#include <string>
#include <sstream>
using namespace core;

Core::Core(WiFiController *wifiController, SDController *sdController, GPSController *gpsController)
{
    wifiController_ = wifiController;
    sdController_ = sdController;
    gpsController_ = gpsController;
    lastCoordinateTransmitted = 0;
    sendingData = false;
}

const char *const data[15] = {
    "$GPGGA,012010.813,5231.067,N,01323.931,E,1,12,1.0,0.0,M,0.0,M,,*6A\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,012010.813,A,5231.067,N,01323.931,E,038.9,265.8,050519,000.0,W*7D\r\n",
    "$GPGGA,012011.813,5231.066,N,01323.914,E,1,12,1.0,0.0,M,0.0,M,,*6D\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,012011.813,A,5231.066,N,01323.914,E,038.9,265.8,050519,000.0,W*7A\r\n",
    "$GPGGA,012012.813,5231.065,N,01323.896,E,1,12,1.0,0.0,M,0.0,M,,*66\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,012012.813,A,5231.065,N,01323.896,E,038.9,265.8,050519,000.0,W*71\r\n",
    "$GPGGA,012013.813,5231.063,N,01323.879,E,1,12,1.0,0.0,M,0.0,M,,*60\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,012013.813,A,5231.063,N,01323.879,E,038.9,265.8,050519,000.0,W*77\r\n",
    "$GPGGA,012014.813,5231.062,N,01323.861,E,1,12,1.0,0.0,M,0.0,M,,*6F\r\n",
    "$GPGSA,A,3,01,02,03,04,05,06,07,08,09,10,11,12,1.0,1.0,1.0*30\r\n",
    "$GPRMC,012014.813,A,5231.062,N,01323.861,E,038.9,265.8,050519,000.0,W*78\r\n",
};

unsigned long datoProcesar = 0;
unsigned long datoRecuperar = 0;

void Core::loop()
{

    Serial.print("Dato a Procesar: ");
    Serial.print(data[datoProcesar]);
    unsigned char *result = formatGps((unsigned char *)data[datoProcesar]);
    if (result)
    {
        Serial.print("Dato procesado: ");
        Serial.write(result, 29);
        Serial.println();
        if (sdController_->checkStart())
        {
            sdController_->appendFile(result);
            sdController_->readFile((datoRecuperar * datoRecuperar) % sdController_->getNumberOfData());
        }
    }
    datoProcesar++;
    if (datoProcesar == 15)
    {
        datoProcesar = 0;
    }
    datoRecuperar++;
    /*
    if (gpsController_->isUpdated())
    {
        string data = gpsController_->getData();
        sdController_->saveData(data);
    }
    if (wifiController_->isConnected())
    {
        if (!sendingData)
        {
            lastCoordinateTransmitted = wifiController_->getLastCoordinateTransmitted();
            sendingData = true;
        }
        if (sdController_->getNumberOfData() >= lastCoordinateTransmitted)
        {
            string data = sdController_->getData(lastCoordinateTransmitted++);
            wifiController_->sendData(data);
        }
    }
    else
    {
        wifiController_->tryToConnect();
        sendingData = false;
    }
    */
}

unsigned char *Core::formatGps(const unsigned char *raw_data)
{
    char messageType[] = "$GPGGA";
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
