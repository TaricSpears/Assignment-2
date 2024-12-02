#ifndef __SLEEP_TASK__
#define __SLEEP_TASK__

#include <UserConsole.h>

#include "kernel/Task.h"
#include "model/WasteDisposal.h"

class SleepTask : public Task {
   public:
    SleepTask(WasteDisposal *wasteDisposal, UserConsole *userConsole);
    void tick();
    void initialize();

   private:
    enum State { SLEEP, NEAR, FAR } state;
    void setState(State state);
    long elapsedTimeInState();
    long stateTimestamp;

    WasteDisposal *wasteDisposal;
    UserConsole *userConsole;
};

#endif