#include "tasks/DoorTask.h"

#include <Arduino.h>

#include "config.h"
#include "kernel/Logger.h"
// #include "UserConsole.h"

#define T1 10000
#define T2 3000

DoorTask::DoorTask(WasteDisposal* wasteDisposal, UserConsole* userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole} {
    setState(AVAIABLE);
}

void DoorTask::tick() {
    switch (state) {
        case AVAIABLE:
            // if bottone premuto
            break;

        case OPENING:
            wasteDisposal->openDoor();
            setState(OPEN);
            break;

        case OPEN:
            userConsole->displayMessage("PRESS CLOSE WHEN DONE");
            if (elapsedTimeInState() > T1 /* oppure bottone premuto*/) {
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
    }
}

void DoorTask::setState(State s) {
    state = s;
    stateTimestamp = millis();
}

long DoorTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}