// SampleCppApp.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "SampleApp.h"
#include "XamlBridge.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst = nullptr; // current instance
HWND hMainWnd = nullptr;
// This Hwnd will be the window handler for the Xaml Island: A child window that contains Xaml.  
HWND hWndXamlIsland = nullptr;
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopXamlSource(nullptr);


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

        {
            std::vector<winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource> xamlSources;
            // Perform application initialization
			desktopXamlSource = InitInstance(hInstance, nCmdShow);
            xamlSources.push_back(desktopXamlSource);
    
            HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLECPPAPP));
            MSG msg = {};
            HRESULT hr = S_OK;
            // Main message loop:
            while (GetMessage(&msg, nullptr, 0, 0))
            {
                // When multiple child windows are present it is needed to pre dispatch messages to all 
                // DesktopWindowXamlSource instances so keyboard accelerators and 
                // keyboard focus work correctly.
                BOOL xamlSourceProcessedMessage = FALSE;
                {
                    for (auto xamlSource : xamlSources)
                    {
                        auto xamlSourceNative2 = xamlSource.as<IDesktopWindowXamlSourceNative2>();
                        hr = xamlSourceNative2->PreTranslateMessage(&msg, &xamlSourceProcessedMessage);
                        winrt::check_hresult(hr);
                        if (xamlSourceProcessedMessage)
                        {
                            break;
                        }
                    }
                }

                if (!xamlSourceProcessedMessage && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
                }
            }
            hWndXamlIsland = nullptr;
            retValue = (int)msg.wParam;
            for (auto xamlSource : xamlSources)
            {
                xamlSource.Close();
            }
			desktopXamlSource = nullptr;
            xamlSources.clear();
        }
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

const auto static invalidReason = static_cast<winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason>(-1);

winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason GetReasonFromKey(WPARAM key)
{
	auto reason = invalidReason;
	if (key == VK_TAB)
	{
		byte keyboardState[256] = {};
		::GetKeyboardState(keyboardState);
		reason = (keyboardState[VK_SHIFT] & 0x80) ? winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Last : reason;
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

	switch (message)
    {
	case WM_CREATE:
		hButton1 = CreateWindow(TEXT("button"), TEXT("Button1"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
			(ButtonMargin + InitialWidth - ButtonWidth)/2, ButtonMargin, ButtonWidth, ButtonHeight,
			hWnd, buttonID1, hInst, NULL);
		hButton2 = CreateWindow(TEXT("button"), TEXT("Button2"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
			(ButtonMargin + InitialWidth - ButtonWidth) / 2, ButtonMargin + InitialHeight, ButtonWidth, ButtonHeight,
			hWnd, buttonID2, hInst, NULL);
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
		DestroyWindow(hButton2);
		PostQuitMessage(0);
        break;
	case WM_ISDIALOGKEY:
	{
		const MSG* msg = reinterpret_cast<MSG*>(lParam);
		if (msg && msg->message == WM_KEYDOWN)
		{
			const auto hFocusedWindow = GetParent(::GetFocus());
			if (hFocusedWindow == hWndXamlIsland)
			{
				const auto key = msg->wParam;
				auto reason = GetReasonFromKey(key);
				if (reason != invalidReason)
				{
					const auto result = desktopXamlSource.NavigateFocus(reason);
					return result.WasFocusMoved() ? 0 : -1;
				}
			}
		}
		break;
	}
	case WM_MOVEFOCUS:
	{
		const auto selectedWnd = (wParam == 1) ? hButton2 : hButton1;
		::SetFocus(selectedWnd);
		break;
	}
    case WM_SIZE:
        {
            if (hMainWnd == hWnd && hWndXamlIsland!=nullptr)
            {
				const auto newHeight = HIWORD(lParam);
				const auto newWidth = LOWORD(lParam);
				const auto islandHeight = newHeight - (ButtonHeight * 2) - ButtonMargin;
				const auto islandWidth = newWidth - (ButtonMargin * 2);
				SetWindowPos(hButton1, 0, (ButtonMargin + newWidth - ButtonWidth) / 2, ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
				SetWindowPos(hWndXamlIsland, hButton1, ButtonMargin, XamlIslandMargin, islandWidth, islandHeight, SWP_SHOWWINDOW);
				SetWindowPos(hButton2, hWndXamlIsland, (ButtonMargin + newWidth - ButtonWidth) / 2, newHeight - ButtonMargin - ButtonHeight, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
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
