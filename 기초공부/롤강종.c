#include <stdio.h>
#include <windows.h>
#include <conio.h>
int main(void)
{
	system("taskkill /f /im \"League of Legends.exe\"");
	system("taskkill /f /im \"LeagueClient.exe\"");
	getchar();
	return 0;
}
