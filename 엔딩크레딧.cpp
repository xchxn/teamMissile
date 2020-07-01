#include <iostream>
#include <windows.h>
#define STRINGSIZE 9 


using namespace std;

string a[STRINGSIZE]={"Team Missile","전북대학교","IT정보공학과","창의적IT공학설계입문","201515300 장우석","201912388 오준혁","201912430 조민서","201918800 정석찬","Thank you"};

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
	for(int i=n;i<STRINGSIZE;i++){
		cout<<"\t\t\t"<<a[i]<<"\n";
	}
	Sleep(1000);
	system("cls");
}
int main()
{	
	PrintEnding(0,1,19);
	PrintEnding(1,1,18);
	PrintEnding(2,1,17);
	PrintEnding(3,1,16);
	PrintEnding(4,1,15);
	PrintEnding(5,1,14);
	PrintEnding(6,1,13);
	PrintEnding(7,1,12);
	PrintEnding(8,1,11);
	PrintEnding(9,1,10);
	PrintEnding2(0,1,9);
	PrintEnding2(1,1,8);
	PrintEnding2(2,1,7);
	PrintEnding2(3,1,6);
	PrintEnding2(4,1,5);
	PrintEnding2(5,1,4);
	PrintEnding2(6,1,3);
	PrintEnding2(7,1,2);
	PrintEnding2(8,1,1);
}
