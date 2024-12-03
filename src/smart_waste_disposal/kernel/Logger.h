#ifndef __LOGGER__
#define __LOGGER__

#include "Arduino.h"

class LoggerService {
   public:
    void log(const String& msg);
    void bin(const String& msg);
    void temp(const String& msg);
    void emergency(const String& msg);
};

extern LoggerService Logger;

#endif
