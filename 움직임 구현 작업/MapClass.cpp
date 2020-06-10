class Map
{	
	private :
		char ground[MAP_X_MAX];					
		char mapData[MAP_X_MAX * MAP_Y_MAX];	 
												 
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
