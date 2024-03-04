using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Mouse_Event
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
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


            // The Grid in XAML needs to have the control name set to myGrid    
            myGrid.Children.Add(b);
        }

        private void B_MouseMove(object sender, MouseEventArgs e)
        {
            Random r = new Random();
            ((Button)sender).Margin = new Thickness(r.Next(0, 400), r.Next(0, 300), 0, 0);
        }

    }
}
