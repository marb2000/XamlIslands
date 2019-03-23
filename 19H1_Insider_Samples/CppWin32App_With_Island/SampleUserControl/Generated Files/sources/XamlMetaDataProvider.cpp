#include "pch.h"
#include "XamlMetaDataProvider.h"

namespace winrt::SampleUserControl::implementation
{
    Windows::UI::Xaml::Markup::IXamlType XamlMetaDataProvider::GetXamlType(Windows::UI::Xaml::Interop::TypeName const& type)
    {
        throw hresult_not_implemented();
    }

    Windows::UI::Xaml::Markup::IXamlType XamlMetaDataProvider::GetXamlType(hstring const& fullName)
    {
        throw hresult_not_implemented();
    }

    com_array<Windows::UI::Xaml::Markup::XmlnsDefinition> XamlMetaDataProvider::GetXmlnsDefinitions()
    {
        throw hresult_not_implemented();
    }
}
