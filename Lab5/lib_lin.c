#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>



 #include <fcntl.h>

#define BUFFER_SIZE 512


void WriteInFile(int hFile, char* buff)
{
	write(hFile,buff,strlen(buff));	
}


void ReadFromFile(int hFile, char* buff)
{
	int n;
	memset(buff, 0, BUFFER_SIZE * sizeof(char));
	char temp[BUFFER_SIZE];
	do{
		memset(temp, 0, BUFFER_SIZE * sizeof(char));

		n=read (hFile,temp,sizeof(char));
		strcat(buff,temp);
	}while(n!=0);	
}