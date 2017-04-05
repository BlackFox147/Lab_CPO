#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h> 

#define BUFFER_SIZE 512

int main(void)
{

	HANDLE hPipe;
	LPTSTR PipeName = TEXT("\\\\.\\pipe\\MyPipe_s");


	char temp[BUFFER_SIZE]="";


	hPipe = CreateNamedPipe( 
          PipeName,			   // имя канала
          PIPE_ACCESS_DUPLEX,       // чтение и запись из канала
          PIPE_TYPE_MESSAGE |       // передача сообщений по каналу
          PIPE_READMODE_MESSAGE |   // режим чтения сообщений 
          PIPE_WAIT,                // синхронная передача сообщений 
          PIPE_UNLIMITED_INSTANCES, // число экземпляров канала 
          4096,			   // размер выходного буфера
          4096,		          // размер входного буфера  
          NMPWAIT_USE_DEFAULT_WAIT, // тайм-аут клиента 
          NULL);                    // защита по умолчанию
	
	if (hPipe == INVALID_HANDLE_VALUE) 
    {
	 printf("1CreatePipe failed: error code %d\n", (int)GetLastError());
        return 0;
    }	
	
	STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	if (CreateProcess("Write_ser.exe",NULL,
		NULL,NULL,FALSE,0,NULL,NULL,&cif,&pi))
	{
		printf("Write\n");
	}
	
	HANDLE hSemServer = CreateSemaphore(NULL, 0, 1, "SemServer");
	HANDLE hSemClient = CreateSemaphore(NULL, 0, 1, "SemClient");	
	// ждем пока клиент свяжется с каналом 
	printf("The server is waiting for connection with a client.\n");

	if(!ConnectNamedPipe( 
		hPipe,NULL )) 
	{  
		CloseHandle(hPipe); 
		printf("Press key to finish the server: ");
		_getch();
		return 0;
	}
	

	
    WaitForSingleObject(hSemServer, INFINITE);
	printf("Client connected\n");	


	while(strcmp(temp, "--")) 
	{
		
		WaitForSingleObject(hSemServer, INFINITE);

			DWORD dwRead1;
			if (ReadFile( hPipe, temp, BUFFER_SIZE, 
				&dwRead1, NULL))  
			{
				printf("%s\n", temp);
			} 		

	}
		
 
	
	CloseHandle(hPipe);
	CloseHandle(hSemServer);
	CloseHandle(hSemClient);	
	printf("Press key to finish the server: ");
    _getch();	
	return 0;
}
