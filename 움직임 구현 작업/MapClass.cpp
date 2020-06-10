class Map		//★나중에 이 클래스 상속해서 추가적으로 다른 맵 만들수 있도록 수정할 예정 
{	
	private :
		char ground[MAP_X_MAX];				//땅을 표현할 일차원 배열 	
		char mapData[MAP_X_MAX * MAP_Y_MAX];	 //1차원 배열을 가로크기MAP_X_MAX * 세로크기 MAP_Y_MAX로 표현. mapData를 지속적으로 출력함으로써 게임 움직임 구현. 
												 //주의점 : 콘송창 크기를 동일하게 배열의 크기와 동일하게 해야만 제대로 된 모양으로 출력됌.
	public :
		Map()
		{	
			fillArray(mapData, ' ' , MAP_X_MAX * MAP_Y_MAX);	
			fillArray(ground, '=', MAP_X_MAX);				
		}
		
		void fillArray(char arr[], char c, int max_value) 
		{	
			for (int i = 0; i < max_value; i++)
				arr[i] = c;
		}
		
		void EditMap(int x, int y, char str) 		
		{
			if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)	 
			mapData[(y - 1) * MAP_X_MAX + x - 1] = str;						
		}
		
		void MakeGround() 
		{	
			Drawfigure(1, 22, MAP_X_MAX, 1, ground);
		}
		
		void Drawfigure(int x, int y, int size_x, int size_y, char figure[])	
		{
			for (int i = 0; i < size_y; i++)
			{
				for (int j = 0; j < size_x; j++)
					EditMap(x + j, y + i, figure[i * size_x + j]);	
			}
		}
		
		char* GetMapData(){return mapData;}
		
		void printMap()
		{
			cout<<mapData;				
		}
};
