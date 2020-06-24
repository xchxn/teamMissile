//Control Character()함수만 구현하면 됌 
class Character
{    
    private : 
		int x;		//캐릭터가 출력될 x좌표
    	int y;		//캐릭터가 출력될 y좌표
    	int size_x;		//캐릭터를 출력할 3*3크기
		int size_y;
    	char figure[10];	//캐릭터 생김새 배열 (3*3크기 출력될 예정)
    	char name[8];		//캐릭터 위에 뜰 이름 
    
	    float t_jump;		//중력 구현할 변수 
	    
	public :
		Character()		//생성자로 초기값 설정 
		{
			x = MAP_X_MAX / 2 + 1;
			y = MAP_Y_MAX / 2 + 1;
			size_x = 3;
			size_y = 3;
			
			//초기 캐릭터 모양 (3*3) 
			figure[0] = ' ';
			figure[1] = '0';
			figure[2] = ' ';
			figure[3] = '(';
			figure[4] = '|';
			figure[5] = ')';
			figure[6] = '_';
			figure[7] = '^';
			figure[8] = '_';
			figure[9] = '\0';
			
			name[0] = 'M';
			name[1] = 'r';
			name[2] = '.';
			name[3] = 'S';
			name[4] = 'o';
			name[5] = 'n';
			name[6] = 'g';
			name[7] = '\0';

			t_jump = 2;
		}
		void ControlCharacter()
		{
			bool move = FALSE;
			 
			if (GetAsyncKeyState(VK_LEFT) && x > 1) 	//kbhit하고 switch문으로도 해봤지만 뭔가 느림
			{											//키가 안눌렸을 때만  GetAsyncKeyState 0을 리턴.
				x -= 1;			//캐릭터의 출력 x좌표를 1 줄임 
				move = TRUE;
			}
			
			if (GetAsyncKeyState(VK_RIGHT) && x < MAP_X_MAX - 2) 
			{
				x += 1;
				move = TRUE;
			}
			
			if (GetAsyncKeyState(VK_UP) && y > 1 && y == 19)
				t_jump = 0;
		
			y -= 2;
			
			if (y < 19)	//캐릭터 그려주는 y위치는 16임. 거기에 y가 19가 될 때 까지 t_jump를 더함.(중력)  && 위화살표 누르면 t_jump를 0으로 만들어줘서 캐릭터가 y죄표 16에 가까이 위치하게 출력
			{
				
				if (t_jump < 4)
					t_jump += 0.3;
					
				y += floor(t_jump);    //floor는 내림함수 
				
				if (y > 19)
					y = 19;
			} 
			else 
			{
				
				t_jump = 0;
				y = 19;
			}	
		}
		
		//private영역에 있는 변수들 리턴
		int GetX(){return x;}
		int GetY(){return y;}
		int GetSizeX(){return size_x;}
		int GetSizeY(){return size_y;}
		char* Getfigure(){return figure;}
		char* Getname(){return name;}

};
		

