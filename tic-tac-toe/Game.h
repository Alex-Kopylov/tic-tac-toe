#pragma once
class Game
{
public:
	Game();
	void deleteBrushes();
	void nextTurn();
	HBRUSH getBrush();
	~Game();
private:
	HBRUSH brush_O = CreateSolidBrush(RGB(255,0,0));
	HBRUSH brush_X = CreateSolidBrush(RGB(0, 0, 255));
	int player_turn = 1;
};

