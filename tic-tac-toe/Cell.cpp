#include "stdafx.h"
#include "Cell.h"
#include "resource.h"


Cell::Cell()
{
	x_icon = (HICON)LoadImageA( // returns a HANDLE so we have to cast to HICON
		NULL,             // hInstance must be NULL when loading from a file
		"X_ICON.ico",   // the icon file name
		IMAGE_ICON,       // specifies that the file is an icon
		300,                // width of the image (we'll specify default later on)
		300,                // height of the image
		LR_LOADFROMFILE |  // we want to load a file (as opposed to a resource)
		LR_DEFAULTSIZE |   // default metrics based on the type (IMAGE_ICON, 32x32)
		LR_SHARED         // let the system release the handle when it's no longer used
	);
	o_icon  = (HICON)LoadImageA( // returns a HANDLE so we have to cast to HICON
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

HICON Cell::getIcon(int player_turn)
{
	return (player_turn == 1) ? o_icon : x_icon;
}
void Cell::deleteBrushes()
{
	DestroyIcon(x_icon);
	DestroyIcon(o_icon);
}
void Cell::markTheCell(HDC hdc, HWND hWnd, int player_turn, int xLeft, int yTop)
{
	DrawIconEx(
		hdc,   //hdc
		xLeft,    //xLeft,
		yTop,    //yTop,
		getIcon(player_turn),//  hIcon,
		100,    //cxWidth,
		100,   //cyWidth,
		0,NULL, DI_NORMAL);
}
Cell::~Cell()
{
}
