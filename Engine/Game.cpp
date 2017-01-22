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
	pawn(Vec2I(1, 1),Team::BLACK, &chessBoard),
	pawn2(Vec2I(6, 1), Team::BLACK, &chessBoard),	
	rook(Vec2I(3,1), Team::BLACK, &chessBoard),
	bishop(Vec2I(4, 3), Team::BLACK, &chessBoard),
	king(Vec2I(4, 2), Team::BLACK, &chessBoard),
	queen(Vec2I(1, 3), Team::BLACK, &chessBoard),
	pawn3(Vec2I(1, 6), Team::WHITE, &chessBoard),
	pawn4(Vec2I(7, 6), Team::WHITE, &chessBoard)
	
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
	//fails
//	queen.moveTo({ pawn.locate() });
//	queen.moveTo({ rook.locate() });
//	queen.moveTo({ king.locate() });
//	queen.moveTo({ bishop.locate() });
//	queen.moveTo({ 2,5 });
//	queen.moveTo({ 5,3 });
//	queen.moveTo({ 4,0 });
//	queen.moveTo({ 5,5 });
//	bishop.moveTo({ 1,5});
//	bishop.moveTo({ 2,4 });
//	bishop.moveTo({ 7,1 });
//	bishop.moveTo({ 6,1 });
//	bishop.moveTo({ 0,1 });
//	bishop.moveTo({ 3,5 });
//	bishop.moveTo(pawn2.locate());
//	king.moveTo({ rook.locate() });
//	king.moveTo({ bishop.locate() });
//	king.moveTo({ pawn3.locate() });
//	king.moveTo({ 4,6 });

	//success
//	queen.moveTo({ 2,3 });
//	queen.moveTo({ 3,3 });
//	queen.moveTo({ 1,4 });
//	queen.moveTo({ 3,3 });
//	queen.moveTo({ 4,6 });
//	queen.moveTo({ 4,4 });
//	queen.moveTo({ 7,1 });
//	queen.moveTo({ 7,6 });
//	king.moveTo({ 4,1 });
//	king.moveTo({ 4,0 });
//	king.moveTo({ 5,0 });
//	king.moveTo({ 4,1 });
//	bishop.moveTo(pawn4.locate());
//	bishop.moveTo(pawn3.locate());
//	bishop.moveTo({ 5,2 });
//	bishop.moveTo({ 2,1 });
//	bishop.moveTo({ 1,6 });
//	rook.moveTo({ 3,0 });
//	rook.moveTo({ 1,4 });
//	rook.moveTo({ 1,6 });
//	rook.moveTo(pawn.locate());
//	rook.moveTo({ 0,1 });
//	rook.moveTo(pawn2.locate());
//	rook.moveTo({ 5,2 });
//	rook.moveTo({ 3,0 });
//	rook.moveTo({ 7,1 });
//	rook.moveTo({ 3,5 });
//	pawn.moveTo({ 1,3 });
//	pawn.moveTo({ 1,6 });
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
	for (auto i = chessBoard.boardTiles.cbegin(); i < chessBoard.boardTiles.cend(); i++)
	{
		//if the location contain a piece, give it another color
		if ((*i)->location == queen.locate())
			c = Colors::Red;
		else if ((*i)->location == king.locate())
			c = Colors::Magenta;
		else if ((*i)->location == bishop.locate())
			c = Colors::Cyan;
		else if ((*i)->location == rook.locate())
			c = Colors::Yellow;
		else if ((*i)->location == pawn.locate() || (*i)->location == pawn2.locate() || (*i)->location == pawn3.locate() || (*i)->location == pawn4.locate())
			c = Colors::Green;		
		else
			c = (*i)->color;
		//Rows are Y , Columns are X
		gfx.PutPixel((*i)->location.x + screenLocationX + xx, (*i)->location.y + screenLocationY + yy, c);
		xx += 10;

		if ((*i)->location.x % 7 == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += 10;
		}
	}
	
}
