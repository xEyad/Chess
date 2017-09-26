#include "Queen.h"
Queen::Queen(Vec2I location, Team team, Board* const board)
	:
	Piece(location, team, QUEEN, board)
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

int Queen::HowManyLeft() const
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

bool Queen::IsValidLocation(Vec2I newLocation) const
{
	return QueenLeg(curLocation, enemyTeam, *board).IsValidLocation(newLocation);	
}




void Queen::GenerateValidMoves()
{
	if (captured)
		return;
	validTiles.clear();
	//rook
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

	//bishop
	//x increases
	for (int upY = curLocation.y, downY = upY, x = curLocation.x; x < board->rows; x++, upY--, downY++)
	{
		if (IsValidLocation({ x,upY }))
			validTiles.push_back({ x,upY });

		if (IsValidLocation({ x,downY }))
			validTiles.push_back({ x,downY });
	}
	//x decreases
	for (int upY = curLocation.y, downY = upY, x = curLocation.x; x >= 0; x--, upY--, downY++)
	{
		if (IsValidLocation({ x,upY }))
			validTiles.push_back({ x,upY });

		if (IsValidLocation({ x,downY }))
			validTiles.push_back({ x,downY });
	}
}

Queen::~Queen()
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

int Queen::nWhiteLeft = 0;
int Queen::nBlackLeft = 0;

bool Queen::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}