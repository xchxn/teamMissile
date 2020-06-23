#include <iostream>
#include <windows.h>
#include <string>                   // 메인이나 함수를 따로 만들어 내턴, 상대턴 번갈아가는 기능 조건 만들 필요성 있음  
#define MAX_SIZE 100                // 위 기능이 있다는 전제 하에 attak, defense, bag, run 
using namespace std;

struct professor_state    
{
 string bag[MAX_SIZE];             // 기본 지급템이나, 상점에서 산 아이템 여기다 저장 
 string skill[MAX_SIZE];           // 기본 스킬이나, 상점에서 산 스킬 여기다 저장 
 int level;                     // 레벨  
 int hp;                      // 체력 
};

void attack();              // 공격  : 1번 누르면 1. 스킬1 2. 스킬2 3. 스킬3 이런식으로 쓸수 있는 스킬 보여주고 1.2.3중 하나 선택  
void defense();             // 수비  : 상대턴에 2번을 눌르면 공격처럼 스킬몇가지 띄우고 데미지 감소시키기 
void bag();                 // 가방 : 3번 누르면 가방에 저장된 아이템 사용 가능 
void run();                 // 도망  : 도망 

void menu();

int main()
{
 professor_state Song, jang, Red;  // 송, 장, 홍 교수님 캐릭터 생성 
 int selMenu;        
   

 while(1)
 {
  system("cls");
  menu();
  cout << "선택하세요  "; 
  cin >> selMenu;
  fflush(stdin);
  system("cls");
  switch(selMenu)
  {
  case 1:
   attack();
   break;
  case 2:
   defense(); 
   break;
  case 3:
   bag();
   break;
  case 4:
   run();
   break;
  case 5:
   cout << "이겼습니다." << endl;  // if 문달아서 상대방을 이겼을때 출력 
   cout << "죽었습니다. " << endl; // if 문달아서 상대방한테 졋을떄 출력 
                                     
   return 0;                       // 그리고 종료  

   } 
  system("pause");
 }
 return 0;
}

void menu()
{
    cout <<"┏━━━━━━━━━━━━━┓" << endl;
    cout <<"┃          전   투!!!      ┃" << endl;
    cout <<"┃       1. 공   격         ┃" << endl;
    cout <<"┃       2. 수   비         ┃" << endl;
    cout <<"┃       3. 가   방         ┃" << endl;
    cout <<"┃       4. 도   망         ┃" << endl;
    cout <<"┃                          ┃" << endl; 
    cout <<"┗━━━━━━━━━━━━━┛" << endl;
   
}

void attack(){
	cout << "공격" << endl;       // 이제 시간 날떄 수정 
}
void defense(){
	cout << "수비 " << endl;   // 수정 
}
void bag(){
	cout << " 가방 " << endl;     // 수정 
}
void run(){
	cout << "도 망 " << endl;       // 수정  
}

