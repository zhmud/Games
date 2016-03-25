#pragma once

#include "BaseApp.h"
#include "Tetromino.h"
#include <ctime>

class Tetris : public BaseApp
{
	typedef BaseApp Parent;

private:
	int mWidth;
	int mHeight;

	Tetromino *mTetrimino;
	Tetromino *mTetriminoOld;
	Tetromino *mNextTetrimino;

	float mSpeed;
	float mTimer;

	int mRandom;

	char **mWell;

public:
	Tetris();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	bool IsCollision(Tetromino t, int dx, int dy)const;
	void RomoveSolidLines();
	void DrawWell();
	void DrawTetramino(Tetromino &t, char c);

	virtual ~Tetris();
};