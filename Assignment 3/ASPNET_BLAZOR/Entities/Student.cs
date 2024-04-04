using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ASPNET_BLAZOR.Entities;

public class Student
{
    [Key, Column("id", TypeName = "int")]
    public int Id { get; set; }

    [Column("studentname", TypeName = "varchar(50)")]
    public string Name { get; set; }

    [Column("studentage", TypeName = "int")]
    public int Age { get; set; }
}