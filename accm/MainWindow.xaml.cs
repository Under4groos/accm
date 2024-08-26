using accm.Module;
using System.Diagnostics;
using System.Windows;

namespace accm
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();


            this.Loaded += MainWindow_Loaded;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            __key_down kd = (int key) =>
            {
                Debug.WriteLine(key);
            };
            int i = Module.Helper.InitHook(kd);
        }
    }
}