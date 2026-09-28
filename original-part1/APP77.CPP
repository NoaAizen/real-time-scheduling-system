
#include "smarts77.h"

// user Functions
void a()
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   A Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j = 0; j < 500; j++)
	{
		// simulate CPU work
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
		// simulate CPU work
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
		// simulate CPU work
		for (long i = 0; i < 600000; i++);
		SMARTS.contextSwitchOff();
		cout << "C";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Finish   *********************";
	SMARTS.contextSwitchOn();
}

void main()
{
	clrscr();
	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, roundRobin);

	// very short deadlines expected to fail for both RR and EDF

	//SMARTS.declareTask(a, 'A', 100, 3);
	//SMARTS.declareTask(b, 'B', 150, 3);
	//SMARTS.declareTask(c, 'C', 200, 3);

	// EDF complete , RR fail task A has the earliest deadline
	//SMARTS.declareTask(a, 'A', 3000, 3);
	//SMARTS.declareTask(b, 'B', 9000, 3);
	//SMARTS.declareTask(c, 'C', 12000, 3);
	// balanced  all tasks are expected to complete successfully

	/*SMARTS.declareTask(a, 'A', 7000, 3);
	SMARTS.declareTask(b, 'B', 5000, 3);
	SMARTS.declareTask(c, 'C', 9000, 3);*/
	SMARTS.runTheTasks();
	for (long i = 0; i < 60000000; i++);
}


