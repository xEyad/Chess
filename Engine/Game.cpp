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
	Director.HandleInput(true); // change parameter for cheating
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
			gfx.DrawText(L"B", { 0.0f,10.0f }, fontus, Colors::Orange);
			break;
		case Team::WHITE:
			gfx.DrawText(L"W", { 0.0f,00.0f }, fontus, Colors::White);
			break;
		default:
			gfx.DrawText(L"Whoops, Error!", { 0.0f,20.0f }, fontus, Colors::Red);
			break;
	}

	if(!Director.IsKingsSafe())
		gfx.DrawText(L"A King under Threat", { 0.0f,10.0f }, fontus, Colors::Red);

	//just a demo on how to load text or Sprite
	if (Director.isGameOver())
	{		
		gfx.DrawText(L"GAME OVER BITCH!", { 0.0f,400.0f }, fontus, Colors::Cyan);
	}
}

