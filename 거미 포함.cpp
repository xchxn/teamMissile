#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define FALSE 0
#define TRUE 1
#define MAP_X_MAX 116
#define MAP_Y_MAX 36
#define FLOOR_Y 32
#define OBJECT_MAX 32
#define SPAWN_TIME 15000

typedef struct _Character {
    int position[2], size[2];   //position[0]이 x좌표, position[1]이 y좌표 ,  size[0]이 size_x, size[1]이 size_y 
    float accel[2], flyTime;   //accel[0]: 대쉬용 가속도  accel[1]: 점프용 가속도  and flotation time
    bool direction;            //true=오른쪽방향 , false=왼쪽방향 
    //status 
    char name[16];
    int lv, exp[2], score, hp[2], mp[2];   //[0]=최대값 , [1]=현재값 
    int power, weapon;
    //animation control
    bool attack;            //키보드 z가 눌리면 attack = TRUE, 아니면 FALSE 
    int tick[4];            //tick : 딜레이(시간측정) 변수  [0]: 피젠 tick [1]: 공격 tick, [2] : 대쉬 tick, [3] : 피격시 무적 tick
}Character;

typedef struct _Object {   //enemies, projectiles, particles, etc.
    int position[2], size[2];
    float accel[2], flyTime;
    bool direction;

    int kind;   //1~99: items, 100~199: enemies, 200~: projectiles, particles
    int hp[2], exp;   //hp: this value is used randomly for item or particle object
    int dam;
    
    int motion[3];   //motion
    int tick[4];   //0: hpshow time(enemy) or active time(projecticles, particles)
}Object;

Character character = {{MAP_X_MAX / 2, MAP_Y_MAX / 2}, {3, 3}, {0, 0}, 0, TRUE, "", 1, {100, 0}, 0, {100, 100}, {50, 50}, 10, 0, FALSE,{0, 1, 0, 0}};
Object **objects;

int tick = 0;                     //tick 
int spon_tick = 0;                  //몬스터 리젠용 tick 
char sprite_floor[MAP_X_MAX];         //땅모양 배열 
char mapData[MAP_X_MAX * MAP_Y_MAX];   //콘솔창 크기의 배열 

//적 능력치 hp, exp, size(x y), tick (2 3 4)
const int stat_enemy[2][7] =
 {{150, 30, 4, 3, 0, 1000, 0},   //몬스터 kind를 100으로하고 stat_enemy[kind-100][]하면 이 능력치 
  {300, 50, 5, 5, 0, 500, 0}};   //몬스터 kind를 101로 하고  stat_enemy[kind-100][]하면 이 능력치

const int stat_weapon[3] = {5, 10, 15};
//캐릭터 모양 배열 (3*3) 
const char sprite_character[10] = " 0  | a^a";
const char sprite_normalAttack[2][3][16] = 
{{" .- o          ", " .   (   o \'   ", "         o \'-  "},      //왼쪽 방향 
 {"o -.           ", "   . o   )   \' ", "     o      -\' "}};      //오른쪽 방향 

//들고있는 무기 모양 
const char sprite_weapon[2][3][4] = 
{{"---", "--+", "<=+"},
 {"---", "+--", "+=>"}};

//상태창 박스의 무기모양 
const char sprite_invenWeapon[3][11] = {"   /   /  ", "   /  '*. ", "  |   \"+\" "};  

//몬스터 모양 
const char sprite_enemy1[2][13] = {" __ (**)----", " __ [  ]\'--\'"};

void StartGame();   //초기 설정 
void UpdateGame();   //게임판인 mapData 업데이트 후 출력 
void ExitGame();   //objects 동적메모리 헤제  
void SetConsole();   //콘솔창 세팅  
void ControlUI();  //기능 : 땅그리기, 왼쪽상단 상태창 그리기 및 갱신
void ControlCharacter();
void ControlObject();   //모든 오브젝트 컨트롤 함수
void ControlItem(int index);
void ControlEnemy(int index);
void ControlParticle(int index);
void CreateObject(int x, int y, int kind);      //x,y좌표에 kind값에 따라 오브젝트 생성 (1~99: 아이템, 100~199: 몬스터, 200~299: 동전)
void RemoveObject(int index);      //object[index] 메모리 해제 후 NULL로 초기화 : 다른 오브젝트를 위한 크기 만들기 위함 
bool EnemyPosition(int x, int size_x);   //캐릭터의 위치와 몬스터의 위치를 비교.  캐릭터가 왼쪽에 있으면 FALSE, 오른쪽에 있으면 TRUE  
bool CollisionCheck(int position1[], int position2[], int size1[], int size2[]);   //충돌 체크 함수 : position1[]의 size1[]크기가 position2[]의 size2[]크기와 충돌이 나면 TRUE  
void MoveControl(int position[], float accel[], int size[], float *flyTime);   // motion control
void DrawBox(int x, int y, int size_x, int size_y);   //상태창에 상자 그리는 함수 (x,y)에 size_x*size_y크기의 상자 그림
void DrawNumber(int x, int y, int num);   //(x,y)에  char형으로 변환된 숫자를 그림
void DrawSprite(int x, int y, int size_x, int size_y, const char spr[]);   //(x,y)를 기준으로 size_x*size_y크기로 spr[]을 그림    //세로 // 가로 
void FillMap(char str[], char str_s, int max_value);   //str배열을 문자 str_s로 max_value만큼 채움 
void EditMap(int x, int y, char str);   //(x,y)를 문자str로 변경 
int NumLen(int num);   //num의 자릿수를 리턴하는 함수 (DrawNumber할때 필요)

char sprite_spider[] ={"|                | |      ##      |  --    {  }    --    |  {    }  |      |-{  --  }-|        { ---- }     |  --{ ---- }--  | -/  {  --  }  \\-     / {    } \\       / { 0000 } \\     -   { 00 }   -   |  /{      }\\  | |  |  \\()()/  |  |"};

int main() {
   StartGame();
   
   while (TRUE) {
      if (tick +30 < GetTickCount()) {   //30ms에 한번씩 updategame되도록 설정   
         tick = GetTickCount();         //컴퓨터 부팅 후 경과한 시간을 ms로 반환. 따라서 tick은 1초에 1000씩 증가함 
         
         UpdateGame();
         
         if (tick == 0)               //character의 hp[1]이 1미만이 되면 tick = 0 
            break;
      }
   }
   
   ExitGame();
   return 0;
}

void StartGame() {
   SetConsole();         //콘솔창 가로 세로 크기 설정, 커서 안보이게 설정 
   srand((int)time(NULL));
   
   printf("이름을 입력하세요 : ");
   scanf("%s", character.name);
   
   FillMap(sprite_floor, '=', MAP_X_MAX);   //땅배열에 '=' 채우기 
   
   objects = (Object **)malloc(sizeof(Object *) * OBJECT_MAX);      //OBJECT_MAX개의 object포인터 공간 할당  
   memset(objects, 0, sizeof(Object *) * OBJECT_MAX);             //objects가 가리키는 놈을 sizeof(object*)*OBJECT_MAX 크기만큼 0으로 초기화 
}

void UpdateGame() {
   FillMap(mapData, ' ', MAP_X_MAX * MAP_Y_MAX);   //맵을 공백으로 초기화 
   
   ControlCharacter();   //mapData에 캐릭터 정보 업데이트 
   ControlObject();   //mapData에 적,동전,아이템 등 업데이트
   ControlUI();      //땅배열 및 상태창 업데이트  
   
   if (spon_tick + SPAWN_TIME < tick) {      //15초마다 몬스터 스폰 
      spon_tick = tick;
      CreateObject(rand() % 90, 5, 100);      //(x: 0~90 , y:5) kind = 100 : 몬스터    
      CreateObject(rand() % 90, 5, 100);
      CreateObject(rand() % 90, 5, 100);
   }
   
   DrawSprite(60, 2, 18,  13, sprite_spider);
   
   printf("%s",mapData);   //draw mapData
}

void ExitGame() {   //objects 동적메모리 헤제  
    for (int i = 0; i < OBJECT_MAX; i++) {
        if (objects[i])
            free(objects[i]);
    }
    
    free(objects);
}

void SetConsole() {
   system("mode con:cols=116 lines=36");
   system("title RPG test");
   
   HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

void ControlUI()    //기능 : 땅그리기, 왼쪽상단 상태창 그리기 및 갱신 
{
   int expPer = roundf(character.exp[1] * 100 / character.exp[0]);      //roundf는 반올림함수    exp[1]은 현재 exp, exp[0]은 최대exp(레벨업) 
   int len;   //length of previous sprite
   
   DrawSprite(1, FLOOR_Y, MAP_X_MAX, 1, sprite_floor);   //draw floor
   
   DrawBox(1, 2, 35, 8); DrawBox(27, 5, 7, 4);   //draw weaponinven
   DrawSprite(28, 6, 5, 2, sprite_invenWeapon[character.weapon]);      //character.weapon이 0,1,2로 각자 무기 모양 배열 나타냄 
   DrawSprite(28, 4, 6, 1, "Weapon");
   
   EditMap(3, 3, '\"');   //draw name, lv, exp
   DrawSprite(4, 3, strlen(character.name), 1, character.name);   len = 4 + strlen(character.name);//len이 x좌표를 나타냄. 각 문자열 길이만큼 len++시키면서 문자열을 알맞은 위치에 출력 
   DrawSprite(len, 3, 7, 1, "\" LV.");   len += 5;
   DrawNumber(len, 3, character.lv);   len += NumLen(character.lv);
   DrawSprite(len, 3, 2, 1, " (");   len += 2;
   
   if (!expPer) {   //경험치 0%면 
      EditMap(len, 3, '0');   len ++;       
   } else {
      DrawNumber(len, 3, expPer);   len += NumLen(expPer);
   }
   DrawSprite(len, 3, 2, 1, "%)");
   
   DrawSprite(MAP_X_MAX - NumLen(character.score) - 7, 3, 6, 1, "SCORE:");   //draw score
   DrawNumber(MAP_X_MAX - NumLen(character.score), 3, character.score);
   
   DrawSprite(4, 5, 3, 1, "HP:");   //draw HP
   DrawNumber(8, 5, character.hp[1]);
   EditMap(9 + NumLen(character.hp[1]), 5, '/');
   DrawNumber(11 + NumLen(character.hp[1]), 5, character.hp[0]);
   
   DrawSprite(4, 6, 3, 1, "MP:");   //draw MP
   DrawNumber(8, 6, character.mp[1]);
   EditMap(9 + NumLen(character.mp[1]), 6, '/');
   DrawNumber(11 + NumLen(character.mp[1]), 6, character.mp[0]);
   
   DrawSprite(4, 8, 6, 1, "Power:");   //draw power
   DrawNumber(11, 8, character.power);
}

void ControlCharacter()
{   
   character.attack = FALSE;   //공격변수를 초기화 (안할 시 공격모션에서 안돌아옴)
    
   //LV up            exp[1]이 현재 exp, exp[0]이 Max exp 
   if (character.exp[1] >= character.exp[0]) {
      character.hp[0] += 10; character.mp[0] += 5; character.power ++;
      character.lv ++; character.exp[1] = 0; character.exp[0] += character.lv * 10;
   }
   //hp,mp gen & control         0.9초마다 피회복  
   if (character.tick[0] + 900 < tick) { 
      character.tick[0] = tick;
      character.hp[1] += 1;      //
      character.mp[1] += 1;
   }
   if (character.hp[1] > character.hp[0])      //최대 hp,mp를 초과하려하면 최대값으로 고정  
      character.hp[1] = character.hp[0];
   if (character.mp[1] > character.mp[0])
      character.mp[1] = character.mp[0];

   //게임 오버 구현    
   if (character.hp[1] < 1)
      tick = 0;         //tick = 0이되면 main함수에서 while문을 탈출해서 게임 끝나게 되어있음 
 
    //깜빡임 
   if (character.tick[3] > 0)      //몬스터와 충돌이 나면 character.tick[3] = 100이 됌. 
      character.tick[3] -= 1;
   
   //공격 구현부 
   if (GetAsyncKeyState(0x5A) && character.tick[1] + 150 <= tick ) {   // 0x5A는 Z의 아스키코드값    공격딜레이 250ms 
      character.tick[1] = tick;
      character.attack = TRUE;
   }

   //움직임구현부 
   if (GetAsyncKeyState(VK_LEFT) && character.position[0] > 1) {   //왼쪽 화살표 눌리고 x>1이면 왼쪽이동 
         character.position[0]--;
         character.direction = FALSE;   //좌측방향 
      }
      
   if (GetAsyncKeyState(VK_RIGHT) && character.position[0] < MAP_X_MAX - 2) {   //오른쪽 화살표 눌리고 x가 맵우측끝보다-2지점보다 작으면 
         character.position[0]++;
         character.direction = TRUE;      //우측방향 
      }
      
   if (GetAsyncKeyState(0x58) && character.tick[2] + 1200 <= tick) {   //dash      0x58은 X의 아스키코드값    1.2초에 한번 사용 가능 
         character.accel[0] = character.direction * 6 - 3;   //character.accel[0]은 왼쪽방향 대쉬면  -9, 오른쪽 방향 대쉬면  +3  
         character.tick[2] = tick;
      }
      
   if (GetAsyncKeyState(VK_UP) && character.position[1] + 3 == FLOOR_Y)   //jump
         character.accel[1] = -1.75;
   
   MoveControl(character.position, character.accel, character.size, &character.flyTime);   // control character movement  중력구현 
   
   //캐릭터 그리는 부분 
   if (character.tick[3] % 2 == 0) {      //무적tick이 짝수면 (무적tick이 100에서 1씩 계속 줄어듬. 따라서 캐릭터가 깜빡이게 됌)
      DrawSprite(character.position[0], character.position[1], character.size[0], character.size[1], sprite_character);   //캐릭터 그림 
      
      
      if (character.direction) {//오른쪽방향이면 몸통 오른쪽으로 
         EditMap(character.position[0], character.position[1] + 1, '(');
      } else {              //왼쪽방향이면  몸통 왼쪽으로 
         EditMap(character.position[0] + 2, character.position[1] + 1, ')');
      }
      
      if (character.accel[0] > 1)  //x키가 눌리고(dash) 오른쪽 방향을 보고있는 경우- 캐릭터 왼쪽에 샤샤샥효과   
         DrawSprite(character.position[0] - 2, character.position[1], 1, 3, "===");
      if (character.accel[0] < -1) //x키가 눌리고(dash) 왼쪽 방향을 보고있는 경우 - 캐릭터 오른쪽에 샤샤샥효과 
         DrawSprite(character.position[0] + 4, character.position[1], 1, 3, "===");
      
      //공격모션 그리기 부분  
      if (character.attack==TRUE ) {
               EditMap(character.position[0] - 2 + 6 * character.direction, character.position[1] + 1, 'o');
               DrawSprite(character.position[0] - 5 + 10 * character.direction, character.position[1] + 1, 3, 1, sprite_weapon[character.direction][character.weapon]);
            } 
      else {
               EditMap(character.position[0] + 2 * character.direction, character.position[1] + 1, 'o');
               DrawSprite(character.position[0] - 3 + 6 * character.direction, character.position[1] + 1, 3, 1, sprite_weapon[character.direction][character.weapon]);
            }
   }      
}

void ControlItem(int index) {
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int item_position[2] = {x, y - 2};
   int item_size[2] = {5, 2};
   
   if (objects[index]->tick[1] < tick) {
      objects[index]->tick[1] = tick * 2;
      objects[index]->accel[0] =  1 - 2 * objects[index]->hp[0] / (float)RAND_MAX;
      objects[index]->accel[1] =  - 2 * objects[index]->hp[1] / (float)RAND_MAX;
   }
   
   if (CollisionCheck(item_position, character.position, item_size, character.size)) {      //아이템과 캐릭터가 충돌이 나면 
      DrawSprite(x + 1, y - 5, 3, 1, "[E]");      //머리 위에 [E] 표시  
      
      if (GetAsyncKeyState(0x45)) {      //E키가 눌리면 
         character.weapon = objects[index]->kind;
      
         RemoveObject(index);
         return;
      }   
   }
   
   DrawSprite(x, y - 2, 5, 2, sprite_invenWeapon[objects[index]->kind]);

   
   MoveControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
}

void ControlEnemy(int index) {
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int attack_position[2] = {character.position[0] - 5 + 8 * character.direction, character.position[1]}, at_size[2] = {5, 3};      //캐릭터 공격 범위 5*3크기 
   int item_code = rand() % 100;
   
   if (objects[index]->hp[1] < 1) {   //몬스터가 죽으면 
      for (int i = 0; i < 3; i++)      //동전 3개 떨어짐 
         CreateObject(x + objects[index]->size[0] / 2, y + objects[index]->size[1] / 2, objects[index]->kind + 100);   //몬스터였다면 kind가 100~199이므로 +100하면 200이 넘어서 동전 
      
      //item_code가 90이상이거나 3이하이면 아이템 떨구게함   
      if (item_code >= 90)
         CreateObject(x + objects[index]->size[0] / 2 - 2, y, 1);   //1번무기 
         
      if (item_code <= 3)
         CreateObject(x + objects[index]->size[0] / 2 - 2, y, 2);   //2번무기  
         
      character.exp[1] += objects[index]->exp;
      
      RemoveObject(index);
      return;
   }
   
   if (objects[index]->tick[0] + 2000 > tick) //몬스터가 공격받은 후 2초동안  
      DrawNumber(x + objects[index]->size[0] / 2 - NumLen(objects[index]->hp[1]) / 2, y - 1, objects[index]->hp[1]);   //몬스터 머리위에 hp뜨게함 
   
   if (character.attack == TRUE && CollisionCheck(objects[index]->position, attack_position, objects[index]->size, at_size)) {      //캐릭터가 공격중 && 몬스터위치와 캐릭터 공격범위가 충돌나면 
      objects[index]->tick[0] = tick;
      objects[index]->hp[1] -= character.power;
      objects[index]->accel[1] = - 0.55;
      
      if (EnemyPosition(x,  objects[index]->size[0]))      //몬스터 왼쪽에 캐릭터가 위치시 
         objects[index]->accel[0] = -0.75;
      else                                    //몬스터 오른쪽에 캐릭터가 위치시 
         objects[index]->accel[0] = 0.75;
   }
   //kide100 슬라임에 대해서 
   if (objects[index]->kind == 100) {
      if (y + objects[index]->size[1] == FLOOR_Y)
         objects[index]->motion[0] = 0;
      else 
         objects[index]->motion[0] = 1;

      if (objects[index]->tick[1] + objects[index]->tick[2] < tick) {
         objects[index]->tick[1] = tick;
         objects[index]->tick[2] = 1000 + rand() % 1000;
         objects[index]->accel[1] = rand() / (float)RAND_MAX / 2 - 1.2;
         
         if (EnemyPosition(x,  objects[index]->size[0]))
            objects[index]->accel[0] = 2.4 - rand() / (float)RAND_MAX;
         else
            objects[index]->accel[0] = rand() / (float)RAND_MAX - 2.4;
      }
      
      if (character.tick[3] == 0 && CollisionCheck(objects[index]->position,character.position, objects[index]->size, character.size)) { //캐릭터의 피격시 무적 tick ==0 이고 몬스터와 충돌이 나면 
         character.tick[3] = 100;   //캐릭터의 피격시 무적 tick = 100    (100에서 1씩 줄어듬. 0까지 다시 줄어들어야 다시 피격판정 가능)
         character.hp[1] -= 10;
      }
      
      DrawSprite(x, y, objects[index]->size[0], objects[index]->size[1], sprite_enemy1[objects[index]->motion[0]]);
   }
   
   MoveControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
}

void ControlParticle(int index) {      //동전떨어지는 함수 
   int x = objects[index]->position[0], y = objects[index]->position[1];
   int money_size[2] = {2, 2};
   int money_position[2] = {x, y - 1};
   
   if (objects[index]->kind == 200) {
      if (objects[index]->tick[1] < tick) {
         objects[index]->tick[1] = tick * 2;
         objects[index]->accel[0] =  2 - 4 * objects[index]->hp[0] / (float)RAND_MAX;
         objects[index]->accel[1] =  - 2 * objects[index]->hp[1] / (float)RAND_MAX;
      }
      
      if (CollisionCheck(money_position, character.position, money_size, character.size)) {
         character.score += 100;
         
         RemoveObject(index);
         return;
      }
      
      EditMap(x, y - 1, '@');
   }
   
   MoveControl(objects[index]->position, objects[index]->accel, objects[index]->size, &objects[index]->flyTime);
}

void ControlObject() {   //모든 오브젝트 컨트롤 함수 
   for(int i = 0; i < OBJECT_MAX; i++) {
      if (objects[i]) {
         if (objects[i]->kind < 100)
            ControlItem(i);
         else if (objects[i]->kind > 99 && objects[i]->kind < 200)
            ControlEnemy(i);
         else
            ControlParticle(i);
      }
   }
}

void CreateObject(int x, int y, int kind) {      //x,y좌표에 kind값에 따라 오브젝트 생성 (1~99: 아이템, 100~199: 몬스터, 200~299: 동전)
   int index = 0;
   Object *obj = 0;
   
   while(TRUE) {
      if (! objects[index])
         break;
         
      if (index == OBJECT_MAX)
         return;

       index ++;
   }
   
   obj = (Object *)malloc(sizeof(Object));    //obj가 새로운 object를 가리킴  
    objects[index] = obj;                    //이중포인터 배열 objects가 obj가 가리키는 주소를 가리킴  
    memset(obj, 0, sizeof(Object));          //object를 0으로 초기화 
    
    obj->kind = kind;                     //object종류에 kind 넣음 
    obj->position[0] = x; obj->position[1] = y;
    obj->tick[0] = 0;
    
    if (kind < 100 || kind > 199) {      //100미만 200이상  -->  몬스터아님  
       obj->hp[0] = rand();
      obj->hp[1] = rand();
      obj->tick[1] = 0;
       obj->tick[2] = 0;
       obj->tick[3] = 0;
   }
   
    if (kind >= 100 && kind < 200) {      //kind가 100~199  -->  몬스터  
       obj->hp[0] = stat_enemy[kind - 100][0];      //몬스터를 일단 kind100을 슬라임으로 해놨음 
      obj->hp[1] = obj->hp[0];
       obj->exp = stat_enemy[kind - 100][1];
       obj->size[0] = stat_enemy[kind - 100][2];
      obj->size[1] = stat_enemy[kind - 100][3];
       obj->tick[1] = stat_enemy[kind - 100][4];
       obj->tick[2] = stat_enemy[kind - 100][5];
       obj->tick[3] = stat_enemy[kind - 100][6];
   }
}

void RemoveObject(int index) {      //object[index] 메모리 해제 후 NULL로 초기화 : 다른 오브젝트를 위한 크기 만들기 위함 
   free(objects[index]);
    objects[index] = 0;
}

bool CollisionCheck(int position1[], int position2[], int size1[], int size2[]) {   //충동 체크 함수 
   if (position1[0] > position2[0] - size1[0] && position1[0] < position2[0] + size2[0]   //position2[0]-size1[0] = 몬스터 시작지점-캐릭터 가로크기 , position2[0]+size2[0] = 몬스터의 우측 끝
       && position1[1] > position2[1] - size1[1] && position1[1] < position2[1] + size2[1])   //y값 충돌 
      return TRUE;
   else
      return FALSE;
}

bool EnemyPosition(int x, int size_x) {      //캐릭터의 중앙이  몬스터의 중앙보다 왼쪽이면 
   if (character.position[0] + 1 < x + size_x / 2)
      return FALSE;      //몬스터의 방향은 왼쪽 
   else
      return TRUE;      //아니라면 오른쪽 
}

//accel[0]은 캐릭터가 왼쪽대쉬중이면 -9, 오른쪽대쉬중이면 3, accel[1]은 점프키 누르면 -1.75  
void MoveControl(int position[], float accel[], int size[], float *flyTime) {
   float y_value = accel[1];
   
   if (position[1] + size[1] == FLOOR_Y) {
      *flyTime = 0;      //땅에 닿아있으면 flyTime = 0 
   } else {            //떨어져 있으면 flyTime += 0.05 
      *flyTime += 0.05;
      accel[1] += *flyTime; 
   }
   
   if (y_value != 0) {
      if (position[1] + size[1] + y_value > FLOOR_Y)      //땅으로 꺼져서 추락하는거 방지  
         y_value = FLOOR_Y - position[1] - size[1];
   }

   position[0] += floor(accel[0] + 0.5); position[1] += y_value + 0.5;     
   
   //accel이 0이되면 아래 문장들은 실행이 안됌. 
   if (accel[0] > 0) accel[0] -= 0.2; if (accel[0] < 0) accel[0] += 0.2;
   if (accel[1] > 0) accel[1] -= 0.1; if (accel[1] < 0) accel[1] += 0.1;
}

void DrawSprite(int x, int y, int size_x, int size_y, const char spr[]) {   //(x,y)를 기준으로 size_x*size_y크기로 spr[]을 그림 
   for (int i = 0; i < size_y; i++) {
      for (int n = 0; n < size_x; n++)
         EditMap(x + n, y + i, spr[i * size_x + n]);
   }
}

void FillMap(char str[], char str_s, int max_value) {   //str배열을 문자 str_s로 max_value만큼 채움 
   for (int i = 0; i < max_value; i++)
      str[i] = str_s;
}

void EditMap(int x, int y, char str) {   //(x,y)를 문자str로 변경 
   if (x > 0 && y > 0 && x - 1 < MAP_X_MAX && y - 1 < MAP_Y_MAX)
      mapData[(y - 1) * MAP_X_MAX + x - 1] = str;
}

int NumLen(int num) {      //num의 자릿수를 리턴하는 함수 (DrawNumber할때 필요) 
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

void DrawNumber(int x, int y, int num) {      //(x,y)에  char형으로 변환된 숫자를 그림 
   int tmp = num, len = NumLen(tmp), index = len;
    char str[len];      //숫자 자릿수+1 크기의 문자 배열 (1자리는 널문자) 
    
    do {
        index--;
        str[index] = (char)(tmp % 10 + 48);
        tmp /= 10;
    } while(tmp != 0);
    
    DrawSprite(x, y, len, 1, str);
}

void DrawBox(int x, int y, int size_x, int size_y) {      //상태창에 상자 그리는 함수 (x,y)에 size_x*size_y크기의 상자 그림 
   EditMap(x, y, '.'); EditMap(x + size_x - 1, y, '.');
   EditMap(x, y + size_y - 1, '\''); EditMap(x + size_x - 1, y + size_y - 1, '\'');
   
   for (int i = 1; i < size_x - 1; i++) {
      EditMap(x + i, y, '-'); EditMap(x + i, y + size_y - 1, '-');
   }
   for (int i = 1; i < size_y - 1; i++) {
      EditMap(x, y + i, '|'); EditMap(x + size_x - 1, y + i, '|');
   }
}
