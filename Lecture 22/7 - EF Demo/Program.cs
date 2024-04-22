using System;
using System.Linq;
using System.Data;
using System.Data.Entity;
using ConsoleApp22;

namespace DataBase {
    class Program {
        static void Main() {

            EntitiesDbContext dc = new EntitiesDbContext();

            DbSet<student> students = dc.student;

            var orderstudents = students.OrderBy(stud => stud.studentage).Where(stud => stud.studentname.Contains("x"));

            foreach (student s in orderstudents)
                Console.WriteLine("{0}({1})", s.studentname, s.studentage);
            Console.ReadKey();
            Console.WriteLine("================================");

            orderstudents = from stud in students
                            orderby stud.studentname
                            select stud;

            foreach (student s in orderstudents)
                Console.WriteLine("{0}({1})", s.studentname, s.studentage);

            Console.ReadKey();
        }
    }
}
