# Shared Components

This folder contains the some UWP components that will be used for other XAML Islands samples. You can find here:

1. A __managed WinRT Component__ in C# with UWP XAML. 
2. A __native WinRT Component__ in C++/WinRT that uses the UWP SwapChainPanel control to render Direct2D content.
3. An __UWP app__ for testing these components in their "natural" enviorment.

## About the managed WinRT Component
We call it "managed" because it is using C# and requires a .NET runtime to run the code. In the case of UWP, UWP uses the __.NET Native__ implementation in Release mode and a sort of __.NET Core__ implementation for Debug mode.

To use Managed WinRT components in Xaml Islands, you need to build your project with two options deactivated. Please, modify your csproj project file and insert this property group:
  ```xml
  <PropertyGroup>
    <EnableTypeInfoReflection>false</EnableTypeInfoReflection>
    <EnableXBindDiagnostics>false</EnableXBindDiagnostics>
  </PropertyGroup>
  ```
