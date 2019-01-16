//
// Declaration of the NativeXamlControl class.
//

#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "NativeXamlControl.g.h"

namespace winrt::CPPWinRTLib::implementation
{
    struct NativeXamlControl : NativeXamlControlT<NativeXamlControl>
    {
        NativeXamlControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::CPPWinRTLib::factory_implementation
{
    struct NativeXamlControl : NativeXamlControlT<NativeXamlControl, implementation::NativeXamlControl>
    {
    };
}
