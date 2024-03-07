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
using SpaceSimLib;

namespace SpaceSimGUI;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{
    private Solarsystem _solarsystem;
    
    private List<Ellipse> _ellipses = [];
    
    public MainWindow()
    {
        InitializeComponent();
        _solarsystem = new Solarsystem();
    }

    private void StartKnapp_OnClick(object sender, RoutedEventArgs e)
    {
        StartKnapp.Visibility = Visibility.Hidden;
        Console.WriteLine("Wallah");
        
        Ellipse sun = new Ellipse
        {
            Name = _solarsystem.Sun.Name.Replace(" ", ""),
            Width = 100,
            Height = 100,
            Fill = Brushes.Yellow,
            Margin = new Thickness(1),
            Stroke = Brushes.Black,
            ToolTip = _solarsystem.Sun.Name
        };
        SimCanvas.Children.Add(sun);
        _ellipses.Add(sun);
        Canvas.SetLeft(sun, _solarsystem.Sun.GetPosition(0).X - sun.Width / 2 + SimCanvas.RenderSize.Width / 2);
        Canvas.SetTop(sun, _solarsystem.Sun.GetPosition(0).Y - sun.Height / 2 + SimCanvas.RenderSize.Height / 2);
    }
}