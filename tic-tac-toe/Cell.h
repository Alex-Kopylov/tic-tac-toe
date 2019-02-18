#pragma once
class Cell
{
public:
	Cell();
	int getCellNumberFromPoint(HWND hWnd, int xPos, int yPos, RECT boardRect);
	~Cell();
};

