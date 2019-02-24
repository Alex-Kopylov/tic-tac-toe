#pragma once
class Game
{
public:
	Game();
	void deleteBrushes();
	void nextTurn();
	void makePlay(int index);
	bool isThisCellEmpty(int index);
	int whatInTheCell(int index);
	HBRUSH getBrush();
	HBRUSH getBrush(int player_turn);
	~Game();
private:
	HBRUSH brush_O = CreateSolidBrush(RGB(255,0,0));
	HBRUSH brush_X = CreateSolidBrush(RGB(0, 0, 255));
	int player_turn = 1;
	int gameboard[9] = { 0,0,0,
						 0,0,0,
						 0,0,0
						};
};

