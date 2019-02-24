#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}

void Game::deleteBrushes()
{
	DeleteObject(brush_O);
	DeleteObject(brush_X);
}

HBRUSH Game::getBrush(char brush)
{
	if (brush == 'O')
		return brush_O;

	return brush_X;
}


Game::~Game()
{
}
