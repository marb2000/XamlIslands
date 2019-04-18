#pragma once

#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>

extern std::vector<winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource> xamlSources;

int MainMessageLoop(HWND hMainWnd, HACCEL hAccelTable);

HWND CreateDesktopWindowsXamlSource(HWND parentWindow, DWORD dwStyle, winrt::Windows::UI::Xaml::UIElement content);
