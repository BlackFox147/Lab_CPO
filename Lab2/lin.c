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


