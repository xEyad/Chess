#pragma once
#include "Tile.h"
#include <memory>
#include "Graphics.h"
class Piece;
class Board
{
public:
	Board(int rows, int columns);
	//getters
	std::shared_ptr<Tile> getTile(Vec2I location) const;
	const Tile::Status getTileState(Vec2I location) const;	
	bool isInsideTheBoard(Vec2I location) const;
	//actions
	void ReadChange(Piece* piece,Vec2I oldLocation);
	void Draw( Graphics &gfx, Vec2I topLeft, Color edgesClr, int widthOfTile = 90, int heightOfTile = 90) const;
	void highlightTile(Graphics & gfx, Vec2I mousePos, Color edgesClr, int widthOfTile = 90, int heightOfTile = 90) const;
	void DrawPieces( Graphics & gfx, Vec2I topLeft, int widthOfTile = 90, int heightOfTile = 90) const;
	void intializeGameDirector(GameDirector &d) { director = &d; }

private:
	std::vector<std::shared_ptr<Tile>> boardTiles; //array of shared pointers of type Tile 
	GameDirector* director;
public:
	const int rows; 
	const int columns;
	const std::vector<std::shared_ptr<Tile>> p = boardTiles;
};
