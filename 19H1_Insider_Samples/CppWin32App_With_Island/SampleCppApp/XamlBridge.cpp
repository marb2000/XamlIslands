#include "pch.h"

#include "XamlBridge.h"
#include "Resource.h"
#include "SampleApp.h"

void OnTakeFocusRequested(winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource const& /* sender */, winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSourceTakeFocusRequestedEventArgs const& args)
{
    const auto reason = args.Request().Reason();
    const BOOL previous =
        (reason == winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::First ||
         reason == winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Down ||
         reason == winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Right) ? false : true;
    const auto nextElement = ::GetNextDlgTabItem(hMainWnd, hWndXamlIsland, previous);
    ::SetFocus(nextElement);
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

    PostMessage(parentWindow, WM_SIZE, 0, MAKELPARAM(InitialHeight, InitialWidth));

    winrt::MyApp::MainUserControl mainUserControl;
    mainUserControl.UpdateLayout();
    desktopSource.Content(mainUserControl);

    desktopSource.TakeFocusRequested(OnTakeFocusRequested);

    return desktopSource;
}

