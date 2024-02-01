// Owner Draw.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Owner Draw.h"

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
INT_PTR CALLBACK    CarsDlg(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_OWNERDRAW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OWNERDRAW));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OWNERDRAW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OWNERDRAW);
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
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_LBUTTONDOWN:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_OWNERDRAW), hWnd, CarsDlg);
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

int cars[] = { 1, 2, 3 };

INT_PTR CALLBACK CarsDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int rowheight = 50;

    switch (message)
    {
    case WM_INITDIALOG:
    {

        HWND carlist = GetDlgItem(hDlg, IDC_CARS);

       

        ComboBox_AddString(carlist, L"1\0");
        ComboBox_AddString(carlist, L"2\0");
        ComboBox_AddString(carlist, L"3\0");



        return (INT_PTR)TRUE;
    }
    case WM_MEASUREITEM:
    {



        LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT)lParam;
        lpmis->itemHeight = rowheight;

        return (INT_PTR)TRUE;
    }
    case WM_DRAWITEM:
    {
        // lParam contains a pointer to a struct containing vital information
        // for our drawing
        LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
        if (lpdis->itemID == -1) // Empty item
            break;


        WCHAR* identifier = (WCHAR*)lpdis->itemData;

        WCHAR text[25];
        wsprintf(text, L"Car %s\0", identifier);

        TEXTMETRIC tm;
        GetTextMetrics(lpdis->hDC, &tm);
        int y = (lpdis->rcItem.bottom + lpdis->rcItem.top - tm.tmHeight) / 2;
        int x = LOWORD(GetDialogBaseUnits()) / 2;
        ExtTextOut(lpdis->hDC, 125 + x, y, ETO_CLIPPED | ETO_OPAQUE, &lpdis->rcItem, text, wcsnlen_s(text, 10), NULL);

        int z = 1;
        switch (*identifier) {
        case '1':
            z = IDB_CAR1;
            break;
        case '2':
            z = IDB_CAR2;
            break;
        case '3':
            z = IDB_CAR3;
            break;
        }

        HBITMAP bmp = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(z), IMAGE_BITMAP, 0, 0, 0);
        BITMAP b;
        GetObject(bmp, sizeof(BITMAP), &b);
        int width = b.bmWidth;
        int height = b.bmHeight;

        int dstwidth = width * rowheight / height;

        HDC hdc = CreateCompatibleDC(lpdis->hDC);
        SelectBitmap(hdc, bmp);
        StretchBlt(lpdis->hDC, 1, lpdis->rcItem.top, dstwidth, rowheight , hdc, 0, 0, width, height, SRCCOPY);

        if (lpdis->itemState & ODS_FOCUS) DrawFocusRect(lpdis->hDC, &lpdis->rcItem);


        DeleteDC(hdc);
        DeleteObject(bmp);



        return (INT_PTR)TRUE;
    }
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