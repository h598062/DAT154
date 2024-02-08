// Part3.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Part3.h"

#include "TrafficLight.cpp"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Traffic light vars
TrafficLight* tl1;
TrafficLight* tl2;

HBRUSH whiteBrush;

HBRUSH roadBrush;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PART3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PART3));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PART3));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PART3);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	case WM_CREATE:
		{
			tl1 = new TrafficLight(TLState::GO, 0, 0, TLDir::VERTICAL);
			tl2 = new TrafficLight(TLState::STOP, 0, 0, TLDir::HORIZONTAL);
			roadBrush = CreateSolidBrush(RGB(100, 100, 100));
			whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
			SetTimer(hWnd, 0, 1000, NULL);
		}
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
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
		}
		break;
	case WM_TIMER:
		{
			tl1->changeState();
			tl2->changeState();
			InvalidateRect(hWnd, NULL, true);
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC phdc = BeginPaint(hWnd, &ps);
			RECT screen;
			GetClientRect(hWnd, &screen);

			// Making our virtual device context and bitmap
			HDC hdc = CreateCompatibleDC(phdc);
			HBITMAP bmp = CreateCompatibleBitmap(phdc, screen.right, screen.bottom);
			SelectObject(hdc, bmp);

			// Select the white brush
			SelectObject(hdc, whiteBrush);

			// Notice all drawing operations go to our virtual device context
			Rectangle(hdc, 0, 0, screen.right, screen.bottom);

			// Draw roads
			HGDIOBJ hOrg = SelectObject(hdc, roadBrush);
			// Draw horizontal road
			Rectangle(hdc, 0, screen.bottom / 2, screen.right, (screen.bottom / 2) + 100);
			// Draw vertical road
			Rectangle(hdc, screen.right / 2, 0, (screen.right / 2) + 100, screen.bottom);
			// Restore original brush
			SelectObject(hdc, hOrg);

			tl1->setPos(screen.right / 2 - 100, screen.bottom / 2 - 220);
			tl2->setPos(screen.right / 2 + 140, screen.bottom / 2 + 140);

			// Draw traffic lights
			tl1->draw(hdc);
			tl2->draw(hdc);

			// One single copy operation copies everything from the virtual context to the
			// physical one
			BitBlt(phdc, 0, 0, screen.right, screen.bottom, hdc, 0, 0, SRCCOPY);

			// Cleaning up our virtual context. For better program performance,
			// We might consider just keeping these around instead of creating new ones and
			// deleting at every WM_PAINT call, but if so, be sure that you reuse the existing
			// ones and not just keep making new ones
			DeleteObject(bmp);
			DeleteDC(hdc);

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		tl1->cleanUp();
		tl2->cleanUp();
		delete tl1;
		delete tl2;
		DeleteObject(roadBrush);
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
