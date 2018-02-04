#include <stdio.h>	
#include <pthread.h>		//for the use of pthreads
#include <unistd.h>		//for the use of usleep()
#include <stdlib.h>		//for the use of RAND_MAX and random() and atoi()
#include <string.h>		//for the use of strlen()

//------Funtion Declarations for threads.c-----
void* SimpleThread();		
int isDigit(char);
int validateInput(char*[], int);

