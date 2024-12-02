#include "tasks/DoorTask.h"

#include <Arduino.h>

#include "config.h"
#include "kernel/Logger.h"

#define T1 10000
#define T2 3000

DoorTask::DoorTask(WasteDisposal* wasteDisposal, UserConsole* userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole} {
    setState(AVAIABLE);
}

void DoorTask::tick() {
    if (wasteDisposal->isEmergency()) {
        if (state == OPEN) {
            wasteDisposal->closeDoor();
            setState(EMERGENCY);
        }
    }
    switch (state) {
        case AVAIABLE:
            if (userConsole->isOpenButtonPressed()) {
                setState(OPENING);
            }
            break;
        case OPENING:
            wasteDisposal->openDoor();
            setState(OPEN);
            userConsole->displayMessage("PRESS CLOSE WHEN DONE");
            break;
        case OPEN:
            if (elapsedTimeInState() > T1 || userConsole->isCloseButtonPressed()) {
                setState(CLOSING);
            }
            break;
        case CLOSING:
            wasteDisposal->closeDoor();
            setState(BLOCKED);
            break;
        case BLOCKED:
            userConsole->displayMessage("WASTE RECEIVED");
            if (elapsedTimeInState() > T2) {
                setState(AVAIABLE);
            }
            break;
        case EMERGENCY:
            if (!wasteDisposal->isEmergency()) {
                setState(AVAIABLE);
            }
            break;
    }
}

void DoorTask::setState(State s) {
    state = s;
    stateTimestamp = millis();
}

long DoorTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}