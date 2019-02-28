#pragma once

#include "MyNativeUserControl.g.h"

namespace winrt::CppWinRTComponent::implementation
{
    struct MyNativeUserControl : MyNativeUserControlT<MyNativeUserControl>
    {
        MyNativeUserControl() = default;

    };
}

namespace winrt::CppWinRTComponent::factory_implementation
{
    struct MyNativeUserControl : MyNativeUserControlT<MyNativeUserControl, implementation::MyNativeUserControl>
    {
    };
}
