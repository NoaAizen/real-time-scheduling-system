#include "smarts77.h"
#include "task_workloads.h"

// Shared A/B/C workloads extracted from the Part 1 application.
// Preserve loop counts, output, and context-switch calls for comparison.

void a()
{
    SMARTS.contextSwitchOff();
    cout << "\n *************   A Start    *********************";
    SMARTS.contextSwitchOn();
    for (int j = 0; j < 500; j++)
    {

        for (long i = 0; i < 600000; i++);
        SMARTS.contextSwitchOff();
        cout << "A";
        SMARTS.contextSwitchOn();
    }
    SMARTS.contextSwitchOff();
    cout << "\n *************   A Finish   *********************";
    SMARTS.contextSwitchOn();
}

void b()
{
    SMARTS.contextSwitchOff();
    cout << "\n *************   B Start    *********************";
    SMARTS.contextSwitchOn();
    for (int j = 0; j < 500; j++)
    {

        for (long i = 0; i < 600000; i++);
        SMARTS.contextSwitchOff();
        cout << "B";
        SMARTS.contextSwitchOn();
    }
    SMARTS.contextSwitchOff();
    cout << "\n *************   B Finish   *********************";
    SMARTS.contextSwitchOn();
}

void c()
{
    SMARTS.contextSwitchOff();
    cout << "\n *************   C Start    *********************";
    SMARTS.contextSwitchOn();
    for (int j = 0; j < 500; j++)
    {

        for (long i = 0; i < 600000; i++);
        SMARTS.contextSwitchOff();
        cout << "C";
        SMARTS.contextSwitchOn();
    }
    SMARTS.contextSwitchOff();
    cout << "\n *************   C Finish   *********************";
    SMARTS.contextSwitchOn();
}
