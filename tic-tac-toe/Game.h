#pragma once
#include <vector>
class Game
{
public:
	Game();
	void nextTurn();
	void makePlay(int index);
	bool isThisCellEmpty(int index);
	std::vector<int> getGameBoard();
	int getWinner();
	void resetTheGame();
	void autoStep();
	int getPlayerTurn();
	~Game();
private:
	int player_turn = 1;
	std::vector<int> gameboard =  std::vector<int>(9,0);
	std::vector<int> win_conditions = { 0,1,2, //24 elements
						3,4,5,
						6,7,8,
						0,3,6,
						1,4,7,
						2,5,8,
						0,4,8,
						2,4,6, };
	void randomStep();
};

