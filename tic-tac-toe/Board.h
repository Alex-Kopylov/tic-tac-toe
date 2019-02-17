#pragma once
class Board
{
public:
	Board();
	void drawCentralizedBoard(HWND hWnd, HDC hdc);
	
	~Board();
private:
	RECT rc;
	int width, height, left, top, right, bottom;
	void drawGrid();
	void drawLine(int x1, int x2, int y1, int y2);
	HWND hWnd; 
	HDC hdc;
};

