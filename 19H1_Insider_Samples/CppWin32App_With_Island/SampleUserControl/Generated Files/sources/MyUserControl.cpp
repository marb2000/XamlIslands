#include "pch.h"
#include "MyUserControl.h"

namespace winrt::SampleUserControl::implementation
{
    hstring MyUserControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MyUserControl::MyProperty(hstring const& value)
    {
        throw hresult_not_implemented();
    }
}
