#pragma once
class Board
{
public:
	Board();
	void drawCentralizedBoard(HWND & hWnd, HDC hdc);
	const RECT  getRectangle();
	void clearBoard(HWND hWnd);

private:
	void drawGrid(HDC * hdc);
	void drawLine(int x1, int y1, int x2, int y2, HDC * hdc);
	RECT gameboardRectangle;
};