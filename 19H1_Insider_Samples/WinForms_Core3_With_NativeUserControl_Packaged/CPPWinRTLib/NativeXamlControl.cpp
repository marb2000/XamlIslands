#include "pch.h"
#include "NativeXamlControl.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::CPPWinRTLib::implementation
{
    NativeXamlControl::NativeXamlControl()
    {
        InitializeComponent();
    }

    int32_t NativeXamlControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void NativeXamlControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void NativeXamlControl::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
