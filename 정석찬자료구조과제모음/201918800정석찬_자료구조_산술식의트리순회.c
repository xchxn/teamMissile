#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct node *nodePointer;
typedef struct node{
	char data;
	nodePointer leftChild;
	nodePointer rightChild;
}node;
nodePointer queue[MAX_QUEUE_SIZE];
int front;
int rear;

node A1={'A',NULL,NULL};
node A2={'B',NULL,NULL};
node A3={'*',&A1,&A2};
node A4={'E',NULL,NULL};
node A5={'F',NULL,NULL};
node A6={'/',&A4,&A5};
node A7={'C',NULL,NULL};
node A8={'D',NULL,NULL};
node A9={'-',&A3,&A7};
node A10={'+',&A8,&A6};
node A11={'/',&A9,&A10};
node *root=&A11;

void postorder(nodePointer ptr);
void levelorder(nodePointer ptr);
void addq(nodePointer item);
nodePointer deleteq();


int main()
{
	printf("postorder:");
	postorder(root);
	printf("\n");
	printf("levelorder:");
	levelorder(root);
	return 0;
}

void postorder(nodePointer ptr)
{
	if(ptr){
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c",ptr->data);
	}
}
void levelorder(nodePointer ptr)
{
	front=0;
	rear=0;
	nodePointer queue[MAX_QUEUE_SIZE];
	if(!ptr) return;
	addq(ptr);
	for(;;){
		ptr=deleteq();
		if(ptr){
			printf("%c",ptr->data);
			if(ptr->leftChild) addq(ptr->leftChild);
			if(ptr->rightChild) addq(ptr->rightChild);
		}
		else break;	
	}
}
void addq(nodePointer item)
{
	if(rear==MAX_QUEUE_SIZE-1)return;
	rear++;
	queue[rear]=item;
}
nodePointer deleteq()
{
	nodePointer node=NULL;
	if(front==rear) return node;
	front++;
	node=queue[front];
	return node;
}
