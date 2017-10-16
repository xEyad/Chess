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
#include "Game.h"
#include "StartMenu.h"
#include "ScreenPainter.h"
Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	manager(gfx, wnd.mouse)
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
	manager.HandleInput();
	switch (wnd.kbd.ReadKey().GetCode())
	{
		case VK_F1:
			ioManager.QuickSaveGame(manager.GetGameState());
			break;
		case VK_F2:
			manager.LoadGameState(ioManager.QuickLoadGame());
			break;
		default:
			break;
	}
}

void Game::ComposeFrame()
{		
	//manager.ManageDrawing();
	ScreenPainter sc(gfx);
	StartMenu s;
	sc.DrawScreenWithHighlights(s, { 0,0 },wnd.mouse.GetPos());
}

