# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as
GCCDIR = /usr/local/nachos/decstation-ultrix/bin/
LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)


# if you aren't cross-compiling:
#GCCDIR =
#LDFLAGS = -N -T 0
#ASFLAGS =
#CPPFLAGS = -P $(INCDIR)


CC = $(GCCDIR)gcc
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = /lib/cpp
INCDIR =-I../userprog -I../threads -I../lib
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort test1 test2 sleep1 sleep2 sleep3 sjftest*-*

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.s > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

#halt.o: halt.c
#	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

#shell.o: shell.c
#	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

#sort.o: sort.c
#	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

#matmult.o: matmult.c
#	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

test1: test1.o start.o
	$(LD) $(LDFLAGS) start.o test1.o -o test1.coff
	../bin/coff2noff test1.coff test1

test2: test2.o start.o
	$(LD) $(LDFLAGS) start.o test2.o -o test2.coff
	../bin/coff2noff test2.coff test2

#sleep1.o: sleep1.c
#	$(CC) $(CFLAGS) -c sleep1.c
sleep1: sleep1.o start.o
	$(LD) $(LDFLAGS) start.o sleep1.o -o sleep1.coff
	../bin/coff2noff sleep1.coff sleep1

#sleeplong.o: sleeplong.c
#	$(CC) $(CFLAGS) -c sleep1.c
sleeplong: sleeplong.o start.o
	$(LD) $(LDFLAGS) start.o sleeplong.o -o sleeplong.coff
	../bin/coff2noff sleeplong.coff sleeplong

#sleep2.o: sleep2.c
#	$(CC) $(CFLAGS) -c sleep1.c
sleep2: sleep2.o start.o
	$(LD) $(LDFLAGS) start.o sleep2.o -o sleep2.coff
	../bin/coff2noff sleep2.coff sleep2

#sleep3.o: sleep3.c
#	$(CC) $(CFLAGS) -c sleep3.c
sleep3: sleep3.o start.o
	$(LD) $(LDFLAGS) start.o sleep3.o -o sleep3.coff
	../bin/coff2noff sleep3.coff sleep3

#sjftest1-1.o: sjftest1-1.c
#	$(CC) $(CFLAGS) -c sjftest1-1.c
sjftest1-1: sjftest1-1.o start.o
	$(LD) $(LDFLAGS) start.o sjftest1-1.o -o sjftest1-1.coff
	../bin/coff2noff sjftest1-1.coff sjftest1-1

#sjftest1-2.o: sjftest1-2.c
#	$(CC) $(CFLAGS) -c sjftest1-2.c
sjftest1-2: sjftest1-2.o start.o
	$(LD) $(LDFLAGS) start.o sjftest1-2.o -o sjftest1-2.coff
	../bin/coff2noff sjftest1-2.coff sjftest1-2

#sjftest1-3.o: sjftest1-3.c
#	$(CC) $(CFLAGS) -c sjftest1-3.c
sjftest1-3: sjftest1-3.o start.o
	$(LD) $(LDFLAGS) start.o sjftest1-3.o -o sjftest1-3.coff
	../bin/coff2noff sjftest1-3.coff sjftest1-3

#sjftest2-1.o: sjftest2-1.c
#	$(CC) $(CFLAGS) -c sjftest2-1.c
sjftest2-1: sjftest2-1.o start.o
	$(LD) $(LDFLAGS) start.o sjftest2-1.o -o sjftest2-1.coff
	../bin/coff2noff sjftest2-1.coff sjftest2-1

#sjftest2-2.o: sjftest2-2.c
#	$(CC) $(CFLAGS) -c sjftest2-2.c
sjftest2-2: sjftest2-2.o start.o
	$(LD) $(LDFLAGS) start.o sjftest2-2.o -o sjftest2-2.coff
	../bin/coff2noff sjftest2-2.coff sjftest2-2

#sjftest2-3.o: sjftest2-3.c
#	$(CC) $(CFLAGS) -c sjftest2-3.c
sjftest2-3: sjftest2-3.o start.o
	$(LD) $(LDFLAGS) start.o sjftest2-3.o -o sjftest2-3.coff
	../bin/coff2noff sjftest2-3.coff sjftest2-3

