#include <iostream>
#include <math.h>
#include <ctime>
#include <windows.h>
#define MAP_X_MAX 130
#define MAP_Y_MAX 32
#define FALSE 0
#define TRUE 1

using namespace std;

class ConsoleSet {      //콘솔창 설정 클래스. Console::SetCon 
public : 
    ConsoleSet() //생성자를 통해 콘솔창 설정 
    {         
        system("mode con:cols=130 lines=32");   //콘솔창의 가로 세로 크기를 맵과 동일하게 설정 
        system("title Team Missile");

        HANDLE hConsole;
        CONSOLE_CURSOR_INFO ConsoleCursor;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        ConsoleCursor.bVisible = 0;      //커서 안보이게 
        ConsoleCursor.dwSize = 1;      //커서 백분율 크기 1로 
        SetConsoleCursorInfo(hConsole , &ConsoleCursor);
    }

    static void gotoxy(short m_x, short m_y)       //ConsloeSet::형식으로 쓸수 있도록 static 함수로 선언 
    {//커서이동함수
        COORD Cur;
       Cur.X = m_x;
        Cur.Y = m_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
    }
};

class Character
{    
private : 
    int x;      //캐릭터가 출력될 x좌표
    int y;      //캐릭터가 출력될 y좌표
    int size_x;      //캐릭터를 출력할 3*3크기 
    int size_y;
    char figure[10];      //캐릭터 생김새 배열 (3*3크기 출력될 예정) 
    char name[32];
    int lv;
    int hp,hpm;
    int exp,expi;
    int power;
    int wepon;         //무기 종류     
    float t_jump;


public :
    char* figure_invenWeapon;
    char rightweaponFigure[4];
    bool attack;
    int weaponX;
    int weaponY;
    bool direction;         //true=우측이동 , false=좌측이동

    Character()      //생성자로 초기값 설정 
    {
        x = 60;
        y = 19;
        size_x = 3;
        size_y = 3;
        lv = 1;
        hpm = 100;
        hp = hpm;
        exp = 0;
        expi = 100;
        power = 10;
        wepon = 0;
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

        attack = FALSE;   
        //인벤토리 내 무기 모양 
        figure_invenWeapon= " ――>";

        //캐릭터가 들고 있는 무기 모양    
        rightweaponFigure[0] = 'o';
        rightweaponFigure[1] = '-';
        rightweaponFigure[2] = '-';   
        rightweaponFigure[3] = '-';     
    }

    void ControlCharacter() {   
        bool move = FALSE;
        weaponX = x+2;
        weaponY = y+1;
         //무기 출력 위치 
        if (GetAsyncKeyState(0x5A))    //공격키 눌리면 
            attack = TRUE;

        if (GetAsyncKeyState(VK_LEFT) && x > 1) {     //kbhit하고 switch문으로도 해봤지만 뭔가 느림                                //키가 안눌렸을 때만  GetAsyncKeyState 0을 리턴. 
            x -= 1;      //캐릭터의 출력 x좌표를 1 줄임 
            direction = FALSE;
            move = TRUE;
        }

        if (GetAsyncKeyState(VK_RIGHT) && x < MAP_X_MAX - 2) 
        {
            x += 1;
            direction = TRUE;
            move = TRUE;
        }
        if (GetAsyncKeyState(VK_UP) && y > 1 && y == 19)
            t_jump = 0;
        y -= 2;      
        if (y < 19) { //캐릭터 그려주는 y위치는 16임. 거기에 y가 19가 될 때 까지 t_jump를 더함.(중력)  && 위화살표 누르면 t_jump를 0으로 만들어줘서 캐릭터가 y죄표 16에 가까이 위치하게 출력 
            if (t_jump < 3)
               t_jump += 0.5;
            y += floor(t_jump);      //floor는 내림함수 
            if (y > 19)
               y = 19;
        } 
        else {
           t_jump = 0;
            y = 19;
        }
        if (direction == TRUE) {     //캐릭터가 우측방향을 보고있으면    
           figure[3] = '('; figure[5] = 'o';      //몸통부분 돌리기     
            rightweaponFigure[0] = 'o';
            rightweaponFigure[3] = '-';
        } 
        else {              //캐릭터가 왼쪽방향을 보고있으면  
            figure[3] = 'o'; figure[5] = ')';       //몸통부분 돌리기 
            rightweaponFigure[0] = '-';
            rightweaponFigure[3] = 'o';
            weaponX = x-3;
            weaponY = y+1;
        }
      }
      //private영역에 있는 변수들 리턴 
      int GetX(){return x;}
      int GetY(){return y;}
      int GetSizeX(){return size_x;}
      int GetSizeY(){return size_y;}
      char* Getfigure(){return figure;}
      char* Getname(){return name;}
      int GetHp(){return hp;}
      int GetHpm(){return hpm;}
      int GetLv(){return lv;}
      int GetExp(){return exp;}
      int GetExpi(){return expi;}
      int GetPower(){return power;}
};



class Monster {
    private : 
       int x;      //캐릭터가 출력될 x좌표
        int y;      //캐릭터가 출력될 y좌표
        int size_x;      //캐릭터를 출력할 3*3크기 
        int size_y;      //캐릭터 생김새 배열 (3*3크기 출력될 예정) 
        char monster[16];
        float t_jump;
        
		int boss_x;
        int boss_y;
        int boss_size_x;
        int boss_size_y;
        char boss[36];
      

   public :
      Monster()      //생성자로 초기값 설정 
      {
         x = 3;
         y = 2;

         t_jump = 4;         

         size_x = 4;
         size_y = 4;

         //초기 캐릭터 모양 (3*3) 
         monster[0] = ' ';
         monster[1] = '_';
         monster[2] = '_';
         monster[3] = ' ';
         monster[4] = '(';
         monster[5] = '*';
         monster[6] = '*';
         monster[7] = ')';
         monster[8] = '-';
         monster[9] = '-';
         monster[10] = '-';
         monster[11] = '-';
         monster[12] = ' ';
         monster[13] = ' ';
         monster[14] = ' ';
         monster[15] = ' ';   
      }

      void Monster_Move() {   
            int num = rand()%3;
            if (num == 0 && x >= 3)
                x -= 2; 
            if (num == 1 && x < MAP_X_MAX - 3)
                x += 2;
            if (y < 19) {
                t_jump = 2;
            y=y-2; 
          }

            if (y <19)  //캐릭터 그려주는 y위치는 19~22임. 거기에 y가 19가 될 때 까지 t_jump를 더함.(중력)  && 위화살표 누르면 t_jump를 0으로 만들어줘서 캐릭터가 y죄표 16에 가까이 위치하게 출력 
            {    
               if (t_jump < 3)
            t_jump += 1;                       
               y += floor(t_jump); 
            if(y>=19) {
               t_jump=0;
               y=19;
            }                 
            }
            else {
               t_jump=0;
               y=19;
         }
      }

      int GetX(){return x;}
      int GetY(){return y;}
      int GetSizeX(){return size_x;}
      int GetSizeY(){return size_y;}
      char* GetMonster(){return monster;}

};

class Map
{   
    private :
       char ground[MAP_X_MAX];                  //땅을 표현할 일차원 배열 
       char mapData[MAP_X_MAX * MAP_Y_MAX];      //1차원 배열을 가로크기MAP_X_MAX * 세로크기 MAP_Y_MAX로 표현. mapData를 지속적으로 출력함으로써 게임 움직임 구현. 
            //주의점 : 콘송창 크기를 동일하게 배열의 크기와 동일하게 해야만 제대로 된 모양으로 출력? . 
    public :
       Character * Song;
       Monster * newMon[100];

       Map() {   
        Song = new Character();
        fillArray(mapData, ' ' , MAP_X_MAX * MAP_Y_MAX);      //생성자로 mapData배열을 공백' '으로 초기화 
        fillArray(ground, '=', MAP_X_MAX);         //생성자로 ground배열을 '='로 초기화 
        }


    void fillArray(char arr[], char c, int max_value) {   //배열의 str[0]~str[max_value]을 문자 c로 채우는 함수    
        for (int i = 0; i < max_value; i++)
           arr[i] = c;
    }

    void EditMap(int x, int y, char str) {       //콘솔창의 x,y좌표를 str로 수정하는 함수.  콘솔창의 좌측최상단이 (1,1)임. 
         if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)      //mapData는 (MAP_X_MAX*MAP_Y_MAX)사이즈 
         mapData[(y - 1) * MAP_X_MAX + x - 1] = str;                  //(y-1)*MAP_X_MAX를 하면 콘솔창의 y번째 열을 나타낼 수 있음. 거기에 x-1를 더하면 (x,y)를 나타냄. 
                                                         //콘솔창의 (1,1)좌표 = 콘솔창의 좌측최상단 = mapData[0]을 의미
                                                         //ex)  EditMap(1,1,'@')를 하면 콘솔창 좌측최상단에 @를 그림.
    }

    void MakeGround() { //땅 배열 ground를 mapData에 반영함으로써 땅 그리기   
        //땅
        Drawfigure(1, 22, 130,1, ground); 
    }

    void DrawMap(int x, int y, char str[]) {
        for(int i=0; i<strlen(str); i++)
        EditMap(x+i, y, str[i]);   
    }

    void Drawfigure(int x, int y, int size_x, int size_y, char figure[]) {  //EditMap함수를 for문 처리해서 x,y좌표를 넣으면 해당 좌표를 기준으로 size_x,size_y크기의 맵을 수정                                          //캐릭터 크기가 size_x,size_y임. 
        for (int i = 0; i < size_y; i++) {  //size_y개 열을 수정 
            for (int j = 0; j < size_x; j++)   //size_x개 행을 수정 
               EditMap(x + j, y + i, figure[i * size_x + j]);      //i*size_x는 1행,2행,3행을 표현. j는 열을 표현. 
        }
    }
    
    void CreateMonster() {
        for(int i=0; i<10; i++)
            newMon[i] = new Monster;
    }      
      
    char* GetMapData(){return mapData;}      //private영역의 변수 리턴. 

    void printMap() {
         cout<<mapData;            //맵 출력 
    }
    
    void printName(int x, int y, char name[]) {
        Drawfigure(x-2,y-2,7,1,name);   //7는 이름 길이 
    }

    void DrawNumber(int x, int y, int num) {//x,y좌표와 숫자를 입력 받으면  해당 위치에 왼쪽 정렬 기준으로 숫자를 화면에 그림
       int tmp = num;
       short len = NumLen(tmp), cnt = len;
      char str[len];
       do {
           cnt--;
           str[cnt] = (char)(tmp % 10 + 48);
           tmp /= 10;
       } while(tmp != 0); 
       Drawfigure(x, y,len,1,str);
    }

    int NumLen(int num) {
        int tmp = num;
        short len = 0;
        while(tmp != 0) {
            tmp /= 10;
            len++;
        }
        return len;
    }
    
    void ShowStatus() {
        Drawfigure(2,1,35,1,"-------------------------------------");
        Drawfigure(2,9,35,1,"--------------------------------------");
        for(int i=0; i<9; i++) {
           EditMap(1,1+i,'|');
            EditMap(37,1+i,'|');
        }
        Drawfigure(4,2,14,1,"\"Mr.Song\"  LV.");
        DrawNumber(18,2,Song->GetLv());

        Drawfigure(27,2,6,1,"Weapon");
        Drawfigure(25,3,10,1,"------------");
        for(int i=0; i<4; i++) {
            EditMap(25,4+i,'I');
            EditMap(35,4+i,'l');
        }
        Drawfigure(25,8,10,1,"------------");

        Drawfigure(4,5,3,1,"HP:");
        DrawNumber(8,5,Song->GetHp());
        EditMap(12,5,'/');
        DrawNumber(14,5,Song->GetHpm());

        Drawfigure(4,7,6,1,"Power:");
        DrawNumber(11,7,Song->GetPower());

        DrawMap(27, 5, Song->figure_invenWeapon);
    }
    
    void DrawWeapon() {
        Drawfigure(Song->weaponX,Song->weaponY,4,1,Song->rightweaponFigure);
    }
    void DrawAttack() {
        if(Song->direction == TRUE && Song->attack == TRUE) {
           Song->weaponX++;
            DrawWeapon();
            Song->weaponX--;
            Song->rightweaponFigure[3] = ' ';
            Song->rightweaponFigure[4] = ' ';
            DrawWeapon();
        }
        if(Song->direction == FALSE && Song->attack == TRUE) {
            Song->weaponX--;
            DrawWeapon();
            Song->weaponX++;
            DrawWeapon();
        }
    }       
};

class GamePlay
{
    public :
    Monster * m;
    int i; 
    GamePlay() {           
        Map m1;
        clock_t start, end;
        start = clock();   //시작측정시작

        m1.CreateMonster();

        while(TRUE) {

        end = clock();   //시간측정끝
        float time = ((float)(end - start) / CLOCKS_PER_SEC);
      ConsoleSet::gotoxy(0,0);
        m1.fillArray(m1.GetMapData(), ' ', MAP_X_MAX * MAP_Y_MAX);   //맵을 공백으로 초기화 시켜줌  
        m1.Song->ControlCharacter();      //캐릭터 움직임        
        for(int i=0; i<10; i++)
            m1.Drawfigure(m1.newMon[i]->GetX()+(i*12),m1.newMon[i]->GetY(),4,4,m1.newMon[i]->GetMonster());
        if (time >= 0.1) {   
         for(int i=0; i<5; i++)
               m1.newMon[i]->Monster_Move();
         start = clock();
        }
       if(time>= 0.5) {
         for(int i=5; i<10; i++)             
               m1.newMon[i]->Monster_Move();
        } 
      m1.MakeGround();      //땅 다시 맵에 반영해주기. 왜냐하면 위에서 반복적으로 맵 전체를 공백으로 초기화 하므로! 
        m1.Drawfigure(m1.Song->GetX(),m1.Song->GetY(), 3, 3,m1.Song->Getfigure());      //맵에 Song캐릭터 그리기 
        m1.printName((m1.Song)->GetX(),(m1.Song)->GetY(),(m1.Song)->Getname());
        m1.ShowStatus();                                
        m1.DrawWeapon();
        m1.DrawAttack();   
        m1.printMap();
        Sleep(30);   //움직임이 너무 빨라서 딜레이 주기.
        }
    }
};

int main() {

   ConsoleSet();   //콘솔창 설정 생성자 호출 
   GamePlay();

   return 0;
}
