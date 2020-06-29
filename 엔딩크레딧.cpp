#include <iostream>
#include <windows.h>


using namespace std;

string a[6]={"Team Missile","201515300 장우석","201912388 오준혁","201912430 조민서","201918800 정석찬","Thank you"};

void Goto(int x,int y)
{
    COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void PrintEnding(int n,int x,int y)
{
	Goto(x,y);
	for(int i=0;i<n;i++){
		cout<<"\t\t\t"<<a[i]<<"\n";
	}
	Sleep(1000);
	system("cls");
}
void PrintEnding2(int n,int x,int y)
{
	Goto(x,y);
	for(int i=n;i<6;i++){
		cout<<"\t\t\t"<<a[i]<<"\n";
	}
	Sleep(1000);
	system("cls");
}
int main()
{	
	PrintEnding(0,1,32);
	PrintEnding(1,1,31);
	PrintEnding(2,1,30);
	PrintEnding(3,1,29);
	PrintEnding(4,1,28);
	PrintEnding(5,1,27);
	PrintEnding(6,1,26);
	PrintEnding2(0,1,24);
	PrintEnding2(1,1,23);
	PrintEnding2(2,1,22);
	PrintEnding2(3,1,21);
	PrintEnding2(4,1,20);
	PrintEnding2(5,1,19);
}
