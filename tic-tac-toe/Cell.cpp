#include "stdafx.h"
#include "Cell.h"



Cell::Cell()
{

}

int Cell::getCellNumberFromPoint(HWND hWnd, int xPos, int yPos, RECT boardRect)
{
	POINT pt = { xPos, yPos };
		if (PtInRect(&boardRect, pt)) {
			xPos = pt.x - boardRect.left;
			yPos = pt.y - boardRect.top;

			int column = xPos / CELL_SIZE;
			int row = yPos / CELL_SIZE;

			return column + row * 3; //index (0..8)
		}
	return -1; //outside gameboard
}

const RECT * Cell::getCellRectangle(HWND hWnd, int index, RECT boardRec)
{
	int y = index / 3; // row number
	int x = index % 3; // column number
	RECT SubRect;

	SubRect.left = boardRec.left + x * CELL_SIZE;
	SubRect.top = boardRec.top + y * CELL_SIZE;
	SubRect.right = SubRect.left + CELL_SIZE;
	SubRect.bottom = SubRect.top + CELL_SIZE;

	
	return &SubRect;
}

//void CELL::

Cell::~Cell()
{
}
