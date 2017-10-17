#pragma once
#include "Painter.h"
#include "Piece.h"
class PiecesPainter :	public Painter
{
public:
	enum class PiecesStyle
	{
		wood,
		stone
	};
public:
	PiecesPainter(Graphics& gfx, const std::vector<std::shared_ptr<Piece>>* pieces);
	~PiecesPainter();

	void DrawPiecesSquares(Vec2I topLeft);
	void DrawPiecesSprites(Vec2I topLeft);
	void ChangeStyleTo(PiecesStyle style);
private:
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

