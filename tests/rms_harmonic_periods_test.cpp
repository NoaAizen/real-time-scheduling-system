#include "smarts77.h"
#include "task_workloads.h"

// Part 2 RMS experiment with shorter periods assigned higher priorities.
#ifndef PART1_SCHEDULER
#define PART1_SCHEDULER RMS
#endif

void main()
{
    clrscr();
    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd,
        PART1_SCHEDULER);

    // Original Part 2 configuration: harmonic periods, five cycles each.
    SMARTS.declareTask(a, 'A', 5000, 5);
    SMARTS.declareTask(b, 'B', 10000, 5);
    SMARTS.declareTask(c, 'C', 20000, 5);

    SMARTS.runTheTasks();
    for (long i = 0; i < 60000000; i++);
}
