#pragma once
#include "Colors.h"
#include "Vec2.h"
#include "GameDirector.h" // for Global enums
#include <memory>
#include <assert.h>
#include "Graphics.h"
#include "ChiliWin.h"
class Mouse;
class Piece;

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
			GlobalEnums::Team pieceTeam = GlobalEnums::Team::INVALID;
		};

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
	Board(Board&& board); //move constructor
	Board(Board& board) = delete;
	//getters
	const std::vector<std::shared_ptr<Tile>>* GetAllTiles() const
	{
		return &boardTiles;
	}
	static int GetTileWidth();
	static int GetTileHeight();
	std::shared_ptr<Tile> GetTile(Vec2I location) const; 
	std::shared_ptr<Tile> GetTileByMouse(Vec2I mousePos) const;
	const Tile::Status GetTileState(Vec2I location) const;	
	Vec2I GetTileStartPoint(Vec2I Tilelocation) const;
	bool IsInsideTheBoard(Vec2I location) const;

	//actions
	void ReadChange(Piece* piece,Vec2I oldLocation);
	//used only with UndoMove
	void ReadChange(Piece * piece, Vec2I locationGoingTo, bool Undo); 

	void ResetAllTiles();
	void ResetTile(Vec2I TileLocation);
	void DrawGrid(Graphics &gfx, Color edgesClr, Vec2I topLeft);
	void DrawGrid(Graphics &gfx, Color edgesClr) const;
	void DrawLabels(Graphics &gfx, Color labelsClr) const;
	void DrawSprite( Graphics &gfx) const;
	void HighlightTile(Graphics & gfx, Vec2I mousePos, Color edgesClr) const;
	void HighlightTiles(Graphics & gfx, std::vector<Vec2I> tilesPos, Color edgesClr) const;
	void DrawPiecesSprite(Graphics & gfx) const;
	void DrawPieces(Graphics & gfx) const;
	void IntializeGameDirector(GameDirector &d) 
	{
		assert(director == nullptr); //if it is already intialized, crash.  (if the director = null then everything is OK)
		director = &d;
	}
	
	Board& operator=(const Board& board) = delete;
	Board& operator=(Board&& board) = delete;
	friend GameDirector;
	friend GiveMeTile;
private:
	std::vector<std::shared_ptr<Tile>> boardTiles; //array of shared pointers of type Tile 
	GameDirector* director;
	Vec2I topLeft = { 20,21 }; //top left point that drawing of the board starts at
public:
	const int rows; 
	const int columns;
	const std::vector<std::shared_ptr<Tile>> p = boardTiles;
};
