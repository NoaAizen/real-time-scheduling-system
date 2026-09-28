#include "smarts77.h"

// Original Part 2 mutex experiment using RMS priorities.
Mutex printMutex;

void taskA()
{
    printMutex.Acquire();
    cout << "\nA Start";
    for (int j = 0; j < 30; j++)
    {
        for (long i = 0; i < 80000L; i++);
        cout << "A";
    }
    cout << "\nA Finish";
    printMutex.Release();
}

void taskB()
{
    printMutex.Acquire();
    cout << "\nB Start";
    for (int j = 0; j < 30; j++)
    {
        for (long i = 0; i < 80000L; i++);
        cout << "B";
    }
    cout << "\nB Finish";
    printMutex.Release();
}

void taskC()
{
    printMutex.Acquire();
    cout << "\nC Start";
    for (int j = 0; j < 30; j++)
    {
        for (long i = 0; i < 80000L; i++);
        cout << "C";
    }
    cout << "\nC Finish";
    printMutex.Release();
}

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
