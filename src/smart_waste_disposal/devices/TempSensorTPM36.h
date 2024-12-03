#ifndef __TEMP_SENSOR_TPM36__
#define __TEMP_SENSOR_TPM36__

#include "TempSensor.h"

class TempSensorTPM36 : public TempSensor {
   public:
    TempSensorTPM36(int p);
    virtual float getTemperature();

   private:
    int pin;
};

#endif
