#include <stdio.h>
#include <stdlib.h>
typedef struct node *nodePointer;
typedef struct node{
	nodePointer llink;
	int data;
	nodePointer rlink;
}node;
void init(nodePointer head){
	head->llink=head;
	head->rlink=head;
};
void ddelete(nodePointer node,nodePointer deleted);
void dinsert(nodePointer node,nodePointer newnode);
void printnode(nodePointer node);

int main()
{	
	node hnode;
	nodePointer p[10];
	
	int i,s;
	init(&hnode);
	
	for(i=0;i<=5;i++){
	p[i]=(nodePointer)malloc(sizeof(node));
	scanf("%d",&s);
	p[i]->data=s;
	dinsert(&hnode,p[i]);
	}
	printnode(&hnode);
	printf("\n");
	
	for(i=0;i<=5;i++){
		if(p[i]->data==30){
			ddelete(&hnode,p[i]);
		}
	}
	printnode(&hnode);
	printf("\n");
	return 0;
}
void ddelete(nodePointer node,nodePointer deleted)
{	
	if(node==deleted) printf("ddd");
	else{
		deleted->llink->rlink=deleted->rlink;
		deleted->rlink->llink=deleted->llink;
		free(deleted);
	}
}
void dinsert(nodePointer node,nodePointer newnode)
{	
	newnode->llink=node;
	newnode->rlink=node->rlink;
	node->rlink->llink=newnode;
	node->rlink=newnode;
}
void printnode(nodePointer head)
{
	nodePointer p;
	for(p=head->llink;p!=head;p=p->llink){
		printf("%d ",p->data);
	}
}
