#pragma once

#include "resource.h"

#include "XamlBridge.h"

#define ButtonMargin   10
#define ButtonWidth   100
#define ButtonHeight   50
#define IslandInitialHeight 800
#define IslandInitialWidth  800
#define XamlIslandMargin ButtonMargin+ButtonHeight
#define InitialHeight (IslandInitialHeight+((ButtonMargin+ButtonHeight)*2))
#define InitialWidth  (IslandInitialWidth+(ButtonMargin*2))

const int WM_MOVEFOCUS = WM_USER + 1;
const int WM_ISDIALOGKEY = WM_USER + 2;

extern HWND hMainWnd;

ATOM                MyRegisterClass(HINSTANCE hInstance);

winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

