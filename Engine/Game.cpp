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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	chessBoard(8,8) //basic chess board
{
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
	int xx=0;
	int yy = 0;
	for (auto i = chessBoard.boardTiles.cbegin(); i < chessBoard.boardTiles.cend(); i++)
	{		
		gfx.PutPixel((*i)->location.x + 150 + xx, (*i)->location.y + 150 +yy ,(*i)->color);
		xx += 10;
		if ((*i)->location.y % 7 == 0 && (*i)->location.y != 0)//first one = 0
		{
			yy += 10;
			xx = 0;
		}
			
		//gfx.PutPixel((*i)->location.x + 150, (*i)->location.y + 150, (*i)->color);
	}
}
