# Native Win32 Sample for Windows 10 1903

## Overview

This sample demostrates the following features:
* [Keyboard input for Windows 10 1903](/19H1_Insider_Samples/CppWin32App_With_Island/ReadMe.md#Keyboard)
* [Generation of WinRT resources for Win32 apps](/19H1_Insider_Samples/CppWin32App_With_Island/ReadMe.md#Resources)
* [Use of custom third party types](/19H1_Insider_Samples/CppWin32App_With_Island/ReadMe.md#AppObject)
* [Auto deployment of the Microsoft VCLib library for Win32 applications](/19H1_Insider_Samples/CppWin32App_With_Island/ReadMe.md#VCLib)
 
![Screenshoot](/19H1_Insider_Samples/CppWin32App_With_Island/Screenshoot.PNG)

## Projects in the solution:

* [Main Win32 Windows Application](/19H1_Insider_Samples/CppWin32App_With_Island/SampleCppApp/ReadMe.md)
* [UWP Application project](/19H1_Insider_Samples/CppWin32App_With_Island/MyApp/ReadMe.md)
* [Xaml Application for Win32](/19H1_Insider_Samples/CppWin32App_With_Island/Microsoft.UI.Xaml.Markup/ReadMe.md)
* [Sample 3rd party control](/19H1_Insider_Samples/CppWin32App_With_Island/SampleUserControl/ReadMe.md)

## <a name="Keyboard"/> Keyboard input for Windows 10 1903

This is an [implementation](/19H1_Insider_Samples/CppWin32App_With_Island/SampleCppApp/SampleApp.cpp#L47-L74) of Win32 message loop for an application that contains a set of instances of [DesktopWindowXamlSource](https://docs.microsoft.com/en-us/uwp/api/windows.ui.xaml.hosting.desktopwindowxamlsource)

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

## <a name="Resources"/> Generation of WinRT resources for Win32 apps

By default a Windows Store app of a Win32 app that uses 3rd party controls or its own resources requires the generation of a consolidated Resources.pri file.
This is performed by the tool MakePri.exe.
In a typical UWP App, this only happens when the Appx is generated.
For Win32 Apps you need to perform the following steps:
1. Create a new Blank UWP App
2. Change the output type to be a Dynamic link dll.
3. Change the [AppxPackage](/19H1_Insider_Samples/CppWin32App_With_Island/MyApp/Package.appxmanifest#L20) to deploy a dummy exe.
4. Change these [properties](/19H1_Insider_Samples/CppWin32App_With_Island/MyApp/MyApp.vcxproj#L18) in your project:
```
  <PropertyGroup Label="Globals">
    <WindowsAppContainer>true</WindowsAppContainer>
    <AppxGeneratePriEnabled>true</AppxGeneratePriEnabled>
    <ProjectPriIndexName>App</ProjectPriIndexName>
    <AppxPackage>true</AppxPackage>
  </PropertyGroup>
```
5. In your [main Win32 project](/19H1_Insider_Samples/CppWin32App_With_Island/SampleCppApp/SampleCppApp.vcxproj#L248), make sure you deploy the file resources.pri to your output directory:
```
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\$(AppProjectName)\resources.pri">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
```
6. Make sure to create a build dependency between your [main Win32 project](/19H1_Insider_Samples/CppWin32App_With_Island/SampleCppApp/SampleCppApp.vcxproj) and the [UWP App project](/19H1_Insider_Samples/CppWin32App_With_Island/MyApp/MyApp.vcxproj)

## <a name="AppObject"/> Use of 3rd party controls

The use of 3rd party control objects requires the use of a consolidated [resources file](/19H1_Insider_Samples/CppWin32App_With_Island/ReadMe.md#Resources) and a [custom application](/19H1_Insider_Samples/CppWin32App_With_Island/Microsoft.UI.Xaml.Markup/ReadMe.md) object that:
1. Registers the Xaml metedata providers.
2. Initializes Xaml by calling [InitializeForCurrentThread](https://docs.microsoft.com/en-us/uwp/api/windows.ui.xaml.hosting.windowsxamlmanager.initializeforcurrentthread)

In this sample this is implemented by [App.xaml](/19H1_Insider_Samples/CppWin32App_With_Island/MyApp/App.xaml) and the [Xaml Application for Win32](/19H1_Insider_Samples/CppWin32App_With_Island/Microsoft.UI.Xaml.Markup/ReadMe.md)

```
<MSMarkup:XamlApplication
    x:Class="MyApp.App"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:local="using:MyApp"
    xmlns:MSMarkup="using:Microsoft.UI.Xaml.Markup"
    xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
    xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
    RequestedTheme="Light"
    mc:Ignorable="d">
    <MSMarkup:XamlApplication.Resources>
        <XamlControlsResources xmlns="using:Microsoft.UI.Xaml.Controls"/>
    </MSMarkup:XamlApplication.Resources>
</MSMarkup:XamlApplication>
```

Also make sure to [deploy](/19H1_Insider_Samples/CppWin32App_With_Island/SampleCppApp/SampleCppApp.vcxproj#L232-L247) all Xaml compiler output from your App in your Win32 app project:
```
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\Microsoft.UI.Xaml.Markup\Microsoft.UI.Xaml.Markup.dll">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\SampleUserControl\SampleUserControl.dll">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\$(AppProjectName)\*.xbf">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\$(AppProjectName)\*.dll">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
```

## <a name="VCLib"/> Auto deployment of the Microsoft VCLib library for Win32 applications

