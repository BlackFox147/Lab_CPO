#include "head.h"

 
 int w=0;
 int r=0;
 int size=0;
 
struct Data
{
	pthread_t pThread[2];
	struct Array *arr;
	
	int semID;
	struct sembuf semBuffRead;
	struct sembuf semBuffWrite; 
};
struct Array
{
	char fileName[100];
};

struct Data *createInfoStruct()
{
	return malloc(sizeof(struct Data));	
}


typedef void (*ReadFromFile)(int, char*);
typedef void (*WriteInFile)(int, char*);

void Search(struct Data *data)
{
	DIR *dir;
    struct dirent *entry; //находим первы файл. Информацию о нём сохраняем в структуре 
	
	 dir = opendir("./Files/");
    if (!dir) {
        perror("diropen");
        exit(1);
    };
  
        while ( (entry = readdir(dir)) != NULL)
        {
			if (!strcmp(entry->d_name, "All.txt")) //если дошли до результирующего файла, то пропускаем его 
			{
				continue;
			}
			if (!strcmp(entry->d_name, "..")) //если дошли до результирующего файла, то пропускаем его 
			{
				continue;
			}
			if (!strcmp(entry->d_name, ".")) //если дошли до результирующего файла, то пропускаем его 
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
			strcpy(data->arr[size].fileName, "./Files/");
			strcat(data->arr[size].fileName, entry->d_name);//записываем имя + путь файла
			size++;
		}   //продолжаем поиск файлов
		size--;
		
        closedir(dir);  //закрыли поиск
		
}





void* ThreadReader(void* fdata)
{
		
	struct Data *data = (struct Data *)fdata;
	char *error;
	int op1;
	
	ReadFromFile readFromFile = (void (*)())(intptr_t)dlsym(library_handler, "ReadFromFile");
	
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }

	while (1)
	{

		if (size == -1)
		{
			break;
		}
		op1 = open(data->arr[size].fileName,O_RDONLY);
		(readFromFile)(op1,buffer);
		printf("Reader: Content to'%s'\n",data->arr[size].fileName);
		
//		ReleaseSemaphore(data->hSemWrite,1,NULL);
//		semop(data->semID, &(data->semBuffRead), 1);
		
		w=1;
//		semop(data->semID, &(data->semBuffWrite), 1);
	
		while(r!=1);
		r=0;
//		while (semctl(data->semID, 0, GETVAL, 0) != 1);
//		semop(data->semID, &(data->semBuffRead), 1);
		close(op1);
	}
	
	return 0;
}

void* ThreadWriter(void* fdata)
{		
	struct Data *data = (struct Data *)fdata;
	char *error;
	
	WriteInFile writeInFile = (void (*)())(intptr_t)dlsym(library_handler, "WriteInFile");
		if ((error = dlerror()) != NULL)  {
			fprintf (stderr, "%s\n", error);
			exit(1);
		}	
		
	int op2;
	remove("./Files/All.txt");
	op2 = open("./Files/All.txt",O_WRONLY|O_CREAT);
	
//	semop(data->semID, &(data->semBuffRead), 1);
	do
	{
//		semop(data->semID, &(data->semBuffRead), 1);
//		semop(data->semID, &(data->semBuffWrite), 1);		
		
		while(w!=1);
		w=0;
//		while (semctl(data->semID, 1, GETVAL, 0) != 1);
//		semop(data->semID, &(data->semBuffWrite), 1);
		
//		WaitForSingleObject(data->hSemWrite, INFINITE);
		(writeInFile)(op2,buffer);
		printf("Writer: Content to '%s'\n",data->arr[size].fileName);
		size--;
//		semop(data->semID, &(data->semBuffRead), 1);
		r=1;
		
//		semop(data->semID, &(data->semBuffWrite), 1);
//		ReleaseSemaphore(data->hSemRead,1,NULL);
	} while (size != -1);
	close(op2);
	return 0;
}


void CreateThreads(struct Data *data)
{
	library_handler = dlopen("./libj",RTLD_LAZY);
	
	if (!library_handler) {
        fputs (dlerror(), stderr);
        exit(1);
    }
	
	
	pthread_create(&(data->pThread[0]), NULL, &ThreadReader, data);
	pthread_create(&(data->pThread[1]), NULL, &ThreadWriter, data);	
}



void CreateSem(struct Data *data)
{
	int key = ftok("server.c", 's');  				//преобразование сущь. полное имя и целочисленный индикатор в значение типа key_t (ключ IPC)			
	data->semID = semget(key, 2, 0666 | IPC_CREAT);
	semctl(data->semID, 0, SETVAL, (int)0);
	semctl(data->semID, 1, SETVAL, (int)0);
	data->semBuffRead.sem_num = 0;
	data->semBuffRead.sem_op = 1;
	data->semBuffWrite.sem_num = 1;
	data->semBuffWrite.sem_op = 1;
}

void CloseApp(struct Data *data)
{
	pthread_join( data->pThread[0], NULL);
    pthread_join( data->pThread[1], NULL);

	
	printf("End\n");
	dlclose(library_handler);
}
