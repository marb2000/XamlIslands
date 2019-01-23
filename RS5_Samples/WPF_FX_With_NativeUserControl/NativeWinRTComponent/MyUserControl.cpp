#include "pch.h"
#include "MyUserControl.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NativeWinRTComponent::implementation
{
    MyUserControl::MyUserControl()
    {
        InitializeComponent();
    }

    int32_t MyUserControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MyUserControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MyUserControl::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
