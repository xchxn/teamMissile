#include <windows.h>	//이 헤더파일 필요! 

class ConsoleSet		//콘솔창 설정 클래스.
{
	public : 
		ConsoleSet() //생성자를 통해 콘솔창 설정 
		{			
			system("mode con:cols=130 lines=32");	//콘솔창의 가로 세로 크기를 맵과 동일하게 설정 
			system("title Team Missile");
				
			HANDLE hConsole;
		    CONSOLE_CURSOR_INFO ConsoleCursor;
		    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			    
		    ConsoleCursor.bVisible = 0;		//커서 안보이게 
		    ConsoleCursor.dwSize = 1;		//커서 백분율 크기 1로 
		    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
		}
		
		static void gotoxy(short _x, short _y) 		//ConsloeSet::gotoxy 형식으로 쓸수 있도록 static 함수로 선언.  _x,_y 좌표로 커서 이동 
		{
        COORD Cur;
        Cur.X = _x;
        Cur.Y = _y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
    	}
};
