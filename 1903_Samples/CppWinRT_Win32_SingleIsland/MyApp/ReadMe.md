# App object for C++/WinRT Win32 Desktop

This example demonstrates how to use a custom Application object. A way to generate a UWP Application is using the template for a UWP Application in C++. However, you need to modify the project and do some changes on the classes to use it within Xaml Islands v1: 

- It has to compile as a Dynamic Link Library instead of an Executable.

- The Xaml Application object has to inherit from Microsoft.UI.Markup.XamlApplication instead of Windows.UI.Xaml.Application. The XamlApplication object comes from Microsoft.Toolkit.Win32.UI.XamlHost Nuget Package. For instance, in the sample the namespace was Toolkit="using:Microsoft.Toolkit.Win32.UI.XamlHost" was added, and the <Application> becomes <Toolkit:XamlApplication>
  
```xml
<Toolkit:XamlApplication
    x:Class="MyApp.App"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:local="using:MyApp"
    xmlns:Toolkit="using:Microsoft.Toolkit.Win32.UI.XamlHost"
    xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
    xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
    RequestedTheme="Light"
    mc:Ignorable="d">
    <Toolkit:XamlApplication.Resources>
        <XamlControlsResources xmlns="using:Microsoft.UI.Xaml.Controls"/>
    </Toolkit:XamlApplication.Resources>
</Toolkit:XamlApplication>
```
- The build settings have been modified to produced resources.pri and AppxManifest at build time. If your app doesn't have app manifest with the <maxversiontested Id="10.0.18632.0"/>, the build will generate it for you. These MSBuild properties allow you to activate/deactivate this autogeneration. 
```xml
  <PropertyGroup Label="Globals">
    <WindowsAppContainer>true</WindowsAppContainer>
    <AppxGeneratePriEnabled>true</AppxGeneratePriEnabled>
    <ProjectPriIndexName>App</ProjectPriIndexName>
    <AppxPackage>true</AppxPackage>
  </PropertyGroup>
```
