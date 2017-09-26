#include "Bishop.h"

Bishop::Bishop(Vec2I location, Team team, Board *const board)
	:
	Piece(location, team, BISHOP, board)
{
	//increment n of pieces
	switch (team)
	{
		case Team::WHITE:
			nWhiteLeft++;
			break;
		case Team::BLACK:
			nBlackLeft++;
			break;
	}
}

int Bishop::HowManyLeft() const
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

bool Bishop::IsValidLocation(Vec2I newLocation) const
{
	return BishopLeg(curLocation, enemyTeam, *board).IsValidLocation(newLocation);
}
bool Bishop::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}


void Bishop::GenerateValidMoves()
{
	if (captured)
		return;
	validTiles.clear();
	//x increases
	for (int upY = curLocation.y, downY = upY,  x = curLocation.x; x < board->rows; x++, upY--,downY++)
	{
		if (IsValidLocation({ x,upY }))
			validTiles.push_back({ x,upY });

		if (IsValidLocation({ x,downY }))
			validTiles.push_back({ x,downY });
	}
	//x decreases
	for (int upY = curLocation.y,  downY = upY,  x = curLocation.x; x >= 0; x--, upY--, downY++)
	{
		if (IsValidLocation({ x,upY }))
			validTiles.push_back({ x,upY });

		if (IsValidLocation({ x,downY }))
			validTiles.push_back({ x,downY });
	}
}

Bishop::~Bishop()
{
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

int Bishop::nWhiteLeft = 0;
int Bishop::nBlackLeft = 0;

