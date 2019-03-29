#include "pch.h"

#include "XamlBridge.h"
#include "Resource.h"
#include "SampleApp.h"

extern HWND hWndXamlIsland;

winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource CreateDesktopWindowsXamlSource(HWND parentWindow)
{
    HRESULT hr = S_OK;

    //auto app = winrt::Windows::UI::Xaml::Application::Current();
    //auto metadataContainer = app.as<winrt::Microsoft::UI::Xaml::Markup::IXamlMetadataProviderContainer>();

    //winrt::SampleUserControl::XamlMetaDataProvider metadataProvider;
    //metadataContainer.Providers().InsertAt(0, metadataProvider);

    //winrt::Microsoft::UI::Xaml::XamlTypeInfo::XamlControlsXamlMetaDataProvider muxMetadataProvider;
    //metadataContainer.Providers().InsertAt(0, muxMetadataProvider);

    // This DesktopWindowXamlSource is the object that enables a non-UWP desktop application 
    // to host UWP controls in any UI element that is associated with a window handle (HWND).
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
    SetWindowPos(hWndXamlIsland, 0, margin, margin, newHeight - margin, newWidth - margin, SWP_SHOWWINDOW);

    winrt::MyApp::MainUserControl mainUserControl;
    mainUserControl.UpdateLayout();
    desktopSource.Content(mainUserControl);

    return desktopSource;
}

