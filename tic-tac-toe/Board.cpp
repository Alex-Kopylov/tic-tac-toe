#include "stdafx.h"
#include "Board.h"
#include "string"


Board::Board()
= default;

void Board::draw_centralized_board(HWND & hWnd, HDC hdc)
{		
	
	if (GetClientRect(hWnd, &gameboard_rectangle))
	{
		const int width = gameboard_rectangle.right - gameboard_rectangle.left;
		const int height = gameboard_rectangle.bottom - gameboard_rectangle.top;

	
		gameboard_rectangle.left = (width - CELL_SIZE * 3) / 2;
		gameboard_rectangle.top = (height - CELL_SIZE * 3) / 2;
		gameboard_rectangle.right = gameboard_rectangle.left + CELL_SIZE * 3;
		gameboard_rectangle.bottom = gameboard_rectangle.top + CELL_SIZE * 3;

		Rectangle(hdc, gameboard_rectangle.left, gameboard_rectangle.top, gameboard_rectangle.right, gameboard_rectangle.bottom);

		draw_grid(&hdc);
	}
}

RECT Board::get_rectangle() const
{
	 return gameboard_rectangle;
 }

void Board::redraw_board(const HWND hWnd)
{
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
}

void Board::draw_current_game_on_the_board(Cell cell, const HDC hdc, std::vector<unsigned int> gameboard) const
{
	for (auto i = 0; i < 9; i++) {
		if (gameboard[i] != 0) {
			const int cell_x_left = cell.get_cell_rectangle(i, get_rectangle())->left;
			const int cell_y_top = cell.get_cell_rectangle(i, get_rectangle())->top;
			cell.mark_the_cell(hdc, gameboard[i], cell_x_left, cell_y_top);
		}
	}
}

void Board::draw_grid(HDC * hdc) const
 {
	 for (auto i = 0; i < 4; i++) {
		 //Draw vertical lines
		 draw_line(gameboard_rectangle.left + CELL_SIZE * i, gameboard_rectangle.top, gameboard_rectangle.left + CELL_SIZE * i, gameboard_rectangle.bottom, hdc);
		 //Draw horizontal lines
		 draw_line(gameboard_rectangle.left, gameboard_rectangle.top + CELL_SIZE * i, gameboard_rectangle.right, gameboard_rectangle.top + CELL_SIZE * i, hdc);
	 }
 }
 void Board::draw_line(const int x1, const int y1, const int x2, const int y2, HDC * hdc) {
	 MoveToEx(*hdc, x1, y1, NULL);
	 LineTo(*hdc, x2, y2);
 }
