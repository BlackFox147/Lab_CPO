#include "head.h"



int main()

{
	struct Data *data;
	data = createInfoStruct();
	
    Search(data);
	
	printf("Waiting...\n");

	CreateSem(data);
	//подгружаем динамическую библиотеку
	CreateThreads(data);
//	WaitForMultipleObjects(2, data->hThreads, TRUE, INFINITE);
	CloseApp(data);

	return 0;
}	

	
