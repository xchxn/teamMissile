#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 6

int parent[MAX_SIZE];
void weightedUnion(int i,int j);
void weightedUnion2(int i,int j);
int collapsingFind(int i);
int main()
{	
	int i,j,count[MAX_SIZE];
	printf("Initial trees: ");
	for(i=0;i<6;i++){
		parent[i]=-1;
		printf("%d",parent[i]);
	}
	
	weightedUnion(0,4);
	weightedUnion(3,1);
	weightedUnion(2,5);
	printf("\n(b)연산\n");
	for(i=0;i<6;i++){
		printf("%d ",parent[i]);
	}
	weightedUnion(0,3);
	printf("\n(c)연산\n");
	for(i=0;i<6;i++){
		printf("%d ",parent[i]);
	}
	weightedUnion2(1,5);
	printf("\n(d)연산\n");
	for(i=0;i<6;i++){
		printf("%d ",parent[i]);
	}
	return 0;
}

void weightedUnion(int i,int j)
{	
	int tmp;
	tmp=parent[i]+parent[j];
	if(parent[i]>parent[j]){
		parent[i]=j;
		parent[j]=tmp;
	}
	else{
		parent[j]=i;
		parent[i]=tmp;
	}
}
void weightedUnion2(int i, int j)
{
    int k;
    int parenttmp[MAX_SIZE]={0};

    for (k=0;k<MAX_SIZE;k++){
        parenttmp[k]=parent[k];
    }
    int x=collapsingFind(i);
    int y=collapsingFind(j);

    if(parent[x]>parent[y]){
        parent[x]=y;
    }
    else{
        parent[y]=x;
    }
}
int collapsingFind(int i)
{
	int root,trail,lead;
	for(root=i;parent[root]>=0;root=parent[root]);
	for(trail=i;trail!=root;trail=lead){
		lead=parent[trail];
		parent[trail]=root;
	}
	return root;
}

