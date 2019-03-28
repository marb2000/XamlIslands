#include "pch.h"

#include "App.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::MyApp::implementation
{
    App::App()
        :App(winrt::MyApp::XamlMetaDataProvider())
    {
    }

    App::App(Windows::UI::Xaml::Markup::IXamlMetadataProvider const& parentProvider)
        : AppT2(parentProvider)
    {
        InitializeComponent();
    }
}
