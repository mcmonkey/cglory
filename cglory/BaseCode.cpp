// BaseCode.cpp : Defines the entry point for the application.
//
// This version has DirectX 10 added in to the project properties

#include "stdafx.h"
#include "BaseCode.h"
/*-----------------------------  NEW CODE --------------------------------*/
// *** add the dxManager header
#include "dxManager.h"
#include <iostream>

#include "InputManager.h"

// *** create the directx manager object
dxManager dx;

// *** define window size here
int windowWidth = 640;
int windowHeight = 480;

// made this global rather than local variable in initInstance
HWND hWnd;

/*--------------------------------------------------------------------------*/

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
bool				quit = false;
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BASECODE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	/*-------------------------- NEW CODE ---------------------------------*/
	// set up the directx manager
	if(!dx.initialize(&hWnd))
	{
		return FALSE;
	}
	/*---------------------------------------------------------------------*/

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BASECODE));

	// Main message loop:
	while (!quit)
	{
		if(PeekMessage(&msg, NULL, 0, 0, 1))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		// NEW CODE - render the current scene each time through
		Stats::startFPS();
		dx.renderScene();
		Stats::endFPS();
		Utility::debugUpdate();
		dx.update();
		Stats::update();

	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0; // could use 0 too for no icon
	wcex.hCursor		= LoadCursorFromFile(L"cursor.cur");
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;  // no menu in use
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= 0; // no small icon either
	return RegisterClassEx(&wcex);
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
   // HWND hWnd;  // made this a global variable

   /*---------------------------- NEW CODE --------------------------*/
   // resize the window
   // create a rectangle with the desired size
   RECT rect = {0,0,windowWidth,windowHeight};

   // adjust the window size - also sets the appearence
   AdjustWindowRect(&rect,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE);
   /*----------------------------------------------------------------*/

   hInst = hInstance; // Store instance handle in our global variable

   // Added a hardcoded title - use L to use wide characters (16 bit)
   // adjusted the size to reflect the requested size
   hWnd = CreateWindow(szWindowClass, L"DirectX 10 Initialization", WS_OVERLAPPEDWINDOW,
   CW_USEDEFAULT, CW_USEDEFAULT, rect.right-rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void killProgram()
{
	quit = true;
	PostQuitMessage(0);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_MOVE:
		case WM_SIZE:
			Utility::resize();
			break;
		case WM_CHAR:
			DeveloperConsole::catchCharacter((wchar_t)wParam);
			break;
		case WM_KEYDOWN:
			// check which key is pressed
			InputManager::keyDown(KeyState(wParam, lParam));
			switch(wParam)
			{
				case VK_F5:
					dx.toggleFullScreen();	
					break;
				case VK_F4: 
					killProgram();
					break;
			}
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// Add any drawing code here...
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			killProgram();
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
