// Based on the SMARTS77 framework by A. Teitelbaum,
// on an idea by H. G. Mendelbaum, Jerusalem College of Technology.

#include "smarts77.h"

// Read the remaining count from the hardware timer.
unsigned getTimerClocks()

{
    unsigned clocks;

    outportb(0x43, 0x00);

    clocks = inportb(0x40);

    clocks += inportb(0x40) << 8;
    return clocks;
}

Parallelism::Parallelism()
{
    currentTask = 0;
    sleepTasks = 0;
    activeTasks = 0;
    totalTasks = 0;
    deadlock = false;
    contextSwitchFlag = true;
    endOfTimeSlice = true;
}

void Parallelism::externalFunctions(void interrupt(*timerInterruptHandler)(...),
    void far* scheduler, void far* userTaskEnd,
    int far(*algorithm)())

{
    this->timerInterruptHandler = timerInterruptHandler;
    this->scheduler = scheduler;
    this->userTaskEnd = userTaskEnd;
    this->algorithm = algorithm;
    contextSched.declare(scheduler, userTaskEnd, 'S');
    for (int i = MaxStack - 1; i >= (MaxStack - 14); i--)
        schedCopy[i] = contextSched.stack[i];
}

// Part 1: initialize the period, deadline counter, and requested cycle count.
int Parallelism::declareTask(void far* code, char name, int period, int numOfPeriods)
{
    if (totalTasks < MaxTask - 1)
    {
        context[totalTasks].declare(code, userTaskEnd, name);

        context[totalTasks].period = period;

        context[totalTasks].remainingTime = period;

        context[totalTasks].numOfPeriod = numOfPeriods;

        context[totalTasks].numOfPeriodRemaining = numOfPeriods;

        context[totalTasks].didRunInCycle = 0;

        totalTasks++;
        activeTasks++;
        return true;
    }
    return false;
}

// Install the framework interrupt handler and restore vectors on normal return.
void Parallelism::runTheTasks()

{
    context[totalTasks].status = READY;
    context[totalTasks].priority = MAXINT;
    context[totalTasks].currentPriority = MAXINT;

    currentTask = totalTasks;

    asm    cli;

    userIntAddress = getvect(userInt);

    setvect(userInt, getvect(timerInt));

    setvect(timerInt, timerInterruptHandler);
    asm    sti;

    while (true)
    {
        if (deadlock)
        {
            textcolor(RED);
            cprintf("\n\n\rExit : deadlock");
            break;
        }
        if (activeTasks == 0)
        {
            cprintf("\n\n\rExit : finish");
            break;
        }
    }

    asm    cli;
    setvect(timerInt, getvect(userInt));
    setvect(userInt, userIntAddress);
    asm    sti;
}

// Request scheduling through the timer interrupt without advancing task timers.
void Parallelism::callScheduler()

{
    setProgInt();
    asm int timerInt;
}

void Parallelism::restoreSchedStack()

{
    for (int i = MaxStack - 1; i >= (MaxStack - 14); i--)
        contextSched.stack[i] = schedCopy[i];
}

int Parallelism::getCurrentTask()
{
    return currentTask;
}

void Parallelism::setCurrentTask(int taskNum)

{
    if (taskNum <= totalTasks)
        currentTask = taskNum;
}

int Parallelism::getTotalTasks()

{
    return totalTasks;
}

int Parallelism::getDeadlock()
{
    return deadlock;
}

void Parallelism::setDeadlock()
{
    deadlock = true;
}

// Re-enable switching and service a previously recorded scheduling request.
int Parallelism::contextSwitchOn()

{
    if (endOfTimeSlice)
    {
        endOfTimeSlice = false;
        contextSwitchFlag = true;
        callScheduler();
        return 1;
    }
    contextSwitchFlag = true;
    return 0;
}

// Suppress task switching; hardware timer processing remains enabled.
void Parallelism::contextSwitchOff()

{
    contextSwitchFlag = false;
}

int Parallelism::getContextSwitch()
{
    return contextSwitchFlag;
}

void Parallelism::setProgInt()

{
    progInt = true;
}

void Parallelism::resetProgInt()
{
    progInt = false;
}

int Parallelism::getProgInt()
{
    return progInt;
}

void Parallelism::setEndOfTimeSlice()

{
    endOfTimeSlice = true;
}

char Parallelism::getName(int taskNum)
{
    return (taskNum <= totalTasks) ? context[taskNum].name : ' ';
}

char Parallelism::getCurrentName()
{
    return context[currentTask].name;
}

taskStatus Parallelism::getStatus(int taskNum)

{
    return (taskNum <= totalTasks) ? context[taskNum].status : UNDEFINED;
}

taskStatus Parallelism::getCurrentStatus()
{
    return context[currentTask].status;
}

void Parallelism::resume(int taskNum)
{
    if (taskNum < totalTasks)
        context[taskNum].status = READY;
}

void Parallelism::resume(char taskName)
{
    for (int i = 0; i < totalTasks; ++i)
        if (context[i].name == taskName)
            context[i].status = READY;
}

// Preserve baseline accounting: marking a task inactive decrements activeTasks.
void Parallelism::setCurrentNotActive()
{
    context[currentTask].status = NOT_ACTIVE;
    --activeTasks;
}
void Parallelism::suspended()
{
    context[currentTask].status = SUSPENDED;
    callScheduler();
}

void Parallelism::incrPriority(int taskNum)
{
    if (taskNum < totalTasks)
        context[taskNum].incrPriority();
}
void Parallelism::setOriginalPriority(int taskNum)
{
    if (taskNum < totalTasks)
        context[taskNum].setOriginalPriority();
}

void Parallelism::setCurrentOriginalPriority()
{
    context[currentTask].setOriginalPriority();
}

Event* Parallelism::getExpectedEvent(int taskNum)

{
    return (taskNum <= totalTasks) ? context[taskNum].expectedEvent : NULL;
}

Event* Parallelism::getCurrentExpectedEvent()
{
    return context[currentTask].expectedEvent;
}

void Parallelism::setCurrentExpectedEvent(Event* expectedEvent)
{
    context[currentTask].expectedEvent = expectedEvent;
}

// Convert milliseconds to the framework's approximate 55 ms timer ticks.
void Parallelism::sleep(int t)

{
    if (t < MAXINT)
    {
        context[currentTask].sleepCount = t / 55 + 1;
        context[currentTask].status = SLEEP;
        ++sleepTasks;
        callScheduler();
    }
}

void Parallelism::sleepDecr(int taskNum)
{
    if (taskNum < totalTasks)
        context[taskNum].sleepDecr();
}

void Parallelism::getCurrentStack(unsigned& StackSeg, unsigned& StackPtr)

{
    StackSeg = context[currentTask].stackSeg;
    StackPtr = context[currentTask].stackPtr;
}

void Parallelism::setCurrentStack(unsigned StackSeg, unsigned StackPtr)

{
    context[currentTask].stackSeg = StackSeg;
    context[currentTask].stackPtr = StackPtr;
}

void Parallelism::getSchedStack(unsigned& StackSeg, unsigned& StackPtr)

{
    StackSeg = contextSched.stackSeg;
    StackPtr = contextSched.stackPtr;
}

// Part 1: check cycle deadlines and reactivate tasks at period boundaries.
// Preserve the baseline getch()/exit(1) path on a missed deadline.
void Parallelism::handleTimers()
{
    for (int i = totalTasks - 1; i >= 0; --i)
    {
        if (context[i].numOfPeriodRemaining == 0)
            continue;

        if (getStatus(i) == SLEEP)
        {
            sleepDecr(i);
            if (getStatus(i) == READY)
                --sleepTasks;
        }

        context[i].remainingTime--;

        if (context[i].remainingTime == 0)
        {

            if (context[i].didRunInCycle == 0)
            {
                cout << "\nERROR: task ";
                cout << context[i].name;
                cout << " missed deadline";
                cout << "\nPress any key to exit...";

                getch();
                exit(1);
            }

            context[i].numOfPeriodRemaining--;

            if (context[i].numOfPeriodRemaining == 0)
            {
                context[i].status = NOT_ACTIVE;
                activeTasks--;
            }
            else
            {

                context[i].reDeclare();
            }
        }
    }
}

// Complete this cycle and wait for the period boundary without retiring the task.
void Parallelism::taskEnd()
{

    SMARTS.markCurrentTaskRan();
    context[currentTask].status = NOT_ACTIVE;

    SMARTS.callScheduler();
}

// Part 1: record completion of the current cycle.
void Parallelism::markCurrentTaskRan()
{
    context[currentTask].didRunInCycle = 1;
}
int Parallelism::getRemainingTime(int taskNum)
{
    return context[taskNum].remainingTime;
}

int Parallelism::getDidRunInCycle(int taskNum)
{
    return context[taskNum].didRunInCycle;
}

int Parallelism::getPeriod(int taskNum)
{
    return context[taskNum].period;
}

Task::Task()
{
    stack[MaxStack - 14] = _BP;
    stack[MaxStack - 13] = _DI;
    stack[MaxStack - 12] = _SI;
    stack[MaxStack - 11] = _DS;
    stack[MaxStack - 10] = _ES;
    stack[MaxStack - 9] = _DX;
    stack[MaxStack - 8] = _CX;
    stack[MaxStack - 7] = _BX;
    stack[MaxStack - 6] = _AX;
    stackSeg = FP_SEG(&stack[MaxStack - 14]);
    stackPtr = FP_OFF(&stack[MaxStack - 14]);
    status = NOT_ACTIVE;
    sleepCount = 0;
    currentPriority = priority = 0;
}

// Save entry points used both for initial execution and periodic reactivation.
void Task::declare(void far* code, void far* userTaskEnd, char name)
{
    taskCode = code;
    taskEndCode = userTaskEnd;

    stack[MaxStack - 5] = FP_OFF(code);
    stack[MaxStack - 4] = FP_SEG(code);
    stack[MaxStack - 3] = _FLAGS;
    stack[MaxStack - 2] = FP_OFF(userTaskEnd);
    stack[MaxStack - 1] = FP_SEG(userTaskEnd);

    this->name = name;
    status = READY;
}

void Task::incrPriority()
{
    --currentPriority;
}

void Task::setOriginalPriority()
{
    currentPriority = priority;
}

void Task::sleepDecr()

{
    if (status == SLEEP)
    {
        if (sleepCount > 0)
            --sleepCount;
        if (!sleepCount)
            status = READY;
    }
}
// Part 1: rebuild the task stack and reset timing state for the next cycle.
void Task::reDeclare()
{
    stack[MaxStack - 14] = _BP;
    stack[MaxStack - 13] = _DI;
    stack[MaxStack - 12] = _SI;
    stack[MaxStack - 11] = _DS;
    stack[MaxStack - 10] = _ES;
    stack[MaxStack - 9] = _DX;
    stack[MaxStack - 8] = _CX;
    stack[MaxStack - 7] = _BX;
    stack[MaxStack - 6] = _AX;

    stack[MaxStack - 5] = FP_OFF(taskCode);
    stack[MaxStack - 4] = FP_SEG(taskCode);
    stack[MaxStack - 3] = _FLAGS;
    stack[MaxStack - 2] = FP_OFF(taskEndCode);
    stack[MaxStack - 1] = FP_SEG(taskEndCode);

    stackSeg = FP_SEG(&stack[MaxStack - 14]);
    stackPtr = FP_OFF(&stack[MaxStack - 14]);

    remainingTime = period;

    didRunInCycle = 0;

    status = READY;
}
