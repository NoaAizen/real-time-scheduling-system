#include "smarts77.h"

Mutex printMutex;
Event eventToB;
Event eventToC;
FILE* myOutput;

void work(char ch, int times)
{
    for (int i = 0; i < times; i++)
    {
        fprintf(myOutput, "%c", ch);
        for (long d = 0; d < 10000L; d++);
    }
    fflush(myOutput);
}

// Low-priority task: acquires the mutex before releasing the other tasks.
void lowTask()
{
    fprintf(myOutput, "\n[A LOW] started\n");
    printMutex.Acquire();
    fprintf(myOutput, "\n[A LOW] acquired mutex\n");
    work('a', 20);

    fprintf(myOutput, "\n[A LOW] sends event to B\n");
    eventToB.send('B', NULL, false);
    fprintf(myOutput, "\n[A LOW] sends event to C\n");
    eventToC.send('C', NULL, false);

    work('a', 120);
    fprintf(myOutput, "\n[A LOW] releases mutex\n");
    printMutex.Release();
    work('a', 20);
    fprintf(myOutput, "\n[A LOW] finished\n");
}

// Medium-priority task: independent CPU work.
void middleTask()
{
    char source;
    fprintf(myOutput, "\n[B MID] waiting for event\n");
    eventToB.wait(source);
    fprintf(myOutput, "\n[B MID] got event from %c\n", source);

    for (int i = 0; i < 300; i++)
    {
        fprintf(myOutput, "B");
        for (long d = 0; d < 10000L; d++);
        if (i % 20 == 0)
            SMARTS.callScheduler();
    }
    fprintf(myOutput, "\n[B MID] finished\n");
}

// High-priority task: blocks on the mutex held by the low-priority task.
void highTask()
{
    char source;
    fprintf(myOutput, "\n[C HIGH] waiting for event\n");
    eventToC.wait(source);
    fprintf(myOutput, "\n[C HIGH] got event from %c\n", source);
    work('C', 20);

    fprintf(myOutput, "\n[C HIGH] trying to acquire mutex\n");
    printMutex.Acquire();
    fprintf(myOutput, "\n[C HIGH] acquired mutex\n");
    work('C', 30);
    fprintf(myOutput, "\n[C HIGH] releases mutex\n");
    printMutex.Release();
    fprintf(myOutput, "\n[C HIGH] finished\n");
}

void main()
{
    clrscr();
    myOutput = fopen("priority_inversion_test.txt", "w");

    if (myOutput == NULL)
    {
        cprintf("Error opening priority_inversion_test.txt");
        return;
    }

    fprintf(myOutput, "=== PRIORITY INVERSION TEST ===\n");
    fprintf(myOutput, "A = Low, B = Middle, C = High\n\n");

    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS);
    SMARTS.declareTask(highTask, 'C', 400, 1);
    SMARTS.declareTask(middleTask, 'B', 401, 1);
    SMARTS.declareTask(lowTask, 'A', 402, 1);
    SMARTS.runTheTasks();

    for (long i = 0; i < 60000000L; i++);

    fprintf(myOutput, "\n=== END ===\n");
    fclose(myOutput);
}

