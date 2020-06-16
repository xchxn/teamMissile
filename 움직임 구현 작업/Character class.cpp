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
		Character();	//private 변수들 초기화 예정 
		void ControlCharacter();
		
		//private영역에 있는 변수들 리턴
		int GetX(){return x;}
		int GetY(){return y;}
		int GetSizeX(){return size_x;}
		int GetSizeY(){return size_y;}
		char* Getfigure(){return figure;}
		char* Getname(){return name;}

};
		

