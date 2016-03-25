#include "game.h"


int game()
{
	bool autoshow = false;
	int index = 0;
	int hard = 3;
	int deploy = 1;
	int x = 24;
	int y = 2;
	int Xcom;
	int Ycom;
	do
	{
		if (index == 0)
		{
			menu(&hard, &deploy);
		}
		Fild fild = { { 0 }, { 0 } };
		int nea = -1;
		bool hit = true;
		int Abulo[4] = { 0 };
		int countship[2][4] = { { 4, 3, 2, 1 }, { 4, 3, 2, 1 } };
		if (deployship(fild.field_Player, countship, deploy))
		{
			positionship(fild.field_OfComp, false);
			info_control("Помощь - F1  ( Выкл )");
			bool mode = false;
			do
			{
				int wound = 1;
				while (wound > 0)
				{
					if (!zalpPlayer(fild.field_OfComp, &x, &y, &mode, countship[0], &autoshow))
						wound = 0;
					if (mode)
					{
						int onesekond = menu(&hard, &deploy, mode);
						if (onesekond == 1)
						{
							mode = false;
							showbattleship(countship[0], countship[1]);
							printPole(fild, autoshow);
							info_control("Помощь - F1  ( Выкл )");
							if (autoshow)
							{
								gotoxy(59, 23); setColor(12, 0); cout << "( Вкл ) ";
							}
						}
						else if (onesekond == 2 || onesekond == 5)
						{
							index = 1;
							wound = -1;
						}
					}
				}
				if (wound == -1)
					break;
				if (zalpComp(fild.field_Player, &Xcom, &Ycom, hard, &hit, Abulo, &nea, countship[1]) == 5)
				{
					index = 0;
					break;
				}
			} while (true);
		}
		else
		{
			index = 0;
		}
	} while (true);
	_getch();
}

int showships(char battleship[][size], const int X, const int Y, const int sizechip, const int orientation, bool paint)
{
	if ((X <= 10 - sizechip) && (!orientation))
	{
		for (int i = 0; i < sizechip; i++)
		{
			if (!(battleship[X + i][Y] == 0) || (battleship[X + i][Y] == 4))
				return 0;
		}
		for (int i = 0; i < sizechip; i++)
		{
			touch(battleship, X + i, Y, 4);
		}
		for (int i = 0; i < sizechip; i++)
		{
			battleship[X + i][Y] = 2;
			if (paint)
			{
				gotoxy((X + i + 1) * 2, (Y + 1) * 2);
				setColor(15, 0); cout << 'X';
			}
		}
		return 1;
	}
	else if ((Y <= 10 - sizechip) && orientation)
	{
		for (int i = 0; i < sizechip; i++)
		{
			if (!(battleship[X][Y + i] == 0) || (battleship[X][Y + i] == 4))
				return 0;
		}
		for (int i = 0; i < sizechip; i++)
		{
			touch(battleship, X, Y + i, 4);
		}
		for (int i = 0; i < sizechip; i++)
		{
			battleship[X][Y + i] = 2;
			if (paint)
			{
				gotoxy((X + 1) * 2, (Y + i + 1) * 2);
				setColor(15, 0); cout << 'X';
			}
		}
		return 1;
	}
	return 0;
}

void touch(char battleship[][size], const int X, const int Y, const int tou)
{
	for (int i = -1; i < 2; i++)
	{
		if (X + i >= 0 && X + i <= 9)
		{
			if (Y + 1 <= 9 && (battleship[X + i][Y + 1] == 0 || battleship[X + i][Y + 1] == 4))
				battleship[X + i][Y + 1] = tou;
			if (Y - 1 >= 0 && (battleship[X + i][Y - 1] == 0 || battleship[X + i][Y - 1] == 4))
				battleship[X + i][Y - 1] = tou;
		}
	}
	if (X - 1 >= 0 && (battleship[X - 1][Y] == 0 || battleship[X - 1][Y] == 4))
		battleship[X - 1][Y] = tou;
	if (X + 1 <= 9 && (battleship[X + 1][Y] == 0 || battleship[X + 1][Y] == 4))
		battleship[X + 1][Y] = tou;
}

int keyEnter(int *x, int *y, int size, bool *flag)
{
	int code = _getch();
	if (code == 80 && ((*y) < 18 - (size * 2) || !(*flag)) && (*y) < 18)
		(*y) += 2;
	else if (code == 72 && (*y) >= 2) 
		(*y) -= 2;
	else if (code == 77 && ((*x) < 18 - (size * 2) || (*flag)) && (*x) < 18)
		(*x) += 2;
	else if (code == 75 && (*x) >= 2) 
		(*x) -= 2;
	else if (code == 32)
		(*flag) = !(*flag);
	else if (code == 13)
		return 1;
	else if (code == 27)
		return 2;
	return 0;
}

int positionship(char battleship[][size], bool paint)
{
	for (int i = 1; i < 5; i++)
	{
		int good = 0;		
		while (good < i)
		{
			if (showships(battleship, rand() % size, rand() % size, 5 - i,rand() % 2, paint) != 0)
			{
				good++;
				manyship(good, 5 + i);
			}
		}
	}
	manyship(10, 5);
	return 1;
}

int selfdeploy(char battleship[][size])
{
	for (int i = 0; i < 5; i++)
		manyship(0, 5 + i);
	int counter = 0;
	int xDirection = 2;
	int yDirection = 2;
	bool flagchange = false;
	for (int i = 1; i < 5; i++)
	{
		int x = 2;
		int y = 2;
		bool flag = false;
		int Finish = true;
		int good = 0;	
		do
		{		
			if (xDirection != x || yDirection != y || flagchange != flag)
			{
				for (int k = xDirection / 2; k < 10; k++)
				{
					for (int j = yDirection / 2; j < 10; j++)
					{
						gotoxy((k + 1) * 2, (j + 1) * 2);
						if (battleship[k][j] == 2)
						{
							setColor(15, 0); cout << 'X';
						}
						else
						{
							setColor(0, 0); cout << ' ';
						}
					}
				}
			}
			int gran;
			do
			{
				gran = showtime(battleship, x / 2, y / 2, 5 - i, flag);
				if (!flag && gran == 2)
					x -= 2;
				if (flag && gran == 2)
					y -= 2;
			}while(gran != 1);
			xDirection = x;
			yDirection = y;
			flagchange = flag;
			int onetime = keyEnter(&x, &y, 4 - i, &flag);
			if (onetime == 2)
				return 1;
			if (onetime)
			{
				if (showships(battleship, x / 2, y / 2, 5 - i, flag))
				{
					good++;
					counter++;
					manyship(counter, 5);
					manyship(good, 5 + i);
				}
			}		
			if (good != 4)
				showtime(battleship, xDirection/2, yDirection/2, 5 - i, flag, 1);
		} while (good < i);
	}
	return 0;
}

int showtime(char battleship[][size], const int X, const int Y, const int sizechip, const bool orientation, bool cls)
{	
	bool ex = false;
	int counter = 0;
	if (((X <= 10 - sizechip) && (!orientation)) || ((Y <= 10 - sizechip) && orientation))
	{	
		for (int k = 0; k < 2; k++)
		{
			for (int i = counter; i < sizechip; i++)
			{
				orientation ? gotoxy((X + 1) * 2, (Y + i + 1) * 2) : gotoxy((X + i + 1) * 2, (Y + 1) * 2);
				if (cls)
				{
					setColor(0, 0); cout << ' ';
				}
				else
				{
					setColor(15, 0); cout << 'X';
				}
			}
			if (k)
				return 1;
			for (int i = 0; i < sizechip; i++)
			{
				if ((!(battleship[X + i][Y] == 0) || (battleship[X + i][Y] == 4)) && !orientation)
				{
					gotoxy((X + i + 1) * 2, (Y + 1) * 2);
					setColor(12, 0); cout << 'X';
					counter = i + 1;
				}
				if ((!(battleship[X][Y + i] == 0) || (battleship[X][Y + i] == 4)) && orientation)
				{
					gotoxy((X + 1) * 2, (Y + i + 1) * 2);
					setColor(12, 0); cout << 'X';
					counter = i + 1;
				}	
			}
		}
	}
	return 2;
}

int kaput(char battleship[][size], int X, int Y, bool pole)
{
	int good = false;
	int *p;
	if (battleship[X][Y] == 3)
	{
		if ((battleship[X][Y] == 3 || battleship[X][Y] == 2) && (((battleship[X][Y + 1] == 3 || battleship[X][Y + 1] == 2) && Y <9) || ((battleship[X][Y - 1] == 3 || battleship[X][Y - 1] == 2) && Y > 0)))
			p = &Y;
		else
			p = &X;
		while ((*p < 10) && (battleship[X][Y] == 3 || battleship[X][Y] == 2))
		{
			(*p)++;
			good = true;
		}
		if (good)
			(*p)--;
		while ((*p) >= 0 && (battleship[X][Y] == 3 || battleship[X][Y] == 2))
		{
			if (battleship[X][Y] == 2)
				return -1;
			(*p)--;
		}
		++(*p);
		int count = 0;
		while ((*p) < 10 && battleship[X][Y] == 3)
		{
			battleship[X][Y] = 5;
			Sleep(100);
			if (pole)
				gotoxy((22 + (X + 1) * 2), ((Y + 1) * 2));	
			else
				gotoxy(((X + 1) * 2), ((Y + 1) * 2));
			setColor(14, 0); cout << '#';
			touch(battleship, X, Y, 6);
			(*p)++;
			count++;
		}
		return count;
	}
	return -1;
}

int zalpPlayer(char battleship[][10], int *x, int *y, bool *mode, int *countship, bool *autoshow)
{
	bool finish = true;
	do
	{
		gotoxy(*x, *y);
		int code = _getch();
		if (code == 80 && *y < 20) (*y) += 2;
		else if (code == 72 && *y > 2) (*y) -= 2;
		else if (code == 77 && *x < 42) (*x) += 2;
		else if (code == 75 && *x > 24) (*x) -= 2;
		else if (code == 59)
		{
			*autoshow = !(*autoshow);
			show_auto(battleship, *autoshow);
		}
		else if (code == 13)
		{
			finish = false;
		}
		else if (code == 27)
		{
			(*mode) = true;
			return 1;
		}
	} while (finish);

	int Xx = (*x - 24) / 2;
	int Yy = (*y - 2) / 2;
	if (battleship[Xx][Yy] == 3 || battleship[Xx][Yy] == 5 || battleship[Xx][Yy] == 1 || (battleship[Xx][Yy] == 6 && *autoshow))
		return 1;
	if (battleship[Xx][Yy] == 2)
	{
		battleship[Xx][Yy] = 3;
		gotoxy(*x, *y); setColor(12, 0);  cout << '*';
		int counter = kaput(battleship, Xx, Yy, true);
		if (counter > -1)
		{
			show_auto(battleship, *autoshow);
			countship[counter - 1]--;
			manyship(countship[counter - 1], 5 - counter);
			manyship(countship[0] + countship[1] + countship[2] + countship[3], 0);
			if (countship[0] + countship[1] + countship[2] + countship[3] == 0)
			{
				system("cls");
				SetConsoleCP(866);
				gotoxy(34, 11); setColor(10, 0); cout << "ТЫ ПОБЕДИЛ!!!" << endl;
				_getch();
				return 5;
			}
		}
		return 1;
	}
	else if (battleship[Xx][Yy] != 3 && battleship[Xx][Yy] != 5)
	{
		battleship[Xx][Yy] = 1;
		SetConsoleCP(1251);
		gotoxy(*x, *y); setColor(11, 0); cout << (char)248;
	}
	return 0;
}

int AI(char battleship[][size], int X, int Y, int way, int *countship)
{
	int *p;
	way == 0 || way == 1 ? p = &X : p = &Y;
	bool iter;
	way == 0 || way == 2 ? iter = false : iter = true;
	int digit = 0;
	do
	{
		if (battleship[X][Y] == 2)
		{
			Sleep(500);
			battleship[X][Y] = 3;
			gotoxy(((X + 1) * 2), ((Y + 1) * 2));
			setColor(12, 0); cout << '*';			
		}
		int counter = kaput(battleship, X, Y);
		if (counter > -1)
		{
			countship[counter - 1]--;
			manyship(countship[counter - 1], 10 - counter);
			manyship(countship[0] + countship[1] + countship[2] + countship[3], 5);
			if (countship[0] + countship[1] + countship[2] + countship[3] == 0)
			{
				system("cls");
				SetConsoleCP(866);
				gotoxy(34, 11); setColor(10, 0); cout << "ТЫ ПРОИГРАЛ!!!" << endl;
				_getch();
				return 5;
			}
			return 1;
		}
		iter ? (*p)++ : (*p)--;
		digit++;
		if (*p < 0 || (battleship[X][Y] == 1 && !iter))
		{	
			iter = true;
			(*p) += (digit + 1);

		}
		else if (*p > 9 || (battleship[X][Y] == 1 && iter))
		{
			iter = false;
			(*p) -= (digit + 1);		
		}
	} while (battleship[X][Y] == 2);
	battleship[X][Y] = 1;
	Sleep(500);
	gotoxy(((X + 1) * 2), ((Y + 1) * 2));
	setColor(11, 0); cout << (char)248;
	if (digit > 1)
		return 0;
	else
		return -1;
}

int zalpComp(char battleship[][size], int *X, int *Y, int hard, bool *hit, int *Abulo, int *nea, int *countship)
{
	int presidion  = 0;
	while (true)
	{
		int anti_bag = 0;
		if (*hit)
		{	
			switch (hard)
			{
			case 1: presidion = rand() % 5; break;
			case 2: presidion = rand() % 20; break;
			case 3: presidion = rand() % 100; break;
			}
			do
			{
				Abulo[0] = 0; Abulo[1] = 0; Abulo[2] = 0; Abulo[3] = 0;
				*X = rand() % 10;
				*Y = rand() % 10;
			} while (!((battleship[*X][*Y] == 2 || battleship[*X][*Y] == 4 || battleship[*X][*Y] == 0) && (presidion != 0 || (battleship[*X][*Y] == 2 && presidion == 0))));
		}
		if (battleship[*X][*Y] == 2 || battleship[*X][*Y] == 3)
		{
			do
			{
				if (*nea == -1)
					*nea = rand() % 4;
				if (*nea == 0 && Abulo[*nea] == 0 && *X > 0 && (battleship[*X - 1][*Y] == 2 || battleship[*X - 1][*Y] == 4 || battleship[*X - 1][*Y] == 0))
					Abulo[*nea]++;
				else if (*nea == 1 && Abulo[*nea] == 0 && *X < 9 && (battleship[*X + 1][*Y] == 2 || battleship[*X + 1][*Y] == 4 || battleship[*X + 1][*Y] == 0))
					Abulo[*nea]++;
				else if (*nea == 2 && Abulo[*nea] == 0 && *Y > 0 && (battleship[*X][*Y - 1] == 2 || battleship[*X][*Y - 1] == 4 || battleship[*X][*Y - 1] == 0))
					Abulo[*nea]++;
				else if (*nea == 3 && Abulo[*nea] == 0 && *Y < 9 && (battleship[*X][*Y + 1] == 2 || battleship[*X][*Y + 1] == 4 || battleship[*X][*Y + 1] == 0))
					Abulo[*nea]++;
				else
					*nea = -1;
				anti_bag++;
				if (anti_bag > 100)
					*nea = rand() % 4;
				if (countship[1] + countship[2] + countship[3] == 0)
					break;
			} while (*nea == -1);
			int value = AI(battleship, *X, *Y, *nea, countship);
			if (value == 5)
				return 5;
			if (value == 3)
				return 3;
			if (value == 0 && *nea % 2)
				(*nea)--;
			else if (value == 0 && !(*nea % 2))
				(*nea)++;
			if (value == -1)
				*nea = -1;
			if (value == 1 && !(*hit))
			{
				(*hit) = true;
			}
			else if (value == 0 || value == -1)
			{
				(*hit) = false;
				return 0;
			}
		}
		else 
		{
			battleship[*X][*Y] = 1;
			gotoxy((((*X) + 1) * 2), (((*Y) + 1) * 2));
			setColor(11, 0); cout << (char)248;
			return 0;
		}
	}
	return 0;
}

int deployship(char battleship[][size], int countship[][4], int deploy)
{
	if (deploy == 1)
	{
		system("cls");
		gotoxy(30, 10); setColor(15, 0); cout << "Расставка кораблей" << endl;
		for (int i = 1; i <= 100; i++)
		{
			gotoxy(64, 15);
			setColor(15, 0); cout << i << "%";
			if (i % 2 == 0)
			{
				gotoxy(12 + (i / 2), 15);
				setColor(0, 15); cout << ' ';
			}Sleep(5);
		}
		setColor(15, 0);
		showbattleship(countship[0], countship[1]);
		positionship(battleship);
	}
	if (deploy == 2)
	{
		showbattleship(countship[0], countship[1]);
		info_control("Поворот - Space");
		if (selfdeploy(battleship) == 1)
			return 0;
	}
	return 1;
}
