#include "smarts77.h"

// Original mutex experiment, retained as an unverified manual DOS scenario.
Mutex printMutex;

void work(char name)
{
    printMutex.Acquire();
    cout << "\n" << name << " Start";
    for (int j = 0; j < 30; j++)
    {
        for (long i = 0; i < 80000L; i++);
        cout << name;
    }
    cout << "\n" << name << " Finish";
    printMutex.Release();
}

void taskA() { work('A'); }
void taskB() { work('B'); }
void taskC() { work('C'); }

void main()
{
    clrscr();
    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS);
    SMARTS.declareTask(taskA, 'A', 400, 3);
    SMARTS.declareTask(taskB, 'B', 401, 3);
    SMARTS.declareTask(taskC, 'C', 402, 3);
    SMARTS.runTheTasks();
    for (long i = 0; i < 60000000L; i++);
}
