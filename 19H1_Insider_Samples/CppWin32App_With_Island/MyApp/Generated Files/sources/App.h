#pragma once

#include "App.g.h"

namespace winrt::MyApp::implementation
{
    struct App : AppT<App>
    {
        App() = default;

    };
}

namespace winrt::MyApp::factory_implementation
{
    struct App : AppT<App, implementation::App>
    {
    };
}
