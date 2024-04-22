using StudentWeb.Models;
using System.Collections.Generic;

namespace StudentWeb.DAL
{
    public class SchoolInitializer : System.Data.Entity.DropCreateDatabaseAlways<SchoolContext> {


        protected override void Seed(SchoolContext context) {

            var students = new List<Student>
            {
            new Student{Name="Hans",Address="Hjemme"},
            new Student{Name="Bjarne",Address="Bergen Kretsfengsel"},
            new Student{Name="Kalle",Address="Nav"},
            new Student{Name="Ole",Address="Borte Bra"},
            new Student{Name="Aleksander",Address="Dronningens Kongeprinsvei 1"},
            new Student{Name="Tommy",Address="Nærmeste Pub"},
            new Student{Name="Hans",Address="Lesesalen"},
            new Student{Name="Kim",Address="Ikke her"}
            };

            students.ForEach(s => context.Students.Add(s));
            context.SaveChanges();
            var courses = new List<Course>
            {
            new Course{CourseID=1050,Title="Teoretisk Kjemi"},
            new Course{CourseID=4022,Title="Java for Dummies"},
            new Course{CourseID=4041,Title="Funksjonell Programmering for Kjøleskap"},
            new Course{CourseID=1045,Title="Matte VII"},
            new Course{CourseID=3141,Title="Pubrunde"},
            new Course{CourseID=2021,Title="Praktisk Dataspilling"},
            new Course{CourseID=2042,Title="Kattegjeting"}
            };
            courses.ForEach(s => context.Courses.Add(s));
            context.SaveChanges();
            var enrollments = new List<Grade>
            {
            new Grade{StudentID=1,CourseID=1050,Grade_=GradeEnum.A},
            new Grade{StudentID=1,CourseID=4022,Grade_=GradeEnum.C},
            new Grade{StudentID=1,CourseID=4041,Grade_=GradeEnum.B},
            new Grade{StudentID=2,CourseID=1045,Grade_=GradeEnum.B},
            new Grade{StudentID=2,CourseID=3141,Grade_=GradeEnum.F},
            new Grade{StudentID=2,CourseID=2021,Grade_=GradeEnum.F},
            new Grade{StudentID=3,CourseID=1050},
            new Grade{StudentID=4,CourseID=1050,},
            new Grade{StudentID=4,CourseID=4022,Grade_=GradeEnum.F},
            new Grade{StudentID=5,CourseID=4041,Grade_=GradeEnum.C},
            new Grade{StudentID=6,CourseID=1045},
            new Grade{StudentID=7,CourseID=3141,Grade_=GradeEnum.A},
            };
            enrollments.ForEach(s => context.Grades.Add(s));
            context.SaveChanges();




        }



    }
}