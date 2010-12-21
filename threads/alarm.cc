// alarm.cc
//	Routines to use a hardware timer device to provide a
//	software alarm clock.  For now, we just provide time-slicing.
//
//	Not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "alarm.h"
#include "main.h"
#include "bedroom.h" //DONE

//----------------------------------------------------------------------
// Alarm::Alarm
//      Initialize a software alarm clock.  Start up a timer device
//
//      "doRandom" -- if true, arrange for the hardware interrupts to
//		occur at random, instead of fixed, intervals.
//----------------------------------------------------------------------

Alarm::Alarm(bool doRandom)
{
    timer = new Timer(doRandom, this);
}

//----------------------------------------------------------------------
// Alarm::CallBack
//	Software interrupt handler for the timer device. The timer device is
//	set up to interrupt the CPU periodically (once every TimerTicks).
//	This routine is called each time there is a timer interrupt,
//	with interrupts disabled.
//
//	Note that instead of calling Yield() directly (which would
//	suspend the interrupt handler, not the interrupted thread
//	which is what we wanted to context switch), we set a flag
//	so that once the interrupt handler is done, it will appear as
//	if the interrupted thread called Yield at the point it is
//	was interrupted.
//
//	For now, just provide time-slicing.  Only need to time slice
//      if we're currently running something (in other words, not idle).
//	Also, to keep from looping forever, we check if there's
//	nothing on the ready list, and there are no other pending
//	interrupts.  In this case, we can safely halt.
//----------------------------------------------------------------------

void
Alarm::CallBack()
{
    Interrupt *interrupt = kernel->interrupt;
    MachineStatus status = interrupt->getStatus();

    if (status == IdleMode) {	// is it time to quit?
        if (!interrupt->AnyFutureInterrupts()) {
	    timer->Disable();	// turn off the timer
	}
    } else {			// there's someone to preempt
        interrupt->YieldOnReturn();
        //DONE
/*        if(kernel->scheduler->getSchedulerType() == RR) interrupt->YieldOnReturn();
        else if(kernel->scheduler->getSchedulerType() == SJF){
            int worktime = kernel->stats->userTicks - kernel->currentThread->getStartTime();
            kernel->currentThread->setBurstTime(worktime);

        }*/

    }


}


void
Alarm::WaitUntil(int x){
  // manipulating interrupts, thus turn off interrupt.
  IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
  Thread* t = kernel->currentThread;

  DEBUG(dbgSleep, "** Thread " << t << " will sleep for " << x << " ticks...");

  kernel->interrupt->Schedule(new Bed(t), x, TimerInt); // set alarm clock
      // the alarm clock will be fired by timer interrupt, x ticks later.

  t->Sleep(false); // good night, Mr.t.

  (void) kernel->interrupt->SetLevel(oldLevel);
  // set the original interrupt level back.
}

