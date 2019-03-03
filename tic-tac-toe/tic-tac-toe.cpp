// tic-tac-toe.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tic-tac-toe.h"
#include "Board.h"
#include "Cell.h"
#include "Game.h"
#include "windowsx.h" // Buttun mouse handler

#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

Board board;
Game game;
Cell cell;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TICTACTOE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TICTACTOE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)GetStockObject(GRAY_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TICTACTOE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}




//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_NEWGAME: {
				game.resetTheGame();
				board.clearBoard(hWnd);
				break;
			}
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_GETMINMAXINFO: 
		{
			MINMAXINFO * pMinMax = (MINMAXINFO*)lParam;
			pMinMax->ptMinTrackSize.x = CELL_SIZE * 5;
			pMinMax->ptMinTrackSize.y = CELL_SIZE * 5;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		board.drawCentralizedBoard(hWnd, hdc);
		board.drawCurrentGameOnTheBoard(cell, hWnd, hdc, game.getGameBoard());
		EndPaint(hWnd, &ps);

	}
	break;

	case WM_LBUTTONDOWN: {
			int xClickPos = GET_X_LPARAM(lParam);
			int yClickPos = GET_Y_LPARAM(lParam);

			int buttonIndex = cell.getCellNumberFromPoint(hWnd, xClickPos, yClickPos, board.getRectangle());
			HDC hdc = GetDC(hWnd);
			if (NULL != hdc) {
				if (buttonIndex != -1 && game.isThisCellEmpty(buttonIndex)) {
					int cell_xLeft = cell.getCellRectangle(hWnd, buttonIndex, board.getRectangle())->left;
					int cell_yTop = cell.getCellRectangle(hWnd, buttonIndex, board.getRectangle())->top;
					cell.markTheCell(hdc,hWnd, game.getPlayerTurn(), cell_xLeft, cell_yTop);
					game.makePlay(buttonIndex);
					switch (game.getWinner()) {
						case (0): {
							board.drawCurrentGameOnTheBoard(cell, hWnd, hdc, game.getGameBoard());
						}
						break;
						case (1): {
							board.drawCurrentGameOnTheBoard(cell, hWnd, hdc, game.getGameBoard());
							MessageBox(hWnd,			
								L"Player [O] is the Winner!",
								L"Victory!",
								MB_OK | MB_ICONINFORMATION);
							
							game.resetTheGame();
							board.clearBoard(hWnd);
							
							break;
						}
						case (2): {
							board.drawCurrentGameOnTheBoard(cell, hWnd, hdc, game.getGameBoard());
							MessageBox(hWnd,
								L"Player [X] is the Winner!",
								L"Victory!",
								MB_OK | MB_ICONINFORMATION);
							
							game.resetTheGame();
							board.clearBoard(hWnd);
							
							break;
						}
						break;
						case (3): {
							board.drawCurrentGameOnTheBoard(cell, hWnd, hdc, game.getGameBoard());
							MessageBox(hWnd,
								L"No one wins this time",
								L"It's a draw!",
								MB_OK | MB_ICONINFORMATION);
							
							game.resetTheGame();
							board.clearBoard(hWnd);
							
							break;
						}
						break;
					}
				}
				ReleaseDC(hWnd, hdc);

			}
				
	}
	break;
    case WM_DESTROY:
		cell.deleteBrushes();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
