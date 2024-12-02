#ifndef __WASTE_DISPOSAL_PLANT__
#define __WASTE_DISPOSAL_PLANT__

#include <Arduino.h>

#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/TempSensor.h"
#include "devices/servo_motor.h"

class WasteDisposal {
   public:
    WasteDisposal();

    void init();

    void openDoor();
    void closeDoor();

    void prepareToSleep();
    void resumeFromSleeping();

    bool isEmergency();
    void setEmergency();

    bool isFull();
    void setFull();

    bool isNormal();
    void setNormal();

    double getCurrentTemperature();
    double getCurrentLevel();
    bool isUserDetected();

   private:
    double currentTemperature;
    double currentCarDistance;
    bool detectedCarPres;

    int nWashes;

    enum { NORMAL, FULL, EMERGENCY } state;

    Led* ledOn;
    Led* ledAlarm;
    Pir* pir;
    Sonar* sonar;
    ServoMotor* doorMotor;
    TempSensor* tempSensor;
};

#endif