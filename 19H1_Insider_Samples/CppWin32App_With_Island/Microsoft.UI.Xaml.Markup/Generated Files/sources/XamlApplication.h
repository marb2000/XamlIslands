#pragma once

#include "XamlApplication.g.h"

namespace winrt::Microsoft::UI::Xaml::Markup::implementation
{
    struct XamlApplication : XamlApplicationT<XamlApplication>
    {
        XamlApplication() = default;

        Windows::Foundation::Collections::IVector<Windows::UI::Xaml::Markup::IXamlMetadataProvider> Providers();
        void Close();
        Windows::UI::Xaml::Markup::IXamlType GetXamlType(Windows::UI::Xaml::Interop::TypeName const& type);
        Windows::UI::Xaml::Markup::IXamlType GetXamlType(hstring const& fullName);
        com_array<Windows::UI::Xaml::Markup::XmlnsDefinition> GetXmlnsDefinitions();
    };
}

namespace winrt::Microsoft::UI::Xaml::Markup::factory_implementation
{
    struct XamlApplication : XamlApplicationT<XamlApplication, implementation::XamlApplication>
    {
    };
}
