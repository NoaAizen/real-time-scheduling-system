#include "smarts77.h"

// Choose one configuration and rebuild. Original expectations are unverified.
#define SCENARIO_SHORT_DEADLINES 1
#define SCENARIO_EDF_VS_RR 2
#define SCENARIO_BALANCED 3
#define SCENARIO_RMS_EQUAL_PERIODS 4
#define SCENARIO_RMS_HARMONIC_PERIODS 5

#ifndef SCHEDULING_SCENARIO
#define SCHEDULING_SCENARIO SCENARIO_BALANCED
#endif

#ifndef SCHEDULING_POLICY
#if SCHEDULING_SCENARIO == SCENARIO_RMS_EQUAL_PERIODS || SCHEDULING_SCENARIO == SCENARIO_RMS_HARMONIC_PERIODS
#define SCHEDULING_POLICY RMS
#else
#define SCHEDULING_POLICY roundRobin
#endif
#endif

void a()
{
    SMARTS.contextSwitchOff(); cout << "\nA Start"; SMARTS.contextSwitchOn();
    for (int j = 0; j < 500; j++)
    {
        for (long i = 0; i < 600000L; i++);
        SMARTS.contextSwitchOff(); cout << "A"; SMARTS.contextSwitchOn();
    }
    SMARTS.contextSwitchOff(); cout << "\nA Finish"; SMARTS.contextSwitchOn();
}

void b()
{
    SMARTS.contextSwitchOff(); cout << "\nB Start"; SMARTS.contextSwitchOn();
    for (int j = 0; j < 500; j++)
    {
        for (long i = 0; i < 600000L; i++);
        SMARTS.contextSwitchOff(); cout << "B"; SMARTS.contextSwitchOn();
    }
    SMARTS.contextSwitchOff(); cout << "\nB Finish"; SMARTS.contextSwitchOn();
}

void c()
{
    SMARTS.contextSwitchOff(); cout << "\nC Start"; SMARTS.contextSwitchOn();
    for (int j = 0; j < 500; j++)
    {
        for (long i = 0; i < 600000L; i++);
        SMARTS.contextSwitchOff(); cout << "C"; SMARTS.contextSwitchOn();
    }
    SMARTS.contextSwitchOff(); cout << "\nC Finish"; SMARTS.contextSwitchOn();
}

void main()
{
    clrscr();
    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd,
        SCHEDULING_POLICY);

#if SCHEDULING_SCENARIO == SCENARIO_SHORT_DEADLINES
    SMARTS.declareTask(a, 'A', 100, 3);
    SMARTS.declareTask(b, 'B', 150, 3);
    SMARTS.declareTask(c, 'C', 200, 3);
#elif SCHEDULING_SCENARIO == SCENARIO_EDF_VS_RR
    SMARTS.declareTask(a, 'A', 3000, 3);
    SMARTS.declareTask(b, 'B', 9000, 3);
    SMARTS.declareTask(c, 'C', 12000, 3);
#elif SCHEDULING_SCENARIO == SCENARIO_RMS_EQUAL_PERIODS
    SMARTS.declareTask(a, 'A', 1000, 3);
    SMARTS.declareTask(b, 'B', 1000, 3);
    SMARTS.declareTask(c, 'C', 1000, 3);
#elif SCHEDULING_SCENARIO == SCENARIO_RMS_HARMONIC_PERIODS
    SMARTS.declareTask(a, 'A', 5000, 5);
    SMARTS.declareTask(b, 'B', 10000, 5);
    SMARTS.declareTask(c, 'C', 20000, 5);
#else
    SMARTS.declareTask(a, 'A', 7000, 3);
    SMARTS.declareTask(b, 'B', 5000, 3);
    SMARTS.declareTask(c, 'C', 9000, 3);
#endif

    SMARTS.runTheTasks();
    for (long i = 0; i < 60000000L; i++);
}
