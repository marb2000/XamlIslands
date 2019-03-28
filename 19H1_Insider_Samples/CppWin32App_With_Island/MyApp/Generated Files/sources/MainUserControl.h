#pragma once

#include "MainUserControl.g.h"

namespace winrt::MyApp::implementation
{
    struct MainUserControl : MainUserControlT<MainUserControl>
    {
        MainUserControl() = default;

    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MainUserControl : MainUserControlT<MainUserControl, implementation::MainUserControl>
    {
    };
}
