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
}
