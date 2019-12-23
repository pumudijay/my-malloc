#include<stdio.h>
#include<string.h>
#include 'mymalloc.h'


void main(){
	intialization();
	int *a = (int *)allocation(20*sizeof(int));
	int *b = (int *)allocation(20*sizeof(int));
	int *c = (int *)allocation(20*sizeof(int));
	int *d = (int *)allocation(20*sizeof(int));
	int *e = (int *)allocation(20*sizeof(int));
	display();
	//myfree(c);
	//myfree(d);
	myfree(a);
	myfree(b);
	//myfree(e);
	printf("\n*******************\n");
	display();
}

