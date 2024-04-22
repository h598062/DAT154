using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace _8___WPF_Demo {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        private dat154Entities dx = new dat154Entities();

        private DbSet<course> course;
        private DbSet<student> student;
        private DbSet<grade> grade;

        public MainWindow() {
            InitializeComponent();

            course = dx.Set<course>();
            student = dx.student;
            grade = dx.grade;


            student.Load();



            studentList.DataContext = student.Local;


        }

        private void SearchButton_Click(object sender, RoutedEventArgs e) {
            studentList.DataContext = student.Local.Where(stud => stud.studentname.Contains(SearchField.Text));
        }

        private void AddButton_Click(object sender, RoutedEventArgs e) {
            new Editor(dx).ShowDialog();
        }


        private void StudentList_OnMouseDoubleClick(object sender, MouseButtonEventArgs e) {
            student s = (student) studentList.SelectedItem;
            new Editor(dx, s).ShowDialog();
        }
    }
}
