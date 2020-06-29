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

