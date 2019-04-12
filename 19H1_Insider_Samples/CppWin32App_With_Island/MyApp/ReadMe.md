# Sample WinRT App

This is a normal UWP Application project that have had the following modifications:
1. Compile as a Dynamic Link Library instead of an Executable
- 2 The Xaml Application object inherits from Microsoft.UI.Markup.XamlApplication instead of Windows.UI.Xaml.Application
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
</MSMarkup:XamlApplication>
```
3. The build settings have been modified to produced resources.pri and AppxManifest at build time:
```
```
