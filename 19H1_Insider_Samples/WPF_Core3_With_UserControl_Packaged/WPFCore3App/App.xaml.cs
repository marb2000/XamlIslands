using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace MyCoreConsole
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        App()
        {
            InitializeComponent();

            // Workaround in DotNET Core preview4
            // An static field is not initialized: Microsoft.Toolkit.Wpf.UI.XamlHost.WindowsXamlHostBase._metadataContainer
            // Here: https://github.com/windows-toolkit/Microsoft.Toolkit.Win32/blob/master/Microsoft.Toolkit.Wpf.UI.XamlHost/WindowsXamlHostBase.cs#L30
            System.Runtime.CompilerServices.RuntimeHelpers.RunClassConstructor(typeof(Microsoft.Toolkit.Wpf.UI.XamlHost.WindowsXamlHostBase).TypeHandle);
        }
    }
}
