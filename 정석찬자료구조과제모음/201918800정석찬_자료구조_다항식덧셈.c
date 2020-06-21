#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int coft;
    int expn;
    struct Node* link;
}Node;

typedef struct ListHead{
    Node* head;
}ListHead;

ListHead* createLinkedList(void);
void addLastNode(ListHead* L,int coft,int expn);
void addPoly(ListHead* a,ListHead* b,ListHead* d);
void printPoly(ListHead* L);

int main(void)
{
    ListHead *a, *b, *d;
	
    a=createLinkedList();
    b=createLinkedList();
    d=createLinkedList();
    
    printf("다항식 a=");
    addLastNode(a,3,10);
    addLastNode(a,6,7);
    addLastNode(a,1,0);
    printPoly(a);
    
    printf("다항식 b=");
    addLastNode(b,2,14);
    addLastNode(b,-5,10);
    addLastNode(b,4,6);
    addLastNode(b,-7,0);
    printPoly(b);
    
    printf("a와 b를 더한 결과 다항식 d=");
    addPoly(a,b,d);
    printPoly(d);
}


ListHead* createLinkedList(void)
{
    ListHead* L;
    L=(ListHead *)malloc(sizeof(ListHead));
    L->head=NULL;
    return L;
}

void addLastNode(ListHead* L,int coft,int expn)
{
    Node* newNode;
    Node* p;
    newNode=(Node *)malloc(sizeof(Node));
    newNode->coft=coft;
    newNode->expn=expn;
    newNode->link=NULL;
    if(L->head==NULL){
        L->head=newNode;
        return;
    }
    else {
        p=L->head;
        while(p->link!=NULL){
            p=p->link;
        }
        p->link=newNode;
    }
}

void addPoly(ListHead* a,ListHead* b,ListHead* d)
{
    Node* pa=a->head;
    Node* pb=b->head;
    int s;
    
    while(pa&&pb){
        if(pa->expn==pb->expn){
            s=pa->coft+pb->coft;
            addLastNode(d,s,pa->expn);
            pa=pa->link; pb=pb->link;
        }
        else if(pa->expn>pb->expn){
            addLastNode(d,pa->coft,pa->expn);
            pa=pa->link;
        }
        else{
            addLastNode(d,pb->coft,pb->expn);
            pb=pb->link;
        }
    }
    for(;pa!=NULL;pa=pa->link){
        addLastNode(d,pa->coft,pa->expn);
    }
	for(;pb!=NULL;pb=pb->link){
        addLastNode(d,pb->coft,pb->expn);
	}
}
void printPoly(ListHead* L)
{	
	int i;
    Node* p=L->head;
    for(i=0;p;p=p->link,i++){
    	if(i!=0&&p!=NULL&&p->coft>0){
        	printf("+");
		}
        printf("%3.0dx^%d",p->coft,p->expn);
    }
    printf("\n");
}
