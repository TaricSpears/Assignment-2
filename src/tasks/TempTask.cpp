#include "tasks/TempTask.h"

#include <Arduino.h>

#include "config.h"
#include "kernel/Logger.h"

#define MAXTEMP 30
#define MAXTEMPTIME 5000

TempTask::TempTask(WasteDisposal* wasteDisposal, UserConsole* userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole} {
    setState(OK);
}

void TempTask::tick() {
    switch (state) {
        case OK:
            if (wasteDisposal->getCurrentTemperature() < MAXTEMP) {
                tempTime = 0;
            }
            if (tempTime > MAXTEMPTIME) {
                setState(EMERGENCY);
            }
            break;
        case EMERGENCY:
            break;
    }
}

void TempTask::setState(State s) {
    state = s;
    stateTimestamp = millis();
}

long TempTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}