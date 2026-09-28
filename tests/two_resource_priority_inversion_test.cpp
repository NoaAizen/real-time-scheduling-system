#include "smarts77.h"

// Set to 0 for the original no-inheritance mode or 1 for direct inheritance.
#ifndef USE_INHERITANCE
#define USE_INHERITANCE 0
#endif

Mutex firstResource(USE_INHERITANCE);
Mutex secondResource(USE_INHERITANCE);

Event wakeHighTask1;
Event wakeLowTask1;
Event wakeHighTask2;
Event wakeMiddleTask1;
Event wakeMiddleTask2;

FILE* myOutput;

void work(char ch, int times)
{
    for (int i = 0; i < times; i++)
    {
        fprintf(myOutput, "%c", ch);
        for (long d = 0; d < 10000L; d++);
        if (i % 20 == 0)
            SMARTS.callScheduler();
    }
    fflush(myOutput);
}

void highTask1()
{
    char source;
    fprintf(myOutput, "\n[HIGH TASK 1] waiting for event\n");
    wakeHighTask1.wait(source);
    fprintf(myOutput, "\n[HIGH TASK 1] trying to acquire first resource\n");
    firstResource.Acquire();
    fprintf(myOutput, "\n[HIGH TASK 1] acquired first resource\n");
    work('H', 30);
    fprintf(myOutput, "\n[HIGH TASK 1] releases first resource\n");
    firstResource.Release();
    fprintf(myOutput, "\n[HIGH TASK 1] finished\n");
}

void middleTask1()
{
    char source;
    fprintf(myOutput, "\n[MIDDLE TASK 1] waiting for event\n");
    wakeMiddleTask1.wait(source);
    fprintf(myOutput, "\n[MIDDLE TASK 1] long independent work\n");
    work('M', 300);
    fprintf(myOutput, "\n[MIDDLE TASK 1] finished\n");
}

void lowTask1()
{
    char source;
    fprintf(myOutput, "\n[LOW TASK 1] waiting for event\n");
    wakeLowTask1.wait(source);
    fprintf(myOutput, "\n[LOW TASK 1] acquiring first resource\n");
    firstResource.Acquire();
    fprintf(myOutput, "\n[LOW TASK 1] acquired first resource\n");
    fprintf(myOutput, "\n[LOW TASK 1] wakes HIGH TASK 1 and MIDDLE TASK 1\n");
    wakeHighTask1.send('H', NULL, false);
    wakeMiddleTask1.send('M', NULL, false);
    work('L', 120);
    fprintf(myOutput, "\n[LOW TASK 1] releases first resource\n");
    firstResource.Release();
    work('L', 20);
    fprintf(myOutput, "\n[LOW TASK 1] finished\n");
}

void highTask2()
{
    char source;
    fprintf(myOutput, "\n[HIGH TASK 2] waiting for event\n");
    wakeHighTask2.wait(source);
    fprintf(myOutput, "\n[HIGH TASK 2] trying to acquire second resource\n");
    secondResource.Acquire();
    fprintf(myOutput, "\n[HIGH TASK 2] acquired second resource\n");
    work('X', 30);
    fprintf(myOutput, "\n[HIGH TASK 2] releases second resource\n");
    secondResource.Release();
    fprintf(myOutput, "\n[HIGH TASK 2] finished\n");
}

void middleTask2()
{
    char source;
    fprintf(myOutput, "\n[MIDDLE TASK 2] waiting for event\n");
    wakeMiddleTask2.wait(source);
    fprintf(myOutput, "\n[MIDDLE TASK 2] long independent work\n");
    work('N', 300);
    fprintf(myOutput, "\n[MIDDLE TASK 2] finished\n");
}

void lowTask2()
{
    fprintf(myOutput, "\n[LOW TASK 2] started\n");
    fprintf(myOutput, "\n[LOW TASK 2] acquiring second resource\n");
    secondResource.Acquire();
    fprintf(myOutput, "\n[LOW TASK 2] acquired second resource\n");
    fprintf(myOutput, "\n[LOW TASK 2] wakes LOW TASK 1\n");
    wakeLowTask1.send('L', NULL, false);
    work('Z', 40);
    fprintf(myOutput, "\n[LOW TASK 2] wakes HIGH TASK 2 and MIDDLE TASK 2\n");
    wakeHighTask2.send('X', NULL, false);
    wakeMiddleTask2.send('N', NULL, false);
    work('Z', 120);
    fprintf(myOutput, "\n[LOW TASK 2] releases second resource\n");
    secondResource.Release();
    work('Z', 20);
    fprintf(myOutput, "\n[LOW TASK 2] finished\n");
}

void main()
{
    clrscr();
    myOutput = fopen("two_resources_test.txt", "w");

    if (myOutput == NULL)
    {
        cout << "\nError opening two_resources_test.txt";
        return;
    }

    fprintf(myOutput, "=== TWO RESOURCES PRIORITY INVERSION TEST ===\n");
    fprintf(myOutput, "USE_INHERITANCE = %d\n\n", USE_INHERITANCE);

    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS);
    SMARTS.declareTask(highTask1, 'H', 400, 1);
    SMARTS.declareTask(middleTask1, 'M', 401, 1);
    SMARTS.declareTask(lowTask1, 'L', 402, 1);
    SMARTS.declareTask(highTask2, 'X', 403, 1);
    SMARTS.declareTask(middleTask2, 'N', 404, 1);
    SMARTS.declareTask(lowTask2, 'Z', 405, 1);
    SMARTS.runTheTasks();

    for (long i = 0; i < 60000000L; i++);

    fprintf(myOutput, "\n=== END ===\n");
    fclose(myOutput);
}
