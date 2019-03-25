#pragma once

#include "MyUserControl.g.h"

namespace winrt::SampleUserControl::implementation
{
    struct MyUserControl : MyUserControlT<MyUserControl>
    {
        MyUserControl() = default;

        hstring MyProperty();
        void MyProperty(hstring const& value);
    };
}

namespace winrt::SampleUserControl::factory_implementation
{
    struct MyUserControl : MyUserControlT<MyUserControl, implementation::MyUserControl>
    {
    };
}
