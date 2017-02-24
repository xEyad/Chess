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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	chessBoard(8, 8), //basic chess board	
	Director(chessBoard,gfx,wnd.mouse),
	pawn(Surface::FromFile(L"Resources\\pawnSmaller.bmp"))
{
	//mo2ktn el 2byd makano ta7t daymn	
	chessBoard.IntializeGameDirector(Director);

	//just test cases
	//auto p = Director.getPiece(11); //pawn
	//if (p != nullptr)
	//	p->MoveTo(19);

	//p = Director.getPiece({ 3,0 }); //queen
	//if (p != nullptr)
	//{
	//	p->MoveTo({ 3,2 });
	//	p->MoveTo({ 1,4 });
	//	p->MoveTo({ 1,5 });

	//}
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
	//Director.HandleInput();
	Director.CH_HandleInput();
}

void Game::ComposeFrame()
{		
	Director.SetStage();

	//just a demo on how to load text or Sprite
	if (Director.isGameOver())
	{
		const TextSurface::Font fontus(L"times", 50.0f);
		gfx.DrawText(L"GAME OVER BITCH!", { 50.0f,400.0f }, fontus, Colors::Red);
	}
	for (int x = 0; x < pawn.GetWidth(); x++)
	{
		for (int y = 0; y < pawn.GetHeight(); y++)
		{
			gfx.PutPixel(x+50,y+150,pawn.GetPixel(x, y));
		}
	}
	

}

