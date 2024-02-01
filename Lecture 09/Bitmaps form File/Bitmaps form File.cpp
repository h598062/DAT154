// Bitmaps form File.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Bitmaps form File.h"
#define _USE_MATH_DEFINES
#include <Math.h>

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
    LoadStringW(hInstance, IDC_BITMAPSFORMFILE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BITMAPSFORMFILE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BITMAPSFORMFILE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BITMAPSFORMFILE);
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
        // Initialising GDI+. These 3 lines are NOT curriculum
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
        Gdiplus::Status status = Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
        break;
    }

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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            

            HBRUSH bg = CreateSolidBrush(RGB(0, 180, 0));
            HGDIOBJ hOrg = SelectObject(hdc, bg);
            RECT area;
            GetClientRect(hWnd, &area);
            Rectangle(hdc, 0, 0, area.right, area.bottom);
            SelectObject(hdc, hOrg);
            DeleteObject(bg);

            // Loading a bitmap via resource
            HBITMAP hbmp1 = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_CAR1), IMAGE_BITMAP, 0,0,0);

            HDC vdc = CreateCompatibleDC(hdc);
            SelectObject(vdc, hbmp1);

            BITMAP bmp;
            GetObject(hbmp1, sizeof(BITMAP), &bmp);
            int width = bmp.bmWidth;
            int height = bmp.bmHeight;


            BitBlt(hdc, 100, 100, width, height, vdc, 0, 0, SRCCOPY);

            StretchBlt(hdc, 300, 300, -width, height, vdc, 0, 0, width, height,SRCCOPY);
            


            // Loading bitmap straight from file
            HBITMAP hbmp2 = (HBITMAP)LoadImage(hInst, L"Car2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            SelectObject(vdc, hbmp2);

            GetObject(hbmp2, sizeof(BITMAP), &bmp);
            width = bmp.bmWidth;
            height = bmp.bmHeight;

            POINT origin = { 300,175 };
            POINT point[3] = { {origin.x,origin.y},{origin.x + width * cos(M_PI / 4),origin.y + width * sin(M_PI / 4)},{origin.x + height * cos(3*M_PI / 4),origin.y + height * sin(3*M_PI / 4)} };
            PlgBlt(hdc, point, vdc, 0, 0, width, height, NULL, NULL, NULL);



            // Diving into GDI+ territory now. GDI+ isn't curriculum, but it is needed
            // for prettier drawings so I'll just show it off here.
            // There's nothing that special about GDI+ of course, we're still working with the SDK
            // so the following should still be familiar
            // Look in WM_CREATE for some required GDI+ initialization, and the .h files for GDI+ headers required

            TransparentBlt(hdc, 50, 200, width, height, vdc, 0, 0, width, height, RGB(255, 255, 255));

            Gdiplus::Bitmap * bmp3 = new Gdiplus::Bitmap(L"Car3.png", false);
            HBITMAP hbmp3;
            bmp3->GetHBITMAP(Gdiplus::Color::AlphaMask, &hbmp3);
            SelectObject(vdc,hbmp3);

            width = bmp3->GetWidth();
            height = bmp3->GetHeight();

            BLENDFUNCTION blendF;
            blendF.BlendOp = AC_SRC_OVER;
            blendF.BlendFlags = 0;
            blendF.SourceConstantAlpha = 255;
            blendF.AlphaFormat = AC_SRC_ALPHA;

            AlphaBlend(hdc, 275, 100, width, height, vdc, 0, 0, width, height, blendF);

            // End GDI+ stuff


            
            DeleteDC(vdc);
            DeleteObject(hbmp1);
            DeleteObject(hbmp2);
            DeleteObject(hbmp3);
            delete bmp3;

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
