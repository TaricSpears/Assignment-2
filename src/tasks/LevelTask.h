#ifndef __CHECKIN_TASK__
#define __CHECKIN_TASK__

#include <UserConsole.h>

#include "kernel/Task.h"
#include "model/WasteDisposal.h"

class LevelTask : public Task
{
public:
    LevelTask(WasteDisposal *wasteDisposal, UserConsole *userConsole);
    void tick();

private:
    enum State
    {
        OK,
        FULL
    } state;
    void setState(State state);
    long elapsedTimeInState();
    long stateTimestamp;

    WasteDisposal *wasteDisposal;
    UserConsole *userConsole;
};