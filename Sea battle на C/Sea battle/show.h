//#define size 10
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
const int size = 10;

struct Fild
{
	char field_Player[size][size];
	char field_OfComp[size][size];
};

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void setColor(int text, int background);
void showInfo(const int index, int *statistic_1, int *statistic_2);
void showbattleship(int *statistic_1, int *statistic_2);
void gotoxy(short x, short y);
int menu(int *hard, int *deploy, bool plusMenu = false);
void manyship(int many, int size);
void show_auto(char battleship[][10], bool autoshow);
void menuInfo();
void menuDep(int *deploy);
void menuHard(int *hard);
void info_control(char *line);
void printPole(Fild fild, bool autoshow);