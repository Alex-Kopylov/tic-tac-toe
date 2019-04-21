#include "stdafx.h"
#include "Cell.h"
#include "resource.h"


Cell::Cell()
{
	x_icon_ = (HICON)LoadImageA( // returns a HANDLE so we have to cast to HICON
		NULL,             // hInstance must be NULL when loading from a file
		"X_ICON.ico",   // the icon file name
		IMAGE_ICON,       // specifies that the file is an icon
		300,                // width of the image (we'll specify default later on)
		300,                // height of the image
		LR_LOADFROMFILE |  // we want to load a file (as opposed to a resource)
		LR_DEFAULTSIZE |   // default metrics based on the type (IMAGE_ICON, 32x32)
		LR_SHARED         // let the system release the handle when it's no longer used
	);
	o_icon_  = (HICON)LoadImageA( // returns a HANDLE so we have to cast to HICON
		NULL,             // hInstance must be NULL when loading from a file
		"O_ICON.ico",   // the icon file name
		IMAGE_ICON,       // specifies that the file is an icon
		100,                // width of the image (we'll specify default later on)
		100,                // height of the image
		LR_LOADFROMFILE |  // we want to load a file (as opposed to a resource)
		LR_DEFAULTSIZE |   // default metrics based on the type (IMAGE_ICON, 32x32)
		LR_SHARED         // let the system release the handle when it's no longer used
	);
}

int Cell::get_cell_number_from_point(int x_pos, int y_pos, RECT board_rect)
{
	const POINT pt = { x_pos, y_pos };
		if (PtInRect(&board_rect, pt)) {
			x_pos = pt.x - board_rect.left;
			y_pos = pt.y - board_rect.top;

			const auto column = x_pos / CELL_SIZE;
			const auto row = y_pos / CELL_SIZE;

			return column + row * 3; //index (0..8)
		}
	return -1; //outside of gameboard
}

const RECT * Cell::get_cell_rectangle(const int index, const RECT board_rect)
{
	const auto y = index / 3; // row number
	const auto x = index % 3; // column number
	RECT sub_rect;

	sub_rect.left = board_rect.left + x * CELL_SIZE;
	sub_rect.top = board_rect.top + y * CELL_SIZE;
	sub_rect.right = sub_rect.left + CELL_SIZE;
	sub_rect.bottom = sub_rect.top + CELL_SIZE;

	
	return &sub_rect;
}

HICON Cell::getIcon(const int player_turn)
{
	return (player_turn == 1) ? o_icon_ : x_icon_;
}
void Cell::delete_brushes() const
{
	DestroyIcon(x_icon_);
	DestroyIcon(o_icon_);
}
void Cell::mark_the_cell(const HDC hdc, int player_turn, const int x_left, const int y_top)
{
	DrawIconEx(
		hdc,   //hdc
		x_left,    //xLeft,
		y_top,    //yTop,
		getIcon(player_turn),//  hIcon,
		100,    //cxWidth,
		100,   //cyWidth,
		0,NULL, DI_NORMAL);
}
Cell::~Cell()
= default;
