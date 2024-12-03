#ifndef __LEVEL_TASK__
#define __LEVEL_TASK__

#include "model/UserConsole.h"

#include "kernel/Task.h"
#include "model/WasteDisposal.h"

class LevelTask : public Task {
   public:
    LevelTask(WasteDisposal *wasteDisposal, UserConsole *userConsole);
    void tick();

   private:
    enum State { OK, FULL } state;
    void setState(State state);
    long elapsedTimeInState();
    long stateTimestamp;

    WasteDisposal *wasteDisposal;
    UserConsole *userConsole;
};

#endif