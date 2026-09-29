// Based on the SMARTS77 framework by A. Teitelbaum,
// on an idea by H. G. Mendelbaum, Jerusalem College of Technology.

#include "smarts77.h"

Mutex::Mutex()
{
    value = 1;
    owner = -1;
    waitingCount = 0;

    for (int i = 0; i < MaxTask; i++)
        waitingTasks[i] = -1;
}


// Prevent a timer-driven context switch while mutex state is updated.
void Mutex::Acquire()
{
    SMARTS.contextSwitchOff();

    int currentTask = SMARTS.getCurrentTask();

    if (value == 1)
    {
        value = 0;
        owner = currentTask;
        cout << "\nTask " << currentTask << " acquired mutex";
        SMARTS.contextSwitchOn();
        return;
    }


    cout << "\nTask " << currentTask << " blocked";
    waitingTasks[waitingCount++] = currentTask;
    SMARTS.suspended();
    SMARTS.contextSwitchOn();
}

void Mutex::Release()
{
    SMARTS.contextSwitchOff();

    int currentTask = SMARTS.getCurrentTask();

    if (owner != currentTask)
    {
        cout << "\nERROR: Task " << currentTask << " is not owner";
        SMARTS.contextSwitchOn();
        return;
    }

    cout << "\nTask " << currentTask << " released mutex";


    if (waitingCount == 0)
    {
        value = 1;
        owner = -1;
        SMARTS.contextSwitchOn();
        return;
    }

    int bestIndex = getHighestPriorityTask();
    int nextTask = waitingTasks[bestIndex];

    for (int i = bestIndex; i < waitingCount - 1; i++)
        waitingTasks[i] = waitingTasks[i + 1];

    waitingCount--;
    owner = nextTask;
    value = 0;

    cout << "\nTask " << nextTask << " resumed and owns mutex";
    SMARTS.resume(nextTask);
    SMARTS.callScheduler();
    SMARTS.contextSwitchOn();
}

int Mutex::getHighestPriorityTask()
{
    int bestIndex = 0;
    int minPriority = MAXINT;

    for (int i = 0; i < waitingCount; i++)
    {
        if (SMARTS.getCurrentPriority(waitingTasks[i]) < minPriority)
        {
            minPriority = SMARTS.getCurrentPriority(waitingTasks[i]);
            bestIndex = i;
        }
    }
    return bestIndex;
}
