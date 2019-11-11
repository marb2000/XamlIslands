using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyWinFormsApp
{
    public partial class MainForm : Form
    {
        public MainForm(bool runTest = true)
        {
            InitializeComponent();

            this.windowsXamlHost1.InitialTypeName = "Samples.ManagedWinRT.MainPage";
            this.runTest = runTest;

            tonsOfMemory = new byte[1024 * 1024 * 100];
        }

        public bool runTest;
        byte[] tonsOfMemory;

        protected override void OnLayout(LayoutEventArgs levent)
        {
            base.OnLayout(levent);

            if (global::Samples.ManagedWinRT.MainPage.NewWinForm == null)
            {
                global::Samples.ManagedWinRT.MainPage.NewWinForm = MainForm.NewWinForm;
            }

            if (runTest)
            {
                OpenWindows();
            }
        }

        public async void OpenWindows()
        {
            var numWindows = 100;
            MainForm form;

            for(int i = 0; i < numWindows; i++)
            {
                form = new MainForm(false);
                form.Show();
                await Task.Delay(1000);
                form.Close();
            }
        }

        static public void NewWinForm()
        {
            MainForm form = new MainForm(false);
            form.Show();
        }
    }
}
