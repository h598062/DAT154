using SpaceLib.SolarSystem;
using SpaceSim.SpaceLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace SpaceSim.WPF {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 


    // This WFP solution is based on manually handling
    // the animation. It does not use functionality
    // like storyboards or the like. It is also a very
    // straight-forward solutions, no Command or
    // MVVC patterns.
    public partial class SimWindow : Window {

        private Point center = new();
        private readonly SolarSystem sim = new();
        private readonly Coordinator coordinator = new();
        private double scale = 1;
        private Star centralObject;
        private Shape centralShape = new Ellipse();
        private readonly List<StellarEllipse> shapes = [];

        public SimWindow() {
            InitializeComponent();

            // Makes sense to set the initial central object as the sun
            // This is the object that will be shown in the middle of the window
            centralObject = sim.Sun;

            // We need to recalculate scale when the window size changes,
            // so we subscribe to the Resize event
            this.SizeChanged += ModelViewChanged;

            // We use the arrow keys to control the sim, so we
            // subscribe to the keydown event
            this.KeyDown += SimWindow_KeyDown;
            showOrbits.PreviewKeyDown += SimWindow_KeyDown;
            showNames.PreviewKeyDown += SimWindow_KeyDown;
            selectCentral.PreviewKeyDown += SimWindow_KeyDown;

            // Each object should recalculate it's own positionon each tick
            // (This was part of the assignment spesification)
            // This subscribes each object to the relevant event
            // Note that we assume a standard solar system here, with two
            // layers, planets orbits the sun, moons orbits planets.
            // Because the list we inherit in the space object is a list of planets
            // I still use the Planet class for the moons here, but 
            // polymorphism handles that neatly for us.
            // (The moons simply inherits the CalculatePos from Planet anyway)
            foreach (Planet p in sim.Sun.Children) {
                coordinator.DoTick += p.CalculatePos;
                foreach (Planet m in p.Children) {
                    coordinator.DoTick += m.CalculatePos;
                }
            }

            // Filling the selection dropdown
            selectCentral.Items.Add(sim.Sun);
            foreach (Planet p in sim.Sun.Children) {
                selectCentral.Items.Add(p);
            }
            selectCentral.SelectedIndex= 0;
            selectCentral.SelectionChanged += SelectCentral_SelectionChanged;


            // Subscribes to the tick event to start the animation
            coordinator.DoTick += UpdateDrawing;


        }

        // This method is called whenever the select an item in the dropdown
        // It changes the central object reference to the new object
        // then call the ModelViewChanged() method which will ensure
        // scale is recalculated and the canvas is populated
        // with the objects for our new view.
        private void SelectCentral_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            centralObject = (Star)((ComboBox)sender).SelectedItem;
            ModelViewChanged(this, null);
        }

        private void PopulateCanvas(Star central) {
            Canvas.Children.Clear();

            foreach (Planet p in central.Children) {

                Ellipse e = new()
                {
                    Fill = new SolidColorBrush(ColorFromRGB(p.Color)),
                    Width = p.SizeClass * 10,
                    Height = p.SizeClass * 10
                };
                StellarEllipse se = new(p, e);
                shapes.Add(se);
                Canvas.Children.Add(se.Orbit);
                Canvas.Children.Add(e);
                Canvas.Children.Add(se.Name);
                p.CalculatePos(coordinator.Time);

                int x = (int)(center.X + p.PositionRelative.X * scale);
                int y = (int)(center.Y + p.PositionRelative.Y * scale);

                Canvas.SetLeft(e, x - e.Width / 2);
                Canvas.SetTop(e, y - e.Height / 2);

                se.Orbit.Visibility = showOrbits.IsChecked == true ? Visibility.Visible : Visibility.Hidden;
                se.Name.Visibility = showNames.IsChecked == true ? Visibility.Visible : Visibility.Hidden;




            }


            centralShape = new Ellipse()
            {
                Fill = new SolidColorBrush(ColorFromRGB(central.Color)),
                Width = central.SizeClass * 10,
                Height = central.SizeClass * 10
            };
            Canvas.Children.Add(centralShape);
            Canvas.SetLeft(centralShape, center.X - centralShape.Width / 2);
            Canvas.SetTop(centralShape, center.Y - centralShape.Height / 2);




        }

        // Helper function to convert the color codes
        // we have stored in our space objects to the
        // triplet format the WPF Color class wants
        private static Color ColorFromRGB(int color) {
            byte r = (byte)((color & 0xFF0000) >> 16);
            byte g = (byte)((color & 0xFF00) >> 8);
            byte b = (byte)(color & 0xFF);

            return Color.FromArgb(255, r, g, b);
        }

        // This is where the animation happens. This method is called on every timer tick
        // and moves the elipses on screen in accordance with the recalculated coordinates
        // of the backing objects.
        private void UpdateDrawing(double time) {

            foreach (StellarEllipse e in shapes) {

                // Calculate the rate our simulation is running and display it in a label
                // on our form
                double simspeed = 1000 / coordinator.Interval.Milliseconds * coordinator.Rate;
                SimSpeedInfo.Content = $"Sim Speed {simspeed:N5} days/second. Left/Right arrows to change";


                // Calculating the position on screen for the current body.
                int x = (int)(center.X + e.Space.PositionRelative.X * scale);
                int y = (int)(center.Y + e.Space.PositionRelative.Y * scale);

                // When you are zoomed out, some objects appear to orbit inside
                // the central star/planet. This is a consequence of using
                // fixed scaling for the objects and only scale the distances
                // but this is required as distances in space are vast and
                // planets are tiny in comparison
                // What we do here is to hide any object that isn't outside
                // the body it orbits.
                // Note that this causes them to simply "pop" into view when we zoom
                // close enough. This could be much prettier (see the WindowsForms solution
                // for another way of doing it, where I fade them in out), but it gets the job
                // done.
                if(Math.Abs(center.X - x) < centralObject.SizeClass * 8 && Math.Abs(center.Y - y) < centralObject.SizeClass * 8) {
                    e.Ellipse.Visibility = Visibility.Hidden;
                    e.Name.Visibility = Visibility.Hidden;
                    e.Orbit.Visibility = Visibility.Hidden;
                } else {
                    e.Ellipse.Visibility = Visibility.Visible;
                    e.Orbit.Visibility = showOrbits.IsChecked == true ? Visibility.Visible : Visibility.Hidden;
                    e.Name.Visibility = showNames.IsChecked == true ? Visibility.Visible : Visibility.Hidden;
                }

                // Updates the drawing canvas with the new positions of the shapes
                Canvas.SetLeft(e.Ellipse, x - e.Ellipse.Width / 2);
                Canvas.SetTop(e.Ellipse, y - e.Ellipse.Height / 2);
                Canvas.SetLeft(e.Name, x + e.Ellipse.Width / 4);
                Canvas.SetTop(e.Name, y + e.Ellipse.Height / 4);

                e.Orbit.Width = e.Orbit.Height = (e.Space as Planet)?.OrbitalRadius * scale * 2 ?? 0;
                Canvas.SetLeft(e.Orbit, center.X - e.Orbit.Width / 2);
                Canvas.SetTop(e.Orbit, center.Y - e.Orbit.Height / 2);

            }

        }

        // Event handler that handles our keyboard input to change scale/speed
        private void SimWindow_KeyDown(object sender, KeyEventArgs e) {
            e.Handled = true;
            switch (e.Key) {
                case Key.Up:
                    scale *= 1.1;
                    break;
                case Key.Down:
                    scale /= 1.1;
                    break;
                case Key.Left:
                    coordinator.Rate /= 1.2;
                    break;
                case Key.Right:
                    coordinator.Rate *= 1.2;
                    break;
                default:
                    e.Handled = false;
                    break;
            }
        }

        // This is called whenever the view of the model changes. This happens
        // when the window changes size (because we need to recalculate scale)
        // as well as when we change the central object (again, because we need
        // to recalculate scale to fit the new view)

        private void ModelViewChanged(object sender, SizeChangedEventArgs? e) {
            center.X = Canvas.RenderSize.Width / 2;
            center.Y = Canvas.RenderSize.Height / 2;

            try {
                scale = Canvas.RenderSize.Height / (2 * centralObject.Children.Last().OrbitalRadius);
            } catch {
                scale = 1;
            }

            PopulateCanvas(centralObject);
            PlanetInfo.Content = centralObject.InfoText();

        }
    }
}
