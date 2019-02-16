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
	HWND hWnd; 
	HDC hdc;
};

