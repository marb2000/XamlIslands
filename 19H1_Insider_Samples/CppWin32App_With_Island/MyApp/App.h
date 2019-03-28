//
// Declaration of the App class.
//

#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"

#include "App.g.h"

namespace winrt::MyApp::implementation
{
    template <typename D, typename ... Interfaces>
    struct AppT2 : public ::winrt::Microsoft::UI::Xaml::Markup::XamlApplicationT<D, ::winrt::Windows::UI::Xaml::Markup::IXamlMetadataProvider, Interfaces...>
    {
        using IXamlType = ::winrt::Windows::UI::Xaml::Markup::IXamlType;

        void InitializeComponent()
        {}

        IXamlType GetXamlType(::winrt::Windows::UI::Xaml::Interop::TypeName const& type)
        {
            return AppProvider()->GetXamlType(type);
        }

        IXamlType GetXamlType(::winrt::hstring const& fullName)
        {
            return AppProvider()->GetXamlType(fullName);
        }

        ::winrt::com_array<::winrt::Windows::UI::Xaml::Markup::XmlnsDefinition> GetXmlnsDefinitions()
        {
            return AppProvider()->GetXmlnsDefinitions();
        }
    protected:
        AppT2(Windows::UI::Xaml::Markup::IXamlMetadataProvider const& parentProvider)
            : XamlApplicationT(parentProvider)
        {
        }

    private:
        bool _contentLoaded{ false };
        std::shared_ptr<XamlMetaDataProvider> _appProvider;
        std::shared_ptr<XamlMetaDataProvider> AppProvider()
        {
            if (!_appProvider)
            {
                _appProvider = std::make_shared<XamlMetaDataProvider>();
            }
            return _appProvider;
        }
    };

    class App : public AppT2<App>
    {
    public:
        App();
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
