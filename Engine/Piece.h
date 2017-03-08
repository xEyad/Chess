#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "GameDirector.h"
#include "Board.h"
#include <iostream>
#include <Windows.h>
using namespace GlobalEnums;
//abstract class
class Piece
{
protected:
	Piece(Vec2I location, Team team, pieceType type, Board* const board, Surface* const sprite)
		:
		curLocation(location),
		oldLocation({-1,-1}),
		team(team),
		type(type),
		board(board),
		sprite(sprite)
	{
		if (team == Team::BLACK)
			enemyTeam = Team::WHITE;
		else if (team == Team::WHITE)
			enemyTeam = Team::BLACK;

		ReportChange();

		for (unsigned int x = 0; x < sprite->GetWidth(); x++)
		{
			for (unsigned int y = 0; y < sprite->GetHeight(); y++)
			{
				sprSurf.push_back(sprite->GetPixel(x, y));
			}
		}
		GenerateValidMoves();

	}
	virtual ~Piece(){}

	//getters
	virtual bool IsWayClear(Vec2I newLocation) const = 0; //it checks if the way to the new location (not the newLocation itself) contains other pieces or not
	virtual bool IsWayClear(int newLocation) const = 0;//support	
	inline int TransLocation(Vec2I location) const
	{
		return location.y * board->rows + location.x;
	}
	inline Vec2I TransLocation(int location) const
	{
		//column = location % totalNumberOfColumns    <= X
		//row = (location - column) / totalNumberOfRows    <= Y
		return{ location % board->columns,(location - (location % board->columns)) / board->rows };
	}
	//actions
	virtual void ReportChange() //sends to board a pointer to the changed piece
	{
		board->ReadChange(this, oldLocation);
	}

public:
	//getters
	
	pieceType GetType() const
	{
		return type;
	}
	Team GetTeam() const
	{
		return team;
	}
	Vec2I Locate() const
	{
		return curLocation;
	}	
	const Surface* GetSprite() const
	{
		return sprite;
	}
	const std::vector<Color>* GetSprSurf() const
	{
		return &sprSurf;
	}
	const std::vector<Vec2I>& getValidTiles() const
	{
		return validTiles;
	}
	virtual int HowManyLeft() const = 0; //should return the number of pieces left in this team
	virtual bool IsValidLocation(Vec2I newLocation) const = 0; //original
	virtual bool IsValidLocation(int newLocation) const = 0; //support
	
	//actions
	virtual bool MoveTo(Vec2I newLocation) = 0;//original
	virtual bool MoveTo(int newLocation) = 0;//support
	virtual void GenerateValidMoves() {} // should be pure virtual
	virtual void SendToPrison()
	{
		captured = true;
		oldLocation = curLocation;
		curLocation = Vec2I({ -1,-1 });
	}
	/*struct CapturedPiece
	{
		pieceType type;
		Vec2I vLocation;
		int iLocation;
	};*/

protected:
	const pieceType type = NOT_DEFINED;
	Vec2I curLocation;
	Vec2I oldLocation;
	const Team team;
	Team enemyTeam;
	std::vector<Color> sprSurf;
	std::vector<Vec2I> validTiles;
	bool captured = false; // the piece itself
	//std::vector< CapturedPiece> capturedPieces; //enemy pieces captured by this piece
	Board* const board;
	Surface* const sprite;
};
