#pragma once

#include <unknwn.h> // To enable support for non-WinRT interfaces, unknwn.h must be included before any C++/WinRT headers.
#include <winrt/Windows.System.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <windowsx.h>

class DesktopWindow
{
public:
    int MessageLoop(HACCEL hAccelTable);
private:
    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource GetFocusedIsland();
    bool FilterMessage(const MSG* msg);
    void OnTakeFocusRequested(winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource const& sender, winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSourceTakeFocusRequestedEventArgs const& args);
    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource GetNextFocusedIsland(MSG* msg);
    bool NavigateFocus(MSG* msg);
protected:
    HWND CreateDesktopWindowsXamlSource(DWORD dwStyle, winrt::Windows::UI::Xaml::UIElement content);
    void ClearXamlIslands();
    HWND m_hMainWnd = nullptr;
private:
    winrt::guid lastFocusRequestId;
    std::vector<winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource> m_xamlSources;
};

template <typename T>
struct DesktopWindowT : public DesktopWindow
{
protected:
    using base_type = DesktopWindowT<T>;

    static LRESULT __stdcall WndProc(HWND const window, UINT const message, WPARAM const wparam, LPARAM const lparam) noexcept
    {
        WINRT_ASSERT(window);

        if (WM_NCCREATE == message)
        {
            auto cs = reinterpret_cast<CREATESTRUCT*>(lparam);
            T* that = static_cast<T*>(cs->lpCreateParams);
            WINRT_ASSERT(that);
            WINRT_ASSERT(!that->m_hMainWnd);
            that->m_hMainWnd = window;
            SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(that));
        }
        else if (T * that = GetThisFromHandle(window))
        {
            return that->MessageHandler(message, wparam, lparam);
        }

        return DefWindowProc(window, message, wparam, lparam);
    }

    LRESULT MessageHandler(UINT const message, WPARAM const wParam, LPARAM const lParam) noexcept
    {
        switch (message)
        {
            HANDLE_MSG(m_hMainWnd, WM_DESTROY, OnDestroy);
            HANDLE_MSG(m_hMainWnd, WM_ACTIVATE, OnActivate);
            HANDLE_MSG(m_hMainWnd, WM_SETFOCUS, OnSetFocus);
        }
        return DefWindowProc(m_hMainWnd, message, wParam, lParam);
    }

    void OnDestroy(HWND)
    {
        ClearXamlIslands();
        PostQuitMessage(0);
    }

private:

    void OnActivate(HWND, UINT state, HWND hwndActDeact, BOOL fMinimized)
    {
        if (state == WA_INACTIVE)
        {
            m_hwndLastFocus = GetFocus();
        }
    }

    void OnSetFocus(HWND, HWND hwndOldFocus)
    {
        if (m_hwndLastFocus) {
            SetFocus(m_hwndLastFocus);
        }
    }

    static T* GetThisFromHandle(HWND const window) noexcept
    {
        return reinterpret_cast<T*>(GetWindowLongPtr(window, GWLP_USERDATA));
    }

    HWND m_hwndLastFocus = nullptr;
};

winrt::Windows::UI::Xaml::UIElement LoadXamlControl(uint32_t id);

template<typename T>
T LoadXamlControl(uint32_t id)
{
    const auto uiElement = LoadXamlControl(id);
    return uiElement.as<T>();
}
