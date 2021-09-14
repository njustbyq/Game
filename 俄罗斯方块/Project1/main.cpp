#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define FrameX 13
#define FrameY 3
#define Frame_height 20
#define Frame_width 18

int i, j, Temp, Temp1, Temp2;

int a[80][80] = { 0 };
int b[4];

struct Tetris {
	int x;
	int y;
	int flag;
	int next;
	int speed;
	int number;
	int score;
	int level;
};
HANDLE hOut;

int color(int c);
void gotoxy(int x, int y);
void DrawGameFrame();
void Flag(struct Tetris*);
void MakeTetris(struct Tetris*);
void PrintTetris(struct Tetris*);
void CleanTetris(struct Tetris*);
int ifMove(struct Tetris*);
void Del_Fullline(struct Tetris*);
void Gameplay();
void regulation();
void explation();
void welcom();
void Replay(struct Tetris* trtris);
void title();
void flower();
void close();

int color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}

void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void title() {
	color(15);
	gotoxy(24, 3);
	printf("趣 味 俄 罗 斯 方 块\n");
	color(11);
	gotoxy(18, 5);
	printf("■");
	gotoxy(18, 6);
	printf("■■");
	gotoxy(18, 7);
	printf("■");

	color(14);
	gotoxy(26, 6);
	printf("■■");
	gotoxy(28, 7);
	printf("■■");

	color(10);
	gotoxy(36, 6);
	printf("■■");
	gotoxy(36, 7);
	printf("■■");

	color(13);
	gotoxy(45, 5);
	printf("■");
	gotoxy(45, 6);
	printf("■");
	gotoxy(45, 7);
	printf("■");
	gotoxy(45, 8);
	printf("■");

	color(12);
	gotoxy(56, 6);
	printf("■");
	gotoxy(52, 7);
	printf("■■■");
}

void flower() {
	gotoxy(66, 11);
	color(12);
	printf("(_)");

	gotoxy(64, 12);
	printf("(_)");

	gotoxy(68, 12);
	printf("(_)");

	gotoxy(66, 13);
	printf("(_)");

	gotoxy(67, 12);
	color(6);
	printf("@");

	gotoxy(72, 10);
	color(13);
	printf("(_)");

	gotoxy(76, 10);
	printf("(_)");

	gotoxy(74, 9);
	printf("(_)");

	gotoxy(74, 11);
	printf("(_)");

	gotoxy(75, 10);
	color(6);
	printf("@");

	gotoxy(71, 12);
	printf("|");

	gotoxy(72, 11);
	printf("/");

	gotoxy(70, 13);
	printf("\\|");

	gotoxy(70, 14);
	printf("'|/");

	gotoxy(70, 15);
	printf("\\|");

	gotoxy(71, 16);
	printf("| /");

	gotoxy(71, 17);
	printf("|");

	gotoxy(67, 17);
	color(10);
	printf("\\\\\\");

	gotoxy(73, 17);
	printf("//");

	gotoxy(67, 18);
	color(2);
	printf("^^^^^^^");
}

void welcom() {
	int n;
	int i, j = 1;
	color(14);
	for (int i = 9; i <= 20; i++) {
		for (int j = 15; j <= 60; j++) {
			gotoxy(j, i);
			if (i == 9 || i == 20) printf("=");
			else if (j == 15 || j == 59) printf("||");
		}
	}
	color(12);
	gotoxy(25, 12);
	printf("1.开始游戏");
	gotoxy(40, 12);
	printf("2.按键说明");
	gotoxy(25, 17);
	printf("3.游戏规则");
	gotoxy(40, 17);
	printf("4.退出");
	gotoxy(21, 22);
	color(3);
	printf("请选择[1 2 3 4]:[ ]\b\b");
	color(14);
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
		system("cls");
		DrawGameFrame();
		Gameplay();
		break;

	case 2:
		explation();
		break;

	case 3:
		regulation();
		break;

	case 4:
		close();
		break;
	}
}

void DrawGameFrame() {
	gotoxy(FrameX + Frame_width - 7, FrameY - 2);
	color(11);
	printf("趣味俄罗斯方块");
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 7);
	color(2);
	printf("**********");
	gotoxy(FrameX + 2 * Frame_width + 13, FrameY + 7);
	color(3);
	printf("下一个方块:");
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 13);
	color(2);
	printf("**********");
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 17);
	color(14);
	printf("⬆键：旋转");
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 19);
	printf("空格：暂停游戏");
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 15);
	printf("Esc: 退出游戏");
	gotoxy(FrameX, FrameY);
	color(12);
	printf("");
	gotoxy(FrameX + 2 * Frame_width - 2, FrameY + FrameY);
	printf("");
	gotoxy(FrameX, FrameY + Frame_height);
	printf("");
	gotoxy(FrameX + 2 * Frame_width - 2, FrameY + Frame_height);
	printf("");
	a[FrameX][FrameY + Frame_height] = 2;
	a[FrameX + 2 * Frame_width - 2][FrameY + Frame_height] = 2;
	for (i = 2; i < 2 * Frame_width - 2; i += 2) {
		gotoxy(FrameX + i, FrameY);
		printf("==");
	}

	for (i = 2; i < 2 * Frame_width - 2; i += 2) {
		gotoxy(FrameX + i, FrameY + Frame_height);
		printf("==");
		a[FrameX + i][FrameY + Frame_height] = 2;
	}

	for (i = 1; i < Frame_height; i++) {
		gotoxy(FrameX, FrameY + i);
		printf("||");
		a[FrameX][FrameY + i] = 2;
	}

	for (int i = 1; i < Frame_height; i++) {
		gotoxy(FrameX + 2 * Frame_width - 2, FrameY + i);
		printf("||");
		a[FrameX + 2 * Frame_width - 2][FrameY + i] = 2;
	}
}

void MakeTetris(struct Tetris* tetris) {
	a[tetris->x][tetris->y] = b[0];
	switch (tetris->flag)
	{
	case 1:
	{
		color(10);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x + 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 2:
	{
		color(13);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y] = b[2];
		a[tetris->x + 4][tetris->y] = b[3];
		break;
	}
	case 3:
	{
		color(13);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y - 2] = b[2];
		a[tetris->x][tetris->y + 1] = b[3];
		break;
	}
	case 4:
	{
		color(11);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y] = b[2];
		a[tetris->x][tetris->y + 1] = b[3];
		break;
	}
	case 5:
	{
		color(11);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y] = b[2];
		a[tetris->x][tetris->y + 1] = b[3];
		break;
	}
	case 6:
	{
		color(11);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 7:
	{
		color(11);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 8:
	{
		color(14);
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x + 2][tetris->y + 1] = b[3];
		break;
	}
	case 9:
	{
		color(14);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y] = b[2];
		a[tetris->x - 2][tetris->y + 1] = b[3];
		break;
	}
	case 10:
	{
		color(14);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 11:
	{
		color(14);
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x - 2][tetris->y] = b[3];
		break;
	}
	case 12:
	{
		color(12);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x - 2][tetris->y - 1] = b[3];
		break;
	}
	case 13:
	{
		color(12);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 14:
	{
		color(12);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 15:
	{
		color(12);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x - 2][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 16:
	{
		color(10);
		a[tetris->x][tetris->y + 1] = b[1];
		a[tetris->x][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y - 1] = b[3];
		break;
	}
	case 17:
	{
		color(12);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x + 2][tetris->y + 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 18:
	{
		color(12);
		a[tetris->x][tetris->y - 1] = b[1];
		a[tetris->x + 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	case 19:
	{
		color(12);
		a[tetris->x - 2][tetris->y] = b[1];
		a[tetris->x - 2][tetris->y - 1] = b[2];
		a[tetris->x + 2][tetris->y] = b[3];
		break;
	}
	}
}

void PrintTetris(struct Tetris* tetris) {
	for (int i = 0; i < 4; i++) {
		b[i] = 1;
	}
	MakeTetris(tetris);
	for (i = tetris->x - 2; i <= tetris->x + 4; i += 2) {
		for (j = tetris->y - 2; j <= tetris->y + 1; j++) {
			if (a[i][j] == 1 && j > FrameY) {
				gotoxy(i, j);
				printf("■");
			}
		}
	}
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 1);
	color(4);
	printf("level : ");
	color(12);
	printf(" %d", tetris->level);
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 3);
	color(4);
	printf("score : ");
	color(12);
	printf(" %d", tetris->score);
	gotoxy(FrameX + 2 * Frame_width + 3, FrameY + 5);
	color(4);
	printf("speed : ");
	color(12);
	printf(" %dms", tetris->speed);
}

int ifMove(struct Tetris* tetris) {
	if (a[tetris->x][tetris->y] != 0)
	{
		return 0;
	}
	else
	{
		if (
			(tetris->flag == 1 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x + 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			(tetris->flag == 2 && (a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y] == 0 && a[tetris->x + 4][tetris->y] == 0)) ||
			(tetris->flag == 3 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y - 2] == 0 && a[tetris->x][tetris->y + 1] == 0)) ||
			(tetris->flag == 4 && (a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y] == 0 && a[tetris->x][tetris->y + 1] == 0)) ||
			(tetris->flag == 5 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 && a[tetris->x - 2][tetris->y] == 0)) ||
			(tetris->flag == 6 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x - 2][tetris->y] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			(tetris->flag == 7 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			(tetris->flag == 8 && (a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x - 2][tetris->y] == 0 && a[tetris->x + 2][tetris->y + 1] == 0)) ||
			(tetris->flag == 9 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x - 2][tetris->y] == 0 && a[tetris->x - 2][tetris->y + 1] == 0)) ||
			(tetris->flag == 10 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x - 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			(tetris->flag == 11 && (a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x - 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			(tetris->flag == 12 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 && a[tetris->x - 2][tetris->y - 1] == 0)) ||
			(tetris->flag == 15 && (a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x - 2][tetris->y + 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			(tetris->flag == 14 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 && a[tetris->x + 2][tetris->y + 1] == 0)) ||
			(tetris->flag == 13 && (a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			(tetris->flag == 16 && (a[tetris->x][tetris->y + 1] == 0 &&
				a[tetris->x][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y - 1] == 0)) ||
			(tetris->flag == 19 && (a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x - 2][tetris->y - 1] == 0 && a[tetris->x + 2][tetris->y] == 0)) ||
			(tetris->flag == 18 && (a[tetris->x][tetris->y - 1] == 0 &&
				a[tetris->x][tetris->y + 1] == 0 && a[tetris->x - 2][tetris->y + 1] == 0)) ||
			(tetris->flag == 17 && (a[tetris->x - 2][tetris->y] == 0 &&
				a[tetris->x + 2][tetris->y + 1] == 0 && a[tetris->x + 2][tetris->y] == 0)))
		{
			return 1;
		}
		return 0;
	}
}

void CleanTetris(struct Tetris* tetris) {
	for (i = 0; i < 4; i++) {
		b[i] = 0;
	}
	MakeTetris(tetris);
	for (i = tetris->x - 2; i <= tetris->x + 4; i++) {
		for (j = tetris->y - 2; j <= tetris->y + 1; j++) {
			if (a[i][j] == 0 && j > FrameY) {
				gotoxy(i, j);
				printf("  ");
			}
		}
	}
}

void Del_Fullline(struct Tetris* tetris) {
	int k, del_rows = 0;
	for (j = FrameY + Frame_height - 1; j >= FrameY + 1; j--) {
		k = 0;
		for (i = FrameX + 2; i < FrameX + 2 * Frame_width - 2; i += 2) {
			if (a[i][j] == 1) {
				k++;
				if (k == Frame_width - 2) {
					for (k = FrameX + 2; k < FrameX + 2 * Frame_width - 2; k += 2) {
						a[k][j] = 0;
						gotoxy(k, j);
						printf("  ");
					}
					for (k = j - 1; k > FrameY; k--) {
						for (i = FrameX + 2; i < FrameX + 2 * Frame_width - 2; i += 2) {
							if (a[i][k] == 1) {
								a[i][k] = 0;
								gotoxy(i, k);
								printf("  ");
								a[i][k + 1] = 1;
								gotoxy(i, k + 1);
								printf("■");
							}
						}
					}
					j++;
					del_rows++;
				}
			}
		}
	}
	tetris->score += 100 * del_rows;
	if (del_rows > 0 && (tetris->score % 1000 == 0 || tetris->score / 1000 > tetris->level - 1))
	{
		tetris->speed -= 20;
		tetris->level += 1;
	}
}

void Flag(struct Tetris* tetris) {
	tetris->number++;
	srand(time(NULL));
	if (tetris->number == 1) {
		tetris->flag = rand() % 19 + 1;
	}
	tetris->next = rand() % 19 + 1;
}

void Gameplay() {
	int n;
	struct Tetris t, * tetris = &t;
	char ch;
	tetris->number = 0;
	tetris->speed = 300;
	tetris->score = 0;
	tetris->level = 1;
	while (1)
	{
		Flag(tetris);
		Temp = tetris->flag;
		tetris->x = FrameX + 2 * Frame_width + 6;
		tetris->y = FrameY + 10;
		tetris->flag = tetris->next;
		PrintTetris(tetris);
		tetris->x = FrameX + Frame_width;
		tetris->y = FrameY - 1;
		tetris->flag = Temp;

		while (1)
		{
		label:PrintTetris(tetris);
			Sleep(tetris->speed);
			CleanTetris(tetris);
			Temp1 = tetris->x;
			Temp2 = tetris->flag;
			if (_kbhit())
			{
				ch = _getch();
				if (ch == 75)
				{
					tetris->x -= 2;
				}
				if (ch == 77)
				{
					tetris->x += 2;
				}
				if (ch == 80)
				{
					if (ifMove(tetris) != 0)
					{
						tetris->y += 2;
					}
					if (ifMove(tetris) == 0)
					{
						tetris->y = FrameY + Frame_height - 2;
					}
				}
				if (ch == 72)
				{
					if (tetris->flag >= 2 && tetris->flag <= 3)
					{
						tetris->flag++;
						tetris->flag %= 2;
						tetris->flag += 2;
					}
					if (tetris->flag >= 4 && tetris->flag <= 7)
					{
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 4;
					}
					if (tetris->flag >= 8 && tetris->flag <= 11)
					{
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 8;
					}
					if (tetris->flag >= 12 && tetris->flag <= 15)
					{
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 12;
					}
					if (tetris->flag >= 16 && tetris->flag <= 19)
					{
						tetris->flag++;
						tetris->flag %= 4;
						tetris->flag += 16;
					}
				}
				if (ch == 32)
				{
					PrintTetris(tetris);
					while (1)
					{
						if (_kbhit())
						{
							ch = _getch();
							if (ch == 32)
							{
								goto label;
							}
						}
					}
				}
				if (ch == 27)
				{
					system("cls");
					memset(a, 0, 6400 * sizeof(int));
					welcom();
				}
				if (ifMove(tetris) == 0)
				{
					tetris->x = Temp1;
					tetris->flag = Temp2;
				}
				else
				{
					goto label;
				}
			}
			tetris->y++;
			if (ifMove(tetris) == 0)
			{
				tetris->y--;
				PrintTetris(tetris);
				Del_Fullline(tetris);
				break;
			}
		}
		for (i = tetris->y - 2; i < tetris->y + 2; i++) {
			if (i == FrameY)
			{
				system("cls");
				gotoxy(29, 7);
				printf("  \n");
				color(12);
				printf("\t\t\t■ ■ ■ ■      ■      ■        ■ ■       \n");
				printf("\t\t\t■               ■ ■   ■        ■    ■     \n");
				printf("\t\t\t■ ■ ■         ■   ■ ■        ■     ■    \n");
				printf("\t\t\t■               ■    ■■        ■    ■     \n");
				printf("\t\t\t■ ■ ■ ■      ■      ■        ■ ■       \n");
				gotoxy(17, 18);
				color(14);
				printf("我要重新玩一局-------1");
				gotoxy(44, 18);
				printf("不玩了，退出吧-------2");
				int n;
				gotoxy(32, 20);
				printf("选择【1/2】: ");
				color(11);
				scanf_s("%d", &n);
				switch (n)
				{
				case 1:
					system("cls");
					Replay(tetris);
					break;
				case 2:
					exit(0);
					break;
				}
			}
		}
		tetris->flag = tetris->next;
		tetris->x = FrameX + 2 * Frame_width + 6;
		tetris->y = FrameY + 10;
		CleanTetris(tetris);
	}
}

void Replay(struct Tetris* tetris) {
	system("cls");
	memset(a, 0, 6400 * sizeof(int));
	DrawGameFrame();
	Gameplay();
}

void explation() {
	int i, j = 1;
	system("cls");
	color(13);
	gotoxy(32, 3);
	printf("按键说明");
	color(2);
	for (i = 6; i <= 16; i++) {
		for (j = 15; j <= 60; j++) {
			gotoxy(j, i);
			if (i == 6 || i == 16) printf("=");
			else if (j == 15 || j == 59) printf("||");
		}
	}
	color(3);
	gotoxy(18, 7);
	printf("tip1: 玩家可以通过左右键来移动方块");
	color(10);
	gotoxy(18, 7);
	printf("tip2: 通过向上键使方块旋转");
	color(14);
	gotoxy(18, 7);
	printf("tip3: 通过向下键加速方块下落");
	color(11);
	gotoxy(18, 7);
	printf("tip4: 按空格键暂停游戏，再按空格键继续");
	color(4);
	gotoxy(18, 7);
	printf("tip5: 按ESC退出游戏");
	_getch();
	system("cls");
}

void regulation()
{
	int i, j = 1;
	system("cls");
	color(13);
	gotoxy(34, 3);
	printf("游戏规则");
	color(2);
	for (i = 6; i <= 18; i++) {
		for (j = 12; j <= 70; j++) {
			gotoxy(j, i);
			if (i == 6 || i == 18) printf("=");
			else if (j == 12 || j == 69) printf("||");
		}
	}
	color(12);
	gotoxy(16, 7);
	printf("tip1: 不同形状的小方块从屏幕上方落下，玩家通过调整");
	gotoxy(22, 9);
	printf("方块的位置和方向，使他们在屏幕底部拼出完整的");
	gotoxy(22, 11);
	printf("一行或几行");
	color(14);
	gotoxy(16, 13);
	printf("tip2: 每消除一行，积分增加100");
	color(11);
	gotoxy(16, 15);
	printf("tip3: 每累积1000分，会提升一个等级");
	color(10);
	gotoxy(16, 17);
	printf("tip4: 提升等级会使方块下落速度加快，游戏难度增大");
	_getch();
	system("cls");
	welcom();
}

void close() {
	exit(0);
}

int main() {
	title();
	flower();
	welcom();
}


