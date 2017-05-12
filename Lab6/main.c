#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int has_initialized = 0;
void *managed_memory_start;		//начало управляемой памяти
void *last_valid_address;		//последний валидный адрес



struct mem_control_block {
	int is_available;			//блок занят да/нет
	int size;				//его размер
};


/* находим текущую системную границу*/
void malloc_init()
{
	last_valid_address = sbrk(0);
	managed_memory_start = last_valid_address;	//пока память пуста
	has_initialized = 1;	//всё проинициализировано
}

void free_new(void *firstbyte) {
	struct mem_control_block *mcb;

	mcb = (struct mem_control_block *)((uint8_t*)firstbyte - sizeof(struct mem_control_block));		//по указателю воостанивливаем структуру

	mcb->is_available = 1;	//помечаем блок как свободный

return;
}

void *malloc_new(long numbytes) {
	
	void *current_location;	
	struct mem_control_block *current_location_mcb;	
	void *memory_location;
	
	if(! has_initialized) {
		malloc_init();
	}
	
	numbytes = numbytes + sizeof(struct mem_control_block); //память для управляющего блока
	
	memory_location = 0;
	
	current_location = managed_memory_start;
	
	while(current_location != last_valid_address)
	{	
		current_location_mcb =
		(struct mem_control_block *)current_location;
		if(current_location_mcb->is_available)
		{
			if(current_location_mcb->size >= numbytes)
				{			
				current_location_mcb->is_available = 0;			
				memory_location = current_location;			
				break;
			}
		}

		current_location = (void*)((uint8_t*)current_location+ current_location_mcb->size);
	}
	
	if(! memory_location)
	{
	
		sbrk(numbytes);
		
		memory_location = last_valid_address;
		
		last_valid_address = (void*)((uint8_t*)last_valid_address + numbytes);
		
		current_location_mcb = memory_location;
		current_location_mcb->is_available = 0;
		current_location_mcb->size = numbytes;
	}
	
	memory_location = (void*)((uint8_t*)memory_location + sizeof(struct mem_control_block));
	
	return memory_location;
}


void *realloc_new(void *ptr, size_t size) {
	struct mem_control_block *mcb;
	
	mcb = (struct mem_control_block *)((uint8_t*)ptr - sizeof(struct mem_control_block));
	
  void *nptr = malloc_new(size);
  if (nptr == NULL) {
    return NULL;
  }
  
  memcpy(nptr, ptr, mcb->size);

	free_new(ptr);
  return nptr;
}

int main(){
	printf("Work\n");

	int *test;
	printf("Для выхода нажмите 0\n");
	int n=0;
	int a;
	
	do{
		
		printf("Ввдите число: ");
		scanf("%d",&a);
		if(a==0){
			break;
		}
		if(n==0){
			test = (int *)malloc_new(sizeof(int));
		}
		else{
			test = (int *)realloc_new(test,(n+1)*sizeof(int));
		}		
		test[n]=a;
	
		n++;	
		
	}while(1);


	
	for(int i=0;i<n;i++){
		printf("%d__",test[i]);
	}
	free_new(test);
	printf("\n");
	return 0;
}