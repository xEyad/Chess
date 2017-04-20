#pragma once
#include "Colors.h"
#include "Vec2.h"
#include "GameDirector.h" // for Global enums


using namespace GlobalEnums;
class Tile
{
private:
	struct Status
	{		
		bool containPiece = false;
		pieceType piecetype = pieceType::NOT_DEFINED;
		Team pieceTeam = Team::INVALID;
	};

private:
	Tile(Vec2I location, Color c)
		:
		color(c),
		location(location)
	{}
	void ApplyChanges(bool containPiece, pieceType piecetype, Team team)
	{
		//backup this state
		prevState.containPiece	=	curState.containPiece;
		prevState.piecetype		=	curState.piecetype;
		prevState.pieceTeam		=	curState.pieceTeam;
		//apply changes
		curState.containPiece = containPiece;
		curState.piecetype = piecetype;
		curState.pieceTeam = team;
	}
	void UndoChanges()
	{
		curState.containPiece	= prevState.containPiece;
		curState.piecetype = prevState.piecetype;
		curState.pieceTeam = prevState.pieceTeam;
	}
	void Reset()
	{
		ApplyChanges(false, pieceType::NOT_DEFINED, Team::INVALID);
	}
public:
	const Color color;
	const Vec2I location;

	const static int HEIGHT; //Graphical value
	const static int WIDTH; //Graphical value

private:
	friend class Board;
	Status curState;
	Status prevState;

};

