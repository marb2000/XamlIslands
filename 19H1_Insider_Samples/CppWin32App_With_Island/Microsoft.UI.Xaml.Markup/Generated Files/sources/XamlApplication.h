#pragma once

#include "XamlApplication.g.h"

namespace winrt::Microsoft::UI::Xaml::Markup::implementation
{
    struct XamlApplication : XamlApplicationT<XamlApplication>
    {
        XamlApplication() = default;

        Windows::Foundation::Collections::IVector<Windows::UI::Xaml::Markup::IXamlMetadataProvider> Providers();
        void Close();
    };
}

namespace winrt::Microsoft::UI::Xaml::Markup::factory_implementation
{
    struct XamlApplication : XamlApplicationT<XamlApplication, implementation::XamlApplication>
    {
    };
}
