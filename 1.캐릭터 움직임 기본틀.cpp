#include <iostream>
#include <time.h>
#include <windows.h>
#define MAP_X_MAX 49
#define MAP_Y_MAX 17
using namespace std;

class Console	//콘솔창을 설정 관련 클래스 
{
	public:
		Console()	//생성자로 콘솔창 초기화 
		{
			system("title Name");		//Name에 나중에 정한 게임 이름 넣기 
		    system("mode con:cols=49 lines=17");	//맵 크기만큼 콘솔창 크기 설정 
		    
		    HANDLE hConsole;
		    CONSOLE_CURSOR_INFO ConsoleCursor;
		    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		    
		    ConsoleCursor.bVisible = 0; //커서 숨기기  
		    ConsoleCursor.dwSize = 1;
		    
		    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
		    
		    COORD Pos = { 0, 0 };
	    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);	//커서 위치를 0,0으로 설정 --> 0,0부터 mapData[]를 출력하기 위해서  
		}
		static void xy(int x,int y)
		{
			COORD Pos = { x, y };
	    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);	//커서 위치를 x,y으로 설정 --> 사용법 : Console::xy(0,0) ;
		}
};

class Map
{
	private: char mapData[MAP_Y_MAX][MAP_X_MAX];		//맵 생성 --- 화면크기의 문자열 
			 
	public: 
			Map()	//맵 초기화 생성자 
			{	
				for(int i = 0; i<MAP_Y_MAX; i++)
				{
					for(int j=0; j<MAP_X_MAX; j++)
					{
						mapData[i][j] = ' ';
					}
				}
			}
			void EditMap(int x, int y,char ch)	//콘솔창 (x,y)좌표의 값을  str로 설정 
			{
				if(x>0&& y>0 && x-1<MAP_X_MAX && y-1<MAP_Y_MAX)
				mapData[y-1][x-1] = ch;
			}
			void printMap()
			{	
				for (int i = 0; i < MAP_Y_MAX; i++)
					for(int j=0; j<MAP_X_MAX; j++)
						cout<<mapData[i][j];
			}
};

class character		//아직 미구현 상태. 테스트중 
{
	public: 
		
			char song[4][4]={
							{' ','@','@',' '},
							{'@','@','@','@'},
							{'@','@','@','@'},
							{' ','@','@',' '}
							};
	
};
int main() 
{
    
    Console();	//콘솔창 설정  
    Map mainMap;	//메인맵 생성 (횡스크롤 하는 맵) 
 	character s1;
 	
    int characterX = MAP_X_MAX / 2 + 1;
	int characterY = MAP_Y_MAX / 2 + 1;
    
    while(1) 
	{	
		
		
	
		Console::xy(0,0);			//다시 커서를 0,0으로 설정. ---> 0,0부터 다시 map배열을 출력하기 위해서  
		mainMap.EditMap(characterX,characterY,' ');		//x,y를 공백으로 초기화  --- 이거 안써주면 잔상이 남게됌. 
	
        if(GetAsyncKeyState(0x25) != 0 && characterX > 1)		//https://m.blog.naver.com/power2845/50143021565  --> GetAsyncKeyState 참조자료 
            characterX -= 1;	//위 화살표 입력시  
            
        if(GetAsyncKeyState(0x27) != 0 && characterX < MAP_X_MAX) 
            characterX += 1;
            
        if(GetAsyncKeyState(0x26) != 0 && characterY > 1)
            characterY -= 1;
            
        if(GetAsyncKeyState(0x28) != 0 && characterY < MAP_Y_MAX)
            characterY += 1;
             
		for(int i=0; i<4; i++)
					for(int j=0; j<4; j++)
						mainMap.EditMap(characterX+j,characterY+i,s1.song[i][j]);	//맵에 캐릭터 그리기 
        
		mainMap.printMap();
		
		for(int i=0; i<4; i++)
					for(int j=0; j<4; j++)
						mainMap.EditMap(characterX+j,characterY+i,' ');	//맵에 캐릭터 그린부분 공백으로 초기화해서 잔상 지우기  
        
        Sleep(50); 		//입력이 너무 빠르게 처리되면 안되므로 딜레이 줌. 
    }
}
//현재 main함수에 있는 캐릭터 움직이는 GetAsyncKeyState부분은 나중에 character클래스 만든 후 controlcharacter멤버함수에  넣어줄 예정. 
