using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ASPNET_BLAZOR.Entities;

public class Student
{
    [Key, Column("id", TypeName = "int")]
    public int Id { get; set; }

    [Column("studentname", TypeName = "varchar(50)")]
    public string StudentName { get; set; }

    [Column("studentage", TypeName = "int")]
    public int StudentAge { get; set; }
}