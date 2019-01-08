using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WPFAppWithWindowsXamlHost
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void WindowsXamlHost_XamlRootChanged(object sender, EventArgs e)
        {
            Windows.UI.Xaml.Controls.Button button = (Windows.UI.Xaml.Controls.Button)windowXamlHost.Child;
            if (button != null)
            {
                button.Content = "XAML Button";
                button.Click += Button_Click;
            }
        }

        private void Button_Click(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            string label = (sender as Windows.UI.Xaml.Controls.Button).Content as string;
            textBlock.Text = $"{label} - {DateTime.Now.ToLongTimeString()}";
        }
    }
}
