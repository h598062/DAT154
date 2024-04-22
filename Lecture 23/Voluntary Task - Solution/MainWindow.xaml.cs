using Microsoft.EntityFrameworkCore;
using System.Windows;
using Voluntary_Task___Solution.Models;

namespace Voluntary_Task___Solution {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        private readonly Dat154Context dx = new();


        public MainWindow() {
            InitializeComponent();

            // I start by piming the cache since a GUI element can only be bound
            // to local data. These two queries loads all the grades and
            // all the students that have a grade
            // There are other ways to handle this, like calling ToList on the query
            // assigned to the GUI control, but that still causes the data to be
            // loaded locally and have the additional issue of disconnecting the 
            // list from the actual database data.
            dx.Students.Where(s => s.Grades.Any()).Load();
            dx.Grades.Load();



            // We query the local cache and bind the query
            // to the graphical list. 

            // Easy version - Count of courses only
            // It may be tempting to use a Join instead of a Select here, and
            // while it generates the same result, it isn't necessary,
            // because LINQ lets us work with data in an object-oriented way
            //
            // The query below is pretty simple, and does the following
            // - Binds to the DataContext of the GUI component the following query:
            //      - Starts with the table of students
            //      - Filters on those students that are connected to at least one course
            //      - Creates anonymous object that contains studen id, name and the count
            //          of the elements in the Grades list for each student
            studentList.DataContext =
                dx.Students.Local
                .Where(s => s.Grades.Any())
                .Select(s => new { s.Studentname, s.Id, CourseCount = s.Grades.Count });


            // Full version - With average grades.
            //
            // The query below is the same as the one explained above, with the
            // exception that this also calculates the average grade by
            // using the aggreate Average function in LINQ.
            // Average really only works on numbers, but it let us specify
            // a conversion function using a lambda-expression, so we simply
            // convert the grade to the equivalent ASCII number by
            // casting it to an int. Since this can result in a decimal number
            // we round it up (remember, even if C is a lower grade than B, it is
            // still higher as far as the alphabet goes) to an integer that we
            // then cast back into char.
        
            studentList.DataContext =
                dx.Students.Local
                .Where(s => s.Grades.Any())
                .Select(s => new { s.Studentname, s.Id, CourseCount = s.Grades.Count,
                    AverageGrade = (char)Math.Ceiling(s.Grades.Average(a => (int)a.Grade1[0]))});





        }
    }
}