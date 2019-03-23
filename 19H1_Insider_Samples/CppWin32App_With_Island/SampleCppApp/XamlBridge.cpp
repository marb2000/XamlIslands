#include "pch.h"

#include "XamlBridge.h"

#include <roapi.h>
#include "..\Microsoft.UI.Xaml.Markup\Generated Files\Microsoft.UI.Xaml.Markup.XamlApplication.g.h"
#include "..\SampleUserControl\Generated Files\MyUserControl.g.h"

winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource CreateDesktopWindowsXamlSource(HWND parentWindow)
{
    HRESULT hr = S_OK;

    auto app = winrt::Windows::UI::Xaml::Application::Current();
    auto metadataContainer = app.as<winrt::Microsoft::UI::Xaml::Markup::IXamlMetadataProviderContainer>();
    winrt::SampleUserControl::XamlMetaDataProvider metadataProvider;
    metadataContainer.Providers().Append(metadataProvider);

    // This DesktopWindowXamlSource is the object that enables a non-UWP desktop application 
    // to host UWP controls in any UI element that is associated with a window handle (HWND).
    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource;

    // Get handle to corewindow
    auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
    // Parent the DesktopWindowXamlSource object to current window
    hr = interop->AttachToWindow(parentWindow);
    winrt::check_hresult(hr);

    // This Hwnd will be the window handler for the Xaml Island: A child window that contains Xaml.  
    HWND hWndXamlIsland = nullptr;
    // Get the new child window's hwnd 
    hr = interop->get_WindowHandle(&hWndXamlIsland);
    winrt::check_hresult(hr);
    // Update the xaml island window size becuase initially is 0,0
    SetWindowPos(hWndXamlIsland, 0, 200, 100, 800, 400, SWP_SHOWWINDOW);
    SetFocus(hWndXamlIsland);

    //Creating the Xaml content
    winrt::SampleUserControl::MyUserControl control;
    winrt::Windows::UI::Xaml::Controls::StackPanel xamlContainer;
    xamlContainer.Children().Append(control);
    xamlContainer.UpdateLayout();
    desktopSource.Content(xamlContainer);

    return desktopSource;
}

