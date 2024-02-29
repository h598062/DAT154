using System.Windows;
using System.Windows.Media;

namespace _2___WPF {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void QuitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string txt = txtField.Text;

            if (txt.Length > 0)
            {
                byte r = (byte)(txt.Length * 5 % 255);
                byte g = (byte)(txt[..1].ToCharArray()[0] * 5 % 255);
                byte b = (byte)((r + g) % 255);

                Background = new SolidColorBrush(Color.FromRgb(r, g, b));

            }
        }
    }
}
