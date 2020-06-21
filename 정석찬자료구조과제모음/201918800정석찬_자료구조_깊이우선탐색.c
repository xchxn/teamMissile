#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 9

typedef struct node *nodePointer;
typedef struct node{
	int vertex;
	nodePointer link;
}node;
nodePointer graph[MAX_VERTICES];
short int visited[MAX_VERTICES];
void dfs(int v);
void print_adlist(int i);
void insert_edge(int u,int v);
void init();
int main()
{
	int v,i,x,y;
	printf("인접리스트\n");
	init();
	for(i=0;i<100;i++){
		scanf("%d",&x);
		if(x==9)break;
		scanf("%d",&y);
		insert_edge(x,y);
	}
	for(i=0;i<9;i++){
		print_adlist(i);
	}	
	printf("시작 노드 입력:");
	scanf("%d",&v);
	dfs(v);
	return 0;	
}
void dfs(int v)
{
	nodePointer w;
	visited[v]=TRUE;
	printf("%3d",v);
	for(w=graph[v];w;w=w->link){
		if(!visited[w->vertex]){
			dfs(w->vertex);
		}
	}
}
void print_adlist(int i)
{
	nodePointer h;

	printf("%d 노드의 인접리스트:",i);
	h=graph[i];
	while(h){
		printf("->%d",h->vertex);
		h=h->link;	
	}
	printf("\n");
}
void insert_edge(int u,int v)
{
	nodePointer nd;
	nd=(nodePointer)malloc(sizeof(node));
	nd->vertex=v;
	nd->link=graph[u];
	graph[u]=nd;
}
void init()
{
	int i;
	for(i=0;i<9;i++){
		graph[i]=NULL;
	}
}
