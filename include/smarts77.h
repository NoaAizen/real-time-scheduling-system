// Based on the SMARTS77 framework by A. Teitelbaum,
// on an idea by H. G. Mendelbaum, Jerusalem College of Technology.

#ifndef SMARTS77_PART1_H
#define SMARTS77_PART1_H

#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <values.h>
#include <iostream.h>
#include <stdlib.h>

#define true 1
#define false 0
#define timerInt 0x08
#define userInt 0x60
#define MaxTask 15
#define MaxStack 512
enum taskStatus { READY, NOT_ACTIVE, SUSPENDED, SLEEP, UNDEFINED };

class Event
{
private:
    int  flag;
    void* data;
    char source;
    char dest;
    int senderWait;
    int testAndSet();
public:
    Event();

    void send(char dest, void* param, int synch);

    void* wait(char& sourceP);

    int arrived(char& sourceP);

    void reset();
};

// Framework task context, extended with Part 1 periodic-task state.
class Task
{
public:

    char name;
    unsigned stack[MaxStack];
    unsigned stackSeg, stackPtr;
    int currentPriority;
    int priority;
    taskStatus status;
    Event* expectedEvent;
    int sleepCount;
    // Each task preserves its own deferred context-switch state.
    int contextSwitchFlag;

    // Period and relative deadline use hardware timer ticks.
    int period;

    int remainingTime;

    // Requested cycles, remaining cycles, and completion of the current cycle.
    int numOfPeriod;

    int numOfPeriodRemaining;

    int didRunInCycle;

    Task();
    void declare(void far* code, void far* taskEnd, char name);
    void sleepDecr();
    void incrPriority();
    void setOriginalPriority();

    // Part 1: rebuild the initial task context for its next period.
    void reDeclare();
    // Preserve entry points for task reactivation.
    void far* taskCode;
    void far* taskEndCode;
};

class Parallelism
{
private:
    Task context[MaxTask];
    Task contextSched;
    unsigned schedCopy[MaxStack];
    int totalTasks;
    int currentTask;
    int deadlock;
    int progInt;
    int endOfTimeSlice;

    void interrupt(*timerInterruptHandler)(...);

    void interrupt(*userIntAddress)(...);
    void far* scheduler;
    void far* userTaskEnd;
public:
    int sleepTasks;
    int activeTasks;
    int traceInd;
    long TScount;
    unsigned timerClocksBegin;
    unsigned timerClocksEnd;
    int far(*algorithm)();
    Parallelism();

    void externalFunctions(void interrupt(*timerInterruptHandler)(...),
        void far* scheduler, void far* userTaskEnd,
        int far(*algorithm)());
    // Part 1: declare a periodic task with a finite number of cycles.
    int declareTask(void far* code, char name, int period, int numOfPeriods);
    void runTheTasks();
    void callScheduler();
    void restoreSchedStack();
    int getCurrentTask();
    void setCurrentTask(int taskNum);
    int getTotalTasks();
    int getDeadlock();
    void setDeadlock();
    int contextSwitchOn();
    void contextSwitchOff();
    int getContextSwitch();
    void setProgInt();
    void resetProgInt();
    int getProgInt();
    void setEndOfTimeSlice();
    char getName(int taskNum);
    char getCurrentName();
    taskStatus getStatus(int taskNum);
    taskStatus getCurrentStatus();
    void resume(int taskNum);
    void resume(char taskName);
    void setCurrentNotActive();
    void suspended();
    void incrPriority(int taskNum);
    void setOriginalPriority(int taskNum);
    void setCurrentOriginalPriority();
    Event* getExpectedEvent(int taskNum);
    Event* getCurrentExpectedEvent();
    void setCurrentExpectedEvent(Event* expectedEvent);
    void sleep(int t);
    void sleepDecr(int taskNum);
    void getCurrentStack(unsigned& StackSeg, unsigned& StackPtr);
    void setCurrentStack(unsigned StackSeg, unsigned StackPtr);
    void getSchedStack(unsigned& StackSeg, unsigned& StackPtr);
    // Update sleep timers and Part 1 deadlines on each hardware tick.
    void handleTimers();
    void taskEnd();
    // Part 1 completion helper called by taskEnd() for the current cycle.
    void markCurrentTaskRan();
    int getRemainingTime(int taskNum);
    int getDidRunInCycle(int taskNum);
    int getPeriod(int taskNum);
    // Base priority is derived from the period; current priority is reserved
    // for later priority-inheritance work.
    int getPriority(int taskNum);
    int getCurrentPriority(int taskNum);
    void setCurrentPriority(int taskNum, int priority);
};

extern unsigned getTimerClocks();

void far interrupt timerInterruptHandler(...);
void scheduler();
void myTaskEnd();

// Provided SMARTS77 scheduling policy.
int roundRobin();

// Part 1 scheduling policy: earliest deadline among READY tasks.
int EDF();

// Part 2 Stage 1 policy: select the READY task with the highest RMS priority.
int RMS();

// Part 2 mutual exclusion with optional direct priority inheritance.
class Mutex
{
private:
    int value;
    int owner;
    int waitingTasks[MaxTask];
    int waitingCount;
    int inheritanceEnabled;
public:
    Mutex();
    Mutex(int inheritance);
    void Acquire();
    void Release();
    int getHighestPriorityTask();
};

extern Parallelism SMARTS;

#endif
