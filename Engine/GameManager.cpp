#include "GameManager.h"

GameManager::GameManager(Graphics& gfx, Mouse& mouse, Keyboard& kbd)
	:
	gfx(gfx),
	mouse(mouse),
	kbd(kbd),
	inputter(mouse, kbd),
	userState(UserStates::startMenu),
	piecesPainter(gfx, director.getPieces()),
	screenPainter(gfx),
	board(8, 8), //basic chess board	
	boardPainter(gfx,board),
	director(board),
	font(L"times", 20.0f),
	feedbackFrame({ gridTopLeft.x ,gridTopLeft.y }, { (int)Graphics::ScreenWidth - gridTopLeft.x ,(int)Graphics::ScreenHeight - gridTopLeft.y + 2 })
{		
	boardPainter.ChangeSpriteTo(BoardPainter::BoardSprites::StoneBlue);
	piecesPainter.ChangeStyleTo(PiecesPainter::PiecesStyle::stone);
	//mo2ktn el 2byd makano ta7t daymn	
}


GameManager::~GameManager()
{
}

//draws appropriate screens in approrpiate times
void GameManager::DrawGameScreen()
{
	switch (userState)
	{
		case GameManager::UserStates::startMenu:
			pScreen = std::make_unique<StartMenu>(StartMenu()); 
			curScreenTopleft = Vec2I( 0,0 );
			screenPainter.DrawScreenWithHighlights(*pScreen, curScreenTopleft ,mouse.GetPos());
			break;

		case GameManager::UserStates::optionsMenu:
			pScreen = std::make_unique<OptionsMenu>(OptionsMenu(&font));
			curScreenTopleft = Vec2I(0, 0);
			screenPainter.DrawScreenWithHighlights(*pScreen, curScreenTopleft, mouse.GetPos());
			break;

		case GameManager::UserStates::gameOver:
			DrawGameplayScreens();
			pScreen = std::make_unique<GameOver>(GameOver(&font));
			curScreenTopleft = Vec2I(0, 0);
			screenPainter.DrawScreen(*pScreen, curScreenTopleft);
			break;

		case GameManager::UserStates::playing:
			pScreen = nullptr;
			curScreenTopleft = gridTopLeft;
			DrawGameplayScreens();
			break;

		default:
			break;
	}
}

bool GameManager::HandleInput()
{
	if (pScreen != nullptr)
	{
		auto btnName = inputter.HandleMouseInput(*pScreen, curScreenTopleft);

		//handle based on what screen is running ----- Use functors------
		if (userState == UserStates::startMenu)
		{
			if (btnName == "playBtn")
				userState = UserStates::playing;
			else if (btnName == "optBtn")
				userState = UserStates::optionsMenu;
			else if (btnName == "exitBtn")
				return false; //exit the program
		}

		else if (userState == UserStates::optionsMenu)
		{
			if (btnName == "stoneGreyBtn")
			{
				boardPainter.ChangeSpriteTo(BoardPainter::BoardSprites::StoneGrey);
				piecesPainter.ChangeStyleTo(PiecesPainter::PiecesStyle::stone);
				userState = UserStates::startMenu;
			}
			if (btnName == "stoneBlueBtn")
			{
				boardPainter.ChangeSpriteTo(BoardPainter::BoardSprites::StoneBlue);
				piecesPainter.ChangeStyleTo(PiecesPainter::PiecesStyle::stone);
				userState = UserStates::startMenu;
			}
			if (btnName == "stoneBlackBtn")
			{
				boardPainter.ChangeSpriteTo(BoardPainter::BoardSprites::StoneBlack);
				piecesPainter.ChangeStyleTo(PiecesPainter::PiecesStyle::stone);
				userState = UserStates::startMenu;
			}
			if (btnName == "woodBtn")
			{		
				boardPainter.ChangeSpriteTo(BoardPainter::BoardSprites::Wood);
				piecesPainter.ChangeStyleTo(PiecesPainter::PiecesStyle::wood);
				userState = UserStates::startMenu;
			}
			if (btnName == "backBtn")
				userState = UserStates::startMenu;
		}

	}
	else // userState = playing
	{
		switch (kbd.ReadKey().GetCode())
		{
			case VK_F1:
				ioManager.QuickSaveGame(GetGameState());
				break;
			case VK_F2:
				LoadGameState(ioManager.QuickLoadGame());
				break;
			case VK_ESCAPE:
				userState = UserStates::startMenu;
				return true;
			default:
				break;
		}
		HandleGameplayInput();
	}

	return true;
}

void GameManager::DrawGameplayScreens()
{
	DrawStage();
	
	if (BlackPromotoinOnGoing)
	{
		static BlackPromotionScreen bps;
		Vec2I topLeft = { 20 + Board::Tile::WIDTH * 2, 20 + Board::Tile::HEIGHT * 4 + 1 };
		screenPainter.DrawScreen(bps, topLeft);
		for each (auto mpdBtn in bps.MappedButtons())
		{
			pawnPromotionRects.push_back(mpdBtn.GetBoundingBox(topLeft));
		}
	}

	if (whitePromotoinOnGoing)
	{
		static WhitePromotionScreen wps;
		Vec2I topLeft = { 20 + Board::Tile::WIDTH * 2 ,20 + Board::Tile::HEIGHT * 3 + 1 };
		screenPainter.DrawScreen(wps, topLeft);
		for each (auto mpdBtn in wps.MappedButtons())
		{
			pawnPromotionRects.push_back(mpdBtn.GetBoundingBox(topLeft));
		}
	}
}

void GameManager::HandleGameplayInput()
{
	ProcessEvents();
	static int clickCounter = 0;
	static std::shared_ptr<Board::Tile> t1, t2;

	if (promotoinOnGoing)
	{
		const Mouse::Event e = mouse.Read();
		if (e.GetType() == Mouse::Event::LPress)
		{
			int loopCounter = 0;
			for each (auto rec in pawnPromotionRects)
			{
				//coloring comes later
				//screenPainter.SetButtonsEdgeClr(Colors::Red);
				if (rec.Contains(mouse.GetPos()))
				{					
					switch (loopCounter)
					{
						case 0:
							director.PromoteTo(ROOK);
							PromotionModeEnd();
							break;
						case 1:
							director.PromoteTo(KNIGHT);
							PromotionModeEnd();
							break;
						case 2:
							director.PromoteTo(BISHOP);
							PromotionModeEnd();
							break;
						case 3:
							director.PromoteTo(QUEEN);
							PromotionModeEnd();
							break;
					}
				}
				loopCounter++;
			}
		}
	}
	else 
	{
		const Mouse::Event e = mouse.Read();
		if (e.GetType() == Mouse::Event::LPress) //update counter on left click
		{
			if (clickCounter == 0) //first click
			{

				t1 = board.GetTileByMouse(gridTopLeft, mouse.GetPos()); //click 1 (get its coordinates)
				if(t1 != nullptr)
					selectedPiece = director.getPiece(t1->location);
				if (selectedPiece)
				{
					clickCounter++;
					tileHighlightClr = Colors::Magenta;
				}
			}
			else if (clickCounter >= 1)
			{
				clickCounter = 0; //reset (cause this means he already made a choice!)			

				tileHighlightClr = Colors::Red;

				t2 = board.GetTileByMouse(gridTopLeft, mouse.GetPos()); //click 2 (get its coordinates)
				if (t1 != nullptr && t2 != nullptr) //if the 2 clicks locations are valid
				{
					if (cheatMode)
						director.HandleInputCheatMode(t1->location, t2->location, WhoseTurn(), gameTurn);
					else
						director.HandleInput(t1->location, t2->location,WhoseTurn(),gameTurn);

					selectedPiece = nullptr;
				}
			}
		}
	}
}

Color GameManager::CurrentHighlight() const
{
	if (kingUnderThreat)
		return kingThreatHighlight;
	else if (WhoseTurn() == Team::BLACK)
		return blackPlayerHighlight;
	else if (WhoseTurn() == Team::WHITE)
		return whitePlayerHighlight;
	else
		return Colors::Green;
}

void GameManager::LoadGameState(GameState newState)
{
	board.copy(*(newState.board)); // use the conversion operator
	gameTurn = newState.turn;
	director.ChangeGamePieces(newState.pieces);	
}

GameState GameManager::GetGameState()
{
	GameState currentState;
	currentState.board = std::make_shared<Board>(board);
	currentState.turn = gameTurn;
	currentState.pieces = *(director.getPieces());
	return currentState;
}

void GameManager::SetCheatingMode(bool cheating)
{
	cheatMode = cheating;
}

void GameManager::DrawStage()
{
#if _DEBUG // DEBUG mode
	piecesPainter.DrawPiecesSquares(gridTopLeft);
#else //release mode
	boardPainter.DrawSprite();
	piecesPainter.DrawPiecesSprites(gridTopLeft);
#endif 
	
	//boardPainter.DrawLabels(gridTopLeft, Colors::White);
	boardPainter.DrawGrid(gridTopLeft, CurrentHighlight());
	
	if (selectedPiece)
	{
		auto p = selectedPiece->getValidTiles();
		boardPainter.HighlightTiles(gridTopLeft, p, Colors::Orange);
	}
	boardPainter.HighlightTile(gridTopLeft, mouse.GetPos(), tileHighlightClr); //re check color
	//DrawTurn(Colors::Orange);	
}

void GameManager::ProcessEvents()
{
	while (director.IsThereEvents()) 
	{
		switch (director.ReadEvent())
		{
			case GameDirector::DirectorEvent::TurnPassed:
				gameTurn++;
				break;
			case GameDirector::DirectorEvent::KingUnderThreat:
				kingUnderThreat = true;
				break;
			case GameDirector::DirectorEvent::KingIsSafe:
				kingUnderThreat = false;
				break;
			case GameDirector::DirectorEvent::EnterBlackPromotion:
				PromotionModeStart(false);
				break;
			case GameDirector::DirectorEvent::EnterWhitePromotion:
				PromotionModeStart(true);
				break;
			case GameDirector::DirectorEvent::GameOver:
				gameOver = true;
				userState = UserStates::gameOver;
				break;
			default:
				break;
		}
	}
}

void GameManager::PromotionModeStart(bool whitePromotion)
{
	whitePromotoinOnGoing = whitePromotion;
	BlackPromotoinOnGoing = !whitePromotion;
	promotoinOnGoing = true;
}

void GameManager::PromotionModeEnd()
{
	whitePromotoinOnGoing = false;
	BlackPromotoinOnGoing = false;
	promotoinOnGoing = false;
}

void GameManager::DrawTurn(Color clr)
{
	std::wstring turnNumber = std::wstring(L"Turn ") + std::to_wstring(gameTurn);
	gfx.DrawText(turnNumber, { 0.0f,0.0f }, font, clr );
}

GlobalEnums::Team GameManager::WhoseTurn() const
{
	if (gameTurn % 2 == 0) //even
		return GlobalEnums::Team::BLACK;
	else //odd
		return GlobalEnums::Team::WHITE;
}


