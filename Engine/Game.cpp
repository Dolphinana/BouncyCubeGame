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
	gfx( wnd )
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
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) { --playerVeloX; }
	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) { ++playerVeloX; }
	if (wnd.kbd.KeyIsPressed(VK_UP)) { --playerVeloY; }
	if (wnd.kbd.KeyIsPressed(VK_DOWN)) { ++playerVeloY; }

	MaxVelocity(playerVeloX, playerVeloY);

	playerX += playerVeloX;
	playerY += playerVeloY;

	WallCollision(playerX, playerY, playerWidth, playerHeight, playerVeloX, playerVeloY);
}

void Game::MaxVelocity(int & veloX, int & veloY)
{
	if (veloX > maxVelo)
	{
		veloX = maxVelo;
	}
	if (veloX < -maxVelo)
	{
		veloX = -maxVelo;
	}
	if (veloY > maxVelo)
	{
		veloY = maxVelo;
	}
	if (veloY < -maxVelo)
	{
		veloY = -maxVelo;
	}
}

void Game::WallCollision(int& x, int& y, int width, int height, int& veloX, int& veloY)
{
	if (x < 0)
	{
		x = 0;
		veloX = -veloX;
	}
	if (x + width >= gfx.ScreenWidth - 1)
	{
		x = gfx.ScreenWidth - width - 1;
		veloX = -veloX;
	}
	if (y < 0)
	{
		y = 0;
		veloY = -veloY;
	}
	if (y + height >= gfx.ScreenHeight - 1)
	{
		y = gfx.ScreenHeight - height - 1;
		veloY = -veloY;
	}
}

void Game::ComposeFrame()
{
	gfx.DrawPlayer(playerX, playerY, playerWidth, playerHeight);
}
