# Some notes about how this work


This project is a WPF .NET Core 3 app where the UI is only UWP Xaml. 

The MainWindow.xaml file contains the instance of the WindowsXamlHost control. This control is a NET wrapper for the Operating System APIs that implement the Xaml Islands.
```XML
<StackPanel>
    <xamlhost:WindowsXamlHost InitialTypeName="Samples.ManagedWinRT.MainPage" />
 </StackPanel>
```
 This control is on the Microsoft.Toolkit.Wpf.UI.XamlHost Nuget Packaged developed on the Windows Community Toolkit site.

 ## Steps to I did to make this work

 The Visual Studio support for Xaml Islands is still in development, so there are several things that you need to do to make work your project:

  1. To running Xaml Islands is requried to specify the maxversiontested property to at least 18362. In this sample, MyApp.manifest file is the app manifest and it contains:

  ```xml
   <maxversiontested Id="10.0.18362.0"/>
   ```

 2. Copy all  the XBF files used by the WinRT components that you want to use into the OutPut directory. The XBF files are the binary compilation of the markup Xaml files. You can do it manually, but in this sample what I did was 1) to create a folder on the project, 2) add the files to it, 3) copy it to the output directorty.

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
3. Copy all  the resources (images, videos, etc) used by the WinRT components that you want to use into the OutPut directory
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


  4. Visual Studio is not copying the dll of the Native WinRT components. You have to copy to the output foler as well. In this case I did this:
  ```xml
   <ItemGroup>
    <Content Include=".\Debug\Native_SwapChainPanel_Comp\Native_SwapChainPanel_Comp.dll">
      <Link>Native_SwapChainPanel_Comp.dll</Link>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </Content>
  </ItemGroup>
  ```
  5. When using Native WinRT Components in unpackaged applications, your WPF app needs to deploy the Visual C++ Runtime Forwarders for running properly. The Microsoft.VCRTForwarders Nuget packaged contains it. Add the latest version to your project:

```xml
  <ItemGroup>
    <PackageReference Update="Microsoft.VCRTForwarders.140" Version="1.0.1-rc" />
  </ItemGroup>
```

6. For using Native WinRT Components, you need to register with dll contains the class implementation and the methods. Add to your App manifest file this section. In this sample, MyApp.manifest file is the app manifest and it contains:  

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
  
## About localization

You can localize your WPF app using the UWP mechanism. When developing your app, your WinRT components can use the resw files. Follow the guidelines for generate the localization correctly.  These files are included into the a big PRI file (resources.PRI) at build time. Your WPF app will use this file to load the resources.

    Unpackaged UWP Xaml apps use the OS Setting of Window Display Language.  Packaged UWP XAML apps use the Preferred Language Setting.

For generating the PRI files you can use MakePRI. This tool is included with the Windows 10 SDK. You can do something like:

1. Open the Visual Studio 2019 Developer Command Prompt
2. Navigate into the project folderc. For instance:
```
 C:\repos\XamlIslands\1903_Samples\WPF_Core3_App
```

3. Create the Config fle: 
```
makepri createconfig /cf config.xml /dq x-generate /o
```

4. Edit config.xml files and remove the <packaging> section:
5. Create the PRI file: 
```
makepri new /pr . /cf config.xml /of resources.pri
```

6. [Optional] if you want to make sure that PRI was created properly, dump it into a XML and open it later. At the end of the doc, you will see the localized Strings

```				
makepri dump /if resources.pri /of resources.pri.xml

Ex: open it with Visual Studio Code:
code resources.pri.xml
```

7. Move this resources.pri file in the same folder of the .EXE and replace the existing one.

```
C:\repos\XamlIslands\1903_Samples\WPF_Core3_App\bin\x86\Debug\netcoreapp3.0
```

8. Run the app, and you should see how the app resolve the resources.
   
### Making Tasks for MSBuild and simplify this a little


All these steps are realy tedious, so I created some MSBuild tasks to make this a little simple. You can find it at __Directory.Build.targets__.





 