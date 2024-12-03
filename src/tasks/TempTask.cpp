#include "tasks/TempTask.h"

#include <Arduino.h>

#include "config.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"

#define MAXTEMP 21
#define MAXTEMPTIME 5000

RestorePattern* restorePattern = new RestorePattern();

TempTask::TempTask(WasteDisposal* wasteDisposal, UserConsole* userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole} {
    setState(OK);
}

void TempTask::tick() {
    Logger.temp(String(wasteDisposal->getCurrentTemperature()));
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
                Logger.emergency("1");
            } else if (wasteDisposal->getCurrentTemperature() <= MAXTEMP) {
                setState(OK);
            }
            break;
        case EMERGENCY:
            if (MsgService.isMsgAvailable(*restorePattern)) {
                Msg* msg = MsgService.receiveMsg(*restorePattern);
                wasteDisposal->setAcceptingWaste();
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