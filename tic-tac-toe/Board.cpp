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
		//FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		drawGrid();
	}
}
 void Board::drawGrid() {
	 for (int i = 0; i < 4; i++) {
		 //Draw vertical lines
		 drawLine(left + CELL_SIZE * i, top, left + CELL_SIZE * i, bottom);
		 //Draw horizontal lines
		 drawLine(left, top + CELL_SIZE * i, right, top + CELL_SIZE * i);	 
	 }
 }
 void Board::drawLine(int x1, int y1, int x2, int y2) {
	 MoveToEx(hdc, x1, y1, NULL);
	 LineTo(hdc, x2, y2);
 }

Board::~Board(){
}
