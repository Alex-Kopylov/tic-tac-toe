#pragma once
class Game
{
public:
	Game();
	void nextTurn();
	void makePlay(int index);
	bool isThisCellEmpty(int index);
	int whatInTheCell(int index);
	int getWinner();
	void resetTheGame();
	int getPlayerTurn();
	~Game();
private:
	int player_turn = 1;
	int gameboard[9] = {0};
	int win_conditions[24] = { 0,1,2,
						3,4,5,
						6,7,8,
						0,3,6,
						1,4,7,
						2,5,8,
						0,4,8,
						2,4,6, };
};

