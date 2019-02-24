#pragma once
class Game
{
public:
	Game();
	void deleteBrushes();
	HBRUSH getBrush(char brush);
	~Game();
private:
	HBRUSH brush_O = CreateSolidBrush(RGB(255,0,0));
	HBRUSH brush_X = CreateSolidBrush(RGB(0, 0, 255));
};

