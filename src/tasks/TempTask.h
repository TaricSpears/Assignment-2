#ifndef __CHECKIN_TASK__
#define __CHECKIN_TASK__

#include <UserConsole.h>

#include "kernel/Task.h"
#include "model/WasteDisposal.h"

class TempTask : public Task {
   public:
    TempTask(WasteDisposal* wasteDisposal, UserConsole* userConsole);
    void tick();

   private:
    enum State { OK, EMERGENCY } state;
    void setState(State state);
    long elapsedTimeInState();
    long stateTimestamp;
    long tempTime;

    WasteDisposal* wasteDisposal;
    UserConsole* userConsole;
};

#endif