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
	HandleMouse();
}

void Game::ComposeFrame()
{		
	
	chessBoard.Draw(gfx,Colors::LightGray);
	chessBoard.DrawPieces(gfx);	
	if (selectionMode)
		highlight = Colors::Magenta;
	else
		highlight = Colors::Red;

	chessBoard.HighlightTile(gfx, wnd.mouse.GetPos(), highlight);
}
void Game::HandleMouse()
{
	static int clickCounter = 0;
	static std::shared_ptr<Tile> t1, t2;
	
	//do highlights
	if (clickCounter == 1)
		selectionMode = true;
	else
		selectionMode = false;

	const Mouse::Event e = wnd.mouse.Read();
	if (e.GetType() == Mouse::Event::LPress) //update counter on left click
	{
		chessBoard.HighlightTile(gfx, wnd.mouse.GetPos(), Colors::Yellow); //flash yellow
		if (clickCounter == 0) //first click
		{
			t1 = chessBoard.GetTileByMouse(wnd.mouse.GetPos()); //click 1 (get its coordinates)
			clickCounter++;
		}
		else if (clickCounter >= 1)
		{
			t2 = chessBoard.GetTileByMouse(wnd.mouse.GetPos()); //click 2 (get its coordinates)
			if (t1 != nullptr && t2 != nullptr) //if the 2 clicks locations are valid
			{
				//move the piece (if its logical)
				auto p = Director.getPiece(t1->location);
				if (p != nullptr)
					p->MoveTo(t2->location);
			}
			clickCounter = 0;
		}
	}
	
}