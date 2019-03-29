#include "pch.h"
#include "MainUserControl.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::MyApp::implementation
{
    MainUserControl::MainUserControl()
    {
        if (!_contentLoaded)
        {
            _contentLoaded = true;
            Windows::Foundation::Uri resourceLocator{ L"ms-appx:///MainUserControl.xaml" };
            Windows::UI::Xaml::Application::LoadComponent(*this, resourceLocator, Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Nested);
        }
        //InitializeComponent();
    }
}
