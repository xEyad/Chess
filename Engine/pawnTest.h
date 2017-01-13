#pragma once
#include "Pawn.h"
class pawnTest
{
public:
	pawnTest(Pawn &pawn);
	~pawnTest();

	void moveOneUp();
	void moveTwoUp();
	void moveOneDown();
	void moveTwoDown();
	void moveRight(int n);
	void moveLeft(int n);
private:
	Pawn &pawn;
};

