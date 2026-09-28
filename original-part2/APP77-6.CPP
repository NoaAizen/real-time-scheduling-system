//#include "smarts77.h"
//void a()
//{
//	SMARTS.contextSwitchOff();
//	cout << "\n *************   A Start    *********************";
//	SMARTS.contextSwitchOn();
//	for (int j = 0; j < 500; j++)
//	{
//		// simulate CPU work
//		for (long i = 0; i < 600000; i++);
//
//		SMARTS.contextSwitchOff();
//		cout << "A";
//		SMARTS.contextSwitchOn();
//	}
//	SMARTS.contextSwitchOff();
//	cout << "\n *************   A Finish   *********************";
//	SMARTS.contextSwitchOn();
//}
//
//void b()
//{
//	SMARTS.contextSwitchOff();
//	cout << "\n *************   B Start    *********************";
//	SMARTS.contextSwitchOn();
//	for (int j = 0; j < 500; j++)
//	{
//		// simulate CPU work
//
//		for (long i = 0; i < 600000; i++);
//		SMARTS.contextSwitchOff();
//		cout << "B";
//		SMARTS.contextSwitchOn();
//	}
//	SMARTS.contextSwitchOff();
//	cout << "\n *************   B Finish   *********************";
//	SMARTS.contextSwitchOn();
//}
//
//void c()
//{
//	SMARTS.contextSwitchOff();
//	cout << "\n *************   C Start    *********************";
//	SMARTS.contextSwitchOn();
//	for (int j = 0; j < 500; j++)
//	{
//		// simulate CPU work
//		for (long i = 0; i < 600000; i++);
//		SMARTS.contextSwitchOff();
//		cout << "C";
//		SMARTS.contextSwitchOn();
//	}
//	SMARTS.contextSwitchOff();
//	cout << "\n *************   C Finish   *********************";
//	SMARTS.contextSwitchOn();
//}
//
//void main()
//{
//	clrscr();
//	SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS);
//    
//    //rms not work
//	//SMARTS.declareTask(a, 'A', 1000, 3);
//	//SMARTS.declareTask(b, 'B', 1000, 3);
//	//SMARTS.declareTask(c, 'C', 1000, 3);
//
//	//rms work
//	//SMARTS.declareTask(a, 'A', 5000 ,5);
//	//SMARTS.declareTask(b, 'B', 10000, 5);
//	//SMARTS.declareTask(c, 'C', 20000, 5);
//
//	// very short deadlines expected to fail for both RR and EDF AND rms*/
//
//	/*SMARTS.declareTask(a, 'A', 100, 3);
//	SMARTS.declareTask(b, 'B', 150, 3);
//	SMARTS.declareTask(c, 'C', 200, 3);*/
//
//	// EDF complete , RR fail task A has the earliest deadline and RMS complete
//	/*SMARTS.declareTask(a, 'A', 3000, 3);
//	SMARTS.declareTask(b, 'B', 9000, 3);
//	SMARTS.declareTask(c, 'C', 12000, 3);*/
//
//	// balanced  all tasks are expected to complete successfully and RMS  complete
//
//	SMARTS.declareTask(a, 'A', 7000, 3);
//	SMARTS.declareTask(b, 'B', 5000, 3);
//	SMARTS.declareTask(c, 'C', 9000, 3);
//	SMARTS.runTheTasks();
//	for (long i = 0; i < 60000000; i++);
//}
//
//





/////////////////////////////////////////////��� �////////////////////////////////////////////////////////

//#include "smarts77.h"
//
//
//Mutex printMutex;
//
//void a()
//{
//    printMutex.Acquire();
//    cout << "\nA Start";
//
//    for (int j = 0; j < 30; j++)
//    {
//        for (long i = 0; i < 80000; i++);
//        cout << "A";
//    }
//
//    cout << "\nA Finish";
//    printMutex.Release();
//}
//
//void b()
//{
//    printMutex.Acquire();
//    cout << "\nB Start";
//
//    for (int j = 0; j < 30; j++)
//    {
//        for (long i = 0; i < 80000; i++);
//        cout << "B";
//    }
//
//    cout << "\nB Finish";
//    printMutex.Release();
//}
//
//void c()
//{
//    printMutex.Acquire();
//    cout << "\nC Start";
//
//    for (int j = 0; j < 30; j++)
//    {
//        for (long i = 0; i < 80000; i++);
//        cout << "C";
//    }
//
//    cout << "\nC Finish";
//    printMutex.Release();
//}
//
//void main()
//{
//    clrscr();
//
//    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, RMS);
//
//    SMARTS.declareTask(a, 'A', 400, 3);
//    SMARTS.declareTask(b, 'B', 401, 3);
//    SMARTS.declareTask(c, 'C', 402, 3);
//
//    SMARTS.runTheTasks();
//
//    for (long i = 0; i < 60000000; i++);
//}
// 
// 
//// 
//////////////////////////////////////////////////////////////////////////////////��� 3 1+2
//
//#include "smarts77.h"
//
//#define USE_INHERITANCE 1
//
//Mutex printMutex(USE_INHERITANCE);
//
//Event eventToB;
//Event eventToC;
//
//FILE* myOutput;
//
//void work(char ch, int times)
//{
//    for (int i = 0; i < times; i++)
//    {
//        fprintf(myOutput, "%c", ch);
//
//        for (long d = 0; d < 10000L; d++);
//    }
//
//    fflush(myOutput);
//}
//
//
//
//
//void a()
//{
//    fprintf(myOutput, "\n[A LOW] started\n");
//
//    printMutex.Acquire();
//
//    fprintf(myOutput, "\n[A LOW] acquired mutex\n");
//
//    work('a', 20);
//
//    fprintf(myOutput, "\n[A LOW] sends event to B\n");
//    eventToB.send('B', NULL, false);
//
//    fprintf(myOutput, "\n[A LOW] sends event to C\n");
//    eventToC.send('C', NULL, false);
//
//    work('a', 120);
//
//    fprintf(myOutput, "\n[A LOW] releases mutex\n");
//
//    printMutex.Release();
//    work('a', 20);
//
//    fprintf(myOutput, "\n[A LOW] finished\n");
//}
//
//void b()
//{
//    char source;
//
//    fprintf(myOutput, "\n[B MID] waiting for event\n");
//
//    eventToB.wait(source);
//
//    fprintf(myOutput,
//        "\n[B MID] got event from %c\n",
//        source);
//
//    for (int i = 0; i < 300; i++)
//    {
//        fprintf(myOutput, "B");
//
//        for (long d = 0; d < 10000L; d++);
//
//        if (i % 20 == 0)
//            SMARTS.callScheduler();
//    }
//
//    fprintf(myOutput, "\n[B MID] finished\n");
//}
//void c()
//{
//    char source;
//
//    fprintf(myOutput, "\n[C HIGH] waiting for event\n");
//
//    eventToC.wait(source);
//
//    fprintf(myOutput,
//        "\n[C HIGH] got event from %c\n",
//        source);
//
//    work('C', 20);
//
//    fprintf(myOutput,
//        "\n[C HIGH] trying to acquire mutex\n");
//
//    printMutex.Acquire();
//
//    fprintf(myOutput,
//        "\n[C HIGH] acquired mutex\n");
//
//    work('C', 30);
//
//    fprintf(myOutput,
//        "\n[C HIGH] releases mutex\n");
//
//    printMutex.Release();
//
//    fprintf(myOutput,
//        "\n[C HIGH] finished\n");
//}
//
//
//
//void main()
//{
//    clrscr();
//
//    myOutput = fopen("Testnyes inheritance.txt", "w");
//
//    if (myOutput == NULL)
//    {
//        cprintf("Error opening test.txt");
//        return;
//    }
//
//    fprintf(myOutput, "=== Priority Inversion Test ===\n");
//    fprintf(myOutput, "USE_INHERITANCE = %d\n", USE_INHERITANCE);
//    fprintf(myOutput, "A = Low, B = Middle, C = High\n\n");
//
//    SMARTS.externalFunctions(
//        timerInterruptHandler,
//        scheduler,
//        myTaskEnd,
//        RMS
//    );
//
//    SMARTS.declareTask(c, 'C', 400, 1);
//    SMARTS.declareTask(b, 'B', 401, 1);
//    SMARTS.declareTask(a, 'A', 402, 1);
//
//    SMARTS.runTheTasks();
//
//    for (long i = 0; i < 60000000L; i++);
//
//    fprintf(myOutput, "\n=== END ===\n");
//    fclose(myOutput);
//}
//


#include "smarts77.h"

#define USE_INHERITANCE 0


Mutex firstResource(USE_INHERITANCE);
Mutex secondResource(USE_INHERITANCE);

Event wakeHighTask1;
Event wakeLowTask1;
Event wakeHighTask2;
Event wakeMiddleTask1;
Event wakeMiddleTask2;

FILE* myOutput;

// simulate work
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

//High task.
//Waits for event and then uses resource 1.
void high1()
{
    char source;

    fprintf(myOutput,
        "\n[HIGH TASK 1] waiting for event\n");

    wakeHighTask1.wait(source);

    fprintf(myOutput,
        "\n[HIGH TASK 1] trying to acquire first resource\n");

    // may wait if resource is busy
    firstResource.Acquire();

    fprintf(myOutput,
        "\n[HIGH TASK 1] acquired first resource\n");

    work('H', 30);

    fprintf(myOutput,
        "\n[HIGH TASK 1] releases first resource\n");

    firstResource.Release();

    fprintf(myOutput,
        "\n[HIGH TASK 1] finished\n");
}


//Middle task
//Does not use shared resources

void middle1()
{
    char source;

    fprintf(myOutput,
        "\n[MIDDLE TASK 1] waiting for event\n");

    wakeMiddleTask1.wait(source);

    fprintf(myOutput,
        "\n[MIDDLE TASK 1] long independent work\n");
    // long work
    work('M', 300);

    fprintf(myOutput,
        "\n[MIDDLE TASK 1] finished\n");
}


//low task takes resource 1 and wakes other tasks

void low1()
{
    char source;

    fprintf(myOutput,
        "\n[LOW TASK 1] waiting for event\n");

    wakeLowTask1.wait(source);

    fprintf(myOutput,
        "\n[LOW TASK 1] acquiring first resource\n");

    firstResource.Acquire();

    //resource 1 is locked by low task 1

    fprintf(myOutput,
        "\n[LOW TASK 1] acquired first resource\n");

    fprintf(myOutput,
        "\n[LOW TASK 1] wakes HIGH TASK 1 and MIDDLE TASK 1\n");

    // wake the othr tasks
    wakeHighTask1.send('H', NULL, false);
    wakeMiddleTask1.send('M', NULL, false);

    work('L', 120);

    fprintf(myOutput,
        "\n[LOW TASK 1] releases first resource\n");

    firstResource.Release();

    work('L', 20);

    fprintf(myOutput,
        "\n[LOW TASK 1] finished\n");
}


//high task waits for event and uses resource 2
void high2()
{
    char source;

    fprintf(myOutput,
        "\n[HIGH TASK 2] waiting for event\n");

    wakeHighTask2.wait(source);

    fprintf(myOutput,
        "\n[HIGH TASK 2] trying to acquire second resource\n");

    secondResource.Acquire();

    fprintf(myOutput,
        "\n[HIGH TASK 2] acquired second resource\n");

    work('X', 30);

    fprintf(myOutput,
        "\n[HIGH TASK 2] releases second resource\n");

    secondResource.Release();

    fprintf(myOutput,
        "\n[HIGH TASK 2] finished\n");
}


// Middle task Only does CPU work
void middle2()
{
    char source;

    fprintf(myOutput,
        "\n[MIDDLE TASK 2] waiting for event\n");

    wakeMiddleTask2.wait(source);

    fprintf(myOutput,
        "\n[MIDDLE TASK 2] long independent work\n");

    work('N', 300);

    fprintf(myOutput,
        "\n[MIDDLE TASK 2] finished\n");
}


//Starts the second scenario Holds resource 2

void low2()
{
    fprintf(myOutput,
        "\n[LOW TASK 2] started\n");

    fprintf(myOutput,
        "\n[LOW TASK 2] acquiring second resource\n");

    secondResource.Acquire();

    fprintf(myOutput,
        "\n[LOW TASK 2] acquired second resource\n");

    fprintf(myOutput,
        "\n[LOW TASK 2] wakes LOW TASK 1\n");

    // start first test
    wakeLowTask1.send('L', NULL, false);

    work('Z', 40);

    fprintf(myOutput,
        "\n[LOW TASK 2] wakes HIGH TASK 2 and MIDDLE TASK 2\n");

    // start second test
    wakeHighTask2.send('X', NULL, false);
    wakeMiddleTask2.send('N', NULL, false);

    work('Z', 120);

    fprintf(myOutput,
        "\n[LOW TASK 2] releases second resource\n");

    secondResource.Release();

    work('Z', 20);

    fprintf(myOutput,
        "\n[LOW TASK 2] finished\n");
}

void main()
{
    clrscr();

    myOutput = fopen("two_resources_test.txt", "w");

    if (myOutput == NULL)
    {
        cout << "\nError opening file";
        return;
    }

    fprintf(myOutput,
        "=== TWO RESOURCES PRIORITY INVERSION TEST ===\n");

    fprintf(myOutput,
        "USE_INHERITANCE = %d\n\n",
        USE_INHERITANCE);

    SMARTS.externalFunctions(
        timerInterruptHandler,
        scheduler,
        myTaskEnd,
        RMS
    );

    SMARTS.declareTask(high1, 'H', 400, 1);
    SMARTS.declareTask(middle1, 'M', 401, 1);
    SMARTS.declareTask(low1, 'L', 402, 1);

    SMARTS.declareTask(high2, 'X', 403, 1);
    SMARTS.declareTask(middle2, 'N', 404, 1);
    SMARTS.declareTask(low2, 'Z', 405, 1);

    SMARTS.runTheTasks();

    for (long i = 0; i < 60000000L; i++);

    fprintf(myOutput, "\n=== END ===\n");

    fclose(myOutput);
}
