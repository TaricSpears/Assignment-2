#include <Arduino.h>

#include "WasteDisposal.h"
#include "config.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "kernel/Scheduler.h"
#include "model/CarWashingPlant.h"
#include "model/UserConsole.h"
#include "tasks/DoorTask.h"
#include "tasks/LevelTask.h"
#include "tasks/SleepTask.h"
#include "tasks/TempTask.h"

Scheduler sched;

WasteDisposal* wasteDisposal;
UserConsole* userConsole;

void setup() {
    MsgService.init();
    sched.init(100);

    Logger.log("Waste Disposal");

    wasteDisposal = new WasteDisposal();
    wasteDisposal->init();

    userConsole = new UserConsole();
    userConsole->init();

    Task* doorTask = new DoorTask(wasteDisposal, userConsole);
    doorTask->init(100);

    Task* levelTask = new LevelTask(wasteDisposal, userConsole);
    levelTask->init(100);

    SleepTask* sleepTask = new SleepTask(wasteDisposal, userConsole);
    sleepTask->init(100);
    sleepTask->initialize();

    Task* tempTask = new TempTask(wasteDisposal, userConsole);
    tempTask->init(100);

    sched.addTask(doorTask);
    sched.addTask(levelTask);
    sched.addTask(sleepTask);
    sched.addTask(tempTask);
}

void loop() {
    sched.schedule();
}