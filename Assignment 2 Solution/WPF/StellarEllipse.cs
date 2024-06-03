using SpaceSim.SpaceLib;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace SpaceSim.WPF {
    // This composite class holds a reference to both a
    // drawing ellipse and space object.
    // If my library should only support WPF apps,
    // I might have changed the Star class in the library
    // instead, but since I am writing 4 solutions here,
    // I leave the library in peace and make this instead
    class StellarEllipse
    {
        public Ellipse Ellipse { get; set; }
        public Star Space { get; set; }
        public Ellipse Orbit { get; set; }
        public Label Name { get; set; }

        public StellarEllipse(Star so, Ellipse el) {
            Space = so;
            Ellipse = el;

            Orbit = new Ellipse()
            {
                Fill = Brushes.Transparent,
                Stroke = Brushes.White,
                StrokeThickness = 2,
                Visibility = Visibility.Hidden
            };
            Name = new Label()
            {
                Content = so.Name,
                Visibility = Visibility.Hidden,
                Foreground = Brushes.WhiteSmoke
            };
            

        }

    }
}
