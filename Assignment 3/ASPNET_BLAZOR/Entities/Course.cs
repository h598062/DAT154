using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ASPNET_BLAZOR.Entities;

[Table("course", Schema = "dbo")]
public class Course
{
    [Key, Column("coursecode", TypeName = "char(6)")]
    public string CourseCode { get; set; }
    
    [Column("coursename", TypeName = "varchar(50)")]
    public string CourseName { get; set; }
    
    [Column("semester", TypeName = "char(1)")]
    public char Semester { get; set; }
    
    [Column("teacher", TypeName = "varchar(50)")]
    public string Teacher { get; set; }
}