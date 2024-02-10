// Part4.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Part4.h"

#include <deque>
#include <forward_list>
#include <vector>

#include "TrafficLight.h"
#include "Bil.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

// variable for counting the state for the traffic lights
int tlStateTeller = 0;

typedef std::deque<Bil*> biler;

biler hzBilerBTL;
biler vertBilerBTL;
biler hzBilerATL;
biler vertBilerATL;

// the below method needs a starting colour
BilColour stupid = BilColour::RED;
//
// Method for getting a new colour for each car
//
BilColour nextColour()
{
	switch (stupid)
	{
	case BilColour::RED:
		stupid = BilColour::GREEN;
		return stupid;
	case BilColour::GREEN:
		stupid = BilColour::BLUE;
		return stupid;
	case BilColour::BLUE:
		stupid = BilColour::YELLOW;
		return stupid;
	case BilColour::YELLOW:
		stupid = BilColour::BLACK;
		return stupid;
	case BilColour::BLACK:
		stupid = BilColour::WHITE;
		return stupid;
	case BilColour::WHITE:
		stupid = BilColour::RED;
		return stupid;
	}
	return BilColour::RED;
}

//
// Moves cars before the traffic lights
//
void moveCars(HWND hWnd)
{
	/*
	TODO: Update logic for moving cars
	maybe use the deques to store "new" cars to appear
	the road should likely be an indexed array or vector,
	atleast the part leading up to the intersection
	this way its easy to prevent a collision by checking if the next pos has a car or not
	then each car can keep moving every timer iteration,
	until there is a car in front or red light
	the red light should be checked at a certain position
	then it can also have collision detection in the intersection,
	if the center position get pushed to both road arrays
	a new car should be added to the road if there is room,
	else added to deque (maybe limit this?)
	*/

	int prevBilPos = -1;
	const int movesize = 10;
	// flytter horisontale biler
	for (const auto bil : hzBilerBTL)
	{
		if (bil->pos > tl2->stopPos)
		{
			hzBilerBTL.pop_front();
			hzBilerATL.push_back(bil);
			// dont need to check for collision if the car is past the traffic light
			bil->updatePos(movesize);
		}
		else
		{
			if (!bil->collidesWith(prevBilPos, movesize))
			{
				if (tl2->canDrive() || !bil->collidesWith(tl2->stopPos, movesize))
				{
					// move car 10 px
					bil->updatePos(movesize);
				}
			}
			prevBilPos = bil->pos - bil->size / 2;
		}
	}
	prevBilPos = -1;
	// flytter vertikale biler
	for (const auto bil : vertBilerBTL)
	{
		if (bil->pos > tl1->stopPos)
		{
			vertBilerBTL.pop_front();
			vertBilerATL.push_back(bil);
			bil->updatePos(movesize);
		}
		else
		{
			if (!bil->collidesWith(prevBilPos, movesize))
			{
				if (tl1->canDrive() || !bil->collidesWith(tl1->stopPos, movesize))
				{
					// move car 10 px
					bil->updatePos(movesize);
				}
			}
			prevBilPos = bil->pos - bil->size / 2;
		}
		InvalidateRect(hWnd, NULL, false);
	}
}

//
// Moves the cars which has passed the traffic light
//
void moveCarsAfterTL(HWND hWnd)
{
	for (const auto bil : hzBilerATL)
	{
		bil->updatePos(10);

		if (bil->invalid)
		{
			hzBilerATL.pop_front();
			delete(bil);
		}
	}
	for (const auto bil : vertBilerATL)
	{
		bil->updatePos(10);

		if (bil->invalid)
		{
			vertBilerATL.pop_front();
			delete(bil);
		}
	}
	InvalidateRect(hWnd, NULL, false);
}

void changeTLStates(HWND hWnd)
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

//
// My programs paint
// extracted from WM_PAINT for better readability
//
void myPaint(HWND hWnd, HDC hdc)
{
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
	// also sets the stop position for the cars
	tl1->setPos(screen.right / 2 - 70 - 50 - 10, screen.bottom / 2 - 190 - 50 - 10);
	tl1->stopPos = (screen.bottom / 2) - 50;
	tl2->setPos(screen.right / 2 - 190 - 50 - 10, screen.bottom / 2 + 50 + 10);
	tl2->stopPos = (screen.right / 2) - 50;

	// Draw traffic lights
	tl1->draw(vdc);
	tl2->draw(vdc);

	for (const auto bil : hzBilerBTL)
	{
		bil->draw(vdc, screen.bottom / 2);
	}
	for (const auto bil : vertBilerBTL)
	{
		bil->draw(vdc, screen.right / 2);
	}
	for (const auto bil : hzBilerATL)
	{
		bil->draw(vdc, screen.bottom / 2);
		bil->invalid = bil->pos > screen.right;
	}
	for (const auto bil : vertBilerATL)
	{
		bil->draw(vdc, screen.right / 2);
		bil->invalid = bil->pos > screen.bottom;
	}

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
			tl1 = new TrafficLight(TLState::GO, TLDir::VERTICAL, 0);
			tl2 = new TrafficLight(TLState::STOP, TLDir::HORIZONTALFLIPPED, 0);
			roadBrush = CreateSolidBrush(RGB(100, 100, 100));
			whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
			noPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));

			// timer for å bytte hvilken retning som er rød / grønn
			SetTimer(hWnd, 0, 10000, NULL);

			// timer for å flytte biler før lyskryss
			SetTimer(hWnd, 2, 100, NULL);

			// timer for å flytte biler etter lyskryss
			SetTimer(hWnd, 3, 100, NULL);
		}
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			vertBilerBTL.push_back(new Bil(nextColour(), BilDirection::VERTICAL, 15));
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			hzBilerBTL.push_back(new Bil(nextColour(), BilDirection::HORIZONTAL, 15));
			InvalidateRect(hWnd, NULL, TRUE);
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
					changeTLStates(hWnd);
				}
				break;
			case 2:
				{
					moveCars(hWnd);
				}
				break;
			case 3:
				{
					moveCarsAfterTL(hWnd);
				}
				break;
			default: break;
			}
		}
		break;
	// Override default background erase
	// I dont need it to happen, as i use double buffering and redraw everything like that
	// leaving this default creates flickering sometimes, when something external forces repaint
	case WM_ERASEBKGND:
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			myPaint(hWnd, hdc);

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
