#pragma once
#include "Tile.h"
#include <memory>
#include <assert.h>
#include "Graphics.h"
class Mouse;
class Piece;
class Board
{
public:
	Board(int rows, int columns, Surface* const sprite);
	//getters
	std::shared_ptr<Tile> GetTile(Vec2I location) const; 
	std::shared_ptr<Tile> GetTileByMouse(Vec2I mousePos) const;
	const Tile::Status GetTileState(Vec2I location) const;	
	Vec2I GetTileStartPoint(Vec2I Tilelocation) const;
	bool IsInsideTheBoard(Vec2I location) const;

	//actions
	void ReadChange(Piece* piece,Vec2I oldLocation);
	//used only with UndoMove
	void ReadChange(Piece * piece, Vec2I locationGoingTo, bool Undo);
	void DrawGrid(Graphics &gfx, Color edgesClr, Vec2I topLeft);
	void DrawGrid(Graphics &gfx, Color edgesClr) const;
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

private:
	std::vector<std::shared_ptr<Tile>> boardTiles; //array of shared pointers of type Tile 
	GameDirector* director;
	Vec2I topLeft = { 0,0 }; //top left point that drawing of the board starts at
	Surface* const sprite;
	std::vector<Color> sprSurf;
public:
	const int rows; 
	const int columns;
	const std::vector<std::shared_ptr<Tile>> p = boardTiles;
};
