#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
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

	int key = ftok("server.c", 's');  				//преобразование сущь. полное имя и целочисленный индикатор в значение типа key_t (ключ IPC)			
	semID = semget(key, 2, 0666 | IPC_CREAT);
	semctl(semID, 0, SETVAL, (int)0);
	semctl(semID, 1, SETVAL, (int)0);
	semBuffServer.sem_num = 0;
	semBuffServer.sem_op = -1;
	semBuffClient.sem_num = 1;
	semBuffClient.sem_op = 1;
	
	key = ftok("server.c", 'c');
	segmentID = shmget(key, BUFFER_SIZE, 0666 | IPC_CREAT);
		
	if (segmentID == -1)
	{
		semctl(semID, 0, IPC_RMID, 0);
		shmdt(segmentPtr);
		perror("shmget");
		exit(0);
	}
	
	char str[BUFFER_SIZE];
	
	if (segmentPtr == (char*)-1)
	{
		perror("shmat");
		exit(0);
	}
	segmentPtr = shmat(segmentID, NULL, 0);	
	
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

				semop(semID, &(semBuffClient), 1);
			}
		}	break;
		
		default:
		{}
			break;
	}
	
	printf("Сервер ожидает подключения клиента.\n");	
	
	while (semctl(semID, 0, GETVAL, 0) != 1);
	
	printf("Клиент подключён\n");



	
	
	while (1)
	{
			
		semop(semID, &(semBuffServer), 1);

		while (semctl(semID, 0, GETVAL, 0) != 1);
		
		if (sprintf(str, "%s", segmentPtr))
		{
			printf("user: ");
			printf("%s\n", str);
		}
		
	}
	
	semctl(semID, 0, IPC_RMID, 0);
	shmdt(segmentPtr);
}
