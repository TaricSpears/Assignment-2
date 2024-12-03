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
    if (!wasteDisposal->canOpenDoor()) {
        if (state == OPEN) {
            wasteDisposal->closeDoor();
        }
        setState(BLOCKED);
    }
    switch (state) {
        case AVAIABLE:
            displayMessageOnce("PRESS OPEN TO", "ENTER WASTE");
            if (userConsole->isOpenButtonPressed()) {
                setState(OPENING);
            }
            break;
        case OPENING:
            wasteDisposal->openDoor();
            setState(OPEN);
            break;
        case OPEN:
            displayMessageOnce("PRESS CLOSE", "WHEN DONE");
            if (elapsedTimeInState() > T1 || userConsole->isCloseButtonPressed()) {
                setState(CLOSING);
            }
            break;
        case CLOSING:
            wasteDisposal->closeDoor();
            setState(JUST_CLOSED);
            break;
        case JUST_CLOSED:
            displayMessageOnce("WASTE RECEIVED", "");
            if (elapsedTimeInState() > T2) {
                setState(AVAIABLE);
            }
            break;
        case BLOCKED:
            if (wasteDisposal->canOpenDoor()) {
                setState(AVAIABLE);
            }
            break;
    }
}

void DoorTask::setState(State s) {
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

void DoorTask::displayMessageOnce(const char* line1, const char* line2) {
    if (justEntered) {
        userConsole->displayMessage(line1, line2);
        justEntered = false;
    }
}

long DoorTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}