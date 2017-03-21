#include "headers.h"

char _getch()
{
	struct termios old, new;
	char ch;
	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &new);
	ch = getchar();

	tcsetattr(0, TCSANOW, &old);
	return ch;
}


void CreateNewProcess(struct Data *data, struct Stack **stack)
{		
	switch(data->pid = fork())
	{
		case -1:
			perror("fork error...");
			exit(1);
		case 0:	
		{	

			while (1)
			{
				
				
				semop(data->semid, &(data->mybuff), 1);
				semop(data->semid, &(data->mybuff1), 1);
				sleep(1/2);
				
					
					printf("%d___", getpid());
					printf("%d___", getpid());
					

				
				printf("\n");				

				data->mybuff1.sem_op = -1;
				semop(data->semid, &(data->mybuff1), 1);
				data->mybuff1.sem_op = 1;	

			}
		}	break;
		
		default:
		{
			
			push(&*stack, *data);
			(*stack)->pid = data->pid;			
		}
			break;
	}
}

void CloseProcess(struct Stack **stack, struct Data *data, int code)
{
 	if (code == 0){
		kill((*stack)->pid, SIGTERM);
		pop(&*stack);
	}
	if (code == 1){
		while (size(*stack) != 0)
		{
			kill((*stack)->pid, SIGTERM);
			pop(&*stack);
		}

		return;
	}
}


void CreateSignal(struct Data *data)
{
	data->key = ftok("/home/Alexandr/spolab2/lab2", 0);
	data->semid = semget(data->key, 1, 0666 | IPC_CREAT);
	semctl(data->semid, 0, SETVAL, (int)0);
	data->mybuff.sem_num = 0;

	data->mybuff1.sem_num = 0;
	data->mybuff1.sem_op = 1;
}


