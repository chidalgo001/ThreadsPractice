#--- This variables are to be defines by the user ---
THREADS ?= $(shell bash -c 'read -p "Threads to run: " threads; echo $$threads')
PTHREAD_SYNC ?= $(shell bash -c 'read -p "Define PTHREAD_SYNC? (y/n): " sync; echo $$sync')

#--- Makefile Variables -----

CC = gcc
OUT = threads
PROG = threads.c threads.h
LIB = -lpthread

#--- makefule Targets -----

build: 

ifeq	($(PTHREAD_SYNC),y) #if 'y' PTHREAD_SYNC will be defined in the program.
	$(CC) -o $(OUT) $(PROG) $(LIB) -DPTHREAD_SYNC
else
	$(CC) -o $(OUT) $(PROG) $(LIB)
endif

run: build 
	./$(OUT) $(THREADS)  

clean:	
	rm -f $(OUT)

#-----------------------------------
