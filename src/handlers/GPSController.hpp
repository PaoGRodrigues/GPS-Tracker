#pragma once

#include <string>

namespace handlers
{
using namespace std;

class GPSController
{
public:
  GPSController();
  // Asigna a data la informacion almacenada, retorna true si es nueva informacion
  virtual bool getData(string *data, int frameNumber);
  // Convierte un dato de GPS en un string Json
  virtual string createJson(string GPSString, int frameNumber);

private:
  // Valida que la trama sea GPRMC y que el estado sea valido
  virtual bool validarTrama(string);
  string lastMessage;
};

} // namespace handlers
