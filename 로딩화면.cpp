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

void Goto(int x,int y)
{
    COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void PrintLogo()
{

	cout<<"\n\n\n ";
		
	for(int i=0;i<111;i++){ 
		cout<<a[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<b[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<c[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<d[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<e[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<f[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<g[i];
		Sleep(5);
	}
	for(int i=0;i<111;i++){
		cout<<h[i];
		Sleep(5);
	}
}
void PrintLogo2()
{
	cout<<"\n\n\n";
		
	for(int i=0;i<111;i++){ 
		cout<<a[i];
	}
	for(int i=0;i<111;i++){
		cout<<b[i];
	}
	for(int i=0;i<111;i++){
		cout<<c[i];
	}
	for(int i=0;i<111;i++){
		cout<<d[i];
	}
	for(int i=0;i<111;i++){
		cout<<e[i];
	}
	for(int i=0;i<111;i++){
		cout<<f[i];
	}
	for(int i=0;i<111;i++){
		cout<<g[i];
	}
	for(int i=0;i<111;i++){
		cout<<h[i];
	}
}
void Loading()
{
	Goto(30,24);
	for(int i=0;i<=100;i=i+3){
		system("cls");
		PrintLogo2();
		cout<<"Loading..."<<i<<"% now";
		Sleep(100);
	}
	getchar();
}

int main()
{
	PrintLogo();
	Loading();
}

