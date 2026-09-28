


#include "smarts77.h"

int roundRobin()
// Round Robin short-term algorithm 
{
    int count;
    int nextTask = (SMARTS.getCurrentTask() + 1) % SMARTS.getTotalTasks();
    for (count = 0;
        SMARTS.getStatus(nextTask) != READY && count < SMARTS.getTotalTasks();
        count++)
        nextTask = ++nextTask % SMARTS.getTotalTasks();
    if (count == SMARTS.getTotalTasks())	// no found READY task to run
        nextTask = SMARTS.getTotalTasks();
    return nextTask;
}

//new - Earliest Deadline First scheduling algorithm
int EDF()
{
    // default to idle task if no READY task exists
    int best = SMARTS.getTotalTasks();
    // initialize minimum deadline value to find the task with the min deadline
    int min = MAXINT;

    for (int i = 0; i < SMARTS.getTotalTasks(); i++)
    {
        // consider only runnable tasks
        if (SMARTS.getStatus(i) == READY)
        {
            // choose task with earliest deadline
            if (SMARTS.getRemainingTime(i) < min)
            {
                min = SMARTS.getRemainingTime(i);
                // update selected task
                best = i;
            }
        }
    }
    return best;
}

