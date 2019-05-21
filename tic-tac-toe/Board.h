#pragma once
#include "Cell.h"
#include <vector>
class Board
{
public:
	Board();
	void draw_centralized_board(HWND & hWnd, HDC hdc);
	RECT  get_rectangle() const;
	static void redraw_board(HWND hWnd);
	void draw_current_game_on_the_board(Cell cell, HDC hdc, std::vector<unsigned int> gameboard) const;
	void draw_grid(HDC * hdc) const;
	static void draw_line(int x1, int y1, int x2, int y2, HDC * hdc);
private:
	RECT gameboard_rectangle{};
};