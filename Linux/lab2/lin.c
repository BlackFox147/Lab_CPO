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

/*
void CreateSignal(struct Stack **stack,struct Data *data)
{
	struct Stack *temp;
	switch(data->pid = fork())
	{
		case -1:
			perror("fork error...");
			exit(1);
		case 0:	
		{	
//			printf("%d___\n", getpid());

			while (1)
			{				
				temp = *stack;
				for (int i = 0; i < size(*stack)-1; i++)
				{
					kill(temp->pid, SIGCONT);
					temp = temp->next;
					sleep(3);
				}	
				 
			}
		}	break;
		default:
		{
			push(stack, *data);
			(*stack)->pid = data->pid;
			printf("%d___\n", (*stack)->pid);
			return; 
		}
			break;
	}
}*/

void CreateNewProcess(struct Data *data, struct Stack **stack)
{	
	switch(data->pid = fork())
	{
		case -1:
			perror("fork error...");
			exit(1);
		case 0:	
		{	

	//		sleep(2);
//			sleep(1);
	//		fflush(stdout);
	//		raise(SIGSTOP);
			while (1)
			{	
//				printf("%d___\n", getpid());
//				raise(SIGSTOP);
				for (int i = 0; i < 5; i++)
				{
					printf("%d___", getpid());
					fflush(stdout);
					sleep(1/2);
				}
				printf("\n");
				sleep(2);
			}
		}	break;
		
		default:
		{
			
			push(&*stack, *data);
			(*stack)->pid = data->pid;
			printf("%d___\n", (*stack)->pid);
			
		}
			break;
	}
}

void CloseProcess(struct Stack **stack, struct Data *data, int code)
{
  // semop(data->semid, &(data->mybuff), 1);
	if (code == 0){
		kill((*stack)->pid, SIGTERM);
		pop(&*stack);
	}
	if (code == 1){
	//	semop(data->semid, &(data->mybuff1), 1);
		while (size(*stack) != 0)
		{
			kill((*stack)->pid, SIGTERM);
			pop(&*stack);
		}
//		printf("\033[2J\033[0;0f"); 
		return;
	}
}


