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
void Draw_Box(int x, int y, int size_x, int size_y);	//상태창에 상자 그리는 함수 (x,y)에 size_x*size_y크기의 상자 그림
void Draw_Number(int x, int y, int num);	//(x,y)에  char형으로 변환된 숫자를 그림
int NumLen(int num);	//num의 자릿수를 리턴하는 함수 (Draw_Number할때 필요)
void Control_UI();  //기능 : 땅그리기, 왼쪽상단 상태창 그리기 및 갱신
void Control_Character();	//기능 : 캐릭터의 움직임,스킬,피격 등 구현  
bool CheckCollision(int position1[], int position2[], int size1[], int size2[]);	//충돌 체크 함수 : position1[]의 size1[]크기가 position2[]의 size2[]크기와 충돌이 나면 TRUE  
void MovementControl(int position[], float accel[], int size[], float *flyTime);	//가속도 함수 
void Control_Item(int index);
void Control_Enemy(int index);
void Control_Particle(int index);
int main()
{
	printf("f"); 
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

void FillMap(char str[], char ch, int max) {	//str배열을 문자 ch로 max만큼 채움 
	for (int i = 0; i < max; i++)
		str[i] = ch;
}

void EditMap(int x, int y, char ch) {	//(x,y)를 문자ch로 변경 
	if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)
		mapData[(y - 1) * MAP_X_MAX + x - 1] = ch;
}

void Draw_Box(int x, int y, int size_x, int size_y) {		//상태창에 상자 그리는 함수 (x,y)에 size_x*size_y크기의 상자 그림 
	EditMap(x, y, '.'); EditMap(x + size_x - 1, y, '.');
	EditMap(x, y + size_y - 1, '\''); EditMap(x + size_x - 1, y + size_y - 1, '\'');
	
	for (int i = 1; i < size_x - 1; i++) {
		EditMap(x + i, y, '-'); EditMap(x + i, y + size_y - 1, '-');
	}
	for (int i = 1; i < size_y - 1; i++) {
		EditMap(x, y + i, '|'); EditMap(x + size_x - 1, y + i, '|');
	}
}

void Draw_Number(int x, int y, int num) {		//(x,y)에  char형으로 변환된 숫자를 그림 
	int tmp = num, len = NumLen(tmp), index = len;
    char str[len];		//숫자 자릿수+1 크기의 문자 배열 (1자리는 널문자) 
    
    do {
        index--;
        str[index] = (char)(tmp % 10 + 48);
        tmp /= 10;
    } while(tmp != 0);
    
    Draw_Figure(x, y, len, 1, str);
}

int NumLen(int num) {		//num의 자릿수를 리턴하는 함수 (Draw_Number할때 필요) 
	int tmp = num, len = 0;
	
	if (num == 0) {
		return 1;
	} else {
		while(tmp != 0) {
        	tmp /= 10;
        	len++;
    	}
	}
	
    return len;
} 

void Control_UI() 	//기능 : 땅그리기, 왼쪽상단 상태창 그리기 및 갱신 
{
	int expPer = (character.exp[1] * 100 / character.exp[0]);		//exp[1]은 현재 exp, exp[0]은 최대exp(레벨업) 
	int len;	//length of previous sprite
	
	Draw_Figure(1, FLOOR_Y, MAP_X_MAX, 1, figure_floor);	//draw floor
	
	Draw_Box(1, 2, 35, 8); Draw_Box(27, 5, 7, 4);	//draw weaponinven
	Draw_Figure(28, 6, 5, 2, figure_invenWeapon[character.weapon]);		//character.weapon이 0,1,2로 각자 무기 모양 배열 나타냄 
	Draw_Figure(28, 4, 6, 1, "Weapon");
	
	EditMap(3, 3, '\"');	//draw name, lv, exp
	Draw_Figure(4, 3, strlen(character.name), 1, character.name);	len = 4 + strlen(character.name);//len이 x좌표를 나타냄. 각 문자열 길이만큼 len++시키면서 문자열을 알맞은 위치에 출력 
	Draw_Figure(len, 3, 7, 1, "\" LV.");	len += 5;
	Draw_Number(len, 3, character.lv);	len += NumLen(character.lv);
	Draw_Figure(len, 3, 2, 1, " (");	len += 2;
	
	if (!expPer) {	//경험치 0%면 
		EditMap(len, 3, '0');	len ++;		 
	} else {
		Draw_Number(len, 3, expPer);	len += NumLen(expPer);
	}
	Draw_Figure(len, 3, 2, 1, "%)");
	
	Draw_Figure(MAP_X_MAX - NumLen(character.score) - 7, 3, 6, 1, "SCORE:");	//draw score
	Draw_Number(MAP_X_MAX - NumLen(character.score), 3, character.score);
	
	Draw_Figure(4, 5, 3, 1, "HP:");	//draw HP
	Draw_Number(8, 5, character.hp[1]);
	EditMap(9 + NumLen(character.hp[1]), 5, '/');
	Draw_Number(11 + NumLen(character.hp[1]), 5, character.hp[0]);
	
	Draw_Figure(4, 6, 3, 1, "MP:");	//draw MP
	Draw_Number(8, 6, character.mp[1]);
	EditMap(9 + NumLen(character.mp[1]), 6, '/');
	Draw_Number(11 + NumLen(character.mp[1]), 6, character.mp[0]);
	
	Draw_Figure(4, 8, 6, 1, "Power:");	//draw power
	Draw_Number(11, 8, character.power);
}

void Control_Character()
{	
	character.attack = FALSE;	//공격변수를 초기화 (안할 시 공격모션에서 안돌아옴)
	character.skill_attack1 = FALSE;
	character.skill_attack2 = FALSE;
	 
	//LV up				exp[1]이 현재 exp, exp[0]이 Max exp 
	if (character.exp[1] >= character.exp[0]) {
		character.lv += character.exp[1] / character.exp[0];	//보스 잡을시 lv업 많이 되도록 변경 
		character.hp[0] = 100 + character.lv * 5 ; character.mp[0] = 100 + character.lv * 3; 
		character.exp[1] = 0; character.exp[0] += character.lv * 10;
		character.power = 10+(character.lv * 2);
	}
	//hp,mp gen & control			0.9초마다 피회복  
	if (character.tick[0] + 900 < tick) { 
		character.tick[0] = tick;
		character.hp[1] += 1;		//
		character.mp[1] += 3;
	}
	if (character.hp[1] > character.hp[0])		//최대 hp,mp를 초과하려하면 최대값으로 고정  
		character.hp[1] = character.hp[0];
	if (character.mp[1] > character.mp[0])
		character.mp[1] = character.mp[0];

	//게임 오버 구현 	
	if (character.hp[1] < 1)
		tick = 0;			//tick = 0이되면 main함수에서 while문을 탈출해서 게임 끝나게 되어있음 
 
 	//깜빡임 
	if (character.tick[3] > 0)		//몬스터와 충돌이 나면 character.tick[3] = 100이 됌. 
	{
		textcolor(15,4); //피격시 빨강색
		character.tick[3] -= 1;
	}
	else 
	{
		textcolor(0,15); 
	}
	
	//공격 구현부 
	if (GetAsyncKeyState(0x5A) && character.tick[1] + 150 <= tick ) {	// 0x5A는 Z의 아스키코드값    공격딜레이 250ms 
		character.tick[1] = tick;
		character.attack = TRUE;
	}

	//스킬공격1 구현부 
	if (GetAsyncKeyState(0x58) && character.mp[1] > 1 && character.tick[1]+ 30<= tick) {	// 0x5A는 x의 아스키코드값    
		character.tick[1] = tick;
		character.skill_attack1 = TRUE;
		character.mp[1] -= 1;
	}
	//스킬공격2 구현부	 
	if (GetAsyncKeyState(0x41) && character.mp[1] > 2 && character.tick[1]+ 30<= tick) {	// 0x5A는 x의 아스키코드값     
		character.tick[1] = tick;
		character.skill_attack2 = TRUE;
		character.mp[1] -= 2;
	}

	//움직임구현부 
	if (GetAsyncKeyState(VK_LEFT) && character.position[0] > 1) {	//왼쪽 화살표 눌리고 x>1이면 왼쪽이동 
			character.position[0]--;
			character.direction = FALSE;	//좌측방향 
		}
		
	if (GetAsyncKeyState(VK_RIGHT) && character.position[0] < MAP_X_MAX - 2) {	//오른쪽 화살표 눌리고 x가 맵우측끝보다-2지점보다 작으면 
			character.position[0]++;
			character.direction = TRUE;		//우측방향 
		}
		
	if (GetAsyncKeyState(0x43) && character.tick[2] + 1200 <= tick) {	//dash		0x58은 X의 아스키코드값 	1.2초에 한번 사용 가능 
			character.accel[0] = character.direction * 6 - 3;	//character.accel[0]은 왼쪽방향 대쉬면  -9, 오른쪽 방향 대쉬면  +3  
			character.tick[2] = tick;
		}
		
	if (GetAsyncKeyState(VK_UP) && character.position[1] + 3 == FLOOR_Y)	//jump
			character.accel[1] = -1.75;
	
	MovementControl(character.position, character.accel, character.size, &character.flyTime);	// control character movement  중력구현 
	
	//캐릭터 그리는 부분 
	if (character.tick[3] % 2 == 0) {		//무적tick이 짝수면 (무적tick이 100에서 1씩 계속 줄어듬. 따라서 캐릭터가 깜빡이게 됌)
		Draw_Figure(character.position[0], character.position[1], character.size[0], character.size[1], figure_character);	//캐릭터 그림 
		
		
		if (character.direction) {//오른쪽방향이면 몸통 오른쪽으로 
			EditMap(character.position[0], character.position[1] + 1, '(');
		} else {				  //왼쪽방향이면  몸통 왼쪽으로 
			EditMap(character.position[0] + 2, character.position[1] + 1, ')');
		}
		
		if (character.accel[0] > 1)  //x키가 눌리고(dash) 오른쪽 방향을 보고있는 경우- 캐릭터 왼쪽에 샤샤샥효과   
			Draw_Figure(character.position[0] - 2, character.position[1], 1, 3, "===");
		if (character.accel[0] < -1) //x키가 눌리고(dash) 왼쪽 방향을 보고있는 경우 - 캐릭터 오른쪽에 샤샤샥효과 
			Draw_Figure(character.position[0] + 4, character.position[1], 1, 3, "===");
		
		//공격모션 그리기 부분  
		if (character.attack==TRUE ) {
					EditMap(character.position[0] - 2 + 6 * character.direction, character.position[1] + 1, 'o');
					Draw_Figure(character.position[0] - 5 + 10 * character.direction, character.position[1] + 1, 3, 1, figure_weapon[character.direction][character.weapon]);
				} 
		else {
					EditMap(character.position[0] + 2 * character.direction, character.position[1] + 1, 'o');
					Draw_Figure(character.position[0] - 3 + 6 * character.direction, character.position[1] + 1, 3, 1, figure_weapon[character.direction][character.weapon]);
				}
		
		//스킬모션1 그리기 부분 
		if (character.skill_attack1 == TRUE && character.direction == TRUE)		//스킬 시전,  오른쪽 방향 
		{	
			int i;
			for(i=0; i<MAP_X_MAX - character.position[0]-4; i++);
			
			Draw_Figure(character.position[0] +4 ,character.position[1]+0 ,i+3, 1, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
			Draw_Figure(character.position[0] +4 ,character.position[1]+1 ,i+3, 1, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
			Draw_Figure(character.position[0] +4 ,character.position[1]+2 ,i+3, 1, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
			}
		}
		if (character.skill_attack1 == TRUE && character.direction == FALSE)		//스킬 시전,  ,왼쪽 방향 
		{	
			int i;
			for(i=0; i<MAP_X_MAX - character.position[0]-4; i++);
			Draw_Figure(0,character.position[1]+0 ,character.position[0]-1, 1, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
			Draw_Figure(0,character.position[1]+1 ,character.position[0]-1, 1, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
			Draw_Figure(0,character.position[1]+2 ,character.position[0]-1, 1, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		}
		//스킬모션2 그리기 부분 
		if (character.skill_attack2 == TRUE)
		{
			Draw_Figure(107,27,10,5,"|\\_/|\"    |q p|   /}( 0 )\"\"\"\\ |\"^\"`    |||_/=\\\\__|");		//강아지 모양
			Draw_Figure(0,28,106,2,"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		} 
			
}


void MovementControl(int position[], float accel[], int size[], float *flyTime) {
	float y_value = accel[1];
	
	if (position[1] + size[1] == FLOOR_Y) {
		*flyTime = 0;		//땅에 닿아있으면 flyTime = 0 
	} else {				//떨어져 있으면 flyTime += 0.05 
		*flyTime += 0.05;
		accel[1] += *flyTime; 
	}
	
	if (y_value != 0) {
		if (position[1] + size[1] + y_value > FLOOR_Y)		//땅으로 꺼져서 추락하는거 방지  
			y_value = FLOOR_Y - position[1] - size[1];
	}

	position[0] += accel[0] + 0.5; position[1] += y_value + 0.5;	  
	
	//accel이 0이되면 아래 문장들은 실행이 안됌. 
	if (accel[0] > 0) accel[0] -= 0.2; if (accel[0] < 0) accel[0] += 0.2;
	if (accel[1] > 0) accel[1] -= 0.1; if (accel[1] < 0) accel[1] += 0.1;
}

bool CheckCollision(int position1[], int position2[], int size1[], int size2[]) {	//충동 체크 함수 
	if (position1[0] > position2[0] - size1[0] && position1[0] < position2[0] + size2[0]	//position2[0]-size1[0] = 몬스터 시작지점-캐릭터 가로크기 , position2[0]+size2[0] = 몬스터의 우측 끝
	    && position1[1] > position2[1] - size1[1] && position1[1] < position2[1] + size2[1])	//y값 충돌 
		{
			return TRUE;
		}
	else
	{
		return FALSE;
	}
}
