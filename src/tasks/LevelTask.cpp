#include "tasks/LevelTask.h"

#include <Arduino.h>

#include "config.h"
#include "kernel/Logger.h"

#define MAXDISTANCE 0.30

LevelTask::LevelTask(WasteDisposal *wasteDisposal, UserConsole *userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole} {
    setState(OK);
}

void LevelTask::tick() {
    switch (state) {
        case OK:
            if (wasteDisposal->getCurrentLevel() <= MAXDISTANCE) {
                wasteDisposal->setFull();
                wasteDisposal->closeDoor();
                userConsole->displayMessage("CONTAINER FULL");
                setState(FULL);
            }
            break;
        case FULL:
            if (wasteDisposal->getCurrentLevel() > MAXDISTANCE) {
                wasteDisposal->setAcceptingWaste();
                setState(OK);
            }
            break;
    }
}

void LevelTask::setState(State s) {
    state = s;
    stateTimestamp = millis();
}

long LevelTask::elapsedTimeInState() {
    return millis() - stateTimestamp;
}