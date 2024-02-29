using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace _4___Simple_WFP_Animation {
    public partial class MainWindow : Window {


        private readonly Ellipse myEllipse;
        private int direction = 1;

        public MainWindow() {
            InitializeComponent();

            StackPanel myStackPanel = new();

            SolidColorBrush mySolidColorBrush = new()
            {
                Color = Color.FromArgb(255, 255, 0, 0)
            };

            myEllipse = new()
            {
                Fill = mySolidColorBrush,
                StrokeThickness = 2,
                Stroke = Brushes.Black,
                Width = 200,
                Height = 100
            };

            myStackPanel.Children.Add(myEllipse);

            this.Content = myStackPanel;

            DispatcherTimer t = new()
            {
                Interval = TimeSpan.FromMilliseconds(30)
            };
            t.Tick += Tick;
            t.Start();

        }

        private void Tick(object sender, EventArgs e) {
            double height = ((StackPanel)this.Content).ActualHeight;
            if ((direction == 1 && myEllipse.Height > height) || (direction == -1 && myEllipse.Height < 25)) {
                direction *= -1;
            } 
            myEllipse.Height += direction;
        }
    }
}
