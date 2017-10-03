/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Piece.h"
#include "ChiliWin.h"
#include <random>
#include <iostream>
#include "Pawn.h"
#include "BoardPainter.h"
#include "PiecesPainter.h"
#include "ScreenPainter.h"
Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	manager(gfx, wnd.mouse)
	//chessBoard(8, 8), //basic chess board	
	//Director(chessBoard,gfx,wnd.mouse),
	//fontus(L"times", 20.0f)
{
	//mo2ktn el 2byd makano ta7t daymn	
	//chessBoard.IntializeGameDirector(Director);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!manager.Director().isGameOver())
	{
		//manager.Director().HandleInput(false); // change parameter for cheating
		manager.HandleInput();
		switch (wnd.kbd.ReadKey().GetCode())
		{
			case VK_F1:
				manager.Director().QuickSaveGame();
				break;
			case VK_F2:
				manager.Director().QuickLoadGame();
				break;
			default:
				break;
		}
			
	}
}

void Game::ComposeFrame()
{		

	manager.ManageDrawing();
//#if _DEBUG
//	manager.Director().SetStage(true);
//#else
//	manager.Director().SetStage();
//#endif // DEBUG
	
	/*BoardPainter s(gfx);
	s.DrawSprite(4);
	s.DrawGrid(chessBoard, { 20,21 });

	PiecesPainter p(gfx, Director.getPieces());
	p.DrawPiecesSprites({ 20,21 });

	BlackPromotionScreen bps(79 * 4, 79, gfx);
	ScreenPainter(gfx).DrawScreen(bps, { 20 + 80 * 2, 20 + 80 * 4  + 1 });
	//just a demo on how to load text or Sprite
	if (Director.isGameOver())
	{		
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::mt19937 eng2(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, 225); // define the range
		for (auto y = 10.0f; y < Graphics::ScreenHeight; y+=30)
		{
			gfx.DrawText(L"GAME OVER!", { Graphics::ScreenWidth / 2 - 80.0f,y }, fontus, Colors::MakeRGB(distr(eng), distr(eng) + distr(eng2), distr(eng) - distr(eng2)));
		}
		gfx.DrawText(L"GAME OVER!", { Graphics::ScreenWidth / 2 - 80.0f,Graphics::ScreenHeight / 2 + 30 }, fontus, Colors::Black);
	}
	*/
}

