#include <stdio.h>
#define MAX_VERTICES 6
#define FALSE 0
#define TRUE 1

int cost[][MAX_VERTICES]={
	{0,50,45,10,1000,1000},
	{1000,0,10,15,1000,1000},
	{1000,1000,0,1000,30,30},
	{20,1000,1000,0,15,1000},
	{1000,20,15,1000,0,1000},
	{1000,1000,1000,1000,3,0}
};

int distance[MAX_VERTICES];
short int found[MAX_VERTICES];
int n=MAX_VERTICES;

void shortestPath(int v,int cost[][MAX_VERTICES],int distance[],int n,short int found[]);
int choose(int distance[],int n,short int found[]);

void main()
{
	int i; 
	shortestPath(0,cost,distance,n,found);
	for(i=1;i<MAX_VERTICES;i++){
	printf("정점 0에서 정점 %d 로의 최단경로 : %d \n",i,distance[i]);
	}
}

void shortestPath(int v,int cost[][MAX_VERTICES],int distance[],int n,short int found[])
{
	int i,u,w;
	for(i=0;i<n;i++){
		found[i]=FALSE;
		distance[i]=cost[v][i];
	}
	found[v]=TRUE;
	distance[v]=0;
	for(i=0;i<n-2;i++){
		u=choose(distance,n,found);
		found[u]=TRUE;
		for(w=0;w<n;w++){
			if(found[w]==FALSE){
				if(distance[u]+cost[u][w]<distance[w]){
					distance[w]=distance[u]+cost[u][w];
				}
			}
		}
	}
}
int choose(int distance[],int n,short int found[])
{
	int i,min,pos;
	min=999999;
	pos=-1;
	for(i=0;i<n;i++){
		if(distance[i]<min&&found[i]==FALSE){
		min=distance[i];
		pos=i;
		}
	}
	return pos;
}

