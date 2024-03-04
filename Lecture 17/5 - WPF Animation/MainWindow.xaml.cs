using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Shapes;

namespace _5___WPF_Animation {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {
        private readonly System.Windows.Threading.DispatcherTimer t;
        private readonly Planet p;
        private readonly Planet p2;
        int time = 0;
        public event Action<int> MoveIt;

        public MainWindow() {
            InitializeComponent();

            t = new System.Windows.Threading.DispatcherTimer
            {
                Interval = new TimeSpan(200000)
            };
            t.Tick += Tick;
            t.Start();

            p = new Planet
            {
                Shape = planet
            };
            MoveIt += p.CalcPos;

            p2 = new Planet
            {
                Shape = planet2,
                Orbital_radius = 100,
                Orbital_speed = 2
            };
            MoveIt += p2.CalcPos;

        }

        private void Tick(object sender, EventArgs e) {
            MoveIt(time++);
        }
    }


    class Planet {

        public int Xpos { get; set; }
        public int Ypos { get; set; }

        public int Orbital_radius { get; set; } = 200;
        public int Orbital_speed { get; set; } = 1;

        public Ellipse Shape { get; set; }

        public void CalcPos(int time) {
            Canvas c = (Canvas)Shape.Parent;



            Xpos = (int)(c.RenderSize.Width / 2 - Shape.Width / 2 +
                (Math.Cos(time * Orbital_speed * 3.1416 / 180) * Orbital_radius));
            Ypos = (int)(c.RenderSize.Height / 2 - Shape.Height / 2 +
                (Math.Sin(time * Orbital_speed * 3.1416 / 180) * Orbital_radius));


            Canvas.SetLeft(Shape, Xpos);
            Canvas.SetTop(Shape, Ypos);

        }
    }


}
