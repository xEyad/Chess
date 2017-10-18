#pragma once
#include <random>
#include "GameDirector.h"
#include "Graphics.h"
#include "BoardPainter.h"
#include "PiecesPainter.h"
#include "ScreenPainter.h"
#include "WhitePromotionScreen.h"
#include "BlackPromotionScreen.h"
#include "InteractionHandler.h"
#include "StartMenu.h"
#include "OptionsMenu.h"
#include "GameOver.h"
#include "IOManger.h"
//responsible for drawing(rendering) and connecting between major classes
class GameManager
{
	enum class UserStates
	{
		startMenu,
		optionsMenu,
		gameOver,
		playing,
		exiting
	};
public:
	GameManager(Graphics& gfx, Mouse& mouse, Keyboard& kbd);
	~GameManager();
	void DrawGameScreen();
	bool HandleInput(); //screens input, false = QUIT
	void LoadGameState(GameState newState);
	GameState GetGameState();
	void SetCheatingMode(bool cheating);
private:
	void DrawGameplayScreens();
	void DrawStage();
	void ProcessEvents();
	void PromotionModeStart(bool whitePromotion);
	void PromotionModeEnd();
	void DrawTurn(Color clr); 
	void HandleGameplayInput(); //only input related to pieces and moving etc..
	Color CurrentHighlight() const;
	GlobalEnums::Team WhoseTurn() const;
private:
	Graphics& gfx;
	Mouse& mouse;
	Keyboard& kbd;
	IOManager ioManager;
	InteractionHandler inputter;
	UserStates userState;
	const TextSurface::Font font;
	Board board; 
	GameDirector director;	
	BoardPainter boardPainter;
	PiecesPainter piecesPainter; 
	ScreenPainter screenPainter;
	Color tileHighlightClr = Colors::Red;
	Color kingThreatHighlight = Colors::Red;
	Color blackPlayerHighlight = Colors::Black;
	Color whitePlayerHighlight = Colors::White;
	const Vec2I gridTopLeft = { 20, 21 };
	RectI feedbackFrame;
	std::shared_ptr<Piece> selectedPiece = nullptr;
	std::shared_ptr<Tile> selectedTile = nullptr;
	std::vector<RectI> pawnPromotionRects;
	int gameTurn = 1; //odd is white's turn 
	std::unique_ptr<GameScreen> pScreen = nullptr;
	Vec2I curScreenTopleft;
	//Flags
	bool kingUnderThreat = false;
	bool whitePromotoinOnGoing = false;
	bool BlackPromotoinOnGoing = false;
	bool promotoinOnGoing = false;
	bool gameOver = false;
	bool cheatMode = false;
};
