#pragma once

#include <string>

namespace handlers
{
using namespace std;

class SDController
{
  public:
    SDController();
    virtual void readFile(const char *path, int dataNumber);
    virtual void writeFile(const char *path, const char *message);
    virtual void appendFile(const char *path, const char *message);
    virtual void deleteFile(const char *path);
    virtual bool checkStart();
    // Almacena en la SD el string "data" luego de la ultima informacion guardada
    virtual void saveData(string data);
    // Retorna el mensaje almacenado en la posicion "position"
    virtual string getData(unsigned long position);
    // Retorna el ultimo indice donde se almaceno informacion
    virtual unsigned long getNumberOfData();

  private:
    // dataSize es al tamaño de dato almacenado en el registro.
    int dataSize = 10;
    int lastDataStore = 0;
};

}