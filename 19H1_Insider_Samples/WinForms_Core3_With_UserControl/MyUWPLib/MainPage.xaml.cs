using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

namespace MyUWPLib
{
    public sealed partial class MainPage : UserControl
    {
        public MainPage()
        {
            this.InitializeComponent();
            contentFrame.Navigate(typeof(WelcomePage),null);
        }

        private void NavView_ItemInvoked(NavigationView sender, NavigationViewItemInvokedEventArgs args)
        {
            FrameNavigationOptions navOptions = new FrameNavigationOptions();
            navOptions.TransitionInfoOverride = args.RecommendedNavigationTransitionInfo;

            Type pageType = null;
            NavigationViewItem nvi = args.InvokedItemContainer as NavigationViewItem;
            if (nvi != null)
            {

                switch (nvi.Tag)
                {
                    case "WelcomePage":
                        pageType = typeof(WelcomePage);
                        break;
                    case "BasicInputPage":
                        pageType = typeof(BasicInputPage);
                        break;
                    case "CollectionsPage":
                        pageType = typeof(CollectionsPage);
                        break;
                    case "DateAndTimePage":
                        pageType = typeof(DateAndTimePage);
                        break;
                    case "DialogsAndFlyoutsPage":
                        pageType = typeof(DialogsAndFlyoutsPage);
                        break;
                    case "LayoutPage":
                        pageType = typeof(LayoutPage);
                        break;
                    case "MediaPage":
                        pageType = typeof(MediaPage);
                        break;
                    case "MenuToolbarPage":
                        pageType = typeof(MenuToolbarPage);
                        break;
                    case "TextPage":
                        pageType = typeof(TextPage);
                        break;
                    case "RevealPage":
                        pageType = typeof(RevealPage);
                        break;
                    case "AnimationsPage":
                        pageType = typeof(AnimationsPage);
                        break;

                }
                if (pageType != null)
                {
                    contentFrame.NavigateToType(pageType, null, navOptions);
                }
            }
            
        }
    }
}
