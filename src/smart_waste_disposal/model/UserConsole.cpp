#include "UserConsole.h"

#include <Arduino.h>
#include <avr/sleep.h>

#include "config.h"
#include "devices/ButtonImpl.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"

UserConsole::UserConsole() {
    lcd = new LiquidCrystal_I2C(0x27, 20, 4);
    openButton = new ButtonImpl(OPEN_BTN_PIN);
    closeButton = new ButtonImpl(CLOSE_BTN_PIN);
}

void UserConsole::init() {
    lcd->init();
    lcd->backlight();
    lcd->noDisplay();
}

void UserConsole::sync() {
    openButton->sync();
    closeButton->sync();
}

void UserConsole::turnOnDisplay() {
    lcd->display();
    lcd->clear();
}

void UserConsole::turnOffDisplay() {
    lcd->noDisplay();
}

bool UserConsole::isCloseButtonPressed() {
    closeButton->sync();
    return closeButton->isPressed();
}

bool UserConsole::isOpenButtonPressed() {
    openButton->sync();
    return openButton->isPressed();
}

void UserConsole::displayWelcome() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Welcome");
}

void UserConsole::displayChekingIn() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Proceed to the Washing Area");
}

void UserConsole::displayWaitToStart() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Ready To Wash");
}

void UserConsole::displayWashing(int perc) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Washing");
    lcd->setCursor(0, 1);
    lcd->setCursor(0, 1);
    lcd->print(String(perc));
    for (int i = 0; i < perc / 10; i++) {
        lcd->setCursor(5 + i, 1);
        lcd->print((char)0xFF);
    }
}

void UserConsole::displayWashingSuspended() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Washing Suspended");
}

void UserConsole::displayChekingOut() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Washing complete, you can leave the area");
}

void UserConsole::prepareToSleep() {
    lcd->noDisplay();
}

void UserConsole::resumeFromSleeping() {
    lcd->display();
}
void UserConsole::displayMessage(const char* message) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(message);
}

void UserConsole::displayMessage(const char* line1, const char* line2) {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(line1);
    lcd->setCursor(0, 1);
    lcd->print(line2);
}

void UserConsole::test() {
    Logger.log("Testing the User Console");
    delay(1000);

    Logger.log("Display test...");
    lcd->display();
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Testing");

    Logger.log("Button test...");
    long t0 = millis();
    while (millis() - t0 < 5000) {
        sync();
        if (openButton->isPressed()) {
            Logger.log("pressed");
        }
    }
}
