#include "Rook.h"
Rook::Rook(Vec2I location, Team team, Board* const board)
	:
	Piece(location, team, ROOK, board)
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

int Rook::HowManyLeft() const
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

bool Rook::IsValidLocation(Vec2I newLocation) const
{
	return RookLeg(curLocation, enemyTeam, *board).IsValidLocation(newLocation);
}


void Rook::GenerateValidMoves()
{
	if (captured)
		return;
	validTiles.clear();
	for (auto x = 0; x < board->rows; x++)
	{
		if (IsValidLocation({ x,curLocation.y }))
			validTiles.push_back({ x,curLocation.y });
	}
	for (auto y = 0; y < board->columns; y++)
	{
		if (IsValidLocation({ curLocation.x,y }))
			validTiles.push_back({ curLocation.x,y });
	}
}

Rook::~Rook()
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

bool Rook::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}


int Rook::nWhiteLeft = 0;
int Rook::nBlackLeft = 0;