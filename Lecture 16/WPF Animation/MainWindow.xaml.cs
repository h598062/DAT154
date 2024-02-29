using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace _5___WPF_Animation {

    public partial class MainWindow : Window {
        private readonly DispatcherTimer t;
        private readonly Planet p;
        private readonly Planet p2;
        int time = 0;
        public event Action<int> MoveIt;

        public MainWindow() {
            InitializeComponent();

            t = new() 
            {
                Interval = new TimeSpan(200000)
            };
            t.Tick += Tick;
            t.Start();

            p = new()
            {
                Shape = planet
            };
            MoveIt += p.CalcPos;

            p2 = new()
            {
                Shape = planet2,
                OrbitalRadius = 100,
                OrbitalSpeed = 2
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

        public int OrbitalRadius { get; set; } = 200;
        public int OrbitalSpeed { get; set; } = 1;

        public Ellipse Shape { get; set; }

        public void CalcPos(int time) {
            Canvas c = (Canvas)Shape.Parent;

            Xpos = (int)(c.RenderSize.Width / 2 - Shape.Width / 2 +
                (Math.Cos(time * OrbitalSpeed * 3.1416 / 180) * OrbitalRadius));
            Ypos = (int)(c.RenderSize.Height / 2 - Shape.Height / 2 +
                (Math.Sin(time * OrbitalSpeed * 3.1416 / 180) * OrbitalRadius));

            Canvas.SetLeft(Shape, Xpos);
            Canvas.SetTop(Shape, Ypos);

        }
    }


}
