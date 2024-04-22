using System;
using System.Collections.Generic;
using System.Linq;

namespace LINQDemo {

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

    class Grades {
        public char Grade { get; set; }
        public string CourseID { get; set; }
        public int StudentID { get; set; }
    }

    // Main program. Creates an instance of each list and // populates it with data. It then uses both forms of // LINQ to query the dataset. Note that both the LINQ // queries produce identical results, except that the // last one also introduces a where condition to only
    // show grades better than a define threshold.class Program {
    class Program {
        static void Main() {

            List<Student> sl = [];
            List<Course> cl = [];
            List<Grades> gl = [];


            sl.Add(new Student() { StudentName = "Roger Rabbit", StudentID = 123 });
            sl.Add(new Student() { StudentName = "Donald Duck", StudentID = 456 });
            sl.Add(new Student() { StudentName = "Superman", StudentID = 111 });

            cl.Add(new Course() { CourseName = "Programming 101", CourseID = "TOD765" });
            cl.Add(new Course() { CourseName = "Difficult Math", CourseID = "FOA432" });
            cl.Add(new Course() { CourseName = "Sleepwalking", CourseID = "TVD879" });

            gl.Add(new Grades() { Grade = 'A', CourseID = "TOD765", StudentID = 123 });
            gl.Add(new Grades() { Grade = 'B', CourseID = "TOD765", StudentID = 111 });
            gl.Add(new Grades() { Grade = 'F', CourseID = "FOA432", StudentID = 123 });
            gl.Add(new Grades() { Grade = 'E', CourseID = "FOA432", StudentID = 456 });
            gl.Add(new Grades() { Grade = 'C', CourseID = "FOA432", StudentID = 111 });
            gl.Add(new Grades() { Grade = 'D', CourseID = "TVD879", StudentID = 123 });
            gl.Add(new Grades() { Grade = 'C', CourseID = "TVD879", StudentID = 456 });

            // Queries the dataset and stores the result in the
            // studcourse variable
            var studcourse = sl
             .Select(stud => new { stud.StudentName, stud.StudentID })
             .Join(gl, stud => stud.StudentID, gr => gr.StudentID, (stud, gr)
                     => new { stud.StudentName, gr.CourseID, gr.Grade })
             .Join(cl, gr => gr.CourseID, course => course.CourseID, (gr, course)
                      => new { gr.StudentName, gr.Grade, course.CourseName });

            // Iterates through the result set stored in studcourse
            foreach (var s in studcourse) {
                Console.WriteLine($"{s.StudentName} - {s.CourseName} - {s.Grade}");
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
                                where gr.Grade <= gradeLimit
                                select new { stud.StudentName, gr.Grade, c.CourseName };

            foreach (var s in studcoursesql) {
                Console.WriteLine($"{s.StudentName} - {s.CourseName} - {s.Grade}");
            }

            Console.ReadKey();

        }
    }
}


