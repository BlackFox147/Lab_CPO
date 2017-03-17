#include "headers.h"



int main(int argc, char *argv[])
{
	struct Stack *stack = NULL;
	struct Data data;

	CreateSignal(&data);

	printf("Run!!!\n");
	int cnt = 0;
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

		
	}
}

