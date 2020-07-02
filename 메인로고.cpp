#include <iostream>
#include <windows.h>
using namespace std;

char a[111]={"   бсбсбсбсбсбсбсбс            бс                бсбс      бс           бсбсбсбсбсбсбс         бсбс        бс\n"};
char b[111]={"                 бс          бс  бс            бс    бс    бс           бс          бс     бсбсбсбсбсбс    бс\n"};
char c[111]={"                 бс        бс      бс        бс        бс  бс           бс          бс       бс    бс      бс\n"};
char d[111]={"                 бс      бс          бс      бс        бс  бс           бс          бс       бс    бс  бсбсбс\n"};
char e[111]={"       бс    бс                                бс    бс    бс           бсбсбсбсбсбсбс         бсбс        бс\n"};
char f[111]={"       бс    бс        бсбсбсбсбсбсбсбсбс        бсбс      бс                 бс                   бсбсбсбсбс\n"};
char g[111]={"       бс    бс                бс                          бс                 бс                   бс      бс\n"};
char h[111]={" бсбсбсбсбсбсбсбсбсбс          бс          бсбсбсбсбсбсбсбсбс         бсбсбсбсбсбсбсбсбс           бсбсбсбсбс\n"};

void PrintLogo()
{
	
	printf("\n\n\n ");
		
	for(int i=0;i<111;i++){ 
		printf("%c",a[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",b[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",c[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",d[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",e[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",f[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",g[i]);
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		printf("%c",h[i]);
		Sleep(5);
	}
}
int main()
{
	PrintLogo();
}
