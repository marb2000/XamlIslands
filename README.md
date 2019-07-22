# XAML Islands v1 early samples repository

This repository has samples to demonstrate how to use XAML Islands in several scenarios. Althought [XAML Islands v1](https://blogs.windows.com/windowsdeveloper/2019/06/13/XAML-islands-v1-updates-and-roadmap/#r17cU1yReAgMH700.97) was shipped within Windows 10 1903 update, the Visual Studio 2019 toolset for support XAML Island is still in development. There is no guarantee that these samples work for everybody. These are for those impatient developers who want to try unfinished and unstable things, like me :) 

To test the samples, I recommend the following developer environment:

1. [Windows 10 1903](https://www.microsoft.com/en-us/software-download/windows10). XAML Islands v1 doesn't work on previews versions of either Windows 10 nor Windows 7/8.x
2. [Visual Studio Preview 2019](https://visualstudio.microsoft.com/vs/preview/). Visual Studio 2019 is already released, but there are, more or less, updates every 4 months. The preview version contains the updates in development. Install these workloads:
   1. Universal Windows Platform development with the Windows 10 18362 SDK and C++ (v142)
   2. .NET development
   3. Desktop development with C++ with C++ MFC for v142, MSVC v142, Windows 10 SDK (10.0.18362.0)

3. [.NET Core 3 Preview](https://dotnet.microsoft.com/download/dotnet-core/3.0). Install both versions: x64 and x86. 

## Samples

* [CppWinRT_Win32_SimpleApp](/1903_Samples/CppWinRT_Win32_SimpleApp/)  - Unpackaged simple C++/WinRT Win32 app. A very simple project that showcases how to use the OS API DesktopWindowXamlSource to create a XAML Island.
* [WinForms_Core3_App](/1903_Samples/WinForms_Core3_App/) - Unpackaged WinForms .NET Core 3 app that consumes a managed and native 3rd WinRT components. These WinRT components are in the Shared_Components project.
  * Read this [doc](/1903_Samples/WnForms_and_WPF_Readme.md) for intructions.
* [WinForms_Packaging_Project](/1903_Samples/WinForms_Packaging_Project/) - Packaged version of the WinForms sample.
  * Read this [doc](/1903_Samples/WnForms_and_WPF_Readme.md) for intructions.
* [WPF_Core3_App](/1903_Samples/WPF_Core3_App/) - Unpackaged WPF .NET Core 3 app that consumes a managed and native 3rd WinRT components.These WinRT components are in the Shared_Components project.
  * Read this [doc](/1903_Samples/WnForms_and_WPF_Readme.md) for intructions.
* [WPF_Packaging_Project](/1903_Samples/WPF_Packaging_Project/) - Packaged version of the WPF sample. 
  * Read this [doc](/1903_Samples/WnForms_and_WPF_Readme.md) for intructions.
* [CppWinRT_Win32_App](/1903_Samples/CppWinRT_Win32_App/). Unpackaged complex C++/WinRT Win32 app: This sample demonstrates how to consume native 3rd party controls.
  * Read this [doc](/1903_Samples/CppWinRT_Win32_App/ReadMe.md) for intructions.

## Running the samples

### Set the right target platform
UWP WinRT Components require to target a specific platform, hence __"Any CPU" is not a supported__ target. Before compile the samples, make sure you are targetting __x86 or x64 platforms__.  

> Sometimes changing the dropdown list of target platforms on the Visual Studio toolbar is not enough. It is recommended going into the Solution Properties → Configuration Properties → Configuration and change all the project's target platforms there.

### Clean the bin and obj folders

After several compilations and builds, your output directories (bin folders) can contain all type of test files causing the builds and runs fail. You should __clean your bin and obj folders after building the project__ for having a clean build.

The clean command from Visual Studio doesn't delete the bin and obj folders enterally. It is recommended to delete these folders manually or running a script in your repro folder. For example, this PowerShell script:

```PS
Get-ChildItem .\ -include bin,obj -Recurse | foreach ($_) { remove-item $_.fullname -Force -Recurse }
```

> Be careful where you execute this script given it deletes all the bin and obj folder of the directory and subdirectories.  

## Feedback

If you want to give us very early feedback, report a bug, tell us whether these samples are useful, etc.,  please, send an email to __xamlIslandsfeedback @ microsoft.com__, my engineering team will receive it. 


Happy hacking!

__Miguel Ramos__


