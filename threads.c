#include "threads.h"

//Program Description: threads.c executes any number of threads. Each thread
//will access a global shared variable and will add to it.
//Program will wait until all threads are done.
//Compilation: make build (This will prompt the user if they want to define PTHREAD_SYNC for
//syncronization)



//--------Global Variables----------

int SharedVariable = 0; 
pthread_barrier_t threadBarrier;
pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;

//----------MAIN---------

int main( int argc, char *argv[]){
	


	char *c;	// this is basically a string
	c = argv[1];	// what is in here is a sequence of strings
	
	int result = validateInput(argv, argc);

	if(result == 0){
		printf("\n-----------------ERROR-----------------\n");
		printf("Please enter ONE NUMBER greater than 0\n");
		printf("---------------------------------------\n");
		return 0;
	}//if validation fails, program exits with a 0.

	printf("\n--------------------------------------\n");

	int barrierStatus = pthread_barrier_init(&threadBarrier, NULL, result);

	pthread_t myThread[result];	
	int threads[result]; 

	for (int i = 0; i < result; i++ ){

	 	threads[i] = i;
		pthread_create(&myThread[i], NULL, SimpleThread, &threads[i] );

	}

	for (int i=0; i < result; i++){

		pthread_join(myThread[i], NULL);

	}//program waits for all threads to finish prior exiting.

	printf("\n-----------------------------\n");
	printf("*** The Program has Ended ***\n");
	printf("-----------------------------\n");
		
}

//*************************************************************************
//validadeInput() takes in 2 inputs, 'argv[]' is the value taken from the 
//command line. 'argc' is the number of arguments.
//(i.e. COMMAND LINE = ./program 32 | input = '32' and argc = 2)
//It will iterate thru the string and check if the char is a digit.
//*************************************************************************

int validateInput(char* argv[], int argc){

	char* input = argv[1];
	char* status = "";

	if(argc > 2)
		return 0;

	int length = strlen(input);
	char temp = ' ';

	for(int count = 0; count <length; count++){

		temp = input[count];

		if( isDigit(temp) == 0 )
			return 0;
	}//this loop checks each char to see if its a digit (0-9)

	int result = atoi((char*)input);

	return result;

}


//*************************************************************************
//isDigit() takes in 1 input, 'position' and it wil check if the char in
//that position is a digit (0-9). Returns a 1 if its a digit, otherwise
//returns 0	
//*************************************************************************
int isDigit(char position)
{
    	int number = position - 48;
	
	if(number >=0 && number <= 9){
		return 1;
	} else {
		return 0;
	}

}

//*************************************************************************
// This is the function that will be executed by the threads.
// if PTHREAD_SYNC is defined it will sync the threads, otherwise it wont.
//*************************************************************************
void* SimpleThread (int* which){

	int count = 0;
	int *limit_ptr = (int*)which;
	int TID = *limit_ptr;

	int num, val;

	for(num = 0; num < 20; num++){

		if(random()> RAND_MAX/2)
			usleep(500);

		#ifdef PTHREAD_SYNC
			pthread_mutex_lock(&threadMutex);
		#endif
	
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", TID, val);
		SharedVariable = val +1 ;
		count++;	

		#ifdef PTHREAD_SYNC
			pthread_mutex_unlock(&threadMutex);
		#endif
	
	}

	#ifdef PTHREAD_SYNC
		pthread_barrier_wait(&threadBarrier);
	#endif
	
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", TID, val);

}
