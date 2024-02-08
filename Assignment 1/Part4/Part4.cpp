// Part4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Part4.h"

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
	LoadStringW(hInstance, IDC_PART4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PART4));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PART4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PART4);
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

// My Global variables

// Vertical trafficlight
TrafficLight* tl1;
// Horizontal trafficlight
TrafficLight* tl2;

HBRUSH whiteBrush;
HBRUSH roadBrush;

HPEN noPen;

int tlStateTeller = 0;
bool driveHorizontally = true;

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
			tl1 = new TrafficLight(TLState::GO, TLDir::VERTICAL);
			tl2 = new TrafficLight(TLState::STOP, TLDir::HORIZONTALFLIPPED);
			roadBrush = CreateSolidBrush(RGB(100, 100, 100));
			whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
			noPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));

			// timer for å bytte hvilken retning som er rød / grønn
			SetTimer(hWnd, 0, 10000, NULL);

			// timer for å flytte horisontale biler
			SetTimer(hWnd, 2, 100, NULL);
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
			switch (wParam)
			{
			case 0:
				{
					// velger hvilket traffikklys som er rødt / grønt
					// stopp denne timeren
					KillTimer(hWnd, 0);
					// trafikklys state bytte timer
					SetTimer(hWnd, 1, 1000, NULL);
				}
				break;
			case 1:
				{
					switch (tlStateTeller)
					{
					case 0:
					case 1:
						{
							// endre state for trafikklys
							tl1->changeState();
							tl2->changeState();
							++tlStateTeller;
						}
						break;
					case 2:
						{
							if (driveHorizontally)
							{
								// timer for å flytte horisontale biler
								SetTimer(hWnd, 2, 100, NULL);
								KillTimer(hWnd, 3);
							}
							else
							{
								// timer for å flytte vertikale biler
								SetTimer(hWnd, 3, 100, NULL);
								KillTimer(hWnd, 2);
							}
							driveHorizontally = !driveHorizontally;
							tlStateTeller = 0;
							KillTimer(hWnd, 1);
							// timer for å bytte hvilken retning som er rød / grønn
							SetTimer(hWnd, 0, 10000, NULL);
						}
						break;
					default: break;
					}
					InvalidateRect(hWnd, NULL, false);
				}
				break;
			case 2:
				{
					// flytter horisontale biler
				}
				break;
			case 3:
				{
					// flytter vertikale biler
				}
				break;
			default: break;
			}
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			RECT screen;
			GetClientRect(hWnd, &screen);

			// Making our virtual device context and bitmap
			HDC vdc = CreateCompatibleDC(hdc);
			HBITMAP bmp = CreateCompatibleBitmap(hdc, screen.right, screen.bottom);
			SelectObject(vdc, bmp);

			// Select the white brush
			HGDIOBJ orgBrush = SelectObject(vdc, whiteBrush);

			// Notice all drawing operations go to our virtual device context
			Rectangle(vdc, 0, 0, screen.right, screen.bottom);

			// Draw roads
			// Select wanted pen and brush, and store original pen & brush
			SelectObject(vdc, roadBrush);
			HGDIOBJ orgPen = SelectObject(vdc, noPen);

			// Draw horizontal road, should be centered in the window
			Rectangle(vdc, 0, (screen.bottom / 2) - 50, screen.right, (screen.bottom / 2) + 50);
			// Draw vertical road, should be centered in the window
			Rectangle(vdc, (screen.right / 2) - 50, 0, (screen.right / 2) + 50, screen.bottom);

			// Restore original pen
			SelectObject(vdc, orgPen);

			// Code for dynamically updating the position of traffic lights for the window size
			// traffic light has height and widths of 190 and 70 pixels, and is drawn from top-left position
			// road is 100 pixels wide, centered on screen so +-50 pixels
			// i want 10 pixels of buffer from road to traffic light
			tl1->setPos(screen.right / 2 - 70 - 50 - 10, screen.bottom / 2 - 190 - 50 - 10);
			tl2->setPos(screen.right / 2 - 190 - 50 - 10, screen.bottom / 2 + 50 + 10);

			// Draw traffic lights
			tl1->draw(vdc);
			tl2->draw(vdc);

			// Restore original brush
			SelectObject(vdc, orgBrush);

			// One single copy operation copies everything from the virtual context to the
			// physical one
			BitBlt(hdc, 0, 0, screen.right, screen.bottom, vdc, 0, 0, SRCCOPY);

			// Cleaning up our virtual context. For better program performance,
			// We might consider just keeping these around instead of creating new ones and
			// deleting at every WM_PAINT call, but if so, be sure that you reuse the existing
			// ones and not just keep making new ones
			DeleteObject(bmp);
			DeleteDC(vdc);

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
