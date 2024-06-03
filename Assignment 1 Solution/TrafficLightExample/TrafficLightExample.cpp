//
// Traffic Light Simulator
//
// This implementation uses a standard non-object oriented approach
// It also intentionally keep all code inline in the various Windows
// Messages instead of using function calls. This causes some
// (unnecessary) repetition of code, but it may be a bit clearer what
// each part does. All constants and includes are also included here in
// the main file.
// There is a lot that can be done to make this prettier, but it shows
// a basic solution fulfilling all requirements



#include "framework.h"
#include "TrafficLightExample.h"
#include <deque>
#include <strsafe.h>
#include <time.h>

#define MAX_LOADSTRING 100
#define ROAD_COLOR RGB(200,200,200)
#define OUTLINE_COLOR RGB(0,0,0)
#define RED_COLOR RGB(255,0,0)
#define YELLOW_COLOR RGB(200,200,0)
#define GREEN_COLOR RGB(0,255,75)
#define LIGHT_OFF_COLOR RGB(100,100,100)
#define TIMER_LIGHTS 1
#define TIMER_CARS 2
#define TIMER_ADD_CARS 3
#define CAR_LENGTH 40
#define CAR_WIDTH 20
#define ROAD_WIDTH 100


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

std::deque<COLORREF> northCarsColor;
std::deque<int> northCarsPosition;
std::deque<COLORREF> westCarsColor;
std::deque<int> westCarsPosition;
int lightstate = 0;
int pN = 100;
int pW = 100;



// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SetProbabilities(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_TRAFFICLIGHTEXAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRAFFICLIGHTEXAMPLE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRAFFICLIGHTEXAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TRAFFICLIGHTEXAMPLE);
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
    case WM_CREATE:
    {
        SetTimer(hWnd, TIMER_LIGHTS, 2000, 0);
        SetTimer(hWnd, TIMER_CARS, 100, 0);
        SetTimer(hWnd, TIMER_ADD_CARS, 500, 0);
        srand(time(0));
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_PROBABILITIES_SET:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_PROB), hWnd, SetProbabilities);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            RECT dims;
            GetClientRect(hWnd, &dims);
            POINT screenCenter = { dims.right / 2, dims.bottom / 2 };

            // Draw the road
            HBRUSH roadBrush = CreateSolidBrush(ROAD_COLOR);
            HPEN outline = CreatePen(PS_SOLID, 2, OUTLINE_COLOR);
            HGDIOBJ hOrgBrush = SelectObject(hdc, roadBrush);
            HGDIOBJ hOrgPen = SelectObject(hdc, outline);

            Rectangle(hdc, dims.left, screenCenter.y - (ROAD_WIDTH / 2), dims.right, screenCenter.y + (ROAD_WIDTH / 2));
            Rectangle(hdc, screenCenter.x - (ROAD_WIDTH / 2), dims.top, screenCenter.x + (ROAD_WIDTH / 2), dims.bottom);

            HPEN nullPen = CreatePen(PS_NULL, 2, 0);
            SelectObject(hdc, nullPen);
            Rectangle(hdc, dims.left, screenCenter.y - (ROAD_WIDTH / 2), dims.right, screenCenter.y + (ROAD_WIDTH / 2));
            Rectangle(hdc, screenCenter.x - (ROAD_WIDTH / 2), dims.top, screenCenter.x + (ROAD_WIDTH / 2), dims.bottom);
            
            SelectObject(hdc, hOrgBrush);
            SelectObject(hdc, hOrgPen);
            DeleteObject(roadBrush);
            DeleteObject(nullPen);


            
            // Draw the lights
            HBRUSH lightBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, outline);
            SelectObject(hdc, lightBrush);

            Rectangle(hdc, screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * 2), screenCenter.x - (ROAD_WIDTH / 2), screenCenter.y - (ROAD_WIDTH / 2));
            Rectangle(hdc, screenCenter.x - (ROAD_WIDTH * 2), screenCenter.y + (ROAD_WIDTH / 2), screenCenter.x - (ROAD_WIDTH / 2), screenCenter.y + ROAD_WIDTH);

            HBRUSH darkBrush = CreateSolidBrush(LIGHT_OFF_COLOR);
            SelectObject(hdc, darkBrush);
            for (double i = 2; i > 0.5; i-=0.5) {
                Ellipse(hdc, screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * i), screenCenter.x - (ROAD_WIDTH / 2), screenCenter.y - (ROAD_WIDTH * (i-0.5)));
                Ellipse(hdc, screenCenter.x - (ROAD_WIDTH * i), screenCenter.y + (ROAD_WIDTH / 2), screenCenter.x - (ROAD_WIDTH * (i-0.5)), screenCenter.y + ROAD_WIDTH);
            }

            // lightstate is based on a 4-step cycle, where one light has green
            // while the other has red, and one light switches to red+yellow as the other
            // switches to yellow.
            // Another common way of switching is a 6-step cycle where the second light 
            // waits untill the first switches to red before going to red+yellow.
            // No real code difference, just a slighly larger switch.
            HBRUSH redLight = CreateSolidBrush(RED_COLOR);
            HBRUSH yellowLight = CreateSolidBrush(YELLOW_COLOR);
            HBRUSH greenLight = CreateSolidBrush(GREEN_COLOR);
            switch (lightstate) {
            case 0: // red   ||   green
                SelectObject(hdc, redLight);
                Ellipse(hdc, screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * 2), screenCenter.x - (ROAD_WIDTH / 2), screenCenter.y - (ROAD_WIDTH * (1.5)));
                SelectObject(hdc, greenLight);
                Ellipse(hdc, screenCenter.x - (ROAD_WIDTH * 2), screenCenter.y + (ROAD_WIDTH / 2), screenCenter.x - (ROAD_WIDTH * (1.5)), screenCenter.y + ROAD_WIDTH);
                break;
            case 1: // red+yellow   ||   yellow
                SelectObject(hdc, redLight);
                Ellipse(hdc, screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * 2), screenCenter.x - (ROAD_WIDTH / 2), screenCenter.y - (ROAD_WIDTH * (1.5)));
                SelectObject(hdc, yellowLight);
                Ellipse(hdc, screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * 1.5), screenCenter.x - (ROAD_WIDTH / 2), screenCenter.y - (ROAD_WIDTH * (1)));
                Ellipse(hdc, screenCenter.x - (ROAD_WIDTH * 1.5), screenCenter.y + (ROAD_WIDTH / 2), screenCenter.x - (ROAD_WIDTH * (1)), screenCenter.y + ROAD_WIDTH);
                break;
            case 2: // green   ||   red
                SelectObject(hdc, redLight);
                Ellipse(hdc, screenCenter.x - (ROAD_WIDTH * 1), screenCenter.y + (ROAD_WIDTH / 2), screenCenter.x - (ROAD_WIDTH * (0.5)), screenCenter.y + ROAD_WIDTH);
                SelectObject(hdc, greenLight);
                Ellipse(hdc, screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * 1), screenCenter.x - (ROAD_WIDTH / 2), screenCenter.y - (ROAD_WIDTH * (0.5)));
                break;
            case 3: // yellow   ||   red+yellow
                SelectObject(hdc, redLight);
                Ellipse(hdc, screenCenter.x - (ROAD_WIDTH * 1), screenCenter.y + (ROAD_WIDTH / 2), screenCenter.x - (ROAD_WIDTH * (0.5)), screenCenter.y + ROAD_WIDTH);
                SelectObject(hdc, yellowLight);
                Ellipse(hdc, screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * 1.5), screenCenter.x - (ROAD_WIDTH / 2), screenCenter.y - (ROAD_WIDTH * (1)));
                Ellipse(hdc, screenCenter.x - (ROAD_WIDTH * 1.5), screenCenter.y + (ROAD_WIDTH / 2), screenCenter.x - (ROAD_WIDTH * (1)), screenCenter.y + ROAD_WIDTH);
                break;
            }
            SelectObject(hdc, hOrgBrush);
            SelectObject(hdc, hOrgPen);
            DeleteObject(lightBrush);
            DeleteObject(darkBrush);
            DeleteObject(redLight);
            DeleteObject(yellowLight);
            DeleteObject(greenLight);


            // Draw percentages
            WCHAR num[10];
            SetBkMode(hdc, TRANSPARENT);
            StringCbPrintf(num, 10, L"%d%%", pN);
            TextOut(hdc, screenCenter.x - ROAD_WIDTH, screenCenter.y - (ROAD_WIDTH * 2) - 20, num,wcsnlen_s(num,4));
            StringCbPrintf(num, 10, L"%d%%", pW);
            TextOut(hdc, screenCenter.x - (ROAD_WIDTH * 2) - 40, screenCenter.y + (ROAD_WIDTH / 2), num, wcsnlen_s(num, 4));


            // Draw cars
            SelectObject(hdc, outline);
            auto itp = northCarsPosition.begin();
            auto itc = northCarsColor.begin();
            while (itp != northCarsPosition.end() && itc != northCarsColor.end()) {
                HBRUSH carBrush = CreateSolidBrush(*itc);
                SelectObject(hdc, carBrush);
                Rectangle(hdc, screenCenter.x - CAR_WIDTH/2, *itp + screenCenter.y, screenCenter.x + CAR_WIDTH/2, *itp + CAR_LENGTH + screenCenter.y);
                SelectObject(hdc, hOrgBrush);
                DeleteObject(carBrush);
                itp++;
                itc++;
            }

            itp = westCarsPosition.begin();
            itc = westCarsColor.begin();
            while (itp != westCarsPosition.end() && itc != westCarsColor.end()) {
                HBRUSH carBrush = CreateSolidBrush(*itc);
                SelectObject(hdc, carBrush);
                Rectangle(hdc, *itp + screenCenter.x, screenCenter.y - CAR_WIDTH/2, *itp + CAR_LENGTH + screenCenter.x, screenCenter.y + CAR_WIDTH/2);
                SelectObject(hdc, hOrgBrush);
                DeleteObject(carBrush);
                itp++;
                itc++;
            }

            SelectObject(hdc, hOrgBrush);
            SelectObject(hdc, hOrgPen);
            DeleteObject(outline);

            EndPaint(hWnd, &ps);
            
        }
        break;
    case WM_TIMER:
    {
        switch (wParam) {
        case TIMER_LIGHTS:
            lightstate = ++lightstate % 4;
            SetTimer(hWnd, TIMER_LIGHTS, lightstate % 2 == 1 ? 1000 : 5000,0);
            break;
        case TIMER_CARS:
        {
            
            int prevpos = 99999; // Setting an impossible high starting value
            int minDistance = 5;
            int speed = 15;

            auto it = northCarsPosition.begin();
            while (it != northCarsPosition.end()) {
                if (*it + minDistance + speed + CAR_LENGTH < prevpos) { // not crashing into other cars

                    if (lightstate != 2                                     // not green light
                        && *it + CAR_LENGTH <= ROAD_WIDTH/-2                // and we have not passed the stop line
                        && (*it + CAR_LENGTH + speed >= ROAD_WIDTH / -2)) { // but additional movement would push us over
                       
                        (*it) = ROAD_WIDTH / -2 - CAR_LENGTH;
                    } else { // nothing blocks our movement
                        (*it) += speed;
                    }
                }
                prevpos = *it;
                it++;
            }

            it = westCarsPosition.begin();
            prevpos = 99999; // Setting an impossible high starting value
            while (it != westCarsPosition.end()) {
                if (*it + minDistance + speed + CAR_LENGTH < prevpos) { // not crashing into other cars

                    if (lightstate != 0                                     // not green light
                        && *it + CAR_LENGTH <= ROAD_WIDTH / -2                // and we have not passed the stop line
                        && (*it + CAR_LENGTH + speed >= ROAD_WIDTH / -2)) { // but additional movement would push us over

                        (*it) = ROAD_WIDTH / -2 - CAR_LENGTH;
                    }
                    else { // nothing blocks our movement
                        (*it) += speed;
                    }
                }
                prevpos = *it;
                it++;
            }


            InvalidateRect(hWnd, 0, 1);
            break;
        }
        case TIMER_ADD_CARS:

            HDC screenDC = GetDC(hWnd);

            int XRes = GetDeviceCaps(screenDC, HORZRES);
            int YRes = GetDeviceCaps(screenDC, VERTRES);

            DeleteDC(screenDC);

            // This calculation base car position on the size of the screen
            // It means it can take a few timer ticks to get them on screen
            // if the window wasn't maximized, but it results in better handling
            // if window size changes when the application is running
            // (Note that it will pull the sizes from the primary display, which
            // could cause weirdness on multi-monitor displays)
            // I am basically trating the middle of the crossroads as an origin
            // here, which is why cars spawn at a bit more than half the screen
            // height/width
                if (northCarsColor.empty() || *(northCarsPosition.rbegin()) > -(YRes / 2 + 50 - CAR_LENGTH)) {
                    if (rand() % 100 < pN) {
                        northCarsColor.push_back(RGB(rand()%255, rand() % 255, rand() % 255));
                        northCarsPosition.push_back(-(YRes / 2 + 50));
                    }
                }

                // remove cars outside screen borders
                if (!northCarsColor.empty()  && *(northCarsPosition.begin()) > YRes / 2 + 50) {
                    northCarsPosition.pop_front();
                    northCarsColor.pop_front();
                }

                if (westCarsColor.empty() || *(westCarsPosition.rbegin()) > -(XRes / 2 + 50 - CAR_LENGTH)) {
                    if (rand() % 100 < pW) {
                        westCarsColor.push_back(RGB(rand() % 255, rand() % 255, rand() % 255));
                        westCarsPosition.push_back(-(XRes / 2 + 50));
                    }
                }

                // remove cars outside screen borders
                if (!westCarsColor.empty() && *(westCarsPosition.begin()) > XRes / 2 + 50) {
                    westCarsPosition.pop_front();
                    westCarsColor.pop_front();
                }


            break;
        }

        break;

    }
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_LEFT:
            pW = pW >= 5 ? pW - 5 : 0;
            break;
        case VK_RIGHT:
            pW = pW <= 95 ? pW + 5 : 100;
            break;
        case VK_DOWN:
            pN = pN >= 5 ? pN - 5 : 0;
            break;
        case VK_UP:
            pN = pN <= 95 ? pN + 5 : 100;
            break;
        }
        break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
        lightstate = ++lightstate % 4;
        InvalidateRect(hWnd, 0, 0);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


INT_PTR CALLBACK SetProbabilities(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemInt(hDlg, IDC_PN, pN, true);
        SetDlgItemInt(hDlg, IDC_PW, pW, true);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK )
        {
            pN = GetDlgItemInt(hDlg, IDC_PN, 0, true);
            pW = GetDlgItemInt(hDlg, IDC_PW, 0, true);
            pN = pN > 100 ? 100 : pN;
            pN = pN < 0 ? 0 : pN;
            pW = pW > 100 ? 100 : pW;
            pW = pW < 0 ? 0 : pW;

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



