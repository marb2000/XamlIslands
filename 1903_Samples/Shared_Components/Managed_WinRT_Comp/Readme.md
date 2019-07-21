This project is a Managed WinRT Component. It is managed because it is using C# and requires a .NET runtime to run the code. In the case of UWP is using the .NET Native implementation in Release mode. For Debug mode is using a sort of .NET Core implementation.

To use Managed WinRT components in Xaml Islands, you need to build your project with these two options deactivated. Modify your csproj and insert this property group:
  ```xml
  <PropertyGroup>
    <EnableTypeInfoReflection>false</EnableTypeInfoReflection>
    <EnableXBindDiagnostics>false</EnableXBindDiagnostics>
  </PropertyGroup>
  ```
  sd