// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------
void pageFaultHandle(int);

void
ExceptionHandler(ExceptionType which)
{
	int	type = kernel->machine->ReadRegister(2);
	int	val;

  switch (which) {
	case SyscallException:
    switch(type) {
		case SC_Halt:
		  DEBUG(dbgAddr, "Shutdown, initiated by user program.\n");
   		kernel->interrupt->Halt();
		  break;
		case SC_PrintInt:
			val=kernel->machine->ReadRegister(4);
			cout << "Print integer:" <<val << endl;
			return;
/*		case SC_Exec:
			DEBUG(dbgAddr, "Exec\n");
			val = kernel->machine->ReadRegister(4);
			kernel->StringCopy(tmpStr, retVal, 1024);
			cout << "Exec: " << val << endl;
			val = kernel->Exec(val);
			kernel->machine->WriteRegister(2, val);
			return;
*/
    case SC_Exit:
			DEBUG(dbgAddr, "Program exit\n");
			val=kernel->machine->ReadRegister(4);
			cout << "return value:" << val << endl;
			kernel->currentThread->Finish();
			break;
    case SC_Sleep: /* DONE: implementation of Sleep() */
        val=kernel->machine->ReadRegister(4); // load the argument x
        kernel->alarm->WaitUntil(val);
        return;
		default:
		    cerr << "Unexpected system call " << type << "\n";
 		    break;
    }
	  break;
	case PageFaultException:
  	    val = kernel->machine->ReadRegister(BadVAddrReg);
        pageFaultHandle(val);

        
	default:
	    cerr << "Unexpected user mode exception" << which << "\n";
	    break;
  }
  ASSERTNOTREACHED();
}

void pageFaultHandle(int badVAddrReg){
        // TODO: handle pagefault exception here!    
    srand ( time(NULL) );
    printf("Page falut ocurred.\n");
    kernel->stats->numPageFaults++;
    int i = 0;
    vpn = (unsigned) badVAddrReg / PageSize;
    AddrSpace * addrSpace = kernel->currentThread->space;
    while(addrSpace->usedPhyPage[i] !=FALSE && i < NumPhysPages)
        ++i;
    if(i < NumPhysPages){
        usedPhyPage[i] = true;
        char *buffer = new char[PageSize];
        kernel->currentThread->space->usedPhyPage[i] = TRUE;
        addrSpace->pageTable[vpn].valid = TRUE;
        addrSpace->pageTable[vpn].physicalPage = i;
        kernel->swapDisk->ReadSector(addrSpace->pageTable[vpn].virtualPage, buf);
        bcopy(buf,&kernel->machine->mainMemory[i * PageSize],PageSize);
    }
    else{
        char *buf1 = new char[PageSize];
        char *buf2 = new char[PageSize];
        int victim = rand() % NumPhysPages;

        printf("Page %d swap out\n",victim);

        bcopy(&kernel->machine->mainMemory[victim * PageSize], buf1, PageSize);
        kernel->swapDisk->ReadSector(addrSpace->pageTable[vpn].virtualPage, buf2);

        bcopy(buf2, &kernel->machine->mainMemory[victim * PageSize], PageSize);
        kernel->swapDisk->WriteSector(addrSpace->pageTable[vpn].virtualPage, buf1);

        addrSpace->pageTable[vpn].valid = TRUE;
        addrSpace->pageTable[vpn].physicalPage = victim;
        printf("Page replacement done\n");
    }


}

