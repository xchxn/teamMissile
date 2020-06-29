#include <stdio.h>
#include <stdlib.h>
#include <memory.h>	//memset
#include <time.h>
#include <windows.h>
#define FALSE 0
#define TRUE 1
#define MAP_X_MAX 116
#define MAP_Y_MAX 36
#define FLOOR_Y 32
#define OBJECT_MAX 100
#define SPAWN_TIME 15000

typedef struct _Character {
    int position[2], size[2];	//position[0]이 x좌표, position[1]이 y좌표 ,  size[0]이 size_x, size[1]이 size_y 
    float accel[2], flyTime;	//accel[0]: 대쉬용 가속도  accel[1]: 점프용 가속도  and flotation time
    bool direction;				//true=오른쪽방향 , false=왼쪽방향 
    //status 
    char name[16];
    int lv, exp[2], score, hp[2], mp[2];	//[0]=최대값 , [1]=현재값 
    int power, weapon;
    //animation control
    bool attack;				//키보드 z가 눌리면 attack = TRUE, 아니면 FALSE 
    bool skill_attack1;			//키보드 x가 눌리면 레이저 스킬  
	bool skill_attack2;			//키보드 a가 눌리면 강아지 스킬  
	int tick[4];				//tick : 딜레이(시간측정) 변수  [0]: 피젠 tick [1]: 공격 tick, [2] : 대쉬 tick, [3] : 피격시 무적 tick
}Character;

typedef struct _Object {	//enemies, projectiles, particles, etc.
    int position[2], size[2];
    float accel[2], flyTime;
    bool direction;
	
    int kind;	//1~99: items, 100~199: enemies, 200~: projectiles, particles
    int hp[2], exp;	//hp: this value is used randomly for item or particle object
    int motion[3];	//motion
    int tick[4];	//0: hpshow time(enemy) or active time(projecticles, particles)
}Object;

Character character = {{MAP_X_MAX / 2, MAP_Y_MAX / 2}, {3, 3}, {0, 0}, 0, TRUE, "", 1, {100, 0}, 0, {100, 100}, {100, 100}, 10, 0, FALSE,FALSE,FALSE,{0, 1, 0, 0}};
Object **objects;

int tick = 0;							//tick 
int spon_tick = 0;						//몬스터 리젠용 tick 
int boss_tick = 0;						//보스 한번만 소환되게 할 tick 
char figure_floor[MAP_X_MAX];			//땅모양 배열 
char mapData[MAP_X_MAX * MAP_Y_MAX];	//콘솔창 크기의 배열 

//캐릭터 모양 배열 (3*3) 
const char figure_character[10] = " 0  | a^a";

//들고있는 무기 모양 
const char figure_weapon[2][3][4] = 
{{"---", "--+", "<=+"},
 {"---", "+--", "+=>"}};

//상태창 박스의 무기모양 
const char figure_invenWeapon[3][11] = {"   /   /  ", "   /  '*. ", "  |   \"+\" "};  

//몬스터 모양 
const char figure_enemy1[2][13] = {" __ (**)----", " __ [  ]\'--\'"};
//보스 거미 모양 
char figure_spider[] ="|                | |      ##      |  --    {  }    --    |  {    }  |      |-{  --  }-|        { ---- }     |  --{ ---- }--  | -/  {  --  }  \\-     / {    } \\       / { 0000 } \\     -   { 00 }   -   |  /{      }\\  | |  |  \\()()/  |  ||  |   ||||   |  || /    \\/\\/    \\ || |            | |  |            |    |            |  ";


void StartGame();	//초기 설정 
void SetConsole();	//콘솔창 세팅  
void Draw_Figure(int x, int y, int size_x, int size_y, const char spr[]);	//(x,y)를 기준으로 size_x*size_y크기로 spr[]을 그림 
void FillMap(char str[], char ch, int max);	//str배열을 문자 str_s로 max_value만큼 채움 
void EditMap(int x, int y, char ch);	//(x,y)를 문자str로 변경 

int main()
{
	
}

void StartGame() {
	SetConsole();			//콘솔창 가로 세로 크기 설정, 커서 안보이게 설정 
	srand((int)time(NULL));
	
	printf("이름을 입력하세요 : ");
	scanf("%s", character.name);
	
	FillMap(figure_floor, '=', MAP_X_MAX);	//땅배열에 '=' 채우기 
	
	objects = (Object **)malloc(sizeof(Object *) * OBJECT_MAX);		//OBJECT_MAX개의 object포인터 공간 할당  
	memset(objects, 0, sizeof(Object *) * OBJECT_MAX); 				//objects가 가리키는 놈을 sizeof(object*)*OBJECT_MAX 크기만큼 0으로 초기화 
}

void SetConsole() {
	system("mode con:cols=116 lines=36");
	system("title 교수의 모험");
	
	HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

void Draw_Figure(int x, int y, int size_x, int size_y, const char spr[]) {	//(x,y)를 기준으로 size_x*size_y크기로 spr[]을 그림 
	for (int i = 0; i < size_y; i++) {
		for (int n = 0; n < size_x; n++)
			EditMap(x + n, y + i, spr[i * size_x + n]);
	}
}
