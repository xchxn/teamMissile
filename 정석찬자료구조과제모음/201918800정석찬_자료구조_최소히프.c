#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200

typedef struct{
	int key;
}element;
element heap[MAX_ELEMENTS];
int n=0;

void push(element item,int *n)
{
	int i=++(*n);
	while((i!=1)&&(item.key<heap[i/2].key)){
		heap[i]=heap[i/2];
		i/=2;
	}
	heap[i]=item;
}
int main()
{
	element a;
	int j;
	printf("키입력: ");
	for(j=0;j<10;j++){
		scanf("%d",&a);
		push(a,&n);
	}
	printf("구성된 최소히프:");
	for(j=1;j<=10;j++){
		printf("%d ",heap[j]);
	}
}
