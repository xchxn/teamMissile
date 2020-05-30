#include <iostream>
#include <windows.h>
#include <string>
#define MAX_SIZE 100
using namespace std;

struct professor_state    
{
 string bag[MAX_SIZE];
 string skill[MAX_SIZE];    
 int level;
 int hp; 
};

void attack();
void bag();
void run();

void menu();

int main()
{
 professor_state Song, jang, Red;  
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
   bag();
   break;
  case 3:
   run();
   break;
  case 4:
   cout << "이겼습니다." << endl;  // if 문달아서 상대방을 이겼을때 출력 
   cout << "죽었습니다. " << endl; // if 문달아서 상대방한테 졋을떄 출력 
   return 0; 

   } 
  system("pause");
 }
 return 0;
}

void menu()
{
    cout <<"┏━━━━━━━━━━━━━┓" << endl ;
    cout <<"┃          전   투!!!      ┃" << endl;
    cout <<"┃                          ┃" << endl;
    cout <<"┃       1. 공   격         ┃" << endl;
    cout <<"┃       2. 가   방         ┃" << endl;
    cout <<"┃       3. 도   망         ┃" << endl;
    cout <<"┃       4. (피 0될시 종료) ┃" << endl;
   cout << "┗━━━━━━━━━━━━━┛" << endl;
   
}

void attack(){
	cout << "공격" << endl;
}

void bag(){
	cout << " 가방 " << endl;
}
void run(){
	cout << "도 망 " << endl;
}

