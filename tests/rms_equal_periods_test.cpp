#include "smarts77.h"
#include "task_workloads.h"

// Part 2 RMS experiment: all tasks have the same period and base priority.
#ifndef PART1_SCHEDULER
#define PART1_SCHEDULER RMS
#endif

void main()
{
    clrscr();
    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd,
        PART1_SCHEDULER);

    // Original Part 2 configuration: equal periods, three cycles each.
    SMARTS.declareTask(a, 'A', 1000, 3);
    SMARTS.declareTask(b, 'B', 1000, 3);
    SMARTS.declareTask(c, 'C', 1000, 3);

    SMARTS.runTheTasks();
    for (long i = 0; i < 60000000; i++);
}
