#include "pch.h"

#include "Microsoft.UI.Xaml.Markup.XamlApplication.h"

namespace xaml = ::winrt::Windows::UI::Xaml;

namespace winrt::Microsoft::UI::Xaml::Markup::implementation
{
    XamlApplication::XamlApplication()
        : m_providers(winrt::single_threaded_vector<xaml::Markup::IXamlMetadataProvider>())
        , m_windowsXamlManager(xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread())
    {
    }

    void XamlApplication::Close()
    {
        m_windowsXamlManager.Close();
        m_providers.Clear();
    }

    XamlApplication::~XamlApplication()
    {
        Close();
    }

    xaml::Markup::IXamlType XamlApplication::GetXamlType(xaml::Interop::TypeName const& type)
    {
        for (const auto& provider : m_providers)
        {
            const auto xamlType = provider.GetXamlType(type);
            if (xamlType != nullptr)
            {
                return xamlType;
            }
        }

        return nullptr;
    }

    xaml::Markup::IXamlType XamlApplication::GetXamlType(winrt::hstring const& fullName)
    {
        for (const auto& provider : m_providers)
        {
            const auto xamlType = provider.GetXamlType(fullName);
            if (xamlType != nullptr)
            {
                return xamlType;
            }
        }

        return nullptr;
    }

    winrt::com_array<xaml::Markup::XmlnsDefinition> XamlApplication::GetXmlnsDefinitions()
    {
        std::list<xaml::Markup::XmlnsDefinition> definitions;
        for (const auto& provider : m_providers)
        {
            auto defs = provider.GetXmlnsDefinitions();
            for (const auto& def : defs)
            {
                definitions.insert(definitions.begin(), def);
            }
        }

        return winrt::com_array<xaml::Markup::XmlnsDefinition>(definitions.begin(), definitions.end());
    }

    winrt::Windows::Foundation::Collections::IVector<xaml::Markup::IXamlMetadataProvider> XamlApplication::Providers()
    {
        return m_providers;
    }

}