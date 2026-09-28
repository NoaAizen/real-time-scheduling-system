#include "smarts77.h"

/**********    GLOBAL Variables    **********/
Parallelism SMARTS;
static unsigned StackSegAct, StackPtrAct;

/**********    EXTERNAL FUNCTION     **********/
void far interrupt timerInterruptHandler(...)
// This function is called 18.2 times per second ( every ~~ 55 millisec).
{
	asm	mov	StackPtrAct,sp; 	// get the stack addr of the task interrupted
	asm	mov	ax,ss;		// by the clock or by a Program interrupt
	asm	mov	StackSegAct,ax;

	SMARTS.timerClocksEnd = getTimerClocks( );

			// if it was called by the timer interrupt (hardware source),
			// it calls the original BIOS routine. not to change the PC work.
	if (!SMARTS.getProgInt( ))
	{
		asm	int userInt;
		SMARTS.handleTimers();
	}
	else	
		SMARTS.resetProgInt( );  //else it is a software "prog interrupt". reset this flag

			// if the 'context switch' flag=true, save the current task variables
			// and call the 'scheduler'
	if (SMARTS.getContextSwitch( ))   // save stack addr of interrupted task in current stack
	{
		SMARTS.setCurrentStack(StackSegAct,StackPtrAct);
		SMARTS.restoreSchedStack( );	      // prepare activation of the task "scheduler"
		SMARTS.getSchedStack(StackSegAct,StackPtrAct);
		asm	mov	ax,StackSegAct;
		asm	mov	ss,ax
		asm	mov	sp,StackPtrAct
	}
			// else if 'context switch' flag=false set 'end of time slice' flag
	else 
	{
		SMARTS.setEndOfTimeSlice();
		++SMARTS.TScount;	// increment Time Share count
	}
}
//void far interrupt timerInterruptHandler(...)
//{
//    asm mov StackPtrAct, sp;
//    asm mov ax, ss;
//    asm mov StackSegAct, ax;
//
//    SMARTS.timerClocksEnd = getTimerClocks();
//
//    if (!SMARTS.getProgInt())
//    {
//        asm int userInt;
//        SMARTS.handleTimers();
//
//        if (SMARTS.getContextSwitch())
//        {
//            SMARTS.setCurrentStack(StackSegAct, StackPtrAct);
//
//            SMARTS.restoreSchedStack();
//            SMARTS.getSchedStack(StackSegAct, StackPtrAct);
//
//            asm mov ax, StackSegAct;
//            asm mov ss, ax;
//            asm mov sp, StackPtrAct;
//        }
//        else
//        {
//            SMARTS.setEndOfTimeSlice();
//            ++SMARTS.TScount;
//        }
//    }
//    else
//    {
//        SMARTS.resetProgInt();
//
//        SMARTS.setCurrentStack(StackSegAct, StackPtrAct);
//
//        SMARTS.restoreSchedStack();
//        SMARTS.getSchedStack(StackSegAct, StackPtrAct);
//
//        asm mov ax, StackSegAct;
//        asm mov ss, ax;
//        asm mov sp, StackPtrAct;
//    }
//}



///**********    EXTERNAL FUNCTION     **********/


void scheduler()
{
	int nextTask, i;

	nextTask = SMARTS.algorithm();

	if (nextTask == SMARTS.getTotalTasks() &&
		SMARTS.sleepTasks == 0 &&
		SMARTS.activeTasks > 0)
	{
		for (i = SMARTS.getTotalTasks() - 1; i >= 0; --i)
		{
			if (SMARTS.getStatus(i) == SUSPENDED &&
				SMARTS.getDidRunInCycle(i) == 0)
			{
				cprintf("\ntask %c  is suspended", SMARTS.getName(i));
				SMARTS.setDeadlock();
			}
		}
	}

	SMARTS.setCurrentTask(nextTask);

	SMARTS.getCurrentStack(StackSegAct, StackPtrAct);
	asm mov ax, StackSegAct;
	asm mov ss, ax
		asm mov sp, StackPtrAct

		asm pop bp;
	asm pop di;
	asm pop si;
	asm pop ds;
	asm pop es;
	asm pop dx;
	asm pop cx;
	asm pop bx;
	asm pop ax;
	asm iret;
}





/**********    EXTERNAL FUNCTION     **********/
void myTaskEnd( )
{
	SMARTS.taskEnd();	
}



