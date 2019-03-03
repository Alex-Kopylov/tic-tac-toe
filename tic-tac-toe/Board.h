#pragma once
#include "Cell.h"
#include <vector>
class Board
{
public:
	Board();
	void drawCentralizedBoard(HWND & hWnd, HDC hdc);
	const RECT  getRectangle();
	void clearBoard(HWND hWnd);
	void drawCurrentGameOnTheBoard(Cell cell, HWND hWnd, HDC hdc, std::vector<int> gameboard);
	void drawGrid(HDC * hdc);
	void drawLine(int x1, int y1, int x2, int y2, HDC * hdc);
	RECT gameboardRectangle;
};