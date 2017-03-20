#include "headers.h"



int main(int argc, char *argv[])
{
	struct Stack *stack = NULL;
//	struct Stack *temp = NULL;
	struct Data data;
	int cnt = 0;
	
//	CreateSignal(&stack,&data);
//	cnt++;

	printf("Run!!!\n");
	
	while (1)
	{
		/*char ss;
		ss = 'a' + cnt;

		char* ptr = &ss;
		ptr[1] = '\0';
		wchar_t wtext[5];
		mbstowcs(wtext, ptr, 2);
		LPWSTR str = wtext;*/

			switch (_getch())
			{
			case '+':
			{
				CreateNewProcess(&data, &stack);
				cnt++;
	//			free(argv[0]);
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
				//	free(ptr);
				return 0;
			}
				break;
			}

		
/*			sleep(3);
			temp = stack;
			for (int i = 0; i < size(temp); i++)
				{
					kill(temp->pid, SIGCONT);
					temp = temp->next;
					fflush(stdout);
//					sleep(3);
				}
		
//		printf("/Ok\n");*/  
	}
	
	
	
}

