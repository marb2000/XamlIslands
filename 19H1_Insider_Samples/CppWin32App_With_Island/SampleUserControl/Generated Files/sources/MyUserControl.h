#pragma once

#include "MyUserControl.g.h"

namespace winrt::SampleUserControl::implementation
{
    struct MyUserControl : MyUserControlT<MyUserControl>
    {
        MyUserControl() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::SampleUserControl::factory_implementation
{
    struct MyUserControl : MyUserControlT<MyUserControl, implementation::MyUserControl>
    {
    };
}
