#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

int nfind(char *string,char *pat)
{
	int i,j,start=0;
	int lasts=strlen(string)-1;
	int lastp=strlen(pat)-1;
	int endmatch=lastp;
		
	for(i=0;endmatch<=lasts;endmatch++,start++){
		if(string[endmatch]==pat[lastp])
			for(j=0,i=start;j<lastp&&string[i]==pat[j];i++,j++);
		if(j==lastp)
			return start;
		}
		return -1;
}

int main()
{
	char s[MAX_SIZE]={"ababbaababaaabaca"},*string=s;
	char p[MAX_SIZE]={"abac"}, *pat=p;
	int pos;
	pos=nfind(s,p);
	if(pos==-1){
		printf("찾을수없음.\n");
	}
	else{
	printf("패턴시작위치:%d\n",pos);
	}
}
