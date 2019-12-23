#include<stdio.h>
#include<string.h>
#include "mymalloc.h"

void initialization()
{
	start=(void *)memory;

	start->size=25000-(sizeof(data));
	start->status='F';
	start->next=NULL;
}

void display()
{
	data *ptr;
    ptr = start;

	printf("\n-------------------------------------------------\n");
    printf("ADDRESS");
    printf("\t\t|\tSTATUS");
    printf("\t|\tSIZE\t|");

    while(ptr!=NULL)
	{
        printf("\n-------------------------------------------------\n");
        printf("|%p",ptr);
        printf("\t|\t %c",ptr -> status);
        printf("\t|\t %d\t|",ptr->size);
        ptr = ptr -> next;
    }
	printf("\n-------------------------------------------------\n\n\n");
}

void * MyMalloc(int blockSize)
{
	
	if(blockSize<=0)
	{
		printf("Invalied Size");	
		return 0;
	}

	if(start==NULL){
		initialization();
	}

	data *ptr,*newdata;
	
	int slotSize=(blockSize+sizeof(data));
	
	ptr=start;  

	while(ptr!=NULL)
	{
		int Size = ptr->size;

		if(ptr->status=='F' && ptr->size>=blockSize){
			
			newdata = ptr;
			newdata->size=blockSize;
			newdata->status='A';
		
			//set freeblock
			if(Size!=blockSize){
				
				data *temp;
				temp=(void *)ptr+slotSize;
				temp->size=Size - slotSize;
				temp->next=ptr->next;
				
				newdata->next=temp;
				temp->status='F';
			}

			else
				newdata->next=ptr->next;//size=blocksize

			break;
		}
		ptr=ptr->next;
	}

	if(ptr == NULL)
	{
		printf("\nERROR: COULDN'T FIND A SUFFICENT MEMORY BLOCK FOR %d",blockSize);//not free space for blocksize
		return ptr;
	}
	else
		return (newdata+sizeof(data));//starting address of next free block
	
}

void myfree(void* address)
{
	data *ptr=address;
	ptr = ptr-sizeof(data);
	if(((void *)ptr>=(void*)memory) && ((void *)ptr<(void *)(memory+25000)))
	{
		ptr->status = 'F';
		
		data *pretemp,*temp,*nexttemp;
		temp = start;
		
		while(temp!=ptr)
		{
			pretemp = temp;
			temp = temp->next;
		}

		nexttemp=ptr->next;

		if(ptr==start){ //free-first block
			if(nexttemp->status=='F'){
	
				ptr->size=(ptr->size+nexttemp->size+sizeof(data));
				ptr->next=nexttemp->next;
			}
		}
		else if(ptr->next==NULL){  //free last block

			if(pretemp->status=='F'){ //preblock free
				pretemp->size=(pretemp->size+ptr->size+sizeof(data));
				pretemp->next=NULL;
				ptr=pretemp;			
			}
			else if(pretemp->status=='A'){
				ptr->next=NULL;
			}
		}

		else{
			
			if(pretemp->status=='F' && nexttemp->status=='F'){	// |F |A |F |
			
				pretemp->size=(pretemp->size+ptr->size+nexttemp->size+(2*sizeof(data)));
				pretemp->next=nexttemp->next;
				ptr=pretemp;
			}
			else if(nexttemp->status=='F'){ // |A |A |F
			
				ptr->size=(ptr->size+nexttemp->size+sizeof(data));
				ptr->next=nexttemp->next;
			
			}
			else if(pretemp->status=='F'){ //|F |A |A
			
				pretemp->size=(pretemp->size+ptr->size+sizeof(data));
				pretemp->next=ptr->next;
				ptr=pretemp;	
			}
			
		}
		
	}
	else
		printf("\nERROR: INVALIED ADDRESS");
	
}


