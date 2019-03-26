#include "pch.h"

#include "XamlBridge.h"
#include "Resource.h"
#include "SampleApp.h"
#include <roapi.h>
#include "..\Microsoft.UI.Xaml.Markup\Generated Files\Microsoft.UI.Xaml.Markup.XamlApplication.g.h"
#include "..\SampleUserControl\Generated Files\MyUserControl.g.h"

extern HWND hWndXamlIsland;

winrt::Windows::UI::Xaml::UIElement LoadXaml(uint32_t id)
{
    auto rc = ::FindResource(nullptr, MAKEINTRESOURCE(id), MAKEINTRESOURCE(XAMLRESOURCE));
    if (!rc)
    {
        winrt::check_hresult(HRESULT_FROM_WIN32(GetLastError()));
    }
    HGLOBAL rcData = ::LoadResource(nullptr, rc);
    if (!rcData)
    {
        winrt::check_hresult(HRESULT_FROM_WIN32(GetLastError()));
    }
    auto pData = static_cast<wchar_t*>(::LockResource(rcData));
    auto content = winrt::Windows::UI::Xaml::Markup::XamlReader::Load(winrt::get_abi(pData));
    auto uiElement = content.as<winrt::Windows::UI::Xaml::UIElement>();
    return uiElement;
}

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

    // Get the new child window's hwnd 
    hr = interop->get_WindowHandle(&hWndXamlIsland);
    winrt::check_hresult(hr);
    SetFocus(hWndXamlIsland);

    const auto newHeight = InitialHeight;
    const auto newWidth = InitialWidth;
    const auto margin = XamlIslandMargin;
    SetWindowPos(hWndXamlIsland, 0, margin, margin, newHeight - margin, newWidth - margin, SWP_SHOWWINDOW);

    auto content = LoadXaml(IDR_XAML_MAINPAGE);
    auto mainPage = content.as<winrt::Windows::UI::Xaml::UIElement>();
    mainPage.UpdateLayout();
    desktopSource.Content(mainPage);

    return desktopSource;
}

