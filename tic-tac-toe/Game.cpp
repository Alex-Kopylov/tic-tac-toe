#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}

void Game::nextTurn()
{
	player_turn = (player_turn == 1) ? 2 : 1;

}

void Game::makePlay(int index)
{
	gameboard[index] = player_turn;
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

int Game::getWinner()
{
	for (int i = 0; i < 24; i += 3) {
		if (gameboard[win_conditions[i]] != 0 &&
			gameboard[win_conditions[i]] == gameboard[win_conditions[i + 1]] &&
			gameboard[win_conditions[i]] == gameboard[win_conditions[i + 2]]) {
				//draw	
			return gameboard[win_conditions[i]]; //winner
		}
	}
	for (int i = 0; i < 9; i++) {
		if (gameboard[i] == 0)
			return 0; //empty cell
	}
	return 3; //draw
}

void Game::resetTheGame()
{
	player_turn = 1;
	for (int i = 0; i < 9; i++)
		gameboard[i] = 0;
}

int Game::getPlayerTurn()
{
	return player_turn;
}

Game::~Game()
{
}
