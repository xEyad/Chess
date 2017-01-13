#include "pawnTest.h"



pawnTest::pawnTest(Pawn &pawn)
	:
	pawn(pawn)
{
}


pawnTest::~pawnTest()
{
}

void pawnTest::moveOneUp()
{
	Vec2I newLocation(pawn.locate().x - 1, pawn.locate().y);
	pawn.moveTo(newLocation);
}

void pawnTest::moveTwoUp()
{
	pawn.moveTo(Vec2I(pawn.locate().x - 2, pawn.locate().y));
}

void pawnTest::moveOneDown()
{
	pawn.moveTo(Vec2I(pawn.locate().x + 1, pawn.locate().y));
}

void pawnTest::moveTwoDown()
{
	pawn.moveTo(Vec2I(pawn.locate().x + 2, pawn.locate().y));
}

void pawnTest::moveRight(int n = 1)
{
	pawn.moveTo(Vec2I(pawn.locate().x, pawn.locate().y + n));
}

void pawnTest::moveLeft(int n = -1)
{
	pawn.moveTo(Vec2I(pawn.locate().x + 2, pawn.locate().y - n));
}
