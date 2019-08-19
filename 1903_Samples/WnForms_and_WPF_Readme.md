# XAML Islands v1 in WinForms/WPF .NET Core 3 apps 

These .NET Core 3 samples demonstrate how to use 3rd party WinRT components from a WinForms/WPF app. Consuming 3rd part UWP Xaml WinRT Components is an expected supported scenario. However, Visual Studio toolset for XAML Islands v1 is still in development. It is necessary to address several steps to make your WPF/WinForms .NET Core 3 app works.

In the WPF and WinForms .NET Core 3 apps, the UI is only UWP XAML, and we didn't add any WPF/WinForms controls for simplicity's sake. 

## WPF
In the WPF app, the MainWindow.xaml file contains the instance of the WindowsXamlHost control. This control is a NET wrapper for the Operating System APIs that implement the XAML Islands.
```XML
<StackPanel>
    <xamlhost:WindowsXamlHost InitialTypeName="Samples.ManagedWinRT.MainPage" />
 </StackPanel>
```
 This control is on the [Microsoft.Toolkit.Wpf.UI.XamlHost Nuget Packaged](https://www.nuget.org/packages/Microsoft.Toolkit.Wpf.UI.XamlHost/6.0.0-preview6.4) developed on the [Windows Community Toolkit](https://github.com/windows-toolkit/Microsoft.Toolkit.Win32) site.

## WinForms

 In the WinForms app, the MainForm.Designer.cs file contains the instance of the WindowsXamlHost control for WinForms:
 
 ```C#
 private void InitializeComponent()
 {
    this.windowsXamlHost1 = new Microsoft.Toolkit.Forms.UI.XamlHost.WindowsXamlHost();
    this.SuspendLayout();
    // 
    // windowsXamlHost1
    // 
    this.windowsXamlHost1.AutoSizeMode =
             System.Windows.Forms.AutoSizeMode.GrowOnly;
    this.windowsXamlHost1.InitialTypeName = null;
    this.windowsXamlHost1.Location = new System.Drawing.Point(0, 0);
    this.windowsXamlHost1.Name = "windowsXamlHost1";
    this.windowsXamlHost1.Size = new System.Drawing.Size(800, 800);
    this.windowsXamlHost1.TabIndex = 0;
    this.windowsXamlHost1.Text = "windowsXamlHost1";
    this.windowsXamlHost1.Dock = System.Windows.Forms.DockStyle.Fill;
...
 ```
 
 In the MainForm.cs file, the Initial type of the XAML Island is set:

 ```C#
public MainForm()
  {
    InitializeComponent();

    this.windowsXamlHost1.InitialTypeName = "Samples.ManagedWinRT.MainPage";
  }
```

This control is on the [Microsoft.Toolkit.Forms.UI.XamlHost Nuget Packaged](https://www.nuget.org/packages/Microsoft.Toolkit.Forms.UI.XamlHost/6.0.0-preview6.4) developed on the [Windows Community Toolkit](https://github.com/windows-toolkit/Microsoft.Toolkit.Win32) site.


 ## Required steps to make this work
 
 There are several steps that you need to do to make work your WinForms/WPF project:

  1. To run XAML Islands is required to specify the max version tested property to at least 18362 in your WinForms/WPF app. In this sample, MyApp.manifest file is the app manifest, and it contains:

  ```xml
   <maxversiontested Id="10.0.18362.0"/>
   ```

2. Change the managed WinRT Component. It is called "managed" because it is using C# and requires a .NET runtime to run the code. Notice that UWP apps use  the __.NET Native__ implementation in Release mode and a sort of __.NET Core__ implementation for Debug mode.
To consume Managed WinRT components in Xaml Islands, you need to build your project with two options deactivated. Please, __modify your csproj project file and insert this property group__. Alternatively, you can add it to a _Directory.Build.props_ file:

    ```xml
    <PropertyGroup>
      <EnableTypeInfoReflection>false</EnableTypeInfoReflection>
      <EnableXBindDiagnostics>false</EnableXBindDiagnostics>
    </PropertyGroup>
    ```

 3. Copy all the XBF files used by the WinRT components that you want to use into the output directory. The XBF files are the binary compilation of the markup Xaml files. You can do it manually, but in this sample what I did was 1) to create a folder on the project, 2) add the files to it, 3) copy it to the output directory.

```xml
 <ItemGroup>
    <Folder Include="Managed_WinRT_Comp\" />
  </ItemGroup>
  <ItemGroup>
    <Content Include="..\Shared_Components\Managed_WinRT_Comp\bin\$(PlatformName)\$(ConfigurationName)\**\*.xbf" LinkBase="Managed_WinRT_Comp">
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </Content>
  </ItemGroup>
  ```
4. Copy all  the resources (images, videos, etc.) used by the WinRT components that you want to use into the output directory
```xml
  <ItemGroup>
    <Folder Include="Assets\" />
  </ItemGroup>
  <ItemGroup>
    <Content Include="..\Shared_Components\Managed_WinRT_Comp\Assets\**" LinkBase="Assets">
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </Content>
  </ItemGroup>
  ```


  5. When Visual Studio builds a Native WinRT Component, it generates, at least, the WinMD and the DLL files. 
  In the case of Native components, WinMD files are pure metadata and the dll contains the implementation. In the case of managed WinRT components, WinMD files include MSIL code, just like traditional CLR assemblies do.
  Visual Studio is not copying the libraries (*.dll files) of the Native WinRT components in the right folder. __You need to copy this DLL to the output folder__ as well. For example:
  ```xml
   <ItemGroup>
    <Content Include=".\Debug\Native_SwapChainPanel_Comp\Native_SwapChainPanel_Comp.dll">
      <Link>Native_SwapChainPanel_Comp.dll</Link>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </Content>
  </ItemGroup>
  ```
  6. When using Native WinRT Components in unpackaged applications, your WinFomrs/WPF app needs to deploy the Visual C++ Runtime Forwarders for running correctly. The __Microsoft VCRTForwarders Nuget packaged__ contains these libraries. Add the latest version to your project:

```xml
  <ItemGroup>
    <PackageReference Update="Microsoft.VCRTForwarders.140" Version="1.0.1-rc" />
  </ItemGroup>
```

7. For using Native WinRT Components, you need to register witch libraries (*.dll) contains the class implementation and the methods.  You need to use the [Registration-Free COM Interop mechanism](https://blogs.windows.com/windowsdeveloper/2019/04/30/enhancing-non-packaged-desktop-apps-using-windows-runtime-components/#Ttthb9vgHSs8G8YA.97) into your application manifest. For example, in the sample,  the MyApp.manifest file contains:  

```xml
  <file name="Native_SwapChainPanel_Comp.dll">
    <activatableClass
        name="Native_SwapChainPanel_Comp.Direct2DPanel"
        threadingModel="both"
        xmlns="urn:schemas-microsoft-com:winrt.v1" />
    <activatableClass
        name="Native_SwapChainPanel_Comp.CustomRenderer"
        threadingModel="both"
        xmlns="urn:schemas-microsoft-com:winrt.v1" />
  </file>
  ```
  
## Support language localization

 >These steps are tedious. Fortunately, the samples contain the "Directory.Build.targets" MSBuild tasks that do it automatically for you. Continue reading this long section if you are still insterested about how this work.

WinRT Components use the resw files to localize strings. You should follow the [guidelines](https://docs.microsoft.com/en-us/windows/uwp/app-resources/localize-strings-ui-manifest) for generating the localization correctly.  The content of these resw files isincluded into just one PRI file (resources.PRI) at build time. Your WinForms/WPF app uses this PRI file to load the resources at runtime.

>Note that __unpackaged UWP Xaml apps__ use the OS Setting of Window Display Language and __packaged UWP XAML apps__ use the Preferred Language Setting.

For generating the PRI files you can use MakePRI tool included with the Windows 10 SDK. You can do something like:

1. Open the Visual Studio 2019 Developer Command Prompt
2. Navigate into the project folderc. For instance:
```
 C:\repos\XamlIslands\1903_Samples\WPF_Core3_App
```

3. Create the Config fle: 
```
makepri createconfig /cf config.xml /dq x-generate /o
```

4. Edit config.xml files and remove the <packaging> section.
5. Create the PRI file: 
```
makepri new /pr . /cf config.xml /of resources.pri
```

   1. __Optional__: If you want to make sure that created PRI is right, dump it into a XML file and open it. You will see the localized strings at the end of the doc:

      ```				
      makepri dump /if resources.pri /of resources.pri.xml
      ```

6. Move the resources.pri file in the same folder of the .EXE and replace the existing one.

```
C:\repos\XamlIslands\1903_Samples\WPF_Core3_App\bin\x86\Debug\netcoreapp3.0
```

7. Run the app. You should see how the app resolve the resources.
   

## Packaging Projects

The WinForms/WPF Packaging Projects samples create an MSIX package that allow the app can be deployed into the Store. 

When you are running your WinForms/WPF app from a MSIX package, some behaviors of the WinRT APIs could change. For example, the localization mechanism. Unpackaged apps use the OS Setting of Window Display Language; however, packaged apps use the Preferred Language Setting.


### Copy WinMD files in the output folder 

The Windows Packaging Project doesn't copy the WinMD files to the right output folder for .NET Core 3 apps. It copies these files into the root folder that contains the app files structure. 

You can copy your WinMD files manually close to your EXE. This should fix this the issue. 

Another way to fix it is applying the workaround described in point 6 at [Package a desktop app from source code using Visual Studio](https://docs.microsoft.com/en-us/windows/msix/desktop/desktop-to-uwp-packaging-dot-net#create-a-package).

```xml
<!-- Stomp the path to application executable. This task will copy the main exe to the appx root folder. -->
<Target Name="_StompSourceProjectForWapProject" BeforeTargets="_ConvertItems">
  <ItemGroup>
    <!-- Stomp all "SourceProject" values for all incoming dependencies to flatten the package. -->
    <_TemporaryFilteredWapProjOutput Include="@(_FilteredNonWapProjProjectOutput)" />
    <_FilteredNonWapProjProjectOutput Remove="@(_TemporaryFilteredWapProjOutput)" />
    <_FilteredNonWapProjProjectOutput Include="@(_TemporaryFilteredWapProjOutput)">
      <!-- Blank the SourceProject here to vend all files into the root of the package. -->
      <SourceProject></SourceProject>
    </_FilteredNonWapProjProjectOutput>
  </ItemGroup>
</Target>
```

This task was included on the __Directory.Build.targets__ in the sample.

### Fix localization issues 
As it was described before, you require to have a resources.PRI file with the localized content. You can use MakePRI for generating the PRI files. For WPF/WinForms packaged apps, you also need to specify the __package manifest__. For example, Package.appxmanifest file. 
```bash
makepri new /pr . /cf config.xml /of resources.pri /mn Package.appxmanifest
```

>Specify the package manifest is not necessary for unpackaged apps.

To simplify this process, the sample is using the __Directory.Build.targets__ MSBuild target file that contains these tasks. 
 