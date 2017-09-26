#pragma once
#include "Painter.h"
#include "Piece.h"
class PiecesPainter :	public Painter
{
public:
	PiecesPainter(Graphics& gfx, const std::vector<std::shared_ptr<Piece>>* pieces);
	~PiecesPainter();

	void DrawPiecesSquares(Vec2I topLeft);
	void DrawPiecesSprites(Vec2I topLeft);
	//1-stone, 2-wood
	void DrawPiecesSprites(Vec2I topLeft, int styleNum);
private:
	//1-stone, 2-wood
	void ChangeStyleTo(int styleNum);
	void DeleteSprites();
	Surface* GetSprite(Piece* pPiece);
private:
	const std::vector<std::shared_ptr<Piece>>* pieces;
	Surface* wPawnSpr;
	Surface* wRookSpr;
	Surface* wKnightSpr;
	Surface* wBishopSpr;
	Surface* wQueenSpr;
	Surface* wKingSpr;

	Surface* bPawnSpr;
	Surface* bRookSpr;
	Surface* bKnightSpr;
	Surface* bBishopSpr;
	Surface* bQueenSpr;
	Surface* bKingSpr;
};

