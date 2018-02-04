# ThreadsPractice
Practice using threads in C

The program executed x number of threads where x is the number inputer by the user.
The threads are to access a shared variable and add 1 to it and finally display the final value it sees.
If PTHREADS_SYNC is defined, the threads will be synchronized. otherwise threads will not be.

USE THE MAKEFILE TO EXECUTE AND RUN THE PROGRAM.
**NOTE: all the files need to be in the same dirctory in order to work properly.**

**To JUST build the program.**
(This will prompt you to build the program with PTHREAD_SYNC defined or not)
```
$ make build
```
**To BUILD and EXECUTE the program.**
(This will prompt you to build the program with PTHREAD_SYNC defined or not).
(ALSO this will prompt you the number of threads to execute in the program).
```
$ make run
```
You will see something like this after you execute 'make run'
```
$ make run
$ Define PTHREAD_SYNC [y/n]:
$ Threads to run: 
```
NOTE: If you enter anything other than 'y' or 'n' when prompt for PTHREAD_SYNC, default value will be 'n'

**To clean** 
```
$ make clean
```

### Bug:
```
When running $ make clean, it prompts the user to define PTHREADS_SYNC, dont know to
stop that from prompting during clean.
```
