// tic-tac-toe.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tic-tac-toe.h"
#include "Board.h"
#include "Cell.h"
#include "Game.h"
#include <string>
#include <thread>
#include <mutex>
#include "windowsx.h"

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

std::ofstream file_;

HANDLE player_threads[2];
HANDLE players_mutex = CreateMutex(NULL, FALSE, NULL);
HANDLE game_is_ended_event = CreateEvent(NULL, TRUE, FALSE, NULL);
HANDLE new_game_event = CreateEvent(NULL, TRUE, FALSE, NULL);
bool thread_players_flag = true;
void write_data_in_file() {
		auto my_struct = game.keep_game_board_in_struct();
		file_ << "Game № " << my_struct->game_number_;
		switch (my_struct->buffer_winner) {
		case (2):
			file_ << " [X win]";
			break;
		case (1):
			file_ << " [O win]";
			break;
		case (0):
			file_ << " [Draw]";
			break;
		default:;
		}
		file_ << std::endl;
		for (auto i = 0; i < 9; i++) {
			switch (my_struct->gameboard_[i]) {
			case 0:
				file_ << " ";
				break;
			case 1:
				file_ << "O";
				break;
			case 2:
				file_ << "X";
				break;
			default:;
			}

			if (i == 2 || i == 5 || i == 8)
				file_ << std::endl;
		}
}

DWORD WINAPI  thread_play(LPVOID lparam) {
	while (thread_players_flag) {
		WaitForSingleObject(new_game_event, INFINITE);
		while (!game.is_game_over()) {
			WaitForSingleObject(players_mutex, INFINITE);
				game.auto_step();
			ReleaseMutex(players_mutex);
		}
		ResetEvent(new_game_event);
		SetEvent(game_is_ended_event);
	}
	return 0;
}

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
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            //TranslateMessage(&msg);
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
ATOM MyRegisterClass(const HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
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
BOOL InitInstance(const HINSTANCE hInstance, const int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   const auto hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
LRESULT CALLBACK WndProc(HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{	
    switch (message)
    {
		case WM_COMMAND:
			{
				const int wmId = LOWORD(wParam);
				// Parse the menu selections:
				switch (wmId)
				{
				case ID_START_GAME: {		
					file_.open("output_file.txt", std::ios::trunc);
					thread_players_flag = true;
					player_threads[0] = CreateThread(NULL, 0, thread_play, NULL, 0, NULL);
					player_threads[1] = CreateThread(NULL, 0, thread_play, NULL, 0, NULL);
					
					for (int i = 0; i < 1000; i++){
						ResetEvent(game_is_ended_event);
						game.start_new_game();
						SetEvent(new_game_event);
						WaitForSingleObject(game_is_ended_event, INFINITE);
						write_data_in_file();
						board.redraw_board(hWnd);
					}
					SetEvent(new_game_event); //set event to signal to quit player's threads. 
					thread_players_flag = false;
					auto result_sting =
						"X wins: " +
						std::to_string(game.get_game_stat()[2]) + "\n" +
						"O wins: " +
						std::to_string(game.get_game_stat()[1]) + "\n" +
						"Draws: " +
						std::to_string(game.get_game_stat()[0]);
					file_.close();

					MessageBox(hWnd, std::wstring(result_sting.begin(), result_sting.end()).c_str(), L"Results", MB_OK | MB_ICONASTERISK );
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
				const auto p_min_max = (MINMAXINFO*) lParam;
				p_min_max->ptMinTrackSize.x = CELL_SIZE * 5;
				p_min_max->ptMinTrackSize.y = CELL_SIZE * 5;
			}
			break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			const auto hdc = BeginPaint(hWnd, &ps);
			board.drawCentralizedBoard(hWnd, hdc);
			board.draw_current_game_on_the_board(cell, hdc, game.get_game_board());
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_DESTROY:
			cell.delete_brushes();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(const HWND hDlg, const UINT message, const WPARAM wParam, LPARAM lParam)
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
    default: ;
    }
    return (INT_PTR)FALSE;
}