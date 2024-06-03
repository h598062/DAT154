//
// Traffic Light Simulator
//
// This is an Object-Oriented approach to the traffic-light sim.
// This version is spread over more files and utilizes .h files
// to a greater degree, and also uses helper functions.
// The main logic is exactly the same as the non-oo version.
// 
// There is a lot that can be done to make this prettier, but it shows
// a basic solution fulfilling all requirements


#include "framework.h"
#include "TrafficLightExampleObjectOriented.h"
#include "TrafficSim.h"



// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

TrafficSim* tfs;



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
    LoadStringW(hInstance, IDC_TRAFFICLIGHTEXAMPLEOBJECTORIENTED, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRAFFICLIGHTEXAMPLEOBJECTORIENTED));

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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRAFFICLIGHTEXAMPLEOBJECTORIENTED));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TRAFFICLIGHTEXAMPLEOBJECTORIENTED);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        tfs = new TrafficSim();
        tfs->Start(hWnd);
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

        RECT screen;
        GetClientRect(hWnd, &screen);

        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP memBitmap = CreateCompatibleBitmap(hdc, screen.right, screen.bottom);
        SelectObject(memDC, memBitmap);

        tfs->Draw(memDC, hWnd);

        BitBlt(hdc, screen.left, screen.top, screen.right, screen.bottom, memDC, 0, 0, SRCCOPY);

        DeleteObject(memBitmap);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);

    }
    break;
    case WM_TIMER:
    {
        switch (wParam) {
        case TIMER_LIGHTS:
            tfs->NextLightstate(hWnd);
            break;
        case TIMER_CARS:
        {
            tfs->MoveCars(hWnd);
            break;
        }
        case TIMER_ADD_CARS:

            tfs->SpawnCars(hWnd);

            break;
        }

        break;

    }
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_LEFT:
            tfs->ChangeSpawnrate(-5, 'W');
             break;
        case VK_RIGHT:
            tfs->ChangeSpawnrate(5, 'W');
            break;
        case VK_DOWN:
            tfs->ChangeSpawnrate(-5, 'N');
            break;
        case VK_UP:
            tfs->ChangeSpawnrate(5, 'N');
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
        tfs->NextLightstate(hWnd);
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
        SetDlgItemInt(hDlg, IDC_PN, tfs->GetSpawnrate('N'), true);
        SetDlgItemInt(hDlg, IDC_PW, tfs->GetSpawnrate('W'), true);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            tfs->SetSpawnrate(GetDlgItemInt(hDlg, IDC_PN, 0, true), 'N');
            tfs->SetSpawnrate(GetDlgItemInt(hDlg, IDC_PW, 0, true), 'W');

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



