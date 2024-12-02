#include "tasks/LevelTask.h"

#include <Arduino.h>

#include "config.h"
#include "kernel/Logger.h"

#define MAXDISTANCE 30

LevelTask::LevelTask(WasteDisposal *wasteDisposal, UserConsole *userConsole)
    : wasteDisposal{wasteDisposal}, userConsole{userConsole}
{
  setState(OK);
}

void LevelTask::tick()
{
  switch (state)
  {
  case OK:
    if (wasteDisposal->getCurentDistance() <= MAXDISTANCE)
    {
      // disabilita apertira sportello
      wasteDisposal->closeDoor();
      userConsole->displayMessage("CONTAINER FULL");
      wasteDispodsal->isEmergency();
      // mostra "CONTAINER FULL" sul display
      
      setState(FULL);
    }

    break;
  case FULL:
    if (wasteDisposal->getCurentDistance() > MAXDISTANCE)
    {
      // abilita apertira sportello
      wasteDisposal->openDoor();
      // accendere led 1
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

long TempTask::elapsedTimeInState()
{
  return millis() - stateTimestamp;
}