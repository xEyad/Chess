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
	Director(chessBoard)
{
	//mo2ktn el 2byd makano ta7t daymn	
	chessBoard.intializeGameDirector(Director);
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
	
}
void Game::ComposeFrame()
{		
	//draw Grid/Board
	//int xx = 0;
	//int yy = 0;
	//const int screenCenterY = (Graphics::ScreenHeight - 100) / 2;
	//const int screenCenterX = (Graphics::ScreenWidth - 100) / 2;
	//int screenLocationX = screenCenterX;
	//int screenLocationY = screenCenterY;
	//Color c;
	chessBoard.Draw(gfx, { 40,40 }, Colors::LightGray);
	chessBoard.DrawPieces(gfx, { 40,40 });

	auto p = Director.getPiece({ 1,0 });
	if (p != nullptr)
		p->moveTo(18);

	p = Director.getPiece({ 2,2 });
	if (p != nullptr)
		p->moveTo(35);

	p = Director.getPiece({ 3,4 });
	if (p != nullptr)
		p->moveTo(52);




	while (!wnd.mouse.IsEmpty())
	{	
		const Vec2 mPos(float(wnd.mouse.GetPosX()), float(wnd.mouse.GetPosY()));
		chessBoard.highlightTile(gfx, mPos, Colors::LightGray); // top left is hardcoded
		const Mouse::Event e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::LPress)
		{
			
		}
	}
}
