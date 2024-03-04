using System.Windows;
using System.Windows.Controls;

namespace Anonymous_Methods___Lambda {

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

            b.Click += (o, e) => MessageBox.Show("Hello");
            b.MouseRightButtonUp += (o, e) => b.Content = e.GetPosition(b).ToString();

            // The Grid in XAML needs to have the control name set to myGrid    
            myGrid.Children.Add(b);
        }
    }
}
