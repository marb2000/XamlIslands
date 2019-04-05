//
// Declaration of the App class.
//

#pragma once

#include "App.g.h"

namespace winrt::MyApp::implementation
{
    template <typename D, typename... I>
    using AppT_Override = App_base<D, I...>; // We dont use AppT as it does not provide access to protected constructors

    class App : public AppT_Override<App>
    {
    public:
        App();
        ~App();
    private:
        App(Windows::UI::Xaml::Markup::IXamlMetadataProvider const& parentProvider);
    };
}

namespace winrt::MyApp::factory_implementation
{
    class App : public AppT<App, implementation::App>
    {
    };
}
