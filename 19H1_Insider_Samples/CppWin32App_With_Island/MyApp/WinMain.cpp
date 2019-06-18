#include "pch.h"

#include "App.h"

extern "C"
{
    __declspec(dllexport) HRESULT CreateApp()
    {
        try
        {
            winrt::MyApp::implementation::App app;
            return S_OK;
        }
        catch (...) { return winrt::to_hresult(); }
    }
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::check_hresult(E_UNEXPECTED);
    return 0;
}

