using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Multiple_Subscribers
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            Button b = new Button
            {
                Content = "Click Me!",
                Width = 100,
                Height = 25,
                VerticalAlignment = VerticalAlignment.Top,
                HorizontalAlignment = HorizontalAlignment.Left,
                Margin = new Thickness(100, 100, 0, 0)
            };

            b.MouseMove += B_MouseMove;
            b.MouseMove += B_MouseMove2;

            myGrid.Children.Add(b);
        }

        void B_MouseMove(object sender, MouseEventArgs e)
        {
            Random r = new Random();
            ((Button)sender).Margin = new Thickness(r.Next(0, 400), r.Next(0, 300), 0, 0);
        }

        void B_MouseMove2(object sender, MouseEventArgs e)
        {
            Random r = new Random();
            ((Button)sender).Background = new
                      SolidColorBrush(Color.FromRgb((Byte)r.Next(0, 255),
                      (Byte)r.Next(0, 255), (Byte)r.Next(0, 255)));
        }


    }
}
