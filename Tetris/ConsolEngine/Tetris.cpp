
#include "Tetris.h"

Tetris::Tetris() : Parent(30, 25)
{
	srand((unsigned int)time(0));
	mWidth = 15;
	mHeight = 20;
	mTimer = 0.0f;
	mSpeed = 0.5f;

	mWell = new char*[mHeight];
	for (int i = 0; i < mHeight; i++)
		mWell[i] = new char[mWidth];

	for (int i = 0; i < mWidth; i++)
		for (int j = 0; j < mHeight; j++)
			mWell[i][j] = '.';

	DrawWell();

	mRandom = rand() % 7;
	mTetrimino = new Tetromino(static_cast<Tetromino::Name>(mRandom), mWidth / 2, 0);
	mTetriminoOld = new Tetromino(static_cast<Tetromino::Name>(mRandom), mWidth / 2, 0);
	
	mRandom = rand() % 7;
	mNextTetrimino = new Tetromino(static_cast<Tetromino::Name>(mRandom), mWidth + 3 , 1);
	DrawTetramino(*mNextTetrimino, '*');
	
}

void Tetris::KeyPressed(int btnCode)
{
	if (btnCode == 80)
		mSpeed = 0.02f;
	else if (btnCode == 75 && IsCollision(*mTetrimino, -1, 0))
		mTetrimino->Move(-1, 0);
	else if (btnCode == 77 && IsCollision(*mTetrimino, 1, 0))
		mTetrimino->Move(1, 0);
	else if (btnCode == 32 && IsCollision(*mTetrimino, 0, 0)) 
		mTetrimino->Rotate();
}

void Tetris::UpdateF(float deltaTime)
{
	DrawTetramino(*mTetriminoOld,'.');
	DrawTetramino(*mTetrimino,'*');
	*mTetriminoOld = *mTetrimino;

	mTimer += deltaTime;
	if (mTimer > mSpeed)
	{
		if (IsCollision(*mTetrimino, 0, 1)) {
			mTetrimino->Move(0, 1);
			mTimer = 0.0f;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (mTetrimino->Map(i, j))
						mWell[mTetrimino->GetX() + i - 1][mTetrimino->GetY() + j - 1] = L'*';
				}
			}
			delete mTetrimino;
			mTetrimino = new Tetromino(static_cast<Tetromino::Name>(mRandom), mWidth / 2, 0);
			*mTetriminoOld = *mTetrimino;
			mRandom = rand() % 7;

			if (!IsCollision(*mTetrimino, 0, 1))
			{
				for (int i = 0; i < mWidth; i++)
				{
					for (int j = 0; j < mHeight; j++)
					{
						mWell[i][j] = '.';
						SetChar(i + 1, j + 1, mWell[i][j]);
					}
				}
			}

			DrawTetramino(*mNextTetrimino, '.');		
			delete mNextTetrimino;
			mNextTetrimino = new Tetromino(static_cast<Tetromino::Name>(mRandom), mWidth + 3, 1);
			DrawTetramino(*mNextTetrimino, '*');

			mSpeed = 0.5f;
			RomoveSolidLines();
		}

	}
}

bool Tetris::IsCollision(Tetromino t, int dx, int dy)const
{
	if (dx == 0 && dy == 0)
		t.Rotate();
	else
		t.Move(dx, dy);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (t.Map(i, j) && (j + t.GetY() == (mHeight + 1) || j + t.GetY() == 0 ||
				i + t.GetX() <= 0 || i + t.GetX() == (mWidth + 1)||
				mWell[i + t.GetX() - 1][j + t.GetY() - 1] == '*'))
				return false;
		}
	}
	return true;
}

void Tetris::RomoveSolidLines()
{
	for (int i = 0; i < mHeight; i++)
	{
		int sum = 0;
		for (int j = 0; j < mWidth; j++)
		{
			if (mWell[j][i] == '*')
				sum++;
		}
		if (sum == mWidth)
		{
			for (int k = i; k > 0; k--)
			{
				for (int j = 0; j < mWidth; j++)
				{
					mWell[j][k] = mWell[j][k - 1];
				}
			}
			for (int i = 0; i < mWidth; i++)
			{
				for (int j = 0; j < mHeight; j++)
				{
					SetChar(i + 1, j + 1, mWell[i][j]);
				}
			}


		}
	}
}

void Tetris::DrawWell()
{
	for (int i = 0; i < mWidth + 2; i++)
	{
		for (int j = 0; j < mHeight + 2; j++)
		{
			if (i == 0 || j == 0 || i == mWidth + 1 || j == mHeight + 1)
				SetChar(i, j, L'#');
			else
				SetChar(i, j, L'.');
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == 0 || j == 0 || i == 7 || j == 5)
				SetChar(mWidth + i + 1, j, L'#');
			else
				SetChar(mWidth + i + 1, j, L'.');
		}
	}
}

void Tetris::DrawTetramino(Tetromino &t, char c)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (t.Map(i, j))
				SetChar(t.GetX() + i, t.GetY() + j, c);
		}
	}
}

Tetris::~Tetris() {
	for (int i = 0; i < mHeight; i++)
		delete[] mWell[i];
	delete[] mWell;

	delete mTetrimino;
	delete mTetriminoOld;
	delete mNextTetrimino;
}
