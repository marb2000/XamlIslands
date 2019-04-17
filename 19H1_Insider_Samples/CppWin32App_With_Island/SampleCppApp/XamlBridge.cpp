#include "pch.h"

#include "XamlBridge.h"
#include "Resource.h"
#include "SampleApp.h"

extern HWND hWndXamlIsland;

void OnTakeFocusRequested(winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource const& /* sender */, winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSourceTakeFocusRequestedEventArgs const& args)
{
	const WPARAM wParam = (args.Request().Reason() == winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::First) ? 1 : 0;
	::SendMessage(hMainWnd, WM_MOVEFOCUS, wParam, 0);
}

winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource CreateDesktopWindowsXamlSource(HWND parentWindow)
{
    HRESULT hr = S_OK;

    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource;

    // Get handle to corewindow
    auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
    // Parent the DesktopWindowXamlSource object to current window
    hr = interop->AttachToWindow(parentWindow);
    winrt::check_hresult(hr);

    // Get the new child window's hwnd 
    hr = interop->get_WindowHandle(&hWndXamlIsland);
    winrt::check_hresult(hr);
	DWORD dwNewStyle = GetWindowLong(hWndXamlIsland, GWL_STYLE);
	dwNewStyle |= WS_TABSTOP;
	SetWindowLong(hWndXamlIsland, GWL_STYLE, dwNewStyle);

	PostMessage(parentWindow, WM_SIZE, 0, MAKELPARAM(InitialWidth, InitialHeight));

    winrt::MyApp::MainUserControl mainUserControl;
    mainUserControl.UpdateLayout();
    desktopSource.Content(mainUserControl);

	desktopSource.TakeFocusRequested(OnTakeFocusRequested);

    return desktopSource;
}

