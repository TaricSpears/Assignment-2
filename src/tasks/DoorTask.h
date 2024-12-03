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
    enum State { AVAIABLE, OPENING, OPEN, CLOSING, JUST_CLOSED, BLOCKED } state;
    void setState(State state);
    long elapsedTimeInState();
    void displayMessageOnce(const char* line1, const char* line2);
    long stateTimestamp;
    bool justEntered;

    WasteDisposal* wasteDisposal;
    UserConsole* userConsole;
};

#endif