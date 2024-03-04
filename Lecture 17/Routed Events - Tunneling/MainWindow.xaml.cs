using System.Windows;
using System.Windows.Input;

namespace Routed_Events___Tunneling
{

    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            inner.PreviewMouseUp += Inner_MouseUp;
            outer.PreviewMouseUp += Outer_MouseUp;

            
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
