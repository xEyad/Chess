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

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	chessBoard(8, 8), //basic chess board
	pawn(Vec2I(1, 2),Piece::Team::BLACK, &chessBoard)
{
	//mo2ktn el 2byda makano ta7t daymn
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
	int xx = 0;
	int yy = 0;
	const int screenCenterY = (Graphics::ScreenHeight - 100) / 2;
	const int screenCenterX = (Graphics::ScreenWidth - 100) / 2;
	int screenLocationX = screenCenterX;
	int screenLocationY = screenCenterY;
	Color c;
	//screenlocation reduces by 1 when x or y increases by 1 so that its place dont change
	for (auto i = chessBoard.boardTiles.cbegin(); i < chessBoard.boardTiles.cend(); i++)
	{		
		//if the location contain a piece, give it another color
		if ((*i)->location == pawn.locate())
			c = Colors::White;
		else
			c = (*i)->color;

		gfx.PutPixel((*i)->location.x + screenLocationX + xx, (*i)->location.y + screenLocationY +yy ,c);
		xx += 10;
		screenLocationY --;
		if ((*i)->location.y % 7 == 0 && (*i)->location.y != 0)//first one = 0, if we pass the 7 then its new row
		{
			yy += 10;
			xx = 0;
			screenLocationX--;
			screenLocationY = screenCenterY;
			
		}			
	}
}
