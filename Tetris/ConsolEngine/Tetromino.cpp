#include "Tetromino.h"

Tetromino::Tetromino(Name name, int x, int y) : mName(name),
												mX(x), mY(y)
{
	static const char *Shares[] =
	{
		"    "//I
		"    "
		"0000"
		"    ",

		"    "//J
		"0   "
		"000 "
		"    ",

		"    "//L
		"  0 "
		"000 "
		"    ",

		"    "//O
		" 00 "
		" 00 "
		"    ",

		"    "//S
		" 00 "
		"00  "
		"    ",

		"    "//Z
		"00  "
		" 00 "
		"    ",

		"    "//T
		" 0  "
		"000 "
		"    ",
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mShare[i][j] = Shares[mName][i + j * 4];
		}
	}
}

void Tetromino::Rotate()
{
	int n = 4;
	char temp[4][4];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			temp[i][j] = mShare[i][j];
		}

	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++) {
			mShare[j][n - i - 1] = temp[i][j];
		}
}

void Tetromino::Move(int dx, int dy)
{
	mX += dx;
	mY += dy;
}

bool Tetromino::Map(int x, int y)const
{
	return mShare[x][y] != ' ';
}
