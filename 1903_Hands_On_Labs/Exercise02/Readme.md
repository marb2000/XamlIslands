# How to create a WinForms .NET Core 3 with XAML Islands

## Adding the WindowsXamlHost to your WinForms app
1. Create a WinForms App (.NET Core), for instance WinForms_XAMLIslands_v1.
2. Target a specifc platform, for instance x86 or x64. UWP XAML controls do no work on Any CPU. 
    Right Click on the Solution -> Properties -> Configuration Properties -> Configuration Manager. In the Active solution platform drop down, select <new...>. The New Solution Platformn dialog shows up; then select x64 and Press OK. Close all the dialogs and return to the Visual Studio code editor. Your project should target now x64.

3. Add the latest preview of the [Microsoft.Toolkit.Forms.UI.XamlHost](https://www.nuget.org/packages/Microsoft.Toolkit.Forms.UI.XamlHost/6.0.0-preview7?_src=template) NuGet Package to the WinForms app.

4. Use the WindowsXamlHost control to host a XAML Island and inside of it, create a CalendarView UWP inbox control. To do it, add the following code to the Form1.cs
```cs
public partial class Form1 : Form
{
        private Microsoft.Toolkit.Forms.UI.XamlHost.WindowsXamlHost windowsXamlHost;

        public Form1()
        {
            InitializeComponent();
            this.windowsXamlHost = new Microsoft.Toolkit.Forms.UI.XamlHost.WindowsXamlHost();
            this.windowsXamlHost.InitialTypeName = "Windows.UI.Xaml.Controls.CalendarView";
        
            this.windowsXamlHost.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            this.windowsXamlHost.Location = new System.Drawing.Point(0, 0);
            this.windowsXamlHost.Name = "windowsXamlHost";
            this.windowsXamlHost.Size = new System.Drawing.Size(800, 800);
            this.windowsXamlHost.TabIndex = 0;
            this.windowsXamlHost.Text = "windowsXamlHost";
            this.windowsXamlHost.Dock = System.Windows.Forms.DockStyle.Fill;

            //Adding the WindowsXamlHost to the Form
            this.Controls.Add(this.windowsXamlHost);
            //Setting the title of the Form
            this.Text = "WinForms .Net Core 3 and Xaml Islands";

            this.ResumeLayout(false);
            
        }
}
```
   
 >__Note:__ Inbox controls are the controls included in the Windows 10 OS.

5.Build the solution (press F5). 

## Creating the XAML application object

To consume WinRT XAML components is required to have an Application object. The WindowsXamlHost wrapper will look for it when creating the Islands. In case you don't have one, it creates one Application for you, however, there is no guarantee this Application object works for all the scenarios. The guideline is to __have always one WinRT Application object in your app__. This Application object should derive from XamlApplication. All the XAML Islands share the same Application object, so just one Application object is required. 

1. Add to your Solution a Blank App (Universal Windows) project. You can called CustomXamlApplication, for example.
2. Select Build 18362 for both Target version and Minimun version. 
3. Add the [Microsoft.Toolkit.Win32.UI.XamlApplication](https://www.nuget.org/packages/Microsoft.Toolkit.Win32.UI.XamlApplication/6.0.0-preview6.4?_src=template) NuGet package to this UWP XAML app.
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
6. Change the App.xaml.cs class to make it derive from XamlApplication, call this.Initialize() method, and remove the rest of the code. Your code behind should be similar to:

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
7. This project is a UAP app that generates a EXE, and we did it because the UWP Blank Application generates an Application object a setup the XAML compiler to generates the types of this project and its dependencies. To generates libreray, a WinMD File, you should change the type of the this project. So unload the project and edit it. Change the OutputType property, that has AppContainerExe value, for Library.   
```xml
<OutputType>Library</OutputType>
```
8. Load the UWP project again.

### Testing that everything is still OK 

1. In the MainPage.xaml of the UWP app, add this code:
```xml
<TextBlock Text="Hello World!" />
```
2. Add a Reference to the UWP project to the WinForms project

3. Change initial type of the WindowsXamlHost object to use this new UWP type:
```
    this.windowsXamlHost.InitialTypeName = "CustomXamlApplication.MainPage";

```
4. Press F5. You should see Hello World.

## Adding the Windows Application Packaging Project
1. Add a new Windows Windows Application Packaging Project to the solution. You can name it WAP, for instance. 

2. Select Build 18362 for Target version and Minimun version.

3. In the Applications section, add a reference to the WinForms App.

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

## Adding a Managed Class Library
1. Add a new Managed Class Library (Universal Windows) project to the solution. Let's call it MyClassLibrary. 
    >  It is called "Managed" because the library is using C# and requires a .NET Runtime to run the code. Notice that UWP apps use the .NET Native implementation in Release mode and a sort of .NET Core implementation for Debug mode. 
2. Select Build 18362 for both Target version and Minimun version.

3. To consume Managed WinRT components in XAML Islands, you need to build your library with two options deactivated.  Unload the project, modify insert the following property group, and load the project again: 
```xml
<PropertyGroup>
  <EnableTypeInfoReflection>false</EnableTypeInfoReflection>
  <EnableXBindDiagnostics>false</EnableXBindDiagnostics>
</PropertyGroup>
```

4. Remove the Class1.cs file

5. Add a new Xaml User Control item. Right click on the project, Add new Item, and Select User Control. Name it WelcomePage.xaml and paste:
```xml
    <Grid>
        <StackPanel HorizontalAlignment="Center" Spacing="10" Padding="20" VerticalAlignment="Center">
            <TextBlock x:Uid="WelcomeHeader" x:Name="HeaderTB" HorizontalAlignment="Center" TextWrapping="Wrap" Text="Hello from Xaml Islands" FontSize="30" />
            <TextBlock HorizontalAlignment="Center" Margin="15" TextWrapping="Wrap" Text="😍❤💋🌹🎉😎�🐱‍👤" FontSize="16" />
            <TextBlock x:Name="WelcomeDescriptionTB" HorizontalAlignment="Center" TextWrapping="WrapWholeWords" Margin="10" Text="This is a sample" FontSize="16" />
        </StackPanel>
    </Grid>
```
6. In the WinForms app, add a reference to the MyClassLibrary. And modify the Form1.cs
```cs
   this.windowsXamlHost.InitialTypeName = "MyClassLibrary.WelcomePage";
```
7. The UWP XAML Application needs to reference this Class Library. In the CustomXamlApplication project, add a reference to MyClassLibrary project. 
8. Press F5, It should work

### Testing in Unpackaged scenario
1. Select the WinForms_XAMLIslands_v1 project as Startup project.
2. Press F5. You should see the Welcome page. 