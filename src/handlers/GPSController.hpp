#pragma once

#include <string>

namespace handlers
{
using namespace std;

class GPSController
{
public:
  GPSController();
  // Retorna true si la informacion que contiene no fue leida por getData
  virtual bool isUpdated();
  // Retorna la informacion almacenada
  virtual string getData();
};

} // namespace handlers
