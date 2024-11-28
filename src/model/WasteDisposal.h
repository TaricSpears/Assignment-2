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
    void readyToAccept();

    void idle();
    void prepareToSleep();
    void resumeFromSleeping();

    void readyForCheckIn();
    bool isReadyForCheckIn();
    bool isCheckInCompleted();
    void checkInStarted();
    void checkInCompleted();

    void readyForWashing();
    bool isReadyForWashing();
    void washingStarted();
    void resumeWashing();
    void washingCompleted();
    bool isWashingCompleted();

    void readyForCheckOut();
    bool isReadyForCheckOut();
    void checkOutStarted();
    void checkOutCompleted();
    bool isCheckOutCompleted();

    void setInMaintenance();
    bool isInMaintenance();
    void maintenanceDone();
    bool isReadyToResume();

    bool isIdle();
    bool isCheckingIn();
    bool isWashing();
    bool isCheckingOut();
    bool isEmergency();
    

    double getCurrentCarDistance();
    bool detectedCarPresence();
    double getCurrentTemperature();
    int getNumWashes();

    void sampleCarPresence();
    void sampleCarDistance();
    void sampleTemperature();

    void test();

   private:
    double currentTemperature;
    double currentCarDistance;
    bool detectedCarPres;

    int nWashes;

    enum {
        IDLE,
        READY_FOR_CHECKIN,
        CHECKING_IN,
        CHECK_IN_COMPLETED,
        READY_FOR_WASHING,
        WASHING,
        WASHING_COMPLETED,
        READY_FOR_CHECKOUT,
        CHECKING_OUT,
        CHECK_OUT_COMPLETED,
        MAINTENANCE,
        READY_TO_RESUME,
        EMERGENCY
    } state;

    Led* ledOn;
    Led* ledAlarm;
    Pir* pir;
    Sonar* sonar;
    ServoMotor* doorMotor;
    TempSensor* tempSensor;
};

#endif