#pragma once
class Cell
{
public:
	Cell();
	int getCellNumberFromPoint(HWND hWnd, int xPos, int yPos, RECT boardRect);
	~Cell();
	const RECT * getCellRectangle(HWND hWnd, int index, RECT boardRect);
	HICON getIcon(int player_turn);
	void deleteBrushes();
	void markTheCell(HDC hdc,HWND hWnd, int player_turn, int xLeft, int yTop);

private:
	HICON x_icon, o_icon;
};

