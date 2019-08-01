# How to create a WPF .NET Core 3 with XAML Islands

## Adding the WindowsXamlHost to your WPF app
1. Create a WPF App (.NET Core), for instance WPF_XAMLIslands_v1.

2. Add the latest preview of the [Microsoft.Toolkit.Wpf.UI.XamlHost](https://www.nuget.org/packages/Microsoft.Toolkit.Wpf.UI.XamlHost/6.0.0-preview7?_src=template) NuGet Package to the WPF app.

3. Add the namespace of the Microsoft.Toolkit.Wpf.UI.XamlHost library into the MainWindow:
```xml
xmlns:xaml="clr-namespace:Microsoft.Toolkit.Wpf.UI.XamlHost;assembly=Microsoft.Toolkit.Wpf.UI.XamlHost"
```

4. Use the WindowXamlHost control with a inbox control. In this case the ColorPicker. 
```XML
 <xaml:WindowsXamlHost InitialTypeName="Windows.UI.Xaml.Controls.ColorPicker" />
 ```

 >__Note:__ Inbox controls are the controls included in the Windows 10 OS.

 5. Before compiling, you need to target a specifc platform, for instance x86 or x64. UWP XAML controls do no work on Any CPU. 
    Right Click on the Solution -> Properties -> Configuration Properties -> Configuration Manager. In drop donw the Active solution platform adn select <new...>. In the New Solution Platformn dialog, select x64 and Press OK. Close all the dialogs and return to the Code editor of Visual Studio. You should see that now your project targets to x64.

 6. Build the solution, for instance pressing F5.

## Creating the XAML application object

To consume WinRT XAML components is required to have an Application object. The WindowsXamlHost wrapper will look for it when creating the Islands. In case you don't have one, it creates one Application for you, however, there is no guarantee this Application object works for all the scenarios. The guideline is to __have always one WinRT Application object in your app__. This Application object should derive from XamlApplication. All the XAML Islands share the same Application object, so just one Application object is required. 

1. Add to your Solution a Blank App (Universal Windows) project. You can called CustomXamlApplication, for example.
2. Select Build 18362 for Target version and Minimun version. 

3. Add the [Microsoft.Toolkit.Win32.UI.XamlApplication](https://www.nuget.org/packages/Microsoft.Toolkit.Win32.UI.XamlApplication/6.0.0-preview7?_src=template) NuGet package to this UWP XAML app.

4. Into the App.xaml file, add the namespace:
```xml
xmlns:xaml="using:Microsoft.Toolkit.Win32.UI.XamlHost"
```
5. Modify the Application object so it derives from Xaml Application:
```xml
<xaml:XamlApplication
    x:Class="CustomXamlApplication.App"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:xaml="using:Microsoft.Toolkit.Win32.UI.XamlHost"
    xmlns:local="using:CustomXamlApplication">

</xaml:XamlApplication>
```
6. Change the App.xaml.cs class to make it derive from XamlApplication, call this.Initialize() method,  and remove the rest of the code. Your code behind should be similar to:

```cs
namespace CustomXamlApplication
{
    sealed partial class App : Microsoft.Toolkit.Win32.UI.XamlHost.XamlApplication
    {
        public App()
        {
            this.Initialize();
        }
    }
}
```
 This project is a UAP app that generates a EXE, and we did it because the UWP Blank Application generates an Application object a setup the XAML compiler to generates the types of this project and its dependencies. To generates libreray, a WinMD File, you should change the type of the this project. So unload the project and edit it. Change the OutputType property, that has AppContainerExe value, for Library.   
```xml
<OutputType>Library</OutputType>
```
8. Load the UWP project again.
### Testing that everything is still OK 

1. In the MainPage.xaml of the UWP app, add this code:
```xml
<TextBlock Text="Hello World!" />
```
2. In the WPF app, add a Reference to this project to the UWP project. 

3. Change MainWindow.xaml to use this new type:
```
<xaml:WindowsXamlHost InitialTypeName="CustomXamlApplication.MainPage" />
```
4. Press F5 and you should see Hello World.

## Adding the Windows Application Packaging Project
1. Add a new Windows Windows Application Packaging (WAP) Project to the solution. 

2. Select Build 18362 for Target version and Minimun version.

3. In the Applications section, add a reference to the WPF App.

4. Set this WAP project as the Startup project.

5. Press F5. __[BUG: It doesn't work]__

## Adding the Windows Application Packaging Project
1. Add a new Windows Windows Application Packaging Project to the solution. You can name it WAP, for instance. 

2. Select Build 18362 for Target version and Minimun version.

3. In the Applications section, add a reference to the WPF App.

4. Set this WAP project as the Startup project.

5. Press F5. __[BUG: It doesn't work. Apply the following hack]__

### The Hack for making work WAP with XAML Islands

1. Unload the WAP project.
2. Remove the import:
```xml
<Import Project="$(WapProjPath)\Microsoft.DesktopBridge.targets" />

```
3. Add the following MSBuild tasks:
```xml
 <ItemGroup>
    <SDKReference Include="Microsoft.VCLibs,Version=14.0">
      <TargetedSDKConfiguration Condition="'$(Configuration)'!='Debug'">Retail</TargetedSDKConfiguration>
      <TargetedSDKConfiguration Condition="'$(Configuration)'=='Debug'">Debug</TargetedSDKConfiguration>
      <TargetedSDKArchitecture>$(PlatformShortName)</TargetedSDKArchitecture>
      <Implicit>true</Implicit>
    </SDKReference>
  </ItemGroup>
  
  <Import Project="$(WapProjPath)\Microsoft.DesktopBridge.targets" />
  
  <Target Name="_StompSourceProjectForWapProject" BeforeTargets="_ConvertItems">
    <ItemGroup>
      <_TemporaryFilteredWapProjOutput Include="@(_FilteredNonWapProjProjectOutput)" />
      <_FilteredNonWapProjProjectOutput Remove="@(_TemporaryFilteredWapProjOutput)" />
      <_FilteredNonWapProjProjectOutput Include="@(_TemporaryFilteredWapProjOutput)">
        <SourceProject>
        </SourceProject>
      </_FilteredNonWapProjProjectOutput>
    </ItemGroup>
  </Target>
```
4. Copy the __Splashscreen.png__ file into the project. select teh file SplashScreen.scale-200.png. 
5. Press Ctrl+C, Ctrl+V. 
6. Rename the copy to SplashScreen.png 

Press F5. It should work.


## Adding an additional controls
1. Add a new Class Library (Universal Windows) project to the solution. Let's call it MyClassLibrary.
2. Select Build 18362 for both Target version and Minimun version.

3. Remove the Class1.cs file

4. Add a new Xaml User Control item. Right click on the project, Add new Item, and Select User Control. Name it WelcomePage.xaml and paste:
```xml
    <Grid>
        <StackPanel HorizontalAlignment="Center" Spacing="10" Padding="20" VerticalAlignment="Center">
            <TextBlock x:Uid="WelcomeHeader" x:Name="HeaderTB" HorizontalAlignment="Center" TextWrapping="Wrap" Text="Hello from Xaml Islands" FontSize="30" />
            <TextBlock HorizontalAlignment="Center" Margin="15" TextWrapping="Wrap" Text="😍❤💋🌹🎉😎�🐱‍👤" FontSize="16" />
            <TextBlock x:Name="WelcomeDescriptionTB" HorizontalAlignment="Center" TextWrapping="WrapWholeWords" Margin="10" Text="This is a sample" FontSize="16" />
        </StackPanel>
    </Grid>
```
4. In the WPF app, add a reference to the MyClassLibrary. And modify the MainWindow.xaml
```xml
 <xaml:WindowsXamlHost InitialTypeName="MyClassLibrary.WelcomePage" />
```
5. The UWP XAML Application needs to reference this Class Library. In the CustomXamlApplication project, add a reference to MyClassLibrary project. 
6. Press F5, It should work.

### Testing in Unpackaged scenario
1. Select the WPF_XAMLIslands_v1 project as Startup project.
2. Press F5 __[BUG: The app crash]__ 













