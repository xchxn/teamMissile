#include <stdio.h>
#include <Windows.h>
#include <MMSystem.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib") 
#define BGM C:\\Users\\조민서\\Downloads\\bensound-hey  // 파일위치 , 파일은 Wav파일만 가능 

int main()
{	
	sndPlaySoundA("BGM",SND_ASYNC | SND_NODEFAULT | SND_LOOP); // 음악연주 C:\\~~~ 는 경로명을 입력합니다. (단, 폴더를 구분하는 역슬래쉬는 2번 써 줘야 합니다. 예) C:\test\aa.wav  일 경우 "C:\\test\\aa.wav"
	system("pause");
	return 0;
}
