// Based on the SMARTS77 framework by A. Teitelbaum,
// on an idea by H. G. Mendelbaum, Jerusalem College of Technology.

#include "smarts77.h"

// Provided SMARTS77 code: scan cyclically for the next READY task.
// The task index returned on an unsuccessful scan is the idle-task index.
int roundRobin()

{
    int count;
    int nextTask = (SMARTS.getCurrentTask() + 1) % SMARTS.getTotalTasks();
    for (count = 0;
        SMARTS.getStatus(nextTask) != READY && count < SMARTS.getTotalTasks();
        count++)
        nextTask = ++nextTask % SMARTS.getTotalTasks();
    if (count == SMARTS.getTotalTasks())
        nextTask = SMARTS.getTotalTasks();
    return nextTask;
}

// Part 1 implementation: select the READY task with the earliest deadline.
// Strict comparison preserves declaration order for equal eligible deadlines.
int EDF()
{

    int best = SMARTS.getTotalTasks();

    int min = MAXINT;

    for (int i = 0; i < SMARTS.getTotalTasks(); i++)
    {

        if (SMARTS.getStatus(i) == READY)
        {

            if (SMARTS.getRemainingTime(i) < min)
            {
                min = SMARTS.getRemainingTime(i);

                best = i;
            }
        }
    }
    return best;
}

// Part 2 Stage 1: select the READY task with the shortest-period priority.
// currentPriority initially equals the period and is retained for later
// priority-inheritance work.
int RMS()
{
    int best = SMARTS.getTotalTasks();
    int minPriority = MAXINT;

    for (int i = 0; i < SMARTS.getTotalTasks(); i++)
    {
        if (SMARTS.getStatus(i) == READY &&
            SMARTS.getCurrentPriority(i) < minPriority)
        {
            minPriority = SMARTS.getCurrentPriority(i);
            best = i;
        }
    }
    return best;
}
