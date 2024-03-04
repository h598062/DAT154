using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Routed_Events {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            inner.MouseUp += (s, e) =>
            {
                ((Label)s).Background = Brushes.Green;
                ((Label)s).Foreground = Brushes.White;

            };

          


            //inner.MouseUp += Inner_MouseUp;
        }

        private void Inner_MouseUp(object sender, MouseButtonEventArgs e)
        {
            ((Label)sender).Background = Brushes.Green;
            ((Label)sender).Foreground = Brushes.White;
        }
    }
}
