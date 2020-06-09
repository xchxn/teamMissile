#include <iostream>
#include <conio.h>
#include <windows.h>
 
#define UP 0x48
#define LEFT 0x4B
#define RIGHT 0x4D
#define DOWN 0x50
#define SPACE 0x20

class CCharacter {
    int m_x, m_y;
    char m_ch;
    int m_key;
public:
    CCharacter(char ch) : m_x(0), m_y(0) //생성자(x,y좌표값을 모두 0으로 초기화 시킨다.)
    {
        m_ch = ch;
    }
    void gotoxy() {//커서이동함수
        COORD Cur;
        Cur.X = m_x;
        Cur.Y = m_y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
    }
    bool KeyProcess() {
        if (kbhit()) // 키입력을 체크
        {
            m_key = getch();
            switch (m_key) {
            case UP: m_y--; break;
            case DOWN: m_y++; break;
            case LEFT: m_x--; break;
            case RIGHT: m_x++; break;
            case SPACE: break;
            }
            return true;
        }
        return false;
    }
    void Draw() {
        system("cls"); // 화면을 지운다.
        gotoxy();//커서를 이동시킨다.
        printf("%c", m_ch); //문자출력
        
    }
};
int main(void) {
    CCharacter ch('A');
    while (1) {
        boolean b = ch.KeyProcess();
        if(b) 
        ch.Draw();
    }
}

