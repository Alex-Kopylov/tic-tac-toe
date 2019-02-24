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

void Game::nextTurn()
{
	player_turn = (player_turn == 1) ? 2 : 1;

}

HBRUSH Game::getBrush()
{
	return (player_turn == 1) ? brush_O : brush_X;
}


Game::~Game()
{
}
