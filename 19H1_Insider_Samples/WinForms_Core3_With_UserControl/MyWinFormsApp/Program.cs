using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyWinFormsApp
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //This is a workaround for making work the Preview 4
            System.Runtime.CompilerServices.RuntimeHelpers.RunClassConstructor(typeof(Microsoft.Toolkit.Forms.UI.XamlHost.WindowsXamlHostBase).TypeHandle);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
