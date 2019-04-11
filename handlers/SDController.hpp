#pragma once

#include <string>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

namespace handlers
{

class SDController
{
  public:
    SDController();
    virtual void listDirectory(std::string ssid, std::string pass);
    virtual bool createDirectory(fs::FS &fs, const char *path);
    virtual bool removeDirectory(fs::FS &fs, const char *path);
    virtual bool readFile(fs::FS &fs, const char *path);
    virtual bool writeFile(fs::FS &fs, const char *path, const char *message);
    virtual bool appendFile(fs::FS &fs, const char *path, const char *message);
    virtual bool deleteFile(fs::FS &fs, const char *path);
    virtual bool checkStart(fs::FS &fs, const char *path);
};

}