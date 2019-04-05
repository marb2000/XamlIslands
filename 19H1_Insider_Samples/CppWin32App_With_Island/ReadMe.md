# Native Win32 Sample for Windows 10 1903

## Overview

This sample demostrates the following features:
* [Keyboard input for Windows 10 1903](/19H1_Insider_Samples/CppWin32App_With_Island/ReadMe.md#Keyboard)
* Generation of the main WinRT resources for Win32 apps.
* Use of custom third party types (e.g.: Microsoft.UI.Xaml controls)
* Auto deployment of the Microsoft VCLib library for Win32 applications
 
## Projects in the solution:

* [Main Win32 Windows Application](/19H1_Insider_Samples/CppWin32App_With_Island/SampleCppApp/ReadMe.md)
* [UWP Application project](/19H1_Insider_Samples/CppWin32App_With_Island/MyApp/ReadMe.md)
* [Xaml Application for Win32](/19H1_Insider_Samples/CppWin32App_With_Island/Microsoft.UI.Xaml.Markup/ReadMe.md)
* [Sample 3rd party control](/19H1_Insider_Samples/CppWin32App_With_Island/SampleUserControl/ReadMe.md)

## <a name="Keyboard"></a> Keyboard input for Windows 10 1903

```
HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLECPPAPP));
MSG msg = {};
HRESULT hr = S_OK;
// Main message loop:
while (GetMessage(&msg, nullptr, 0, 0))
{
  // When multiple child windows are present it is needed to pre dispatch messages to all 
  // DesktopWindowXamlSource instances so keyboard accelerators and 
  // keyboard focus work correctly.
  BOOL xamlSourceProcessedMessage = FALSE;
  for (auto xamlSource : xamlSources)
  {
    auto xamlSourceNative2 = xamlSource.as<IDesktopWindowXamlSourceNative2>();
    hr = xamlSourceNative2->PreTranslateMessage(&msg, &xamlSourceProcessedMessage);
    winrt::check_hresult(hr);
    if (xamlSourceProcessedMessage)
    {
      break;
    }
  }
  if (!xamlSourceProcessedMessage && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}
```
