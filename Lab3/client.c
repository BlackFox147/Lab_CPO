#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h> 



#define BUFFER_SIZE 512

int main(void)
{
	HANDLE hPipe;
	LPTSTR PipeName = TEXT("\\\\.\\pipe\\MyPipe_c");
	hPipe = CreateFile( 
         PipeName,	      // имя канала
         GENERIC_READ |  // чтение и запись в канал
         GENERIC_WRITE, 
         0,              // нет разделяемых операций 
         NULL,           // защита по умолчанию
         OPEN_EXISTING,  // открытие существующего канала 
         0,              // атрибуты по умолчанию
         NULL);          // нет дополнительных атрибутов 
	
	if (hPipe == INVALID_HANDLE_VALUE) 
    {
	 printf("CreatePipe failed: error code %d\n", (int)GetLastError());
	 
        return 0;
    }
	
	STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	if (CreateProcess("Write_cl.exe",NULL,
		NULL,NULL,FALSE,0,NULL,NULL,&cif,&pi))
	{
		printf("Write_cl\n");
	}
	
	HANDLE hSemServer = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SemServer"));
	HANDLE hSemClient = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SemClient"));

    printf("Connected to server.\n");
	
	
	
	ReleaseSemaphore(hSemServer, 1, NULL);

	char str[BUFFER_SIZE]="";

	while(strcmp(str, "--"))
	{ 

		WaitForSingleObject(hSemClient, INFINITE);
		

		DWORD dwRead;
		if (ReadFile(hPipe, str,    
		BUFFER_SIZE, &dwRead,NULL ))  
		{
			
			printf("%s\n", str);
		} 


	} 
 
	CloseHandle(hPipe);
	CloseHandle(hSemClient); 

 	printf("The end Read!");

	
	return 0;
}
