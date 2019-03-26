#include "pch.h"

#include "Microsoft.UI.Xaml.Markup.XamlApplication.h"

namespace xaml = ::winrt::Windows::UI::Xaml;

extern "C" {
    WINBASEAPI HMODULE WINAPI LoadLibraryExW(_In_ LPCWSTR lpLibFileName, _Reserved_ HANDLE hFile, _In_ DWORD dwFlags);
    WINBASEAPI HMODULE WINAPI GetModuleHandleW(_In_opt_ LPCWSTR lpModuleName);
    WINUSERAPI BOOL WINAPI PeekMessageW(_Out_ LPMSG lpMsg, _In_opt_ HWND hWnd, _In_ UINT wMsgFilterMin, _In_ UINT wMsgFilterMax, _In_ UINT wRemoveMsg);
    WINUSERAPI LRESULT WINAPI DispatchMessageW(_In_ CONST MSG* lpMsg);
}

namespace winrt::Microsoft::UI::Xaml::Markup::implementation
{
    XamlApplication::XamlApplication()
        : m_providers(winrt::single_threaded_vector<xaml::Markup::IXamlMetadataProvider>())
        , m_windowsXamlManager(xaml::Hosting::WindowsXamlManager::InitializeForCurrentThread())
    {
    }

    void XamlApplication::Close()
    {
        if (m_bIsClosed)
        {
            return;
        }

        m_bIsClosed = true;
        m_windowsXamlManager.Close();
        m_providers.Clear();
        m_windowsXamlManager = nullptr;

        Exit();
        {
            MSG msg = {};
            while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                ::DispatchMessageW(&msg);
            }
        }
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

namespace winrt::Microsoft::UI::Xaml::Markup::factory_implementation
{
    XamlApplication::XamlApplication()
    {
        // Workaround a bug where twinapi.appcore.dll gets loaded after it has been unloaded
        // becuase of a call to GetActivationFactory
        m_tWinApiAppCoreInstance = ::LoadLibraryExW(L"twinapi.appcore.dll", nullptr, 0);
    }

    XamlApplication::~XamlApplication()
    {
        if (m_tWinApiAppCoreInstance != nullptr)
        {
            ::FreeLibrary(m_tWinApiAppCoreInstance);
            m_tWinApiAppCoreInstance = nullptr;
        }
    }
}