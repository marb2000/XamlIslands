#pragma once

#include "resource.h"

#define ButtonMargin   10
#define ButtonWidth   100
#define ButtonHeight   50
#define XamlIslandMargin ButtonMargin+ButtonHeight
#define InitialHeight 1000
#define InitialWidth  900

ATOM                MyRegisterClass(HINSTANCE hInstance);

HWND InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

