using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SpaceSimGUI;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
    }

    private void StartKnapp_OnClick(object sender, RoutedEventArgs e)
    {
        StartKnapp.Visibility = Visibility.Hidden;
        Console.WriteLine("Wallah");
        Ellipse eclipse = new Ellipse
        {
            Width = 100,
            Height = 100,
            Fill = Brushes.Red,
            Margin = new Thickness(1),
            Stroke = Brushes.Black,
            ToolTip = "This is a planet!"
        };
        SimCanvas.Children.Add(eclipse);
    }
}