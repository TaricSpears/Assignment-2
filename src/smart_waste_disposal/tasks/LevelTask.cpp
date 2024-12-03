#include "tasks/LevelTask.h"

#include <Arduino.h>

#include "config.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"

#define MAXDISTANCE 0.10
#define T3 5000

LevelTask::LevelTask(WasteDisposal *wasteDisposal, UserConsole *userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole}
{
    setState(OK);
}

CleanPattern *cleanPattern = new CleanPattern();

void LevelTask::tick()
{
    double level = wasteDisposal->getCurrentLevel();
    switch (state)
    {
    case OK:
    {
        Logger.bin(String((int)((1 - level) * 100.0 / (1 - MAXDISTANCE))));
        if (level <= MAXDISTANCE)
        {
            wasteDisposal->setFull();
            wasteDisposal->closeDoor();
            userConsole->displayMessage("CONTAINER FULL");
            setState(FULL);
        }
        break;
    }
    case FULL:
        if (MsgService.isMsgAvailable(*cleanPattern) && level > MAXDISTANCE)
        {
            Msg *msg = MsgService.receiveMsg(*cleanPattern);
            setState(EMPTYING);
            wasteDisposal->bendDoor();
        }
        break;
    case EMPTYING:
        if (elapsedTimeInState() > T3)
        {
            wasteDisposal->closeDoor();
            wasteDisposal->setAcceptingWaste();
            setState(OK);
        }
        break;
    }
}

void LevelTask::setState(State s)
{
    state = s;
    stateTimestamp = millis();
}

long LevelTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}