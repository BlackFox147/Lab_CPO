#include "headers.h"



int main(int argc, char *argv[])
{
	struct Stack *stack = NULL;
	struct Data data;
	int cnt = 0;

	printf("Run!!!\n");
	
	while (1)
	{
			switch (_getch())
			{
			case '+':
			{
				CreateNewProcess(&data, &stack);
				cnt++;
	
			}
				break;
			case '-':
			{
				if (cnt != 0){				
					CloseProcess(&stack, &data, 0);
					cnt--;
				}
			}

			break;
			case 'q':
			{			
				CloseProcess(&stack, &data, 1);
				cnt = 0;
				
				return 0;
			}
				break;
			}
	}
}

