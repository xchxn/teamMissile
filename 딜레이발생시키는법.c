#include <stdio.h>
#include <windows.h>

int main() 
{    
    printf("지우기 1초전\n");
    Sleep(1000);     //1초 딜레이
    system("cls");   //콘솔화면 지우기
    Sleep(1000);
    printf("지우기 완료\n");
    
    return 0;
}
