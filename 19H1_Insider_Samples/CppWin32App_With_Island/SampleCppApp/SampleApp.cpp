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

struct MyWindow : DesktopWindowT<MyWindow>
{
    HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
    {
        hInst = hInstance; // Store instance handle in our global variable
        HWND hMainWnd = CreateWindow(
            szWindowClass,
            szTitle,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, InitialWidth, InitialHeight,
            nullptr, nullptr, hInstance, this);

        if (!hMainWnd)
        {
            winrt::check_hresult(E_FAIL);
        }

        ShowWindow(hMainWnd, nCmdShow);
        UpdateWindow(hMainWnd);
        SetFocus(hMainWnd);
        return hMainWnd;
    }

    MyWindow(HINSTANCE hInstance, int nCmdShow) noexcept
    {
        LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadStringW(hInstance, IDC_SAMPLECPPAPP, szWindowClass, MAX_LOADSTRING);

        WNDCLASSEXW wcex = {};
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
        WINRT_VERIFY(RegisterClassEx(&wcex));
        WINRT_ASSERT(!m_hMainWnd);

        m_hMainWnd = InitInstance(hInstance, nCmdShow);
        WINRT_ASSERT(m_hMainWnd);
    }

    LRESULT MessageHandler(UINT const message, WPARAM const wParam, LPARAM const lParam) noexcept
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
                m_hMainWnd, (HMENU)IDM_ButtonID1, hInst, NULL);

            DEVICE_SCALE_FACTOR scaleFactor = {};
            winrt::check_hresult(GetScaleFactorForMonitor(MonitorFromWindow(m_hMainWnd, 0), &scaleFactor));
            const auto dpi = static_cast<int>(scaleFactor) / 100.0f;

            const auto bt1 = LoadXamlControl<winrt::Windows::UI::Xaml::Controls::Button>(IDR_XAML_BUTTON1);
            bt1.Height(ButtonHeight / dpi);
            bt1.Width(ButtonWidth / dpi);
            hWndXamlButton1 = CreateDesktopWindowsXamlSource(WS_TABSTOP, bt1);

            mainUserControl = winrt::MyApp::MainUserControl();
            hWndXamlIsland = CreateDesktopWindowsXamlSource(WS_TABSTOP, mainUserControl);

            hButton2 = CreateWindow(TEXT("button"), TEXT("Button &2"),
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
                (ButtonMargin + InitialWidth - ButtonWidth) / 2, InitialHeight - ButtonMargin - ButtonHeight,
                ButtonWidth, ButtonHeight,
                m_hMainWnd, (HMENU)IDM_ButtonID2, hInst, NULL);
        }
        break;
        case WM_COMMAND:
        {
            const auto wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), m_hMainWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(m_hMainWnd);
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
                return base_type::MessageHandler(message, wParam, lParam);
            }
        }
        break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hMainWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(m_hMainWnd, &ps);
        }
        break;
        case WM_DESTROY:
            DestroyWindow(hButton1);
            hButton1 = nullptr;

            DestroyWindow(hButton2);
            hButton2 = nullptr;

            break;
        case WM_SIZE:
        {
            const auto newHeight = HIWORD(lParam);
            const auto newWidth = LOWORD(lParam);
            const auto islandHeight = newHeight - (ButtonHeight * 2) - ButtonMargin;
            const auto islandWidth = newWidth - (ButtonMargin * 2);
            SetWindowPos(hButton1, 0, ButtonWidth * 2, ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
            SetWindowPos(hWndXamlButton1, hButton1, newWidth - (ButtonWidth * 2), ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
            SetWindowPos(hWndXamlIsland, hWndXamlButton1, 0, XamlIslandMargin, islandWidth, islandHeight, SWP_SHOWWINDOW);
            SetWindowPos(hButton2, hWndXamlIsland, (ButtonMargin + newWidth - ButtonWidth) / 2, newHeight - ButtonMargin - ButtonHeight, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
        }
        break;
        default:
            return base_type::MessageHandler(message, wParam, lParam);
        }
        return base_type::MessageHandler(message, wParam, lParam);
    }
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    winrt::init_apartment(winrt::apartment_type::single_threaded);
    winrt::MyApp::App app;

    MyWindow myWindow(hInstance, nCmdShow);
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLECPPAPP));
    int retValue = myWindow.MessageLoop(hAccelTable);

    app.Close();
    app = nullptr;
    return retValue;
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
