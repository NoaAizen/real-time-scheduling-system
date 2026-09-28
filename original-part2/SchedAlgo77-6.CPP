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

/* Earliest Deadline First scheduler
   Chooses the READY task with the
   smallest remaining deadline. */
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



// int RMS()
// {
//    // Start with the idle task as default
//    int choose = SMARTS.getTotalTasks();
//    // Used to find the highest priority task
//    int min = MAXINT;

//    for (int i = 0; i < SMARTS.getTotalTasks(); i++)
//    {
//        // consider only runnable tasks
//        if (SMARTS.getStatus(i) == READY)
//        {
//            // choose task with big priorty - min period
//            if (SMARTS.getPeriod(i) < min)
//            {
//                min = SMARTS.getPeriod(i);
//                // update selected task
//                choose = i;
//            }
//        }
//    }
//    return choose;
// }



int RMS()
{
    int choose = SMARTS.getTotalTasks();
    int min = MAXINT;

    for (int i = 0; i < SMARTS.getTotalTasks(); i++)
    {
        if (SMARTS.getStatus(i) == READY)
        {
            if (SMARTS.getCurrentPriority(i) < min)
            {
                min = SMARTS.getCurrentPriority(i);
                choose = i;
            }
        }
    }

    return choose;
}

