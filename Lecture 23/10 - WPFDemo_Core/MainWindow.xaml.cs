using Microsoft.EntityFrameworkCore;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Input;
using WPFDemo.Models;

namespace WPFDemo {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        private readonly Dat154Context dx = new();

        private readonly ObservableCollection<Student> Students;

        public MainWindow() {
            InitializeComponent();

            Students = dx.Students.Local.ToObservableCollection();

            dx.Students.Load();

            studentList.DataContext = Students.OrderBy(s => s.Studentname);

            studentList.MouseDoubleClick += StudentList_MouseDoubleClick;

            dx.Students.Local.CollectionChanged += Local_CollectionChanged;

            searchField.TextChanged += SearchField_TextChanged;

        }

        private void SearchField_TextChanged(object sender, System.Windows.Controls.TextChangedEventArgs e) {
            DoSearch_Click(DoSearch, new RoutedEventArgs());
        }

        private void Local_CollectionChanged(object? sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e) {
            DoSearch_Click(DoSearch, new RoutedEventArgs());
        }

        private void StudentList_MouseDoubleClick(object sender, MouseButtonEventArgs e) {

            Student? s = studentList.SelectedItem as Student;

            if (s != null) {

                Editor ed = new(s)
                {
                    dx = dx
                };

                ed.Show();
            }
        
        }

        private void DoSearch_Click(object sender, RoutedEventArgs e) {
            //dx.Students.Where(s => s.Studentname.Contains(searchField.Text)).Load();
            studentList.DataContext = Students
                .Where(s => s.Studentname.Contains(searchField.Text,StringComparison.CurrentCultureIgnoreCase))
                .OrderBy(s => s.Studentname);
        }

        private void DoEdit_Click(object sender, RoutedEventArgs e) {

            Editor ed = new()
            {
                dx = dx
            };

            ed.Show();



        }
    }
}