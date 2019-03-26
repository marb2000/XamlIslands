#pragma once

#include "InternalUserControl.g.h"

namespace winrt::SampleUserControl::implementation
{
    struct InternalUserControl : InternalUserControlT<InternalUserControl>
    {
        InternalUserControl() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::SampleUserControl::factory_implementation
{
    struct InternalUserControl : InternalUserControlT<InternalUserControl, implementation::InternalUserControl>
    {
    };
}
