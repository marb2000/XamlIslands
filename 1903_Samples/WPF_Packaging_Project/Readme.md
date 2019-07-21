# Making this work

This project is the packaging project for the WPF/WinForms app. It creates an MSIX app that can be deployed into the Store. Also, it changes the behavior of some UWP APIs: for instance, the localization mechanism. Unpackaged UWP Xaml apps use the OS Setting of Window Display Language; however, packaged UWP XAML apps use the Preferred Language Setting.

## Fix localization issues 

You can localize your WinRT components using the resw files. Remember, follow the guidelines to generate the localization assets correctly.  These resources files are included in just one PRI file (resources.PRI) at build time. Your package WPF app will use this file to load the resources.

You can use MakePRI for generating the PRI files. The MakePRI tool is included with the Windows 10 SDK. For WPF/WinForms package apps, you need to specify the package manifest (For example, Package.appxmanifest file). Specify the package manifest is not necessary for unpackaged apps.

To simplify this process, this sample is using a MSBUILD target file that contains these tasks: 
```
Directory.Build.targets
```

## Fix lack of the WinMd files in the output folder 

Besides creating the PRI files, these MSBuild tasks workaround a second issue with the "winmd" files. These files are no copied to the right Output folder. The tasks do this:

```xml
<Exec Command="XCopy &quot;$(TargetDir)Appx&quot;\*.winmd  &quot;$(TargetDir)Appx\$(SolutionName)&quot;\ /Y /F" />
```
