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
    	bool direction;		//true=우측이동 , false=좌측이동 
    
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
			direction = TRUE;
			t_jump = 2;
		    leg_m = 1;				
		    t_leg = 0;
		}
		void ControlCharacter()
		{
			bool move = FALSE;
			 
			if (GetAsyncKeyState(VK_LEFT) && x > 1) 
			{											 
				x -= 1;	
				direction = FALSE;
				move = TRUE;
			}
			
			if (GetAsyncKeyState(VK_RIGHT) && x < MAP_X_MAX - 2) 
			{
				x += 1;
				direction = TRUE;
				move = TRUE;
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
		

