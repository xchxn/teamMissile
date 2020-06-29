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

	string a[6]={"Team Missile","201515300 장우석","201912388 오준혁","201912430 조민서","201918800 정석찬","Thank you"};
	PrintEnding(4,1,32);
	Goto(1,32);
	cout<<a[0];
	Sleep(1000);
	system("cls");
	Goto(1,31);
	cout<<a[0]<<"\n"<<a[1];
	Sleep(1000);
	system("cls");
	Goto(1,30);
	cout<<a[0]<<"\n"<<a[1]<<"\n"<<a[2];
	Sleep(1000);
	system("cls");
	Goto(1,29);
	cout<<a[0]<<"\n"<<a[1]<<"\n"<<a[2]<<"\n"<<a[3];
	Sleep(1000);
	system("cls");
	Goto(1,28);
	cout<<a[0]<<"\n"<<a[1]<<"\n"<<a[2]<<"\n"<<a[3]<<"\n"<<a[4];
	Sleep(1000);
	system("cls");
	Goto(1,27);
	cout<<a[0]<<"\n"<<a[1]<<"\n"<<a[2]<<"\n"<<a[3]<<"\n"<<a[4]<<"\n"<<a[5];
	Sleep(1000);
	system("cls");
	Goto(1,26);
	cout<<a[1]<<"\n"<<a[2]<<"\n"<<a[3]<<"\n"<<a[4]<<"\n"<<a[5];
	Sleep(1000);
	system("cls");
	Goto(1,25);
	cout<<a[2]<<"\n"<<a[3]<<"\n"<<a[4]<<"\n"<<a[5];
	Sleep(1000);
	system("cls");
	Goto(1,24);
	cout<<a[3]<<"\n"<<a[4]<<"\n"<<a[5];
	Sleep(1000);
	system("cls");
	Goto(1,23);
	cout<<a[4]<<"\n"<<a[5];
	Sleep(1000);
	system("cls");
	Goto(1,22);
	cout<<a[5];
	
}
