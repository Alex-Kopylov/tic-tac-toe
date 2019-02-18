#include "stdafx.h"
#include "Board.h"
#include "string"

Board::Board(){
}


void Board::drawCentralizedBoard(HWND & hWnd, HDC hdc)
{		
	
	if (GetClientRect(hWnd, &rc))
	{
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

	
		rc.left = (width - CELL_SIZE * 3) / 2;
		rc.top = (height - CELL_SIZE * 3) / 2;
		rc.right = rc.left + CELL_SIZE * 3;
		rc.bottom = rc.top + CELL_SIZE * 3;

		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		
		//FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		drawGrid(&hdc,rc);
		//return TRUE;
	}
	//SetRectEmpty(hWnd,rc);
	//return FALSE;
}
RECT Board::getRectangle()
 {
	 return rc;
 }
 //int Board::getLeft()
 //{
	// return left;
 //}
 //int Board::getRight()
 //{
	// return right;
 //}
 //int Board::getTop()
 //{
	// return top;
 //}
 //int Board::getBot()
 //{
	// return bottom;
 //}
 void Board::drawGrid(HDC * hdc, RECT rc) {
	 for (int i = 0; i < 4; i++) {
		 //Draw vertical lines
		 drawLine(rc.left + CELL_SIZE * i, rc.top, rc.left + CELL_SIZE * i, rc.bottom, hdc);
		 //Draw horizontal lines
		 drawLine(rc.left, rc.top + CELL_SIZE * i, rc.right, rc.top + CELL_SIZE * i, hdc);
	 }
 }
 void Board::drawLine(int x1, int y1, int x2, int y2, HDC * hdc) {
	 MoveToEx(*hdc, x1, y1, NULL);
	 LineTo(*hdc, x2, y2);
 }
