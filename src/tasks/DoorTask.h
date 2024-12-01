#ifndef __DOOR_TASK__
#define __DOOR_TASK__

#include <UserConsole.h>

#include "kernel/Task.h"
#include "model/WasteDisposal.h"

class DoorTask : public Task {
   public:
    DoorTask(WasteDisposal* wasteDisposal, UserConsole* userConsole);
    void tick();

   private:
    enum State { AVAIABLE, OPENING, OPEN, CLOSING, BLOCKED, EMERGENCY } state;
    void setState(State state);
    long elapsedTimeInState();
    long stateTimestamp;

    WasteDisposal* wasteDisposal;
    UserConsole* userConsole;
};

#endif