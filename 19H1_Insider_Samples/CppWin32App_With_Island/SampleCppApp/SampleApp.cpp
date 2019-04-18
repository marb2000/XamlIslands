#include "pch.h"
#include "framework.h"
#include "SampleApp.h"
#include "XamlBridge.h"
#include <ShellScalingApi.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst = nullptr; // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    winrt::init_apartment(winrt::apartment_type::single_threaded);
    winrt::MyApp::App app;

    int retValue = 0;
    {
        // Initialize global strings
        LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadStringW(hInstance, IDC_SAMPLECPPAPP, szWindowClass, MAX_LOADSTRING);
        MyRegisterClass(hInstance);
        HWND hMainWnd = InitInstance(hInstance, nCmdShow);

        HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLECPPAPP));
        retValue = MainMessageLoop(hMainWnd, hAccelTable);
    }
    app.Close();
    app = nullptr;
    return retValue;
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
    wcex.cbClsExtra = DLGWINDOWEXTRA;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAMPLECPPAPP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SAMPLECPPAPP);
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
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable
    HWND hMainWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, InitialWidth, InitialHeight,
        nullptr, nullptr, hInstance, nullptr);

    if (!hMainWnd)
    {
        winrt::check_hresult(E_FAIL);
    }

    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);
    SetFocus(hMainWnd);
    return hMainWnd;
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
    static HWND hButton1 = nullptr;
    const static WPARAM IDM_ButtonID1 = 0x1001;
    const static WPARAM IDM_ButtonID2 = 0x1002;
    static HWND hButton2 = nullptr;
    static HWND hWndXamlIsland = nullptr;
    static HWND hWndXamlButton1 = nullptr;
    static winrt::MyApp::MainUserControl mainUserControl(nullptr);
    static float dpi = 0;
    HRESULT hr = S_OK;

    switch (message)
    {
    case WM_CREATE:
        {
            hButton1 = CreateWindow(TEXT("button"), TEXT("Button &1"),
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
                (ButtonMargin + InitialWidth - ButtonWidth) / 2, ButtonMargin,
                ButtonWidth, ButtonHeight,
                hWnd, (HMENU)IDM_ButtonID1, hInst, NULL);

            DEVICE_SCALE_FACTOR scaleFactor = {};
            winrt::check_hresult(GetScaleFactorForMonitor(MonitorFromWindow(hWnd, 0), &scaleFactor));
            const auto dpi = static_cast<int>(scaleFactor) / 100.0f;
            //const auto dip = GetWindowS
            winrt::Windows::UI::Xaml::Controls::TextBlock txt;
            txt.Text(winrt::hstring(L"Xbt1"));
            winrt::Windows::UI::Xaml::Controls::Button bt1;
            bt1.Height(ButtonHeight / dpi);
            bt1.Width(ButtonWidth / dpi);
            bt1.Content(txt);
            hWndXamlButton1 = CreateDesktopWindowsXamlSource(hWnd, WS_TABSTOP, bt1);

            mainUserControl = winrt::MyApp::MainUserControl();
            hWndXamlIsland = CreateDesktopWindowsXamlSource(hWnd, WS_TABSTOP, mainUserControl);

            hButton2 = CreateWindow(TEXT("button"), TEXT("Button &2"),
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
                (ButtonMargin + InitialWidth - ButtonWidth) / 2, InitialHeight - ButtonMargin - ButtonHeight,
                ButtonWidth, ButtonHeight,
                hWnd, (HMENU)IDM_ButtonID2, hInst, NULL);
        }
        break;
    case WM_COMMAND:
    {
        const auto wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_ButtonID1:
        case IDM_ButtonID2:
        {
            if (mainUserControl)
            {
                const auto string = (wmId == IDM_ButtonID1) ? winrt::hstring(L"Native button 1") : winrt::hstring(L"Native button 2");
                mainUserControl.MyProperty(string);
            }
        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_GETDLGCODE:
        return DefWindowProc(hWnd, message, wParam, lParam);
        //return DLGC_WANTALLKEYS;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        DestroyWindow(hButton1);
        hButton1 = nullptr;

        DestroyWindow(hButton2);
        hButton2 = nullptr;

        for (auto xamlSource : xamlSources)
        {
            xamlSource.Close();
        }
        xamlSources.clear();

        PostQuitMessage(0);
        break;
    case WM_SIZE:
    {
        const auto newHeight = HIWORD(lParam);
        const auto newWidth = LOWORD(lParam);
        const auto islandHeight = newHeight - (ButtonHeight * 2) - ButtonMargin;
        const auto islandWidth = newWidth - (ButtonMargin * 2);
        SetWindowPos(hButton1, 0, ButtonWidth * 2, ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
        SetWindowPos(hWndXamlButton1, hButton1, newWidth - (ButtonWidth *2), ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
        SetWindowPos(hWndXamlIsland, hWndXamlButton1, 0, XamlIslandMargin, islandWidth, islandHeight, SWP_SHOWWINDOW);
        SetWindowPos(hButton2, hWndXamlIsland, (ButtonMargin + newWidth - ButtonWidth) / 2, newHeight - ButtonMargin - ButtonHeight, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
    }
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
