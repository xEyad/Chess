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
Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	chessBoard(8, 8,new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Grey\\Chess_Board_Stone2.png"))), //basic chess board	
	Director(chessBoard,gfx,wnd.mouse),
	fontus(L"times", 20.0f)
{
	//mo2ktn el 2byd makano ta7t daymn	
	chessBoard.IntializeGameDirector(Director);
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
	if (!Director.isGameOver())
	{
		Director.HandleInput(true); // change parameter for cheating

		switch (wnd.kbd.ReadKey().GetCode())
		{
			case VK_F1:
				Director.QuickSaveGame();
				break;
			case VK_F2:
				Director.QuickLoadGame();
				break;
			default:
				break;
		}
			
	}
}

void Game::ComposeFrame()
{		
#if _DEBUG
	Director.SetStage(true);
#else
	Director.SetStage();
#endif // DEBUG

	switch (Director.WhoseTurn())
	{
		case Team::BLACK:
			//gfx.DrawText(L"B", { 0.0f,0.0f }, fontus, Colors::Green);
			gfx.DrawText(L"B", { Graphics::ScreenWidth - 25.0f,Graphics::ScreenHeight - 30.0f, }, fontus, Colors::Green);
			break;
		case Team::WHITE:
			//gfx.DrawText(L"W", { 0.0f,00.0f }, fontus, Colors::Green);
			gfx.DrawText(L"W", { Graphics::ScreenWidth - 30.0f,Graphics::ScreenHeight - 30.0f, }, fontus, Colors::Green);
			break;
		default:
			gfx.DrawText(L"Whoops, Error!", { 0.0f,20.0f }, fontus, Colors::Red);
			break;
	}

	if (!Director.AreKingsSafe())
		gfx.DrawText(L"King is under Threat", {Graphics::ScreenWidth/2 - 80.0f,0.0f }, TextSurface::Font(L"times", 15.0f), Colors::Green);
	
	std::wstring turnNumber = std::wstring(L"Turn ") + std::to_wstring(Director.getTurn());
	gfx.DrawText(turnNumber, { 0.0f,0.0f }, fontus, Colors::Orange);
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
}

