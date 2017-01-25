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
	chessBoard.Draw(gfx, { 40,40 }, Colors::LightGray);
	chessBoard.DrawPieces(gfx,Director, { 40,40 });
	/*for (auto i = chessBoard.boardTiles.cbegin(); i < chessBoard.boardTiles.cend(); i++)
	{
		bool enteredIF = false; // somehow the break of the switch inside the if statment makes the compiler to enter the else as if we didn't enter the IF block
		for (auto p = Director.pieces.cbegin(); p < Director.pieces.cend(); p++)
		{			
			//check if there is a piece on the current location, then give it a color
			if ((*i)->location == (*p)->locate())
			{
				enteredIF = true;
				switch ((*p)->getType())
				{
					case QUEEN:
						c = Colors::Red;
						break;
					case KING:
						c = Colors::Magenta;
						break;
					case BISHOP:
						c = Colors::Cyan;
						break;
					case ROOK:
						c = Colors::Yellow;
						break;
					case PAWN:
						c = Colors::Green;
						break;
					case KNIGHT:
						c = Colors::LightGray;
						break;
					default:
						c = Colors::Black;
						break;
				}
			}
			else if (!enteredIF)
				c = (*i)->color;
		}
					
		//Rows are Y , Columns are X
		gfx.PutPixel((*i)->location.x + screenLocationX + xx, (*i)->location.y + screenLocationY + yy, c);
		xx += 10;

		if ((*i)->location.x % 7 == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += 10;
		}
	}*/	
}
