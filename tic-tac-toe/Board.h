#pragma once
class Board
{
public:
	Board();
	void drawCentralizedBoard(HWND & hWnd, HDC hdc);
	RECT  getRectangle();
	//int getLeft();
	//int getRight();
	//int getTop();
	//int getBot();
private:
	void drawGrid(HDC * hdc, RECT rc);
	void drawLine(int x1, int y1, int x2, int y2, HDC * hdc);
	RECT rc;
};