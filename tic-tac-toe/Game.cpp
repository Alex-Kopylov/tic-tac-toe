#include "stdafx.h"
#include "Game.h"
#include <algorithm>
#include <ctime>

Game::Game()
{
}

void Game::nextTurn()
{
	player_turn = (player_turn == 1) ? 2 : 1;

}

void Game::makePlay(int index)
{
	if (gameboard[index] != 0) {
		resetTheGame();
		MessageBoxA(GetActiveWindow(), "You can't do this. The cell isn't empty", "Error", MB_ICONERROR);
		return;
	}
	gameboard[index] = player_turn;
	nextTurn();
}

bool Game::isThisCellEmpty(int index)
{
	if (gameboard[index] == 0)
		return true;
	return false;
}

std::vector<int> Game::getGameBoard()
{
	return gameboard;
}

int Game::getWinner()
{
	autoStep();
	for (int i = 0; i < 24; i += 3) {
		if (gameboard[win_conditions[i]] != 0 &&
			gameboard[win_conditions[i]] == gameboard[win_conditions[i + 1]] &&
			gameboard[win_conditions[i]] == gameboard[win_conditions[i + 2]]) {
				//draw	
			return gameboard[win_conditions[i]]; //winner
		}
	}
	for (int i = 0; i < 9; i++) {
		if (gameboard[i] == 0) {
			
			return 0; //no winner
		}
	}
	return 3; //draw
}

void Game::resetTheGame()
{
	player_turn = 1;
		std::fill(gameboard.begin(), gameboard.end(), 0);
}

void Game::autoStep()
{
	for (int i = 0; i < 24; i += 3) {
		std::vector<int> winCondition = { gameboard[win_conditions[i]], gameboard[win_conditions[i + 1]], gameboard[win_conditions[i + 2]] };
		if (std::count(winCondition.begin(), winCondition.end(), 0) < 2)
		{
			//Try to win
			if (winCondition[0] == 0)
				if (winCondition[1] == winCondition[2] && winCondition[1] == getPlayerTurn()) {
					makePlay(win_conditions[i]);
					return;
				}
			if (winCondition[1] == 0)
				if (winCondition[0] == winCondition[2] && winCondition[0] == getPlayerTurn()) {
					makePlay(win_conditions[i + 1]);
					return;
				}
			if (winCondition[2] == 0)
				if (winCondition[0] == winCondition[1] && winCondition[0] == getPlayerTurn()) {
					makePlay(win_conditions[i + 2]);
					return;
				}
		}
		else 
			continue;
	}
	for (int i = 0; i < 24; i += 3) {
		std::vector<int> winCondition = { gameboard[win_conditions[i]], gameboard[win_conditions[i + 1]], gameboard[win_conditions[i + 2]] };
		if (std::count(winCondition.begin(), winCondition.end(), 0) < 2)
		{
			//Try to not to fail
			if (winCondition[0] == 0)
				if (winCondition[1] == winCondition[2] && winCondition[1] != getPlayerTurn()) {
					makePlay(win_conditions[i]);
					return;
				}
			if (winCondition[1] == 0)
				if (winCondition[0] == winCondition[2] && winCondition[0] != getPlayerTurn()) {
					makePlay(win_conditions[i + 1]);
					return;
				}
			if (winCondition[2] == 0)
				if (winCondition[0] == winCondition[1] && winCondition[0] != getPlayerTurn()) {
					makePlay(win_conditions[i + 2]);
					return;
				}


		}
		else 
			continue;
	}
	randomStep();
}
void Game::randomStep() {
	std::vector<int> emptyCells;
	for (int i = 0; i < 9; i++) {
		if (gameboard[i] == 0) {
			emptyCells.push_back(i);
		}
	}
	srand(time(0));
	int randomEmptyCell = emptyCells[rand() % emptyCells.size()];
	makePlay(randomEmptyCell);
}
int Game::getPlayerTurn()
{
	return player_turn;
}

Game::~Game()
{
}
