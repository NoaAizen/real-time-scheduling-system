/////////////////////////////////////////////////שלב א./////////////////////////////////////////////////




//#include "smarts77.h"
//
///**********    Function     **********/
//unsigned getTimerClocks()
//// Gets the remaining clocks of the timer register
//{
//	unsigned clocks;
//	/* latch counter #0 */
//	outportb(0x43, 0x00);
//	/* read counter #0 low byte */
//	clocks = inportb(0x40);
//	/* read counter #0 high byte */
//	clocks += inportb(0x40) << 8;
//	return clocks;
//}
//////////////////////////////////////////////////////
///**********    class body:  Parallelism     **********/
//Parallelism::Parallelism()
//{
//	currentTask = 0;
//	sleepTasks = 0;
//	activeTasks = 0;
//	totalTasks = 0;
//	deadlock = false;
//	contextSwitchFlag = true;
//	endOfTimeSlice = true;
//}
//
//void Parallelism::externalFunctions(void interrupt(*timerInterruptHandler)(...),
//	void far* scheduler, void far* userTaskEnd,
//	int far(*algorithm)())
//	// Sets the external functions
//{
//	this->timerInterruptHandler = timerInterruptHandler;
//	this->scheduler = scheduler;
//	this->userTaskEnd = userTaskEnd;
//	this->algorithm = algorithm;
//	contextSched.declare(scheduler, userTaskEnd, 'S'); // prepare the stack of the scheduler task
//	for (int i = MaxStack - 1; i >= (MaxStack - 14); i--)
//		schedCopy[i] = contextSched.stack[i];
//}
//
//int Parallelism::declareTask(void far* code, char name, int period, int numOfPeriods)
//{
//	if (totalTasks < MaxTask - 1)
//	{
//		context[totalTasks].declare(code, userTaskEnd, name);
//		//new - initialize periodic task timing values
//		context[totalTasks].period = period;
//		//new - set initial deadline time
//		context[totalTasks].remainingTime = period;
//		//new - set total number of task cycles
//		context[totalTasks].numOfPeriod = numOfPeriods;
//		//new - initialize remaining cycles counter
//		context[totalTasks].numOfPeriodRemaining = numOfPeriods;
//		//new - task has not completed current cycle yet in first intial
//		context[totalTasks].didRunInCycle = 0;
//
//		totalTasks++;
//		activeTasks++;
//		return true;
//	}
//	return false;
//}
//
//
//
//void Parallelism::runTheTasks()
//// Start running all tasks declared in SMARTS.		
//{
//	context[totalTasks].status = READY;	//for task 'runTheTasks' (IDLE task)
//	context[totalTasks].priority = MAXINT;
//	context[totalTasks].currentPriority = MAXINT;
//
//	currentTask = totalTasks;
//
//	asm	cli;		// forbids interrupts (clear interrupts) while changing the interrupt vect
//	// saves the original BIOS userInt in our variable 'userIntAddress' to be restored at the end
//	userIntAddress = getvect(userInt);	// BIOS userInt 0x60  (unused by PC)
//	// puts the normal BIOS timerInt into the unused userInt address
//	setvect(userInt, getvect(timerInt));	// timerInt 0x08 
//
//	// sets our SMARTS external function 'timerInterruptHandler' as the new PC hard interrupt time handler
//	setvect(timerInt, timerInterruptHandler);
//	asm	sti;	// allows back interrupts (set interrupts)
//
//	// waits for end of runTheTasks (end of all the tasks)
//	while (true)
//	{
//		if (deadlock)
//		{
//			textcolor(RED);
//			cprintf("\n\n\rExit : deadlock");
//			break;
//		}
//		if (activeTasks == 0)
//		{
//			cprintf("\n\n\rExit : finish");
//			break;
//		}
//	}
//
//	// restore the original BIOS 'interrupt vector' at the end before returning to regular DOS
//	asm	cli;	// no interrupts
//	setvect(timerInt, getvect(userInt));	// restore original BIOS time handler
//	setvect(userInt, userIntAddress);	// restore original BIOS userInt
//	asm	sti;	// yes interrupts
//}
//
//void Parallelism::callScheduler()
//// Return the control to the scheduler, this sets ON the software interrupt ProgInt flag
//{
//	setProgInt();
//	asm int timerInt;
//}
//
//void Parallelism::restoreSchedStack()
//// Restore the scheduler stack
//{
//	for (int i = MaxStack - 1; i >= (MaxStack - 14); i--)
//		contextSched.stack[i] = schedCopy[i];
//}
//
//int Parallelism::getCurrentTask()
//{
//	return currentTask;
//}
//
//void Parallelism::setCurrentTask(int taskNum)
//// Sets the next task to be run
//{
//	if (taskNum <= totalTasks)
//		currentTask = taskNum;
//}
//
//int Parallelism::getTotalTasks()
//// Gets total tasks declared
//{
//	return totalTasks;
//}
//
//int Parallelism::getDeadlock()
//{
//	return deadlock;
//}
//
//void Parallelism::setDeadlock()
//{
//	deadlock = true;
//}
//
//int Parallelism::contextSwitchOn()
//// flag which enables context switch
//{
//	if (endOfTimeSlice) //is current time slice finished ?
//	{
//		endOfTimeSlice = false;
//		contextSwitchFlag = true;
//		callScheduler();	// return control to the scheduler
//		return 1;
//	}
//	contextSwitchFlag = true;
//	return 0;
//}
//
//void Parallelism::contextSwitchOff()
//// Disable context switch
//{
//	contextSwitchFlag = false;
//}
//
//int Parallelism::getContextSwitch()
//{
//	return contextSwitchFlag;
//}
//
//void Parallelism::setProgInt()
//// flag indicates to the extern function 'timerInterruptHandler' 
//// that this is an internal SMARTS software interrupt call, 
//// and the original BIOS function has no to be called.
//{
//	progInt = true;
//}
//
//void Parallelism::resetProgInt()
//{
//	progInt = false;
//}
//
//int Parallelism::getProgInt()
//{
//	return progInt;
//}
//
//void Parallelism::setEndOfTimeSlice()
//// flag indicates that when 'context switch' will be enabled, 
//// it must also return the control to the scheduler.
//{
//	endOfTimeSlice = true;
//}
//
//char Parallelism::getName(int taskNum)	// returns name found or ' ' if not
//{
//	return (taskNum <= totalTasks) ? context[taskNum].name : ' ';
//}
//
//char Parallelism::getCurrentName()
//{
//	return context[currentTask].name;
//}
//
//taskStatus Parallelism::getStatus(int taskNum)
//// returns status or undefined if not found
//{
//	return (taskNum <= totalTasks) ? context[taskNum].status : UNDEFINED;
//}
//
//taskStatus Parallelism::getCurrentStatus()
//{
//	return context[currentTask].status;
//}
//
//void Parallelism::resume(int taskNum)
//{
//	if (taskNum < totalTasks)
//		context[taskNum].status = READY;
//}
//
//void Parallelism::resume(char taskName)
//{
//	for (int i = 0; i < totalTasks; ++i)
//		if (context[i].name == taskName)
//			context[i].status = READY;
//}
//
//
//void Parallelism::setCurrentNotActive()
//{	//new task waits for next cycle activation
//	context[currentTask].status = NOT_ACTIVE;
//	--activeTasks;
//}
//void Parallelism::suspended()
//{
//	context[currentTask].status = SUSPENDED;
//	callScheduler();
//}
//
//void Parallelism::incrPriority(int taskNum)
//{
//	if (taskNum < totalTasks)
//		context[taskNum].incrPriority();
//}
//void Parallelism::setOriginalPriority(int taskNum)
//{
//	if (taskNum < totalTasks)
//		context[taskNum].setOriginalPriority();
//}
//
//void Parallelism::setCurrentOriginalPriority()
//{
//	context[currentTask].setOriginalPriority();
//}
//
//Event* Parallelism::getExpectedEvent(int taskNum)
//// returns *Event  or  NULL  if not found
//{
//	return (taskNum <= totalTasks) ? context[taskNum].expectedEvent : NULL;
//}
//
//Event* Parallelism::getCurrentExpectedEvent()
//{
//	return context[currentTask].expectedEvent;
//}
//
//void Parallelism::setCurrentExpectedEvent(Event* expectedEvent)
//{
//	context[currentTask].expectedEvent = expectedEvent;
//}
//
//void Parallelism::sleep(int t)
//// Current task sleeps for 't' milliseconds
//{
//	if (t < MAXINT)
//	{
//		context[currentTask].sleepCount = t / 55 + 1;
//		context[currentTask].status = SLEEP;
//		++sleepTasks;
//		callScheduler();		// return control to scheduler
//	}
//}
//
//void Parallelism::sleepDecr(int taskNum)
//{
//	if (taskNum < totalTasks)
//		context[taskNum].sleepDecr();
//}
//
//void Parallelism::getCurrentStack(unsigned& StackSeg, unsigned& StackPtr)
//// Load current task stack pointer
//{
//	StackSeg = context[currentTask].stackSeg;
//	StackPtr = context[currentTask].stackPtr;
//}
//
//void Parallelism::setCurrentStack(unsigned StackSeg, unsigned StackPtr)
//// Save current task stack pointer
//{
//	context[currentTask].stackSeg = StackSeg;
//	context[currentTask].stackPtr = StackPtr;
//}
//
//void Parallelism::getSchedStack(unsigned& StackSeg, unsigned& StackPtr)
//// Load scheduler  stack pointer
//{
//	StackSeg = contextSched.stackSeg;
//	StackPtr = contextSched.stackPtr;
//}
//
//void Parallelism::handleTimers()
//{
//	for (int i = totalTasks - 1; i >= 0; --i)
//	{
//		if (context[i].numOfPeriodRemaining == 0)
//			continue;
//
//		if (getStatus(i) == SLEEP)
//		{
//			sleepDecr(i);
//
//			if (getStatus(i) == READY)
//				--sleepTasks;
//		}
//
//		context[i].remainingTime--;
//
//		if (context[i].remainingTime == 0)
//		{
//			if (context[i].didRunInCycle == 0)
//			{
//				cout << "\nERROR: task ";
//				cout << context[i].name;
//				cout << " missed deadline";
//
//				setDeadlock();
//
//				for (int j = 0; j < totalTasks; j++)
//				{
//					context[j].status = NOT_ACTIVE;
//				}
//
//				activeTasks = 0;
//
//				return;
//			}
//
//			context[i].numOfPeriodRemaining--;
//
//			if (context[i].numOfPeriodRemaining == 0)
//			{
//				context[i].status = NOT_ACTIVE;
//				activeTasks--;
//			}
//			else
//			{
//				context[i].reDeclare();
//			}
//		}
//	}
//}
//
//void Parallelism::taskEnd()
//{
//	SMARTS.markCurrentTaskRan();
//	context[currentTask].status = NOT_ACTIVE;
//	SMARTS.callScheduler();
//}
////new - mark current task cycle as completed
//void Parallelism::markCurrentTaskRan()
//{
//	context[currentTask].didRunInCycle = 1;
//}
//int Parallelism::getRemainingTime(int taskNum)
//{
//	return context[taskNum].remainingTime;
//}
//
//int Parallelism::getDidRunInCycle(int taskNum)
//{
//	return context[taskNum].didRunInCycle;
//}
//
//int Parallelism::getPeriod(int taskNum)
//{
//	return context[taskNum].period;
//}
//
///**********    class body:  Task     **********/
//Task::Task()
//{
//	stack[MaxStack - 14] = _BP;
//	stack[MaxStack - 13] = _DI;
//	stack[MaxStack - 12] = _SI;
//	stack[MaxStack - 11] = _DS;
//	stack[MaxStack - 10] = _ES;
//	stack[MaxStack - 9] = _DX;
//	stack[MaxStack - 8] = _CX;
//	stack[MaxStack - 7] = _BX;
//	stack[MaxStack - 6] = _AX;
//	stackSeg = FP_SEG(&stack[MaxStack - 14]);
//	stackPtr = FP_OFF(&stack[MaxStack - 14]);
//	status = NOT_ACTIVE;
//	sleepCount = 0;
//	currentPriority = priority = 0;
//}
////-----------------------------------------------------
//void Task::declare(void far* code, void far* userTaskEnd, char name)
//{
//	taskCode = code;
//	taskEndCode = userTaskEnd;
//
//	stack[MaxStack - 5] = FP_OFF(code);
//	stack[MaxStack - 4] = FP_SEG(code);
//	stack[MaxStack - 3] = _FLAGS;
//	stack[MaxStack - 2] = FP_OFF(userTaskEnd);
//	stack[MaxStack - 1] = FP_SEG(userTaskEnd);
//
//	this->name = name;
//	status = READY;
//}
////----------------------------------------------------
//void Task::incrPriority()
//{
//	--currentPriority;
//}
////----------------------------------------------------
//void Task::setOriginalPriority()
//{
//	currentPriority = priority;
//}
////----------------------------------------------------
//void Task::sleepDecr()
//// Decrements the sleep counter and update the task status accordingly
//{
//	if (status == SLEEP)
//	{
//		if (sleepCount > 0)
//			--sleepCount;
//		if (!sleepCount)
//			status = READY;
//	}
//}
//void Task::reDeclare()
//{
//	stack[MaxStack - 14] = _BP;
//	stack[MaxStack - 13] = _DI;
//	stack[MaxStack - 12] = _SI;
//	stack[MaxStack - 11] = _DS;
//	stack[MaxStack - 10] = _ES;
//	stack[MaxStack - 9] = _DX;
//	stack[MaxStack - 8] = _CX;
//	stack[MaxStack - 7] = _BX;
//	stack[MaxStack - 6] = _AX;
//
//	//new - rebuild task stack for new execution cycle
//	stack[MaxStack - 5] = FP_OFF(taskCode);
//	stack[MaxStack - 4] = FP_SEG(taskCode);
//	stack[MaxStack - 3] = _FLAGS;
//	stack[MaxStack - 2] = FP_OFF(taskEndCode);
//	stack[MaxStack - 1] = FP_SEG(taskEndCode);
//
//	stackSeg = FP_SEG(&stack[MaxStack - 14]);
//	stackPtr = FP_OFF(&stack[MaxStack - 14]);
//
//	//new - reset deadline timer for next cycle
//	remainingTime = period;
//	//new - reset cycle completion flag
//	didRunInCycle = 0;
//	//new - make task runnable again
//	status = READY;
//}
//

///////////////////////////////////////////////////////////////////////שלב ב/////////////////////////////

//
//
//
//#include "smarts77.h"
//
///**********    Function     **********/
//unsigned getTimerClocks()
//// Gets the remaining clocks of the timer register
//{
//	unsigned clocks;
//	/* latch counter #0 */
//	outportb(0x43, 0x00);
//	/* read counter #0 low byte */
//	clocks = inportb(0x40);
//	/* read counter #0 high byte */
//	clocks += inportb(0x40) << 8;
//	return clocks;
//}
//////////////////////////////////////////////////////
///**********    class body:  Parallelism     **********/
//Parallelism::Parallelism()
//{
//	currentTask = 0;
//	sleepTasks = 0;
//	activeTasks = 0;
//	totalTasks = 0;
//	deadlock = false;
//	//contextSwitchFlag = true;
//	context[currentTask].contextSwitchFlag = true;
//	endOfTimeSlice = true;
//}
//
//void Parallelism::externalFunctions(void interrupt(*timerInterruptHandler)(...),
//	void far* scheduler, void far* userTaskEnd,
//	int far(*algorithm)())
//	// Sets the external functions
//{
//	this->timerInterruptHandler = timerInterruptHandler;
//	this->scheduler = scheduler;
//	this->userTaskEnd = userTaskEnd;
//	this->algorithm = algorithm;
//	contextSched.declare(scheduler, userTaskEnd, 'S'); // prepare the stack of the scheduler task
//	for (int i = MaxStack - 1; i >= (MaxStack - 14); i--)
//		schedCopy[i] = contextSched.stack[i];
//}
//
//int Parallelism::declareTask(void far* code, char name, int period, int numOfPeriods)
//{
//	if (totalTasks < MaxTask - 1)
//	{
//		context[totalTasks].declare(code, userTaskEnd, name);
//		//new - initialize periodic task timing values
//		context[totalTasks].period = period;
//		//new - set initial deadline time
//		context[totalTasks].remainingTime = period;
//		//new - set total number of task cycles
//		context[totalTasks].numOfPeriod = numOfPeriods;
//		//new - initialize remaining cycles counter
//		context[totalTasks].numOfPeriodRemaining = numOfPeriods;
//		//new - task has not completed current cycle yet in first intial
//		context[totalTasks].didRunInCycle = 0;
//
//		totalTasks++;
//		activeTasks++;
//		return true;
//	}
//	return false;
//}
//
//
//
//void Parallelism::runTheTasks()
//// Start running all tasks declared in SMARTS.		
//{
//	context[totalTasks].status = READY;	//for task 'runTheTasks' (IDLE task)
//	context[totalTasks].priority = MAXINT;
//	context[totalTasks].currentPriority = MAXINT;
//
//	currentTask = totalTasks;
//
//	asm	cli;		// forbids interrupts (clear interrupts) while changing the interrupt vect
//	// saves the original BIOS userInt in our variable 'userIntAddress' to be restored at the end
//	userIntAddress = getvect(userInt);	// BIOS userInt 0x60  (unused by PC)
//	// puts the normal BIOS timerInt into the unused userInt address
//	setvect(userInt, getvect(timerInt));	// timerInt 0x08 
//
//	// sets our SMARTS external function 'timerInterruptHandler' as the new PC hard interrupt time handler
//	setvect(timerInt, timerInterruptHandler);
//	asm	sti;	// allows back interrupts (set interrupts)
//
//	// waits for end of runTheTasks (end of all the tasks)
//	while (true)
//	{
//		if (deadlock)
//		{
//			textcolor(RED);
//			cprintf("\n\n\rExit : deadlock");
//			break;
//		}
//		if (activeTasks == 0)
//		{
//			cprintf("\n\n\rExit : finish");
//			break;
//		}
//	}
//
//	// restore the original BIOS 'interrupt vector' at the end before returning to regular DOS
//	asm	cli;	// no interrupts
//	setvect(timerInt, getvect(userInt));	// restore original BIOS time handler
//	setvect(userInt, userIntAddress);	// restore original BIOS userInt
//	asm	sti;	// yes interrupts
//}
//
//void Parallelism::callScheduler()
//// Return the control to the scheduler, this sets ON the software interrupt ProgInt flag
//{
//	setProgInt();
//	asm int timerInt;
//}
//
//void Parallelism::restoreSchedStack()
//// Restore the scheduler stack
//{
//	for (int i = MaxStack - 1; i >= (MaxStack - 14); i--)
//		contextSched.stack[i] = schedCopy[i];
//}
//
//int Parallelism::getCurrentTask()
//{
//	return currentTask;
//}
//
//void Parallelism::setCurrentTask(int taskNum)
//// Sets the next task to be run
//{
//	if (taskNum <= totalTasks)
//		currentTask = taskNum;
//}
//
//int Parallelism::getTotalTasks()
//// Gets total tasks declared
//{
//	return totalTasks;
//}
//
//int Parallelism::getDeadlock()
//{
//	return deadlock;
//}
//
//void Parallelism::setDeadlock()
//{
//	deadlock = true;
//}
//
//int Parallelism::contextSwitchOn()
//// flag which enables context switch
//{
//	if (endOfTimeSlice) //is current time slice finished ?
//	{
//		endOfTimeSlice = false;
//		//contextSwitchFlag = true;
//		context[currentTask].contextSwitchFlag = true;
//		callScheduler();	// return control to the scheduler
//		return 1;
//	}
//	context[currentTask].contextSwitchFlag = true;
//	//contextSwitchFlag = true;
//	return 0;
//}
//
//void Parallelism::contextSwitchOff()
//// Disable context switch
//{
//	context[currentTask].contextSwitchFlag = false;
//
//
//	//contextSwitchFlag = false;
//}
//
//int Parallelism::getContextSwitch()
//{
//	//return contextSwitchFlag;
//	return 	context[currentTask].contextSwitchFlag;
//
//}
//
//void Parallelism::setProgInt()
//// flag indicates to the extern function 'timerInterruptHandler' 
//// that this is an internal SMARTS software interrupt call, 
//// and the original BIOS function has no to be called.
//{
//	progInt = true;
//}
//
//void Parallelism::resetProgInt()
//{
//	progInt = false;
//}
//
//int Parallelism::getProgInt()
//{
//	return progInt;
//}
//
//void Parallelism::setEndOfTimeSlice()
//// flag indicates that when 'context switch' will be enabled, 
//// it must also return the control to the scheduler.
//{
//	endOfTimeSlice = true;
//}
//
//char Parallelism::getName(int taskNum)	// returns name found or ' ' if not
//{
//	return (taskNum <= totalTasks) ? context[taskNum].name : ' ';
//}
//
//char Parallelism::getCurrentName()
//{
//	return context[currentTask].name;
//}
//
//taskStatus Parallelism::getStatus(int taskNum)
//// returns status or undefined if not found
//{
//	return (taskNum <= totalTasks) ? context[taskNum].status : UNDEFINED;
//}
//
//taskStatus Parallelism::getCurrentStatus()
//{
//	return context[currentTask].status;
//}
//
//void Parallelism::resume(int taskNum)
//{
//	if (taskNum < totalTasks)
//		context[taskNum].status = READY;
//}
//
//void Parallelism::resume(char taskName)
//{
//	for (int i = 0; i < totalTasks; ++i)
//		if (context[i].name == taskName)
//			context[i].status = READY;
//}
//
//
//void Parallelism::setCurrentNotActive()
//{	//new task waits for next cycle activation
//	context[currentTask].status = NOT_ACTIVE;
//	--activeTasks;
//}
//void Parallelism::suspended()
//{
//	context[currentTask].status = SUSPENDED;
//	callScheduler();
//}
//
//void Parallelism::incrPriority(int taskNum)
//{
//	if (taskNum < totalTasks)
//		context[taskNum].incrPriority();
//}
//void Parallelism::setOriginalPriority(int taskNum)
//{
//	if (taskNum < totalTasks)
//		context[taskNum].setOriginalPriority();
//}
//
//void Parallelism::setCurrentOriginalPriority()
//{
//	context[currentTask].setOriginalPriority();
//}
//
//Event* Parallelism::getExpectedEvent(int taskNum)
//// returns *Event  or  NULL  if not found
//{
//	return (taskNum <= totalTasks) ? context[taskNum].expectedEvent : NULL;
//}
//
//Event* Parallelism::getCurrentExpectedEvent()
//{
//	return context[currentTask].expectedEvent;
//}
//
//void Parallelism::setCurrentExpectedEvent(Event* expectedEvent)
//{
//	context[currentTask].expectedEvent = expectedEvent;
//}
//
//void Parallelism::sleep(int t)
//// Current task sleeps for 't' milliseconds
//{
//	if (t < MAXINT)
//	{
//		context[currentTask].sleepCount = t / 55 + 1;
//		context[currentTask].status = SLEEP;
//		++sleepTasks;
//		callScheduler();		// return control to scheduler
//	}
//}
//
//void Parallelism::sleepDecr(int taskNum)
//{
//	if (taskNum < totalTasks)
//		context[taskNum].sleepDecr();
//}
//
//void Parallelism::getCurrentStack(unsigned& StackSeg, unsigned& StackPtr)
//// Load current task stack pointer
//{
//	StackSeg = context[currentTask].stackSeg;
//	StackPtr = context[currentTask].stackPtr;
//}
//
//void Parallelism::setCurrentStack(unsigned StackSeg, unsigned StackPtr)
//// Save current task stack pointer
//{
//	context[currentTask].stackSeg = StackSeg;
//	context[currentTask].stackPtr = StackPtr;
//}
//
//void Parallelism::getSchedStack(unsigned& StackSeg, unsigned& StackPtr)
//// Load scheduler  stack pointer
//{
//	StackSeg = contextSched.stackSeg;
//	StackPtr = contextSched.stackPtr;
//}
//
//void Parallelism::handleTimers()
//{
//	for (int i = totalTasks - 1; i >= 0; --i)
//	{
//		if (context[i].numOfPeriodRemaining == 0)
//			continue;
//
//		if (getStatus(i) == SLEEP)
//		{
//			sleepDecr(i);
//
//			if (getStatus(i) == READY)
//				--sleepTasks;
//		}
//
//		context[i].remainingTime--;
//
//		if (context[i].remainingTime == 0)
//		{
//			if (context[i].didRunInCycle == 0)
//			{
//				cout << "\nERROR: task ";
//				cout << context[i].name;
//				cout << " missed deadline";
//
//				setDeadlock();
//
//				for (int j = 0; j < totalTasks; j++)
//				{
//					context[j].status = NOT_ACTIVE;
//				}
//
//				activeTasks = 0;
//
//				return;
//			}
//
//			context[i].numOfPeriodRemaining--;
//
//			if (context[i].numOfPeriodRemaining == 0)
//			{
//				context[i].status = NOT_ACTIVE;
//				activeTasks--;
//			}
//			else
//			{
//				context[i].reDeclare();
//			}
//		}
//	}
//}
//
//void Parallelism::taskEnd()
//{
//	SMARTS.markCurrentTaskRan();
//	context[currentTask].status = NOT_ACTIVE;
//	SMARTS.callScheduler();
//}
////new - mark current task cycle as completed
//void Parallelism::markCurrentTaskRan()
//{
//	context[currentTask].didRunInCycle = 1;
//}
//int Parallelism::getRemainingTime(int taskNum)
//{
//	return context[taskNum].remainingTime;
//}
//
//int Parallelism::getDidRunInCycle(int taskNum)
//{
//	return context[taskNum].didRunInCycle;
//}
//
//int Parallelism::getPeriod(int taskNum)
//{
//	return context[taskNum].period;
//}
//
///**********    class body:  Task     **********/
//Task::Task()
//{
//	stack[MaxStack - 14] = _BP;
//	stack[MaxStack - 13] = _DI;
//	stack[MaxStack - 12] = _SI;
//	stack[MaxStack - 11] = _DS;
//	stack[MaxStack - 10] = _ES;
//	stack[MaxStack - 9] = _DX;
//	stack[MaxStack - 8] = _CX;
//	stack[MaxStack - 7] = _BX;
//	stack[MaxStack - 6] = _AX;
//	stackSeg = FP_SEG(&stack[MaxStack - 14]);
//	stackPtr = FP_OFF(&stack[MaxStack - 14]);
//	status = NOT_ACTIVE;
//	sleepCount = 0;
//	currentPriority = priority = 0;
//	contextSwitchFlag = true;
//}
////-----------------------------------------------------
//void Task::declare(void far* code, void far* userTaskEnd, char name)
//{
//	taskCode = code;
//	taskEndCode = userTaskEnd;
//
//	stack[MaxStack - 5] = FP_OFF(code);
//	stack[MaxStack - 4] = FP_SEG(code);
//	stack[MaxStack - 3] = _FLAGS;
//	stack[MaxStack - 2] = FP_OFF(userTaskEnd);
//	stack[MaxStack - 1] = FP_SEG(userTaskEnd);
//
//	this->name = name;
//	status = READY;
//}
////----------------------------------------------------
//void Task::incrPriority()
//{
//	--currentPriority;
//}
////----------------------------------------------------
//void Task::setOriginalPriority()
//{
//	currentPriority = priority;
//}
////----------------------------------------------------
//void Task::sleepDecr()
//// Decrements the sleep counter and update the task status accordingly
//{
//	if (status == SLEEP)
//	{
//		if (sleepCount > 0)
//			--sleepCount;
//		if (!sleepCount)
//			status = READY;
//	}
//}
//void Task::reDeclare()
//{
//	stack[MaxStack - 14] = _BP;
//	stack[MaxStack - 13] = _DI;
//	stack[MaxStack - 12] = _SI;
//	stack[MaxStack - 11] = _DS;
//	stack[MaxStack - 10] = _ES;
//	stack[MaxStack - 9] = _DX;
//	stack[MaxStack - 8] = _CX;
//	stack[MaxStack - 7] = _BX;
//	stack[MaxStack - 6] = _AX;
//
//	//new - rebuild task stack for new execution cycle
//	stack[MaxStack - 5] = FP_OFF(taskCode);
//	stack[MaxStack - 4] = FP_SEG(taskCode);
//	stack[MaxStack - 3] = _FLAGS;
//	stack[MaxStack - 2] = FP_OFF(taskEndCode);
//	stack[MaxStack - 1] = FP_SEG(taskEndCode);
//
//	stackSeg = FP_SEG(&stack[MaxStack - 14]);
//	stackPtr = FP_OFF(&stack[MaxStack - 14]);
//
//	//new - reset deadline timer for next cycle
//	remainingTime = period;
//	//new - reset cycle completion flag
//	didRunInCycle = 0;
//	//new - make task runnable again
//	status = READY;
//}
////new
//
//
//Mutex::Mutex()
//{
//	value = 1;   // פנוי בהתחלה
//	owner = -1;
//	waitingCount = 0;
//
//	for (int i = 0; i < MaxTask; i++)
//	{
//		waitingTasks[i] = -1;
//	}
//}
//
//
//void Mutex::Acquire()
//{
//	SMARTS.contextSwitchOff();
//
//	int current = SMARTS.getCurrentTask();
//
//	// פנוי
//	if (value == 1)
//	{
//		value = 0;
//		owner = current;
//
//		cout << "\nTask " << current << " acquired mutex";
//
//		SMARTS.contextSwitchOn();
//		return;
//	}
//
//	// תפוס → נכנס להמתנה
//	cout << "\nTask " << current << " blocked";
//
//	waitingTasks[waitingCount++] = current;
//
//	SMARTS.setCurrentNotActive();
//	SMARTS.suspended();
//
//	SMARTS.contextSwitchOn();
//}
//
//void Mutex::Release()
//{
//	SMARTS.contextSwitchOff();
//
//	int currentTask = SMARTS.getCurrentTask();
//
//	if (owner != currentTask)
//	{
//		cout << "\nERROR: Task " << currentTask << " is not owner";
//		SMARTS.contextSwitchOn();
//		return;
//	}
//
//	cout << "\nTask " << currentTask << " released mutex";
//
//	if (waitingCount == 0)
//	{
//		owner = -1;
//		value = 1;
//
//		SMARTS.contextSwitchOn();
//		return;
//	}
//
//	int bestIndex = getHighestPriorityTask();
//	int nextTask = waitingTasks[bestIndex];
//
//	for (int i = bestIndex; i < waitingCount - 1; i++)
//	{
//		waitingTasks[i] = waitingTasks[i + 1];
//	}
//
//	waitingCount--;
//
//	owner = nextTask;
//	value = 0;
//
//	cout << "\nTask " << nextTask << " resumed and owns mutex";
//
//	SMARTS.resume(nextTask);
//	SMARTS.callScheduler();  
//
//	SMARTS.contextSwitchOn();
//}
//
//
//int Mutex::getHighestPriorityTask()
//{
//	int bestIndex = 0;
//	int minPeriod = MAXINT;
//
//	for (int i = 0; i < waitingCount; i++)
//	{
//		if (SMARTS.getPeriod(waitingTasks[i]) < minPeriod)
//		{
//			minPeriod = SMARTS.getPeriod(waitingTasks[i]);
//			bestIndex = i;
//		}
//	}
//
//	return bestIndex;
//}
//
//



////////////////////////////////////////שלב 3





#include "smarts77.h"

/**********    Function     **********/
unsigned getTimerClocks()
// Gets the remaining clocks of the timer register
{
	unsigned clocks;
	/* latch counter #0 */
	outportb(0x43, 0x00);
	/* read counter #0 low byte */
	clocks = inportb(0x40);
	/* read counter #0 high byte */
	clocks += inportb(0x40) << 8;
	return clocks;
}
////////////////////////////////////////////////////
/**********    class body:  Parallelism     **********/
Parallelism::Parallelism()
{
	currentTask = 0;
	sleepTasks = 0;
	activeTasks = 0;
	totalTasks = 0;
	deadlock = false;
	//contextSwitchFlag = true;
	context[currentTask].contextSwitchFlag = true;
	endOfTimeSlice = true;
}

void Parallelism::externalFunctions(void interrupt(*timerInterruptHandler)(...),
	void far* scheduler, void far* userTaskEnd,
	int far(*algorithm)())
	// Sets the external functions
{
	this->timerInterruptHandler = timerInterruptHandler;
	this->scheduler = scheduler;
	this->userTaskEnd = userTaskEnd;
	this->algorithm = algorithm;
	contextSched.declare(scheduler, userTaskEnd, 'S'); // prepare the stack of the scheduler task
	for (int i = MaxStack - 1; i >= (MaxStack - 14); i--)
		schedCopy[i] = contextSched.stack[i];
}

int Parallelism::declareTask(void far* code, char name, int period, int numOfPeriods)
{
	if (totalTasks < MaxTask - 1)
	{
		context[totalTasks].declare(code, userTaskEnd, name);

		//new- In RMS, smaller period means higher priority
		// Save both original and current priority
		context[totalTasks].period = period;	
		context[totalTasks].remainingTime = period;

		//new - set total number of task cycles
		context[totalTasks].numOfPeriod = numOfPeriods;
		//new - initialize remaining cycles counter
		context[totalTasks].numOfPeriodRemaining = numOfPeriods;
		//new - task has not completed current cycle yet in first intial
		context[totalTasks].didRunInCycle = 0;
		context[totalTasks].priority = period;
		context[totalTasks].currentPriority = period;

		totalTasks++;
		activeTasks++;
		return true;
	}
	return false;
}



void Parallelism::runTheTasks()
// Start running all tasks declared in SMARTS.		
{
	context[totalTasks].status = READY;	//for task 'runTheTasks' (IDLE task)
	context[totalTasks].priority = MAXINT;
	context[totalTasks].currentPriority = MAXINT;

	currentTask = totalTasks;

	asm	cli;		// forbids interrupts (clear interrupts) while changing the interrupt vect
	// saves the original BIOS userInt in our variable 'userIntAddress' to be restored at the end
	userIntAddress = getvect(userInt);	// BIOS userInt 0x60  (unused by PC)
	// puts the normal BIOS timerInt into the unused userInt address
	setvect(userInt, getvect(timerInt));	// timerInt 0x08 

	// sets our SMARTS external function 'timerInterruptHandler' as the new PC hard interrupt time handler
	setvect(timerInt, timerInterruptHandler);
	asm	sti;	// allows back interrupts (set interrupts)

	// waits for end of runTheTasks (end of all the tasks)
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

	// restore the original BIOS 'interrupt vector' at the end before returning to regular DOS
	asm	cli;	// no interrupts
	setvect(timerInt, getvect(userInt));	// restore original BIOS time handler
	setvect(userInt, userIntAddress);	// restore original BIOS userInt
	asm	sti;	// yes interrupts
}

void Parallelism::callScheduler()
// Return the control to the scheduler, this sets ON the software interrupt ProgInt flag
{
	setProgInt();
	asm int timerInt;
}

void Parallelism::restoreSchedStack()
// Restore the scheduler stack
{
	for (int i = MaxStack - 1; i >= (MaxStack - 14); i--)
		contextSched.stack[i] = schedCopy[i];
}

int Parallelism::getCurrentTask()
{
	return currentTask;
}

void Parallelism::setCurrentTask(int taskNum)
// Sets the next task to be run
{
	if (taskNum <= totalTasks)
		currentTask = taskNum;
}

int Parallelism::getTotalTasks()
// Gets total tasks declared
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

int Parallelism::contextSwitchOn()
// flag which enables context switch
{
	if (endOfTimeSlice) //is current time slice finished ?
	{
		endOfTimeSlice = false;
		//contextSwitchFlag = true;
		context[currentTask].contextSwitchFlag = true;
		callScheduler();	// return control to the scheduler
		return 1;
	}
	context[currentTask].contextSwitchFlag = true;
	//contextSwitchFlag = true;
	return 0;
}

void Parallelism::contextSwitchOff()
// Disable context switch
{
	context[currentTask].contextSwitchFlag = false;


	//contextSwitchFlag = false;
}

int Parallelism::getContextSwitch()
{
	//return contextSwitchFlag;
	return 	context[currentTask].contextSwitchFlag;

}

void Parallelism::setProgInt()
// flag indicates to the extern function 'timerInterruptHandler' 
// that this is an internal SMARTS software interrupt call, 
// and the original BIOS function has no to be called.
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
// flag indicates that when 'context switch' will be enabled, 
// it must also return the control to the scheduler.
{
	endOfTimeSlice = true;
}

char Parallelism::getName(int taskNum)	// returns name found or ' ' if not
{
	return (taskNum <= totalTasks) ? context[taskNum].name : ' ';
}

char Parallelism::getCurrentName()
{
	return context[currentTask].name;
}

taskStatus Parallelism::getStatus(int taskNum)
// returns status or undefined if not found
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


void Parallelism::setCurrentNotActive()
{	//new task waits for next cycle activation
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
// returns *Event  or  NULL  if not found
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

void Parallelism::sleep(int t)
// Current task sleeps for 't' milliseconds
{
	if (t < MAXINT)
	{
		context[currentTask].sleepCount = t / 55 + 1;
		context[currentTask].status = SLEEP;
		++sleepTasks;
		callScheduler();		// return control to scheduler
	}
}

void Parallelism::sleepDecr(int taskNum)
{
	if (taskNum < totalTasks)
		context[taskNum].sleepDecr();
}

void Parallelism::getCurrentStack(unsigned& StackSeg, unsigned& StackPtr)
// Load current task stack pointer
{
	StackSeg = context[currentTask].stackSeg;
	StackPtr = context[currentTask].stackPtr;
}

void Parallelism::setCurrentStack(unsigned StackSeg, unsigned StackPtr)
// Save current task stack pointer
{
	context[currentTask].stackSeg = StackSeg;
	context[currentTask].stackPtr = StackPtr;
}

void Parallelism::getSchedStack(unsigned& StackSeg, unsigned& StackPtr)
// Load scheduler  stack pointer
{
	StackSeg = contextSched.stackSeg;
	StackPtr = contextSched.stackPtr;
}

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

				setDeadlock();

				for (int j = 0; j < totalTasks; j++)
				{
					context[j].status = NOT_ACTIVE;
				}

				activeTasks = 0;

				return;
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

void Parallelism::taskEnd()
{
	SMARTS.markCurrentTaskRan();
	context[currentTask].status= NOT_ACTIVE;
	SMARTS.callScheduler();
}
//new - mark current task cycle as completed
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
//new 2

int Parallelism::getPeriod(int taskNum)
{
	return context[taskNum].period;
}

// Returns the original task priority
int Parallelism::getPriority(int task)
{
	return context[task].priority;
}

// new - Returns the current priority
// (may change because of inheritance)
int Parallelism::getCurrentPriority(int task)
{
	return context[task].currentPriority;
}
//new- Updates the current priority of a task
void Parallelism::setCurrentPriority(int task, int p)
{
	context[task].currentPriority = p;
}

/**********    class body:  Task     **********/
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
	//new- Original and current priorities are identical at creation
	currentPriority = priority = 0;
	contextSwitchFlag = true;
}
//-----------------------------------------------------
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
//----------------------------------------------------
void Task::incrPriority()
{
	--currentPriority;
}
//----------------------------------------------------
void Task::setOriginalPriority()
{
	currentPriority = priority;
}
//----------------------------------------------------
void Task::sleepDecr()
// Decrements the sleep counter and update the task status accordingly
{
	if (status == SLEEP)
	{
		if (sleepCount > 0)
			--sleepCount;
		if (!sleepCount)
			status = READY;
	}
}
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
	
		//new - rebuild task stack for new execution cycle
		stack[MaxStack - 5] = FP_OFF(taskCode);
	stack[MaxStack - 4] = FP_SEG(taskCode);
	stack[MaxStack - 3] = _FLAGS;
	stack[MaxStack - 2] = FP_OFF(taskEndCode);
	stack[MaxStack - 1] = FP_SEG(taskEndCode);

	stackSeg = FP_SEG(&stack[MaxStack - 14]);
	stackPtr = FP_OFF(&stack[MaxStack - 14]);

	//new - reset deadline timer for next cycle
	remainingTime = period;
	//new - reset cycle completion flag
	didRunInCycle = 0;
	//new - make task runnable again
	status = READY;
}
//new - Mutex without priority inheritance */
Mutex::Mutex()
{
	value = 1;   // Mutex is available
	owner = -1;
	waitingCount = 0;
	inheritanceEnabled = 0;

	for (int i = 0; i < MaxTask; i++)
		waitingTasks[i] = -1;
}
//new -Mutex with optional priority inheritance 
Mutex::Mutex(int inheritance)
{
	value = 1;   // Mutex is available
	owner = -1;
	waitingCount = 0;
	inheritanceEnabled = inheritance;

	for (int i = 0; i < MaxTask; i++)
		waitingTasks[i] = -1;
}

void Mutex::Acquire()
{
	SMARTS.contextSwitchOff();

	int currentTask = SMARTS.getCurrentTask();

	 // Mutex is available
	if (value == 1)
	{
		value = 0;    // Mutex is not available
		owner = currentTask;

		cout << "\nTask " << currentTask
			<< " acquired mutex";

		SMARTS.contextSwitchOn();
		return;
	}
	/*new - Priority inheritance:
   	If a higher-priority task is blocked,
   	temporarily raise the owner's priority */
	if (inheritanceEnabled && owner != -1)
	{
		if (SMARTS.getCurrentPriority(currentTask) <
			SMARTS.getCurrentPriority(owner))
		{
			// Give the owner the blocked task's priority
			SMARTS.setCurrentPriority(
				owner,
				SMARTS.getCurrentPriority(currentTask)
			);

			cout << "\nPriority inheritance: Task "
				<< owner << " inherits priority of Task "
				<< currentTask;
		}
	}

	// Resource is busy, task must wait - mutex is lock
	cout << "\nTask " << currentTask
		<< " blocked";

	waitingTasks[waitingCount++] = currentTask;
	SMARTS.suspended();
	SMARTS.contextSwitchOn();
}

void Mutex::Release()
{
	SMARTS.contextSwitchOff();

	int currentTask = SMARTS.getCurrentTask();

	// Only the owner can release the mutex
	if (owner != currentTask)
	{
		cout << "\nERROR: Task "
			<< currentTask
			<< " is not owner";

		SMARTS.contextSwitchOn();
		return;
	}

	cout << "\nTask "
		<< currentTask
		<< " released mutex";

	//new - Restore the original priority
	// after leaving the critical section
	if (inheritanceEnabled)
	{
		SMARTS.setCurrentPriority(
			currentTask,
			SMARTS.getPriority(currentTask)
		);
	}

	// No tasks are waiting
	if (waitingCount == 0)
	{
		value = 1;  //Resource is available
		owner = -1;

		SMARTS.contextSwitchOn();
		return;
	}

	//new -  Select the waiting task with
	// the highest current priority
	int bestIndex = getHighestPriorityTask();
	int nextTask = waitingTasks[bestIndex];

	// Remove from waiting list
	for (int i = bestIndex; i < waitingCount - 1; i++)
	{
		waitingTasks[i] = waitingTasks[i + 1];
	}

	waitingCount--;

	owner = nextTask;
	value = 0;   // Mutex is not available

	cout << "\nTask "
		<< nextTask
		<< " resumed and owns mutex";

	SMARTS.resume(nextTask);

	SMARTS.callScheduler();

	SMARTS.contextSwitchOn();
}
/*new -  Returns the waiting task with
   the highest priority */
int Mutex::getHighestPriorityTask()
{
	int bestIndex = 0;
	int minPeriod = MAXINT;

	for (int i = 0; i < waitingCount; i++)
	{	// Smaller value = higher priority
		if (SMARTS.getCurrentPriority(waitingTasks[i]) < minPeriod) {
			minPeriod = SMARTS.getCurrentPriority(waitingTasks[i]);
			bestIndex = i;
		}
	}

	return bestIndex;
}