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
    virtual void listDirectory(fs::FS &fs, const char *dirname, uint8_t levels);
    virtual void createDirectory(fs::FS &fs, const char *path);
    virtual void removeDirectory(fs::FS &fs, const char *path);
    virtual void readFile(fs::FS &fs, const char *path);
    virtual void writeFile(fs::FS &fs, const char *path, const char *message);
    virtual void appendFile(fs::FS &fs, const char *path, const char *message);
    virtual void deleteFile(fs::FS &fs, const char *path);
    virtual void checkStart();
};

}