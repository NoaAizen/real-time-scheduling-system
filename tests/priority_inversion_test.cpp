#include "smarts77.h"

#define ONE_RESOURCE 1
#define TWO_RESOURCES 2
#ifndef INVERSION_SCENARIO
#define INVERSION_SCENARIO ONE_RESOURCE
#endif
#ifndef USE_INHERITANCE
#define USE_INHERITANCE 0
#endif

Mutex resource1(USE_INHERITANCE);
Mutex resource2(USE_INHERITANCE);
Event wakeHigh1, wakeLow1, wakeHigh2, wakeMiddle1, wakeMiddle2;
FILE* output;

void work(char mark, int count, int yieldToScheduler = true)
{
    for (int i = 0; i < count; i++)
    {
        fprintf(output, "%c", mark);
        for (long delay = 0; delay < 10000L; delay++);
        if (yieldToScheduler && i % 20 == 0)
            SMARTS.callScheduler();
    }
    fflush(output);
}

// One-resource experiment: low owns the mutex, high blocks, middle runs.
void oneLow()
{
    resource1.Acquire(); work('a', 20, false);
    wakeMiddle1.send('B', NULL, false); wakeHigh1.send('C', NULL, false);
    work('a', 120, false); resource1.Release(); work('a', 20, false);
}
void oneMiddle()
{
    char source; wakeMiddle1.wait(source); work('B', 300);
}
void oneHigh()
{
    char source; wakeHigh1.wait(source); work('C', 20, false);
    resource1.Acquire(); work('C', 30, false); resource1.Release();
}

// Two-resource experiment: each low task holds a resource before waking peers.
void high1()
{
    char source; wakeHigh1.wait(source);
    resource1.Acquire(); work('H', 30); resource1.Release();
}
void middle1()
{
    char source; wakeMiddle1.wait(source); work('M', 300);
}
void low1()
{
    char source; wakeLow1.wait(source);
    resource1.Acquire();
    wakeHigh1.send('H', NULL, false); wakeMiddle1.send('M', NULL, false);
    work('L', 120); resource1.Release(); work('L', 20);
}
void high2()
{
    char source; wakeHigh2.wait(source);
    resource2.Acquire(); work('X', 30); resource2.Release();
}
void middle2()
{
    char source; wakeMiddle2.wait(source); work('N', 300);
}
void low2()
{
    resource2.Acquire(); wakeLow1.send('L', NULL, false); work('Z', 40);
    wakeHigh2.send('X', NULL, false); wakeMiddle2.send('N', NULL, false);
    work('Z', 120); resource2.Release(); work('Z', 20);
}

void main()
{
    clrscr();
#if INVERSION_SCENARIO == TWO_RESOURCES
    output = fopen("two_resources_test.txt", "w");
#else
    output = fopen("priority_inversion_test.txt", "w");
#endif
    if (output == NULL)
        return;

    fprintf(output, "Priority inversion scenario; inheritance = %d\n",
        USE_INHERITANCE);
    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS);

#if INVERSION_SCENARIO == TWO_RESOURCES
    SMARTS.declareTask(high1, 'H', 400, 1);
    SMARTS.declareTask(middle1, 'M', 401, 1);
    SMARTS.declareTask(low1, 'L', 402, 1);
    SMARTS.declareTask(high2, 'X', 403, 1);
    SMARTS.declareTask(middle2, 'N', 404, 1);
    SMARTS.declareTask(low2, 'Z', 405, 1);
#else
    SMARTS.declareTask(oneHigh, 'C', 400, 1);
    SMARTS.declareTask(oneMiddle, 'B', 401, 1);
    SMARTS.declareTask(oneLow, 'A', 402, 1);
#endif
    SMARTS.runTheTasks();
    for (long i = 0; i < 60000000L; i++);
    fclose(output);
}
