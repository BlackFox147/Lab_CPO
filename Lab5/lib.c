#include <windows.h>

#define BUFFER_SIZE 512


void WriteInFile(HANDLE hFile, char* buff)
{
	struct _OVERLAPPED overlapped;
	overlapped.Offset = 0xFFFFFFFF;    //становимся в конец файла
	overlapped.OffsetHigh = 0xFFFFFFFF;  
	overlapped.hEvent = NULL;  
	DWORD cbWritten;
	WriteFile(hFile, buff, strlen(buff), &cbWritten, &overlapped);
	WaitForSingleObject(hFile, INFINITE);		
}


void ReadFromFile(HANDLE hFile, char* buff)
{
	memset(buff, 0, BUFFER_SIZE * sizeof(char));
	struct _OVERLAPPED overlapped;
	overlapped.Offset = 0;				//начало файла
	overlapped.OffsetHigh = 0;
	overlapped.hEvent = NULL;
	DWORD cbRead;
	ReadFile(hFile, buff, BUFFER_SIZE, &cbRead, &overlapped);
	WaitForSingleObject(hFile, INFINITE);
}
