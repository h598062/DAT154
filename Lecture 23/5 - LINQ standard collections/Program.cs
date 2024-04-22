using System;
using System.Collections.Generic;
using System.Linq;

// The following 3 classes represent the 3 main items in our
// application: Students, Grades and Courses.
class Student {
    public string StudentName { get; set; }
    public int StudentID { get; set; }
}

class Course {
    public string CourseName { get; set; }
    public string CourseID { get; set; }
}

class Grade {
    public char grade { get; set; }
    public string CourseID { get; set; }
    public int StudentID { get; set; }
}

// Main program. Creates an instance of each list and 
// populates it with data. It then uses both forms of 
// LINQ to query the dataset. Note that both the LINQ 
// queries produce identical results, except that the 
// last one also introduces a where condition to only
// show grades better than a define threshold.
class Program {
    static void Main() {

        List<Student> sl =
        [
            new() { StudentName = "Roger Rabbit", StudentID = 123 },
            new() { StudentName = "Donald Duck", StudentID = 456 },
            new() { StudentName = "Superman", StudentID = 111 }
        ];

        List<Course> cl =
        [
            new() { CourseName = "Programming 101", CourseID = "TOD765" },
            new() { CourseName = "Difficult Math", CourseID = "FOA432" },
            new() { CourseName = "Sleepwalking", CourseID = "TVD879" }
        ];

        List<Grade> gl =
        [
            new() { grade = 'A', CourseID = "TOD765", StudentID = 123 },
            new() { grade = 'B', CourseID = "TOD765", StudentID = 111 },
            new() { grade = 'F', CourseID = "FOA432", StudentID = 123 },
            new() { grade = 'E', CourseID = "FOA432", StudentID = 456 },
            new() { grade = 'C', CourseID = "FOA432", StudentID = 111 },
            new() { grade = 'D', CourseID = "TVD879", StudentID = 123 },
            new() { grade = 'C', CourseID = "TVD879", StudentID = 456 }
        ];

        // Queries the dataset and stores the result in the
        // studcourse variable
        var studcourse = sl
         .Select(stud => new { stud.StudentName, stud.StudentID })
         .Join(gl, stud => stud.StudentID, gr => gr.StudentID, (stud, gr)
                 => new { stud.StudentName, gr.CourseID, gr.grade })
         .Join(cl, gr => gr.CourseID, course => course.CourseID, (gr, course)
                  => new { gr.StudentName, gr.grade, course.CourseName });

        // Iterates through the result set stored in studcourse
        foreach (var s in studcourse) {
            Console.WriteLine("{0} - {1} - {2}", s.StudentName, s.CourseName, s.grade);
        }
        Console.WriteLine();
        Console.ReadKey();

        char gradeLimit = 'B';

        // Queries the dataset and stores the result in the
        // studcoursesql variable
        var studcoursesql = from stud in sl
                            join gr in gl
                            on stud.StudentID equals gr.StudentID
                            join c in cl
                            on gr.CourseID equals c.CourseID
                            where gr.grade <= gradeLimit
                            select new { stud.StudentName, gr.grade, c.CourseName };

        foreach (var s in studcoursesql) {
            Console.WriteLine("{0} - {1} - {2}", s.StudentName, s.CourseName, s.grade);
        }

        Console.ReadKey();

    }
}


