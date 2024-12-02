#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "devices/Button.h"

class UserConsole {
   public:
    UserConsole();

    void init();
    void sync();

    void turnOffDisplay();
    void turnOnDisplay();

    void displayMessage(const char* message);
    void displayMessage(const char* line1, const char* line2);
    void displayWelcome();
    void displayChekingIn();
    void displayWaitToStart();
    void displayWashing(int perc);
    void displayWashingSuspended();
    void displayChekingOut();

    void prepareToSleep();
    void resumeFromSleeping();

    void test();

    bool isCloseButtonPressed();
    bool isOpenButtonPressed();

   private:
    Button* openButton;
    Button* closeButton;
    LiquidCrystal_I2C* lcd;
};

#endif
