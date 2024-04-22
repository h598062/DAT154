using System.Data.Entity;
using System.Data.Entity.ModelConfiguration.Conventions;
using StudentWeb.Models;

namespace StudentWeb.DAL
{
    public class SchoolContext : DbContext {

        public SchoolContext() : base("SchoolContext") {
            Database.SetInitializer<SchoolContext>(new SchoolInitializer());
        }

        public DbSet<Student> Students { get; set; }
        public DbSet<Grade> Grades { get; set; }
        public DbSet<Course> Courses { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder) {
            modelBuilder.Conventions.Remove<PluralizingTableNameConvention>();
        }

    }
}