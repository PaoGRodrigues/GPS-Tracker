#pragma once

#include <string>

namespace handlers
{

class SDController
{
  public:
    SDController();
    virtual void listDirectory(const char *dirname, uint8_t levels);
    virtual void createDirectory(const char *path);
    virtual void removeDirectory(const char *path);
    virtual void readFile(const char *path);
    virtual void writeFile(const char *path, const char *message);
    virtual void appendFile(const char *path, const char *message);
    virtual void deleteFile(const char *path);
    virtual bool checkStart();
};

}