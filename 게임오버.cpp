#include <stdio.h>
#include <windows.h>
using namespace std;

char q[110]={"  бсбсбс        бс        бсбсбсбс    бсбсбсбс     бсбсбсбс   бс      бс  бсбсбсбс  бсбсбсбс  \n"};
char w[110]={"бс             бсбс      бс  бс  бс   бс          бс      бс   бс    бс   бс        бс     бс \n"};
char e[110]={"бс            бс  бс     бс  бс  бс   бсбсбсбс    бс      бс    бс  бс    бсбсбсбс  бсбсбсбс  \n"};
char r[110]={"бс    бсбс   бсбсбсбс    бс  бс  бс   бс          бс      бс     бсбс     бс        бс     бс \n"};
char t[110]={"  бсбс  бс  бс      бс   бс  бс  бс   бсбсбсбс     бсбсбсбс       бс      бсбсбсбс  бс      бс\n"};

int main()
{	
	printf("\n");
	for(int i=0;i<110;i++){ 
		printf("%c",q[i]);
		Sleep(5);
	}
	for(int i=0;i<110;i++){
		printf("%c",w[i]);
		Sleep(5);
	}
	for(int i=0;i<110;i++){
		printf("%c",e[i]);
		Sleep(5);
	}
	for(int i=0;i<110;i++){
		printf("%c",r[i]);
		Sleep(5);
	}
	for(int i=0;i<110;i++){
		printf("%c",t[i]);
		Sleep(5);
	}

}
