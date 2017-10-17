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
	font(L"times", 20.0f)
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
		case GameManager::UserStates::paused:
			break;
		case GameManager::UserStates::playing:
			pScreen = nullptr;
			DrawGameplayScreens();
			break;
		case GameManager::UserStates::exiting:
			//kill Message
			break;
		default:
			break;
	}
}

void GameManager::HandleInput()
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
				userState = UserStates::exiting;
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
	else
		HandleGameplayInput();
}

void GameManager::DrawGameplayScreens()
{
	DrawStage();

	if(kingUnderThreat)
		gfx.DrawText(L"King is under Threat", { Graphics::ScreenWidth / 2 - 80.0f,0.0f }, font, Colors::Green);

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

	if (gameOver)
		DrawGameOverScreen();
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
					director.HandleInput(t1->location, t2->location,WhoseTurn(),gameTurn);
					selectedPiece = nullptr;
				}
			}
		}
	}
}

void GameManager::LoadGameState(GameState newState)
{
	board(*(newState.board)); // use the conversion operator	
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

void GameManager::DrawStage()
{
#if _DEBUG // DEBUG mode
	piecesPainter.DrawPiecesSquares(gridTopLeft);
#else //release mode
	boardPainter.DrawSprite();
	piecesPainter.DrawPiecesSprites(gridTopLeft);
#endif 
			
	boardPainter.DrawLabels(gridTopLeft, Colors::White);
	boardPainter.DrawGrid(gridTopLeft, Colors::LightGray);
	
	if (selectedPiece)
	{
		auto p = selectedPiece->getValidTiles();
		boardPainter.HighlightTiles(gridTopLeft, p, Colors::Orange);
	}
	boardPainter.HighlightTile(gridTopLeft, mouse.GetPos(), tileHighlightClr); //re check color
	DrawWhoseTurn(Colors::Green);
	DrawTurn(Colors::Orange);	
}

void GameManager::DrawGameOverScreen()
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::mt19937 eng2(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 225); // define the range
	for (auto y = 10.0f; y < Graphics::ScreenHeight; y += 30)
	{
		gfx.DrawText(L"GAME OVER!", { Graphics::ScreenWidth / 2 - 80.0f,y }, TextSurface::Font(L"times", 15.0f), Colors::MakeRGB(distr(eng), distr(eng) + distr(eng2), distr(eng) - distr(eng2)));
	}
	gfx.DrawText(L"GAME OVER!", { Graphics::ScreenWidth / 2 - 80.0f,Graphics::ScreenHeight / 2 + 30 }, TextSurface::Font(L"times", 15.0f), Colors::Black);
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

void GameManager::DrawWhoseTurn(Color clr)
{
	switch (WhoseTurn())
	{
		case Team::BLACK:
			//gfx.DrawText(L"B", { 0.0f,0.0f }, fontus, Colors::Green);
			gfx.DrawText(L"B", { Graphics::ScreenWidth - 25.0f,Graphics::ScreenHeight - 30.0f, }, font, clr);
			break;
		case Team::WHITE:
			//gfx.DrawText(L"W", { 0.0f,00.0f }, fontus, Colors::Green);
			gfx.DrawText(L"W", { Graphics::ScreenWidth - 30.0f,Graphics::ScreenHeight - 30.0f, }, font, clr);
			break;
		default:
			gfx.DrawText(L"Whoops, Error!", { 0.0f,20.0f }, font, Colors::Red);
			break;
	}
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


