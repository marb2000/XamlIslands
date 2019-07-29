using Microsoft.Toolkit.Wpf.UI.XamlHost;
using System;
using System.Windows;
using Windows.UI.Core;

namespace InkCanvasWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void WindowsXamlHost_ChildChanged(object sender, EventArgs e)
        {
            var grid = (sender as WindowsXamlHost).Child as Windows.UI.Xaml.Controls.Grid;
            if (grid == null) return;

            var gridInkCanvas = new Windows.UI.Xaml.Controls.Grid();
            gridInkCanvas.Background = new Windows.UI.Xaml.Media.SolidColorBrush(Windows.UI.Colors.White);
            var inkCanvas = new Windows.UI.Xaml.Controls.InkCanvas();
            gridInkCanvas.Children.Add(inkCanvas);
            gridInkCanvas.SetValue(Windows.UI.Xaml.Controls.Grid.RowProperty, 1);
            inkCanvas.InkPresenter.InputDeviceTypes = CoreInputDeviceTypes.Mouse | CoreInputDeviceTypes.Pen | CoreInputDeviceTypes.Touch;


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
    }
}
