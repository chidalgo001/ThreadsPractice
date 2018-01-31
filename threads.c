#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//-------------------
void* SimpleThread();
int isDigit(char);
int validateInput(char*[], int);
int checkCommand(char*);
//-------------------
int SharedVariable = 0; 
pthread_barrier_t threadBarrier;
pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;
int PTHREAD_SYNC = 0;
//-------------------

int main( int argc, char *argv[]){
	

	char *c;// this is basically a string
	c = argv[1];// what is in here is a sequence of strings
	
	int result = validateInput(argv, argc);

	if(result == 0){
		printf("Please enter ONE NUMBER greater than 0\n ");
		return 0;
	}
	
	int barrierStatus = pthread_barrier_init(&threadBarrier, NULL, result);

	pthread_t myThread[result];	
	int threads[result]; 

	for (int i = 0; i < result; i++ ){

	 	threads[i] = i;
		pthread_create(&myThread[i], NULL, SimpleThread, &threads[i] );

	}// end of for

	for (int i=0; i < result; i++){

		pthread_join(myThread[i], NULL);

	}

	printf("\n-----------------------------\n");
	printf("*** The Program has Ended ***\n");
	printf("-----------------------------\n");
		
}

//*************************************************************************
//validadeInput() takes in 2 inputs, 'input' is the value taken from the 
//command line. 'argc' is the number of arguments.
//(i.e. COMMAND LINE = ./program 32 | input = '32' and argc = 2)
//It will iterate thru the string and check if the char is a digit.
//*************************************************************************

int validateInput(char* argv[], int argc){

	char* input = argv[1];
	char* status = "";
	int indicator;

	if(argc == 3){
		char* command = argv[2];
		indicator = checkCommand(command);
	}

	if(argc > 3 || indicator == -1)
		return 0;

	int length = strlen(input);
	char temp = ' ';

	for(int count = 0; count <length; count++){

		temp = input[count];

		if( isDigit(temp) == 0 )
			return 0;
	}

	if(indicator == 1){
		status = "SYNC";	
	}else{
		status = "NORMAL";
	}

	printf("-------------------------------\n");
	printf("*** Program mode: %s ***\n", status);
	printf("-------------------------------\n");
	sleep(2);

	int result = atoi((char*)input);

	return result;

}

int checkCommand(char* command){
	
	if(command[0] != '-'){
		return -1;
	}
	else if(command[0]=='-' && command[1]=='s' && strlen(command)==2){
		PTHREAD_SYNC = 1;
	}
	else{

		printf("\n**NOTE: %s is NOT a valid command.\n", command);
		printf("Program will execute in 'normal' mode.\n\n");
		sleep(3);
		return 0;
	}

	
	return 1;			

}

//*************************************************************************
//isDigit() takes in 1 input, 'position'
//command line. 'argc' is the number of arguments.
//(i.e. COMMAND LINE = ./program 32 | input = '32' and argc = 2)
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

//*************************************************************************
void* SimpleThread (int* which){

	int count = 0;
	int *limit_ptr = (int*)which;
	int TID = *limit_ptr;

	int num, val;

	for(num = 0; num < 20; num++){

		if(random()> RAND_MAX/2)
			usleep(500);

		if(PTHREAD_SYNC == 1)
			pthread_mutex_lock(&threadMutex);
	
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", TID, val);
		SharedVariable = val +1 ;
		count++;	

		if (PTHREAD_SYNC == 1)
			pthread_mutex_unlock(&threadMutex);
	
	}

	if (PTHREAD_SYNC == 1)
		pthread_barrier_wait(&threadBarrier);
	
	val = SharedVariable;
	printf("Thread %d sees final value %d\n", TID, val);
	//printf("Thread %d count: %d\n", TID, count);

}
