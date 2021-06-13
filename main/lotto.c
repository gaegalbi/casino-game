#include <time.h>
#include <Windows.h>
extern void textcolor(int);
extern void gotoxy(int, int);
int lotto() {
	int comlotto[6] = { 0 };
	int userlotto[7] = { 0 };
	int corretlotto = 0;
	int bonus = 0;
	time_t ltime;
	struct tm tmCurTime;
	int year, month, day;
	time(&ltime);
	localtime_s(&tmCurTime,&ltime);
	year = tmCurTime.tm_year + 1900;
	month = tmCurTime.tm_mon + 1;
	day = tmCurTime.tm_mday;
	for (int i = 0; i < 6; ) {
		*(comlotto + i) = rand() % 45 + 1;
		int j;
		for (j = 0; j < i; ++j)
			if (*(comlotto + i) == *(comlotto + j))
				break;
		if (i == j)
			++i;
	}

	for (int i = 0; i < 7; ) {
		*(userlotto + i) = rand() % 45 + 1;
		int j;
		for (j = 0; j < i; ++j)
			if (*(userlotto + i) == *(userlotto + j))
				break;
		if (i == j)
			++i;
	}
	textcolor(15);
	gotoxy(2, 1); printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	for (int i = 0; i < 10; i++)
	{
		gotoxy(2, 2 + i); printf("┃                       ┃");
	}
	gotoxy(2, 12); printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(11, 2); printf("영진복권");
	gotoxy(4, 5); printf("발행일:%d/%02d/%02d", year, month, day);
	gotoxy(4, 6); printf("일렬번호: %d", 10000 + rand() % 50000);
	gotoxy(4, 7); printf("----------------------");


	gotoxy(4, 9); printf("----------------------");
	gotoxy(4, 11); printf("금액            \\1,000");
	gotoxy(1, 14);
	printf("당첨번호: ");
	for (int i = 0; i < 6; i++)
	{
		printf("%d ", comlotto[i]);
	}
	gotoxy(5, 8);
	for (int i = 0; i < 6; i++)
	{
		Sleep(500);
		PlaySound(TEXT("sound\\paper.wav"), NULL, SND_ASYNC);

		for (int j = 0; j < 6; j++)
		{
			if (*(userlotto + i) == *(comlotto + j)) {

				textcolor(12);
				corretlotto++;
				break;
			}
		}
		if (*(userlotto + 6) == *(comlotto + i)) {
			corretlotto++;
			bonus = 1;
		}
		printf("%2d ", userlotto[i]);
		textcolor(15);
	}
	Sleep(500);
	PlaySound(TEXT("sound\\paper.wav"), NULL, SND_ASYNC);
	if (bonus == 1)
		textcolor(12);
	printf("%2d ", userlotto[6]);
	Sleep(500);
	textcolor(15);
	gotoxy(10, 16);
	switch (corretlotto)
	{
	case 0:
	case 1:
	case 2:
		gotoxy(12, 16);
		printf("꽝\n");
		PlaySound(TEXT("sound\\draw.wav"), NULL, SND_ASYNC);
		return 0;
	case 3:
		printf("5등 당첨!\n");
		printf("      5,000원을 얻었다!!!\n");
		PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
		return 5000;
	case 4:
		printf("4등 당첨!\n");
		printf("     50,000원을 얻었다!!!\n");
		PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
		return 50000;
	case 5:
		printf("3등 당첨!\n");
		printf("    1,000,000원을 얻었다!!!\n");
		PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
		return 1000000;
	case 6:
		if (bonus == 0) {
			printf("1등 당첨!\n");
			printf("   1,000,000,000원을 얻었다!!!\n");
			PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
			return 1000000000;
		}
		printf("2등 당첨!\n");
		printf("    50,000,000원을 얻었다!!!\n");
		PlaySound(TEXT("sound\\win.wav"), NULL, SND_ASYNC);
		return 50000000;
	}
	return 0;
}