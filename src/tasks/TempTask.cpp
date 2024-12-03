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
            if (wasteDisposal->getCurrentTemperature() > MAXTEMP) {
                setState(HOT);
            }
            break;
        case HOT:
            if (elapsedTimeInState() > MAXTEMPTIME) {
                setState(EMERGENCY);
                wasteDisposal->setEmergency();
                userConsole->displayMessage("PROBLEM DETECTED");
            } else if (wasteDisposal->getCurrentTemperature() <= MAXTEMP) {
                setState(OK);
            }
            break;
        case EMERGENCY:
            if (!wasteDisposal->isEmergency()) {
                setState(OK);
            }
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