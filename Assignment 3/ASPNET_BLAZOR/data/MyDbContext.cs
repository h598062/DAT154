using ASPNET_BLAZOR.Entities;
using Microsoft.EntityFrameworkCore;

namespace ASPNET_BLAZOR.data;

public class MyDbContext : DbContext
{
    public MyDbContext(DbContextOptions<MyDbContext> options)
        : base(options)
    {
    }

    public DbSet<Student> Students { get; set; }
    public DbSet<Grade> Grades { get; set; }
    public DbSet<Course> Courses { get; set; }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Student>().ToTable("student", schema: "dbo");
        modelBuilder.Entity<Grade>().ToTable("grade", schema: "dbo");
        modelBuilder.Entity<Course>().ToTable("course", schema: "dbo");
        modelBuilder.Entity<Grade>().HasKey(e => new { e.StudentId, e.CourseCode });
    }
}