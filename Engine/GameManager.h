#pragma once
#include <random>
#include "GameDirector.h"
#include "Graphics.h"
#include "BoardPainter.h"
#include "PiecesPainter.h"
#include "ScreenPainter.h"
#include "WhitePromotionScreen.h"
#include "BlackPromotionScreen.h"
//singelton, responsible for drawing(rendering) and connecting between major classes
//handels input 
class GameManager
{
public:
	GameManager(Graphics& gfx, Mouse& mouse);
	~GameManager();
	void ManageDrawing();
	void HandleInput();
	//temp functions (should be deleted)
	GameDirector& Director()
	{
		return director;
	}
private:
	void DrawStage();
	void DrawGameOverScreen(); //should be a subclass of GameScreen
	void ProcessEvents();
	void PromotionModeStart(bool whitePromotion);
	void PromotionModeEnd();
	void DrawWhoseTurn(Color clr); 
	void DrawTurn(Color clr); 

	GlobalEnums::Team WhoseTurn() const;
private:
	Graphics& gfx;
	Mouse& mouse;
	const TextSurface::Font font;
	Board board; //the manager should create it
	GameDirector director;	//the manager should create it
	BoardPainter boardPainter;
	PiecesPainter piecesPainter; 
	ScreenPainter screenPainter;
	Color tileHighlightClr = Colors::Red;
	std::shared_ptr<Piece> selectedPiece = nullptr;
	std::shared_ptr<Tile> selectedTile = nullptr;
	std::vector<RectI> pawnPromotionRects;
	int gameTurn = 1; //odd is white's turn 
	//Flags
	bool kingUnderThreat = false;
	bool whitePromotoinOnGoing = false;
	bool BlackPromotoinOnGoing = false;
	bool promotoinOnGoing = false;
	bool gameOver = false;
};

