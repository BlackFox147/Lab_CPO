#include <stdlib.h>
#include <stdio.h>
#include <process.h>

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

//	char _getch();
#endif 
HANDLE Event;

int main(int argc, char* argv[])
{	
	HANDLE Event = OpenEvent(EVENT_ALL_ACCESS, FALSE, "MyEvent");


	while (1)
	{
		WaitForSingleObject(Event, INFINITE);

		printf("%d___", getpid());
		printf("%d___", getpid());
		printf("\n");

		SetEvent(Event);
//		Sleep(2000);
	}

	printf("End\n");
	return 0;
}

