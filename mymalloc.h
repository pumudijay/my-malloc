#include<stdio.h>


struct metadata_block{
	int size;
	char status;
	struct metadata_block *next;
	
};
typedef struct metadata_block data;

char memory[25000];
data *start;

void initialization();
void display();
void * MyMalloc(int blockSize);
void myfree(void* address);
