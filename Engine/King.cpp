#include "King.h"
King::King(Vec2I location, Team team, Board* const board)
	:
	Piece(location, team, KING, board)
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


int King::HowManyLeft() const
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

bool King::IsValidLocation(Vec2I newLocation) const
{
	return KingLeg(curLocation, enemyTeam, *board).IsValidLocation(newLocation);
}
bool King::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}



void King::GenerateValidMoves()
{
	validTiles.clear();
	for (int y = curLocation.y - 1; y <= curLocation.y + 1; y++)
	{
		for (int x = curLocation.x - 1; x <= curLocation.x + 1; x++)
		{
			if (IsValidLocation({ x,y }))
				validTiles.push_back({ x,y });
		}
	}
}

King::~King()
{
	//decrement number of pieces
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
int King::nWhiteLeft = 0;
int King::nBlackLeft = 0;
