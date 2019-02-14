#pragma once
class Board
{
public:
	Board(HWND hWnd, HDC hdc, const int CELL_SIZE);
	void drawCentralizedBoard();
	~Board();
private:
	RECT rc;
	int width, height, left, top, right, bottom;
	int CELL_SIZE;
	HWND hWnd; 
	HDC hdc;
};

