using Windows.UI.Core;
using Windows.UI.Input.Inking;
using Windows.UI.Xaml.Controls;

namespace MyUWPLib
{

    public sealed partial class MediaPage : Page
    {
        private InkPresenter inkPresenter;
        public MediaPage()
        {
            this.InitializeComponent();
            inkPresenter = inkCanvas.InkPresenter;
            inkPresenter.InputDeviceTypes =
                CoreInputDeviceTypes.Mouse | CoreInputDeviceTypes.Pen | CoreInputDeviceTypes.Touch;
        }
    }
}
