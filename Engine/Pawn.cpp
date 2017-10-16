#include "Pawn.h"
Pawn::Pawn(Vec2I location, Team team, Board *const board, int nStepsMoved)
	:
	Piece(location, team, PAWN, board),
	stepsCounter(nStepsMoved)
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


int Pawn::HowManyLeft() const
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

bool Pawn::IsValidLocation(Vec2I newLocation) const
{
	if (team == Team::BLACK && curLocation.y > newLocation.y)		//black and tries to move up
		return false;

	else if (team == Team::WHITE && curLocation.y < newLocation.y)	//white and tries to move down
		return false;
	else 													//other than that... then its a valid logical move
	{
		auto tile = board->GetTileState(newLocation);
		int yDiff = abs(curLocation.y - newLocation.y);
		int xDiff = abs(curLocation.x - newLocation.x);
		if (!movedBefore && IsWayClear(newLocation) && yDiff <= 2 && !tile.containPiece)	// can do 2 vertical moves 
			return true;

		else if (IsWayClear(newLocation) && yDiff == 1 && !tile.containPiece) //basically 1 vertical move
			return true;

		else if (yDiff == 1 && xDiff == 1 &&  tile.containPiece &&tile.pieceTeam != team) //eating(capturing) case
		{
			return true;
		}
		else
			return false;
	}
	
}

bool Pawn::IsWayClear(Vec2I newLocation) const
{
	if (board->IsInsideTheBoard(newLocation) && newLocation.x == curLocation.x)
	{
		int judge;
		for (int i = min(newLocation.y, curLocation.y); i <= max(newLocation.y, curLocation.y) -1; i++)
		{//start from the lowest to bigger. checks if any of those tiles have a piece on it
			if (Vec2I(curLocation.x, i) == curLocation)
				judge = 1;
			else
				judge = 0;

			if (board->GetTileState(Vec2I(curLocation.x, i + judge)).containPiece)
				return false;
		}
		//if we get out of the loop then the way is clear
		return true;
	}
	else
		return false;
}

void Pawn::CopyThisTurn()
{
	lastTurn.stepsCounter = this->stepsCounter;
	lastTurn.curLocation = this->curLocation;
	lastTurn.oldLocation = this->oldLocation;
	lastTurn.captured = this->captured;
	lastTurn.movedBefore = this->movedBefore;
}

bool Pawn::MoveTo(Vec2I newLocation)
{
	if (IsValidLocation(newLocation))
	{
		CopyThisTurn();
		stepsCounter += abs(newLocation.y - curLocation.y);
		oldLocation = curLocation;
		curLocation = newLocation;		
		if (stepsCounter >= 6 )
			transformed = true;
		movedBefore = true;	
		return true;
	}
	else
		return false;
}

void Pawn::UndoMove()
{
	Vec2I locationGoingTo = curLocation; //this is the location which the piece will leave empty, Board needs to know it
	stepsCounter = lastTurn.stepsCounter;
	curLocation = lastTurn.curLocation;
	oldLocation = lastTurn.oldLocation;
	captured = lastTurn.captured;
	movedBefore = lastTurn.movedBefore;
}

void Pawn::GenerateValidMoves()
{
	if (captured)
		return;
	validTiles.clear();
	if (team == Team::BLACK)
	{
		Vec2I p1(curLocation.x, curLocation.y + 1);
		Vec2I p2(curLocation.x, curLocation.y + 2);
		Vec2I p3(curLocation.x + 1, curLocation.y + 1);
		Vec2I p4(curLocation.x - 1, curLocation.y + 1);

		if (IsValidLocation(p1))
			validTiles.push_back(p1);
		if (IsValidLocation(p2))
			validTiles.push_back(p2);
		if (IsValidLocation(p3))
			validTiles.push_back(p3);
		if (IsValidLocation(p4))
			validTiles.push_back(p4);
	}
	else if (team == Team::WHITE)
	{
		Vec2I p1(curLocation.x, curLocation.y - 1);
		Vec2I p2(curLocation.x, curLocation.y - 2);
		Vec2I p3(curLocation.x + 1, curLocation.y - 1);
		Vec2I p4(curLocation.x - 1, curLocation.y - 1);

		if (IsValidLocation(p1))
			validTiles.push_back(p1);
		if (IsValidLocation(p2))
			validTiles.push_back(p2);
		if (IsValidLocation(p3))
			validTiles.push_back(p3);
		if (IsValidLocation(p4))
			validTiles.push_back(p4);
	}
}

Pawn::~Pawn()
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


bool Pawn::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}
bool Pawn::IsWayClear(int newLocation) const
{
	return IsWayClear(TransLocation(newLocation));
}


//static variables should be intialized like this, in the def file!
int Pawn::nWhiteLeft = 0;
int Pawn::nBlackLeft = 0;