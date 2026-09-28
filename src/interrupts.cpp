// Based on the SMARTS77 framework by A. Teitelbaum,
// on an idea by H. G. Mendelbaum, Jerusalem College of Technology.

#include "smarts77.h"

Parallelism SMARTS;
static unsigned StackSegAct, StackPtrAct;

// Handle hardware ticks and software scheduling requests.
// Preserve the Part 1 baseline: no deferred-switch branch is enabled here.
void far interrupt timerInterruptHandler(...)

{
    asm    mov    StackPtrAct,sp;
    asm    mov    ax,ss;
    asm    mov    StackSegAct,ax;

    SMARTS.timerClocksEnd = getTimerClocks( );

    if (!SMARTS.getProgInt( ))
    {
        asm    int userInt;
        SMARTS.handleTimers();
    }
    else
        SMARTS.resetProgInt( );

    if (SMARTS.getContextSwitch( ))
    {
        SMARTS.setCurrentStack(StackSegAct,StackPtrAct);
        SMARTS.restoreSchedStack( );
        SMARTS.getSchedStack(StackSegAct,StackPtrAct);
        asm    mov    ax,StackSegAct;
        asm    mov    ss,ax
        asm    mov    sp,StackPtrAct
    }

}

// Invoke the selected policy, check for suspended tasks, and restore context.
// Keep the framework register order and assembly instructions unchanged.
void scheduler( )

{
    int nextTask, i;

    nextTask = SMARTS.algorithm( );

    if (nextTask == SMARTS.getTotalTasks() &&
        SMARTS.sleepTasks==0 && SMARTS.activeTasks>0)
    {
        for (i=SMARTS.getTotalTasks()-1; i >= 0 ; --i)
            if (SMARTS.getStatus(i) == SUSPENDED)
            {
                cprintf("\ntask %c  is suspended",SMARTS.getName(i)) ;
                SMARTS.setDeadlock();
            }
    }

    SMARTS.setCurrentTask(nextTask);

    SMARTS.getCurrentStack(StackSegAct,StackPtrAct);
    asm    mov    ax,StackSegAct;
    asm    mov    ss,ax
    asm    mov    sp,StackPtrAct

    asm    pop    bp;
    asm    pop    di;
    asm    pop    si;
    asm    pop    ds;
    asm    pop    es;
    asm    pop    dx;
    asm    pop    cx;
    asm    pop    bx;
    asm    pop    ax;
    asm    iret;
}

// Framework task-return callback.
void myTaskEnd( )
{
    SMARTS.taskEnd();
}
