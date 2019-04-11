#pragma once

#include <string>
#include <vector>

namespace handlers
{
using namespace std;

class WiFiController
{
public:
  WiFiController();
  virtual void addAccessPoint(string ssid, string pass);
  virtual bool isConnected();
  virtual bool tryToConnect();
  virtual void sendData(string data);

private:
  vector<pair<string, string>*>* accessPoints_;
  int timeout_;
  int selected_;
};

} 
