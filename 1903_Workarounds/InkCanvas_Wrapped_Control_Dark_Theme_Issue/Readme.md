
# __Bug__: _User Experience for the InkCanvas/InToolbar WPF/WinForms wrapped controls is degrated in Dark theme._

The XAML InkCanvas control sets the background color for the canvas automatically to black or white, depending on the system theme. The default InkToolbar colors for pen/pencil are black, so in dark theme, the user is stuck with a black brush on a black background. 

Users report this issue: https://github.com/windows-toolkit/Microsoft.Toolkit.Win32/issues/16#issuecomment-515818643 

One possible solution is that the InkCanvas Wrapped control for WPF/WinForms exposes the background color. So that app dev can set the color that they want.  However, the XAML InkCanvas doesn't have background property. 

This following is a suggested workaround for this scenario:

1. Use the WindowXamlHost control with a UWP Grid as XAML Island type. The WindowsXamlHost control is in the NuGet package [Microsoft.Toolkit.Wpf.UI.XamlHost](https://www.nuget.org/packages/Microsoft.Toolkit.Wpf.UI.XamlHost/6.0.0-preview6.4)
```xaml
<Window
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
        xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
        xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
        xmlns:local="clr-namespace:InkCanvasWrapperWPF"
        xmlns:xamlHost="clr-namespace:Microsoft.Toolkit.Wpf.UI.XamlHost;assembly=Microsoft.Toolkit.Wpf.UI.XamlHost"
        mc:Ignorable="d"
        Title="MainWindow" Height="450" Width="800">
    <Grid>
         <xamlHost:WindowsXamlHost Grid.Row="1"
            InitialTypeName="Windows.UI.Xaml.Controls.Grid" 
            ChildChanged="WindowsXamlHost_ChildChanged" />

    </Grid>
</Window>
```
2. In the code behind, create the InkCanvas and InkToolbar. The InkCanvas is wrapped by a Grid with the White color as background. The other grid is just for layout proposals.

```cs
 private void WindowsXamlHost_ChildChanged(object sender, EventArgs e)
        {
            var grid = (sender as WindowsXamlHost).Child as Windows.UI.Xaml.Controls.Grid;
            if (grid == null) return;

            var gridInkCanvas = new Windows.UI.Xaml.Controls.Grid();
            gridInkCanvas.Background = new Windows.UI.Xaml.Media.SolidColorBrush(Windows.UI.Colors.White);
            var inkCanvas = new Windows.UI.Xaml.Controls.InkCanvas();
            gridInkCanvas.Children.Add(inkCanvas);
            gridInkCanvas.SetValue(Windows.UI.Xaml.Controls.Grid.RowProperty, 1);

            var inkToolbar = new Windows.UI.Xaml.Controls.InkToolbar();
            inkToolbar.TargetInkCanvas = inkCanvas;
            inkToolbar.SetValue(Windows.UI.Xaml.Controls.Grid.RowProperty, 0);

            var firstRow = new Windows.UI.Xaml.Controls.RowDefinition();
            firstRow.Height = new Windows.UI.Xaml.GridLength(1, Windows.UI.Xaml.GridUnitType.Auto);
            var secondRow = new Windows.UI.Xaml.Controls.RowDefinition();
            secondRow.Height = new Windows.UI.Xaml.GridLength(1, Windows.UI.Xaml.GridUnitType.Star);
            grid.RowDefinitions.Add(firstRow);
            grid.RowDefinitions.Add(secondRow);

            grid.Children.Add(gridInkCanvas);
            grid.Children.Add(inkToolbar);
        }
```




