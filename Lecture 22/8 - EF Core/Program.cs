using _8___EF_Core.Models;
using Microsoft.EntityFrameworkCore;

Dat154Context dc = new();

DbSet<Student> students = dc.Students;

var orderstudents = students.OrderBy(stud => stud.Studentage)
                            .Where(stud => stud.Studentname.Contains("x"));

foreach (Student s in orderstudents) {
    Console.WriteLine($"{s.Studentname}({s.Studentage})");
}
Console.ReadKey();
Console.WriteLine("================================");

orderstudents = from stud in students
                orderby stud.Studentname
                select stud;

foreach (Student s in orderstudents) {
    Console.WriteLine($"{s.Studentname}({s.Studentage})");
}