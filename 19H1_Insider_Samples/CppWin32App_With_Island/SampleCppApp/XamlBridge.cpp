#include "pch.h"

#include "XamlBridge.h"
#include "Resource.h"
#include "SampleApp.h"

extern HWND hWndXamlIsland;

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
    SetFocus(hWndXamlIsland);

    const auto newHeight = InitialHeight;
    const auto newWidth = InitialWidth;
    const auto margin = XamlIslandMargin;
    SetWindowPos(hWndXamlIsland, 0, ButtonMargin, XamlIslandMargin, IslandInitialWidth, IslandInitialHeight, SWP_SHOWWINDOW);

    winrt::MyApp::MainUserControl mainUserControl;
    mainUserControl.UpdateLayout();
    desktopSource.Content(mainUserControl);

    return desktopSource;
}

