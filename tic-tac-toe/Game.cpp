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

void Game::makePlay(int index)
{
	gameboard[index] = this->player_turn;
}

bool Game::isThisCellEmpty(int index)
{
	if (gameboard[index] == 0)
		return true;
	return false;
}

int Game::whatInTheCell(int index)
{
	return gameboard[index];
}

HBRUSH Game::getBrush()
{
	return (this->player_turn == 1) ? brush_O : brush_X;
}

HBRUSH Game::getBrush(int player_turn)
{
	return (player_turn == 1) ? brush_O : brush_X;
}


Game::~Game()
{
}
