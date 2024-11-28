#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "config.h"
#include "devices/Button.h"
// #include "Bridge.h"

class UserConsole {
   public:
    UserConsole();

    void init();
    void sync();

    void turnOffDisplay();
    void turnOnDisplay();

    bool started();

    void displayMessage(const char* message);
    void displayWelcome();
    void displayChekingIn();
    void displayWaitToStart();
    void displayWashing(int perc);
    void displayWashingSuspended();
    void displayChekingOut();

    void prepareToSleep();
    void resumeFromSleeping();

    void test();

   private:
    Button* pButton;
    LiquidCrystal_I2C* pLcd;
};

#endif
