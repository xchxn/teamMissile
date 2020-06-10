class Map		//★나중에 이 클래스 상속해서 추가적으로 다른 맵 만들수 있도록 수정할 예정 
{	
	private :
		char ground[MAP_X_MAX];				//땅을 표현할 일차원 배열 	
		char mapData[MAP_X_MAX * MAP_Y_MAX];	 //1차원 배열을 가로크기MAP_X_MAX * 세로크기 MAP_Y_MAX로 표현. mapData를 지속적으로 출력함으로써 게임 움직임 구현. 
												 //주의점 : 콘송창 크기를 동일하게 배열의 크기와 동일하게 해야만 제대로 된 모양으로 출력됌.
	public :
		Map()
		{	
			fillArray(mapData, ' ' , MAP_X_MAX * MAP_Y_MAX);	//생성자로 mapData배열을 공백' '으로 초기화 
			fillArray(ground, '=', MAP_X_MAX);					//생성자로 ground배열을 '='로 초기화 
		}
		
		void fillArray(char arr[], char c, int max_value) 		//배열의 str[0]~str[max_value]을 문자 c로 채우는 함수 
		{	
			for (int i = 0; i < max_value; i++)
				arr[i] = c;
		}
		
		void EditMap(int x, int y, char str) 					//콘솔창의 x,y좌표를 str로 수정하는 함수.
		{
			if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)	 
			mapData[(y - 1) * MAP_X_MAX + x - 1] = str;				//(y-1)*MAP_X_MAX를 하면 콘솔창의 y번째 열을 나타낼 수 있음. 거기에 x-1를 더하면 (x,y)를 나타냄. 
																	//콘솔창의 (1,1)좌표 = 콘솔창의 좌측최상단 = mapData[0]을 의미
		}															//ex)  EditMap(1,1,'@')를 하면 콘솔창 좌측최상단에 @를 그림.
		
		void MakeGround() 		//땅 배열 ground를 mapData에 반영함으로써 땅 그리기
		{	
			Drawfigure(1, 22, MAP_X_MAX, 1, ground);
		}
		
		void Drawfigure(int x, int y, int size_x, int size_y, char figure[])	//EditMap함수를 for문 처리해서 x,y좌표를 넣으면 해당 좌표를 기준으로 size_x,size_y크기의 맵을 수정
		{
			for (int i = 0; i < size_y; i++)		//3개 열을 수정 
			{
				for (int j = 0; j < size_x; j++)		//3개 행을 수정
					EditMap(x + j, y + i, figure[i * size_x + j]);		//i*size_x는 1행,2행,3행을 표현. j는 열을 표현.
			}
		}
		
		void printMap()
		{
			cout<<mapData;		//맵 출력		
		}
		
		char* GetMapData(){return mapData;}		//private영역에 있는 mapData[]의 주소 리턴 
	
};
