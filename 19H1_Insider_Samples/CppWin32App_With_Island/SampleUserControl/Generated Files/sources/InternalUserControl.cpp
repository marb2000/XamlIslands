#include "pch.h"
#include "InternalUserControl.h"

namespace winrt::SampleUserControl::implementation
{
    int32_t InternalUserControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void InternalUserControl::MyProperty(int32_t value)
    {
        throw hresult_not_implemented();
    }
}
