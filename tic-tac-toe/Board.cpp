#include "stdafx.h"
#include "Board.h"


Board::Board(){	
}

 void Board::drawCentralizedBoard(HWND hWnd, HDC hdc)
{
	this->hWnd = hWnd;
	this->hdc = hdc;

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

Board::~Board(){
}
