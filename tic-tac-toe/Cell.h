#pragma once
class Cell
{
public:
	Cell();
	int getCellNumberFromPoint(HWND hWnd, int xPos, int yPos, RECT boardRect);
	~Cell();
	const RECT * getCellRectangle(HWND hWnd, int index, RECT boardRect);

private:

};

