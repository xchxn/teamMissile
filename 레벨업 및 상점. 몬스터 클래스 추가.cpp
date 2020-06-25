#include <iostream>
#include <windows.h>
#include <string>                   // 메인이나 함수를 따로 만들어 내턴, 상대턴 번갈아가는 기능 조건 만들 필요성 있음  
#define MAX_SIZE 100 
                                   // 위 기능이 있다는 전제 하에 attak, defense, bag, run 
using namespace std;

 bool kill = false;                // 나중에 몬스터를 죽이면 kill을 true;로 바꾼다. true일때 경험치를 올려 레벨을 올리기 위한 조건 
 bool sw = false;                     // 가방에서 주문서  힘강화 할때 사욯하는 조건 
class professor_state    
{
 		 
 public:
	int level;           // 레벨
	int EX_VA;  
 	int experince_value[EX_VA];   // 경험치통 일단 5로 정함 나중에 얘기해서 수정 
	string bag[MAX_SIZE];             // 기본 지급템이나, 상점에서 산 아이템 여기다 저장 
    string skill[MAX_SIZE];       // 기본 스킬이나, 상점에서 산 스킬 여기다 저장 
	void levelup()
	{
		level++;
	} 
};

class store
{
	public:
		int item;
		int potion;
}

class Monster
{
	public: 
	     int level;
	     int giving_experince;
};

void experincevalueup(professor_state a, Monster b )                           // 몬스터 잡을 시 오르는 경험치 함수 
{
		while(kill){ 
		  	  for(int i= 1; i<= b.giving_experince ; i++){          // 몬스터의 giving experince 즉, 몬스터를 잡을시 주는 경험치가 3이라 할때 경험치통 5 에서 3까지 참.  
		  	  	     a.experince_value[i]  = 1;                     // giving experince 와  
				} 
			  for(int i = 1; i <= a.EX_VA; i++){               // 경험치 통 5공간이 모두 1이 될시 레벨업  
			  	if(a.experince_value[i] = 1){
			  		a.levelup();
				    int next = a.EX_VA *2;              // 레벨업 할시  경험치 통 2배되기로 일단 해놈 이것도 나중에 얘기후 수정 
					a[next];		
				  }
			  }	
			  
				
		  }
		 kill = False;	               
}

void attack();              // 공격  : 1번 누르면 1. 스킬1 2. 스킬2 3. 스킬3 이런식으로 쓸수 있는 스킬 보여주고 1.2.3중 하나 선택  
void defense();             // 수비  : 상대턴에 2번을 눌르면 공격처럼 스킬몇가지 띄우고 데미지 감소시키기 
void bag();                 // 가방 : 3번 누르면 가방에 저장된 아이템 사용 가능 
void run();                 // 도망  : 도망 

void menu();

int main()
{
 professor_state Song;             // 주인공인 교수님 생 성 
 Song.skill[0] = "basic attack";       // 기본 공격과 기본스킬 저장 나중에 수치 정해얄듯 
 Song.skill[1] = "basic skill";
 Song.level  = 0;           // 레벨
 Song.EX_VA = 5;
 
 Monster jang;
 jang.giving_experince = 3;
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
   kill = true;
   experincevalueup(Song, jang);   
   cout << "죽었습니다. " << endl; // if 문달아서 상대방한테 봉?? 출력 

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
	int num;
	cout << "무슨 공격을 할까요?" << endl;
	cin >> num;
	switch(num){
		case 1:
			cout << "기본 공격(데미지: 5) " << endl;
			basic attack();
			break; 
		case 2:
			cout << "기본 스킬1(데미지: 10)" << endl;
			basic skill1(); 
			break;
		case 3:
		    cout << "기본 스킬2 (데미지: 15)"  << endl; 
		    basic skill2();
		    break;
	}
}

void basic attack( )                        //만날시 열리는 전투창으로 이동 나중에  
{
	Monster_Hp = Monster_Hp - 5;
	if(sw){
		Monster_Hp = Monster_Hp - 15;
		sw = false;
	}
}

void basic skill1()                             //만날시 열리는 전투창으로 이동 나중에 
{ 
	Monster_Hp = Monster_Hp - 10;
	if(sw){
		Monster_Hp = Monster_Hp - 20;
	    sw = false; 
	}
}

void basic skill2()                              //만날시 열리는 전투창으로 이동 나중에 
{
	Monster_Hp = Monster_Hp - 15;
	if(sw){
		Monster_Hp = Monster_Hp - 25;
	    sw = false; 
	}
}

void bag(){
	int num ;
	cout << " 가방을 여시겠습니까? " << endl;     // 수정'
    cout << " 1. 네  " << endl;
	cout << " 2. 아니오 " << endl;
	cin >> num;
	if(num = 1){
		cout << " 멀꺼내시겠습니까? " << endl;
		cout << " 1. 사과 " << endl;
		cout << " 2. 주문서 " << endl; 
		switch(num){
			case 1:
				heal();    // 사과를 먹게 되면 체력 힐       나중에 밑에 힐 함수 만들어야함. 
			case 2: 
				strup();  // 주문서를 통한 공격력 강화        나중에 밑에 함수 만들어야함. 
				
		}
		
	} 
}

void heal()             // 나중에 만날시 열리는 전투창에 옮겨야함. 
{
	int hp_up = 10;
	Song_ hp = Song_ hp +10;
	
}

void strup()            //나중에 만날시 열리는 전투창에 옮겨야함. 
{
	sw = true;     // 나중에 만날시 열리는 전투창에서 전역변수로 빼야할듯, 그리고 강화된 상태에서 평타나 스킬때리면 원래대로 돌아옴. 
	int str_up = 10;
	cout << "모든 공격과 스킬에 공격력 10이 붙었습니다." << endl;
}

void run(){
	int num; 
	int num_2;
	cout << "도망가시겠습니까? " << endl;      
	cout << "1. 네 도망가겠습니다." << endl;
	cout << "2. 아니요." << endl;
	cin >> num;
	switch(num){
		case 1:
			selMenu = 5;
		case 2:
			cout<<"1.공격하시겠습니까?" << endl;
			cout<<"2.가방을 여시겠습니까?" << endl;
			cin >> num_2;
			if(num_2 == 1){
				attach();
			}
			if(num_2 == 2){
				bag();
			}
	}	
}
