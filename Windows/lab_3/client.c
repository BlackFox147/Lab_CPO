#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h> 
#define BUFFER_SIZE 512

int main(void)
{
	HANDLE hPipe;
	LPTSTR PipeName = TEXT("\\\\.\\pipe\\MyPipe");
	hPipe = CreateFile( 
         PipeName,	      // имя канала
         GENERIC_READ |  // чтение и запись в канал
         GENERIC_WRITE, 
         0,              // нет разделяемых операций 
         NULL,           // защита по умолчанию
         OPEN_EXISTING,  // открытие существующего канала 
         0,              // атрибуты по умолчанию
         NULL);          // нет дополнительных атрибутов 
	
	HANDLE hSemServer = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SemServer"));
	HANDLE hSemClient = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SemClient"));

    printf("Connected to server.\n");

	ReleaseSemaphore(hSemServer, 1, NULL);

	 char str[BUFFER_SIZE];
	while(strcmp(str, "quit"))
 { 
	DWORD dwRead; 
	if (ReadFile(hPipe, str,    
	BUFFER_SIZE, &dwRead,NULL ))  
	{
		printf("%s\n", str);
	} 
	ReleaseSemaphore(hSemServer, 1, NULL);
	
	WaitForSingleObject(hSemClient, INFINITE);
	if (ReadFile(hPipe, str,    
	BUFFER_SIZE, &dwRead,NULL ))  
	{
		printf("%s\n", str);
		DWORD dwWritten;
		if (!WriteFile( hPipe, "the client has received a message", BUFFER_SIZE, 
			&dwWritten, NULL))  
		{
			break;
		} 
	} 
	ReleaseSemaphore(hSemServer,1,NULL);	
 } 
 
 CloseHandle(hPipe);
 CloseHandle(hSemClient); 

 	printf("The end!");

	
	return 0;
}
