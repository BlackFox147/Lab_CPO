#include <stdlib.h>
#include <stdio.h>



#if defined(_WIN32) || defined(_WIN64) 
	#include <windows.h> 
	#include <conio.h> 
#else 
	#include <sys/sem.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <errno.h>
	#include <unistd.h>
	#include <termios.h>

	char _getch();
#endif 




struct Data
{
#if defined(_WIN32) || defined(_WIN64)
	PROCESS_INFORMATION prInfo;
#else
	pid_t pid;
	key_t key;
	int semid;
	struct sembuf mybuff, mybuff1;
#endif
};

struct Stack
{
#if defined(_WIN32) || defined(_WIN64)
	HANDLE hand;
	
#else
	pid_t pid;
	
#endif
	struct Stack *next;
};

int size(const struct  Stack *);
void push(struct Stack **, struct Data);
void pop(struct Stack **);




void CreateNewProcess(struct Data *, struct Stack **);
void CloseProcess(struct Stack **, struct Data *, int code);

void CreateSignal(struct Data *);

void PrintProcesses(char **argv, struct Data *);
