#pragma once

class Tetromino
{
public:
	enum Name { I, J, L, O, S, Z, T };
	Tetromino(Name name, int x, int y);
	void Move(int dx, int dy);
	void Rotate();
	bool Map(int x, int y) const;
	int GetX() const { return mX; }
	int GetY() const { return mY; }

private:	
	Name mName;
	int mX;
	int mY;
	char mShare[4][4];
};