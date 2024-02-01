// Messages
// 
// This demo demonstrate two main things
// 1. How to use the different mouse messages combined with WM_PAINT
// to provide simple drawing functions with preview
// 2. How to send messages to other programs
//

#include "framework.h"
#include "Messages.h"
#include <vector>

#define MAX_LOADSTRING 100

struct LINE{
    POINT p1;
    POINT p2;
    COLORREF color = RGB(0, 0, 150);
};


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::vector<LINE> lines;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




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
    LoadStringW(hInstance, IDC_MESSAGES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MESSAGES));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MESSAGES));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MESSAGES);
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
      CW_USEDEFAULT, 0, 500, 400, nullptr, nullptr, hInstance, nullptr);

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
    static BOOL isMouseButtonDown;
    static LINE previewLine;
    static BOOL color;

    switch (message)
    {
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
                if (MessageBox(hWnd, L"Do you wish to quit?", L"Quit?", MB_YESNO) == IDYES) {
                    DestroyWindow(hWnd);
                }
                break;
            case MENU_START:
            {
                WCHAR filePath[255] = L"notepad.exe";
                ShellExecute(NULL, L"open", filePath, NULL, NULL, SW_SHOWNORMAL);

                break;
            }
            case MENU_WM_CLOSE:
            {
                // Tells notepad nicely that we want to close the window
                // If we have unsaved changes, it will ask you before closing
                HWND hNotepad = FindWindow(L"Notepad", NULL);
                PostMessage(hNotepad, WM_CLOSE, 0, 0);
                break;
            }
            case MENU_WM_DESTROY:
            {
                // Hitting harder. This just close the window and force the application to quit
                HWND hNotepad = FindWindow(L"Notepad", NULL);
                PostMessage(hNotepad, WM_DESTROY, 0, 0);
                break;
            }
            case MENU_WM_QUIT:
            {
                // Who cares about closing windows. Let's just hit the application instead
                HWND hNotepad = FindWindow(L"Notepad", NULL);
                PostMessage(hNotepad, WM_QUIT, 0, 0);
                break;
            }
            case MENU_MAXIMIZE:
            {
                HWND hNotepad = FindWindow(L"Notepad", NULL);
                PostMessage(hNotepad, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
                break;
            }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN:
        isMouseButtonDown = true;
        previewLine.p1.x = GET_X_LPARAM(lParam);
        previewLine.p1.y = GET_Y_LPARAM(lParam);
        break;
    case WM_LBUTTONUP:
        isMouseButtonDown = false;
        previewLine.p2.x = GET_X_LPARAM(lParam);
        previewLine.p2.y = GET_Y_LPARAM(lParam);
        if (color) {
            previewLine.color = RGB(170, 0, 0);
        } else {
            previewLine.color = RGB(0, 0, 150);
        }
        lines.push_back(previewLine);
        InvalidateRect(hWnd, 0, false);
        break;
    case WM_MOUSEMOVE:
        if (!isMouseButtonDown) break;
        previewLine.p2.x = GET_X_LPARAM(lParam);
        previewLine.p2.y = GET_Y_LPARAM(lParam);

        RECT area;
        area.left = min(previewLine.p1.x, previewLine.p2.x) - 10;
        area.right = max(previewLine.p1.x, previewLine.p2.x) + 10;
        area.top = min(previewLine.p1.y, previewLine.p2.y) - 10;
        area.bottom = max(previewLine.p1.y, previewLine.p2.y) + 10;

        InvalidateRect(hWnd, &area, true);
        break;
    case WM_RBUTTONUP:
        color = !color;
        break;
    case WM_CLOSE:

        if (MessageBox(hWnd, L"Do you wish to quit?", L"Quit?", MB_YESNO) == IDYES) {
            DestroyWindow(hWnd);
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            WCHAR msg[255] = L"Try holding down the mouse button and move the mouse to draw lines";
            TextOut(hdc, 10, 20, msg, wcsnlen_s(msg, 254));

            

            if (isMouseButtonDown) {
                MoveToEx(hdc, previewLine.p1.x, previewLine.p1.y, 0);
                LineTo(hdc, previewLine.p2.x, previewLine.p2.y);
            }



            auto it = lines.begin();
            while (it != lines.end()) {
                HPEN pen = CreatePen(PS_SOLID, 3, it->color);
                HGDIOBJ hOrg = SelectObject(hdc, pen);

                MoveToEx(hdc, it->p1.x, it->p1.y, 0);
                LineTo(hdc, it->p2.x, it->p2.y);

                SelectObject(hdc, hOrg);
                DeleteObject(pen);
                it++;
            }




            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
