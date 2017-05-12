#include "head.h"
int size=0;

typedef void (*ReadFromFile)(HANDLE, char*);
typedef void (*WriteInFile)(HANDLE, char*);

HINSTANCE library;

struct Data
{
	HANDLE hThreads[2];
	HANDLE hSemRead;
	HANDLE hSemWrite;
	struct Array *arr;
};
struct Array
{
	char fileName[100];
};

void Search(struct Data *data)
{
	WIN32_FIND_DATA wfd;
 
    HANDLE hFind = FindFirstFile(".\\Files\\*.txt", &wfd); //находим первы файл. Информацию о нём сохраняем в структуре wdf
	setlocale(LC_ALL, "");
 
    if (hFind != INVALID_HANDLE_VALUE)	//еслс нет ошибки
    {
        do
        {
			if (!strcmp(wfd.cFileName, "All.txt")) //если дошли до результирующего файла, то пропускаем его 
			{
				continue;
			}
			if(size==0)  //если это первый файл 
			{
				data->arr=(struct Array*) malloc(1 * sizeof(struct Array));  //выделяем под него память
			}
			else
			{
				data->arr=(struct Array*) realloc(data->arr, (size+1) * sizeof(struct Array)); //переопределяем память для добавления нового файла в массив
			}
			strcpy(data->arr[size].fileName, "Files\\");
			strcat(data->arr[size].fileName, wfd.cFileName);//записываем имя + путь файла
			size++;
		} while (FindNextFile(hFind, &wfd) != 0);  //продолжаем поиск файлов
		size--;
        FindClose(hFind);  //закрыли поиск
    }
}

unsigned CALLBACK ThreadReader(void* fdata)
{
	struct Data *data = (struct Data *)fdata;
	ReadFromFile readFromFile = (ReadFromFile) GetProcAddress(library,"ReadFromFile");
	
	while (1)
	{
		WaitForSingleObject(data->hSemRead, INFINITE);
		if (size == -1)
		{
			break;
		}
		HANDLE hFile = CreateFile(data->arr[size].fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
		(*readFromFile)(hFile, buffer);
		printf("Reader: Content to'%s'\n",data->arr[size].fileName);
		CloseHandle(hFile);
		ReleaseSemaphore(data->hSemWrite,1,NULL);
	}
	
	_endthreadex(0);
	return 0;
}

unsigned CALLBACK ThreadWriter(void* fdata)
{		
	struct Data *data = (struct Data *)fdata;
	HANDLE hFile = CreateFile("Files\\All.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
	WriteInFile writeInFile = (WriteInFile) GetProcAddress(library,"WriteInFile");
	
	do
	{
		WaitForSingleObject(data->hSemWrite, INFINITE);
		(*writeInFile)(hFile, buffer);
		printf("Writer: Content to '%s'\n",data->arr[size].fileName);
		size--;
		ReleaseSemaphore(data->hSemRead,1,NULL);
	} while (size != -1);

	CloseHandle(hFile);
	_endthreadex(0);
	return 0;
}

void CreateThreads(struct Data *data)
{
	data->hThreads[1]  = (HANDLE) _beginthreadex(NULL, 0, ThreadReader, (void*) data, 0, NULL);
	data->hThreads[0]  = (HANDLE) _beginthreadex(NULL, 0, ThreadWriter, (void*) data, 0, NULL);
	
	WaitForMultipleObjects(2, data->hThreads, TRUE, INFINITE);
}

void CloseApp(struct Data *data)
{
	CloseHandle(data->hThreads[0]);
	CloseHandle(data->hThreads[1]);
	CloseHandle(data->hSemWrite);
	CloseHandle(data->hSemRead);
	FreeLibrary(library);
	printf("Press any key...\n");
	_getch();
}

void CreateSem(struct Data *data)
{
	data->hSemRead = CreateSemaphore(NULL, 1, 1, "SemRead");
	data->hSemWrite = CreateSemaphore(NULL, 0, 1, "SemWrite");
	
	library = LoadLibrary("libWin.dll");
}

struct Data *createInfoStruct()
{
	return malloc(sizeof(struct Data));	
}

	
