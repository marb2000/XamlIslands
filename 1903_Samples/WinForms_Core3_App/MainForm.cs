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
        public MainForm()
        {
            InitializeComponent();

            this.windowsXamlHost1.InitialTypeName = "Samples.ManagedWinRT.MainPage";
        }

        protected override void OnLayout(LayoutEventArgs levent)
        {
            base.OnLayout(levent);

            if (global::Samples.ManagedWinRT.MainPage.NewWinForm == null)
            {
                global::Samples.ManagedWinRT.MainPage.NewWinForm = MainForm.NewWinForm;
            }
        }

        static public void NewWinForm()
        {
            MainForm form = new MainForm();
            form.Show();
        }
    }
}
