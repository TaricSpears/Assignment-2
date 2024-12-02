#include "tasks/LevelTask.h"

#include <Arduino.h>

#include "config.h"
#include "kernel/Logger.h"

SleepTask::SleepTask(WasteDisposal *wasteDisposal, UserConsole *userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole}
{
    setState(SLEEP);
}

void SleepTask::tick()
{
    switch (state)
    {
    case SLEEP:
        if ()
        {
            // disabilita apertira sportello
            wasteDisposal->closeDoor();
            // SETTA IN MODALITA IDLE IL DISPOSITIVO
        }
        break;
    case ACTIVE:
        if ()
        {
            // abilita apertira sportello
            wasteDisposal->openDoor();
            // accendere led 1 O 2 IN BASE ALLO STATO
            setState(SLEEP);
        }
        break;
    }
}