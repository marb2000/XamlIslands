// SampleCppApp.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "SampleApp.h"
#include "XamlBridge.h"
#include "..\Microsoft.UI.Xaml.Markup\Generated Files\Microsoft.UI.Xaml.Markup.XamlApplication.g.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst = nullptr; // current instance
HWND hMainWnd = nullptr;
// This Hwnd will be the window handler for the Xaml Island: A child window that contains Xaml.  
HWND hWndXamlIsland = nullptr;
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
    winrt::Microsoft::UI::Xaml::Markup::XamlApplication app;
    app.RequestedTheme(winrt::Windows::UI::Xaml::ApplicationTheme::Light);

    int retValue = 0;
    {
        // Initialize global strings
        LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadStringW(hInstance, IDC_SAMPLECPPAPP, szWindowClass, MAX_LOADSTRING);
        MyRegisterClass(hInstance);

        // Perform application initialization:
        auto desktopSource = InitInstance(hInstance, nCmdShow);
        auto desktopSourceNative2 = desktopSource.as<IDesktopWindowXamlSourceNative2>();
        HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLECPPAPP));
        MSG msg = {};
        HRESULT hr = S_OK;

        // Main message loop:
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            BOOL processMessage = FALSE;
            // When multiple child windows are present it is needed to pre dispatch messages to all 
            // DesktopWindowXamlSource instances so keyboard accelerators and 
            // keyboard focus work correctly.
            hr = desktopSourceNative2->PreTranslateMessage(&msg, &processMessage);
            winrt::check_hresult(hr);
            if (!processMessage && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        hWndXamlIsland = nullptr;
        retValue = (int)msg.wParam;
        desktopSource.Close();
    }
    app.Close();

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
    wcex.cbClsExtra = 0;
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
winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable
    hMainWnd = CreateWindow(
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

    auto desktopXamlSource = CreateDesktopWindowsXamlSource(hMainWnd);

    return desktopXamlSource;
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
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        {
            if (hMainWnd == hWnd && hWndXamlIsland!=nullptr)
            {
                auto newHeight = LOWORD(lParam);
                auto newWidth = HIWORD(lParam);
                const auto margin = XamlIslandMargin;
                SetWindowPos(hWndXamlIsland, 0, margin, margin, newHeight - margin, newWidth - margin, SWP_SHOWWINDOW);
            }
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
