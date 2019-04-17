#include "pch.h"
#include "framework.h"
#include "SampleApp.h"
#include "XamlBridge.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst = nullptr; // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::vector<winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource> xamlSources;

bool FilterMessage(const MSG* msg)
{
    // When multiple child windows are present it is needed to pre dispatch messages to all 
    // DesktopWindowXamlSource instances so keyboard accelerators and 
    // keyboard focus work correctly.
    BOOL xamlSourceProcessedMessage = FALSE;
    {
        for (auto xamlSource : xamlSources)
        {
            auto xamlSourceNative2 = xamlSource.as<IDesktopWindowXamlSourceNative2>();
            const auto hr = xamlSourceNative2->PreTranslateMessage(msg, &xamlSourceProcessedMessage);
            winrt::check_hresult(hr);
            if (xamlSourceProcessedMessage)
            {
                break;
            }
        }
    }

    return !!xamlSourceProcessedMessage;
}

winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource GetFocusedIsland()
{
    for (auto xamlSource : xamlSources)
    {
        if (xamlSource.HasFocus())
        {
            return xamlSource;
        }
    }
    return nullptr;
}

const auto static invalidReason = static_cast<winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason>(-1);

winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason GetReasonFromKey(WPARAM key)
{
    auto reason = invalidReason;
    if (key == VK_TAB)
    {
        byte keyboardState[256] = {};
        WINRT_VERIFY(::GetKeyboardState(keyboardState));
        reason = (keyboardState[VK_SHIFT] & 0x80) ?
            winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Last :
            winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::First;
    }
    else if (key == VK_LEFT)
    {
        reason = winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Left;
    }
    else if (key == VK_RIGHT)
    {
        reason = winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Right;
    }
    else if (key == VK_UP)
    {
        reason = winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Up;
    }
    else if (key == VK_DOWN)
    {
        reason = winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Down;
    }
    return reason;
}

void NavigateFocus(HWND previousFocusedWindow, const MSG& msg)
{
    if (msg.message != WM_KEYDOWN)
    {
        return;
    }
    const auto focusedIsland = GetFocusedIsland();
    if (!focusedIsland)
    {
        return;
    }
    const auto key = msg.wParam;
    auto reason = GetReasonFromKey(key);
    if (reason != invalidReason)
    {
        RECT rect = {};
        WINRT_VERIFY(::GetWindowRect(previousFocusedWindow, &rect));
        const auto nativeIsland = focusedIsland.as<IDesktopWindowXamlSourceNative>();
        HWND islandWnd = nullptr;
        winrt::check_hresult(nativeIsland->get_WindowHandle(&islandWnd));
        POINT pt = { rect.left, rect.top };
        SIZE size = { rect.right - rect.left, rect.bottom - rect.top };
        ::ScreenToClient(islandWnd, &pt);
        const auto hintRect = winrt::Windows::Foundation::Rect({ static_cast<float>(pt.x), static_cast<float>(pt.y), static_cast<float>(size.cx), static_cast<float>(size.cy) });
        const auto request = winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationRequest(reason, hintRect);
        const auto result = focusedIsland.NavigateFocus(request);
        WINRT_VERIFY(result.WasFocusMoved());
    }
}

int MainMessageLoop(HWND hMainWnd, HACCEL hAccelTable)
{
    MSG msg = {};
    HRESULT hr = S_OK;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        const bool xamlSourceProcessedMessage = FilterMessage(&msg);
        if (!xamlSourceProcessedMessage && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            const auto previousFocusedWindow = ::GetFocus();
            const auto previousFocusedIsland = GetFocusedIsland();
            if (previousFocusedIsland || !IsDialogMessage(hMainWnd, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                NavigateFocus(previousFocusedWindow, msg);
            }
        }
    }

    return (int)msg.wParam;
}

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
    const static HMENU buttonID1 = (HMENU)0x1001;
    const static HMENU buttonID2 = (HMENU)0x1002;
    static HWND hButton2 = nullptr;
    static HWND hWndXamlIsland = nullptr;
    static winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopXamlSource;
    HRESULT hr = S_OK;

    switch (message)
    {
    case WM_CREATE:
        {
            hButton1 = CreateWindow(TEXT("button"), TEXT("Button1"),
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
                (ButtonMargin + InitialWidth - ButtonWidth) / 2, ButtonMargin,
                ButtonWidth, ButtonHeight,
                hWnd, buttonID1, hInst, NULL);

            hButton2 = CreateWindow(TEXT("button"), TEXT("Button2"),
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
                (ButtonMargin + InitialWidth - ButtonWidth) / 2, InitialHeight - ButtonMargin - ButtonHeight,
                ButtonWidth, ButtonHeight,
                hWnd, buttonID2, hInst, NULL);

            desktopXamlSource = CreateDesktopWindowsXamlSource(hWnd);
            const auto interop = desktopXamlSource.as<IDesktopWindowXamlSourceNative>();
            hr = interop->get_WindowHandle(&hWndXamlIsland);
            winrt::check_hresult(hr);
            xamlSources.push_back(desktopXamlSource);
        }
        break;
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
        DestroyWindow(hButton1);
        hButton1 = nullptr;

        DestroyWindow(hButton2);
        hButton2 = nullptr;

        desktopXamlSource = nullptr;
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
        SetWindowPos(hButton1, 0, (ButtonMargin + newWidth - ButtonWidth) / 2, ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
        SetWindowPos(hWndXamlIsland, hButton1, 0, XamlIslandMargin, islandWidth, islandHeight, SWP_SHOWWINDOW);
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
