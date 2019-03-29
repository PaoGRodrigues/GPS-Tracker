#pragma once

#include <string>

namespace handlers
{

class WiFiController
{
public:
  WiFiController();
  virtual void addAccessPoint(std::string ssid, std::string pass);
  virtual bool isConnected();
  virtual bool tryToConnect();

private:
  vector<pair<std::string, std::string>*>* accessPoints_;
  int timeout_;
  int selected_;
};

} 
