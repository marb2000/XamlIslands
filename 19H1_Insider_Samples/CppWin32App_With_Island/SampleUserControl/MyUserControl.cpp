#include "pch.h"
#include "MyUserControl.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SampleUserControl::implementation
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
}


void winrt::SampleUserControl::implementation::MyUserControl::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& )
{
    Text1().Text(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());
}
