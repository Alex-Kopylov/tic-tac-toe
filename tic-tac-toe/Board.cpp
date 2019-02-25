#include "stdafx.h"
#include "Board.h"
#include "string"

Board::Board(){
}


void Board::drawCentralizedBoard(HWND & hWnd, HDC hdc)
{		
	
	if (GetClientRect(hWnd, &gameboardRectangle))
	{
		int width = gameboardRectangle.right - gameboardRectangle.left;
		int height = gameboardRectangle.bottom - gameboardRectangle.top;

	
		gameboardRectangle.left = (width - CELL_SIZE * 3) / 2;
		gameboardRectangle.top = (height - CELL_SIZE * 3) / 2;
		gameboardRectangle.right = gameboardRectangle.left + CELL_SIZE * 3;
		gameboardRectangle.bottom = gameboardRectangle.top + CELL_SIZE * 3;

		Rectangle(hdc, gameboardRectangle.left, gameboardRectangle.top, gameboardRectangle.right, gameboardRectangle.bottom);
		
		//FillRect(hdc, &gameboardRectangle, (HBRUSH)GetStockObject(WHITE_BRUSH));
		drawGrid(&hdc);
		//return TRUE;
	}
	//SetRectEmpty(hWnd,gameboardRectangle);
	//return FALSE;
}
const RECT Board::getRectangle()
 {
	 return gameboardRectangle;
 }

void Board::clearBoard(HWND hWnd)
{
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
}

 void Board::drawGrid(HDC * hdc) {
	 for (int i = 0; i < 4; i++) {
		 //Draw vertical lines
		 drawLine(gameboardRectangle.left + CELL_SIZE * i, gameboardRectangle.top, gameboardRectangle.left + CELL_SIZE * i, gameboardRectangle.bottom, hdc);
		 //Draw horizontal lines
		 drawLine(gameboardRectangle.left, gameboardRectangle.top + CELL_SIZE * i, gameboardRectangle.right, gameboardRectangle.top + CELL_SIZE * i, hdc);
	 }
 }
 void Board::drawLine(int x1, int y1, int x2, int y2, HDC * hdc) {
	 MoveToEx(*hdc, x1, y1, NULL);
	 LineTo(*hdc, x2, y2);
 }
