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
    private readonly System.Windows.Threading.DispatcherTimer timer;

    private List<Ellipse> ellipses = [];

    // orbit i 1 = 1000km
    private long largestOrbit = 0;

    private int dag = 0;

    public MainWindow()
    {
        InitializeComponent();

        _solarsystem = new Solarsystem();
        foreach (var spaceObject in _solarsystem.SolarSystem)
        {
            if (spaceObject is OrbitalBody orbitalBody && orbitalBody.OrbitalRadiuskKm > largestOrbit)
            {
                largestOrbit = orbitalBody.OrbitalRadiuskKm;
            }
        }

        timer = new System.Windows.Threading.DispatcherTimer
        {
            Interval = new TimeSpan(20000)
        };
        timer.Tick += Tick;
    }

    private void Tick(object sender, EventArgs e)
    {
        dag++;
        foreach (var ellipse in ellipses)
        {
            var spaceObject = _solarsystem.SolarSystem.Find(x => x.Name.Replace(" ", "") == ellipse.Name);
            if (spaceObject == null) continue;
            Canvas.SetLeft(ellipse,
                Map(spaceObject.GetPosition(dag).X, -largestOrbit, largestOrbit, 0, (float)SimCanvas
                    .RenderSize
                    .Width) - ellipse.Width / 2);
            Canvas.SetTop(ellipse,
                Map(spaceObject.GetPosition(dag).Y, -largestOrbit, largestOrbit, 0,
                    (float)SimCanvas.RenderSize.Height) - ellipse.Height / 2);
        }
    }

    private void StartKnapp_OnClick(object sender, RoutedEventArgs e)
    {
        StartKnapp.Visibility = Visibility.Hidden;
        Console.WriteLine("StartKnapp");

        Ellipse sun = new Ellipse
        {
            Name = _solarsystem.Sun.Name.Replace(" ", ""), // Remove spaces to avoid errors
            Width = 50,
            Height = 50,
            Fill = ColourSelector(_solarsystem.Sun.Colour),
            Margin = new Thickness(1),
            Stroke = Brushes.Black,
            ToolTip = _solarsystem.Sun.Name
        };
        SimCanvas.Children.Add(sun);
        ellipses.Add(sun);
        Canvas.SetLeft(sun,
            Map(_solarsystem.Sun.GetPosition(dag).X, -largestOrbit, largestOrbit, 0, (float)SimCanvas
                .RenderSize
                .Width) - sun.Width / 2);
        Canvas.SetTop(sun,
            Map(_solarsystem.Sun.GetPosition(dag).Y, -largestOrbit, largestOrbit, 0,
                (float)SimCanvas.RenderSize.Height) - sun.Height / 2);


        // Enable adding planets
        AddPlanets.Visibility = Visibility.Visible;
        timer.Start();
    }

    private void AddPlanets_OnClick(object sender, RoutedEventArgs e)
    {
        Console.WriteLine("AddPlanets");

        _solarsystem.Planets.ForEach(planet =>
        {
            Ellipse ellipse = new Ellipse
            {
                Name = planet.Name.Replace(" ", ""), // Remove spaces to avoid errors
                Width = 20,
                Height = 20,
                Fill = ColourSelector(planet.Colour),
                Margin = new Thickness(1),
                Stroke = Brushes.Black,
                ToolTip = planet.Name
            };
            SimCanvas.Children.Add(ellipse);
            ellipses.Add(ellipse);
            Canvas.SetLeft(ellipse,
                Map(planet.GetPosition(dag).X, -largestOrbit, largestOrbit, 0, (float)SimCanvas.RenderSize
                    .Width) - ellipse.Width / 2);
            Canvas.SetTop(ellipse,
                Map(planet.GetPosition(dag).Y, -largestOrbit, largestOrbit, 0,
                    (float)SimCanvas.RenderSize.Height) - ellipse.Height / 2);
        });

        // Enable adding moons
        AddMoons.Visibility = Visibility.Visible;
        // Hide adding planets
        AddPlanets.Visibility = Visibility.Hidden;
    }

    private void AddMoons_OnClick(object sender, RoutedEventArgs e)
    {
        Console.WriteLine("AddMoons");

        _solarsystem.Moons.ForEach(moon =>
        {
            Ellipse ellipse = new Ellipse
            {
                Name = moon.Name.Replace(" ", ""), // Remove spaces to avoid errors
                Width = 10,
                Height = 10,
                Fill = ColourSelector(moon.Colour),
                Margin = new Thickness(1),
                Stroke = Brushes.Black,
                ToolTip = moon.Name
            };
            SimCanvas.Children.Add(ellipse);
            ellipses.Add(ellipse);
            Canvas.SetLeft(ellipse,
                Map(moon.GetPosition(dag).X, -largestOrbit, largestOrbit, 0, (float)SimCanvas.RenderSize
                    .Width) - ellipse.Width / 2);
            Canvas.SetTop(ellipse,
                Map(moon.GetPosition(dag).Y, -largestOrbit, largestOrbit, 0,
                    (float)SimCanvas.RenderSize.Height) - ellipse.Height / 2);
        });


        // Hide add moons
        AddMoons.Visibility = Visibility.Hidden;
    }

    private Brush ColourSelector(String colour)
    {
        return colour switch
        {
            "Yellow" => Brushes.Yellow,
            "Blue" => Brushes.Blue,
            "Red" => Brushes.Red,
            "Green" => Brushes.Green,
            "White" => Brushes.White,
            "Black" => Brushes.Black,
            "Brown" => Brushes.Brown,
            _ => Brushes.Gray
        };
    }

    private static float Map(float value, float fromLow, float fromHigh, float toLow, float toHigh)
    {
        // Map the value from the input range to the output range
        return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
    }
}