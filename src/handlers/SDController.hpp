#pragma once

#include <string>

namespace handlers
{
using namespace std;

class SDController
{
public:
  SDController();
  // Almacena en la SD el string "data" luego de la ultima informacion guardada
  virtual void saveData(string data);
  // Retorna el mensaje almacenado en la posicion "position"
  virtual string getData(unsigned long position);
  // Retorna el ultimo indice donde se almaceno informacion
  virtual unsigned long getNumberOfData();
};

} // namespace handlers
