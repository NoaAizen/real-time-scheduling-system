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

// Select the READY task with the highest current RMS priority.
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
