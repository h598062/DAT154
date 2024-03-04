using System.Windows;
using System.Windows.Input;

namespace Routed_Events___Bubbling
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            inner.MouseUp += Inner_MouseUp;
            outer.MouseUp += Outer_MouseUp;
        }

        void Outer_MouseUp(object sender, MouseButtonEventArgs e)
        {
            MessageBox.Show("Groupbox clicked!");
            e.Handled = true;
        }

        void Inner_MouseUp(object sender, MouseButtonEventArgs e)
        {
            MessageBox.Show("Label Clicked!");
            e.Handled = true;
        }

    }
}
