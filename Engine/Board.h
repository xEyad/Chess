#pragma once
#include "Colors.h"
#include "Vec2.h"
#include <memory>
#include <assert.h>
#include "Graphics.h"
#include "ChiliWin.h"
#include "GlobalEnums.h"
class Piece;

//it is responsiblity is managing its own tiles and which tile contain what
class Board
{
public:
	class Tile
	{
	private:
		struct Status
		{
			bool containPiece = false; 
			GlobalEnums::pieceType piecetype = GlobalEnums::pieceType::NOT_DEFINED;
			GlobalEnums::Team pieceTeam = GlobalEnums::Team::INVALID; //should be deleted
		};
	public:
		Status CurState()
		{
			return curState;
		}
	private:
		Tile(Vec2I location, Color c)
			:
			color(c),
			location(location)
		{}
		void ApplyChanges(bool containPiece, GlobalEnums::pieceType piecetype, GlobalEnums::Team team)
		{
			//backup this state
			prevState.containPiece = curState.containPiece;
			prevState.piecetype = curState.piecetype;
			prevState.pieceTeam = curState.pieceTeam;
			//apply changes
			curState.containPiece = containPiece;
			curState.piecetype = piecetype;
			curState.pieceTeam = team;
		}
		void UndoChanges()
		{
			curState.containPiece = prevState.containPiece;
			curState.piecetype = prevState.piecetype;
			curState.pieceTeam = prevState.pieceTeam;
		}
		void Reset()
		{
			ApplyChanges(false, GlobalEnums::pieceType::NOT_DEFINED, GlobalEnums::Team::INVALID);
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
	
	
public:
	Board(int rows, int columns);
	Board(Board& board);
	void copy(Board& rhs) //used only in loading
	{
		if (rhs.rows == rows && rhs.columns == columns)
		{
			ResetAllTiles();
			boardTiles.clear();
			boardTiles = rhs.boardTiles;
		}
	}

	
	//getters
	const std::vector<std::shared_ptr<Tile>>* GetAllTiles() const
	{
		return &boardTiles;
	}
	std::shared_ptr<Tile> GetTile(Vec2I location) const; 
	std::shared_ptr<Tile> GetTileByMouse(Vec2I gridTopLeft, Vec2I mousePos) const;
	const Tile::Status GetTileState(Vec2I location) const;	
	bool IsInsideTheBoard(Vec2I location) const;

	//actions
	void ResetAllTiles();
	void ResetTile(Vec2I TileLocation);
	void PutPieceOnTile(Vec2I TileLocation, std::shared_ptr<Piece> piece);

	
	Board& operator=(const Board& board) = delete;
	Board& operator=(Board&& board) = delete;
private:
	std::vector<std::shared_ptr<Tile>> boardTiles; //array of shared pointers of type Tile 
public:
	const int rows; 
	const int columns;
};

