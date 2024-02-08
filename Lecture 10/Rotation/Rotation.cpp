// 
// This demo shows rotation of a drwaing in GDI using PlgBlt
// 
// To be able to show the various versions on screen, there
// is a bunch of calculations here which can be confuding to follow
// The rotation of the "main" car on screen happens at line 300.
// I recommend you start looking at the code there if you just want
// to see how the rotation works.
// // 
//

#include "framework.h"
#include "Rotation.h"

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
    LoadStringW(hInstance, IDC_ROTATION, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROTATION));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROTATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROTATION);
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
      10, 10, 980, 660, nullptr, nullptr, hInstance, nullptr);

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

    static HDC carDC;
    static HBITMAP carBMP;
    static RECT car;
    static int rotation = 0;

    switch (message)
    {
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_UP:
        case VK_RIGHT:
            rotation = rotation < 359 ? rotation + 1 : 0;
            break;
        case VK_LEFT:
        case VK_DOWN:
            rotation = rotation > 0 ? rotation - 1 : 359;
            break;
        }
        InvalidateRect(hWnd, 0, false);
        break;
    case WM_CREATE:
    {
        HDC hdc = GetDC(hWnd);

        carDC = CreateCompatibleDC(hdc);
        carBMP = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_CAR), IMAGE_BITMAP, 0, 0, 0);
        SelectObject(carDC, carBMP);

        BITMAP b;
        GetObject(carBMP, sizeof(BITMAP), &b);
        car.right = b.bmWidth;
        car.bottom = b.bmHeight;

        ReleaseDC(hWnd, hdc);
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
            if (!carDC) return 0; // Can't draw if the memory DC hasn't been initialized

            PAINTSTRUCT ps;
            HDC screenDC = BeginPaint(hWnd, &ps);
            HDC hdc = CreateCompatibleDC(screenDC);

            RECT client;
            GetClientRect(hWnd,&client);

            HBITMAP bmp = CreateCompatibleBitmap(screenDC,client.right, client.bottom);
            SelectObject(hdc, bmp);
            Rectangle(hdc, client.left, client.top, client.right, client.bottom);


            int paneDim = max(car.right, car.bottom) + 150;
            HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
            HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));


            WCHAR rotText[255];
            wsprintf(rotText, L"Rotation: %d degrees. Use the arrow keys to rotate car.", rotation);
            TextOut(hdc, 10, paneDim, rotText, wcsnlen_s(rotText, 100));


            // Drawing the basic car

            int left = 0;
            int top = 0;

            Rectangle(hdc, left + 0, top + 0, left + paneDim, top + paneDim);
            BitBlt(hdc, left + (paneDim-car.right)/2, top + (paneDim-car.bottom)/2, car.right, car.bottom, carDC, 0, 0, SRCCOPY);

            TextOut(hdc, left + 10, top + paneDim - 20, L"Original Car",12);


            // Draw car with helper nodes
            left += paneDim;
            top += 0;

            Rectangle(hdc, left + 0, top + 0, left + paneDim, top + paneDim);
            BitBlt(hdc, left + (paneDim - car.right) / 2, top + (paneDim - car.bottom) / 2, car.right, car.bottom, carDC, 0, 0, SRCCOPY);

            POINT node1TopLeft = { left + (paneDim - car.right) / 2 , top + (paneDim - car.bottom) / 2 };
            POINT node2TopRight = { left + car.right + (paneDim - car.right) / 2, top + (paneDim - car.bottom) / 2 };
            POINT node3BottomLeft = { left + (paneDim - car.right) / 2 , top + car.bottom + (paneDim - car.bottom) / 2 };

            MoveToEx(hdc, node3BottomLeft.x, node3BottomLeft.y, 0);
            LineTo(hdc, node1TopLeft.x, node1TopLeft.y);
            LineTo(hdc, node2TopRight.x, node2TopRight.y);


            HGDIOBJ hOrg = SelectObject(hdc, redBrush);
            Ellipse(hdc, node1TopLeft.x -5, node1TopLeft.y - 5, node1TopLeft.x + 5, node1TopLeft.y + 5);
            SelectObject(hdc, greenBrush);
            Ellipse(hdc, node2TopRight.x - 5, node2TopRight.y - 5, node2TopRight.x + 5, node2TopRight.y + 5);
            SelectObject(hdc, blueBrush);
            Ellipse(hdc, node3BottomLeft.x - 5, node3BottomLeft.y - 5, node3BottomLeft.x + 5, node3BottomLeft.y + 5);

            TextOut(hdc, left + 10, top + paneDim - 35, L"Car with Guides", 15);
            TextOut(hdc, left + 10, top + paneDim - 20, L"Coordinates from source image", 29);

            WCHAR coords[12];

            wsprintf(coords, L"(%d,%d)", car.left, car.top);
            TextOut(hdc, node1TopLeft.x + 5, node1TopLeft.y - 10, coords, wcsnlen_s(coords, 12));
            wsprintf(coords, L"(%d,%d)", car.right, car.top);
            TextOut(hdc, node2TopRight.x + 5, node2TopRight.y - 10, coords, wcsnlen_s(coords, 12));
            wsprintf(coords, L"(%d,%d)", car.left, car.bottom);
            TextOut(hdc, node3BottomLeft.x + 5, node3BottomLeft.y - 10, coords, wcsnlen_s(coords, 12));



            // draw (non-rotated) car with destination(rotated) coordinates
            left += paneDim;
            top += 0;

            SelectObject(hdc, hOrg);
            Rectangle(hdc, left + 0, top + 0, left + paneDim, top + paneDim);
            BitBlt(hdc, left + (paneDim - car.right) / 2, top + (paneDim - car.bottom) / 2, car.right, car.bottom, carDC, 0, 0, SRCCOPY);


            node1TopLeft = { left + (paneDim - car.right) / 2 , top + (paneDim - car.bottom) / 2 };
            node2TopRight = { left + car.right + (paneDim - car.right) / 2, top + (paneDim - car.bottom) / 2 };
            node3BottomLeft = { left + (paneDim - car.right) / 2 , top + car.bottom + (paneDim - car.bottom) / 2 };

            MoveToEx(hdc, node3BottomLeft.x, node3BottomLeft.y, 0);
            LineTo(hdc, node1TopLeft.x, node1TopLeft.y);
            LineTo(hdc, node2TopRight.x, node2TopRight.y);


            SelectObject(hdc, redBrush);
            Ellipse(hdc, node1TopLeft.x - 5, node1TopLeft.y - 5, node1TopLeft.x + 5, node1TopLeft.y + 5);
            SelectObject(hdc, greenBrush);
            Ellipse(hdc, node2TopRight.x - 5, node2TopRight.y - 5, node2TopRight.x + 5, node2TopRight.y + 5);
            SelectObject(hdc, blueBrush);
            Ellipse(hdc, node3BottomLeft.x - 5, node3BottomLeft.y - 5, node3BottomLeft.x + 5, node3BottomLeft.y + 5);

            
            TextOut(hdc, left + 10, top + paneDim - 35, L"Car with Guides, coordinates matching rotation", 46);
            TextOut(hdc, left + 10, top + paneDim - 20, L"Coordinates in destination display", 34);



            left = paneDim * 3 / 2;
            top = paneDim;
            POINT origCenter = { car.right / 2, car.bottom / 2 };
            POINT destCenter = { left + paneDim / 2, top + paneDim / 2 };
            double radRot = rotation * M_PI / 180;


            wsprintf(coords, L"(%d,%d)", (int)((car.left - origCenter.x)* cos(radRot) - (car.top - origCenter.y) * sin(radRot) + destCenter.x), (int)((car.left - origCenter.x)* sin(radRot) + (car.top - origCenter.y) * cos(radRot) + destCenter.y));
            TextOut(hdc, node1TopLeft.x + 5, node1TopLeft.y - 10, coords, wcsnlen_s(coords, 12));
            wsprintf(coords, L"(%d,%d)", (int)((car.right - origCenter.x)* cos(radRot) - (car.top - origCenter.y) * sin(radRot) + destCenter.x), (int)((car.right - origCenter.x)* sin(radRot) + (car.top - origCenter.y) * cos(radRot) + destCenter.y));
            TextOut(hdc, node2TopRight.x + 5, node2TopRight.y - 10, coords, wcsnlen_s(coords, 12));
            wsprintf(coords, L"(%d,%d)", (int)((car.left - origCenter.x)* cos(radRot) - (car.bottom - origCenter.y) * sin(radRot) + destCenter.x), (int)((car.left - origCenter.x)* sin(radRot) + (car.bottom - origCenter.y) * cos(radRot) + destCenter.y));
            TextOut(hdc, node3BottomLeft.x + 5, node3BottomLeft.y - 10, coords, wcsnlen_s(coords, 12));






            // *************
            // Draw rotated car - This is the main part of the example
            // *************

            left = paneDim / 2;
            top = paneDim;


            // Time for trigonometry.
            // I want to rotate the car along it's center, so we need to take that into account
            // Furthermore, the car will be translated to a new location in the destination DC
            // The coordinates for any given point should then be
            // x = (orgX - origCenter.X) * cos(rotationAngle) - (orgY - OrigCenter.Y) * sin(rotationAngle) + destCenter.X
            // y = (orgX - origCenter.X) * sin(rotationAngle) + (orgY - OrigCenter.Y) * cos(rotationAngle) + destCenter.X

            origCenter = { car.right / 2, car.bottom / 2 }; // Center of car in the image in carDC (Loaded in WM_CREATE)
            destCenter = { left + paneDim/2, top + paneDim /2  }; // Position for the center of the car on screen

            radRot = rotation * M_PI / 180; // Converting angle to radians

            // Here we calculate the rotated locations of the three key points on the car (These variables are POINT's)
            node1TopLeft.x = (car.left - origCenter.x) * cos(radRot) - (car.top - origCenter.y) * sin(radRot) + destCenter.x;
            node1TopLeft.y = (car.left - origCenter.x) * sin(radRot) + (car.top - origCenter.y) * cos(radRot) + destCenter.y;
            
            node2TopRight.x = (car.right - origCenter.x) * cos(radRot) - (car.top - origCenter.y) * sin(radRot) + destCenter.x;
            node2TopRight.y = (car.right - origCenter.x) * sin(radRot) + (car.top - origCenter.y) * cos(radRot) + destCenter.y;

            node3BottomLeft.x = (car.left - origCenter.x) * cos(radRot) - (car.bottom - origCenter.y) * sin(radRot) + destCenter.x;
            node3BottomLeft.y = (car.left - origCenter.x) * sin(radRot) + (car.bottom - origCenter.y) * cos(radRot) + destCenter.y;

            POINT pos[3] = { node1TopLeft,node2TopRight, node3BottomLeft };

            // Copy the image from carDC and rotate it according to our specs
            PlgBlt(hdc, pos, carDC, 0, 0, car.right, car.bottom, 0, 0, 0);


            // ****************
            // End main example
            // ****************




            // Draw rotated car with guides


            left = paneDim * 3 / 2;
            top = paneDim;



            origCenter = { car.right / 2, car.bottom / 2 };
            destCenter = { left + paneDim / 2, top + paneDim / 2 };

            radRot = rotation * M_PI / 180;

            node1TopLeft.x = (car.left - origCenter.x) * cos(radRot) - (car.top - origCenter.y) * sin(radRot) + destCenter.x;
            node1TopLeft.y = (car.left - origCenter.x) * sin(radRot) + (car.top - origCenter.y) * cos(radRot) + destCenter.y;

            node2TopRight.x = (car.right - origCenter.x) * cos(radRot) - (car.top - origCenter.y) * sin(radRot) + destCenter.x;
            node2TopRight.y = (car.right - origCenter.x) * sin(radRot) + (car.top - origCenter.y) * cos(radRot) + destCenter.y;

            node3BottomLeft.x = (car.left - origCenter.x) * cos(radRot) - (car.bottom - origCenter.y) * sin(radRot) + destCenter.x;
            node3BottomLeft.y = (car.left - origCenter.x) * sin(radRot) + (car.bottom - origCenter.y) * cos(radRot) + destCenter.y;


            pos[0] = node1TopLeft; pos[1] = node2TopRight; pos[2] = node3BottomLeft;

            PlgBlt(hdc, pos, carDC, 0, 0, car.right, car.bottom, 0, 0, 0);

            MoveToEx(hdc, node3BottomLeft.x, node3BottomLeft.y, 0);
            LineTo(hdc, node1TopLeft.x, node1TopLeft.y);
            LineTo(hdc, node2TopRight.x, node2TopRight.y);


            SelectObject(hdc, redBrush);
            Ellipse(hdc, node1TopLeft.x - 5, node1TopLeft.y - 5, node1TopLeft.x + 5, node1TopLeft.y + 5);
            SelectObject(hdc, greenBrush);
            Ellipse(hdc, node2TopRight.x - 5, node2TopRight.y - 5, node2TopRight.x + 5, node2TopRight.y + 5);
            SelectObject(hdc, blueBrush);
            Ellipse(hdc, node3BottomLeft.x - 5, node3BottomLeft.y - 5, node3BottomLeft.x + 5, node3BottomLeft.y + 5);




            BitBlt(screenDC, 0, 0, client.right, client.bottom, hdc, 0, 0, SRCCOPY);
            DeleteDC(hdc);
            DeleteObject(bmp);


            SelectObject(hdc, hOrg);
            DeleteObject(redBrush);
            DeleteObject(greenBrush);
            DeleteObject(blueBrush);

            
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        DeleteDC(carDC);
        DeleteObject(carBMP);

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
