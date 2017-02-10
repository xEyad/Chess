#pragma once
#include "Tile.h"
#include <memory>
#include "Graphics.h"
class Mouse;
class Piece;
class Board
{
public:
	Board(int rows, int columns);
	//getters
	std::shared_ptr<Tile> GetTile(Vec2I location) const; 
	std::shared_ptr<Tile> GetTileByMouse(Vec2I mousePos) const;
	const Tile::Status GetTileState(Vec2I location) const;	
	bool IsInsideTheBoard(Vec2I location) const;

	//actions
	void ReadChange(Piece* piece,Vec2I oldLocation);
	void Draw(Graphics &gfx, Color edgesClr, Vec2I topLeft);
	void Draw( Graphics &gfx, Color edgesClr) const;
	void HighlightTile(Graphics & gfx, Vec2I mousePos, Color edgesClr) const;
	void DrawPieces(Graphics & gfx) const;
	void IntializeGameDirector(GameDirector &d) { director = &d; }

private:
	std::vector<std::shared_ptr<Tile>> boardTiles; //array of shared pointers of type Tile 
	GameDirector* director;
	Vec2I topLeft = { 40,40 }; //top left point that drawing of the board starts at
public:
	const int rows; 
	const int columns;
	const std::vector<std::shared_ptr<Tile>> p = boardTiles;
};
