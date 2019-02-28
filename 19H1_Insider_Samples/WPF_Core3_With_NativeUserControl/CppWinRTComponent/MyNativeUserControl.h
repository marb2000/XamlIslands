//
// Declaration of the MyNativeUserControl class.
//

#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "MyNativeUserControl.g.h"

namespace winrt::CppWinRTComponent::implementation
{
	struct MyNativeUserControl : MyNativeUserControlT<MyNativeUserControl>
	{
		MyNativeUserControl();

	};
}

namespace winrt::CppWinRTComponent::factory_implementation
{
	struct MyNativeUserControl : MyNativeUserControlT<MyNativeUserControl, implementation::MyNativeUserControl>
	{
	};
}
