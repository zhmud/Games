#include "show.h"

void setColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void showInfo(const int index, int *statistic_1, int *statistic_2)
{
	SetConsoleCP(866);
	switch (index)
	{
	case 0:{ setColor(3, 0); cout << " Корабли компьютера ( " << statistic_1[0] + statistic_1[1] +
		statistic_1[2] + statistic_1[3] << " )";  setColor(15, 0); }						   break;
	case 1:{ setColor(3, 0); cout << "    XXXX - " << statistic_1[3];		setColor(15, 0); } break;
	case 2:{ setColor(3, 0); cout << "    XXX - " << statistic_1[2];		setColor(15, 0); } break;
	case 3:{ setColor(3, 0); cout << "    XX - " << statistic_1[1];			setColor(15, 0); } break;
	case 4:{ setColor(3, 0); cout << "    X - " << statistic_1[0];			setColor(15, 0); } break;
	case 5:{ setColor(10, 0); cout << " Корабли игрока ( " << statistic_2[0] + statistic_2[1] +
		statistic_2[2] + statistic_2[3] << " )";      setColor(15, 0); }					   break;
	case 6:{ setColor(10, 0); cout << "    XXXX - " << statistic_2[3];		setColor(15, 0); } break;
	case 7:{ setColor(10, 0); cout << "    XXX - " << statistic_2[2];		setColor(15, 0); } break;
	case 8:{ setColor(10, 0); cout << "    XX - " << statistic_2[1];		setColor(15, 0); } break;
	case 9:{ setColor(10, 0); cout << "    X - " << statistic_2[0];			setColor(15, 0); } break;
	default:																				   break;
	}
	SetConsoleCP(1251);
}

void manyship(int many, int size)
{
	SetConsoleCP(866);
	switch (size)
	{
	case 0:{ gotoxy(66, 2); many <= 3 ? setColor(12, 0) : setColor(3, 0); cout << many << ' ';  setColor(15, 0); } break;
	case 1:{ gotoxy(55, 4); setColor(3, 0); cout << many;	setColor(15, 0); } break;
	case 2:{ gotoxy(54, 6); setColor(3, 0); cout << many;	setColor(15, 0); } break;
	case 3:{ gotoxy(53, 8); setColor(3, 0); cout << many;	setColor(15, 0); } break;
	case 4:{ gotoxy(52, 10); setColor(3, 0); cout << many;	setColor(15, 0); } break;
	case 5:{ gotoxy(62, 12); many <= 3 ? setColor(12, 0) : setColor(10, 0); cout << many << ' '; setColor(15, 0); } break;
	case 6:{ gotoxy(55, 14); setColor(10, 0); cout << many;	setColor(15, 0); } break;
	case 7:{ gotoxy(54, 16); setColor(10, 0); cout << many;	setColor(15, 0); } break;
	case 8:{ gotoxy(53, 18); setColor(10, 0); cout << many;	setColor(15, 0); } break;
	case 9:{ gotoxy(52, 20); setColor(10, 0); cout << many; setColor(15, 0); } break;
	default:																   break;
	}
	SetConsoleCP(1251);
}

void showbattleship(int *statistic_1, int *statistic_2)
{
	SetConsoleCP(1251);
	const unsigned char up[] = { 218, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 191 };
	const unsigned char down[] = { 192, 196, 193, 196, 193, 196, 193, 196, 193, 196, 193, 196, 193, 196, 193, 196, 193, 196, 193, 196, 217 };
	system("cls");
	for (int k = 0; k < 2; k++)
	{
		cout << " ";
		for (int i = 0; i < size; i++)
		{
			cout << " " << (char)(i + 'A');
		}
		cout << " ";
	}
	cout << endl;
	cout << " ";
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 21; i++)
		{
			cout << up[i];
		}
		cout << " ";
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		bool one = true;
		for (int n = 0; n < 2; n++)
		{
			cout << i;
			for (int j = 0; j < size; j++)
			{
				cout << (char)179;
				cout << " ";
				if (j == size - 1)
				{
					cout << (char)179;
				}
			}
		}
		showInfo(i, statistic_1, statistic_2);
		cout << endl << " ";
		for (int k = 0; k < 2; k++)
		{
			if (i < size - 1)
			{
				for (int j = 0; j < size - 1; j++)
				{
					if (j == 0)
					{
						cout << (char)195 << (char)196;
					}
					cout << (char)197 << (char)196;
					if (j == size - 2)
					{
						cout << (char)180;
					}
				}
			}
			if (i != size - 1)
				cout << " ";
		}
		if (i != size - 1)
			cout << endl;
	}
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < 21; i++)
		{
			cout << down[i];
		}
		cout << " ";
	}
	cout << endl;
}

void gotoxy(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int menu(int *hard, int *deploy, bool plusMenu)
{
	int flag = 1; 
	bool showMenu = true;
	SetConsoleCP(866);
	setlocale(LC_ALL, "RUS");
	system("cls");
	do
	{
		system("cls");
		showMenu = true;
		gotoxy(23, 5); setColor(9, 0); cout << "********************************";
		gotoxy(23, 6); setColor(9, 0); cout << "*         МОРСКОЙ БОЙ          *";
		gotoxy(23, 7); setColor(9, 0); cout << "********************************";
		while (showMenu)
		{			
			gotoxy(32, 9); setColor(15, 0); cout << "Главное меню" << endl;
			if (plusMenu)
			{ 
				gotoxy(32, 11); setColor(15, 0); cout << "["; flag == 0 ? setColor(0, 2) : setColor(15, 0); cout << "Продолжить"; setColor(15, 0); cout << "]";
			}
			gotoxy(32, 13); setColor(15, 0); cout << "["; flag == 1 ? setColor(0, 2) : setColor(15, 0); cout << "Новая игра"; setColor(15, 0); cout << "]";
			gotoxy(26, 14); setColor(15, 0); cout << "["; flag == 2 ? setColor(0, 2) : setColor(15, 0); cout << "Уровень сложности игры"; setColor(15, 0); cout << "]";
			gotoxy(30, 15); setColor(15, 0); cout << "["; flag == 3 ? setColor(0, 2) : setColor(15, 0); cout << "Создатель игры"; setColor(15, 0); cout << "]";
			gotoxy(34, 16); setColor(15, 0); cout << "["; flag == 4 ? setColor(0, 2) : setColor(15, 0); cout << "выход"; setColor(15, 0); cout << "]";
			int code = _getch();
			if (flag < 4 && code == 80)
				flag++;
			if ((flag > 1 || (flag > 0 && plusMenu)) && code == 72)
				flag--;
			if (code == 13)
				showMenu = false;
		} 
		system("cls");
		if (flag == 2)
		{
			menuHard(hard);
		}
		else if (flag == 3)
		{
			menuInfo();
		}
		else if (flag == 1)
		{
			menuDep(deploy);
			return 2;
		}
		else if (flag == 0)
		{
			return 1;
		}
		else
			exit(0);
	} while (true);
}

void show_auto(char battleship[][10], bool autoshow)
{
	SetConsoleCP(866);
	gotoxy(59, 23); 
	if (autoshow)
	{
		setColor(12, 0); cout << "( Вкл ) ";
	}
	else
	{
		setColor(14, 0); cout << "( Выкл )";
	}
	SetConsoleCP(1251);
	for (int k = 0; k < 10; k++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (battleship[k][j] == 6)
			{
				gotoxy((k + 1) * 2 + 22, (j + 1)* 2);
				if (autoshow)
				{
					setColor(15, 0); cout << char(248);
				}
				else
				{
					setColor(0, 0); cout << ' ';
				}
			}
		}
	}
}

void menuInfo()
{
	gotoxy(21, 10); setColor(0, 2); cout << "*****************************************";
	gotoxy(21, 11); setColor(0, 2); cout << "*        Студент группы ВНУ-1322        *";
	gotoxy(21, 12); setColor(0, 2); cout << "*             Жмуд Евгений              *";
	gotoxy(21, 13); setColor(0, 2); cout << "*                 2014                  *";
	gotoxy(21, 14); setColor(0, 2); cout << "*****************************************";
	setColor(15, 0);
	_getch();
}

void menuDep(int *deploy)
{
	bool showMenu = true;
	do
	{
		gotoxy(30, 10); setColor(15, 0); cout << "Расставить корабли" << endl;
		gotoxy(25, 12); setColor(15, 0); cout << "["; *deploy == 1 ? setColor(0, 2) : setColor(15, 0); cout << "Автоматически"; setColor(15, 0); cout << "]";
		gotoxy(45, 12); setColor(15, 0); cout << "["; *deploy == 2 ? setColor(0, 2) : setColor(15, 0); cout << "Вручную"; setColor(15, 0); cout << "]";
		int code = _getch();
		if (*deploy < 2 && code == 77)
			(*deploy)++;
		if (*deploy > 1 && code == 75)
			(*deploy)--;
		if (code == 13)
			showMenu = false;
	} while (showMenu);
}

void menuHard(int *hard)
{
	bool showMenu = true;
	do
	{
		gotoxy(29, 10); setColor(15, 0); cout << "Уровень сложности игры" << endl;
		gotoxy(25, 12); setColor(15, 0); cout << "["; *hard == 1 ? setColor(0, 2) : setColor(15, 0); cout << "Высокий"; setColor(15, 0); cout << "]";
		gotoxy(36, 12); setColor(15, 0); cout << "["; *hard == 2 ? setColor(0, 2) : setColor(15, 0); cout << "Средний"; setColor(15, 0); cout << "]";
		gotoxy(47, 12); setColor(15, 0); cout << "["; *hard == 3 ? setColor(0, 2) : setColor(15, 0); cout << "Легкий"; setColor(15, 0); cout << "]";
		int code = _getch();
		if (*hard < 3 && code == 77)
			(*hard)++;
		if (*hard > 1 && code == 75)
			(*hard)--;
		if (code == 13)
			showMenu = false;
	} while (showMenu);
}

void info_control(char *line)
{
	SetConsoleCP(866);
	gotoxy(2, 23); setColor(14, 0); cout << "Управление - стрелки";
	gotoxy(46, 23); setColor(14, 0); cout << line;
	gotoxy(46, 24); setColor(14, 0); cout << "Выход в меню - Esc";
	gotoxy(2, 24); setColor(14, 0); cout << "Принять - Enter";
}

void printPole(Fild fild, bool autoshow)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			SetConsoleCP(1251);
			gotoxy((i + 1) * 2, (j + 1) * 2);
			if (fild.field_Player[i][j] == 2) { setColor(15, 0); cout << 'X'; }
			else if (fild.field_Player[i][j] == 1) { setColor(11, 0); cout << (char)248; }
			else if (fild.field_Player[i][j] == 3) { setColor(12, 0); cout << '*'; }
			else if (fild.field_Player[i][j] == 5) { setColor(14, 0); cout << '#'; }
			gotoxy(22 + (i + 1) * 2, (j + 1) * 2);
			if (fild.field_OfComp[i][j] == 1) { setColor(11, 0); cout << (char)248; }
			else if (fild.field_OfComp[i][j] == 6 && autoshow) { setColor(15, 0); cout << (char)248; }
			else if (fild.field_OfComp[i][j] == 3) { setColor(12, 0); cout << '*'; }
			else if (fild.field_OfComp[i][j] == 5) { setColor(14, 0); cout << '#'; }
			SetConsoleCP(866);
		}
	}
}