using System.Diagnostics;
using System.Windows;
using System.Windows.Interop;
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

        IntPtr UIWindowHWND;
        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            UIWindowHWND = new WindowInteropHelper(this).Handle;



            if (Module.Helper.InitHook(UIWindowHWND) != -1)
            {

            }

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Debug.WriteLine("Cluck");
        }
    }
}