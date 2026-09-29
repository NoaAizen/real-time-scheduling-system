// Based on the SMARTS77 framework by A. Teitelbaum,
// on an idea by H. G. Mendelbaum, Jerusalem College of Technology.

#ifndef SMARTS77_H
#define SMARTS77_H

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

// Provided SMARTS77 task context.
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

    Task();
    void declare(void far* code, void far* taskEnd, char name);
    void sleepDecr();
    void incrPriority();
    void setOriginalPriority();


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
    int contextSwitchFlag;
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
    // Declare a task that runs once.
    int declareTask(void far* code, char name);
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
    // Update sleeping tasks on each hardware tick.
    void handleTimers();
    void taskEnd();

};

extern unsigned getTimerClocks();

void far interrupt timerInterruptHandler(...);
void scheduler();
void myTaskEnd();

// Provided SMARTS77 scheduling policy.
int roundRobin();


extern Parallelism SMARTS;

#endif
