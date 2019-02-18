#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
}

int Cell::getCellNumberFromPoint(HWND hWnd, int xPos, int yPos, RECT boardRect)
{
	POINT pt = { xPos, yPos };
	if (GetClientRect(hWnd, &boardRect))
	{
		if (PtInRect(&boardRect, pt)) {
			xPos = pt.x - boardRect.left;
			yPos = pt.y - boardRect.top;

			int column = xPos / CELL_SIZE;
			int row = yPos / CELL_SIZE;

			return column + row * 3; //index (0..8)
		}
	}
	return -1; //outside gameboard
}


Cell::~Cell()
{
}
