#include "tasks/SleepTask.h"

#include <Arduino.h>
#include <avr/sleep.h>

#include "config.h"
#include "kernel/Logger.h"

#define Tsleep 12000
SleepTask::SleepTask(WasteDisposal *wasteDisposal, UserConsole *userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole} {
    setState(SLEEP);
}

void wakeUp() {
}

void SleepTask::initialize() {
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), wakeUp, RISING);
}

void SleepTask::tick() {
    switch (state) {
        case SLEEP:
            wasteDisposal->prepareToSleep();
            userConsole->prepareToSleep();
            delay(100);
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();
            wasteDisposal->resumeFromSleeping();
            userConsole->resumeFromSleeping();
            setState(NEAR);
            break;
        case NEAR:
            if (!wasteDisposal->isUserDetected()) {
                setState(FAR);
            }
            break;
        case FAR:
            if (elapsedTimeInState() > Tsleep) {
                setState(SLEEP);
            } else if (wasteDisposal->isUserDetected()) {
                setState(NEAR);
            }
            break;
    }
}

void SleepTask::setState(State s) {
    state = s;
    stateTimestamp = millis();
}

long SleepTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}