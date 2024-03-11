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
    private OrbitSystem mainOrbitSystem;
    private OrbitSystem planetOrbitSystem;
    private readonly System.Windows.Threading.DispatcherTimer timerFullView;
    public event Action<int> UpdatePositionsFullView;
    private int dagerFullView = 0;
    
    public MainWindow()
    {
        InitializeComponent();

        _solarsystem = new Solarsystem();


        timerFullView = new System.Windows.Threading.DispatcherTimer
        {
            Interval = TimeSpan.FromTicks(10000)
        };
        timerFullView.Tick += Tickv2;
        this.KeyDown += InputHandler;
    }

    private void InputHandler(object sender, KeyEventArgs e)
    {
        Console.WriteLine(e.Key);

        switch (e.Key)
        {
            case Key.Up:
            {
                timerFullView.Stop();
                timerFullView.Interval = timerFullView.Interval.Add(TimeSpan.FromTicks(10));
                timerFullView.Start();
                break;
            }
            case Key.Down:
            {
                timerFullView.Stop();
                timerFullView.Interval = timerFullView.Interval.Subtract(TimeSpan.FromTicks(10));
                timerFullView.Start();
                break;
            }
            case Key.Right:
            {
                timerFullView.Stop();
                timerFullView.Interval = timerFullView.Interval.Add(TimeSpan.FromTicks(1000));
                timerFullView.Start();
                break;
            }
            case Key.Left:
            {
                timerFullView.Stop();
                timerFullView.Interval = timerFullView.Interval.Subtract(TimeSpan.FromTicks(1000));
                timerFullView.Start();
                break;
            }
            case Key.Space:
            {
                timerFullView.IsEnabled = !timerFullView.IsEnabled;
                break;
            }
            case Key.Enter:
            {
                mainOrbitSystem.ToggleOrbit();
                planetOrbitSystem?.ToggleOrbit();
                break;
            }
            default:
                break;
        }


    }

    private void Tick(object sender, EventArgs e)
    {
        mainOrbitSystem.Update();
    }
    
    private void Tickv2(object sender, EventArgs e)
    {
        UpdatePositionsFullView(dagerFullView++);
    }

    private void StartKnapp_OnClick(object sender, RoutedEventArgs e)
    {
        StartKnapp.Visibility = Visibility.Hidden;
        Console.WriteLine("StartKnapp");

        mainOrbitSystem = new OrbitSystem(_solarsystem.Sun, MainCanvas);
        foreach (var obj in mainOrbitSystem.Orbiters)
        {
            obj.OrbiterClicked += HandleOrbiterClicked;
            UpdatePositionsFullView += obj.UpdatePositionFullView;
        }
        timerFullView.Start();
    }
    
    private void HandleOrbiterClicked(OrbitalBody parent)
    {
        if (MainCanvas.Visibility == Visibility.Hidden)
        {
            return;
        }
        MainCanvas.Visibility = Visibility.Hidden;
        PlanetCanvas.Visibility = Visibility.Visible;
        planetOrbitSystem = new OrbitSystem(parent, PlanetCanvas);
        planetOrbitSystem.CenterObjectClicked += HandleCenterObjectClicked;
        foreach (var obj in planetOrbitSystem.Orbiters)
        {
            UpdatePositionsFullView += obj.UpdatePositionFullView;
        }
    }
    
    private void HandleCenterObjectClicked(SpaceObject parent)
    {
        if (MainCanvas.Visibility == Visibility.Visible)
        {
            return;
        }
        MainCanvas.Visibility = Visibility.Visible;
        PlanetCanvas.Visibility = Visibility.Hidden;
        foreach (var obj in planetOrbitSystem.Orbiters)
        {
            UpdatePositionsFullView -= obj.UpdatePositionFullView;
        }
        planetOrbitSystem.Destroy(PlanetCanvas);
    }
}

public class OrbitSystem
{
    public SpaceObject CenterObject { get; set; }
    public Ellipse CenterEllipse { get; set; }
    public List<CompositeOrbiter> Orbiters { get; set; }
    public float maxOrbit { get; set; }
    public float maxDiameter { get; set; }
    public int days = 0;
    private bool _showOrbit = true;
    
    public delegate void CenterObjectClickedHandler(SpaceObject parent);
    public event CenterObjectClickedHandler CenterObjectClicked;

    public OrbitSystem(SpaceObject centerObject, Canvas canvas)
    {
        maxDiameter = Helpers.MaxDiameter(centerObject);
        maxOrbit = Helpers.MaxOrbit(centerObject);
        Orbiters = new List<CompositeOrbiter>();
        CenterObject = centerObject;
        CenterEllipse = new Ellipse
        {
            Width = 100,
            Height = 100,
            Fill = Helpers.ColourSelector(CenterObject.Colour),
            Margin = new Thickness(1),
            Stroke = Brushes.Black,
            Name = CenterObject.Name.Replace(" ", ""),
            ToolTip = CenterObject.Name,
            Cursor = Cursors.Hand
        };
        canvas.Children.Add(CenterEllipse);
        Canvas.SetZIndex(CenterEllipse, 1);
        Canvas.SetLeft(CenterEllipse, (float)canvas.RenderSize.Width / 2 - CenterEllipse.Width / 2);
        Canvas.SetTop(CenterEllipse, (float)canvas.RenderSize.Height / 2 - CenterEllipse.Height / 2);
        CenterEllipse.MouseLeftButtonDown += OnClick;
        
        foreach (var obj in CenterObject.Orbiters)
        {
            float diameter = Helpers.Map(obj.DiameterKm, 0, maxDiameter, 5, 25);
            float orbit = Helpers.Map(obj.OrbitalRadiuskKm, 0, maxOrbit * 1.04f, 0,
                (float)canvas
                    .RenderSize
                    .Width / 2);

            Orbiters.Add(new CompositeOrbiter(obj, orbit, diameter, canvas));
        }
    }

    public void Update()
    {
        days++;
        foreach (var orbiter in Orbiters)
        {
            orbiter.UpdatePositionFullView(days);
        }
    }
    
    public void ToggleOrbit()
    {
        _showOrbit = !_showOrbit;
        foreach (var orbiter in Orbiters)
        {
            orbiter.ShowOrbit(_showOrbit);
        }
    }
    
    public void OnClick(object sender, RoutedEventArgs e)
    {
        Console.WriteLine(CenterObject.Name);
        CenterObjectClicked?.Invoke(CenterObject);
    }

    public void Destroy(Canvas canvas)
    {
        foreach (var orbiter in Orbiters)
        {
            orbiter.Destroy(canvas);
        }
        CenterEllipse.MouseLeftButtonDown -= OnClick;
        canvas.Children.Remove(CenterEllipse);
    }
}

public class CompositeOrbiter
    {
        private Ellipse _ellipse;
        private Ellipse _orbitEllipse;
        private OrbitalBody _ob;

        private double _orbitRadius;
        private double _centerX;
        private double _centerY;
        private double _diameter;
        
        public delegate void OrbiterClickedHandler(OrbitalBody parent);
        public event OrbiterClickedHandler OrbiterClicked;

        public CompositeOrbiter(OrbitalBody ob, double orbitRadius, double diameter, Canvas canvas)
        {
            _centerX = canvas.RenderSize.Width / 2;
            _centerY = canvas.RenderSize.Height / 2;
            _orbitRadius = orbitRadius;
            _diameter = diameter;
            _ob = ob;
            
            _orbitEllipse = new Ellipse
            {
                Width = orbitRadius * 2,
                Height = orbitRadius * 2,
                Fill = Brushes.Transparent,
                Stroke = Brushes.Black,
                StrokeThickness = 1,
                Margin = new Thickness(1),
                Opacity = 0.5,
                StrokeDashArray = [2]
            };
            canvas.Children.Add(_orbitEllipse);
            Canvas.SetZIndex(_orbitEllipse, 0);
            Canvas.SetLeft(_orbitEllipse, _centerX - orbitRadius);
            Canvas.SetTop(_orbitEllipse, _centerY - orbitRadius);
            
            _ellipse = new Ellipse
            {
                Width = diameter,
                Height = diameter,
                Fill = Helpers.ColourSelector(ob.Colour),
                Margin = new Thickness(1),
                Stroke = Brushes.Black,
                Name = ob.Name.Replace(" ", ""),
                ToolTip = ob.Name,
                Cursor = Cursors.Hand
            };
            canvas.Children.Add(_ellipse);
            Canvas.SetLeft(_ellipse, _centerX + orbitRadius - diameter / 2);
            Canvas.SetTop(_ellipse, _centerY - diameter / 2);
            Canvas.SetZIndex(_ellipse, 1);
            _ellipse.MouseLeftButtonDown += OnClick;
        }

        public void UpdatePositionFullView(int days)
        {
            double angle = days / _ob.OrbitalPeriodDays * 2 * Math.PI;
            double x = Math.Cos(angle) * _orbitRadius;
            double y = Math.Sin(angle) * _orbitRadius;
            Canvas.SetLeft(_ellipse, _centerX + x - _diameter / 2);
            Canvas.SetTop(_ellipse, _centerY + y - _diameter / 2);
        }
        
        public void ShowOrbit(bool show)
        {
            _orbitEllipse.Visibility = show ? Visibility.Visible : Visibility.Hidden;
        }

        public void OnClick(object sender, RoutedEventArgs e)
        {
            Console.WriteLine(_ob.Name);
            OrbiterClicked?.Invoke(_ob);
        }
        
        public void Destroy(Canvas canvas)
        {
            _ellipse.MouseLeftButtonDown -= OnClick;
            canvas.Children.Remove(_ellipse);
            canvas.Children.Remove(_orbitEllipse);
        }
    }