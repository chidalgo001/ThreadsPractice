#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//-------------------
void* SimpleThread();
int isDigit(char);
int validateInput(char*, int);
//-------------------
int SharedVariable = 0; 
pthread_barrier_t threadBarrier;
pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;
//-------------------

int main( int argc, char *argv[]){
	
	printf("*******************************\n");
	printf("*** The Program has Started ***\n");
	printf("*******************************\n");

	char *c;// this is basically a string
	c = argv[1];// what is in here is a sequence of strings
	
	int result = validateInput(c, argc);

	if(result == 0){
		printf("Please enter a NUMBER greater than 0\n ");
		return 0;
	}
	
	int barrierStatus = pthread_barrier_init(&threadBarrier, NULL, result);

	pthread_t myThread[result];	
	int threads[result]; 

	for (int i = 0; i < result; i++ ){
	 	threads[i] = i;
		printf("this is argc: %d and this is i: %d\n" ,argc , i);

		pthread_create(&myThread[i], NULL, SimpleThread, &threads[i] );

	}// end of for

	for (int i=0; i < result; i++){

		pthread_join(myThread[i], NULL);

	}

	printf("\n*******************************\n");
	printf("*** The Program has Ended ***\n");
	printf("*******************************\n");
		
}

//*************************************************************************
//validadeInput() takes in 2 inputs, 'input' is the value taken from the 
//command line. 'argc' is the number of arguments.
//(i.e. COMMAND LINE = ./program 32 | input = '32' and argc = 2)
//It will iterate thru the string and check if the char is a digit.
//*************************************************************************

int validateInput(char* input, int argc){

	if(argc != 2)
		return 0;

	int length = strlen(input);
	char temp = ' ';

	for(int count = 0; count <length; count++){

		temp = input[count];

		if( isDigit(temp) == 0 )
			return 0;
	}

	int result = atoi((char*)input);

	return result;

}

//*************************************************************************
//isDigit() takes in 1 input, 'posotion'
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
	//TID ++;

	printf("this is TID %d \n",TID);

	int num, val;
pthread_mutex_lock(&threadMutex);
	for(num = 0; num < 20; num++){
		if(random()> RAND_MAX/2)
			usleep(500);
	
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", TID, val);
		SharedVariable = val +1 ;
		count++;	
	}
pthread_mutex_unlock(&threadMutex);
	
	pthread_barrier_wait(&threadBarrier);

	val = SharedVariable;
	printf("Thread %d sees final value %d\n", TID, val);
	//printf("Thread %d count: %d\n", TID, count);

}
