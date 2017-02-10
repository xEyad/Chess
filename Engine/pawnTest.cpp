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
	Vec2I newLocation(pawn.Locate().x - 1, pawn.Locate().y);
	pawn.MoveTo(newLocation);
}

void pawnTest::moveTwoUp()
{
	pawn.MoveTo(Vec2I(pawn.Locate().x - 2, pawn.Locate().y));
}

void pawnTest::moveOneDown()
{
	pawn.MoveTo(Vec2I(pawn.Locate().x + 1, pawn.Locate().y));
}

void pawnTest::moveTwoDown()
{
	pawn.MoveTo(Vec2I(pawn.Locate().x + 2, pawn.Locate().y));
}

void pawnTest::moveRight(int n = 1)
{
	pawn.MoveTo(Vec2I(pawn.Locate().x, pawn.Locate().y + n));
}

void pawnTest::moveLeft(int n = -1)
{
	pawn.MoveTo(Vec2I(pawn.Locate().x + 2, pawn.Locate().y - n));
}
