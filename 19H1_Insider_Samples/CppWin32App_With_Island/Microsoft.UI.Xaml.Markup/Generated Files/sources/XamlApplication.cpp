#include "pch.h"
#include "XamlApplication.h"

namespace winrt::Microsoft::UI::Xaml::Markup::implementation
{
    Windows::Foundation::Collections::IVector<Windows::UI::Xaml::Markup::IXamlMetadataProvider> XamlApplication::Providers()
    {
        throw hresult_not_implemented();
    }

    void XamlApplication::Close()
    {
        throw hresult_not_implemented();
    }

    Windows::UI::Xaml::Markup::IXamlType XamlApplication::GetXamlType(Windows::UI::Xaml::Interop::TypeName const& type)
    {
        throw hresult_not_implemented();
    }

    Windows::UI::Xaml::Markup::IXamlType XamlApplication::GetXamlType(hstring const& fullName)
    {
        throw hresult_not_implemented();
    }

    com_array<Windows::UI::Xaml::Markup::XmlnsDefinition> XamlApplication::GetXmlnsDefinitions()
    {
        throw hresult_not_implemented();
    }
}
