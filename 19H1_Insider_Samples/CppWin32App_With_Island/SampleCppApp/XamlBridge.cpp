#include "pch.h"

#include "XamlBridge.h"

#include <roapi.h>

winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource CreateDesktopWindowsXamlSource(HWND parentWindow)
{
    HRESULT hr = S_OK;

    winrt::Windows::Foundation::IInspectable app;
    hr = ::RoActivateInstance(reinterpret_cast<::HSTRING>(winrt::get_abi(winrt::hstring(L"Microsoft.UI.Xaml.Markup.XamlApplication"))), reinterpret_cast<::IInspectable * *>(winrt::put_abi(app)));
    winrt::check_hresult(hr);

    // This DesktopWindowXamlSource is the object that enables a non-UWP desktop application 
    // to host UWP controls in any UI element that is associated with a window handle (HWND).
    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource;

    // Get handle to corewindow
    auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
    // Parent the DesktopWindowXamlSource object to current window
    winrt::check_hresult(interop->AttachToWindow(parentWindow));

    // This Hwnd will be the window handler for the Xaml Island: A child window that contains Xaml.  
    HWND hWndXamlIsland = nullptr;
    // Get the new child window's hwnd 
    interop->get_WindowHandle(&hWndXamlIsland);
    // Update the xaml island window size becuase initially is 0,0
    SetWindowPos(hWndXamlIsland, 0, 200, 100, 800, 400, SWP_SHOWWINDOW);

    winrt::Windows::Foundation::IInspectable control;
    hr = ::RoActivateInstance(reinterpret_cast<::HSTRING>(winrt::get_abi(winrt::hstring(L"SampleUserControl.MyUserControl"))), reinterpret_cast<::IInspectable * *>(winrt::put_abi(control)));
    winrt::check_hresult(hr);
    auto uiElement = control.as<winrt::Windows::UI::Xaml::UIElement>();

    //Creating the Xaml content
    winrt::Windows::UI::Xaml::Controls::StackPanel xamlContainer;

    xamlContainer.Children().Append(uiElement);
    xamlContainer.UpdateLayout();
    desktopSource.Content(xamlContainer);

    return desktopSource;
}

