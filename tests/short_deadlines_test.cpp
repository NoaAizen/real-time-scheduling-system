#include "smarts77.h"
#include "task_workloads.h"

// Short-deadline configuration from the Part 1 application.
// Select roundRobin, EDF, or RMS, then rebuild this scenario.
#ifndef PART1_SCHEDULER
#define PART1_SCHEDULER roundRobin
#endif

void main()
{
    clrscr();
    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd,
        PART1_SCHEDULER);

    // Original APP77 configuration: periods in timer ticks, three cycles each.
    SMARTS.declareTask(a, 'A', 100, 3);
    SMARTS.declareTask(b, 'B', 150, 3);
    SMARTS.declareTask(c, 'C', 200, 3);

    SMARTS.runTheTasks();
    for (long i = 0; i < 60000000; i++);
}
