void DrawSprite(int x, int y, int size_x, int size_y, const char spr[]) {   //(x,y)를 기준으로 size_x*size_y크기로 spr[]을 그림 
   for (int i = 0; i < size_y; i++) {
      for (int n = 0; n < size_x; n++)
         EditMap(x + n, y + i, spr[i * size_x + n]);
   }
}

int main()
{
	
	char sprite_spider[] ={"|                | |      ##      |  --    {  }    --    |  {    }  |      |-{  --  }-|        { ---- }     |  --{ ---- }--  | -/  {  --  }  \\-     / {    } \\       / { 0000 } \\     -   { 00 }   -   |  /{      }\\  | |  |  \\()()/  |  ||  |   ||||   |  || /    \\/\\/    \\ || |            | |  |            |    |            |  "};
	
}
