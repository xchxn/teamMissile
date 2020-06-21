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
element pop(int *n)
{
	element item,temp;
	int parent,child;
	item=heap[1];
	temp=heap[(*n)--];
	parent=1;
	child=2;
	while(child<=*n){
		if((child<*n)&&(heap[child].key>heap[child+1].key)) child++;
		if(temp.key<heap[child].key) break;
		heap[child/2]=heap[child];
		child*=2;
	}
	heap[child/2]=temp;
	return item;
}
int main()
{
	element a;
	int j;
	for(j=0;j<10;j++){
		scanf("%d",&a);
		push(a,&n);
	}
	printf("최소히프 ");
	for(j=1;j<=10;j++){
		printf("%d ",heap[j]);
	}
	printf("\n소팅 ");
	for(j=0;j<10;j++){
	printf("%d ",pop(&n));
	}
}
