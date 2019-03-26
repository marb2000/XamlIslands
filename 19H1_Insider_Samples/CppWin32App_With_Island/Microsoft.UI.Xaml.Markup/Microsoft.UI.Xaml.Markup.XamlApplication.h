#pragma once

#include "Microsoft.UI.Xaml.Markup.XamlApplication.g.h"
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <Windows.h>

namespace winrt::Microsoft::UI::Xaml::Markup::implementation
{
    class XamlApplication : public XamlApplicationT<XamlApplication>
    {
    public:
        XamlApplication();
        ~XamlApplication();

        void Close();

        winrt::Windows::UI::Xaml::Markup::IXamlType GetXamlType(winrt::Windows::UI::Xaml::Interop::TypeName const& type);
        winrt::Windows::UI::Xaml::Markup::IXamlType GetXamlType(winrt::hstring const& fullName);
        winrt::com_array<winrt::Windows::UI::Xaml::Markup::XmlnsDefinition> GetXmlnsDefinitions();

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Markup::IXamlMetadataProvider> Providers();

    private:
        winrt::Windows::UI::Xaml::Hosting::WindowsXamlManager m_windowsXamlManager;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Markup::IXamlMetadataProvider> m_providers;
        bool m_bIsClosed = false;
    };
}

namespace winrt::Microsoft::UI::Xaml::Markup::factory_implementation
{
    class XamlApplication : public XamlApplicationT<XamlApplication, implementation::XamlApplication>
    {
    public:
        XamlApplication();
        ~XamlApplication();
    private:
        HINSTANCE m_tWinApiAppCoreInstance = nullptr;
    };
}
