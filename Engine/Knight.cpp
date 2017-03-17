#include "Knight.h"


Knight::Knight(Vec2I location, Team team, Board* const board, Surface* const sprite)
	:
Piece(location, team, KNIGHT, board,sprite)
{
	//increment number of pieces
	switch (team)
	{
		case Team::WHITE:
			nWhiteLeft++;
			break;
		case Team::BLACK:
			nBlackLeft++;
			break;
	}
};

int Knight::HowManyLeft() const
{
	switch (team)
	{
		case Team::WHITE:
			return nWhiteLeft;
			break;
		case Team::BLACK:
			return nBlackLeft;
			break;
		default:
			return -1;
			break;
	}
}

bool Knight::IsValidLocation(Vec2I newLocation) const
{
	if (board->IsInsideTheBoard(newLocation))
	{
		bool notFriendly = board->GetTileState(newLocation).pieceTeam != team;
		int xDiff = abs(newLocation.x - curLocation.x);
		int yDiff = abs(newLocation.y - curLocation.y);

		if (xDiff == 1 && yDiff == 2 && notFriendly)
			return true;
		else if (xDiff == 2 && yDiff == 1 && notFriendly)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Knight::IsWayClear(Vec2I newLocation) const
{
		return false;
}




void Knight::GenerateValidMoves()
{
	validTiles.clear();
	int x = curLocation.x;
	int y = curLocation.y;
	Vec2I p1(x + 2, y - 1);
	Vec2I p2(x + 2, y + 1);
	Vec2I p3(x - 2, y - 1);
	Vec2I p4(x - 2, y + 1);

	Vec2I p5(x + 1, y - 2);
	Vec2I p6(x - 1, y - 2);
	Vec2I p7(x - 1, y + 2);
	Vec2I p8(x + 1, y + 2);

	if (IsValidLocation(p1))
		validTiles.push_back(p1);
	if (IsValidLocation(p2))
		validTiles.push_back(p2);
	if (IsValidLocation(p3))
		validTiles.push_back(p3);
	if (IsValidLocation(p4))
		validTiles.push_back(p4);
	if (IsValidLocation(p5))
		validTiles.push_back(p5);
	if (IsValidLocation(p6))
		validTiles.push_back(p6);
	if (IsValidLocation(p7))
		validTiles.push_back(p7);
	if (IsValidLocation(p8))
		validTiles.push_back(p8);
}

Knight::~Knight()
{//decrement number of pieces
	switch (team)
	{
		case Team::WHITE:
			nWhiteLeft--;
			break;
		case Team::BLACK:
			nBlackLeft--;
			break;
	}
}
int Knight::nWhiteLeft = 0;
int Knight::nBlackLeft = 0;

bool Knight::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}
bool Knight::IsWayClear(int newLocation) const
{
	return IsWayClear(TransLocation(newLocation));
}
