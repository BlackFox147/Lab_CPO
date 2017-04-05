#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BUFFER_SIZE 512

int main()
{
	int segmentID;
	char* segmentPtr = NULL;
	int semID;
	struct sembuf semBuffServer;
	struct sembuf semBuffClient; 

	int key = ftok("server.c", 's');
	semID = semget(key, 0, 0666);
	if (semID == -1)
	{
		exit(0);
	}
	semBuffServer.sem_num = 0;
	semBuffServer.sem_op = 1;
	semBuffClient.sem_num = 1;
	semBuffClient.sem_op = -1;
	
	key = ftok("server.c", 'c');
	segmentID = shmget(key, BUFFER_SIZE, 0666);
		
	if (segmentID == -1)
	{
		perror("shmget");
		exit(0);
	}
	char str[BUFFER_SIZE];
	segmentPtr = shmat(segmentID, NULL, 0);   
	
	if (segmentPtr == (char*)-1)
	{
		perror("shmat");
		exit(0);
	}
	
	switch(fork())						
	{
		case -1:
			perror("fork error...");
			exit(1);
		case 0:	
		{	
			
			
			while (1)
			{
				
				
				fflush(stdin);
				fgets(str, BUFFER_SIZE, stdin);
				int i = strlen(str) - 1;
				if (str[i] == '\n')
				{
					str[i] = '\0';
				}
				
				if (!sprintf(segmentPtr, "%s", str))
				{	
					break;
				}

				semop(semID, &(semBuffServer), 1);
			}
		}	break;
		
		default:
		{}
			break;
	}
	
	printf("Подключение к серверу.\n");
	
	semop(semID, &(semBuffServer), 1);
	
	while (1)
	{
		while (semctl(semID, 1, GETVAL, 0) != 1);
		if (sprintf(str, "%s", segmentPtr))
		{
			printf("server: ");
			printf("%s\n", str);
		}
		
		semop(semID, &(semBuffClient), 1);
	}
		
		semop(semID, &(semBuffClient), 1);		
		semop(semID, &(semBuffServer), 1);
	}
