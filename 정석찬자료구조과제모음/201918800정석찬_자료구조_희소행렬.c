#include <stdio.h>
#define MAX_TERMS 10
typedef struct{
	int col;
	int row;
	int value;
}term;
void transpose(term a[],term b[])
{
	int n,i,j,currentb;
	n=a[0].value;
	b[0].row=a[0].col;
	b[0].col=a[0].row;
	b[0].value=n;
	if(n>0){
		for(i=0;i<a[0].col;i++){
			for(j=1;j<=n;j++){
				if(a[j].col==i){
					b[currentb].row=a[j].col;
					b[currentb].col=a[j].row;
					b[currentb].value=a[j].value;
					currentb++;
				}
			}
		}
	}
}
int main()
{	
	term a[MAX_TERMS]={{6,6,9},{0,0,10},{0,3,22},{0,5,-15},{1,1,11},{1,2,3},{2,3,6},{3,4,20},{4,0,71},{5,2,-2}};
	term b[MAX_TERMS];
	int i;
	for(i=0;i<=9;i++){
	printf("%d %d %d\n",a[i].col,a[i].row,a[i].value);
	}	
	printf("transpose\n");	transpose(a,b);
	for(i=0;i<a[0].value;i++){
	printf("%d %d %d\n",b[i].col,b[i].row,b[i].value);
	}
	return 0;
}

