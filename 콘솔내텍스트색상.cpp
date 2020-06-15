#define BLACK 0
#define BLUE  1
#define GREEN  2 
#define CYAN 3
#define RED  4 
#define MAGENTA  5 
#define BROWN  6 
#define LIGHTGRAY  7 
#define DARKGRAY  8 
#define LIGHTBLUE  9 
#define LIGHTGREEN 10 
#define LIGHTCYAN
#define LIGHTRED 12 
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#include <Windows.h>
#include <iostream>
using namespace std;

void textcolor(int foreground);

int main()
{
	for (int i = 0; i < 15; i++){
		textcolor(i);
		cout << "콘솔안에서 글자 색을 바꾸자!" << endl;
	}

}
void textcolor(int foreground)
{
	int color = foreground;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
