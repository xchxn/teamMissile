#include <iostream>
#include <windows.h>
#include <string>

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
		cout<<a[i]<<"\n";
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
}
