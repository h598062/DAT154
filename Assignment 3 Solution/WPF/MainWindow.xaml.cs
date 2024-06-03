using System.Windows;
using System.Linq;
using System.Data.Entity;
using System.Windows.Controls;
using System.Windows.Data;
using System.Collections.ObjectModel;

// This solution uses .NET framework and Entity Framework
// For a solution using .NET and Entity Framework Core, see
// the other project

// Note that this solution shows a very basic way of handling
// LINQ queries from graphical elements to Entity Framework
// There is nothing wrong with this simple approach, but note
// that far more elgant ways also exist, but they are slighly
// less transparent for beginner, so I keep this solution simple.

// The data model and all entity classes are found under 
// "StudentModel.edmx"


namespace WPF {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        private readonly dat154Entities dx = new dat154Entities();
        private readonly ObservableCollection<student> students;
        private readonly ObservableCollection<course> courses;
        private readonly ObservableCollection<grade> grades;

        public MainWindow() {
            InitializeComponent();

            // These variables just makes the queries cleaner and more readble
            // Not technically needed, could write it out each time
            students = dx.student.Local;
            courses = dx.course.Local; 
            grades = dx.grade.Local;

            // WPF needs the data in memory to bind it to a GUI control
            // Loading all the data like this works for a small database
            // but for a larger DB we should of course use other solutions
            // like populating a list with only the requested data and show
            // that.
            // EntityFramework itself supports lazy loading (only loding what
            // is needed) but for the gui to do operations on it, it need to
            // have all the data it is supposed to be working on available
            dx.student.Load();
            dx.course.Load();
            dx.grade.Load();

            // Task 1 - Search for students by name
            // Here we just set the datacontext of the display grid to a LINQ query
            A1Students.DataContext = students.Where(x => x.studentname.ToLower().Contains(A1Search.Text.ToLower()));


            // Task 2 - List Students in course
            // First, make a list of courses that is bound to a listbox
            A2Courses.DataContext = courses;
            A2Courses.SelectedIndex = 0;
            // Then we build the list of students based on the selection
            // in the listbox
            A2Students.DataContext = grades
                                        .Where(g => g.coursecode == ((course)A2Courses.SelectedItem).coursecode)
                                        .Join(students, g => g.studentid, s => s.id, (g, s) => new { g.grade1, s.studentname });


            // Task 3 - List students by grade
            // Build the list of students based on the selected grade
            // This example uses "SQL-like" syntax for of LINQ
            A3Students.DataContext = from st in students
                                     join gr in grades on st.id equals gr.studentid
                                     join co in courses on gr.coursecode equals co.coursecode
                                     where gr.grade1[0] <= ((A3Grades.SelectedValue as ComboBoxItem).Content as string)[0]
                                     orderby co.coursename, gr.grade1, st.studentname
                                     select new { st.studentname, gr.grade1, co.coursename };


            // Task 4 - Failed Students
            // Here we take advantage of the fact that Entity Framework is
            // an Object Oriented model of the database. Why do all those explicit
            // joins when we can deal with this in an object-oriented fashion.
            // Both student and course are properties on the grade object, and can be
            // accessed through those (see the XAML) instead of messing with
            // join and select. Much cleaner to deal with.
            A4Students.DataContext = grades.Where(g => g.grade1 == "F");


            // Task 5 - Assign students to courses
            // This screen contains three lists
            // Left list is a list of courses
            // Middle list is a list of students in the current course. To remove a student
            // from a course, select it here and click the remove button
            // Right list is a list of students NOT in this course. Select one, pick a grade
            // and hit add to add them to the course
            A5Courses.DataContext = courses;
            A5Courses.SelectedIndex = 0;
            // This list and query is a clone of the one from task 2, so I take the opportunity
            // to rewrite it showing the object-orientet approach instead
            A5Students.DataContext = grades
                            .Where(g => g.coursecode == ((course)A5Courses.SelectedItem).coursecode);

            // This query might be a bit tricky to understand
            // Basically, I am selecting all the students, except those
            // that has the currently selected course in their list of courses
            // Again, note the object-oriented approach here. I compare course
            // objects directly, no need to extract properties and compare those
            A5StudentsAdd.DataContext = students
                        .Where(s => !s.grade.Any(x => x.course == ((course)A5Courses.SelectedItem)))
                        .OrderBy(s => s.studentname);
        }

        private void A1Search_TextChanged(object sender, TextChangedEventArgs e) {
            // Refreshing the data in the grid
            CollectionViewSource.GetDefaultView(A1Students.ItemsSource).Refresh();

            // This also works fine
            // A1Students.DataContext = students.Where(x => x.studentname.Contains(A1Search.Text));
        }

        private void A2Courses_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            // Refreshing the data in the grid
            // Notice the null check here. This is required because this event
            // gets triggered in the constructor when we set the selection
            // But if we don't set it there, we have troubles populating
            // the student list because no course is selected
            // There are plenty of other ways to handle this of course, best option
            // would probably be to NOT set everything up in the constructor, but
            // it works, and a simple null check here isn't a problem
            CollectionViewSource.GetDefaultView(A2Students.ItemsSource)?.Refresh();
        }

        private void A3Grades_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            CollectionViewSource.GetDefaultView(A3Students?.ItemsSource)?.Refresh();
        }

        private void RefreshA5Lists() {
            CollectionViewSource.GetDefaultView(A5Students?.ItemsSource)?.Refresh();
            CollectionViewSource.GetDefaultView(A5StudentsAdd?.ItemsSource)?.Refresh();
        }

        private void A5Courses_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            RefreshA5Lists();
        }

        private void RemoveButton_Click(object sender, RoutedEventArgs e) {

            // Did someone click the button without selecting anything?
            if (A5Students.SelectedItem as grade == null) return;

            // Removes the selected grade from the list
            // (Remember, a "grade" is what connects a student to a course in this schema)
            grades.Remove(A5Students.SelectedItem as grade);

            // Commits changes to database
            dx.SaveChanges();

            // Update the view
            RefreshA5Lists();
        }

        private void AddButton_Click(object sender, RoutedEventArgs e) {

            // Did they click the button without selecting a student?
            if (A5StudentsAdd.SelectedItem as student == null) return;

            // Construct a new grade object
            grade g = new grade { course = (course)A5Courses.SelectedItem, 
                                  grade1 = (A5Grades.SelectedValue as ComboBoxItem).Content as string,
                                  student = (student)A5StudentsAdd.SelectedItem
                                 };

            // add it to the list
            dx.grade.Add(g);
            
            // Commit to database
            dx.SaveChanges();



            RefreshA5Lists();

        }



    }
}
