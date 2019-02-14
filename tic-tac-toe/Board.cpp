#include "stdafx.h"
#include "Board.h"


Board::Board(HWND hWnd, HDC hdc,const int CELL_SIZE)
{
	this->hWnd = hWnd;
	this->hdc = hdc;
	this->CELL_SIZE = CELL_SIZE;
}

void Board::drawCentralizedBoard()
{
	if (GetClientRect(hWnd, &rc))
	{
		width = rc.right - rc.left;
		height = rc.bottom - rc.top;

	
		left = (width - CELL_SIZE * 3) / 2;
		top = (height - CELL_SIZE * 3) / 2;
		right = left + CELL_SIZE * 3;
		bottom = top + CELL_SIZE * 3;

		Rectangle(hdc, left, top, right, bottom);
	}
}

Board::~Board()
{
}
