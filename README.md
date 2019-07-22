# XAML Islands v1 early samples repository

This repository has samples to demonstrate how to use XAML Islands in several scenarios. Althought [XAML Islands v1](https://blogs.windows.com/windowsdeveloper/2019/06/13/XAML-islands-v1-updates-and-roadmap/#r17cU1yReAgMH700.97) was shipped within Windows 10 1903 update, the Visual Studio 2019 toolset for support XAML Island is still in development. There is no guarantee that these samples work for everybody. These are for those impatient developers who want to try unfinished and unstable things, like me :) 

To test the samples, I recommend the following developer environment:

1. [Windows 10 1903](https://www.microsoft.com/en-us/software-download/windows10). XAML Islands v1 doesn't work on previews versions of either Windows 10 nor Windows 7/8.x
2. [Visual Studio Preview 2019](https://visualstudio.microsoft.com/vs/preview/). Visual Studio 2019 is already released, but there are, more or less, updates every 4 months. The preview version contains the updates in development. Install these workloads:
   1. Universal Windows Platform development with the Windows 10 18362 SDK and C++ (v142)
   2. .NET development
   3. Desktop development with C++ with C++ MFC for v142, MSVC v142, Windows 10 SDK (10.0.18362.0)

3. [.NET Core 3 Preview](https://dotnet.microsoft.com/download/dotnet-core/3.0). Install both versions: x64 and x86. 

If you want to give us very early feedback, report a bug, tell us whether these samples are useful, etc.,  please, send an email to __xamlIslandsfeedback @ microsoft . com__, my engineering team will receive it. 

## Samples

* [CppWinRT_Win32_SimpleApp](/1903_Samples/CppWinRT_Win32_App/CppWinRT_Win32_SimpleApp/)  - Unpackaged simple C++/WinRT Win32 app. A very simple project that showcases how to use the OS API DesktopWindowXamlSource to create a XAML Island.
* [WinForms_Core3_App](1/903_Samples/CppWinRT_Win32_App/WinForms_Core3_App/) - Unpackaged WinForms .NET Core 3 app that consumes a managed and native 3rd WinRT components. These WinRT components are in the Shared_Components project.
* [WinForms_Packaging_Project](1903_Samples/CppWinRT_Win32_App/WinForms_Packaging_Project) - Packaged version of the WinForms sample.
* [WPF_Core3_App](/1903_Samples/CppWinRT_Win32_App/WPF_Core3_App/) - Unpackaged WPF .NET Core 3 app that consumes a managed and native 3rd WinRT components.These WinRT components are in the Shared_Components project.
* [WPF_Packaging_Project](/1903_Samples/CppWinRT_Win32_App/WPF_Packaging_Project/) - Packaged version of the WPF sample. 
* [CppWinRT_Win32_App](/1903_Samples/CppWinRT_Win32_App/CppWinRT_Win32_App/). Unpackaged complex C++/WinRT Win32 app: This sample demonstrates how to consume native 3rd party controls.



Happy hacking!

__Miguel Ramos__


